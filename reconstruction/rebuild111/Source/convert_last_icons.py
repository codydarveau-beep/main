"""MIT. Add five original skill icons inside unused existing HUD atlas space."""
from pathlib import Path
import re,zipfile,csv,io,hashlib,zlib,sys,os,time
from PIL import Image
ROOT=Path(__file__).resolve().parent
p=ROOT/'skin_assets.c';s=p.read_text();cp=bytes(map(int,re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1].replace('\n','').strip().strip(',').split(',')));b=zlib.decompress(cp);im=Image.frombytes('RGBA',(512,256),b,'raw','BGRA')
rects=[]
with zipfile.ZipFile(sys.argv[1]) as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,(x,y) in zip(['ac_owl.bmp','ac_vulture.bmp','ac_double.bmp','mc_discount.bmp','mc_overcharge.bmp','mc_mammonite.bmp','보우.bmp'],[(288+i*26,218) for i in range(7)]):
  r=next(r for r in rows if r['virtual_path'].lower().endswith('\\'+name));raw=z.read(r['payload']);assert hashlib.sha256(raw).hexdigest()==r['sha256'];icon=Image.open(io.BytesIO(raw)).convert('RGBA').resize((24,24))
  icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa) for rr,gg,bb,aa in icon.getdata()]);im.paste(icon,(x,y));rects.append((x,y,24,24))
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original user supplied RO artwork; ownership retained. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+''.join(','.join(map(str,cp[i:i+32]))+',\n' for i in range(0,len(cp),32))+'};\n');os.utime(p,(time.time()+21600,)*2)
p=ROOT/'skin_data.h';s=p.read_text();old=re.findall(r'\{\d+,\d+,\d+,\d+\}',s)[:31];p.write_text('/* Original HUD atlas rectangles, with new class icons26..30. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%r for r in rects])+'\n};\n');os.utime(p,(time.time()+21600,)*2)
print('Original class icons added; atlas unchanged:',len(raw),'bytes')
