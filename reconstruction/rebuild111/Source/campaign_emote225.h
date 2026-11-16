/* Original four-entry scene-emote ring. Presentation never writes quest state. */
#ifndef MYRO_CAMPAIGN_EMOTE225_H
#define MYRO_CAMPAIGN_EMOTE225_H
#include "campaign_scene200.h"
typedef struct{unsigned kind,id,map;float age,x,y;}CampaignEmoteEvent225;
typedef struct{CampaignEmoteEvent225 events[4];unsigned next,lastCursor,lastNode;}CampaignEmotes225;
typedef int(*CampaignEmotePosition225)(void*,const char*,float*,float*);
static CampaignEmotes225 campaignEmotes225={.lastCursor=~0u,.lastNode=~0u};
static void campaign_emote_reset225(void){memset(&campaignEmotes225,0,sizeof campaignEmotes225);campaignEmotes225.lastCursor=campaignEmotes225.lastNode=~0u;}
static void campaign_emote_update225(CampaignEmotes225*r,const Combat*g,float dt,int status,const NpcState55*state,Scene200*scene,CampaignEmotePosition225 position,void*context){
 if(!r||!g||!isfinite(dt)||dt<0)return;
 for(unsigned i=0;i<4;i++){CampaignEmoteEvent225*e=r->events+i;if(e->kind){e->age+=dt;if(e->map!=g->mapId||e->age>4)e->kind=0;}}
 if(status!=SC200_LINE){r->lastCursor=r->lastNode=~0u;return;}
 Campaign200 c;if(campaign_load200(state,&c)!=1)return;
 if(r->lastCursor==c.cursor&&r->lastNode==c.checkpoint)return;r->lastCursor=c.cursor;r->lastNode=c.checkpoint;
 if(!scene||!scene->data||!position)return;unsigned emotion=scene_emotion195(scene);if(!emotion)return;
 float x,y;if(!position(context,scene_text200(scene,0),&x,&y))return;
 r->events[r->next++%4]=(CampaignEmoteEvent225){1,emotion-1,g->mapId,0,x,y};
}
#endif
