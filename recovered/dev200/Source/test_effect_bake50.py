"""MIT. Compare actual source STR sampling and independent scalar blend algebra."""
from pathlib import Path
import itertools,json,re,subprocess,tempfile
import numpy as np
from PIL import Image
from asset_index50 import paths,key50
from convert_class_effects50 import parse_str,sample50,composite50
r=Path(__file__).resolve().parent
ref=(r.parent.parent/'reference48/roBrowserLegacy/src/Renderer/Effects/StrEffect.js').read_text()
a=ref.index('function calculateAnimation(');b=ref.index('\n/**',a);function=ref[a:b]
cases=[];expected=[]
report=json.loads((r/'class_effects50.json').read_text())
for row in report:
 keys=[k for k in row['sources'] if k.endswith('.str')]
 if not keys:continue
 fps,end,layers=parse_str(paths[key50(keys[0])].read_bytes())
 for names,frames in layers:
  if not names:continue
  for t in sorted(set([0,end,end+1,*range(0,end,4),*[k[0] for k in frames]])):
   cases.append(dict(t=t,count=len(names),frames=frames));v=sample50(frames,t,len(names));expected.append(None if v is None else [*v[2:20],v[20],v[23],*v[24:30]])
js=function+'''
const input=JSON.parse(require('fs').readFileSync(0,'utf8'));
const out=input.map(c=>{const frames=c.frames.map(v=>({frame:v[0],type:v[1],pos:v.slice(2,4),uv:v.slice(4,12),xy:v.slice(12,20),aniframe:v[20],anitype:v[21],delay:v[22],angle:v[23],color:v.slice(24,28),srcalpha:v[28],destalpha:v[29]}));const result={pos:new Float64Array(2),uv:new Float64Array(8),xy:new Float64Array(8),color:new Float64Array(4)};return calculateAnimation({animations:frames,anikeynum:frames.length,texcnt:c.count},c.t,result)?[...result.pos,...result.uv,...result.xy,result.aniframe,result.angle,...result.color,result.srcalpha,result.destalpha]:null});process.stdout.write(JSON.stringify(out));
'''
with tempfile.TemporaryDirectory() as td:
 p=Path(td)/'reference.cjs';p.write_text(js);actual=json.loads(subprocess.run(['node',str(p)],input=json.dumps(cases),text=True,capture_output=True,check=True).stdout)
assert len(actual)==len(expected)
for i,(a,b) in enumerate(zip(actual,expected)):
 assert (a is None)==(b is None),(i,cases[i])
 if a is not None:assert np.allclose(a,b,rtol=0,atol=1e-5),(i,a,b)
# One triangle-interior pixel: arbitrary source colors/alpha and three layer
# sequences. This oracle models GL SRC_ALPHA/INV_SRC_ALPHA/DST_ALPHA/ONE/ZERO
# separately, including true destination alpha and shader black/zero discard.
for blends in itertools.product([(5,7),(5,6),(2,1),(0,0)],repeat=3):
 canvas=np.zeros((256,128,4),np.float32);da=np.ones((256,128),np.float32);rgb=np.zeros(3);att=1.;alpha=1.
 for j,blend in enumerate(blends):
  pixel=np.array([21+10*j,51+7*j,81+9*j,90+20*j],dtype=float)/255
  a=[0.]*31;a[24:28]=[255]*4;a[28:30]=blend
  im=Image.new('RGBA',(4,4),tuple((pixel*255).astype(int)));composite50(canvas,da,im,a,[(0,0),(4,0),(4,4),(0,4)])
  if blend==(0,0):rgb=np.zeros(3);att=0;alpha=0
  elif blend==(2,1):rgb=pixel[:3];att=0;alpha=pixel[3]
  elif blend==(5,6):rgb=pixel[:3]*pixel[3]+rgb*(1-pixel[3]);att*=1-pixel[3];alpha=pixel[3]**2+alpha*(1-pixel[3])
  else:rgb=pixel[:3]*pixel[3]+rgb*alpha;att*=alpha;alpha=pixel[3]**2+alpha**2
  rgb=np.clip(rgb,0,1);alpha=min(1,alpha)
  assert np.allclose(canvas[1,1,:3],rgb,atol=1e-6) and abs(canvas[1,1,3]-(1-att))<1e-6 and abs(da[1,1]-alpha)<1e-6,(blends,j)
print('PASS50',len(cases),'source JavaScript key/morph/end/repeat/reverse comparisons;64 independent three-layer GL blend sequences.')
