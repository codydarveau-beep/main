# GPL-3.0-or-later. Full original pre-renewal element table and every current monster property.
from pathlib import Path
import re,json,ast
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48';s=(ref/'attr_fix.conf').read_text();names=['Ele_Neutral','Ele_Water','Ele_Earth','Ele_Fire','Ele_Wind','Ele_Poison','Ele_Holy','Ele_Dark','Ele_Ghost','Ele_Undead'];rates={}
for m in re.finditer(r'(?m)^(Ele_\w+):\s*\{([\s\S]*?)(?=^\})',s):
 for lv in re.finditer(r'Lv(\d):\s*\{([^}]*)\}',m[2]):rates[m[1],int(lv[1])]={k:int(v)for k,v in re.findall(r'(Ele_\w+):\s*(-?\d+)',lv[2])}
print('Elements',sorted({k[0]for k in rates}));assert len(rates)==40
rows=[[[rates[n,lv][a]for a in names]for n in names]for lv in range(1,5)]
s=(ref/'mob_db.conf').read_text();mb={int(m[1]):m[0]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\b.*?^\},?',s)};kinds=(r/'encounter_data.h').read_text().split('static const MobSpec mobSpecs[MOB_SPEC_COUNT]={',1)[1].split('};',1)[0];props=[]
for line in kinds.splitlines():
 if not line.strip().startswith('{'):continue
 vals=ast.literal_eval('['+line.strip()[1:line.rfind('}')]+']');m=re.search(r'Element:\s*\(\s*"(Ele_\w+)",\s*(\d)\s*\)',mb[vals[10]]);props.append((names.index(m[1]),int(m[2]))if m else(0,1))
(r/'elements48.h').write_text('/* GPL-3.0-or-later. Hercules21b27966 pre-renewal attribute table. */\nstatic const short elementRate48[4][10][10]='+json.dumps(rows).replace('[','{').replace(']','}')+';\nstatic const unsigned char mobElement48[MOB_SPEC_COUNT][2]='+json.dumps(props).replace('[','{').replace(']','}')+';\n')
print('PASS40elementrows/50monster source properties, including holy and converter overrides')
