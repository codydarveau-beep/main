"""Original Miri branch choices against the production candidate helper."""
from pathlib import Path
import runpy,ctypes,struct,json,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
ns=runpy.run_path(str(R/'Preparation/check_companion_specialist209.py'));globals().update({k:ns[k] for k in ['u','lib','U','sp','UC_HOOK_CODE','UC_X86_REG_ESP','UC_X86_REG_EIP','UC_X86_REG_ECX','UC_X86_REG_EDX','UC_X86_REG_EAX']})
lib.choice210.argtypes=[U]*5+[ctypes.POINTER(U)]
def chosen(cpu,at,size,user):cpu.emu_stop()
h=u.hook_add(UC_HOOK_CODE,chosen,begin=0x31dc0,end=0x31dc0)
rng=random.Random(210);cases=0;choices={}
for i in range(1200):
 jl=rng.choice([1,2,10,20,49,50,70]);level=rng.choice([20,69,70,79,80,89,90,99]);points=rng.choice([0,1,5,10,12,20,30,50,100,500]);kind=rng.randrange(100);primed=rng.randrange(2);m=bytearray(244)
 for off,val in [(0,18),(4,3),(16,level),(20,100),(24,points),(48,jl),(56,45)]:struct.pack_into('<I',m,off,val)
 struct.pack_into('<f',m,156,11. if primed else 0.);u.mem_write(0xd2f8b0,bytes(m));u.mem_write(0xbef888,struct.pack('<I',kind));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(sp,bytes(0x400))
 for off,value in [(0x40,0),(0x70,0xd2f8b0+20),(0xa0,0xd2f8b0+8),(0xf0,0xd2f8b0),(0x240,0)]:u.mem_write(sp+off,struct.pack('<I',value))
 u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x30e7a,0x35034,count=100000);at=u.reg_read(UC_X86_REG_EIP);assert at in [0x31dc0,0x35034];expected=struct.unpack('<I',u.mem_read(sp+0x120,4))[0] if at==0x31dc0 else 0
 rank=U();actual=lib.choice210(jl,level,points,kind,primed,ctypes.byref(rank));assert actual==expected,(jl,level,points,kind,primed,actual,expected)
 if expected:
  u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0xd2f8b0);u.reg_write(UC_X86_REG_EDX,expected);u.emu_start(0x941f0,0x1000000,count=100000);assert rank.value==u.reg_read(UC_X86_REG_EAX)
 else:assert rank.value==0
 choices[actual]=choices.get(actual,0)+1;cases+=1
u.hook_del(h)
assert all(choices.get(skill,0)>0 for skill in [0,438,439,440]),choices
(V/'Companion-Soullinker-Choice-Checks210.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,choiceCoverage=choices,scope='Original inline Miri decision branch with real native learning/cost data: prepared follow-up priority, size preference and alternate, own level and Kaina/job-learning/SP boundaries. Candidate movement/casting integration remains separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Soul Linker choices and own-resource boundaries; host only.')
