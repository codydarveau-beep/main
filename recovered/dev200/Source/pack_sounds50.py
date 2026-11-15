"""MIT. Append original class WAVs as bounded, disc-backed 48 kHz mono PCM16."""
from pathlib import Path
import hashlib,json,re,struct,subprocess,zlib,sys
from concurrent.futures import ThreadPoolExecutor
from asset_index50 import paths,key50
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48/roBrowserLegacy/src'
source=(r/'collect_requests50.py').read_text();ns=dict(re=re,json=json);exec(source[source.index('def js_string'):source.index('const={')],ns)
table=(ref/'DB/Effects/EffectTable.js').read_text();blocks={m[1].strip("'"):ns['balanced'](table,table.index('[',m.start())) for m in re.finditer(r"(?m)^\s*(\d+|[a-zA-Z_][\w]*|'[^']+'):\s*\[",table)}
trace=json.loads((r/'class_asset_audit50.json').read_text())['effectTrace'];catalog=json.loads((r.parent/'ClassAssets50/catalog50.json').read_text());mapping=[]
def wav_key(value):return key50('data/wav/'+value+('' if value.lower().endswith('.wav') else '.wav'))
for skill in catalog['skills']:
    if skill['id']<127 and skill['id']!=7 or skill['id'] in [171,253] or skill['passive']:continue
    sounds=[]
    for effect in trace.get(skill['key'],[]):
        block=ns['masked'](blocks.get(effect,''),False)
        for match in re.finditer(r"\bwav:\s*('(?:\\.|[^'])*'|\"(?:\\.|[^\"])*\")",block):
            name=ns['js_string'](match[1]);key=wav_key(name)
            if name and not name.startswith('_') and key not in sounds:sounds.append(key)
    if skill['id']==202:sounds=[wav_key('effect/ef_hit2'),wav_key('effect/ef_hit4'),wav_key('effect/ef_hit2')]
    if skill['id']==234:sounds=[wav_key('effect/black_maximize_power_circle.wav'),wav_key('effect/black_maximize_power_sword.wav'),wav_key('effect/black_maximize_power_sword.wav'),wav_key('effect/black_maximize_power_sword_bic.wav')]
    if sounds:
        delays=[0]*len(sounds)
        if skill['id']==234:delays=[1,550,700,950]
        elif skill['id']==202:delays=[0,200,400]
        mapping.append(dict(skill=skill['id'],key=skill['key'],owners=skill['owners'],sounds=sounds,delays=delays))
expected=mapping.copy();missing=sorted({key for row in mapping for key in row['sounds'] if key not in paths});assert not missing or '--prepare-received' in sys.argv,missing
mapping=[row for row in mapping if all(k in paths for k in row['sounds'])];keys=sorted({key for row in mapping for key in row['sounds']})
report=json.loads((r/'systems50.json').read_text());base_blobs=report['blobs'][:25];cut=base_blobs[-1]['offset']+base_blobs[-1]['packed'];pack=r.parent/'Systems/systems.bin';payload=bytearray(pack.read_bytes()[:cut]);blobs=base_blobs.copy();sfx=[]
def decode(key):
    pcm=subprocess.run(['ffmpeg','-v','error','-i',str(paths[key]),'-ac','1','-ar','48000','-f','s16le','pipe:1'],check=True,capture_output=True).stdout
    assert pcm and len(pcm)%2==0 and len(pcm)<4*1024*1024;return key,pcm
with ThreadPoolExecutor(max_workers=4) as pool:
    for key,pcm in pool.map(decode,keys):
        cp=zlib.compress(pcm,9);b=dict(name=key,offset=len(payload),packed=len(cp),raw=len(pcm),crc=zlib.crc32(cp));blob=len(blobs);blobs.append(b);payload.extend(cp)
        owners=sorted({owner for row in mapping if key in row['sounds'] for owner in row['owners']});sfx.append(dict(id=60+len(sfx),blob=blob,key=key,frames=len(pcm)//2,owners=owners,rawSHA256=hashlib.sha256(pcm).hexdigest(),sourceSHA256=hashlib.sha256(paths[key].read_bytes()).hexdigest()))
lookup={v['key']:v['id'] for v in sfx};out='/* Original class sounds; base native sound IDs0..59 unchanged. */\n#ifndef MYRO_CLASS_SOUND_DATA50_H\n#define MYRO_CLASS_SOUND_DATA50_H\n#define CLASS_SOUND_COUNT50 %d\n#define SOUND_TOTAL50 %d\ntypedef struct{unsigned blob,frames,owners;} ClassSound50;\nstatic const ClassSound50 classSounds50[CLASS_SOUND_COUNT50]={\n'%(len(sfx),60+len(sfx))
out+=','.join('{%d,%d,%du}'%(v['blob'],v['frames'],sum(1<<o for o in v['owners'])) for v in sfx)+'};\ntypedef struct{unsigned skill,count,ids[4],delayMS[4];} ClassSoundSkill50;\nstatic const ClassSoundSkill50 classSoundSkills50[]={\n'
for row in mapping:
    assert len(row['sounds'])<=4;out+='{%d,%d,{%s},{%s}},\n'%(row['skill'],len(row['sounds']),','.join(str(lookup[k]) for k in row['sounds']),','.join(map(str,row['delays'])))
out+='};\n#endif\n';(r/'class_sound_data50.h').write_text(out)
header=(r/'system_data50.h').read_text();a=header.index('static const SystemBlob50 systemBlobs50');b=header.index('static const float companionContact50',a)
header=header[:a]+'static const SystemBlob50 systemBlobs50[SYSTEM_BLOBS50]={\n'+','.join('{%d,%d,%d,%du}'%(v['offset'],v['packed'],v['raw'],v['crc']) for v in blobs)+'};\n'+header[b:];header=re.sub(r'SYSTEM_FILE_BYTES50 \d+','SYSTEM_FILE_BYTES50 '+str(len(payload)),header);header=re.sub(r'SYSTEM_BLOBS50 \d+','SYSTEM_BLOBS50 '+str(len(blobs)),header);(r/'system_data50.h').write_text(header);pack.write_bytes(payload)
report['blobs']=blobs;report['sha256']=hashlib.sha256(payload).hexdigest();report['sounds']=sfx;(r/'systems50.json').write_text(json.dumps(report,indent=2)+'\n');(r/'class_sounds50.json').write_text(json.dumps(dict(source='Hercules21b27966/roBrowserLegacy2dc0d153',complete=not missing,missing=missing,expectedMappings=expected,mapping=mapping,sounds=sfx),indent=2)+'\n')
# Extend only the two lookup arrays; all original sample values are untouched.
p=r/'sound_assets.c';text=p.read_text()
for name in ['soundData','soundLengths']:
    m=re.search(r'\b'+name+r'\[\]=\{([^}]+)\}',text);values=m[1].split(',')[:60];assert len(values)==60;values+=['0']*len(sfx);text=text[:m.start(1)]+','.join(values)+text[m.end(1):]
text=text.replace('const unsigned soundLengths[]','unsigned soundLengths[]');p.write_text(text)
print('PASS50',len(sfx),'original WAVs;',len(mapping),'skill sound mappings; system pack',len(payload),'bytes; fixed old60sound IDs and samples.')
