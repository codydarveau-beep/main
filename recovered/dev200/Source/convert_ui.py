"""MIT. Bake a small antialiased font atlas and one supplied NPC sprite.
Requires Pillow, NumPy; font path can be provided as the second argument.
"""
from pathlib import Path
import sys,zlib,struct
from PIL import Image,ImageFont,ImageDraw
import numpy as np
root=Path(__file__).resolve().parent.parent
source=(root/'Source/convert_combat_assets.py').read_text().split("body='data")[0]
ns={'__file__':str(root/'Source/convert_combat_assets.py'),'__name__':'ui_baker'}
saved=sys.argv[:];sys.argv=[sys.argv[0],sys.argv[1]];exec(compile(source,'sprite-baker','exec'),ns);sys.argv=saved
raw=ns['bake']('merchant','data\\sprite\\npc\\4_m_01',None,[0,0,0,0,0],90)
fontpath=sys.argv[2] if len(sys.argv)>2 else '/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf'
font=ImageFont.truetype(fontpath,13);canvas=Image.new('RGBA',(256,128));d=ImageDraw.Draw(canvas);widths=[]
for i in range(96):
 c=chr(i+32);x=i%16*16;y=i//16*20;d.text((x,y+14),c,font=font,fill=(255,255,255,255),anchor='ls');widths.append(max(3,round(font.getlength(c))))
a=np.array(canvas,dtype=np.uint32);argb=(a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2];canvas.save(root/'font-preview.png')
with (root/'Source/ui_assets.c').open('w') as f:
 for name,data in [('font_image',argb.astype('<u4').tobytes()),('merchant_image',raw)]:
  cp=zlib.compress(data,9);f.write('const unsigned int %s_raw=%d,%s_size=%d;\nconst unsigned char %s[]={\n'%(name,len(data),name,len(cp),name))
  for j in range(0,len(cp),32):f.write(','.join(map(str,cp[j:j+32]))+',\n')
  f.write('};\n')
 f.write('const unsigned char fontWidths[96]={'+','.join(map(str,widths))+'};\n')
