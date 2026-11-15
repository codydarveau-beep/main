"""Read-only replay of pure released arcade logic; NOT Xbox/Xemu execution."""
from pathlib import Path
import sys,struct,json
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UcError
from unicorn.x86_const import *
R=Path(__file__).resolve().parent.parent
x=(R.parent/'packet194/released-default.xbe').read_bytes();base=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-base+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x1000000,0x1000);u.mem_map(0x2000000,0x200000);u.reg_write(UC_X86_REG_CR4,0x200)
STATE=0xd478f0;SIZE=0x70c;STOP=0x1000000;STACK=0x21ff000
rows=[]
for game in range(6):
 u.mem_write(STACK,struct.pack('<I',STOP));u.reg_write(UC_X86_REG_ESP,STACK);u.reg_write(UC_X86_REG_ECX,game);u.reg_write(UC_X86_REG_EDX,197)
 try:u.emu_start(0xcc5a0,STOP,count=2000000)
 except UcError as e:raise RuntimeError((game,hex(u.reg_read(UC_X86_REG_EIP)),str(e)))
 assert u.reg_read(UC_X86_REG_EIP)==STOP
 raw=bytes(u.mem_read(STATE,SIZE));assert struct.unpack_from('<I',raw)[0]==game and struct.unpack_from('<I',raw,12)[0]==3;(R/'Preparation/reference197'/('reset-%d.bin'%game)).write_bytes(raw)
 rows.append(dict(game=game,words=struct.unpack_from('<13I',raw),positions=struct.unpack_from('<6f',raw,52),length=struct.unpack_from('<H',raw,1250)[0],food=struct.unpack_from('<H',raw,1252)[0],tail=raw[1284:1324].hex()))
print(json.dumps(dict(resets=rows,constants={hex(va):struct.unpack('<f',u.mem_read(va,4))[0]for va in [0x74a304,0x74a308,0x74a2c4,0x74aeb0,0x74a3a0]}),indent=2))
