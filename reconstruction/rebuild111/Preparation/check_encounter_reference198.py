"""Independent native reference for authored encounter eligibility and spawns.
Only storage and NPC attachment allocation are intercepted; not Xbox execution.
"""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x40000);u.mem_map(0x1000000,4096);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/encounter_adapter198.c'),'-lm','-lz','-o',str(R/'Validation/encounter198.so')],check=True)
lib=ctypes.CDLL(str(R/'Validation/encounter198.so'));U=ctypes.c_uint;lib.encounter_plans198.argtypes=[U,U,U,U*15];context={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0x919b0:cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),context['state']);cpu.reg_write(UC_X86_REG_EAX,1)
 elif at in[0xc7260,0xc7630]:cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x1377e0:
  dest,limit,fmt,src=struct.unpack('<4I',cpu.mem_read(esp+4,16));s=bytes(cpu.mem_read(src,128)).split(b'\0')[0][:limit-1];cpu.mem_write(dest,s+b'\0');cpu.reg_write(UC_X86_REG_EAX,len(s))
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in[0x919b0,0xc7260,0xc7630,0x1377e0]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
r=json.loads((R/'Preparation/Campaign-Stages-Recovery197.json').read_text());rows=r['earlier']['rows']+r['later']['rows'];rng=random.Random(198);count=spawns=0;fixtures=[]
for row,d in enumerate(rows):
 if not d['trailing'][1]:continue
 gate=7 if d['cursor']in[7,10]else 8 if d['cursor']==34 else struct.unpack_from('<I',x,0x5c0738-65536+d['cursor']*4)[0]
 for checkpoint in set([0,gate,5,15]):
  for objectives in[0,0x100,0x200,0x300,0x400,0x700,0xffffffff,*[rng.getrandbits(12)for _ in range(12)]]:
   cursor=d['cursor'];context['state']=struct.pack('<6I',cursor,1,1,0,objectives,checkpoint)+bytes(28)
   u.mem_write(0xd424c8,struct.pack('<I',(0x5c1848+row*128)if row<9 else 0x5c07c8+(row-9)*128));u.mem_write(0xd424cc,struct.pack('<I',1));u.mem_write(0xbe30b0,struct.pack('<I',100));u.mem_write(0xbec5ac,struct.pack('<I',d['map']));u.mem_write(0xbe3080,struct.pack('<2f',*d['position']));u.mem_write(0xceeba4,struct.pack('<5I',0x3000000,0,32,d['map'],0));u.mem_write(0xd42a14,struct.pack('<5I',0xbde5e0,0xceeba4,0x12345,cursor,0))
   for k in range(336):u.mem_write(0xbef898+k*0x298,bytes(4))
   u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x12345);u.emu_start(0x80195,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000,hex(u.reg_read(UC_X86_REG_EIP))
   n=struct.unpack('<I',u.mem_read(0xceeba8,4))[0];expected=[]
   for i in range(n):
    raw=bytes(u.mem_read(0x3000000+i*120,120));kind,tag=struct.unpack_from('<I',raw,4)[0],struct.unpack_from('<I',raw,16)[0];source=struct.unpack('<I',u.mem_read(0x25979c+kind*68,4))[0];expected.append([source,tag,*struct.unpack_from('<2I',raw,32)])
   out=(U*15)();lib.encounter_plans198(row,checkpoint,objectives,out);actual=[[out[k*5],out[k*5+1],out[k*5+3],out[k*5+4]]for k in range(3)if out[k*5]]
   assert actual==expected,(row,cursor,checkpoint,hex(objectives),actual,expected);fixtures.append([row,checkpoint,objectives,*list(out)]);count+=1;spawns+=n
 print('Compared encounter row',row,flush=True)
(R/'Validation/encounter_fixtures198.h').write_text('/* Independent original spawn outcomes. */\nstatic const unsigned encounterFixtures198[][18]={\n'+''.join('{'+','.join(str(v)+'u'for v in case)+'},\n'for case in fixtures)+'};\n')
(R/'Validation/Encounter-Reference-Checks198.json').write_text(json.dumps(dict(passed=True,cases=count,originalSpawns=spawns,sourceSHA256=hashlib.sha256((R/'Source/campaign_encounter198.h').read_bytes()).hexdigest(),scope='Actual original encounter tick with storage/attachment allocation adapters compared to editable C spawn plans. Real lifecycle and failure checks are separate; not Xbox/Xemu playtesting.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS authored encounter eligibility, monster IDs, tags and exact positions against independent original CPU replay.')
