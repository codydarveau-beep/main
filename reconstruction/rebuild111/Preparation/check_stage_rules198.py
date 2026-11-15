"""Compare recovered editable C stage rules with independent released x86 code.
Host CPU reference replay, never Xbox/Xemu playtesting.
"""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/stage_rules_adapter198.c'),'-lm','-lz','-o',str(R/'Validation/stage_rules198.so')],check=True)
lib=ctypes.CDLL(str(R/'Validation/stage_rules198.so'));U=ctypes.c_uint;lib.stage_decide198.argtypes=[U,U,U,U,U,U*4]
context={}
def hook(cpu,at,size,user):
 if at==0x2e1f4:cpu.emu_stop();return
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0xf7e30:context['talk']=1;cpu.emu_stop();return
 if at==0x919b0:cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),context['state']);cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x91cc0:
  context['write']=1;context['state']=bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_EDX),52));cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x74540:context['message']=struct.unpack('<I',cpu.mem_read(esp+8,4))[0]
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x2e1f4,0xf7e30,0x919b0,0x91cc0,0x74540]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
r=json.loads((R/'Preparation/Campaign-Stages-Recovery197.json').read_text());rows=r['earlier']['rows']+r['later']['rows'];rng=random.Random(198);count=0;fixture=[]
for row,d in enumerate(rows):
 cursor=d['cursor'];gate=9 if cursor in [3,6,9] else 7 if cursor<12 else 8 if cursor==34 else struct.unpack_from('<I',x,0x5c0738-65536+cursor*4)[0]
 docs=1 if cursor in[3,4]else d['trailing'][0] if cursor>=6 else 0
 masks={0,1,3,7,8,16,32,0x300,0x301,0x310,0x330,0x331,0xffffffff,0x40000000,0x300|0x40000000,*[rng.getrandbits(16)for _ in range(32)]}
 for route in [1,2,3]:
  for checkpoint in set([0,gate,max(0,gate-1)]):
   for objectives in masks:
    for who in ([102 if cursor==5 else 100]if d["count"]else[])+list(range(110,110+docs)):
     state=struct.pack('<6I',cursor,route,1,0,objectives,checkpoint)+bytes(28);context.clear();context.update(state=state,write=0,message=0,talk=0)
     u.mem_write(sp+0x1670,state);u.mem_write(0xd424c8,struct.pack('<I',(0x5c1848+row*128)if row<9 else 0x5c07c8+(row-9)*128));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ESI,who);u.emu_start(0x2d078,0x2e1f4,count=10000)
     assert u.reg_read(UC_X86_REG_EIP)in[0x2e1f4,0xf7e30]
     expected=[context['write'],struct.unpack_from('<I',context['state'],16)[0],context['message'],context['talk']];out=(U*4)();lib.stage_decide198(row,route,checkpoint,objectives,who,out);actual=list(out)
     assert actual==expected,(row,cursor,route,checkpoint,hex(objectives),who,actual,expected)
     fixture.append([row,route,checkpoint,objectives,who,*expected]);count+=1
 print('Stage rule records compared',row+1,'/',len(rows),flush=True)
(R/'Validation/stage_rules_fixtures198.h').write_text('/* Independent released-code outcomes. */\nstatic const unsigned stageFixtures198[][9]={\n'+''.join('{'+','.join(str(v)+'u'for v in case)+'},\n'for case in fixture)+'};\n')
# Exercise actual production nearest-contact/evidence selection independently.
u.mem_map(0x3000000,0x60000);u.mem_map(0x1000000,4096)
u.mem_write(0xd424c0,struct.pack('<I',0x3000000));u.mem_write(0xd424cc,struct.pack('<I',1))
lib.stage_near198.argtypes=[U,U,U,U,ctypes.c_float,ctypes.c_float];lib.stage_near198.restype=ctypes.c_int
nearCount=0
for row,d in enumerate(rows):
 docs=1 if d['cursor']<5 else d['trailing'][0] if d['cursor']>=6 else 0
 points=[(a['x'],a['y'])for a in d['actors']]
 points += [(d['document'][0]+(i-(docs-1)*.5)*24 if d['cursor']>=6 else d['document'][0],d['document'][1])for i in range(docs)]
 points += [(d['position'][0]+rng.uniform(-70,70),d['position'][1]+rng.uniform(-70,70))for _ in range(48)]
 points += [(p[0]+dx,p[1]+dy)for p in list(points[:d['count']+docs])for dx,dy in [(19.999,0),(20,0),(20.001,0),(0,20),(-16,-8)]]
 for cursor,mapid,hp in [(d['cursor'],d['map'],100),(d['cursor'],d['map'],0),(d['cursor'],498,100),((d['cursor']+1)%36,d['map'],100)]:
  for xx,yy in points:
   xx=ctypes.c_float(xx).value;yy=ctypes.c_float(yy).value
   state=struct.pack('<6I',cursor,1,1,0,0,0)+bytes(28);context.clear();context.update(state=state,write=0,message=0,talk=0)
   u.mem_write(0xd424c8,struct.pack('<I',(0x5c1848+row*128)if row<9 else 0x5c07c8+(row-9)*128));u.mem_write(0x3000000+0x4aa0,struct.pack('<2f',xx,yy));u.mem_write(0x3000000+0x4ad0,struct.pack('<I',hp));u.mem_write(0x3000000+0xdfcc,struct.pack('<I',mapid));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0xf76f0,0x1000000,count=10000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
   expected=ctypes.c_int(u.reg_read(UC_X86_REG_EAX)).value;actual=lib.stage_near198(row,cursor,mapid,hp,xx,yy)
   assert actual==expected,('nearest',row,cursor,mapid,hp,xx,yy,actual,expected);nearCount+=1
report=dict(passed=True,cases=count,nearestCases=nearCount,stageRecords=len(rows),sourceSHA256=hashlib.sha256((R/'Source/campaign_stage_rules198.h').read_bytes()).hexdigest(),scope='Full authored contact/document decisions and production nearest-contact selection against independent released-code CPU replay. Encounter lifecycle, world binding and target execution remain separate checks.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0)
(R/'Validation/Stage-Rules-Checks198.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS authored stage proof rules and independent original feedback/state/nearest decisions; host only.')
