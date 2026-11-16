"""Normal streaming/all-map allocation coverage, not a 64MB runtime claim."""
from pathlib import Path
import subprocess,os,json,struct,re
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env['MYRO_WORLD_PATH']=str(R/'XboxFiles/world.bin')
with(V/'world-residency234.log').open('w')as out:
 subprocess.run(['cc','-O1','-I'+str(S),str(S/'test_world_residency234.c'),'-lm','-lz','-o',str(V/'world-residency234')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'world-residency234')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
rows=[tuple(map(int,m))for m in re.findall(r'MAP (\d+) GPU (\d+) grid (\d+) (\d+) terrain (\d+) (\d+)',(V/'world-residency234.log').read_text())];assert len(rows)==497
x=(S/'main.exe').read_bytes();p=struct.unpack_from('<I',x,60)[0];image=struct.unpack_from('<I',x,p+24+56)[0];peak=max(rows,key=lambda r:r[1]);
(V/'World-Residency-Checks234.json').write_text(json.dumps(dict(passed=True,maps=len(rows),nativeImageBytes=image,peakWorldGPUBytes=peak[1],peakMap=peak[0],mapGPUBytes={str(r[0]):r[1]for r in rows},scope='Actual current-source world blob decode/activation for every map and alias with tracked CPU-backed GPU allocations, map-to-map cleanup and no recorded GPU leaks. PE SizeOfImage records native static image commitment. This is a partial resource inventory: native heap/transient decode/framebuffers/audio/render caches/full guild layout and real Xbox memory/high-water/timing require separate evidence. No 64MB acceptance or target execution claim.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS all-map streaming and tracked world allocations; full Xbox64 residency remains separate.')
