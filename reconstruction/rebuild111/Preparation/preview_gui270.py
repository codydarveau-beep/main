"""Approximate software layout previews from production HUD quad recorder, not GPU screenshots."""
from pathlib import Path
import subprocess
import numpy as np
from PIL import Image,ImageDraw
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
def render(args):
 run=subprocess.run([str(V/'hud194_asan'),*args],cwd=R,capture_output=True,text=True,check=True)
 atlas=np.frombuffer(Path('/tmp/myro40-skin.raw').read_bytes(),np.uint8).reshape(2048,512,4)[:,:,[2,1,0,3]].astype(np.float32)/255
 dst=np.ones((480,640,4),np.float32);dst[:,:,:3]=(.16,.22,.2)
 for line in run.stdout.splitlines():
  a=line.split()
  if not a or a[0]not in ['F','Q']:continue
  x,y,w,h=map(float,a[1:5]);l=max(0,int(np.ceil(x-.5)));r=min(640,int(np.ceil(x+w-.5)));t=max(0,int(np.ceil(y-.5)));b=min(480,int(np.ceil(y+h-.5)))
  if r<=l or b<=t:continue
  if a[0]=='F':
   c=int(a[5]);sample=np.array([(c>>16&255)/255,(c>>8&255)/255,(c&255)/255,(c>>24&255)/255])[None,None,:]
  else:
   u,v,uw,vh=map(float,a[5:9]);xx=u+(np.arange(l,r)+.5-x)*uw/w-.5;yy=v+(np.arange(t,b)+.5-y)*vh/h-.5
   xx=np.clip(xx,0,511);yy=np.clip(yy,0,2047);x0=xx.astype(int);y0=yy.astype(int);x1=np.minimum(x0+1,511);y1=np.minimum(y0+1,2047);fx=(xx-x0)[None,:,None];fy=(yy-y0)[:,None,None]
   sample=(atlas[y0[:,None],x0]*(1-fx)+atlas[y0[:,None],x1]*fx)*(1-fy)+(atlas[y1[:,None],x0]*(1-fx)+atlas[y1[:,None],x1]*fx)*fy
  out=dst[t:b,l:r];alpha=sample[:,:,3:4];out[:,:,:3]=sample[:,:,:3]*alpha+out[:,:,:3]*(1-alpha)
 im=Image.fromarray(np.uint8(np.clip(dst[:,:,:3]*255,0,255)),'RGB');d=ImageDraw.Draw(im);d.text((8,466),'HOST LAYOUT PREVIEW - not Xbox GPU output',fill='white');return im
for name,args in [('basic-info',['status44','8488']),('status',['status50','1','0']),('inventory',['inventory','18']),('equipment',['equip49']),('diagnostics',['diagvideo255','7','0','0'])]:render(args).save(V/f'GUI-Preview270-{name}.png')
print('Approximate host layouts generated; no GPU/CRT acceptance claim.')
