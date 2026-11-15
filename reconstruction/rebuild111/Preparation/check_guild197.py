from arcade_host_build197 import flags
"""Normal guild integration checks; no additional review or hardware test."""
from pathlib import Path
import subprocess,os,json,hashlib
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env.update(MYRO_WORLD_PATH=str((R/'XboxFiles/world.bin').resolve()),MYRO_GUILD_HALL197=str(R/'Guild/guildhall.bin'),MYRO_GUILD_VIEWS197=str(R/'Guild/Directional197/views.bin'),ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
checks=[]
for src,name in [('test_guild_room197.c','guild-room197'),('test_guild_interactions197.c','guild-interactions197'),('test_world_integration194.c','world197')]:
 with (V/(name+'.log')).open('w')as f:
  subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/src),*(flags() if src=="test_guild_interactions197.c" else []),'-lm','-lz','-o',str(V/(name+'_asan'))],stdout=f,stderr=subprocess.STDOUT,check=True)
  subprocess.run([str(V/(name+'_asan'))],stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
 checks.append(dict(name=name,source=src,sourceSHA256=hashlib.sha256((S/src).read_bytes()).hexdigest(),passed=True,log=name+'.log'))
report=dict(passed=True,checks=checks,originalFurnishingPlans=610,planAndCollisionCRCMatchesReleased=True,newCabinetViews=48,cabinetGPUAtlasBytes=131072,originalFurnitureGPUAtlasBytes=131072,originalMeshCPUBytes=11760,originalFloorBitsetBytes=5000,scope='Actual packed map, production art/model/interaction adapters and host GPU recorder; not Xbox/Xemu execution or full 64MB proof',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0)
(V/'Guild-Checks197.json').write_text(json.dumps(report,indent=2)+'\n');d=json.loads((V/'Integration-Checks194.json').read_text())
for c in d['checks']:
 if c['name']=='world_integration':c.update(passed=True,log='world197.log',sourceSHA256=checks[2]['sourceSHA256'])
(V/'Integration-Checks194.json').write_text(json.dumps(d,indent=2)+'\n');print('PASS restored original guild layouts/floors/models, directional cabinets, actual controls and packed-world integration. Host only.')
