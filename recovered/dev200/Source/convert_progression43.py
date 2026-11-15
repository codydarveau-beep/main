# MIT. Import full pre-renewal player curves without changing prototype stat formula.
from pathlib import Path
import re
r=Path(__file__).resolve().parent;s=(r.parent.parent/'asset-library/Payon43-return/server/db/pre-re/exp_group_db.conf').read_text();j=(r.parent.parent/'asset-library/Payon43-return/server/db/pre-re/job_db.conf').read_text()
def block(s,n):
 m=re.search(r'(?m)^\s*'+n+r'\s*:\s*\{',s);assert m,n
 start=m.end();i=start;d=1
 while d:
  if s[i]=='{':d+=1
  if s[i]=='}':d-=1
  i+=1
 return s[start:i-1]
def nums(s,key):
 b=re.search(r'\b'+key+r'\s*:\s*\[([^]]*)\]',s)[1];b=re.sub(r'//[^\n]*','',b);return list(map(int,re.findall(r'\d+',b)))
def table(n,key):
 b=block(j,n)
 if re.search(r'\b'+key+r'\s*:',b):return nums(b,key)[:99]
 m=re.search(r'\bInherit'+('HP'if key=='HPTable'else'SP')+r':\s*\(\s*"([^"]+)"',b)or re.search(r'\bInherit:\s*\(\s*"([^"]+)"',b);assert m,n;return table(m[1],key)
old=(r/'progression_data.h').read_text();parts=['/* Generated from supplied Hercules pre-re curves. Stat formula remains prototype. */','#define TEST_LEVEL_CAP 99','#define TEST_JOB_CAP 70']
base=block(s,'base_exp_group_db');jobs=block(s,'job_exp_group_db')
for name,values in [('baseCurve',nums(block(base,'FirstClasses'),'Exp')),('highBaseCurve',nums(block(base,'TranscendedClasses'),'Exp')),('jobCurve',nums(block(jobs,'Novice'),'Exp')),('firstJobCurve',nums(block(jobs,'FirstClasses'),'Exp')),('secondJobCurve',nums(block(jobs,'SecondClasses'),'Exp')),('highJobCurve',nums(block(jobs,'TranscendedSecondClasses'),'Exp'))]:
 assert len(values)in[98,9,49,69],(name,len(values));parts.append('static const int '+name+'['+str(len(values))+']={'+','.join(map(str,values))+'};')
for name,key in [('jobHP','HPTable'),('jobSP','SPTable')]:
 rows=[table(n,key)for n in ['Novice','Swordsman','Magician','Acolyte','Thief','Archer','Merchant','Knight','High_Wizard']];assert all(len(x)==99 for x in rows);parts.append('static const int '+name+'[9][99]={'+','.join('{'+','.join(map(str,x))+'}'for x in rows)+'};')
parts+=['static int progression_job_cap43(unsigned job){return job==8?70:job?50:10;}','static const int*progression_job_curve43(unsigned job){return job==8?highJobCurve:job==7?secondJobCurve:job?firstJobCurve:jobCurve;}','static const int*progression_base_curve43(unsigned job){return job==8?highBaseCurve:baseCurve;}','#define LEARN_COUNT 65']
(r/'progression_data.h').write_text('\n'.join(parts)+'\n')
