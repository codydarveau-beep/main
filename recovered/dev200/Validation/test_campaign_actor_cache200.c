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
#define MYRO_CAMPAIGN_ACTOR_DATA200_H
#define CAMPAIGN_ACTOR_COUNT200 8u
#define CAMPAIGN_ACTIONS_PER_ACTOR200 16u
#define CAMPAIGN_OPENING_READY200 1u
#define CAMPAIGN_FRAME_COUNT200 128u
static const float campaignContact200[8][8][2]={{{0}}};
static unsigned fixtureBytes;
#define CAMPAIGN_ACTOR_BYTES200 fixtureBytes
static struct{unsigned offset,packed,raw,crc;}campaignFrames200[128];
static struct{unsigned first,count,ms;}campaignActions200[128];
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
static const char*path="/workspace/myro/dev200/Validation/campaign-actor-fixture200.bin";
int main(void){FILE*f=fopen(path,"wb");assert(f);for(unsigned i=0;i<128;i++){unsigned char raw[548]={0};unsigned header[8]={128,128,1,40,1,64,90,0x8000000c};memcpy(raw,header,32);for(unsigned action=0;action<40;action++){unsigned row[3]={0,1,100};memcpy(raw+32+action*12,row,12);}unsigned crop[5]={60,80,2,3,0};memcpy(raw+516,crop,20);for(unsigned j=0;j<6;j++){uint16_t c=0x8000|((i+1)<<4);memcpy(raw+536+j*2,&c,2);}unsigned char packed[1024];unsigned long n=sizeof(packed);assert(compress(packed,&n,raw,sizeof(raw))==Z_OK);campaignFrames200[i].offset=(unsigned)ftell(f);campaignFrames200[i].packed=(unsigned)n;campaignFrames200[i].raw=sizeof(raw);campaignFrames200[i].crc=crc32(0,packed,n);assert(fwrite(packed,1,n,f)==n);campaignActions200[i].first=i;campaignActions200[i].count=1;campaignActions200[i].ms=100;}fixtureBytes=(unsigned)ftell(f);fclose(f);assert(!setenv("MYRO_CAMPAIGN_ACTOR_PATH",path,1));assert(campaign_art_ready200());static Combat g;combat_init(&g,1452,2820,NULL,NULL);campaignRescue200.active=1;campaignRescue200.driverX=1468;campaignRescue200.driverY=2780;float matrix[16]={0};matrix[0]=matrix[5]=1;matrix[3]=-1100;matrix[7]=-2600;DrawActor actors[8];
 for(unsigned yaw=0;yaw<8;yaw++){int count=0;float a=yaw*.7853981634f;campaign_actor_collect200(&g,matrix,cosf(a),sinf(a),3,actors,&count);assert(count==4);campaign_actor_prepare200();for(unsigned i=0;i<4;i++){assert(campaignSprites200[i].raw&&campaignPose200[i]==campaignWanted200[i]);assert(actors[i].slot==CAMPAIGN_TEXTURE200+(int)i&&actors[i].slot<SPRITE_SLOT_COUNT);unsigned char*p=campaignSprites200[i].raw;campaign_actor_prepare200();assert(campaignSprites200[i].raw==p);}}
 campaignRescue200.escort=1;int count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);campaign_actor_prepare200();assert(campaignPose200[3]>=3*16+8);for(unsigned i=0;i<4;i++)entityTextures[CAMPAIGN_TEXTURE200+i]=malloc(16);matrix[3]=1000000;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);campaign_actor_prepare200();assert(frees==4);for(unsigned i=0;i<4;i++)assert(!campaignSprites200[i].raw&&!entityTextures[CAMPAIGN_TEXTURE200+i]);campaignRescue200.active=0;unsigned selected[2]={COMP200_ROAN,COMP200_YUUFA};assert(campaign_follow_select200(&campaignParty200,18,selected,2));for(unsigned k=0;k<2;k++){campaignParty200.members[k].map=g.mapId;campaignParty200.members[k].x=g.x+k*24;campaignParty200.members[k].y=g.y;campaignParty200.members[k].faceY=1;campaignParty200.members[k].moving=1;}matrix[3]=-1100;count=0;campaign_actor_collect200(&g,matrix,1,0,3,actors,&count);assert(count==2&&actors[0].slot==CAMPAIGN_TEXTURE200&&actors[1].slot==CAMPAIGN_TEXTURE200+1);campaign_actor_prepare200();assert(campaignSprites200[0].raw&&campaignSprites200[1].raw&&!campaignSprites200[2].raw&&!campaignSprites200[3].raw);assert(campaignPose200[0]>=16+8&&campaignPose200[1]>=32+8);campaign_actor_release200();count=0;campaign_actor_submit200(&g,matrix,1,0,3,0,7,g.x,g.y,0,1,0,NULL,actors,&count);assert(count==1&&actors[0].slot==CAMPAIGN_TEXTURE200&&campaignWanted200[0]>=112&&campaignWanted200[0]<120);campaign_actor_prepare200();assert(campaignSprites200[0].raw&&campaignPose200[0]>=112);campaign_actor_submit200(&g,matrix,1,0,3,4,7,g.x,g.y,0,1,0,NULL,actors,&count);campaign_actor_submit200(&g,matrix,1,0,3,1,8,g.x,g.y,0,1,0,NULL,actors,&count);assert(count==1);campaign_actor_release200();campaignWanted200[0]=0;f=fopen(path,"r+b");assert(f);fputc(1,f);fclose(f);pid_t pid=fork();assert(pid>=0);if(!pid){campaign_actor_prepare200();_Exit(0);}int status;waitpid(pid,&status,0);assert(WIFEXITED(status)&&WEXITSTATUS(status)==9);campaign_actor_release200();puts("PASS actual campaign pose reader:4 actors/8 camera directions, stable reuse,driver walk action,all actor slots bounded,offscreen CPU/GPU release and corrupt compressed pose rejection.");}
