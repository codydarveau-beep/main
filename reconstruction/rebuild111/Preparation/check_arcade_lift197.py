"""Differential replay: recovered native assembly versus original arcade logic.
Host CPU emulation only; neither an Xbox nor Xemu playtest.
"""
from pathlib import Path
import sys,struct,subprocess,json,hashlib
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
R=Path(__file__).resolve().parent.parent;V=R/'Validation';x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
old=Uc(UC_ARCH_X86,UC_MODE_32);old.mem_map(0x10000,0xe60000)
for s in ss:old.mem_write(s[1],x[s[3]:s[3]+s[4]])
new=Uc(UC_ARCH_X86,UC_MODE_32);elf=(V/'arcade_recovered197.elf').read_bytes();phoff=struct.unpack_from('<I',elf,28)[0];size,count=struct.unpack_from('<HH',elf,42);segments=[struct.unpack_from('<8I',elf,phoff+i*size)for i in range(count)];segments=[s for s in segments if s[0]==1];lo=min(s[2]for s in segments)&~4095;hi=(max(s[2]+s[5]for s in segments)+4095)&~4095;pages=sorted({a for s in segments for a in range(s[2]&~4095,(s[2]+s[5]+4095)&~4095,4096)})
for a in pages:new.mem_map(a,4096)
for s in segments:new.mem_write(s[2],elf[s[1]:s[1]+s[4]])
symbols={line.split()[2]:int(line.split()[0],16)for line in subprocess.check_output(['nm','-n',str(V/'arcade_recovered197.elf')],text=True).splitlines()if len(line.split())==3};NEWSTATE=symbols['_arcade197_state'];STATE=0xd478f0;BYTES=1804;SP=0x2010000;STOP=0x1000000;phase=''
for u in [old,new]:u.mem_map(0x2000000,0x20000);u.mem_map(STOP,4096);u.reg_write(UC_X86_REG_CR4,0x200)
def stop_input(u,address,size,ctx):
 if phase=='input':u.emu_stop()
old.hook_add(UC_HOOK_CODE,stop_input,begin=0x1e44d,end=0x1e44d)
def initialize(u):
 for reg in [UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP]:u.reg_write(reg,0)
 u.reg_write(UC_X86_REG_ESP,SP)
def reset(game,seed):
 global phase
 phase='reset';initialize(old);old.mem_write(SP,struct.pack('<I',STOP));old.reg_write(UC_X86_REG_ECX,game);old.reg_write(UC_X86_REG_EDX,seed);old.emu_start(0xcc5a0,STOP,count=100000)
 initialize(new);new.mem_write(SP,struct.pack('<III',STOP,game,seed));new.emu_start(symbols['_arcade197_reset'],STOP,count=100000);compare(game,seed,'reset')
def compare(game,seed,where):
 a=bytes(old.mem_read(STATE,BYTES));b=bytes(new.mem_read(NEWSTATE,BYTES));
 if a!=b:
  at=next(i for i in range(BYTES)if a[i]!=b[i]);raise AssertionError((game,seed,where,at,a[at:at+16].hex(),b[at:at+16].hex()))
 assert bytes(new.mem_read(NEWSTATE-16,16))==b'\xa5'*16 and bytes(new.mem_read(NEWSTATE+BYTES,16))==b'\x5a'*16
 return a
def event(game,seed,pressed,held,dt,index):
 global phase
 phase='input';initialize(old);old.mem_write(SP+0x50,struct.pack('<I',pressed));old.emu_start(0x1d343,0x1f941,count=100000)
 initialize(new);new.mem_write(SP,struct.pack('<II',STOP,pressed));new.emu_start(symbols['_arcade197_input'],STOP,count=100000);compare(game,seed,('input',index))
 phase='tick';initialize(old);old.mem_write(SP+0x254,struct.pack('<I',held));old.mem_write(SP+0xb0,struct.pack('<4f',dt,0,0,0));old.emu_start(0x1e44d,0x1f941,count=1000000)
 initialize(new);new.mem_write(SP,struct.pack('<IIf',STOP,held,dt));new.emu_start(symbols['_arcade197_tick'],STOP,count=1000000);return compare(game,seed,('tick',index))
new.mem_write(NEWSTATE-16,b'\xa5'*16);new.mem_write(NEWSTATE+BYTES,b'\x5a'*16);events=0
for game in range(6):
 for seed in [0,1,2,17,197,0x12345678,0xffffffff]:
  reset(game,seed)
  for i in range(720):
   direction=[1024,8192,2048,4096][i//45%4];pressed=(direction if i%15==0 else 0)|(2 if i%7==0 else 0)|(16 if i%181==180 else 0);held=direction|(2 if i%3 else 0);dt=[1/60,1/30,1/120,.15,0][i%5];event(game,seed,pressed,held,dt,i);events+=1
 print('Exact six-game native restoration: game',game,'passed',flush=True)
report=dict(passed=True,games=6,resetSeeds=7,events=events,stateBytes=BYTES,completeByteForByteStateMatch=True,redzonesIntact=True,assemblySHA256=hashlib.sha256((R/'Source/arcade_recovered197.s').read_bytes()).hexdigest(),scope='Host CPU differential replay of original and relocated native logic; no Xbox/Xemu execution or display/controller acceptance',additionalReviewPassesCompleted=0)
(V/'Arcade-Logic-Checks197.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report))
