#define _POSIX_C_SOURCE 200809L
#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){(void)s;_Exit(9);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*out=malloc(raw);unsigned long z=raw;assert(out&&uncompress(out,&z,p,packed)==Z_OK&&z==raw);return out;}
#include "sprites.h"
#include "campaign_rescue200.h"
#define MERCENARY_KIND180 (MOB_SPEC_COUNT+18)
#define MERCENARY_TEXTURE180 (RENDER_MOBS+24)
static void*entityTextures[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];static unsigned entityCapacity51[SPRITE_SLOT_COUNT],uploadedFrames[SPRITE_SLOT_COUNT],frees;
static void MmFreeContiguousMemory(void*p){assert(p);free(p);frees++;}
typedef struct {int slot,kind;unsigned frame;float x,y,depth,groundY;unsigned sourceFade50c;int water54;float waterline54,scale60;}DrawActor;
static float height_at(float x,float y){(void)x;(void)y;return 0;}
static void world_project(const float*m,float x,float y,float z,float*sx,float*sy){*sx=m[0]*x+m[1]*y+m[2]*z+m[3];*sy=m[4]*x+m[5]*y+m[6]*z+m[7];}
static int facing(float fx,float fy,float co,float si){float sx=co*fx+si*fy,sy=si*fx-co*fy;return((int)floorf(atan2f(-sx,sy)*4/3.14159265f+.5f)+8)%8;}
static int interiorRooms181;
static int rooms_point181(const int*r,float x,float y){(void)r;(void)x;(void)y;return 1;}
static void water_actor_mark54(DrawActor*a,const float*m,float x,float y,float z){(void)m;(void)x;(void)y;(void)z;a->water54=0;}
#define WORLD_SPRITE_BIAS .01f
#include "campaign_actor_render200.h"
int main(void){assert(!setenv("MYRO_CAMPAIGN_ACTOR_PATH","/workspace/myro/dev200/Campaign/actors.bin",1));unsigned checked=0;for(unsigned actor=0;actor<CAMPAIGN_ACTOR_COUNT200;actor++)for(unsigned action=0;action<CAMPAIGN_ACTIONS_PER_ACTOR200;action++){unsigned a=actor*CAMPAIGN_ACTIONS_PER_ACTOR200+action;for(unsigned i=0;i<campaignActions200[a].count;i++){unsigned frame=campaignActions200[a].first+i;campaignWanted200[0]=frame;campaign_actor_prepare200();SparseSprite*s=campaignSprites200;assert(s->raw&&s->frames==1&&s->anchorX==64&&s->anchorY>0&&s->anchorY<128);unsigned*d=s->directory;assert(d[0]>0&&d[1]>0&&d[0]+d[2]<128&&d[1]+d[3]<128);unsigned opaque=0;for(unsigned k=0;k<d[2]*d[3];k++)opaque+=(((const uint16_t*)s->pixels)[k]&0x8000)!=0;assert(opaque>150);checked++;}}assert(checked==CAMPAIGN_FRAME_COUNT200);campaign_actor_release200();static Combat g;combat_init(&g,1452,2820,NULL,NULL);g.mapId=0;g.time=11;campaignRescue200.active=0;unsigned selected[2]={COMP200_ROAN,COMP200_YUUFA};assert(campaign_follow_select200(&campaignParty200,18,selected,2));for(unsigned k=0;k<2;k++){CampaignFollower200*m=campaignParty200.members+k;m->initialized=m->hp=1;m->map=0;m->x=g.x+24*k;m->y=g.y;m->faceY=1;m->attackAt=10;m->hurtAt=-100;}CampaignFollower200*r=campaignParty200.members,*y=campaignParty200.members+1;r->attackUntil=11.5f;r->lastSkill=SKILL_BASH;y->castUntil=12;y->attackUntil=12.3f;y->lastSkill=SKILL_HOLY_LIGHT;float matrix[16]={0};matrix[0]=matrix[5]=1;matrix[3]=-1100;matrix[7]=-2600;DrawActor actors[8];int count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(count==2);unsigned dir=(unsigned)facing(0,1,1,0),ra=48+16+dir,ya=96+40+dir;assert(campaignWanted200[0]>=campaignActions200[ra].first&&campaignWanted200[0]<campaignActions200[ra].first+campaignActions200[ra].count);assert(campaignWanted200[1]>=campaignActions200[ya].first&&campaignWanted200[1]<campaignActions200[ya].first+campaignActions200[ya].count);campaign_actor_prepare200();r->hp=0;g.time=13;y->hurtAt=12.9f;count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(campaignWanted200[0]==campaignActions200[48+32+dir].first);assert(campaignWanted200[1]>=campaignActions200[96+24+dir].first&&campaignWanted200[1]<campaignActions200[96+24+dir].first+campaignActions200[96+24+dir].count);campaign_actor_prepare200();campaign_actor_release200();NpcState55 stageState={0};Campaign200 story={0};story.cursor=4;story.route=1;story.lineage=1;story.recruits=18;assert(campaign_store200(&stageState,&story));g.mapId=132;g.x=564;g.y=340;matrix[3]=-240;matrix[7]=-100;for(unsigned k=0;k<2;k++){campaignParty200.members[k].map=132;campaignParty200.members[k].x=g.x+k*24;campaignParty200.members[k].y=g.y;}campaign_stage_bind200(&campaignStage200,&g,&stageState,1);count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(count==4);for(unsigned k=0;k<4;k++)assert(actors[k].slot==CAMPAIGN_TEXTURE200+(int)k);campaign_actor_prepare200();assert(campaignPose200[0]>=campaignActions200[5*48].first&&campaignPose200[1]>=campaignActions200[6*48].first);story.cursor=5;assert(campaign_store200(&stageState,&story));g.x=188;g.y=1116;matrix[3]=100;matrix[7]=-900;for(unsigned k=0;k<2;k++){campaignParty200.members[k].x=g.x+k*24;campaignParty200.members[k].y=g.y;}campaign_stage_bind200(&campaignStage200,&g,&stageState,1);campaignStageModal200=0;count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(count==4);campaign_actor_prepare200();campaignStageModal200=1;count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(count==4);campaign_actor_prepare200();campaign_actor_release200();npc_state_clear55(&stageState);memset(&campaignStage200,0,sizeof(campaignStage200));campaignStageModal200=0;printf("PASS all%u genuine source actor poses through runtime sparse reader: CRC/size, complete crop margins, head/body pixels, per-actor action bounds and release.\n",checked);}
