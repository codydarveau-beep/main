# MIT. Bake only used original client interface images into one 512 KiB atlas.
from pathlib import Path
import csv,io,zipfile,hashlib,sys,zlib,re,json
import numpy as np
from PIL import Image,ImageDraw,ImageFont
root=Path(__file__).resolve().parent.parent
z=zipfile.ZipFile(sys.argv[1]);rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))));assets={r['virtual_path'].lower():r for r in rows}
def read(n):
 r=next(r for k,r in assets.items() if k.endswith('\\'+n.lower()));b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];return b
atlas=Image.new('RGBA',(512,256));meta=[]
# dark text atlas shares white HUD font glyph layout
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',11)
white=Image.new('RGBA',(256,96));dark=Image.new('RGBA',(256,96));widths=[]
for i in range(96):
 c=chr(i+32);x=i%16*16;y=i//16*16
 for im,col in [(white,(255,255,255,255)),(dark,(30,43,65,255))]:ImageDraw.Draw(im).text((x,y+13),c,font=font,fill=col,anchor='ls')
 widths.append(max(3,round(font.getlength(c))))
atlas.paste(dark,(0,0));atlas.paste(white,(0,160));x=256;y=0;rowh=0
names=['basewin_mini.bmp','sys_close_off.bmp','sys_close_on.bmp','btn_status_off.bmp','btn_items_off.bmp','btn_equip_off.bmp','btn_skill_off.bmp','itemwin_mid.bmp','nv_basic.bmp','nv_firstaid.bmp','sm_bash.bmp','mg_firebolt.bmp','wz_heavendrive.bmp','al_blessing.bmp','al_incagi.bmp','pr_kyrie.bmp']
# file names for original item icons mapped through the supplied resource table
for n in ['사과.bmp','젤로피.bmp','클로버.bmp','나이프.bmp','코튼셔츠.bmp','샌들.bmp','가드.bmp','빨간포션.bmp']:
 if any(k.endswith('\\'+n) for k in assets):names.append(n)
names+=['sm_magnum.bmp','mg_coldbolt.bmp']
# Layout title strip below the font, icons in the right half.
for n in names:
 try:im=Image.open(io.BytesIO(read(n))).convert('RGBA')
 except StopIteration:continue
 a=np.array(im);mask=(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245);a[mask,3]=0;im=Image.fromarray(a)
 if n=='basewin_mini.bmp':im=im.crop((0,0,280,16));xx,yy=0,130
 else:
  if x+im.width>512:x=256;y+=rowh+2;rowh=0
  assert y+im.height<=256;xx,yy=x,y;x+=im.width+2;rowh=max(rowh,im.height)
 atlas.alpha_composite(im,(xx,yy));meta.append((n,xx,yy,im.width,im.height))
# Solid-colour patches let panels/highlights use the same textured batch as text.
colors=set()
for name in ['main.c','hud.h','window_draw.h']:
 for h in re.findall(r'0xff[0-9a-fA-F]{6}',(root/'Source'/name).read_text()):colors.add(int(h,16))
colors=sorted(colors)
assert len(colors)<=64
for i,c in enumerate(colors):
 xx=284+(i%28)*8;yy=100+(i//28)*8
 ImageDraw.Draw(atlas).rectangle((xx,yy,xx+5,yy+5),fill=((c>>16)&255,(c>>8)&255,c&255,(c>>24)&255))
with (root/'Source/skin_colors.h').open('w') as f:
 f.write('/* Generated solid texels in the shared atlas. */\nstatic const unsigned skinColors[]={'+','.join(hex(c)+'u' for c in colors)+'};\n')
a=np.array(atlas,dtype=np.uint32);raw=((a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2]).astype('<u4').tobytes();packed=zlib.compress(raw,9)
(root/'skin-preview.png').write_bytes(b'')
atlas.save(root/'skin-preview.png')
with (root/'Source/skin_assets.c').open('w') as f:
 f.write('/* Original user supplied RO artwork; ownership retained. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(packed)))
 for i in range(0,len(packed),32):f.write(','.join(map(str,packed[i:i+32]))+',\n')
 f.write('};\n')
with (root/'Source/skin_data.h').open('w') as f:
 f.write('/* Generated atlas rectangles; index 0 is the original title bar. */\nstatic const unsigned short skinRects[][4]={\n')
 for n,x,y,w,h in meta:f.write('{%d,%d,%d,%d}, /* %s */\n'%(x,y,w,h,n))
 f.write('};\n')
# Replace just font image and widths, retain the already-working NPC bytes.
p=root/'Source/ui_assets.c';s=p.read_text();a=np.array(white.resize((256,128)),dtype=np.uint32);b=((a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2]).astype('<u4').tobytes();cp=zlib.compress(b,9)
start=s.index('const unsigned int font_image_raw');end=s.index('const unsigned int merchant_image_raw')
s=s[:start]+'const unsigned int font_image_raw=%d,font_image_size=%d;\nconst unsigned char font_image[]={\n'%(len(b),len(cp))+','.join(map(str,cp))+'};\n'+s[end:]
s=re.sub(r'const unsigned char fontWidths\[96\]=\{.*?\};','const unsigned char fontWidths[96]={'+','.join(map(str,widths))+'};',s,flags=re.S);p.write_text(s)
(root/'skin-index.json').write_text(json.dumps(meta,ensure_ascii=False,indent=2))
print('Atlas',len(raw),'bytes, packed',len(packed),'images',len(meta))
