/* MIT. Actual terrain draw-state submission plus real map triangle winding. */
#define main world_test_main45a
#include "test_world43.c"
#undef main
#include "projection.h"
#include "nv_regs.h"
typedef uintptr_t DWORD;
static uint32_t buffer45a[4096];static unsigned front45a,cull45a,draw45a;
static uint32_t*pb_begin(void){return buffer45a;}
static void pb_end(uint32_t*p){assert(p>=buffer45a&&p<buffer45a+4096);}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){if(reg==NV097_SET_FRONT_FACE)front45a=value;if(reg==NV097_SET_CULL_FACE_ENABLE)cull45a=value;if(reg==NV097_DRAW_ARRAYS)draw45a++;*p++=reg;*p++=value;return p;}
static void pb_push(uint32_t*p,unsigned reg,unsigned n){(void)reg;(void)n;*p=0;}
static void program(int n){(void)n;}
static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned fmt){(void)p;(void)w;(void)h;(void)pitch;(void)fmt;}
static void gpu_depth_state(int n){(void)n;}
#include "gpu_ground45a.h"
int main(void){unsigned checked=0;
 for(unsigned map=0;map<WORLD_MAP_COUNT;map++){
  assert(world_activate(map));const float*v=gpuMesh;unsigned flat=~0u;
  for(unsigned i=0;i+2<nverts;i+=3){const float*a=v+i*5,*b=a+5,*c=a+10;float cross=(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0]);if(cross>1&&fabsf(a[2]-b[2])<.001f&&fabsf(a[2]-c[2])<.001f){flat=i;break;}}
  assert(flat!=~0u);
  for(int yaw=0;yaw<32;yaw++)for(int tilt=0;tilt<8;tilt++){
   float m[16],p[6];world_camera(m,spawnx,spawny,0,yaw*.2f,.52f+tilt*.08f,1.2f);for(int k=0;k<3;k++){const float*a=v+(flat+k)*5;world_project(m,a[0],a[1],a[2],p+k*2,p+k*2+1);}
   float area=(p[2]-p[0])*(p[5]-p[1])-(p[3]-p[1])*(p[4]-p[0]);assert(area<0);front45a=cull45a=draw45a=0;assert(gpu_ground(m,spawnx/16,spawny/16,1)>0);assert(front45a==NV097_SET_FRONT_FACE_V_CCW&&cull45a==1&&draw45a);checked++;
  }
 }
 world_release();assert(!allocated&&!bytesNow);printf("PASS45a actual native terrain front-face/cull commands and real flat triangles:18 maps,%u camera configurations; corrected orientation retained.\n",checked);
}
