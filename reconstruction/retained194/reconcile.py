"""Inventory retained excerpts against immutable local source and released data.

This does not modify the game, infer missing policy, or generate runtime headers.
"""
from pathlib import Path
import hashlib
import json
import re
import struct
import zlib

ROOT = Path(__file__).resolve().parent
SOURCE = Path('/workspace/myro/dev200/Source')
RECOVERY = ROOT.parent


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def save(name, value):
    (ROOT / name).write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n')


packet = (ROOT / 'recovery-packet-original.txt').read_bytes()
text = packet.decode('utf-8')
sections = list(re.finditer(r'^\*\*(\d+)\. .*$', text, re.M))
complete = {
    1: 'career_access194.h', 2: 'career_warp194.h',
    3: 'campaign_access194.h', 4: 'native_admission194.h',
    8: 'regional194.h', 9: 'regional_world194.h',
}
out = ROOT / 'Source'
out.mkdir(exist_ok=True)
headers = []
for i, section in enumerate(sections):
    number = int(section[1])
    if number not in complete:
        continue
    end = sections[i + 1].start() if i + 1 < len(sections) else len(text)
    block = re.search(r'^```c\n(.*?)^```', text[section.end():end], re.M | re.S)
    assert block, complete[number]
    raw = block[1].encode('utf-8')
    target = out / complete[number]
    target.write_bytes(raw)
    headers.append({'name': target.name, 'section': number, 'bytes': len(raw),
                    'sha256': digest(raw), 'status': 'verbatim excerpt; not integrated'})
assert len(headers) == 6

include_report = []
for header in headers:
    for include in re.findall(r'^#include "([^"]+)"', (out / header['name']).read_text(), re.M):
        location = 'packet' if (out / include).exists() else 'earlier snapshot' if (SOURCE / include).exists() else 'missing'
        include_report.append({'header': header['name'], 'include': include, 'location': location})

registry = (SOURCE / 'npc_registry_data55.h').read_text()
old_entries_text = re.search(r'npcProgramFiles55\[\]=\{(.*?)\};', registry, re.S)[1]
old_entries = [list(map(int, re.findall(r'\d+', row)))
               for row in re.findall(r'\{([^{}]+)\}', old_entries_text)]
assert len(old_entries) == 3948

baseline = json.loads((RECOVERY / 'baseline-file-verification.json').read_text())
info = baseline['files']['scripts.bin']
with (RECOVERY / 'released-1.10.0.iso').open('rb') as f:
    f.seek(info['isoOffset'])
    scripts = f.read(info['bytes'])
assert digest(scripts) == info['sha256'] == 'a101e501cbc97b73b7268e0ba3a3f7361c2f3624416be51c6b5f6b1fe1fea93e'
(ROOT / 'released-scripts.bin').write_bytes(scripts)

info_xbe = baseline['files']['default.xbe']
with (RECOVERY / 'released-1.10.0.iso').open('rb') as f:
    f.seek(info_xbe['isoOffset'])
    xbe = f.read(info_xbe['bytes'])
assert digest(xbe) == info_xbe['sha256']
(ROOT / 'released-default.xbe').write_bytes(xbe)

# Recover the actually deployed table, rather than interpreting obsolete offsets
# or assuming that the last occurrence of an owner is the active program.
needle = struct.pack('<8I', *old_entries[0])
table_candidates = []
scan = 0
while True:
    found = xbe.find(needle, scan)
    if found < 0:
        break
    scan = found + 1
    if found + 3948 * 32 > len(xbe):
        continue
    rows = [list(struct.unpack_from('<8I', xbe, found + i * 32)) for i in range(3948)]
    if all(start + size <= len(scripts) and scripts[start:start + 8] == b'MYRONP55'
           and struct.unpack_from('<I', scripts, start + 12)[0] == size
           and struct.unpack_from('<I', scripts, start + 36)[0] == owner
           for start, size, owner, *_ in rows):
        table_candidates.append((found, rows))
assert len(table_candidates) == 1, 'Deployed lookup table must be unique'
table_offset, deployed_entries = table_candidates[0]

programs = []
for program_id, deployed in enumerate(deployed_entries, 1):
    start, size = deployed[:2]
    end = start + size
    assert size >= 40 and end <= len(scripts)
    raw = scripts[start:end]
    assert raw[:8] == b'MYRONP55'
    version, length, nc, ns, nl, nf, crc, owner = struct.unpack_from('<8I', raw, 8)
    assert version == 1 and length == size
    assert 40 + nc * 12 + (nl + nf) * 8 + ns == size
    assert zlib.crc32(raw[36:], zlib.crc32(raw[:32])) == crc
    assert 0 < nc <= 65536 and 0 < ns <= 262144 and nl <= nc and nf <= nc
    strings = raw[40 + nc * 12 + (nl + nf) * 8:]
    assert strings[0] == strings[-1] == 0

    def string(offset):
        assert 0 <= offset < ns
        stop = strings.find(b'\0', offset)
        assert stop >= 0
        return strings[offset:stop].decode('utf-8', 'replace')

    calls = set()
    for i in range(nc):
        op, a, b = struct.unpack_from('<III', raw, 40 + i * 12)
        assert op <= 15
        if op in (2, 3, 12):
            name = string(a)
            if op == 12:
                assert b <= 512
                calls.add(name)
        elif op in (10, 11):
            assert a < nc
        elif op == 8:
            assert a <= 3
        elif op == 9:
            assert a <= 16
        elif op == 15:
            assert a <= 1 and b <= 1
    entry_names = []
    for i in range(nl + nf):
        name, pc = struct.unpack_from('<II', raw, 40 + nc * 12 + i * 8)
        assert string(name) and pc < nc
        entry_names.append(string(name))
    assert len(set(entry_names[:nl])) == nl
    assert len(set(entry_names[nl:])) == nf
    old = old_entries[program_id - 1]
    programs.append({'id': program_id, 'offset': start, 'bytes': size, 'owner': owner,
                     'sha256': digest(raw), 'instructions': nc, 'calls': sorted(calls),
                     'sameOwnerAsSnapshot': owner == old[2],
                     'sameOffsetAndLengthAsSnapshot': [start, size] == old[:2],
                     'deployedMetadata': deployed,
                     'labels': entry_names[:nl], 'functions': entry_names[nl:],
                     'labelEntries': [list(struct.unpack_from('<II', raw, 40 + nc * 12 + i * 8)) for i in range(nl)],
                     'functionEntries': [list(struct.unpack_from('<II', raw, 40 + nc * 12 + (nl + i) * 8)) for i in range(nf)]})
assert len(programs) == 3948
assert all(p['sameOwnerAsSnapshot'] for p in programs)
save('released-program-index.json', programs)

records = []
for match in re.finditer(r'^\{([\d,\-]+),"((?:\\.|[^"\\])*)"', registry, re.M):
    values = list(map(int, match[1].split(',')))
    if len(values) != 12:
        continue
    records.append(dict(zip(['id', 'program', 'map', 'x', 'y', 'direction', 'model', 'view', 'rx', 'ry', 'kind', 'flags'], values), name=match[2]))
assert len(records) == 10181
careers = [r for r in records if r['id'] in (7351, 7588)]
assert [(r['id'], r['program']) for r in careers] == [(7351, 3829), (7588, 3886)]
maps = json.loads('[' + re.search(r'mapNames\[\]=\{(.*?)\}', (SOURCE / 'world_data.h').read_text(), re.S)[1] + ']')
save('reconciliation.json', {
    'packetSHA256': digest(packet), 'packetBytes': len(packet), 'headers': headers,
    'includes': include_report, 'releasedScriptsSHA256': digest(scripts),
    'releasedProgramTableXbeOffset': table_offset,
    'programSelection': 'Exact deployed XBE lookup table; unique validated table candidate',
    'releasedScriptsBytes': len(scripts), 'snapshotScriptsBytes': int(re.search(r'NPC_SCRIPT_FILE_BYTES55 (\d+)', registry)[1]),
    'programs': len(programs), 'sameProgramOwners': sum(p['sameOwnerAsSnapshot'] for p in programs),
    'changedProgramOffsetsOrLengths': sum(not p['sameOffsetAndLengthAsSnapshot'] for p in programs),
    'npcRecords': len(records), 'careerRecordIdsAreOneBased': True, 'originalCareerRecords': careers,
    'snapshotMaps': len(maps), 'packetPolicyMaps': 497,
    'absentPacketMaps': [n for n in ['guild_in194', 'story_thana194', 'story_moc194'] if n not in maps],
    'transitiveDependenciesRegenerated': False, 'runtimeIntegrated': False,
    'nativeCompiled': False, 'hostSuitesRerun': False, 'xboxPlaytested': False,
    'additionalReviewPassesCompleted': 0,
})
print(json.dumps({
    'headers': len(headers), 'releasedProgramsValidated': len(programs),
    'ownerMatches': sum(p['sameOwnerAsSnapshot'] for p in programs),
    'changedOffsetsOrLengths': sum(not p['sameOffsetAndLengthAsSnapshot'] for p in programs),
    'missingIncludes': sorted({x['include'] for x in include_report if x['location'] == 'missing'}),
    'snapshotMaps': len(maps), 'packetPolicyMaps': 497,
}, indent=2))
