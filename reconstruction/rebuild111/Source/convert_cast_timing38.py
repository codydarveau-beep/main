"""Regenerate timing data from the supplied Hercules pre-re skill_db.conf (GPL3+)."""
from pathlib import Path
import re,json,hashlib,sys
r=Path(__file__).resolve().parent
src=Path(sys.argv[1]).read_text()
ids={3:'MG_FIREBOLT',9:'MG_COLDBOLT',21:'MG_LIGHTNINGBOLT',22:'MG_NAPALMBEAT',23:'MG_SOULSTRIKE',24:'MG_FIREBALL',29:'MG_FROSTDIVER',30:'MG_THUNDERSTORM',31:'MG_FIREWALL',49:'MG_STONECURSE',51:'AL_HOLYLIGHT',67:'MG_ENERGYCOAT',6:'AL_INCAGI',41:'AL_DECAGI',33:'AL_ANGELUS',59:'AC_CHARGEARROW',56:'TF_PICKSTONE'}
def values(block,key):
 m=re.search(r'\b'+key+r':\s*(\{[^}]*\}|\d+)',block)
 if not m:return [0]*10
 v=m[1]
 if v.startswith('{'):
  d={int(a):int(b) for a,b in re.findall(r'Lv(\d+):\s*(\d+)',v)};return [d.get(i,0) for i in range(1,11)]
 return [int(v)]*10
rows=[]
for id,name in ids.items():
 pos=src.index('Name: "'+name+'"');a=src.rfind('\n{',0,pos);b=src.index('\n},',pos);block=src[a:b]
 rows.append(dict(id=id,name=name,cast=values(block,'CastTime'),delay=values(block,'AfterCastActDelay'),cooldown=values(block,'CoolDown'),hp=values(block,'HPCost'),interruptible=bool(re.search(r'InterruptCast:\s*true',block))))
header='/* Generated from supplied Hercules pre-re skill_db.conf (GPL-3.0-or-later).\n * Reproduce with convert_cast_timing38.py; source identity recorded in cast-timing38.json. */\n#ifndef MYRO_CAST_TIMING_H\n#define MYRO_CAST_TIMING_H\ntypedef struct {unsigned id;unsigned short cast[10],delay[10],cooldown[10],hp[10];unsigned char interruptible;} CastTiming;\nstatic const CastTiming castTimings[]={\n'
for row in rows:header+='{%d,%s,%s,%s,%s,%d},\n'%(row['id'],*['{'+','.join(map(str,row[k]))+'}' for k in ['cast','delay','cooldown','hp']],row['interruptible'])
header+='};\nstatic const CastTiming*cast_timing(unsigned id){for(unsigned i=0;i<sizeof(castTimings)/sizeof(*castTimings);i++)if(castTimings[i].id==id)return &castTimings[i];return NULL;}\n#endif\n'
(r/'cast_timing.h').write_text(header);(r/'cast-timing38.json').write_text(json.dumps(dict(source='User-supplied Hercules db/pre-re/skill_db.conf',sha256=hashlib.sha256(src.encode()).hexdigest(),rows=rows),indent=2)+'\n')
