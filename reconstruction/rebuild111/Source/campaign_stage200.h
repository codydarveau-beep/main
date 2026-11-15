/* MIT. Chapter2 map contacts and physical evidence; no duplicated NPC VM/world. */
#ifndef MYRO_CAMPAIGN_STAGE200_H
#define MYRO_CAMPAIGN_STAGE200_H
#include "campaign_state200.h"
#include "campaign_actor_data200.h"
#include "chapter2_gates200.h"
typedef struct{unsigned source;float x,y;const char*name;}CampaignStageActor200;
typedef struct{unsigned cursor,map,count;float x,y,docX,docY;CampaignStageActor200 actor[4];unsigned recoveredFields197[9];}CampaignStageDefinition200;
#include "campaign_stage_data197.h"
typedef struct{Combat*player;NpcState55*state;const CampaignStageDefinition200*definition;unsigned active;}CampaignStage200;
static CampaignStage200 campaignStage200;
static int campaignStageModal200;
static void campaign_stage_bind200(CampaignStage200*r,Combat*g,NpcState55*state,int graphicsReady){r->player=g;r->state=state;r->active=0;r->definition=NULL;Campaign200 c;if(!graphicsReady||CAMPAIGN_ACTOR_COUNT200<7||!state||campaign_load200(state,&c)!=1||c.cursor<3||c.cursor>5)return;const CampaignStageDefinition200*d=campaignStages200+c.cursor-3;if(g->mapId!=d->map)return;r->definition=d;r->active=1;}
static int campaign_stage_reachable200(const Combat*g,float x,float y){return(!g->canAim||g->canAim(g->world,g->x,g->y,x,y))&&(!g->canMove||g->canMove(g->world,g->x,g->y,x,y));}
/*100..103=contacts,110=physical document. A stale stage never grants proof. */
static int campaign_stage_near200(const CampaignStage200*r){if(!r->active||!r->player||!r->definition||r->player->hp<=0)return-1;const Combat*g=r->player;const CampaignStageDefinition200*d=r->definition;Campaign200 c;if(g->mapId!=d->map||campaign_load200(r->state,&c)!=1||c.cursor!=d->cursor)return-1;int best=-1;float distance=20;for(unsigned i=d->cursor==5?2:0;i<d->count;i++){const CampaignStageActor200*a=d->actor+i;float near=combat_dist(g->x,g->y,a->x,a->y);if(near<distance&&campaign_stage_reachable200(g,a->x,a->y)){best=100+(int)i;distance=near;}}if(d->cursor<5){float near=combat_dist(g->x,g->y,d->docX,d->docY);if(near<distance&&campaign_stage_reachable200(g,d->docX,d->docY))best=110;}return best;}
/*1=open dialogue,2=evidence saved,-1=handled denial/error,0=no matching contact. */
static int campaign_stage_interact200(CampaignStage200*r,int who){if(who<100||campaign_stage_near200(r)!=who)return 0;Campaign200 c;if(campaign_load200(r->state,&c)!=1)return 0;if(who!=110)return 1;unsigned bit;if(c.cursor==3){if(c.checkpoint!=CHAPTER2_WITNESS_GATE200||(c.objectives&3)!=3){combat_message(r->player,"Hear both Payon accounts before comparing the old register.");return-1;}bit=2;}else if(c.cursor==4){if(c.checkpoint!=CHAPTER2_LEDGER_GATE200){combat_message(r->player,"Ask Maya and Veyr about examining the dispatch ledger first.");return-1;}bit=0;}else return 0;if(c.objectives&(1u<<bit)){combat_message(r->player,"You have recorded this comparison. Return to the group.");return-1;}if(!campaign_objective200(r->state,c.cursor,bit)){combat_message(r->player,"The comparison could not be saved. Please try again.");return-1;}combat_message(r->player,c.cursor==3?"The old register agrees with the family. Return to Judia.":"The dispatch ledger names Geffen. Return to Maya and Veyr.");return 2;}
#endif
