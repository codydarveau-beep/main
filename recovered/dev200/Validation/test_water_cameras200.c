#define MYRO_HOST 1
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <zlib.h>
#include "world_data.h"
#include "projection.h"
#include "water_mode190.h"
enum{NV097_SET_CULL_FACE_ENABLE,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_DEPTH_TEST_ENABLE,NV097_SET_DEPTH_MASK,NV097_SET_BLEND_ENABLE,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,NV097_SET_TRANSFORM_CONSTANT_LOAD=100,NV097_SET_TRANSFORM_CONSTANT=101,NV097_SET_BEGIN_END=102};
static uint64_t vertexHash=14695981039346656037ull;
static unsigned draws,vertices,primitive,textureWidth,currentMap;static int writes,blending,tests;static uint32_t commands[200];static float corners[6][5];
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(3);}
static void*gpu_alloc(unsigned n){void*p=calloc(1,n);assert(p);return p;}
static void MmFreeContiguousMemory(void*p){free(p);}
static void gpu_depth_state(int write){assert(!write);writes=write;tests=1;}
static void program(int n){assert(n==1);}
static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned format){assert(p&&pitch==w*4&&format==0x0001122a);assert((w==32&&h==4)||(w==128&&h==128)||(w==256&&h==256));textureWidth=w;}
static uint32_t*pb_begin(void){return commands;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned val){if(reg==NV097_SET_DEPTH_MASK)writes=val;if(reg==NV097_SET_BLEND_ENABLE)blending=val;if(reg==NV097_SET_DEPTH_TEST_ENABLE)tests=val;if(reg==NV097_SET_BEGIN_END&&val){assert(tests&&!writes&&blending);primitive=val;draws++;vertices=0;assert(val==(waterOriginal190?5u:6u));}return p;}
static void pb_push(uint32_t*p,unsigned reg,unsigned n){assert(reg==NV097_SET_TRANSFORM_CONSTANT&&n==16);(void)p;}
static void pb_end(uint32_t*p){(void)p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){float hashValues[5]={x,y,z,u,v};for(unsigned k=0;k<sizeof(hashValues);k++){vertexHash^=((unsigned char*)hashValues)[k];vertexHash*=1099511628211ull;}assert(isfinite(x)&&isfinite(y)&&isfinite(z));assert(u>=0&&u<=textureWidth&&v>=0&&v<=textureWidth);assert(vertices<6);corners[vertices][0]=x;corners[vertices][1]=y;corners[vertices][2]=z;corners[vertices][3]=u;corners[vertices][4]=v;vertices++;if(!waterOriginal190)assert(u==1&&v==1);return p;}
#include "water_draw.h"
static unsigned activeMap;
typedef struct{int water54;float waterline54;}DrawActor;
#include "water_actor54.h"
int main(void){unsigned allCurrent=0,allOriginal=0;for(unsigned mode=0;mode<2;mode++){waterOriginal190=mode;for(unsigned map=0;map<WORLD_MAP_COUNT;map++){activeMap=currentMap=map;waterTime190=7.25f;if(!waterMaps[map].count)continue;const unsigned short*r=waterRects[waterMaps[map].start];float x=(r[0]+r[2])*.5f,y=(r[1]+r[3])*.5f,z=waterMaps[map].z;water_prepare190(map);for(unsigned pose=0;pose<24;pose++){float m[16],before[16];world_camera(m,x,y,z,pose*.44879895f,.35f+.07f*(pose%6),.9f+.25f*(pose%5));memcpy(before,m,sizeof(m));unsigned old=draws;water_prepare_view190(m,map);water_draw(m,map);assert(!memcmp(before,m,sizeof(m)));assert(draws>old);if(mode)allOriginal+=draws-old;else allCurrent+=draws-old;assert(vertices==(mode?6u:4u));DrawActor a;water_actor_mark54(&a,m,x,y,z-20);assert(a.water54);float surface=mode?water_surface190(map,x,y,waterTime190,z):z;assert(fabsf(a.waterline54-(m[4]*x+m[5]*y+m[6]*surface+m[7]))<.001f);water_actor_mark54(&a,m,x,y,z+20);assert(!a.water54);}}}float off[16]={0};off[3]=off[7]=-1000000;waterOriginal190=1;unsigned beforeReads=waterReads190;water_prepare_view190(off,0);assert(!waterGpu190&&!waterFile190&&waterReads190==beforeReads);unsigned beforeDraws=draws;water_draw(off,0);assert(draws==beforeDraws);water_release190();free(waterTexture);printf("PASS actual renderer: all wet maps/four poses, %u unchanged CURRENT quads/%u ORIGINAL tiles; source UV bounds, depth/no-write alpha states, actor wave-line and dry bridge exclusion.\n",allCurrent,allOriginal);printf("VERTEXHASH %016llx\n",(unsigned long long)vertexHash);}
