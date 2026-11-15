"""Recover data tables from verified released bytes; never edit the old source.

The resulting header is a staged reconstruction, not an integrated game build.
"""
from pathlib import Path
import hashlib
import json
import re
import struct

ROOT = Path(__file__).resolve().parent
OLD = Path('/workspace/myro/dev200/Source')
xbe = (ROOT / 'released-default.xbe').read_bytes()
wire = (ROOT / 'released-scripts.bin').read_bytes()
programs = json.loads((ROOT / 'released-program-index.json').read_text())
old = (OLD / 'npc_registry_data55.h').read_text()
base, = struct.unpack_from('<I', xbe, 0x104)
count, table_va = struct.unpack_from('<II', xbe, 0x11c)
sections = [struct.unpack_from('<14I', xbe, table_va - base + i * 56) for i in range(count)]


def offset(va):
    matches = [s[3] + va - s[1] for s in sections if s[1] <= va < s[1] + s[4]]
    assert len(matches) == 1, hex(va)
    return matches[0]


def string(va):
    start = offset(va)
    end = xbe.find(b'\0', start, start + 4096)
    assert end >= start
    return xbe[start:end].decode('utf-8')


def occurrences(needle):
    start = 0
    while True:
        at = xbe.find(needle, start)
        if at < 0:
            break
        yield at
        start = at + 1


def addresses(text):
    for at in occurrences(text.encode() + b'\0'):
        for section in sections:
            if section[3] <= at < section[3] + section[4]:
                yield section[1] + at - section[3]


record_prefix = struct.pack('<12I', 1, 29, 65535, 4, 4, 0, 0xffffffff, 0xffffffff, 0, 0, 0, 3)
candidates = []
for at in occurrences(record_prefix):
    if at + 10181 * 60 > len(xbe):
        continue
    rows = []
    try:
        for i in range(10181):
            raw = list(struct.unpack_from('<15I', xbe, at + i * 60))
            assert raw[0] == i + 1 and raw[1] <= 3948
            assert raw[2] == 65535 or raw[2] < 495
            for field in (6, 7):
                if raw[field] & 0x80000000:
                    raw[field] -= 1 << 32
            rows.append(raw[:12] + [string(p) for p in raw[12:]])
        assert rows[0][12] == 'HerculesMOTD'
    except (AssertionError, UnicodeDecodeError, struct.error):
        continue
    candidates.append((at, rows))
assert len(candidates) == 1
record_offset, records = candidates[0]

old_maps = json.loads('[' + re.search(r'mapNames\[\]=\{(.*?)\}', (OLD / 'world_data.h').read_text(), re.S)[1] + ']')
map_candidates = []
for first_address in addresses(old_maps[0]):
    for at in occurrences(struct.pack('<I', first_address)):
        try:
            names = [string(struct.unpack_from('<I', xbe, at + i * 4)[0]) for i in range(495)]
            assert names[:494] == old_maps and names[494] == 'guild_in194'
        except (AssertionError, UnicodeDecodeError, struct.error):
            continue
        map_candidates.append((at, names))
assert len(map_candidates) == 1
map_offset, names = map_candidates[0]

function_text = re.search(r'npcFunctions55\[\]=\{(.*?)\};', old, re.S)[1]
functions = [(json.loads('"' + name + '"'), int(pid)) for name, pid in re.findall(r'\{"((?:\\.|[^"\\])*)",(\d+)u\}', function_text)]
function_candidates = []
for first_address in addresses(functions[0][0]):
    for at in occurrences(struct.pack('<II', first_address, functions[0][1])):
        try:
            rows = [(string(struct.unpack_from('<I', xbe, at + i * 8)[0]), struct.unpack_from('<I', xbe, at + i * 8 + 4)[0]) for i in range(len(functions))]
            assert rows == functions
        except (AssertionError, UnicodeDecodeError, struct.error):
            continue
        function_candidates.append(at)
assert len(function_candidates) == 1

timers = []
for program in programs:
    meta = program['deployedMetadata']
    labels = dict(zip(program['labels'], [entry[1] for entry in program['labelEntries']]))
    assert meta[3:6] == [labels.get(k, 0xffffffff) for k in ['OnInit', 'OnTouch', 'OnTouch_']]
    own_timers = sorted((int(name[7:]), pc) for name, pc in labels.items() if re.fullmatch(r'OnTimer\d+', name))
    assert meta[6:] == [len(timers), len(own_timers)]
    timers.extend(own_timers)

def quote(text):
    return json.dumps(text, ensure_ascii=False)


def array(rows):
    return ',\n'.join('{' + ','.join(str(v) + 'u' for v in row) + '}' for row in rows)


header = '/* Reconstructed from released 1.10.0 default.xbe and scripts.bin.\n * Generated data only; runtime integration and native validation are pending. */\n'
header += '#ifndef MYRO_NPC_REGISTRY_DATA55_H\n#define MYRO_NPC_REGISTRY_DATA55_H\n'
header += '#define NPC_RECORD_COUNT55 10181u\n#define NPC_PROGRAM_COUNT55 3948u\n'
header += f'#define NPC_SCRIPT_FILE_BYTES55 {len(wire)}u\n'
# The old runtime branches on this preprocessor value. Its deployed value is
# not established by the data tables, so do not silently copy the old value.
header += '/* NPC_RELEASE_JOBS_ONLY55 is unresolved and intentionally undefined. */\n'
header += 'typedef struct{unsigned id,program,map,x,y,direction;int model,view;unsigned rx,ry,kind,flags;const char*name,*label,*unique;}NpcRecord55;\n'
header += 'static const NpcRecord55 npcRecords55[]={\n'
header += ',\n'.join('{' + ','.join(map(str, row[:12])) + ',' + ','.join(quote(s) for s in row[12:]) + '}' for row in records) + '\n};\n'
header += 'static const struct{unsigned offset,bytes,owner,init,touch,touchPlayer,timerStart,timerCount;}npcProgramFiles55[]={\n' + array([p['deployedMetadata'] for p in programs]) + '\n};\n'
header += 'static const struct{unsigned delay,entry;}npcTimerLabels55[]={\n' + array(timers) + '\n};\n'
header += 'static const struct{const char*name;unsigned program;}npcFunctions55[]={'+ ','.join('{' + quote(n) + ',' + str(pid) + 'u}' for n, pid in functions) + '};\n'
by_map = [[i for i, row in enumerate(records) if row[2] == m] for m in range(495)]
flat, spans = [], []
for group in by_map:
    spans.append((len(flat), len(group)))
    flat.extend(group)
header += 'static const unsigned short npcMapRecords55[]={' + ','.join(map(str, flat)) + '};\n'
header += 'static const struct{unsigned start,count;}npcMapSpans55[]={\n' + array(spans) + '\n};\n'
order = sorted(range(len(records)), key=lambda i: records[i][14].encode())
header += 'static const unsigned short npcNameOrder55[]={' + ','.join(map(str, order)) + '};\n'
header += old[old.index('static int npc_record_name55'):]
dest = ROOT / 'RecoveredMetadata'
dest.mkdir(exist_ok=True)
(dest / 'npc_registry_data55.h').write_text(header)
(dest / 'released-map-names.json').write_text(json.dumps(names, indent=2) + '\n')
old_rows = []
for match in re.finditer(r'^\{([\d,\-]+),"((?:\\.|[^"\\])*)"', old, re.M):
    values = list(map(int, match[1].split(',')))
    if len(values) == 12:
        old_rows.append(values)
changes = [{'id': row[0], 'before': old_rows[i], 'released': row[:12]} for i, row in enumerate(records) if row[:12] != old_rows[i]]
report = {
    'status': 'Reconstructed metadata, not runtime-integrated',
    'xbeSHA256': hashlib.sha256(xbe).hexdigest(), 'scriptsSHA256': hashlib.sha256(wire).hexdigest(),
    'npcTableXbeOffset': record_offset, 'functionTableXbeOffset': function_candidates[0],
    'mapNamesXbeOffset': map_offset, 'records': len(records), 'programs': len(programs),
    'maps': len(names), 'functionsMatchedToXbe': len(functions), 'timerLabelsValidated': len(timers),
    'changedRecords': changes, 'headerSHA256': hashlib.sha256(header.encode()).hexdigest(),
    'remainingPrivateMapsUnavailable': ['story_thana194', 'story_moc194'],
    'unresolvedRuntimeMacro': 'NPC_RELEASE_JOBS_ONLY55',
}
(ROOT / 'released-registry-recovery.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({k: v for k, v in report.items() if k != 'changedRecords'}, indent=2))
print('Changed record rows:', len(changes))
