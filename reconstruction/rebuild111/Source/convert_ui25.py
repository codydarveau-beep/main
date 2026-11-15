"""MIT. Two original Mage icons and a native 9px EXP font in unused atlas cells.
Usage: python convert_ui25.py HUD-Assets.zip. Idempotent, texture size unchanged.
"""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image,ImageDraw,ImageFont
r=Path(__file__).resolve().parent;p=r/'skin_assets.c';cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',p.read_text(),re.S)[1])));im=Image.frombytes('RGBA',(512,256),zlib.decompress(cp),'raw','BGRA')
rects=[(256,186,24,24),(256,212,24,24)];report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,(x,y,w,h)in zip(['mg_frostdiver.bmp','mg_thunderstorm.bmp'],rects):
  row=next(row for row in rows if row['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);icon=icon.resize((w,h),Image.Resampling.LANCZOS);im.paste(icon,(x,y));report.append(dict(icon=name,sha256=row['sha256'],rect=[x,y,w,h]))
glyphs=''.join(dict.fromkeys(' BASEJOBEXP:0123456789/MAX'));font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',9);widths=[]
for k,c in enumerate(glyphs):
 cell=Image.new('RGBA',(12,12));d=ImageDraw.Draw(cell);d.text((0,10),c,font=font,fill=(30,43,65,255),anchor='ls');alpha=cell.getchannel('A').point(lambda a:min(255,round(a*1.16)));cell.putalpha(alpha);im.paste(cell,(k%16*12,98+k//16*12));widths.append(round(font.getlength(c)))
(r/'compact_font.h').write_text('/* Native 9px EXP glyphs; no fractional texture scaling. */\nstatic const char compactGlyphs[]='+json.dumps(glyphs)+';\nstatic const unsigned char compactWidths[]={'+','.join(map(str,widths))+'};\nstatic void ui_exp_text(int x,int y,const char*fmt,...){char line[96];va_list a;va_start(a,fmt);vsnprintf(line,sizeof(line),fmt,a);va_end(a);for(const char*c=line;*c;c++){const char*p=strchr(compactGlyphs,*c);if(!p)continue;unsigned k=p-compactGlyphs;if(*c!=\' \')hud_quad(x,y,12,12,(k%16)*12,98+(k/16)*12,12,12);x+=compactWidths[k]+1;}}\n')
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original client artwork and native-size font glyphs. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:46];assert len(old)==46;p.write_text('/* Stable icon indices; Mage control skills at 46/47. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%v for v in rects])+'\n};\n');im.save(r.parent/'hud25-atlas.png');(r.parent/'MAGE-ICONS-REPORT.json').write_text(json.dumps(report,indent=2));print('PASS two original icons + native EXP font; same',len(raw),'byte atlas')

fp=r/'compact_font.h'
fp.write_text(fp.read_text()+'\nstatic int ui_exp_width(const char*s){int w=0;for(;*s;s++){const char*p=strchr(compactGlyphs,*s);if(p)w+=compactWidths[p-compactGlyphs]+1;}return w;}\n')
