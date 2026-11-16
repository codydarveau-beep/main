#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "hud_batch.h"
typedef uintptr_t DWORD;
static float skin[HUD_BATCH_QUADS*HUD_QUAD_FLOATS],damage[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];
static float*hudSkinVertices54b=skin,*hudDamageVertices54b=damage;
static unsigned hudSkinUsed253,hudDamageUsed253;
static HudBatch hudBatch;
static void*skinTexture=(void*)1,*hudBatchTexture53;
static unsigned hudBatchWidth53,hudBatchHeight53,hudBatchPitch53,hudBatchFormat53;
static void fail(const char*s){(void)s;_Exit(77);}
static uint32_t commands[16];
static uint32_t*pb_begin(void){return commands;}
static void pb_end(uint32_t*p){(void)p;}
static uint32_t*pb_push1(uint32_t*p,unsigned k,unsigned v){(void)k;(void)v;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){(void)x;(void)y;(void)z;(void)u;(void)v;return p;}
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned p,unsigned f,int b){(void)t;(void)w;(void)h;(void)p;(void)f;(void)b;}
#define NV097_BREAK_VERTEX_BUFFER_CACHE 0
#define NV097_DRAW_ARRAYS 0
#define NV097_SET_BEGIN_END 0
#define NV097_SET_BEGIN_END_OP_QUADS 0
#define NV097_SET_VERTEX_DATA_ARRAY_FORMAT 0
#define NV097_SET_VERTEX_DATA_ARRAY_OFFSET 0
static void hud_frame_begin253(void){if(hudBatch.active)fail("HUD frame reset inside a batch");hudSkinUsed253=hudDamageUsed253=0;hudBatch.count=0;hudBatch.vertices=hudSkinVertices54b;}
static void hud_batch_begin_texture53(void*texture,unsigned width,unsigned height,unsigned pitch,unsigned format){if(hudBatch.active)fail("Nested HUD batch");unsigned used253=texture==skinTexture?hudSkinUsed253:hudDamageUsed253;if(used253>HUD_BATCH_QUADS)fail("HUD arena bounds invalid");hudBatch.vertices=(texture==skinTexture?hudSkinVertices54b:hudDamageVertices54b)+used253*HUD_QUAD_FLOATS;hudBatchTexture53=texture;hudBatchWidth53=width;hudBatchHeight53=height;hudBatchPitch53=pitch;hudBatchFormat53=format;hudBatch.count=0;hudBatch.active=1;}
static void hud_batch_end(void){
 hudBatch.active=0;if(!hudBatch.count)return;
 float*arena253=hudBatchTexture53==skinTexture?hudSkinVertices54b:hudDamageVertices54b;unsigned used253=(unsigned)(hudBatch.vertices-arena253)/HUD_QUAD_FLOATS+hudBatch.count;if(used253>HUD_BATCH_QUADS)fail("HUD arena capacity exceeded");if(hudBatchTexture53==skinTexture)hudSkinUsed253=used253;else hudDamageUsed253=used253;
 __sync_synchronize(); /* publish write-combined vertices before GPU submission */
 hud_setup_direct(hudBatchTexture53,hudBatchWidth53,hudBatchHeight53,hudBatchPitch53,hudBatchFormat53,1);
 uint32_t*p=pb_begin();
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,2|(3<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+9*4,2|(2<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET,(DWORD)hudBatch.vertices&0x03ffffff);
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET+9*4,((DWORD)hudBatch.vertices+12)&0x03ffffff);
 p=pb_push1(p,NV097_BREAK_VERTEX_BUFFER_CACHE,0);
 p=pb_push1(p,NV097_SET_BEGIN_END,NV097_SET_BEGIN_END_OP_QUADS);
 unsigned count=hudBatch.count*4,at=0;
 while(at<count){unsigned n=count-at;if(n>252)n=252;p=pb_push1(p,NV097_DRAW_ARRAYS,((n-1)<<24)|at);at+=n;}
 p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){
 if(hudBatch.active){float*base200=hudBatchTexture53==skinTexture?hudSkinVertices54b:hudDamageVertices54b;if(hudBatch.vertices+(hudBatch.count+1)*HUD_QUAD_FLOATS>base200+HUD_BATCH_QUADS*HUD_QUAD_FLOATS)fail("HUD segment capacity exceeded");if(!hud_batch_add(&hudBatch,x,y,w,h,u,v,uw,vh))fail("HUD batch capacity exceeded");return;}
 uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,6);p=vertex(p,x,y,1,u,v);p=vertex(p,x+w,y,1,u+uw,v);p=vertex(p,x,y+h,1,u,v+vh);p=vertex(p,x+w,y+h,1,u+uw,v+vh);p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
}

static void start(void*t){hud_batch_begin_texture53(t,512,2048,2048,0);}
int main(void){for(unsigned prefix=1;prefix<1000;prefix*=7){hud_frame_begin253();start(skinTexture);for(unsigned i=0;i<prefix;i++)hud_quad(i+1,2,3,4,5,6,7,8);hud_batch_end();float*saved=malloc(prefix*HUD_QUAD_FLOATS*sizeof(float));memcpy(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float));start(skinTexture);assert(hudBatch.vertices==skin+prefix*HUD_QUAD_FLOATS);for(unsigned i=0;i<30;i++)hud_quad(100,20,3,4,5,6,7,8);hud_batch_end();assert(!memcmp(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float)));start((void*)2);assert(hudBatch.vertices==damage);hud_quad(2,2,2,2,0,0,1,1);hud_batch_end();start(skinTexture);assert(hudBatch.vertices==skin+(prefix+30)*HUD_QUAD_FLOATS);hud_quad(9,9,9,9,0,0,1,1);hud_batch_end();assert(!memcmp(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float)));free(saved);}hud_frame_begin253();hudSkinUsed253=HUD_BATCH_QUADS-1;start(skinTexture);hud_quad(1,1,1,1,1,1,1,1);hud_batch_end();assert(hudSkinUsed253==HUD_BATCH_QUADS);pid_t p=fork();assert(p>=0);if(!p){start(skinTexture);hud_quad(1,1,1,1,1,1,1,1);_Exit(0);}int status;assert(waitpid(p,&status,0)==p&&WIFEXITED(status)&&WEXITSTATUS(status)==77);hud_frame_begin253();assert(!hudSkinUsed253&&!hudDamageUsed253);puts("PASS actual shared HUD arenas: modal/adjacent windows preserve submitted vertex prefixes, separate skin/damage cursors, frame reset and capacity denial. GPU boundary modeled.");}
