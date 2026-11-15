from pathlib import Path
import sys,ast,struct,math,json
import numpy as np
from PIL import Image,ImageDraw
R=Path('/workspace/myro/dev200');sys.path.insert(0,str(R/'Source'));from asset_index50 import paths,key50
import ro_sprite_bake as ro
ns=dict(ro=ro,np=np,Image=Image,struct=struct,math=math,Reader=ro.Reader);tree=ast.parse((R/'Source/convert_classic49.py').read_text());exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name=='sprites'],type_ignores=[]),'source-SPR','exec'),ns)
rows=[('Roan',2,'남'),('Yuufa',1,'여'),('Judia',4,'여'),('Maya',6,'여')];sheet=Image.new('RGBA',(1000,480),(50,60,65,255));d=ImageDraw.Draw(sheet);report=[]
for row,(name,style,sex)in enumerate(rows):
 data=paths[key50(f'data/sprite/인간족/머리통/{sex}/{style}_{sex}.spr')].read_bytes();cells=[]
 for col,colour in enumerate([-1]+list(range(9))):
  pal=paths.get(key50(f'data/palette/머리/머리{style}_{sex}_{colour}.pal'))if colour>=0 else None
  if colour>=0 and not pal:continue
  b=data[:-1024]+pal.read_bytes()if pal else data;images,_=ns['sprites'](b);head=images[0];head=head.resize((head.width*3,head.height*3),Image.Resampling.NEAREST);sheet.alpha_composite(head,(col*100+(100-head.width)//2,row*120+10));d.text((col*100+5,row*120+100),name+' '+('SPR'if colour<0 else str(colour)),fill='white');cells.append(dict(colour=colour,palette=str(pal)if pal else None))
 report.append(dict(name=name,style=style,sex=sex,options=cells))
sheet.save(R/'Validation/campaign-hair-palettes200.png');(R/'Preparation/Campaign-Hair-Options200.json').write_text(json.dumps(report,indent=2)+'\n')
