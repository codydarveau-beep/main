"""Original Dagna inline attack caller versus the production candidate tick."""
from pathlib import Path
import runpy,ctypes,struct,json,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
ns=runpy.run_path(str(R/'Preparation/check_companion_archer212.py'));globals().update({k:ns[k] for k in ['u','lib','U','sp','ctx','UC_HOOK_CODE','UC_X86_REG_ESP','UC_X86_REG_EIP','UC_X86_REG_EAX']})
import subprocess
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_blacksmith_adapter217.c'),'-lm','-lz','-o',str(V/'companion_blacksmith217.so')],check=True);lib=ctypes.CDLL(str(V/'companion_blacksmith217.so'))
lib.begin217.argtypes=[U]*16+[U*71]
def hook212(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0]
 if at==0x95650:
  ptr=cpu.reg_read(ns['UC_X86_REG_ECX']);hp=cpu.reg_read(ns['UC_X86_REG_EDX']);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 else:
  args=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert args==(0xbde5e0,16,ctx['identity']+1),args;ctx['effect']+=1
 cpu.reg_write(UC_X86_REG_EAX,1);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x95650,0x676a0]:u.hook_add(UC_HOOK_CODE,hook212,begin=at,end=at)
rng=random.Random(1212);cases=0;coverage={}
for i in range(1200):
 identity=11;job=rng.choice([19,31]);jl=rng.choice([1,2,20,50] if job<21 else [1,2,20,50,70]);points=rng.choice([0,1,10,12,50,500]);agility=rng.randrange(1,151);dex=rng.randrange(1,151);bless=rng.choice([0,5,10]);agibuff=rng.choice([0,5,10]);enabled=rng.randrange(2);preference=rng.randrange(3);cooling=rng.randrange(2);distance=rng.randrange(8,17);counter=rng.randrange(16);kind=rng.randrange(600);traits=0;stunned=rng.randrange(2);m=bytearray(244)
 for off,val in [(0,identity),(4,3),(16,90),(20,100),(24,points),(48,jl),(56,job),(108,0),(120,123)]:struct.pack_into('<I',m,off,val)
 m[81]=agility;m[84]=dex;m[86]=bless;m[87]=agibuff
 for off,f in [(88,20. if bless else 0.),(92,20. if agibuff else 0.),(164,100.),(168,100.),(212,11. if cooling else 0.)]:struct.pack_into('<f',m,off,f)
 u.mem_write(0xd2f8b0,bytes(m));u.mem_write(0xbef884,struct.pack('<3I',123,kind,100000));u.mem_write(0xbef86c,struct.pack('<I',bool(traits)));u.mem_write(0xbef880,struct.pack('<I',traits));u.mem_write(0xbef8ac,struct.pack('<f',float(stunned)));u.mem_write(0xbef7d8,struct.pack('<2f',100.+distance,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xbec5ac,struct.pack('<I',3));u.mem_write(0xd42501+identity,bytes([enabled]));u.mem_write(0xd424ee+identity,bytes([preference]));u.mem_write(0xe381c0,struct.pack('<I',counter));u.mem_write(0xd42894,bytes(224));u.mem_write(sp,bytes(0x3400))
 for off,val in [(0x40,0),(0x70,0xd2f8b0+20),(0x90,identity),(0xa0,0xd2f8b0+8),(0xf0,0xd2f8b0),(0x100,0xd2f8b0+164),(0xd0,0xd2f8b0+168),(0x220,0xbef7d8),(0x240,0xd2f8b0+108),(0x120,0),(0x160,0xd2f8b0+196),(0x290,0xd2f8b0+196),(0x330,0xd2f8b0+108),(0x2f0,0)]:u.mem_write(sp+off,struct.pack('<I',val))
 u.mem_write(sp+0x15c,struct.pack('<f',float(distance)));ctx['effect']=0;ctx['identity']=identity;u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(ns['UC_X86_REG_XMM0'],struct.unpack('<I',struct.pack('<f',10.))[0]);
 try:u.emu_start(0x30b1a,0x35034,count=100000)
 except Exception:
  print('FAULT',i,identity,job,jl,points,hex(u.reg_read(UC_X86_REG_EIP)),{n:hex(u.reg_read(ns['UC_X86_REG_'+n])) for n in ['EAX','ECX','EDX','ESI','EDI','EBX','ESP']});raise
 assert u.reg_read(UC_X86_REG_EIP)==0x35034
 expected=[struct.unpack('<I',u.mem_read(0xd2f8b0+off,4))[0]for off in [24,128,132,60,112,124,136,188,192,196,200,204,212]]+[struct.unpack('<I',u.mem_read(0xe381c0,4))[0],ctx['effect']]+list(struct.unpack('<56I',u.mem_read(0xd42894,224)))
 out=(U*71)();lib.begin217(identity,job,jl,points,agility,dex,bless,agibuff,enabled,preference,cooling,distance,counter,kind,traits,stunned,out);assert list(out)==expected,(i,kind,traits,stunned,job,jl,points,enabled,preference,cooling,[(j,a,b)for j,(a,b)in enumerate(zip(out,expected))if a!=b]);cases+=1;coverage[out[1]]=coverage.get(out[1],0)+1
assert all(coverage.get(skill,0)>0 for skill in [1,230]),coverage
(V/'Companion-Blacksmith-Cast-Checks217.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,choiceCoverage=coverage,scope='Original complete Dagna inline physical choice and initiation across both careers, original non-boss/already-stunned target rules, own learning/preferences/cooldowns/affordability, exact motion/timing/serial records, deferred fee and absence of invented arrows. Target validity and line fixtures are explicit; actual candidate ticks and real area status resolution are separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Dagna physical choice, payment and attack records; host only.')
