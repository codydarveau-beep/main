"""Normal preservation checks for the reported regression batch, before extra reviews."""
from pathlib import Path
import hashlib,json,os,subprocess,sys
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source'
def sources():return {str(p.relative_to(R)):hashlib.sha256(p.read_bytes()).hexdigest()for p in sorted(S.rglob('*'))if p.is_file()and(p.suffix in ['.c','.h','.s','.inc']or p.name=='Makefile')}
before=sources();env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1',MYRO_ENEMY_PATH=str(R/'XboxFiles/enemies.bin'),MYRO_ACTOR_PATH=str(R/'XboxFiles/actors.bin'),MYRO_WORLD_PATH=str(R/'XboxFiles/world.bin'))
results=[]
def command(name,args):
 with(V/f'restoration270-{name}.log').open('w')as out:r=subprocess.run(args,cwd=R,env=env,stdout=out,stderr=subprocess.STDOUT)
 results.append(dict(name=name,passed=r.returncode==0,log=f'restoration270-{name}.log'));print(('PASS 'if not r.returncode else'FAIL ')+name,flush=True)
 if r.returncode:raise RuntimeError(name)
def fixture(name,src,assets=False,argv=[]):
 exe=V/f'restoration270-{name}_asan';args=['cc','-O0','-g','-fmax-errors=2','-fno-diagnostics-show-caret','-fsanitize=address,undefined','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-I'+str(S),str(R/src)]
 if assets:args += [str(S/'ui_assets.c'),str(S/'skin_assets.c')]
 args += ['-lm','-lz','-o',str(exe)];command(name+'-build',args);command(name,[str(exe),*argv])
try:
 for script in ['check_training_exit252.py','check_shared_ui253.py','check_inline_buttons254.py','check_icon_sampling268.py']:command(script,[sys.executable,str(R/'Preparation'/script)])
 fixtures=[('controls','Validation/test_controls254.c'),('button-tokens','Validation/test_button_tokens254.c'),('diagnostics','Validation/test_diagnostics261.c'),('quests','Validation/test_quests257.c'),('quest-marks','Validation/test_quest_marks269.c'),('creator','Validation/test_creator265.c'),('damage','Validation/test_damage262.c'),('willow','Validation/test_willow_layers259.c'),('equipment','Validation/test_equipment_preview260.c'),('bash','Validation/test_bash263.c'),('bash-fx','Validation/test_bash_fx263.c'),('basic-contact','Validation/test_basic_contact267.c'),('dialogue','Validation/test_dialogue264.c'),('empty-dialogue','Validation/test_dialogue_empty264.c'),('gui-contract','Validation/test_gui_contract270.c'),('training-floor','Validation/training-reach266.c'),('guardian-cadence','Validation/guardian-cadence265.c'),('guardian-sprites','Validation/guardian-sprites265.c'),('sprite-safety','Validation/test_sprite_safety253.c'),('packet-timing','Source/test_timing49.c'),('legacy-combat-regression','Source/test_review50c.c')]
 for name,src in fixtures:fixture(name,src)
 # Assert that the copied rendering fixture still contains exact production functions.
 prod=(S/'frontend_xbox56.h').read_text();test=(V/'test_creator_draw265.c').read_text()
 for name in ['frontend_stat_line112','frontend_stat_web58','frontend_keyboard56']:
  start=prod.index('static void '+name+'(');a=prod.index('{',start);i=a+1;depth=1
  while depth:depth+=(prod[i]=='{')-(prod[i]=='}');i+=1
  assert prod[start:i]in test,name
 fixture('creator-draw','Validation/test_creator_draw265.c',True)
 fixture('tutorial-branches','Validation/check_tutorial264.c',False,[str(R.parent/'packet194/released-scripts.bin')])
 assert before==sources(),'Source changed during normal preservation checks'
 passed=True
except Exception as error:
 print('STOP',str(error),flush=True);passed=False
report=dict(passed=passed,phase='normal regression preservation checks',sourceFiles=before,commands=results,normalReleaseWideChecksComplete=False,additionalReviewPassesStarted=False,additionalReviewPassesCompleted=0,packagingValidated=False,originalXboxPlaytested=False,xemuPlaytested=False,limitations=['Host CPU/sanitizer and modeled GPU boundaries; no target raster, controller, CRT or64MB acceptance','Native/tutorial prerequisites are explicit fixtures where stated','Generic normal contact phase is reconstructed; Bash phase and icon sampling arithmetic are independently recovered'])
(V/'Restoration-Normal-Checks270.json').write_text(json.dumps(report,indent=2)+'\n')
if not passed:raise SystemExit(1)
print('PASS focused preservation normal checks; final release-wide completion and two additional reviews remain separate.')
