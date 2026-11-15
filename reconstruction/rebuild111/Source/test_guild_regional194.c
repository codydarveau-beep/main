#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static int failStateAllocation;
static void*state_alloc(size_t n){return failStateAllocation?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 state_alloc
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "world_data.h"
#include "npc_world55.h"
#include "career_warp194.h"
#include "campaign_access194.h"
static int failBagAllocation;
static void*bag_alloc(size_t n){return failBagAllocation?NULL:malloc(n);}
#define malloc bag_alloc
#include "guild194.h"
#include "regional194.h"
#undef malloc
#include "../Validation/released_guild_fixture194.h"
static Combat game,oldGame;
static NpcState55 state;
static void story(unsigned cursor){Campaign200 c={0};c.cursor=cursor;c.route=1;c.lineage=1;strcpy(c.guild,"Recovery");assert(campaign_store200(&state,&c));}
static unsigned count(unsigned source){return guild_material_count194(&game,source);}
static void supplies(const RegionalJourney194*p){for(unsigned k=0;k<2;k++)assert(owned_add52(&game.owned52,0,p->item[k],p->amount[k],item_rule52)==OWNED_OK52);}
static void roundtrip(void){unsigned char*wire=malloc(NPC_STATE_FILE55);assert(wire&&npc_state_encode55(&state,wire,NPC_STATE_FILE55));unsigned n=npc_state_wire_bytes55(&state);NpcState55 next={0};assert(npc_state_decode55(&next,wire,n));free(wire);npc_state_clear55(&state);state=next;}
int main(void){
 combat_init(&game,188,1116,NULL,NULL);game.level=99;game.zeny=20000;game.mapId=132;story(36);
 Guild194 g={4095,4095,3,{10,20,30,40,50,60}},restored;
 assert(npc_state_set_text55(&state,GUILD_KEY194,0,releasedGuildFixture194,112));assert(guild_load194(&state,&restored)==1&&!memcmp(&g,&restored,sizeof(g)));
 assert(guild_store194(&state,&g));const NpcVariable55*record=npc_state_get55(&state,GUILD_KEY194,0);assert(record&&record->length==112&&!memcmp(record->text,releasedGuildFixture194,112));
 roundtrip();assert(guild_load194(&state,&restored)==1&&!memcmp(&g,&restored,sizeof(g)));
 for(unsigned i=0;i<6;i++){assert(guild_score194(&state,i,100+i));}assert(guild_load194(&state,&restored)==1&&restored.completed==4095&&restored.style==3);
 assert(!regional_available194(&state,3)&&!regional_available194(&state,4));
 unsigned order[9]={0,1,2,5,3,4,6,7,8};
 for(unsigned k=0;k<9;k++){
  unsigned i=order[k];const RegionalJourney194*p=regionalJourneys194+i;
  story(campaignRegionMinimum194[p->region-1]-1);assert(!regional_accept194(&state,i));story(36);
  if(p->region==8||p->region==9){CampaignRegions194 r;assert(campaign_regions_load194(&state,&r)&&r.completed&(1u<<10));}
  assert(regional_accept194(&state,i));oldGame=game;unsigned rev=state.revision;
  assert(!regional_deliver194(&state,&game,i)&&state.revision==rev&&!memcmp(&game,&oldGame,sizeof(game)));
  supplies(p);oldGame=game;rev=state.revision;failBagAllocation=1;
  assert(!regional_deliver194(&state,&game,i)&&state.revision==rev&&!memcmp(&game,&oldGame,sizeof(game)));failBagAllocation=0;
  unsigned before[2]={count(p->item[0]),count(p->item[1])};assert(regional_deliver194(&state,&game,i));
  for(unsigned j=0;j<2;j++)assert(count(p->item[j])==before[j]-p->amount[j]);assert(game.zeny==20000);
  assert(!regional_deliver194(&state,&game,i));game.mapId=p->map;game.x=p->noteX;game.y=p->noteY;
  assert(regional_near194(&state,&game)==(int)i);oldGame=game;rev=state.revision;failBagAllocation=1;
  assert(!regional_collect194(&state,&game,i)&&state.revision==rev&&!memcmp(&game,&oldGame,sizeof(game)));failBagAllocation=0;
  assert(regional_collect194(&state,&game,i));assert(!regional_collect194(&state,&game,i));
  assert(regional_near194(&state,&game)==(int)i);roundtrip();assert(regional_near194(&state,&game)==(int)i);
  game.mapId=132;game.x=188;game.y=1116;
 }
 assert(guild_load194(&state,&restored)==1&&restored.completed==4095&&restored.scores[5]==105);
 /* A real native pilgrimage savepoint rolls back home if its durable receipt
  * cannot grow the sparse state, then survives native temporary-flag cleanup. */
 story(1);assert(npc_state_set_number55(&state,npc_variable_key55("job_acolyte_q",0),0,3));
 while(state.count<state.capacity)assert(npc_state_set_number55(&state,UINT64_C(100000)+state.count,0,1));
 NpcWorld55 world={&game,mapNames,mapWidth43,mapHeight43,MYRO_MAP_COUNT43};NpcMachine55 machine={0};NpcValue55 out,args[]={npc_vm_string55("moc_fild07"),npc_vm_number55(35),npc_vm_number55(355)};
 WorldPosition home=game.home;unsigned rev=state.revision;failStateAllocation=1;
 assert(npc_career_world194(&world,&machine,1,3821,&state,"savepoint",args,3,&out)==N55_ERROR);
 assert(!memcmp(&home,&game.home,sizeof(home))&&state.revision==rev);failStateAllocation=0;
 assert(npc_career_world194(&world,&machine,1,3821,&state,"savepoint",args,3,&out)==N55_READY&&game.home.map==108);
 assert(npc_state_set_number55(&state,npc_variable_key55("job_acolyte_q",0),0,0));roundtrip();assert(campaign_access194(&state,108,0)==ACCESS_OPEN194&&campaign_access194(&state,127,0)==ACCESS_STORY194);
 const NpcVariable55*v=npc_state_get55(&state,GUILD_KEY194,0);char damaged[113];memcpy(damaged,v->text,112);damaged[0]='0';damaged[112]=0;assert(npc_state_set_text55(&state,GUILD_KEY194,0,damaged,112));assert(guild_load194(&state,&restored)==-1);
 npc_state_clear55(&state);puts("PASS HOST: released guild wire roundtrip and six score slots preserved; nine dispatches, prerequisites, material counters, failed-ledger atomicity, one-time rewards, completed notices and reload; corruption fails closed");
}
