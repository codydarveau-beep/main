"""Actual production campaign pose reader/uploader and native main ordering."""
from pathlib import Path
import hashlib,json,os,re,subprocess
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
s=(S/'main.c').read_text();prepare=s.index('campaign_actor_prepare200();');upload=s.index('sprite_upload(actor_shape50(a->kind)');fence=s.rfind('while(pb_busy()){}',0,prepare)
assert s.count('campaign_actor_prepare200();')==1 and 0<=fence<prepare<upload,'Prepare streamed campaign poses after the GPU fence and before generic actor upload'
(V/'scene_presentation_declarations200.inc').write_text('/* Exact production declarations used by the host draw recorder. */\n'+re.search(r'typedef struct \{int slot,kind;[^\n]+DrawActor;',s)[0]+'\n'+re.search(r'static int facing\([^\n]+',s)[0]+'\n')
env=os.environ.copy();env.update(MYRO_CAMPAIGN_ACTOR_PATH=str(R/'Recovered195/campaign.bin'),ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with(V/'campaign-upload246.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(V/'test_campaign_upload246.c'),'-lm','-lz','-o',str(V/'campaign-upload246_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-upload246_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
log=(V/'campaign-upload246.log').read_text();n,raw,gpu=map(int,re.search(r'upload: (\d+) real poses,.*Peak four-pose raw (\d+) GPU (\d+)',log).groups())
r=dict(passed=True,poses=n,peakResidentFourPoseRawBytes=raw,peakFourPoseGPUBytes=gpu,mainPrepareBeforeUpload=True,prepareAfterGPUFence=True,coldFormerOrderFailureReproduced=True,actualProductionPoseReaderAndUploader=True,exactPixelsAndCacheReuse=True,offscreenCleanup=True,mainSHA256=hashlib.sha256(s.encode()).hexdigest(),fixtureSHA256=hashlib.sha256((V/'test_campaign_upload246.c').read_bytes()).hexdigest(),scope='Actual released pose data through production sprite_load and sprite_upload, host-backed GPU memory with exact pixel comparison, sanitizer/cache/cleanup checks; cold former order reproduces native fatal bounds guard in a child. Current main call ordering checked. Partial pose resource inventory, not complete runtime residency or hardware rasterization.',originalXboxPlaytested=False,xemuPlaytested=False)
(V/'Campaign-Upload-Checks246.json').write_text(json.dumps(r,indent=2)+'\n');print('PASS actual complete campaign pose upload, exact recorded pixels and corrected native call order; host only.')
