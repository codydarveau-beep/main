"""Recover personality priorities and validate stats/promotions against native code."""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,re,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x20000);u.mem_map(0x1000000,4096);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200)
initial=struct.unpack_from('<19I',x,0x2a7984-65536);promoted=struct.unpack_from('<13I',x,0x5e593c-65536);final=[7,11,9,10,17,18,12,13,14,15,16,19,20];paths=[]
for identity in range(19):
 u.mem_write(0x3000000,bytes(244));u.mem_write(0x3000000,struct.pack('<I',identity));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,1);u.emu_start(0x93140,0x931a7,count=10000);assert u.reg_read(UC_X86_REG_EIP)==0x931a7;path=list(u.mem_read(u.reg_read(UC_X86_REG_EBP),12));assert max(path)<6;paths.append(path)
(R/'Source/companion_paths_data200.h').write_text('/* Exact native authored priority and promotion tables; generated. */\n#ifndef MYRO_COMPANION_PATHS_DATA200_H\n#define MYRO_COMPANION_PATHS_DATA200_H\nstatic const unsigned char partyStatPaths200[19][12]={'+','.join('{'+','.join(map(str,p))+'}'for p in paths)+'};\nstatic const unsigned partyFinalJobs200[13]={'+','.join(map(str,final))+'};\nstatic const unsigned partyPromotedJobs200[13]={'+','.join(map(str,promoted))+'};\n#endif\n')
# Existing source resource/budget tables must match their native references.
s=(R/'Source/solo_tables53.h').read_text()
for name,va in [('solojobHP52',0x2a83e0),('solojobSP52',0x2b3790)]:
 vals=list(map(int,re.findall(r'\d+',s.split(name+'[J52_COUNT][SOLO_LEVEL_CAP53]=')[1].split(';')[0])));assert struct.pack('<%dI'%len(vals),*vals)==x[va-65536:va-65536+len(vals)*4]
(R/'Validation/companion_paths_adapter200.c').write_text('#include "companion_paths200.h"\nunsigned promote200(unsigned i,unsigned j,unsigned l,unsigned c){return party_growth_promotion200(i,j,l,c);}\nvoid stats200(unsigned i,unsigned j,unsigned l,unsigned*out){unsigned char s[6];if(!party_growth_stats200(i,j,l,s,out+6,out+7))abort();for(unsigned k=0;k<6;k++)out[k]=s[k];}\n')
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/companion_paths_adapter200.c'),'-lz','-o',str(R/'Validation/companion_paths200.so')],check=True);lib=ctypes.CDLL(str(R/'Validation/companion_paths200.so'));U=ctypes.c_uint;lib.stats200.argtypes=[U,U,U,U*8];lib.promote200.argtypes=[U,U,U,U];rng=random.Random(200);statCases=promotionCases=0
for identity in range(19):
 jobs={0,initial[identity],final[identity]if identity<13 else initial[identity],promoted[identity]if identity<13 else initial[identity]}
 for job in jobs:
  for level in[0,1,2,25,49,50,70,99,100,150,249,250,251]:
   u.mem_write(0x3000000,bytes(244));u.mem_write(0x3000000,struct.pack('<I',identity));u.mem_write(0x3000038,struct.pack('<I',job));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,level);u.emu_start(0x93140,0x1000000,count=1000000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;expected=[*u.mem_read(0x3000050,6),*struct.unpack('<2I',u.mem_read(0x300001c,8))];out=(U*8)();lib.stats200(identity,job,level,out);assert list(out)==expected,(identity,job,level,list(out),expected);statCases+=1
  for cursor in[0,14,15,26,27,35,36]:
   for jobLevel in[0,1,49,50,69,70,99]:
    u.mem_write(0x3000100-12,struct.pack('<I',jobLevel));u.mem_write(0x3000100-4,struct.pack('<I',job));u.mem_write(sp,struct.pack('<I',cursor));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_EBP,0x3000100);u.reg_write(UC_X86_REG_EDX,cursor);u.reg_write(UC_X86_REG_EBX,identity)
    # Bound the original inlined selection before its actual stat/resource update.
    from unicorn import UC_HOOK_CODE
    def stop(cpu,at,size,user):
     if at in[0x80a60,0x80bf2]:cpu.emu_stop()
    h=u.hook_add(UC_HOOK_CODE,stop,begin=0x80a58,end=0x80bf2);u.emu_start(0x80a82,0x80bf2,count=10000);at=u.reg_read(UC_X86_REG_EIP);u.hook_del(h);assert at in[0x80a60,0x80bf2];expected=u.reg_read(UC_X86_REG_EDI)if at==0x80bf2 else job;actual=lib.promote200(identity,job,jobLevel,cursor);assert actual==expected,(identity,job,jobLevel,cursor,actual,expected);promotionCases+=1
 print('Companion personality and promotion path',identity+1,'/19',flush=True)
(R/'Validation/Companion-Path-Checks200.json').write_text(json.dumps(dict(passed=True,personalities=19,statCases=statCases,promotionCases=promotionCases,storyMilestones=[15,27],nativeHPAndSPTablesMatch=True,sourceSHA256=hashlib.sha256((R/'Source/companion_paths200.h').read_bytes()).hexdigest(),runtimeCallersIntegrated=False,scope='Original per-person stat allocation, resource calculation and story/job-level promotion eligibility compared to actual native functions. EXP awards, promotion commits and full skill/AI behavior still require integration.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS all original personality stat profiles and story/growth promotion boundaries; host CPU reference only.')
