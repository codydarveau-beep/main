"""Original Maya potion support and durable transaction versus the production helper."""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,zlib,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x20000);u.mem_map(0x1000000,4096);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200);ctx={}
def hook215(cpu,at,size,user):
 if at in [0x3298c,0x333c3]:cpu.emu_stop();return
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0x113990:
  x,y,reach,dt,enemy=struct.unpack('<4fi',cpu.mem_read(esp+4,20));assert x==100. and y==100. and reach==64 and abs(dt-.05)<.000001 and enemy==-1,(x,y,reach,dt,enemy);ctx['walk']=1;cpu.emu_stop();return
 result=1
 if at==0x93460:
  high,out,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert high==0xeca20000
  if n==640:cpu.mem_write(out,ctx['raw'])
  else:result=0xffffffff
 elif at==0x13d320:
  seed,ptr,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));result=zlib.crc32(bytes(cpu.mem_read(ptr,n)),seed)
 elif at==0x137420:
  dest,value,count=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.mem_write(dest,bytes([value&255])*count);result=dest
 elif at==0x95200:result=0 if ctx['blocked'] else 1
 elif at==0x957c0:result=ctx['vitality']
 elif at==0x91ff0:
  ptr,n=struct.unpack('<2I',cpu.mem_read(esp+24,8));assert n==1280,n;raw=bytes.fromhex(bytes(cpu.mem_read(ptr,n)).decode());assert len(raw)==640
  result=0 if ctx['failure']==1 else 1
  if result:ctx['saved']=raw;ctx['accepted']=1
 elif at==0x114370:
  assert cpu.reg_read(UC_X86_REG_ECX)==10,hex(cpu.reg_read(UC_X86_REG_ECX));ctx['cues']+=1
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x93460,0x13d320,0x137420,0x95200,0x957c0,0x91ff0,0x114370,0x113990,0x3298c,0x333c3]:u.hook_add(UC_HOOK_CODE,hook215,begin=at,end=at)
V=R/'Validation';subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_potion_adapter215.c'),'-lm','-lz','-o',str(V/'companion_potion215.so')],check=True);lib=ctypes.CDLL(str(V/'companion_potion215.so'));U=ctypes.c_uint;B=ctypes.c_ubyte;lib.potion215.argtypes=[U]*12+[U*17,B*640];rng=random.Random(215);cases=0;coverage={}
for i in range(1236):
 job=rng.choice([20,32]);jl=rng.choice([1,2,10,20,49,50,70]);points=rng.choice([0,1,10,30,50,100]);preference=rng.randrange(3);enabled=rng.randrange(2);cooling=rng.randrange(2);distance=rng.choice([0,32,63,64,65,72,80]);recipient=rng.randrange(4);vitality=rng.randrange(151);potions=rng.choice([0,1,2,30]);blocked=rng.randrange(2);failure=rng.choice([0,0,0,1,2])
 if i<36:
  job=20 if i<18 else 32;jl=50 if job==20 else 70;points=100;preference=1;enabled=1;cooling=0;distance=0;recipient=i%3;vitality=(i%6)*30;potions=1 if i%2 else 2;blocked=0;failure=(i//3)%3
 out=(U*17)();actualRaw=(B*640)();lib.potion215(job,jl,points,preference,enabled,cooling,distance,recipient,vitality,potions,blocked,failure,out,actualRaw)
 raw=bytearray(640);raw[:4]=b'RPV3';struct.pack_into('<3I',raw,4,1,(1<<12)|(1<<4),17)
 for identity,values in [(12,[90,1234,jl,0,job,1 if recipient==2 else 100,points,0]),(4,[20,1234,2,0,3,1 if recipient==1 else 100,10,0])]:struct.pack_into('<8I',raw,16+identity*32,*values)
 struct.pack_into('<I',raw,636,zlib.crc32(raw[:636]))
 if failure==2:raw[639]=(raw[639]&240)|(1 if raw[639]&15==0 else 0)
 m=bytearray(244)
 for off,val in [(0,12),(4,3),(16,90),(20,1 if recipient==2 else 100),(24,points),(28,100),(36,1234),(40,1),(48,jl),(56,job)]:struct.pack_into('<I',m,off,val)
 m[82]=vitality
 for off,f in [(164,100.+distance),(168,100.),(212,11. if cooling else 0.)]:struct.pack_into('<f',m,off,f)
 a=bytearray(244)
 for off,val in [(0,4),(4,3),(16,20),(20,1 if recipient==1 else 100),(24,10),(28,100),(36,123),(40,1),(48,2),(56,3)]:struct.pack_into('<I',a,off,val)
 a[82]=vitality;struct.pack_into('<2f',a,164,100.,100.);u.mem_write(0xd2f8b0,bytes(m+a));u.mem_write(0xd2fb8c,struct.pack('<I',2));u.mem_write(0xbec5ac,struct.pack('<I',3));u.mem_write(0xbe3080,struct.pack('<2f',100.,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xbe30b0,struct.pack('<3I',1 if recipient==0 else 1000,1000,77));u.mem_write(0xd424ee+12,bytes([preference]));u.mem_write(0xd42501+12,bytes([enabled]));u.mem_write(0xd424d4,struct.pack('<I',0x3000000));u.mem_write(0x3000000,struct.pack('<5I',0x3001000,1,1,0,0));u.mem_write(0x3001000,struct.pack('<8I',0xf219bc63,0xeca20000,0,2,0,0,0x3002000,1280));u.mem_write(0xbe5484,bytes(3600));u.mem_write(0xbec504,struct.pack('<H',1 if potions else 0))
 if potions:
  bag=bytearray(36);struct.pack_into('<3I',bag,0,1,501,potions);bag[33]=1;u.mem_write(0xbe5484,bytes(bag))
 u.mem_write(0xbef344,bytes(772));u.mem_write(sp,bytes(0x4000))
 for off,val in [(0x40,0),(0x70,0xd2f8b0+20),(0x90,12),(0xa0,0xd2f8b0+8),(0xf0,0xd2f8b0),(0x100,0xd2f8b0+164),(0xd0,0xd2f8b0+168),(0x160,0xd2f8b0+12),(0x158,0)]:u.mem_write(sp+off,struct.pack('<I',val))
 ctx.update(raw=bytes(raw),saved=bytes(raw),blocked=blocked,failure=failure,vitality=out[15],walk=0,accepted=0,cues=0);u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x3087f,0x35034,count=200000);assert u.reg_read(UC_X86_REG_EIP) in [0x35034,0x3298c,0x333c3,0x113990],hex(u.reg_read(UC_X86_REG_EIP))
 count=struct.unpack('<H',u.mem_read(0xbec504,2))[0];remaining=sum(struct.unpack('<I',u.mem_read(0xbe548c+j*36,4))[0]for j in range(count)if struct.unpack('<I',u.mem_read(0xbe5488+j*36,4))[0]==501)
 expected=[ctx['walk'] or ctx['accepted']]+[struct.unpack('<I',u.mem_read(at,4))[0]for at in [0xd2f8b0+24,0xd2f8b0+20,0xd2f8b0+244+20,0xbe30b0,0xbe30b8]]+[remaining]+[struct.unpack('<I',u.mem_read(0xd2f8b0+off,4))[0]for off in [136,188,192,196,212]]+[struct.unpack('<I',u.mem_read(0xbef354,4))[0],ctx['cues'],54321,out[15],ctx['accepted']]
 assert list(out)==expected,(i,job,jl,points,preference,enabled,cooling,distance,recipient,vitality,potions,blocked,failure,list(out),expected);assert bytes(actualRaw)==ctx['saved'],('durable record mismatch',i,job,jl,points,recipient,failure,[(j,a,b) for j,(a,b) in enumerate(zip(bytes(actualRaw),ctx['saved'])) if a!=b]);cases+=1
 if ctx['accepted']:coverage['committed-career-'+str(job)]=coverage.get('committed-career-'+str(job),0)+1;coverage['committed-recipient-'+str(recipient)]=coverage.get('committed-recipient-'+str(recipient),0)+1
 key='committed'if ctx['accepted']else'walking'if ctx['walk']else'denied';coverage[key]=coverage.get(key,0)+1
assert all(coverage.get(key,0)>0 for key in ['committed','walking','denied','committed-career-20','committed-career-32','committed-recipient-0','committed-recipient-1','committed-recipient-2']),coverage
(V/'Companion-Potion-Checks215.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,caseCoverage=coverage,scope='Original complete Maya support branch versus production helper: both careers and real native learning, target selection, raw red-potion SP fee, exact research/recipient-VIT healing, actual native inventory removal and durable RPV3 put/CRC/commit payload. Every durable byte, live caster/recipient resources, potion count, cooldown and cue/number request agree. Commit rejection/corrupt record/missing items/range/line/learning/cooldown preserve resources; original approach request is recorded. Native NPC storage/player VIT and visual callbacks are explicit fixtures; actual complete battle integration and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Maya support transactions and complete durable records; host only.')
