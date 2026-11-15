"""Use real production sprite and art readers against all restored released art."""
from pathlib import Path
import json,re,subprocess,os,hashlib
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';D=R/'Recovered195';data=json.loads((D/'content-recovery195.json').read_text())
s=(S/'sprites.h').read_text().split('#include "enemy_stream51.h"')[0];s=s.replace('static SparseSprite sprites[MOB_SPEC_COUNT+1];static unsigned spriteEpoch;','').replace('#include "enemy_blobs.h"','')
(V/'actual_sprite195.inc').write_text(s)
portraitByOffset={t['offset']:t for t in data['portraits.bin']['streams']}
expected='static const unsigned portraitRawCRC195[]={'+','.join(str(portraitByOffset[t[1]]['rawCRC'])+'u'for t in data['portraits.bin']['metadata'])+'};\n'
(V/'portrait_crc195.h').write_text(expected)
cmd=['cc','-std=c99','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_content195.c'),'-lm','-lz','-o',str(V/'content195_asan')]
subprocess.run(cmd,check=True);env=os.environ.copy();env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1'
subprocess.run([str(V/'content195_asan'),str(D)],env=env,check=True)
report=dict(passed=True,actorSources=data['campaign.bin']['actorCount'],actorPoses=len(data['campaign.bin']['streams']),npcEffectFrames=len(data['npcfx.bin']['metadata']),npcEffectClips=len(data['npcfx.bin']['clips']),npcPortraits=len(data['portraits.bin']['metadata']),storyExpressions=len(data['storyportraits.bin']['metadata']),rosterMappings=len(data['roster']['rows']),sourceSpriteReaderSHA256=hashlib.sha256(s.encode()).hexdigest(),scope='Actual production readers, complete restored catalogs, CRC/bounds and failed-read/corruption checks under ASan/UBSan/leak checks. No native/Xbox/Xemu execution. Four visible sprite slots retained.',storyActivation=False)
(V/'Content-Checks195.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report))
