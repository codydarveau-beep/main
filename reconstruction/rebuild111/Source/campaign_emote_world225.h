/* Original speaker resolution: player, opening actors, staged actors, followers. */
#ifndef MYRO_CAMPAIGN_EMOTE_WORLD225_H
#define MYRO_CAMPAIGN_EMOTE_WORLD225_H
#include "campaign_emote225.h"
static int campaign_emote_position225(void*context,const char*name,float*x,float*y){
 const Combat*g=context;if(!strcmp(name,"Player")){if(g->hp<=0)return 0;*x=g->x;*y=g->y;return 1;}
 if(campaignRescue200.active){unsigned actor=~0u;if(!strcmp(name,"Nera"))actor=R200_NERA;else if(!strcmp(name,"Roan"))actor=R200_ROAN;else if(!strcmp(name,"Yuufa"))actor=R200_YUUFA;else if(!strcmp(name,"Driver")||!strcmp(name,"Hald"))actor=R200_DRIVER;if(actor!=~0u){rescue_position200(&campaignRescue200,actor,x,y);return 1;}}
 if(campaignStage200.active&&campaignStage200.definition){const CampaignStageDefinition200*d=campaignStage200.definition;for(unsigned i=0;i<d->count&&i<4;i++)if(!strcmp(name,d->actor[i].name)){*x=d->actor[i].x;*y=d->actor[i].y;return 1;}}
 for(unsigned i=0;i<campaignParty200.count&&i<3;i++){const CampaignFollower200*m=campaignParty200.members+i;if(m->id<19&&m->hp&&m->map==g->mapId&&!strcmp(name,campaignCompanions200[m->id].name)){*x=m->x;*y=m->y;return 1;}}
 return 0;
}
static void campaign_emote_tick225(Combat*g,float dt,int status,const NpcState55*state,Scene200*scene){campaign_emote_update225(&campaignEmotes225,g,dt,status,state,scene,campaign_emote_position225,g);}
#endif
