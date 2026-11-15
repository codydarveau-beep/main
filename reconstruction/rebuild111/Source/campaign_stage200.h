/* MIT. Chapter2 map contacts and physical evidence; no duplicated NPC VM/world. */
#ifndef MYRO_CAMPAIGN_STAGE200_H
#define MYRO_CAMPAIGN_STAGE200_H
#include "campaign_state200.h"
#include "campaign_actor_data200.h"
#include "chapter2_gates200.h"
#include "chapter1_data200.h"
typedef struct{unsigned source;float x,y;const char*name;}CampaignStageActor200;
typedef struct{unsigned cursor,map,count;float x,y,docX,docY;CampaignStageActor200 actor[4];unsigned recoveredFields197[9];}CampaignStageDefinition200;
#include "campaign_stage_data197.h"
#include "campaign_stage_rules198.h"
typedef struct{Combat*player;NpcState55*state;const CampaignStageDefinition200*definition;unsigned active;}CampaignStage200;
static CampaignStage200 campaignStage200;
static int campaignStageModal200;
static void campaign_stage_bind_bounded200(CampaignStage200*r,Combat*g,NpcState55*state,int graphicsReady,unsigned ceiling){r->player=g;r->state=state;r->active=0;r->definition=NULL;Campaign200 c;if(!graphicsReady||CAMPAIGN_ACTOR_COUNT200<7||!state||ceiling>36||campaign_load200(state,&c)!=1||c.cursor<3||c.cursor>=ceiling)return;const CampaignStageDefinition200*d=campaign_stage_select198(c.cursor,g->mapId,c.objectives);if(!d)return;r->definition=d;r->active=1;}
/* Retain the release ceiling while restoring all verified early scene staging. */
static void campaign_stage_bind200(CampaignStage200*r,Combat*g,NpcState55*state,int graphicsReady){campaign_stage_bind_bounded200(r,g,state,graphicsReady,CAMPAIGN_RELEASE_SCENES193);}
static int campaign_stage_reachable200(const Combat*g,float x,float y){return(!g->canAim||g->canAim(g->world,g->x,g->y,x,y))&&(!g->canMove||g->canMove(g->world,g->x,g->y,x,y));}
/* Lead contact and independently positioned physical evidence. A stale stage
 * never grants proof; prepared later rules do not expand the activation guard. */
static int campaign_stage_near200(const CampaignStage200*r){
 if(!r->active||!r->player||!r->definition||r->player->hp<=0)return-1;
 const Combat*g=r->player;const CampaignStageDefinition200*d=r->definition;Campaign200 c;
 if(g->mapId!=d->map||campaign_load200(r->state,&c)!=1||c.cursor!=d->cursor)return-1;
 int best=-1;float distance=20;unsigned lead=campaign_stage_lead198(d);
 if(lead<d->count){const CampaignStageActor200*a=d->actor+lead;float near=combat_dist(g->x,g->y,a->x,a->y);if(near<distance&&campaign_stage_reachable200(g,a->x,a->y)){best=100+(int)lead;distance=near;}}
 unsigned documents=d->cursor<5?1:d->cursor>=6?d->recoveredFields197[0]:0;
 for(unsigned i=0;i<documents;i++){float x,y;campaign_stage_document198(d,i,&x,&y);float near=combat_dist(g->x,g->y,x,y);if(near<distance&&campaign_stage_reachable200(g,x,y)){best=110+(int)i;distance=near;}}
 return best;
}
/*1=open dialogue,2=evidence saved,-1=handled denial/error,0=no matching contact. */
static int campaign_stage_interact200(CampaignStage200*r,int who){
 if(who<100||campaign_stage_near200(r)!=who)return 0;Campaign200 c;if(campaign_load200(r->state,&c)!=1)return 0;
 CampaignStageDecision198 decision=campaign_stage_decide198(r->definition,&c,who);
 if(decision.talk)return 1;
 if(decision.write){c.objectives=decision.objectives;if(!campaign_store200(r->state,&c)){combat_message(r->player,"The comparison could not be saved. Please try again.");return-1;}}
 if(decision.message)combat_message(r->player,"%s",campaign_stage_text198(decision.message));
 return decision.write?2:decision.message?-1:0;
}
#endif
