"""Restore retained guild semantics, with explicit naming adapters for current callers."""
from pathlib import Path
import re,json,struct
R=Path(__file__).resolve().parent.parent;S=R/'Source';retained=(R/'Retained196/guild194.h').read_text()
# Compare retained project data directly with independent released-XBE recovery.
pattern=r'\{\s*"([^"\n]+)",\s*"([^"\n]+)",\s*(\d+),(\d+),\{(\d+),(\d+)\},\{(\d+),(\d+)\}\s*\}'
rows=re.findall(pattern,retained);deployed=json.loads((R/'Preparation/Guild-Recovery194.json').read_text())['projects'];assert len(rows)==len(deployed)==12
for row,p in zip(rows,deployed):assert list(row[:2])==[p['title'],p['pitch']]and list(map(int,row[2:]))==[p['minimum'],p['requires'],*p['items'],*p['amounts']]
# Verify material selection against deployed machine instructions: sourceID and
# equipped field only; no invented bound-item exclusion in the retained loop.
xbe=(R.parent/'packet194/released-default.xbe').read_bytes();assert xbe.count(bytes.fromhex('397c9104750b8b4c2460837c911c007409'))==2
s=retained
for a,b in [('built','completed'),('decor','style'),('highscore','scores'),('name','title'),('chapter','minimum')]:s=re.sub(r'\b'+a+r'\b',b,s)
s=s.replace('/* MIT. Optional', '/* Retained implementation restored; member names adapted for existing callers. */\n/* MIT. Optional',1)
helpers='''
/* Compatibility names; retained transactions and invitation predicates above. */
static int guild_project_available194(const NpcState55*s,unsigned index){return guild_available194(s,index);}
static int guild_deliver194(NpcState55*s,Combat*g,unsigned index){return guild_build194(s,g,index);}
static int guild_style194(NpcState55*s,unsigned style){return guild_decor194(s,style);}
static unsigned guild_material_count194(const Combat*g,unsigned source){unsigned n=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(p->sourceID==source&&!p->equipped)n+=p->quantity;}return n;}
/* Original Alberta proximity/clear-path contract. The temporary room's board
 * coordinate remains explicit until the original room geometry is restored. */
static int guild_near194(const Combat*g){return g&&g->hp>0&&((g->mapId==132&&combat_dist(g->x,g->y,188,1116)<22&&(!g->canMove||g->canMove(g->world,g->x,g->y,188,1116)))||(g->mapId==494&&combat_dist(g->x,g->y,800,1440)<24&&(!g->canMove||g->canMove(g->world,g->x,g->y,800,1440))));}
'''
s=s.rsplit('#endif',1)[0]+helpers+'#endif\n';(S/'guild194.h').write_text(s)
# Restore original root rows 14=invitations,15=physical visit; retain journeys16.
p=S/'guild_ui194.h';s=p.read_text().replace('#include "guild_arcade194.h"','#include "guild_arcade194.h"\n#include "campaign_companions200.h"');s=s.replace('u->page==2?12:13;','u->page==2?12:u->page==8?14:13;');s=s.replace('u->page==5?9:0;', 'u->page==5?9:u->page==8?19:0;')
s=s.replace('else if(u->row==14){if(guildVisit194', 'else if(u->row==14){u->page=8;u->row=0;}\n  else if(u->row==15){if(guildVisit194').replace('  else if(u->row==15)g->utilityMenu=0;\n','')
s=s.replace(' if(u->page==5){u->journey', ''' if(u->page==8){Campaign200 c;if(campaign_load200(questPins65,&c)!=1){combat_message(g,"The guild roster could not be read.");return;}unsigned bit=1u<<u->row;
  combat_message(g,(c.recruits&bit)?"Already a member. Choose your active group in Companions.":guild_invite194(questPins65,u->row)?"Invitation accepted. Choose your active group in Companions.":"Meet this ally in the story first. No invitation was sent.");return;}
 if(u->page==5){u->journey''')
s=s.replace('u->page==3?6:9,first=', 'u->page==3?6:u->page==8?19:9,first=')
s=s.replace('static const char*styles[]={"Plain","Common room","Library","Workshop"};','static const char*styles[]={"Plain and practical","Cosy common room","Reading room","Workshop"};')
s=s.replace('"Visit the guild hall","Close noticeboard"','"Invite an introduced ally","Visit the guild hall"').replace('(row==14&&g->mapId==494)','(row==15&&g->mapId==494)')
s=s.replace('  else if(u->page==2)label=styles[row];','  else if(u->page==8){Campaign200 c;if(campaign_load200(questPins65,&c)!=1)return;label=(guild_met_mask194(c.cursor)&(1u<<row))?campaignCompanions200[row].name:"Not yet introduced";}\n  else if(u->page==2)label=styles[row];')
p.write_text(s)
(R/'Preparation/Guild-Reconciliation196.json').write_text(json.dumps(dict(retainedProjectDefinitionsMatchReleased=True,projectCount=12,wireMatchesReleased=True,materialPredicate='sourceID matches and unequipped; bound flag is not a deployed exclusion',restored=['complete retained guild core with member-name adapters','introduced-ally invitations','original root invitation/visit entries plus regional row','original furnishing labels','Alberta proximity and clear path'],unresolved=['original room geometry and furniture generator','complete original arcade engines','temporary interior noticeboard coordinate differs from original']),indent=2)+'\n')
print('Restored retained guild core, invitations and original menu entries; verified project data and inventory filter against released executable.')
