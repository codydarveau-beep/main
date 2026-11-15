# MIT. Reproducible original job animations and supplied progression-table extraction.
from pathlib import Path
import sys,re,zipfile,csv,io,hashlib,zlib,json
root=Path(__file__).resolve().parent.parent
jobzip=Path(sys.argv[1]);expzip=Path(sys.argv[2])
source=(root/'Source/convert_combat_assets.py').read_text().split("body='data")[0]
source=source.replace('argb=(a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2]','argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)').replace("argb.astype('<u4')","argb.astype('<u2')").replace('anchor,len(pixels)))','anchor,len(pixels)|0x80000000))')
saved=sys.argv[:];sys.argv=[sys.argv[0],str(jobzip)];ns={'__file__':str(root/'Source/convert_combat_assets.py'),'__name__':'job_bake'};exec(compile(source,'job_bake','exec'),ns);sys.argv=saved
head='data\\sprite\\인간족\\머리통\\남\\1_남';blobs=[]
for name,stem in [('swordsman','검사_남'),('mage','마법사_남')]:
 raw=ns['bake'](name,'data\\sprite\\인간족\\몸통\\남\\'+stem,head,[0,1,5,6,8,2],90);blobs.append(raw)
with (root/'Source/job_assets.c').open('w') as f:
 f.write('/* Original user supplied job graphics. Ownership retained. */\n')
 for i,raw in enumerate(blobs,1):
  cp=zlib.compress(raw,9);f.write('const unsigned int job%d_raw=%d,job%d_size=%d;\nconst unsigned char job%d[]={\n'%(i,len(raw),i,len(cp),i))
  for at in range(0,len(cp),32):f.write(','.join(map(str,cp[at:at+32]))+',\n')
  f.write('};\n')
z=zipfile.ZipFile(expzip);rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))));hashes={}
def text(name):
 r=next(r for r in rows if r['virtual_path']=='server/db/pre-re/'+name);b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];hashes[name]=r['sha256'];return re.sub(r'//[^\n]*','',b.decode('utf-8-sig'))
exp=text('exp_group_db.conf');jobs=text('job_db.conf');tree=text('skill_tree.conf')
def block(s,name):
 m=re.search(r'(?m)^\s*'+re.escape(name)+r'\s*:\s*\{',s);assert m,name
 start=m.end();depth=1;i=start
 while depth:
  if s[i]=='{':depth+=1
  if s[i]=='}':depth-=1
  i+=1
 return s[start:i-1]
def nums(s,key):
 m=re.search(r'\b'+key+r'\s*:\s*\[([^\]]*)\]',s);assert m,key;return list(map(int,re.findall(r'\d+',m[1])))
base=nums(block(exp.split('job_exp_group_db:')[0],'FirstClasses'),'Exp')[:19]
jexp=exp.split('job_exp_group_db:')[1];nov=nums(block(jexp,'Novice'),'Exp');first=nums(block(jexp,'FirstClasses'),'Exp')[:19]
hp=[];sp=[]
for name in ['Novice','Swordsman','Magician']:
 b=block(jobs,name);hp.append(nums(b,'HPTable')[:20]);sp.append(nums(b,'SPTable')[:20])
assert base[:9]==[9,16,25,36,77,112,153,200,253]
assert re.search(r'SM_BASH\s*:\s*5',block(tree,'Swordsman'))
with (root/'Source/progression_data.h').open('w') as f:
 f.write('/* Generated from supplied Hercules pre-re tables; original GPL3+ data. */\n#define TEST_LEVEL_CAP 20\n#define TEST_JOB_CAP 20\n')
 for name,values in [('baseCurve',base),('jobCurve',nov),('firstJobCurve',first)]:f.write('static const int %s[%d]={%s};\n'%(name,len(values),','.join(map(str,values))))
 for name,values in [('jobHP',hp),('jobSP',sp)]:f.write('static const int %s[3][20]={%s};\n'%(name,','.join('{'+','.join(map(str,v))+'}' for v in values)))
(root/'JOB-CONVERSION-REPORT.json').write_text(json.dumps({'sources':hashes,'base_cap':20,'first_job_cap':20,'novice_job_cap':10,'magnum_requires_bash':5,'decoded_sprite_bytes':list(map(len,blobs))},indent=2))
print('PASS job assets and source progression tables')
