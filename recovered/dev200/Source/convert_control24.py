"""MIT. Read-only source-trait extraction for the two Mage control tests.
Usage: python convert_control24.py /path/to/hercules/db/pre-re
Input data remains licensed GPL3+ by Hercules.
"""
from pathlib import Path
import re,sys,json
root=Path(__file__).resolve().parent;db=Path(sys.argv[1]);s=(db/'mob_db.conf').read_text();entries={int(m[1]):m[2]for m in re.finditer(r'^\{\s*\n\s*Id:\s*(\d+)([\s\S]*?)(?=^\},)',s,re.M)}
a=(db/'attr_fix.conf').read_text();rates={}
for m in re.finditer(r'^(Ele_\w+):\s*\{([\s\S]*?)(?=^\})',a,re.M):
 for lv in re.finditer(r'Lv(\d):\s*\{([^}]*)\}',m[2]):rates[m[1],int(lv[1])]={k:int(v)for k,v in re.findall(r'(Ele_\w+):\s*(-?\d+)',lv[2])}
ids=list(map(int,re.findall(r'\{"[^"]+",[^\n]*?,(\d{4}),\d+,\d+,\d+,\d+,\d+,\d+\}',(root/'encounter_data.h').read_text())));assert len(ids)==18
out=[]
for id in ids:
 t=entries[id];m=re.search(r'Element:\s*\("(Ele_\w+)",\s*(\d)\)',t);el,lv=(m[1],int(m[2]))if m else('Ele_Neutral',1);lv=max(1,lv);race=re.search(r'Race:\s*"(\w+)"',t);race=race[1]if race else'RC_Formless';md=re.search(r'Mdef:\s*(\d+)',t);md=int(md[1])if md else 0
 # MD_STATUSIMMUNE is represented in the source boss/status mode entries.
 immune=race=='RC_Undead'or el=='Ele_Undead'or bool(re.search(r'(?:Boss|StatusImmune):\s*true',t))
 out.append(dict(id=id,element=el,level=lv,mdef=md,immune=int(immune),water=rates[el,lv]['Ele_Water'],wind=rates[el,lv]['Ele_Wind']))
with (root/'mob_control_traits.h').open('w')as f:
 f.write('/* Generated Hercules pre-re traits/element rates. GPL3+ data. */\n')
 for name,key in [('mobFreezeImmune','immune'),('mobFreezeMdef','mdef'),('mobWaterRate','water'),('mobWindRate','wind')]:f.write('static const short '+name+'[MOB_SPEC_COUNT]={'+','.join(str(r[key])for r in out)+'};\n')
(root.parent/'CONTROL-TRAITS-REPORT.json').write_text(json.dumps(out,indent=2));print(out)
