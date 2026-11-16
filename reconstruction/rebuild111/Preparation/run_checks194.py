from arcade_host_build197 import flags
from pathlib import Path
import subprocess,concurrent.futures,json,os,hashlib,time
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source'
names=['travel_preflight','policy','native_lifecycle','guild_regional','guild_ui','world_integration']
def check(name):
 source=S/('test_'+name+'194.c');binary=V/('test_'+name+'194_asan');log=V/(name+'194.log')
 cmd=['cc','-std=c99','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-I'+str(S),str(source),*(flags() if name=="guild_ui" else []),'-lm','-lz','-o',str(binary)]
 env=os.environ.copy();env['MYRO_WORLD_PATH']=str(R/'XboxFiles/world.bin');env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1'
 with log.open('w')as f:
  f.write('HOST ONLY: address/undefined sanitizers. No native build or Xbox/Xemu playtest.\n');f.flush()
  build=subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT)
  if build.returncode:return {'name':name,'passed':False,'phase':'host compilation','log':log.name}
  args=[str(binary)]+([str(R.parent/'packet194/released-scripts.bin')]if name=='travel_preflight'else[])
  run=subprocess.run(args,stdout=f,stderr=subprocess.STDOUT,env=env)
 return {'name':name,'passed':run.returncode==0,'phase':'host execution','log':log.name,'sourceSHA256':hashlib.sha256(source.read_bytes()).hexdigest()}
results=[]
with concurrent.futures.ThreadPoolExecutor(max_workers=2)as pool:
 for result in pool.map(check,names):results.append(result);print(json.dumps(result),flush=True)
report={'scope':'Reconstructed policy/preflight/guild/dispatch integration; HOST tests only','checks':results,'allPassed':all(x['passed']for x in results),'nativeCompiled':False,'originalXboxPlaytested':False,'xemuPlaytested':False,'additionalReviewPassesCompleted':0}
(V/'Integration-Checks194.json').write_text(json.dumps(report,indent=2)+'\n')
raise SystemExit(0 if report['allPassed']else 1)
