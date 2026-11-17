#define MYRO_HOST
#define MYRO_DISC_ENEMIES44 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
#include "developer.h"
static void fail(const char*s){fprintf(stderr,"HEAD TEST:%s\n",s);exit(2);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf len=raw;assert(uncompress(b,&len,p,packed)==Z_OK&&len==raw);return b;}
#include "sprites.h"
#include "projection.h"
#include "sprite_slice54.h"
#include "sprite_tint.h"
static unsigned spriteFrozen[SPRITE_SLOT_COUNT],spriteStone[SPRITE_SLOT_COUNT],spritePoison[SPRITE_SLOT_COUNT],spriteFlash49[SPRITE_SLOT_COUNT];
static int spriteHiddenPlayer,spriteCoatedPlayer,spriteQuickenPlayer45,spriteBerserkPlayer45;
static unsigned liveGPU,peakGPU;static void*gpu_alloc(unsigned n){size_t*p=malloc(n+sizeof(size_t));assert(p);*p=n;liveGPU+=n;if(liveGPU>peakGPU)peakGPU=liveGPU;return p+1;}
static void MmFreeContiguousMemory(void*p){if(p){size_t*q=(size_t*)p-1;assert(liveGPU>=*q);liveGPU-=*q;free(q);}}
static int pb_busy(void){return 0;}static uint32_t commands[512];static unsigned vertexCount;static float vertices[64][5];
static uint32_t*pb_begin(void){return commands;}static void pb_end(uint32_t*p){(void)p;}static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){(void)reg;(void)value;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(vertexCount<64);float a[]={x,y,z,u,v};memcpy(vertices[vertexCount++],a,sizeof(a));return p;}
static void gpu_depth_state(unsigned write){(void)write;}static void program(unsigned n){(void)n;}static void bindTexture(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format){assert(t&&w&&h&&pitch>=w*2&&!(pitch%64)&&format==0x00011d2a);}
enum{NV097_SET_VERTEX_DATA_ARRAY_FORMAT,NV097_SET_CULL_FACE_ENABLE=20,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_BLEND_ENABLE,NV097_SET_BEGIN_END};
#include "headgear54.h"
static Combat g;

static unsigned char spriteScratch50b[65536];static unsigned quads;static float boundsUI[4];
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){assert(t&&w&&h&&pitch>=w*2&&blend);assert(format==0x00011d2a||format==0x0001102a||format==0x0001122a);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){(void)u;(void)v;assert(w>0&&h>0&&uw>0&&vh>0);boundsUI[0]=fminf(boundsUI[0],x);boundsUI[1]=fminf(boundsUI[1],y);boundsUI[2]=fmaxf(boundsUI[2],x+w);boundsUI[3]=fmaxf(boundsUI[3],y+h);quads++;}
static void*entityTextures[SPRITE_SLOT_COUNT];
#include "appearance_render58.h"
#include "headgear_ui180.h"
#include "equipment_preview260.h"
int main(void){combat_init(&g,1000,1000,NULL,NULL);dev_class_preset(&g,9);sprite_set_equipment(class_actor_id50(9,0),0);owned_init52(&g.owned52);const unsigned slots[]={8,5,9};
for(unsigned j=0;j<3;j++){unsigned id=0;for(unsigned i=0;i<sizeof(headgearItems54)/sizeof(*headgearItems54);i++){unsigned source=headgearItems54[i][0];const OwnedRule52*r=item_rule52(source);if(r&&r->location==(inventorySlotBits52[slots[j]]&(1|256|512))&&equipment_allowed52(equipment_rule52(source),9,1,250)&&head_definition54(headgearItems54[i][1],1)){id=source;break;}}assert(id&&owned_add52(&g.owned52,0,id,1,item_rule52)==OWNED_OK52);assert(inventory_equip_uid52(&g,g.owned52.items[g.owned52.count[0]-1].uid,slots[j]));}
head_prepare54(&g);HeadPose54 back=head_pose54(sprites,0,4,0,0,0);head_frames54(back,0);head_upload54();unsigned worldFrames[3],anchor=sprites[0].anchorX;for(unsigned i=0;i<3;i++)worldFrames[i]=headCache54[i].frame;unsigned original=liveGPU;equipment_prepare260(1);assert(equipmentTexture260&&liveGPU>original);unsigned once=liveGPU;void*texture=equipmentTexture260;equipment_prepare260(1);assert(liveGPU==once&&equipmentTexture260==texture);for(unsigned i=0;i<3;i++)assert(headCache54[i].frame==worldFrames[i]);assert(sprites[0].anchorX==anchor);
SparseSprite copy=sprites[0];unsigned front=sprite_frame(&copy,0,0,0,0,0),*d=copy.directory+front*5;static unsigned char expected[65536];for(unsigned y=0;y<d[3];y++)memcpy(expected+((d[1]+y)*copy.w+d[0])*copy.bytesPerPixel,copy.pixels+d[4]+y*d[2]*copy.bytesPerPixel,d[2]*copy.bytesPerPixel);unsigned b[4];appearance_compose58(&copy,front,0,expected,b);assert(!memcmp(expected,equipmentTexture260,65536));
boundsUI[0]=boundsUI[1]=1e9f;boundsUI[2]=boundsUI[3]=-1e9f;equipment_draw260(120,90,52,210);assert(quads==4&&boundsUI[0]>=120&&boundsUI[1]>=90&&boundsUI[2]<=172&&boundsUI[3]<=300);assert(fabsf((boundsUI[0]+boundsUI[2])/2-146)<.01f&&fabsf((boundsUI[1]+boundsUI[3])/2-195)<.01f);equipment_prepare260(0);assert(liveGPU==original&&!equipmentTexture260);for(unsigned review272=0;review272<100;review272++){equipment_prepare260(1);assert(equipmentTexture260);quads=0;equipment_draw260(120,90,52,210);assert(quads==4);equipment_prepare260(0);assert(liveGPU==original&&!equipmentTexture260);}head_release54();free(sprites[0].raw);sprites[0].raw=NULL;assert(!liveGPU);printf("PASS restoration additional review2 equipment (100 reopen/close lifetimes): exact forward idle body pixels, all three head attachments, larger centered union within52x210, world direction/head frames preserved, cached refresh and complete close cleanup. Peak preview/head GPU bytes %u; target GPU not exercised.\n",peakGPU);}
