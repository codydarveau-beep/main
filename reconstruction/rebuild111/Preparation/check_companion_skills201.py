"""Compare independent recovered learning paths against the actual native routine."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c)
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);sp=0x2008000
def memset(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret,dest,value,count=struct.unpack('<4I',cpu.mem_read(esp,16));cpu.mem_write(dest,bytes([value&255])*count);cpu.reg_write(UC_X86_REG_EAX,dest);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,memset,begin=0x137420,end=0x137420)
(V/'companion_skills_adapter201.c').write_text('#include "companion_skill_cost201.h"\nunsigned cost201(unsigned i,unsigned j,unsigned l,unsigned level,unsigned s,unsigned r){return party_skill_cost_values201(i,j,l,level,s,r); }\nunsigned rank201(unsigned i,unsigned j,unsigned l,unsigned s){return party_skill_path_rank201(i,j,l,s);}\n')
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_skills_adapter201.c'),'-lz','-o',str(V/'companion_skills201.so')],check=True)
lib=ctypes.CDLL(str(V/'companion_skills201.so'));lib.rank201.argtypes=[ctypes.c_uint]*4;cases=0
paths=json.loads((R/'Preparation/Companion-Skills-Recovery201.json').read_text())['paths']
for row in paths:
 for level in [0,1,2,10,49,50,69,70,99,100]:
  member=bytearray(244);struct.pack_into('<I',member,0,row['identity']);struct.pack_into('<I',member,48,level);struct.pack_into('<I',member,56,row['job']);u.mem_write(0x3000000,bytes(member))
  for skill in range(446):
   u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,skill);u.emu_start(0x941f0,0x1000000,count=20000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
   expected=u.reg_read(UC_X86_REG_EAX);actual=lib.rank201(row['identity'],row['job'],level,skill);assert actual==expected,(row['identity'],row['job'],level,skill,actual,expected);cases+=1
 print('Authored companion career skill path',row['identity'],row['job'],'passed',flush=True)
(V/'Companion-Skill-Checks201.json').write_text(json.dumps(dict(passed=True,paths=len(paths),nativeComparisons=cases,boundedCaches=3,scope='Exact original per-character/per-career job-level learning and rank limits, including innate exceptions and invalid levels. Full career combat AI/effects remain separate.',sourceSHA256=hashlib.sha256((R/'Source/companion_skills201.h').read_bytes()).hexdigest(),originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
lib.cost201.argtypes=[ctypes.c_uint]*6;costCases=0
for row in paths:
 level=90;jobLevel=lib.rank201(row['identity'],row['job'],1,338) # fixed innate rank sanity
 assert jobLevel==9
 jobLevel=70 if row['job'] in [8,41,42] or 21<=row['job']<=32 else 99 if row['job']==40 else 50
 member=bytearray(244);struct.pack_into('<I',member,0,row['identity']);struct.pack_into('<I',member,16,level);struct.pack_into('<I',member,48,jobLevel);struct.pack_into('<I',member,56,row['job']);u.mem_write(0x3000000,bytes(member))
 for skill in range(446):
  for rank in [0,1,5,10,11]:
   u.mem_write(sp,struct.pack('<2I',0x1000000,rank));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,skill);u.emu_start(0x114d40,0x1000000,count=30000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
   expected=u.reg_read(UC_X86_REG_EAX);actual=lib.cost201(row['identity'],row['job'],jobLevel,level,skill,rank);assert actual==expected,('cost',row['identity'],row['job'],skill,rank,actual,expected);costCases+=1
 for ownLevel in [69,70,79,80,89,90,250]:
  u.mem_write(0x3000010,struct.pack('<I',ownLevel))
  for skill in [438,439,440]:
   for rank in [1,10]:
    u.mem_write(sp,struct.pack('<2I',0x1000000,rank));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,skill);u.emu_start(0x114d40,0x1000000,count=30000)
    expected=u.reg_read(UC_X86_REG_EAX);actual=lib.cost201(row['identity'],row['job'],jobLevel,ownLevel,skill,rank);assert actual==expected,('Kaina boundary',row['identity'],row['job'],ownLevel,skill,rank,actual,expected);costCases+=1
 print('Companion career SP costs',row['identity'],row['job'],'passed',flush=True)
(V/'Companion-Cost-Checks201.json').write_text(json.dumps(dict(passed=True,nativeComparisons=costCases,scope='Exact rank-sensitive original SP costs, own skill paths and passive reductions. Payment atomicity and full career casting behavior remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS original companion skill learning and SP costs; independent native CPU comparison only.')
