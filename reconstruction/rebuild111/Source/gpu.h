#include "sprite_tint.h"
#include "terrain_key52.h"
#include "terrain_minify52.h"
/* SPDX-License-Identifier: MIT
 * Native nv2a terrain mesh plus screen-facing character. No CPU pixel loop.
 */
#include <xboxkrnl/xboxkrnl.h>
static void *gpuTerrain,*gpuMesh,*entityTextures[SPRITE_SLOT_COUNT];
static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static void *gpu_alloc(unsigned n){
 void *p=MmAllocateContiguousMemoryEx(n,0,0x03ffafff,4096,PAGE_READWRITE|PAGE_WRITECOMBINE);
 if(!p){char msg[96];snprintf(msg,sizeof(msg),"GPU allocation of %u KiB failed",n/1024);fail(msg);}return p;
}
static void gpu_memory(void){
 if(terrain){terrain_minify52(terrain,tw,th,mapNames[surfaceMap]);groundTextureFormat52=terrain_prepare52(terrain,tw*th);gpuTerrain=gpu_alloc(tw*th*2);memcpy(gpuTerrain,terrain,tw*th*2);free((unsigned char*)terrain-8);terrain=NULL;}
 /* Actor textures are allocated by upload only when a slot is actually drawn. */
 if(meshRaw){gpuMesh=gpu_alloc(nverts*20);memcpy(gpuMesh,meshVertices,nverts*20);free(meshRaw);meshRaw=NULL;meshVertices=NULL;}
}
#include "gpu_program51.h"
static void screen_fill55(int x,int y,int w,int h,unsigned color){if(w<=0||h<=0)return;if(x==0&&y==0&&w==640&&h==480)pb_fill(0,0,640,480,0xff000000u);int left=screen_layout_edge55(x,1),right=screen_layout_edge55(x+w,1),top=screen_layout_edge55(y,0),bottom=screen_layout_edge55(y+h,0);if(left<0)left=0;if(top<0)top=0;if(right>640)right=640;if(bottom>480)bottom=480;if(right>left&&bottom>top)pb_fill(left,top,right-left,bottom-top,color);}
#define pb_fill screen_fill55

static void gpu_setup(void){
 uint32_t *p=pb_begin();
 p=pb_push1(p,NV097_SET_DEPTH_FUNC,0x203);
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);
 p=pb_push1(p,NV097_SET_LIGHTING_ENABLE,0);
 p=pb_push1(p,NV097_SET_FOG_ENABLE,0);
 p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);
 p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);
 p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);
 p=pb_push1(p,NV097_SET_BLEND_EQUATION,0x8006);
 p=pb_push1(p,NV097_SET_SHADER_STAGE_PROGRAM,1);
 p=pb_push1(p,NV097_SET_COMBINER_CONTROL,1);
 p=pb_push1(p,NV097_SET_COMBINER_COLOR_ICW,0);
 p=pb_push1(p,NV097_SET_COMBINER_ALPHA_ICW,0);
 p=pb_push1(p,NV097_SET_COMBINER_COLOR_OCW,0);
 p=pb_push1(p,NV097_SET_COMBINER_ALPHA_OCW,0);
 p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW0,8);
 p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW1,0x1800);
 for(unsigned i=1;i<4;i++)p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_ENABLE(i),0x0003ffc0);
 pb_end(p);
}
static void bindTexture(void *texture,unsigned width,unsigned height,unsigned pitch,unsigned format){
 uint32_t *p=pb_begin();
 p=pb_push2(p,NV20_TCL_PRIMITIVE_3D_TX_OFFSET(0),(DWORD)texture&0x03ffffff,format);
 p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_NPOT_PITCH(0),pitch<<16);
 p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_NPOT_SIZE(0),(width<<16)|height);
 p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_WRAP(0),0x00030303);
 p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_ENABLE(0),0x4003ffc0);
 p=pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_FILTER(0),0x02022000);
 pb_end(p);
}
/* Reassert world depth explicitly after HUD/loading passes. */
static void gpu_depth_state(int write){
 /* pb_target_back_buffer selects W-buffering (bit 16) every frame.
  * All our vertex programs emit W=1 and explicitly compute Z; use Z-buffering.
  * Retain stencil writes and perspective-correct texture coordinates. */
 uint32_t*p=pb_begin();
 p=pb_push1(p,NV097_SET_CONTROL0,NV097_SET_CONTROL0_STENCIL_WRITE_ENABLE|NV097_SET_CONTROL0_TEXTURE_PERSPECTIVE_ENABLE);
 p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_FUNC,0x203);p=pb_push1(p,NV097_SET_DEPTH_MASK,write);p=pb_push1(p,NV097_SET_ZMIN_MAX_CONTROL,1);pb_end(p);
}
#include "gpu_ground45a.h"
static uint32_t *vertex(uint32_t *p,float x,float y,float z,float u,float v){
 p=pb_push4f(p,NV097_SET_VERTEX_DATA4F_M+9*16,u,v,0,1);
 return pb_push4f(p,NV097_SET_VERTEX_DATA4F_M,x,y,z,1);
}
#include "sprite_slice54.h"
static void gpu_stream_plane51(void*,SparseSprite*,float,float,float,float,float,float);
static void gpu_sprite_plane50(void*texture,SparseSprite*s,float x,float y,float depth,float zoom,float depthTop,float depthBottom){
 if(s->stream51){gpu_stream_plane51(texture,s,x,y,depth,zoom,depthTop,depthBottom);return;}
 gpu_depth_state(0);program(0);bindTexture(texture,s->w,s->h,s->w*s->bytesPerPixel,s->alpha4444?0x00011d2a:s->bytesPerPixel==2?0x0001102a:0x0001122a);
 uint32_t *p=pb_begin();
 p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);
 for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);
 p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);
 float rect[4];sprite_screen_rect(x,y,zoom,s->anchorX,s->anchorY,s->h,rect);float x0=rect[0],y0=rect[1],w=s->w*zoom,h=rect[3];
 SpriteSlice54 slice;if(!sprite_slice54(y0,h,depthTop,depthBottom,s->h,&slice)){pb_end(p);return;}
 p=pb_push1(p,NV097_SET_BEGIN_END,6);
 p=vertex(p,x0,slice.y,slice.top,0,slice.v0);p=vertex(p,x0+w,slice.y,slice.top,s->w,slice.v0);
 p=vertex(p,x0,slice.y+slice.height,slice.bottom,0,slice.v1);p=vertex(p,x0+w,slice.y+slice.height,slice.bottom,s->w,slice.v1);
 p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
}
static void gpu_sprite(void*t,SparseSprite*s,float x,float y,float depth,float scale){gpu_sprite_plane50(t,s,x,y,depth,scale,depth,depth);}
static void gpu_actor_sprite50(void*t,SparseSprite*s,float x,float y,float depth,float scale,float footY,float slope){float r[4];sprite_screen_rect(x,y,scale,s->anchorX,s->anchorY,s->h,r);gpu_sprite_plane50(t,s,x,y,depth,scale,sprite_upright_cached50(depth,r[1],footY,slope),sprite_upright_cached50(depth,r[1]+r[3],footY,slope));}

#include "willow_death259.h"
static void gpu_actor_sprite50c(void*t,SparseSprite*s,float x,float y,float depth,float scale,float footY,float slope,int sourceFade){if(sourceFade>=2&&(s==sprites+20||s==sprites+28)){willow_draw259(s==sprites+28,(unsigned)sourceFade-2,x,y,depth,scale);return;}float r[4],corners[2];sprite_screen_rect(x,y,scale,s->anchorX,s->anchorY,s->h,r);sprite_depth_corners50c(depth,r[1],r[1]+r[3],footY,slope,sourceFade,corners);gpu_sprite_plane50(t,s,x,y,depth,scale,corners[0],corners[1]);}

#include "gpu_sprite_upload45.h"

#include "world_gpu_stream171.h"

#include "npc_feet182.h"
