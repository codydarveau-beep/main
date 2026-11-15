"""MIT. Bake Acolyte/Thief body+cast actions and source HP/SP/racial tables."""
from pathlib import Path
import sys,re,zipfile,csv,io,hashlib,zlib,json,os,time
ROOT=Path(__file__).resolve().parent.parent
source=(ROOT/'Source/convert_combat_assets.py').read_text().split("body='data")[0]
source=source.replace('argb=(a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2]','argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)').replace("argb.astype('<u4')","argb.astype('<u2')").replace('anchor,len(pixels)))','anchor,len(pixels)|0x80000000))')
saved=sys.argv[:];sys.argv=[sys.argv[0],saved[1]];ns={'__file__':str(ROOT/'Source/convert_combat_assets.py'),'__name__':'job_bake'};exec(compile(source,'job_bake','exec'),ns);sys.argv=saved
head='data\\sprite\\인간족\\머리통\\남\\1_남';blobs=[]
for name,stem in [('Archer','궁수_남'),('Merchant','상인_남')]:
 body='data\\sprite\\인간족\\몸통\\남\\'+stem
 if body+'.spr' not in ns['assets']:
  print([k for k in ns['assets'] if '몸통' in k and k.endswith('.spr')]);raise RuntimeError('Missing '+body)
 blobs.append(ns['bake'](name,body,head,[0,1,5,6,8,2,4],90))
with (ROOT/'Source/last_job_assets.c').open('w') as f:
 f.write('/* Original user supplied job graphics; ownership retained. */\n')
 for i,raw in enumerate(blobs,5):
  cp=zlib.compress(raw,9);f.write('const unsigned int job%d_raw=%d,job%d_size=%d;\nconst unsigned char job%d[]={\n'%(i,len(raw),i,len(cp),i))
  for at in range(0,len(cp),32):f.write(','.join(map(str,cp[at:at+32]))+',\n')
  f.write('};\n')
with zipfile.ZipFile(saved[2]) as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 def text(n):
  r=next(r for r in rows if r['virtual_path']=='server/db/pre-re/'+n);b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];return re.sub(r'//[^\n]*','',b.decode('utf-8-sig'))
 jobs=text('job_db.conf');mobs=text('mob_db.conf')
 def block(s,n):
  m=re.search(r'(?m)^\s*'+re.escape(n)+r'\s*:\s*\{',s);assert m,n
  start=m.end();d=1;i=start
  while d:
   if s[i]=='{':d+=1
   if s[i]=='}':d-=1
   i+=1
  return s[start:i-1]
 def nums(s,k):return list(map(int,re.findall(r'\d+',re.search(r'\b'+k+r'\s*:\s*\[([^\]]*)\]',s)[1])))
 p=ROOT/'Source/progression_data.h';s=p.read_text()
 for name,key in [('jobHP','HPTable'),('jobSP','SPTable')]:
  def table(n):
   b=block(jobs,n)
   if re.search(r'\b'+key+r'\s*:',b):return nums(b,key)[:20]
   inherit=re.search(r'Inherit'+('HP' if key=='HPTable' else 'SP')+r'\s*:\s*\(\s*"([^"]+)"',b)
   assert inherit,n
   return table(inherit[1])
  a=[table(n) for n in ['Novice','Swordsman','Magician','Acolyte','Thief','Archer','Merchant']]
  replacement='static const int %s[7][20]={%s};'%(name,','.join('{'+','.join(map(str,v))+'}' for v in a))
  s=re.sub(r'static const int '+name+r'\[[357]\]\[20\]=\{.*?\};',replacement,s)
 s=re.sub(r'\n#define LEARN_COUNT 17\n','\n',s);p.write_text(s+'\n#define LEARN_COUNT 17\n');os.utime(p,(time.time()+21600,)*2)
 (ROOT/'LAST-JOBS-REPORT.json').write_text(json.dumps({'decoded_body_bytes':list(map(len,blobs)),'actions_per_body':56,'source_job_table':'server/db/pre-re/job_db.conf'},indent=2))
print('Generated Acolyte/Thief:',list(map(len,blobs)))
