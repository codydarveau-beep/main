#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static int failAllocation198;
static void*alloc198(size_t n){return failAllocation198?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 alloc198
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_stage200.h"
#include "../Validation/stage_rules_fixtures198.h"
static Combat game;
static NpcState55 state;
static int blocked198(void*ctx,float x,float y,float tx,float ty){(void)ctx;(void)x;(void)y;(void)tx;(void)ty;return 0;}
int main(void){unsigned sampled[42]={0},writes=0;for(unsigned i=0;i<sizeof(stageFixtures198)/sizeof(*stageFixtures198);i++){
 const unsigned*f=stageFixtures198[i];const CampaignStageDefinition200*d=f[0]<9?campaignStages200+f[0]:campaignLaterStages197+f[0]-9;Campaign200 c={0};c.cursor=d->cursor;c.route=f[1];c.lineage=1;c.checkpoint=f[2];c.objectives=f[3];CampaignStageDecision198 r=campaign_stage_decide198(d,&c,(int)f[4]);assert(r.write==f[5]&&r.objectives==f[6]&&r.message==f[7]&&r.talk==f[8]);
 if(!r.write||sampled[f[0]])continue;sampled[f[0]]=1;assert(campaign_store200(&state,&c));game.mapId=d->map;game.hp=100;game.zeny=12345;campaign_stage_document198(d,f[4]-110,&game.x,&game.y);CampaignStage200 stage={&game,&state,d,1};assert(campaign_stage_near200(&stage)==(int)f[4]);unsigned revision=state.revision;
 game.canMove=blocked198;assert(campaign_stage_interact200(&stage,(int)f[4])==0&&state.revision==revision);game.canMove=NULL;
 failAllocation198=1;assert(campaign_stage_interact200(&stage,(int)f[4])==-1);failAllocation198=0;Campaign200 old;assert(campaign_load200(&state,&old)==1&&!memcmp(&c,&old,sizeof c)&&state.revision==revision&&game.zeny==12345);
 assert(campaign_stage_interact200(&stage,(int)f[4])==2);assert(campaign_load200(&state,&old)==1&&old.objectives==r.objectives&&old.cursor==c.cursor&&old.checkpoint==c.checkpoint&&old.route==c.route&&old.recruits==c.recruits&&game.zeny==12345);writes++;
 stage.active=0;revision=state.revision;assert(!campaign_stage_interact200(&stage,(int)f[4])&&state.revision==revision);
 }
 Campaign200 c={0};c.cursor=6;c.route=1;c.lineage=1;assert(campaign_store200(&state,&c));game.mapId=42;CampaignStage200 stage={0};campaign_stage_bind200(&stage,&game,&state,1);assert(!stage.active);npc_state_clear55(&state);printf("PASS authored interaction replay fixtures, %u physical evidence adapters, denied movement and save-allocation preservation; activation unchanged. HOST ONLY.\n",writes);}
