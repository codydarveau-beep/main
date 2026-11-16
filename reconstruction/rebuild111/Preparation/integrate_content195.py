"""Install exact recovered art tables; retain story activation/scene wire gates."""
from pathlib import Path
import json,os,struct,re
R=Path(__file__).resolve().parent.parent;D=R/'Recovered195';d=json.loads((D/'content-recovery195.json').read_text());S=R/'Source'
uints=lambda row:','.join(str(v)+'u'for v in row)
quote=lambda s:json.dumps(s,ensure_ascii=True)
a=d['campaign.bin'];n=a['actorCount']
h='/* Released 1.10.0 actor catalog recovered from verified executable and pack. */\n#ifndef MYRO_CAMPAIGN_ACTOR_DATA200_H\n#define MYRO_CAMPAIGN_ACTOR_DATA200_H\n'
h+='#define CAMPAIGN_ACTOR_COUNT200 %du\n#define CAMPAIGN_ACTIONS_PER_ACTOR200 48u\n#include "campaign_release238.h"\n#define CAMPAIGN_FRAME_COUNT200 %du\n#define CAMPAIGN_ACTOR_BYTES200 %du\n'%(n,len(a['streams']),a['bytes'])
h+='static const struct{unsigned offset,packed,raw,crc;}campaignFrames200[]={\n'+''.join('{'+uints([t[k]for k in ['offset','packed','raw','crc']])+'},\n'for t in a['streams'])+'};\n'
h+='static const struct{unsigned first,count,ms;}campaignActions200[]={\n'+''.join('{'+uints(t)+'},\n'for t in a['actions'])+'};\n'
h+='static const float campaignContact200[%d][8][2]={\n'%n
for i in range(n):h+='{'+','.join('{'+repr(a['contacts'][i*16+j*2])+'f,'+repr(a['contacts'][i*16+j*2+1])+'f}'for j in range(8))+'},\n'
h+='};\n#endif\n';(S/'campaign_actor_data200.h').write_text(h)
p=S/'campaign_companions200.h';s=p.read_text();begin=s.index('static const CampaignCompanion200 campaignCompanions200[19]={');s=s[:begin]+'static const CampaignCompanion200 campaignCompanions200[19]={\n'+''.join('{'+quote(name)+','+str(job)+','+str(actor)+'},\n'for name,job,actor in d['roster']['rows'])+'};\n#endif\n';p.write_text(s)
a=d['npcfx.bin'];h='#ifndef MYRO_NPC_EFFECT_DATA172_H\n#define MYRO_NPC_EFFECT_DATA172_H\n/* Exact released frame/clip descriptors, including replaced and appended effects. */\n#define NPC_FX_BYTES172 %du\n'%a['bytes'];h+='typedef struct{unsigned offset,packed,raw,crc,x,y,w,h;}NpcFxFrame172;\nstatic const NpcFxFrame172 npcFxFrames172[]={\n'+''.join('{'+uints(t)+'},\n'for t in a['metadata'])+'};\n';h+='typedef struct{unsigned id,first,count,ms;float scale;unsigned variant,variants;}NpcFxClip172;\nstatic const NpcFxClip172 npcFxClips172[]={\n'+''.join('{'+uints(t[:4])+','+repr(t[4])+'f,'+uints(t[5:])+'},\n'for t in a['clips'])+'};\n#endif\n';(S/'npc_effect_data172.h').write_text(h)
a=d['portraits.bin'];h='/* Exact released original NPC portrait catalog. */\n#define NPC_PORTRAIT_RAW171 1048576u\n#define NPC_PORTRAIT_FILE_BYTES171 %du\n'%a['bytes'];h+='static const struct{const char*name;unsigned offset,packed,crc,width,height;}npcPortraits171[]={\n'+''.join('{'+quote(t[0])+','+uints(t[1:])+'},\n'for t in a['metadata'])+'};\n';(S/'npc_portrait_data171.h').write_text(h)
a=d['storyportraits.bin'];h='#ifndef MYRO_CAMPAIGN_PORTRAIT_DATA200_H\n#define MYRO_CAMPAIGN_PORTRAIT_DATA200_H\n/* Exact released speaker expressions. */\n#define CAMPAIGN_PORTRAIT_RAW200 262144u\n#define CAMPAIGN_PORTRAIT_FILE_BYTES200 %du\n'%a['bytes'];h+='static const struct{const char*name;unsigned expression,offset,packed,crc,rawCRC;}campaignPortraits200[]={\n'+''.join('{'+quote(t[0])+','+uints(t[1:])+'},\n'for t in a['metadata'])+'};\n#endif\n';(S/'campaign_portrait_data200.h').write_text(h)
# Scene header/reader compatibility is integrated separately with verified cue semantics.
for name in ['campaign.bin','npcfx.bin','portraits.bin','storyportraits.bin']:
 p=R/'XboxFiles'/name;assert p.is_symlink();p.unlink();p.symlink_to(D/name)
print('Installed released actor/roster/effect/portrait catalogs and four exact released packs. Runtime scope is controlled separately by campaign_release238.h.')

sceneHeader=(D/'chapter1_data200.h').read_text();sceneHeader=re.sub(r'^#define CAMPAIGN_RELEASE_SCENES193[^\n]+', '#include \"campaign_release238.h\"',sceneHeader,flags=re.M);(S/'chapter1_data200.h').write_text(sceneHeader)
p=R/'XboxFiles/chapter1.bin';assert p.is_symlink();p.unlink();p.symlink_to(D/'chapter1.bin')
