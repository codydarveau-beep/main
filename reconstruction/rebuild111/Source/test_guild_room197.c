/* Actual packed map, recovered furnishing generator and streaming/draw adapters.
 * GPU commands/allocations are host recorders, never a console playtest. */
#define main legacy_world_room197
#include "test_world43.c"
#undef main
#include "quest_journal65.h"
#include "campaign_admission_runtime194.h"
#include "guild_world194.h"
#include "../Validation/guild_prop_fixtures197.h"
#include "../Validation/guild_floor_fixtures197.h"
static unsigned resets197,drawVertices197,drawQuads197;
static void campaign_reset200(void){resets197++;}
static uint32_t commands197[4096];
enum{NV097_SET_DEPTH_TEST_ENABLE,NV097_SET_DEPTH_MASK,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_ALPHA_FUNC,NV097_SET_ALPHA_REF,NV097_SET_BEGIN_END};
static uint32_t*pb_begin(void){return commands197;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){(void)reg;(void)value;assert(p<commands197+4096);return p+1;}
static void pb_end(uint32_t*p){assert(p<=commands197+4096);}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&isfinite(u)&&isfinite(v));drawVertices197++;return p;}
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){(void)blend;assert(t&&w==256&&h==256&&pitch==512&&format==0x0001102a);}
static void gpu_depth_state(int on){assert(on==1);}
static void world_project(const float*m,float x,float y,float z,float*sx,float*sy){*sx=m[0]*x+m[1]*y+m[2]*z+m[3];*sy=m[4]*x+m[5]*y+m[6]*z+m[7];}
#define WORLD_SPRITE_BIAS .01f
static float sprite_upright_cached50(float z,float top,float base,float slope){return z+(base-top)*slope;}
static void ground_quad58(float x,float y,float w,float h,float top,float bottom,float u,float v,float uw,float vh){assert(isfinite(x)&&isfinite(y)&&w>0&&h>0&&isfinite(top)&&isfinite(bottom)&&u>=0&&v>=0&&u+uw<=256&&v+vh<=256);drawQuads197++;}
#include "guild_furnish_draw197.h"
#include "guild_cabinet_draw197.h"
static NpcState55 state197,quests197;static Combat game197,before197;
static int view_read197(void*ctx,unsigned at,unsigned char*out,unsigned bytes){FILE*f=ctx;return !fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;}
int main(void){quest_journal_bind65(&quests197,&state197);campaign_admission_install194();guildRoomCompleted194=guild_world_completed194;guildRoomStyle194=guild_world_style194;worldSceneRelease200=campaign_guild_release197;
 Campaign200 c={.cursor=36,.route=1,.lineage=1};strcpy(c.guild,"Original");assert(campaign_store200(&state197,&c));Guild194 hall={4095,4095,0,{0}};assert(guild_store194(&state197,&hall));assert(world_activate(494));combat_init(&game197,192,1408,world_can_move,NULL);game197.mapId=494;
 for(unsigned p=0;p<sizeof(guildPropFixtures197)/sizeof(*guildPropFixtures197);p++){const unsigned*v=guildPropFixtures197[p];hall.accepted=hall.completed=v[0];hall.style=v[1];assert(guild_store194(&state197,&hall));guild_floor_apply197();assert(guildPropCount197==v[2]);assert(crc32(0,(unsigned char*)guildProps197,guildPropCount197*sizeof(*guildProps197))==v[3]);unsigned crc=crc32(0,walk,gw*gh);if(crc!=guildFloorCRCs197[p]){fprintf(stderr,"Floor mismatch plan %u built %u decor %u actual %u expected %u\n",p,v[0],v[1],crc,guildFloorCRCs197[p]);abort();}assert(allowed(192,1408)&&allowed(128,1444));}
 hall.accepted=hall.completed=4095;hall.style=0;assert(guild_store194(&state197,&hall));guild_floor_apply197();before197=game197;guild_furnish_prepare197(&game197);unsigned baselineGPU=bytesNow;
 FILE*f=fopen(getenv("MYRO_GUILD_VIEWS197"),"rb");assert(f);unsigned char*frame=malloc(GUILD_VIEW_RAW197);assert(frame);
 for(unsigned game=0;game<6;game++)for(unsigned view=0;view<8;view++){assert(guild_view_decode197(game,view,view_read197,f,frame,GUILD_VIEW_RAW197));unsigned opaque=0,last=0;for(unsigned i=0;i<GUILD_VIEW_RAW197/2;i++){unsigned v=frame[2*i]|(unsigned)frame[2*i+1]<<8;if(v&0x8000){opaque++;last=i/64;assert(i%64>0&&i%64<63);}}assert(opaque>500&&last>=92&&last<=93);}
 free(frame);fclose(f);
 float matrix[16]={.1f,0,0,180,0,.05f,-.1f,70,0,0,-.001f,.5f};
 for(unsigned view=0;view<8;view++){float yaw=view*.785398163397f;assert(guild_view_direction197(yaw,0)==view);guild_cabinet_prepare197(&game197,yaw+1.57079632679f);assert(bytesNow==baselineGPU+131072);for(unsigned i=0;i<6;i++)assert(guildCabinetPose197[i]==view);unsigned bytes=bytesNow;guild_cabinet_prepare197(&game197,yaw+1.57079632679f);assert(bytesNow==bytes);guild_furnish_draw197(&game197,matrix);unsigned old=drawQuads197;guild_cabinet_draw197(&game197,matrix,1,0);assert(drawQuads197==old+6);}
 assert(guild_view_direction197(-.785398163397f,0)==7&&guild_view_direction197(6.28318530718f-.001f,0)==0&&guild_view_direction197(NAN,0)==0);assert(!memcmp(&game197,&before197,sizeof(game197)));
 world_release();assert(!allocated&&!bytesNow&&!guildOriginalFloor197&&!guildFurnishTexture197&&!guildFurnishMesh197&&!guildCabinetTexture197);npc_state_clear55(&state197);npc_state_clear55(&quests197);
 printf("PASS original guild floor/prop plans, complete model mesh, eight-view sprite decoding/camera/drawing, bounded cache and map cleanup. %u recorded vertices; %u quads. HOST ONLY.\n",drawVertices197,drawQuads197);return 0;}
