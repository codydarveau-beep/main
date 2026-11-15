/* MIT. Exercise actual water renderer with recorded NV2A state/vertices. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include "world_data.h"
#include "projection.h"
enum {NV097_SET_CULL_FACE_ENABLE,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_DEPTH_TEST_ENABLE,NV097_SET_DEPTH_MASK,NV097_SET_BLEND_ENABLE,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,NV097_SET_TRANSFORM_CONSTANT_LOAD=100,NV097_SET_TRANSFORM_CONSTANT=101,NV097_SET_BEGIN_END=102};
static unsigned allocations,draws,vertices;static int writes,blending,tests;static float actual[16];static uint32_t commands[200];
static void*gpu_alloc(unsigned n){assert(n==512);allocations++;return calloc(1,n);}
static void gpu_depth_state(int write){assert(!write);writes=write;tests=1;}
static void program(int n){assert(n==1);}
static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned format){assert(p&&w==32&&h==4&&pitch==128&&format==0x0001122a);}
static uint32_t*pb_begin(void){return commands;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned val){if(reg==NV097_SET_DEPTH_MASK)writes=val;if(reg==NV097_SET_BLEND_ENABLE)blending=val;if(reg==NV097_SET_DEPTH_TEST_ENABLE)tests=val;if(reg==NV097_SET_BEGIN_END&&val){assert(val==6&&tests&&!writes&&blending);draws++;}return p;}
static void pb_push(uint32_t*p,unsigned reg,unsigned n){assert(reg==NV097_SET_TRANSFORM_CONSTANT&&n==16);(void)p;}
static void pb_end(uint32_t*p){(void)p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&u==1&&v==1);vertices++;return p;}
#include "water_draw.h"
int main(void){float camera[16];for(unsigned map=0;map<WORLD_MAP_COUNT;map++){unsigned before=draws;world_camera(camera,mapWidths[map]*8,mapHeights[map]*8,0,.3f,.8f,1);memcpy(actual,camera,sizeof(actual));water_draw(camera,map);assert(vertices==draws*4);assert(draws-before<=waterMaps[map].count);assert(!memcmp(actual,camera,sizeof(actual)));for(unsigned i=0;i<waterMaps[map].count;i++){const unsigned short*r=waterRects[waterMaps[map].start+i];assert(r[0]<r[2]&&r[1]<r[3]&&r[2]<=mapWidths[map]*16&&r[3]<=mapHeights[map]*16);} }assert(allocations==1&&draws>0);unsigned before=draws;water_draw(camera,WORLD_MAP_COUNT);assert(draws==before);free(waterTexture);puts("PASS actual water renderer: bounded source rectangles, visible quad submission, one persistent 4KiB page, alpha blend, depth test/no depth writes, no camera mutation, empty/invalid map handling");}
