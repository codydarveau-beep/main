#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "world_data.h"
#include "npc_game55.h"
#include "native_admission194.h"
static Combat game,oldGame;
static NpcGame55 context,oldContext;
static NpcState55 state;
static NativeAdmissionCache194 cache;
static const char*admission(unsigned index){return native_admission_reason194(&cache,index);}
int main(void){
 combat_init(&game,1000,1000,NULL,NULL);context.player.game=&game;context.pendingTalk=context.ui=context.lobby=-1;
 Campaign200 story={0};story.cursor=1;assert(campaign_store200(&state,&story));native_admission_refresh194(&cache,&state,0);npcNativeAdmission194=admission;
 unsigned npc=NPC_RECORD_COUNT55;
 for(unsigned i=0;i<NPC_RECORD_COUNT55;i++){
  const NpcRecord55*n=npcRecords55+i;if((n->flags&2)||!n->program||n->map>=WORLD_MAP_COUNT)continue;
  if(npcProgramFiles55[n->program-1].init==UINT32_MAX||!npc_scene_available64(&context.scene,i)||!admission(i))continue;
  npc=i;break;
 }assert(npc<NPC_RECORD_COUNT55);unsigned entry=npcProgramFiles55[npcRecords55[npc].program-1].init;
 oldContext=context;oldGame=game;unsigned rev=state.revision;
 for(unsigned i=0;i<10;i++)assert(!npc_game_open55(&context,npc));
 assert(!memcmp(&context,&oldContext,sizeof(context))&&!memcmp(&game,&oldGame,sizeof(game))&&state.revision==rev);
 context.map=game.mapId=npcRecords55[npc].map;game.x=npcRecords55[npc].x;game.y=npcRecords55[npc].y;context.scene.flags[npc]|=N55_NPC_INIT_DONE;
 oldContext=context;oldGame=game;npc_game_touch55(&context);
 assert(!memcmp(&context,&oldContext,sizeof(context))&&!memcmp(&game,&oldGame,sizeof(game))&&state.revision==rev);
 context.scene.flags[npc]&=(unsigned char)~N55_NPC_INIT_DONE;
 assert(!npc_game_schedule55(&context,npc,entry,0,N55_EVENT_CALL|N55_EVENT_ATTACHED));assert(!context.events.count);
 assert(npc_game_schedule55(&context,npc,entry,0,N55_EVENT_INIT|N55_EVENT_ATTACHED));assert(context.events.count==1);npc_events_clear55(&context.events);
 assert(npc_game_schedule55(&context,npc,entry,0,N55_EVENT_INIT));assert(context.events.count==1);npc_events_clear55(&context.events);
 assert(npc_game_schedule55(&context,npc,entry,0,N55_EVENT_CALL));assert(context.events.count==1);npc_events_clear55(&context.events);
 assert(npc_scene_available64(&context.scene,npc)); /* Initialization predicate is deliberately unchanged. */
 story.cursor=36;story.route=1;story.lineage=1;assert(campaign_store200(&state,&story));CampaignRegions194 regions={0};regions.accepted=regions.unlocked=regions.completed=(1u<<17)-1;assert(campaign_regions_store194(&state,&regions));native_admission_refresh194(&cache,&state,0);
 assert(!admission(npc));assert(npc_game_open55(&context,npc)&&context.pendingTalk==(int)npc);
 npc_state_clear55(&state);printf("PASS HOST actual NPC open/scheduler: blocked record %u preserves pendingTalk, full character/context and quest revision; attached calls blocked, global/attached OnInit and unattached preparation preserved; unlocked native opening proceeds\n",npcRecords55[npc].id);
}
