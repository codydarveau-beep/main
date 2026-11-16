"""Compare actual original basic/Bash resolver with production C impact step."""
from pathlib import Path
import sys,struct,ctypes,json,random,subprocess
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];result=1
 if at==0x137420:
  dest,value,count=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.mem_write(dest,bytes([value&255])*count);result=dest
 elif at==0xf3500:result=ctx['flee']
 elif at in [0xca050,0x94070]:result=0 if (at==0xca050 and ctx['scenario']&8) or (at==0x94070 and ctx['scenario']&1) else 1
 elif at==0x114540:
  life,damage,magic=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert life==123 and magic==0;ctx['damage']=damage
 elif at==0x114370:ctx['cues']+=1
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x94070,0xf3500,0x114540,0x114370,0x94440,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_basic_adapter208.c'),'-lm','-lz','-o',str(V/'companion_basic208.so')],check=True);lib=ctypes.CDLL(str(V/'companion_basic208.so'));U=ctypes.c_uint;lib.basic213.argtypes=[U]*12+[U*6];rng=random.Random(208);cases=0
for k in range(1600):
 identity=13;skill=1 if identity==6 else rng.choice([1,2]);rank=rng.randrange(1,11);job=40;jl=rng.choice([1,2,20,50,70]);level=rng.randrange(1,100);strength=rng.randrange(1,151);dex=rng.randrange(1,151);luck=rng.randrange(1,151);bless=rng.choice([0,0,1,5,10]);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16]);out=(U*6)();lib.basic213(identity,skill,rank,job,jl,level,strength,dex,luck,bless,seed,scenario,out)
 m=bytearray(244)
 for off,val in [(0,identity),(4,3),(16,level),(20,100),(24,77),(48,jl),(56,job),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
 m[80]=strength;m[84]=dex;m[85]=luck;m[86]=bless
 for off,f in [(88,20. if bless else 0.),(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
 u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef884,struct.pack('<3I',124 if scenario&4 else 123,0,100000));u.mem_write(0xbef7d8,struct.pack('<2f',125. if scenario&2 else 112.,100.));u.mem_write(0xbe3098,struct.pack('<f',9. if scenario&16 else 10.));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,damage=0,cues=0,flee=out[5]);u.emu_start(0x111490,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128]]+[ctx['damage'],struct.unpack('<I',u.mem_read(0xc25dc8,4))[0],ctx['cues']];assert list(out)[:4]==expected[:4],(identity,job,jl,skill,rank,scenario,list(out),expected);cases+=1
(V/'Companion-Pip-Basic-Checks214.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,scope='Actual native Pip basic/Bash impact across his authored career: original own weapon/STR/DEX/LUK/Blessing and Sword Mastery, ranks, hit chance/RNG and range/line/serial/time rejection. Final hit and enemy flee are explicit fixtures; initiation and Envenom remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Pip basic/Bash impacts; host only.')
