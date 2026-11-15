# MIT. Exercise HUD using the actual SDK asserting math stub, not host libm.
from pathlib import Path
import subprocess,tempfile,sys,os
r=Path(__file__).resolve().parent;nxdk=Path(sys.argv[1])if len(sys.argv)>1 else r.parent.parent/'toolchain/xbox-nxdk';stub=nxdk/'lib/pdclib/platform/xbox/functions/math/lround.c';assert stub.exists()
with tempfile.TemporaryDirectory(prefix='myro-sdk47a-')as td:
 d=Path(td);probe=d/'probe.c';probe.write_text('#include <math.h>\nint main(void){volatile float x=.5f;return (int)lroundf(x);}\n');exe=d/'probe';subprocess.run(['cc','-O0','-fno-builtin-lroundf',str(probe),str(stub),'-lm','-o',str(exe)],check=True);run=subprocess.run([str(exe)],capture_output=True,text=True);assert run.returncode<0 and 'lroundf' in run.stderr and 'Assertion' in run.stderr;print('PASS reproduction: real nxdk lroundf aborts with assertion, matching Test47 first-frame diagnostics call.')
 exe=d/'ui';subprocess.run(['cc','-O1','-fno-builtin-lroundf',str(r/'test_ui42.c'),str(r/'ui_assets.c'),str(r/'skin_assets.c'),str(stub),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['diag45',str(off),str(open)]for off in range(2)for open in range(16)]+[['windows','0',str(stat),'0']for stat in range(6)]+[['status44',str(hp)]for hp in [60,8488,32767]]
 cases += [['audio50']]
 for args in cases:
  run=subprocess.run([str(exe),*args],capture_output=True,text=True);assert run.returncode==0,(args,run.stderr)
 print('PASS47a',len(cases),'actual diagnostics/Status HUD cases with nxdk asserting math stub linked; no unsupported call reached.')
 # These labels use bounded tenths and half-away-from-zero conversion.
 probe.write_text((r/'test_ui42.c').read_text().replace('int main(int argc,char**argv)','static int sdk_ui_entry(int argc,char**argv)')+'\nint main(void){assert(ui_round47a(0)==0);assert(ui_round47a(.49f)==0);assert(ui_round47a(.5f)==1);assert(ui_round47a(-.5f)==-1);assert(ui_round47a(1625.4f)==1625);return 0;}\n');exe=d/'round';subprocess.run(['cc','-O1','-I'+str(r),str(probe),str(r/'ui_assets.c'),str(r/'skin_assets.c'),str(stub),'-lm','-lz','-o',str(exe)],check=True);subprocess.run([str(exe)],check=True);print('PASS47a bounded UI rounding: zero, positive/negative half values, ASPD tenths.')
 obj=r/'main.obj'
 if obj.exists():
  tool=nxdk.parent/'xbox-toolchain/usr/lib/llvm-18/bin/llvm-objdump';env=os.environ.copy();env['LD_LIBRARY_PATH']=str(nxdk.parent/'xbox-toolchain/usr/lib/x86_64-linux-gnu');table=subprocess.check_output([str(tool),'-t',str(obj)],env=env,text=True);assert '_lroundf'not in table;print('PASS47a native main.obj has no lroundf symbol/reference.')
