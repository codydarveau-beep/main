from pathlib import Path
import re,json,struct,zlib,hashlib,unicodedata
R=Path('/workspace/myro');B=R/'dev200';text=(R/'story-design/CAMPAIGN.md').read_text();part=text.split('## 6. Complete main-campaign scene script')[1].split('## 7.')[0]
chapters={int(a):b for a,b in re.findall(r'^### Chapter (\d+) — (.+)$',part,re.M)}
pattern=r'^\*\*(\d+)\.(\d+) — ([^*]+)\*\*([^\n]*)\n(.*?)(?=^\*\*\d+\.\d+ —|^### Chapter|\Z)'
scenes=[]
for m in re.finditer(pattern,part,re.M|re.S):
 ch,n=int(m[1]),int(m[2]);body=m[5];lines=[]
 for line in body.splitlines():
  line=line.strip()
  if not line or ':'not in line:continue
  who,words=line.split(':',1)
  if "'"not in words:continue
  quotes=words[words.find("'")+1:words.rfind("'")].split("' / '")
  if not quotes:continue
  role='all'
  if re.match(r'^[VPK] — ',who):role={'V':'Vanguard','P':'Pathfinder','K':'Keeper'}[who[0]];who=who[4:]
  lines.append(dict(speaker=who.strip(),role=role,kind='choice'if 'choices'in who.lower()else'line',text=quotes))
 scenes.append(dict(id=f'{ch}.{n}',cursor=(ch-1)*3+n-1,chapter=ch,title=m[3].rstrip('.'),chapterTitle=chapters[ch],staging=m[4].strip(),dialogue=lines,fullSceneText=body.strip(),placement='requires-map-and-trigger-audit',playable=False))
assert len(scenes)==36 and [x['cursor']for x in scenes]==list(range(36))
D=B/'Campaign';D.mkdir(exist_ok=True);index=[]
with (D/'campaign-scenes.bin').open('wb')as f:
 for scene in scenes:
  raw=json.dumps(scene,ensure_ascii=True,separators=(',',':')).encode();packed=zlib.compress(raw,6);index.append(dict(id=scene['id'],offset=f.tell(),packed=len(packed),raw=len(raw),crc32=zlib.crc32(raw)));f.write(packed)
(B/'Preparation/Campaign-Scenes200.json').write_text(json.dumps(dict(format=1,scenes=scenes,discIndex=index,scope='Authored scene text; trigger/map/encounter integration pending. Not playable scenes yet.'),indent=2))
def cstr(s):return json.dumps(unicodedata.normalize('NFKD',s).encode('ascii','ignore').decode())
h=['/* MIT. Small campaign journal metadata; full scene text stays on disc. */\n#ifndef MYRO_CAMPAIGN_DATA200_H\n#define MYRO_CAMPAIGN_DATA200_H\ntypedef struct{const char*title,*objective;}CampaignQuest200;\nstatic const CampaignQuest200 campaignQuests200[]={\n']
objectives={0:'Finish Training Grounds. Then meet Nera on the entrance road. Story scene placement is under development.',1:'Complete your first-job examination, then confirm your permanent story role.',2:'Speak with Roan and Yuufa at the first camp.'}
for x in scenes:h.append('{'+cstr(x['chapterTitle'])+','+cstr(objectives.get(x['cursor'],'Continue '+x['title']+'. Destination will be supplied after quest integration.'))+'},\n')
h.append('};\n#include "campaign_objectives200.h"\n#endif\n');(B/'Source/campaign_data200.h').write_text(''.join(h))
print('Compiled36 authored scenes into', (D/'campaign-scenes.bin').stat().st_size,'disc bytes; journal metadata generated. No unverified scene marked playable.')
