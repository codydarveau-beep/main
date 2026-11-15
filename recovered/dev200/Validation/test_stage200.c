#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static int failStageAlloc;
static void*stage_alloc200(size_t n){return failStageAlloc?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 stage_alloc200
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_stage200.h"
static int blocked;
static int line(void*ctx,float x,float y,float nx,float ny){(void)ctx;(void)x;(void)y;(void)nx;(void)ny;return!blocked;}
static Combat g;static NpcState55 state;
static void start(unsigned cursor){npc_state_clear55(&state);combat_init(&g,0,0,line,NULL);g.canAim=line;g.mapId=cursor==3?12:132;g.hp=g.maxhp;g.zeny=12345;Campaign200 c={0};c.cursor=cursor;c.route=1;c.lineage=1;c.recruits=18;assert(campaign_store200(&state,&c));campaign_stage_bind200(&campaignStage200,&g,&state,1);assert(campaignStage200.active);}
int main(void){start(3);Campaign200 c;g.x=348;g.y=1004;assert(campaign_stage_near200(&campaignStage200)==100&&campaign_stage_interact200(&campaignStage200,100)==1);blocked=1;assert(campaign_stage_near200(&campaignStage200)==-1);blocked=0;g.hp=0;assert(campaign_stage_near200(&campaignStage200)==-1);g.hp=g.maxhp;g.x=364;g.y=1028;assert(campaign_stage_near200(&campaignStage200)==110&&campaign_stage_interact200(&campaignStage200,110)==-1);assert(campaign_load200(&state,&c)==1&&!c.objectives);c.checkpoint=CHAPTER2_WITNESS_GATE200;assert(campaign_store200(&state,&c));assert(campaign_stage_interact200(&campaignStage200,110)==-1);assert(campaign_objective200(&state,3,0)&&campaign_objective200(&state,3,1));unsigned revision=state.revision;assert(!campaign_stage_interact200(&campaignStage200,100)&&state.revision==revision);failStageAlloc=1;assert(campaign_stage_interact200(&campaignStage200,110)==-1&&state.revision==revision);failStageAlloc=0;assert(campaign_load200(&state,&c)==1&&c.objectives==3);assert(campaign_stage_interact200(&campaignStage200,110)==2&&campaign_load200(&state,&c)==1&&c.objectives==7);revision=state.revision;assert(campaign_stage_interact200(&campaignStage200,110)==-1&&state.revision==revision&&g.zeny==12345);g.mapId=11;assert(campaign_stage_near200(&campaignStage200)==-1&&!campaign_stage_interact200(&campaignStage200,110));
 start(4);g.x=564;g.y=364;assert(campaign_stage_near200(&campaignStage200)==110&&campaign_stage_interact200(&campaignStage200,110)==-1);assert(campaign_load200(&state,&c)==1&&!c.objectives);c.checkpoint=CHAPTER2_LEDGER_GATE200;assert(campaign_store200(&state,&c));assert(campaign_stage_interact200(&campaignStage200,110)==2&&campaign_load200(&state,&c)==1&&c.objectives==1);assert(g.zeny==12345);
 start(5);g.x=204;g.y=1132;assert(campaign_stage_near200(&campaignStage200)==103&&campaign_stage_interact200(&campaignStage200,103)==1);g.x=172;g.y=1100;assert(campaign_stage_near200(&campaignStage200)==-1);campaign_stage_bind200(&campaignStage200,&g,&state,0);assert(!campaignStage200.active);npc_state_clear55(&state);puts("PASS Chapter2 actual map contacts/documents: nearest reachable contact, stale map/death/blocked denial, assigned native testimony gates, allocation-failure retry, exactly-once physical register/ledger receipts, no Zeny/item grants and bounded inn contacts.");}
