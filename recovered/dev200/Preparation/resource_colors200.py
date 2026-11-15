from pathlib import Path
import re,zlib
from PIL import Image
S=Path('/workspace/myro/dev200/Source');p=S/'skin_assets.c';s=p.read_text();m=re.search(r'skin_image\[\]=\{([^}]+)\}',s);im=Image.frombytes('RGBA',(512,2048),zlib.decompress(bytes(int(x,0)for x in m[1].split(',')if x.strip())),'raw','BGRA');glyph=[tuple(map(int,x))for x in re.findall(r'\{(\d+),(\d+)\}',(S/'font_native53.h').read_text())];assert len(glyph)==960
for row,color in enumerate([(45,104,64),(48,88,145)]):
 y=2016+row*16;assert im.crop((256,y,416,y+16)).getchannel('A').getbbox()is None
 for n in range(10):
  x0,y0=glyph[4*192+ord(str(n))-32];tile=im.crop((x0,y0,x0+16,y0+16));a=tile.getchannel('A');colored=Image.new('RGBA',(16,16),color+(255,));colored.putalpha(a);im.paste(colored,(256+n*16,y))
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original atlas preserved; healthy HP/SP digit strips in verified empty cells. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={%s};\n'%(len(raw),len(cp),','.join(map(str,cp))))
