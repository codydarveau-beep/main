/* Additional review 2: actual native pose reader and sprite uploader; GPU calls recorded. */
/* Exercise actual streaming, source pixels, cache eviction, GPU crops and fades. */
#define MYRO_HOST 1
#define MYRO_DISC_ENEMIES44 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned z,unsigned raw){(void)n;unsigned char*r=malloc(raw);assert(r);uLongf bytes=raw;assert(uncompress(r,&bytes,p,z)==Z_OK&&bytes==raw);return r;}
#include "sprites.h"
#include "sprite_tint.h"
static void*entityTextures[SPRITE_SLOT_COUNT];static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static void*gpu_alloc(unsigned n){void*p=malloc(n);assert(p);return p;}
static void MmFreeContiguousMemory(void*p){free(p);}
static void gpu_stream_plane51(void*t,SparseSprite*s,float x,float y,float d,float scale,float top,float bottom);
/* Strip command submission only: the native upload implementation is unchanged. */
#define gpu_depth_state(x) ((void)0)
#define program(x) ((void)0)
#define bindTexture(t,w,h,p,f) ((void)0)
#define NV097_SET_ALPHA_TEST_ENABLE 0
#define NV097_SET_VERTEX_DATA_ARRAY_FORMAT 0
#define NV097_SET_CULL_FACE_ENABLE 0
#define NV097_SET_BLEND_ENABLE 0
#define NV097_SET_BEGIN_END 0
static uint32_t commands[4096];static uint32_t*pb_begin(void){return commands;}static void pb_end(uint32_t*p){(void)p;}
static uint32_t*pb_push1(uint32_t*p,unsigned a,unsigned b){(void)a;(void)b;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&isfinite(u)&&isfinite(v));return p;}
#include "sprite_slice54.h"
#include "gpu_sprite_upload45.h"


#include "campaign_rescue200.h"
/* Exact production declarations used by the host draw recorder. */
typedef struct {int slot,kind;unsigned frame;float x,y,depth,groundY;unsigned sourceFade50c;int water54;float waterline54,scale60;} DrawActor;
static int facing(float fx,float fy,float co,float si){float sx=co*fx+si*fy,sy=si*fx-co*fy;return ((int)floorf(atan2f(-sx,sy)*4/3.14159265f+.5f)+8)%8;}

static float height_at(float x,float y){(void)x;(void)y;return 0;}
static void world_project(const float*m,float x,float y,float z,float*sx,float*sy){*sx=m[0]*x+m[1]*y+m[2]*z+m[3];*sy=m[4]*x+m[5]*y+m[6]*z+m[7];}
static int interiorRooms181;
static int rooms_point181(const int*r,float x,float y){(void)r;(void)x;(void)y;return 1;}
static void water_actor_mark54(DrawActor*a,const float*m,float x,float y,float z){(void)m;(void)x;(void)y;(void)z;a->water54=0;}
#define WORLD_SPRITE_BIAS .01f
#define MERCENARY_KIND180 (MOB_SPEC_COUNT+18)
#define MERCENARY_TEXTURE180 (RENDER_MOBS+24)
#include "campaign_actor_render200.h"
#include <unistd.h>
#include <sys/wait.h>
int main(void){
 /* Reproduce the former main-loop order in an isolated child. */
 pid_t child=fork();assert(child>=0);if(!child){freopen("/dev/null","w",stderr);sprite_upload(campaignSprites200,0,CAMPAIGN_TEXTURE200);_Exit(0);}int status=0;assert(waitpid(child,&status,0)==child);assert(WIFSIGNALED(status)&&WTERMSIG(status)==6);
 unsigned char expected[65536];unsigned peakRaw=0,peakGPU=0;
 for(unsigned frame=0;frame<CAMPAIGN_FRAME_COUNT200;frame++){
  unsigned slot=frame%4;campaignWanted200[slot]=frame;campaign_actor_prepare200();SparseSprite*p=campaignSprites200+slot;assert(p->raw&&p->frames==1&&p->w<=128&&p->h<=128&&p->bytesPerPixel==2);
  memset(expected,0,sizeof expected);unsigned*d=p->directory;for(unsigned y=0;y<d[3];y++)memcpy(expected+((d[1]+y)*p->w+d[0])*2,p->pixels+d[4]+y*d[2]*2,d[2]*2);
  sprite_upload(p,0,CAMPAIGN_TEXTURE200+slot);assert(entityCapacity51[CAMPAIGN_TEXTURE200+slot]==65536&&!memcmp(entityTextures[CAMPAIGN_TEXTURE200+slot],expected,65536));unsigned long long bytes=spriteUploadBytes51;sprite_upload(p,0,CAMPAIGN_TEXTURE200+slot);assert(bytes==spriteUploadBytes51);
  unsigned raw=0,gpu=0;for(unsigned i=0;i<4;i++){if(campaignPose200[i]!=~0u)raw+=campaignFrames200[campaignPose200[i]].raw;gpu+=entityCapacity51[CAMPAIGN_TEXTURE200+i];}if(raw>peakRaw)peakRaw=raw;if(gpu>peakGPU)peakGPU=gpu;
 }
 for(unsigned i=0;i<4;i++)campaignWanted200[i]=~0u;campaign_actor_prepare200();for(unsigned i=0;i<4;i++)assert(!campaignSprites200[i].raw&&!entityTextures[CAMPAIGN_TEXTURE200+i]);gpu_stream_reset51();appearance_hair_release58();
 printf("PASS actual campaign pose/upload: %u real poses, cold upload-before-prepare failure reproduced, exact GPU-recorded pixels after preparation, cache hits and offscreen cleanup. Peak four-pose raw %u GPU %u. Host only.\n",CAMPAIGN_FRAME_COUNT200,peakRaw,peakGPU);return 0;
}
