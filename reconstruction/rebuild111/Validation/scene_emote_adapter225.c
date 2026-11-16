#define main legacy_emote_world225
#include "../Source/test_world43.c"
#undef main
#include "campaign_scene200.h"
#include "campaign_rescue200.h"
#include "campaign_stage200.h"
#include "campaign_battle200.h"
#include "campaign_emote_world225.h"
static Combat emoteGame225;static NpcState55 emoteState225;
void emote225(const unsigned char*data,unsigned bytes,unsigned cursor,unsigned node,unsigned map,unsigned status,unsigned kind,unsigned flags,float dt,unsigned paused,unsigned char*wire){
 Combat*g=&emoteGame225;memset(g,0,sizeof(*g));g->x=123.25f;g->y=234.5f;g->mapId=map;g->hp=flags&4?0:100;g->sp=77;g->zeny=12345;
 Campaign200 c={0};c.cursor=cursor;c.checkpoint=node;c.route=c.lineage=1;c.recruits=(1u<<19)-1;assert(campaign_store200(&emoteState225,&c));Scene200 scene={0};scene.state=&emoteState225;scene.data=(unsigned char*)data;scene.bytes=bytes;scene.count=scene_u16_200(data+6);scene.pool=16+scene.count*32;scene.cursor=cursor;const char*speaker=scene_text200(&scene,0);
 memset(&campaignRescue200,0,sizeof campaignRescue200);campaignRescue200.active=kind==1||kind==5;campaignRescue200.player=g;campaignRescue200.driverX=1501.25f;campaignRescue200.driverY=2803.5f;
 CampaignStageDefinition200 definition={0};definition.count=1;definition.actor[0]=(CampaignStageActor200){0,301.25f,407.5f,speaker};memset(&campaignStage200,0,sizeof campaignStage200);campaignStage200.active=kind==2||kind==4||kind==5;campaignStage200.definition=&definition;
 memset(&campaignParty200,0,sizeof campaignParty200);if(kind==3||kind==4||kind==6){for(unsigned id=0;id<19;id++)if(!strcmp(speaker,campaignCompanions200[id].name)){campaignParty200.count=1;CampaignFollower200*m=campaignParty200.members;m->id=id;m->hp=flags&2?0:100;m->map=map+(flags&1?1:0);m->x=501.5f;m->y=601.25f;break;}}
 CampaignEmotes225 state;assert(sizeof state==108);memcpy(&state,wire,108);unsigned revision=emoteState225.revision;if(!paused)campaign_emote_update225(&state,g,dt,(int)status,&emoteState225,&scene,campaign_emote_position225,g);memcpy(wire,&state,108);assert(emoteState225.revision==revision&&g->sp==77&&g->zeny==12345);npc_state_clear55(&emoteState225);
}
