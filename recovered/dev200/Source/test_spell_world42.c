/* MIT. Exercise actual world geometry submission with bounded pbkit recorder. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "projection.h"
#include "art_visual39.h"
#include "skin_colors.h"
#define SKIN_PALETTE_X 0
#define SKIN_PALETTE_Y 256
#define SKIN_H 512
#include "hud_palette.h"
enum{NV097_SET_VERTEX_DATA_ARRAY_FORMAT=1,NV097_SET_CULL_FACE_ENABLE=100,NV097_SET_DEPTH_TEST_ENABLE,NV097_SET_DEPTH_MASK,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_BLEND_ENABLE,NV097_SET_BLEND_FUNC_SFACTOR,NV097_SET_BLEND_FUNC_DFACTOR,NV097_SET_BEGIN_END};
static unsigned gw=512,gh=512,quadCount,vertexCount,peak;static int art39Preview=-1;static float art39PreviewAt;static void*skinTexture;static uint32_t cmd[128];
static uint32_t*pb_begin(void){return cmd;}
static uint32_t*pb_push1(uint32_t*p,unsigned m,unsigned v){(void)m;(void)v;assert(p+2<=cmd+128);return p+2;}
static void pb_end(uint32_t*p){assert(p<=cmd+128);if((unsigned)(p-cmd)>peak)peak=p-cmd;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&u>=0&&u<512&&v>=256&&v<264);assert(p+8<=cmd+128);vertexCount++;if(!(vertexCount%4))quadCount++;return p+8;}
static void gpu_depth_state(int write){assert(write==0);}
static void program(int id){assert(id==0);}
static void bindTexture(void*t,int w,int h,int pitch,int fmt){(void)t;assert(w==512&&h==512&&pitch==2048&&fmt==0x0001122a);}
static float height_at(float x,float y){return .01f*x-.02f*y;}
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
#include "spell_world41.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);for(int rot=0;rot<32;rot++){float m[16];world_camera(m,g.x,g.y,height_at(g.x,g.y),rot*.19634954f,.8f,1.2f);for(int tick=0;tick<60;tick++){g.time=tick*.01f;unsigned before=quadCount;spell_aim_ring41(&g,m,g.x,g.y,20,tick&1);assert(quadCount-before==224);before=quadCount;spell_success_circle41(m,g.x,g.y,g.time);assert(quadCount-before==38);}}unsigned before=quadCount;float m[16];world_camera(m,g.x,g.y,0,0,.8f,1.2f);spell_success_circle41(m,g.x,g.y,.6f);spell_success_circle41(m,g.x,g.y,1.59f);assert(quadCount-before==76);before=quadCount;spell_success_circle41(m,g.x,g.y,1.6f);assert(quadCount==before);assert(spell_circle_radius41(.6f)==spell_circle_radius41(1.59f));printf("PASS42 actual ground geometry: %u quads, finite camera projections, palette UVs, world bounds and max%u/128 DWORD submission blocks\n",quadCount,peak);}
