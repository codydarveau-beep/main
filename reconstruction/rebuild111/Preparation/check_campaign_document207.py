"""Original document callers versus production renderer with host GPU recording."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json,math
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c)
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200)
expected=[];currentCursor=currentGuild=0
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0]
 if at==0x919b0:
  record=bytearray(52);struct.pack_into('<I',record,0,currentCursor);record[24]=65 if currentGuild else 0;cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),bytes(record));cpu.reg_write(UC_X86_REG_EAX,1)
 else:expected.append(struct.unpack('<2f',cpu.mem_read(esp+12,8)))
 cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x919b0,0x117850]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'campaign_document_adapter207.c'),'-lm','-lz','-o',str(V/'campaign_document207.so')],check=True)
lib=ctypes.CDLL(str(V/'campaign_document207.so'));F=ctypes.c_float;U=ctypes.c_uint;lib.document207.argtypes=[U]*6+[ctypes.POINTER(F),F,F,ctypes.POINTER(F)]
cases=views=0
def run(row,cursor,mapid,guild,active):
 global currentCursor,currentGuild,cases,views
 currentCursor=cursor;currentGuild=guild;expected.clear();stage=0x5c1848+row*128 if row<9 else 0x5c07c8+(row-9)*128 if row<42 else 0
 u.mem_write(0xd424c8,struct.pack('<2I',stage,active));u.mem_write(0xbec5ac,struct.pack('<I',mapid));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x45dd1,0x45f2f,count=10000);assert u.reg_read(UC_X86_REG_EIP)==0x45f2f
 center=expected[0] if expected else (0,0)
 for angle in range(8):
  yaw=angle*math.pi/4;co=math.cos(yaw);si=math.sin(yaw);ct=math.cos(.8);sn=math.sin(.8);zoom=2.;cx,cy=center
  matrix=(F*16)(zoom*co,zoom*si,0,320-zoom*(co*cx+si*cy),zoom*ct*si,-zoom*ct*co,-zoom*sn,245-zoom*ct*(si*cx-co*cy)+zoom*sn*7,-2048*sn*si,2048*sn*co,-2048*ct,8388608+2048*sn*si*cx-2048*sn*co*cy+2048*ct*7,1,0,0,0);out=(F*387)();slope=matrix[10]/matrix[6]
  lib.document207(row,cursor,mapid,guild,active,0,matrix,zoom,slope,out);positions=[tuple(out[3+i*2:5+i*2])for i in range(int(out[0]))];assert positions==expected,(row,positions,expected)
  quads=[]
  for px,py in expected:
   sx=matrix[0]*px+matrix[1]*py+matrix[3];sy=matrix[4]*px+matrix[5]*py+matrix[6]*7+matrix[7]
   if not(-30<=sx<=670 and -30<=sy<=510):continue
   depth=matrix[8]*px+matrix[9]*py+matrix[10]*7+matrix[11]-256
   quads.append([sx-5,sy-10,10,10,depth-10*slope,depth,11,12,13,14])
  assert int(out[1])==len(quads)
  for i,q in enumerate(quads):
   for j,value in enumerate(q):assert abs(out[67+i*10+j]-value)<(2 if j in [4,5] else .005),(row,angle,j,out[67+i*10+j],value)
  # Existing room, icon availability and atlas fallback rules apply to all props.
  for failure in [1,2,3,4,5]:
   lib.document207(row,cursor,mapid,guild,active,failure,matrix,zoom,slope,out);assert int(out[1])==(len(quads) if failure==4 else 0)
  views+=1
 cases+=1
for row in range(42):
 stage=0x5c1848+row*128 if row<9 else 0x5c07c8+(row-9)*128;cursor,mapid=struct.unpack_from('<2I',x,stage-0x10000);run(row,cursor,mapid,0,1)
for cursor in [8,9,35,36]:
 for mapid in [131,132]:
  for guild in [0,1]:
   for active in [0,1]:run(42,cursor,mapid,guild,active)
lib.document_clear207()
(V/'Campaign-Document-Checks207.json').write_text(json.dumps(dict(passed=True,nativeCallerComparisons=cases,cameraViews=views,sourceHelper='0x117850',sourceCallers=['0x45dd1..0x45f2f'],scope='Actual native caller enumeration for all stage records and static guild paper conditions; production renderer host recording checks authored positions, eight bearings, projection, depth, room visibility, unavailable icons and atlas fallback without state mutation. GPU rasterization and target residency remain untested.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS restored original evidence props and host draw integration; no target playtest.')
