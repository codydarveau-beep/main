"""Host-only native arcade replay linkage; never linked into the Xbox game."""
from pathlib import Path
import fcntl,os,subprocess,sys
R=Path(__file__).resolve().parent.parent
U=R.parent/'emulation-libs/unicorn'
def flags():
 # Cleanup may remove reproducible ELF artifacts. Rebuild from the checked-in
 # exact same lifted assembly, without changing production Source mid-test.
 V=R/'Validation';elf=V/'arcade_recovered197.elf'
 with (V/'.arcade-host-build264.lock').open('w')as lock:
  fcntl.flock(lock,fcntl.LOCK_EX)
  if not elf.is_file():
   root=Path('/workspace/myro/toolchain/xbox-toolchain/usr/lib/llvm-18/bin');env=os.environ.copy();env['LD_LIBRARY_PATH']='/workspace/myro/toolchain/xbox-toolchain/usr/lib/x86_64-linux-gnu'
   subprocess.run([str(root/'clang'),'-target','i386-unknown-linux-gnu','-c',str(V/'arcade_recovered197-host.s'),'-o',str(V/'arcade_recovered197.o')],env=env,check=True)
   temporary=elf.with_suffix('.elf.tmp264')
   subprocess.run([str(root/'ld.lld'),'-m','elf_i386','-Ttext=0x10000000','--entry=_arcade197_reset',str(V/'arcade_recovered197.o'),'-o',str(temporary)],env=env,check=True)
   os.replace(temporary,elf)
 return [str(V/'arcade_host197.c'),'-I'+str(U/'include'),'-L'+str(U/'lib'),'-Wl,-rpath,'+str(U/'lib'),'-l:libunicorn.so.2']
