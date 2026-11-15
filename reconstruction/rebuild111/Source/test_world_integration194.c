/* Real packed collision/height loader; GPU allocation is a host recorder. */
#define main unused_legacy_world_fixture194
#include "test_world43.c"
#undef main
#include "quest_journal65.h"
#include "campaign_admission_runtime194.h"
#include "regional_world194.h"
#include "guild_world194.h"
static NpcState55 character,quests194;
static Combat player194,old194;
static void story194(unsigned cursor){Campaign200 c={0};c.cursor=cursor;if(cursor>1){c.route=1;c.lineage=1;}strcpy(c.guild,"Recovery");assert(campaign_store200(&character,&c));}
static int notice_path194(float sx,float sy,float tx,float ty){
 int startX=(int)(sx/8),startY=(int)(sy/8);unsigned queue[1681];unsigned char seen[1681]={0};unsigned head=0,tail=0;queue[tail++]=20*41+20;seen[20*41+20]=1;
 while(head<tail){unsigned at=queue[head++];int dx=(int)(at%41)-20,dy=(int)(at/41)-20;float x=(startX+dx)*8+4,y=(startY+dy)*8+4;
  if(combat_dist(x,y,tx,ty)<=12&&world_can_move(NULL,x,y,tx,ty))return 1;
  static const int xx[]={-1,1,0,0},yy[]={0,0,-1,1};
  for(unsigned k=0;k<4;k++){int nx=dx+xx[k],ny=dy+yy[k];if(nx< -20||nx>20||ny< -20||ny>20)continue;unsigned next=(unsigned)((ny+20)*41+nx+20);if(!seen[next]&&world_can_move(NULL,x,y,(startX+nx)*8+4,(startY+ny)*8+4)){seen[next]=1;queue[tail++]=next;}}
 }return 0;
}
int main(void){
 quest_journal_bind65(&quests194,&character);campaign_admission_install194();guildRoomCompleted194=guild_world_completed194;guildRoomStyle194=guild_world_style194;
 story194(36);Guild194 guild={4095,4095,0,{0}};assert(guild_store194(&character,&guild));CampaignRegions194 regions={0};regions.accepted=regions.unlocked=regions.completed=(1u<<0)|(1u<<1)|(1u<<2)|(1u<<7)|(1u<<8)|(1u<<10)|(1u<<11)|(1u<<12)|(1u<<13);assert(campaign_regions_store194(&character,&regions));
 assert(world_activate(132));combat_init(&player194,188,1116,world_can_move,NULL);player194.mapId=132;player194.zeny=30000;
 for(unsigned i=0;i<9;i++){
  const RegionalJourney194*p=regionalJourneys194+i;assert(world_activate(p->map));assert(allowed(p->x,p->y)&&allowed(p->noteX,p->noteY));assert(notice_path194(p->x,p->y,p->noteX,p->noteY));
  player194.mapId=p->map;player194.x=p->noteX;player194.y=p->noteY;assert(regional_near194(&character,&player194)==(int)i);
  assert(regional_world_return194(&player194,i));assert(player194.mapId==132&&player194.zeny==30000&&allowed(player194.x,player194.y));
 }
 /* Real road rejection happens before random arrival, activation and RNG. */
 assert(world_activate(16));WorldGate gate={0};int found=0;for(unsigned i=0;i<WORLD_GATE_COUNT;i++)if(worldGates[i].source==16&&worldGates[i].destination==17){gate=worldGates[i];found=1;break;}assert(found);
 player194.mapId=16;player194.x=gate.x;player194.y=gate.y;assert(npc_state_set_text55(&character,CAMPAIGN_KEY200,0,"bad",3));old194=player194;unsigned oldLoads=loads;world_travel(&player194);
 assert(player194.rng==old194.rng&&player194.zeny==old194.zeny&&player194.mapId==old194.mapId&&!memcmp(&player194.owned52,&old194.owned52,sizeof(player194.owned52))&&loads==oldLoads);
 /* Every project-room combination is bounded and actually walkable at entry. */
 story194(36);unsigned peak=0;
 for(unsigned mask=1;mask<64;mask+=2){
  guild.accepted=guild.completed=mask;guild.style=mask%4;assert(guild_store194(&character,&guild));activeMap=~0u;assert(world_activate(494));assert(allowed(800,1440)&&world_can_move(NULL,800,1440,800,900));
  assert(!!allowed(400,400)==!!(mask&2));assert(!!allowed(800,400)==!!(mask&4));assert(!!allowed(1280,400)==!!(mask&8));
  assert(gw==200&&gh==200&&mw==100&&mh==100&&nverts<=80000&&allocated==2);if(bytesNow>peak)peak=bytesNow;
 }
 player194.mapId=494;player194.x=800;player194.y=1440;assert(guild_world_visit194(&player194)&&player194.mapId==132&&allowed(player194.x,player194.y));
 assert(campaign_npc_admission194(&player194,495)&&campaign_npc_admission194(&player194,496));
 /* Retained career coach endpoints use the real packed maps and original
  * gate indices remain untouched. Pilgrimage access is never a story grant. */
 story194(0);for(unsigned i=0;i<8;i++)assert(!world_gate_enabled64(CAREER_GATE_START194+i));story194(1);
 for(unsigned i=0;i<8;i++){
  const WorldGate*g=worldGates+CAREER_GATE_START194+i;assert(world_activate(g->source));assert(allowed(g->x,g->y));assert(world_activate(g->destination));assert(allowed(g->destX,g->destY));
  assert(!!world_gate_enabled64(CAREER_GATE_START194+i)==(i<6));
 }
 assert(npc_state_set_number55(&character,CAREER_PILGRIMAGE_KEY194,0,1));assert(world_gate_enabled64(CAREER_GATE_START194+6)&&world_gate_enabled64(CAREER_GATE_START194+7));
 world_release();assert(!allocated&&!bytesNow);npc_state_clear55(&character);npc_state_clear55(&quests194);
 printf("PASS HOST actual world: all nine arrival-to-notice paths and free returns; denied road preserves RNG/resources before load; 32 separate guild-room combinations, return, no leaked recorded GPU resources (peak guild GPU allocation %u bytes); private absent maps denied. Not an Xbox RAM/FPS playtest.\n",peak);
}
