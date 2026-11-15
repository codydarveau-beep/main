/* SPDX-License-Identifier: MIT. Render actual UI draw calls through a host recorder. */
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
#include "window_ui.h"
#include "hud_batch.h"
#include "skin_colors.h"
extern const unsigned char fontWidths[96];
static unsigned whiteDigits,yellowDigits;static int yellowValue;static float whiteX[800];static float whiteTop=9999,yellowBottom=-9999;
static void*skinTexture,*currentTexture;static HudBatch batch;
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
static void*gpu_alloc(unsigned n){return malloc(n);}
static unsigned char*inflateasset(const char*n,const unsigned char*s,unsigned sz,unsigned raw){(void)n;unsigned char*p=malloc(raw);uLongf len=raw;if(uncompress(p,&len,s,sz)||len!=raw)fail("inflate");return p;}
static void hud_setup(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){(void)w;(void)h;(void)pitch;(void)format;(void)blend;currentTexture=t;}
static void pb_fill(int x,int y,int w,int h,unsigned c){unsigned i=0;for(;i<sizeof(skinColors)/sizeof(skinColors[0]);i++)if(skinColors[i]==c)break;if(i==sizeof(skinColors)/sizeof(skinColors[0]))fail("missing palette");if(!hud_batch_add(&batch,x,y,w,h,i%64*8,256+i/64*8,0,0))fail("batch overflow");printf("F %d %d %d %d %u\n",x,y,w,h,c);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){if(v==144){whiteX[whiteDigits]=x;whiteDigits++;if(y<whiteTop)whiteTop=y;}if(v==162){yellowValue=yellowValue*10+(int)((u-384)/12);yellowDigits++;if(y+h>yellowBottom)yellowBottom=y+h;}if(!hud_batch_add(&batch,x,y,w,h,u,v,uw,vh))fail("batch overflow");printf("Q %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",x,y,w,h,u,v,uw,vh);}
#include "hud_theme.h"
static void hud_text(int x,int y,const char*f,...){char line[160];va_list a;va_start(a,f);vsnprintf(line,sizeof(line),f,a);va_end(a);for(unsigned i=0;line[i]&&x<622;i++){unsigned c=(unsigned char)line[i];if(c<32||c>127)c='?';unsigned k=c-32;if(c!=' ')hud_quad(x,y,16,16,(k%16)*16,(k/16)*16,16,16);x+=fontWidths[k]+1;}}
static void hud_bar(int x,int y,int w,int n,int max,unsigned c){pb_fill(x,y,w,8,0xff101711);if(max>0&&n>0)pb_fill(x+1,y+1,(w-2)*n/max,6,c);}
#include "window_draw.h"
static int musicVolume=50,soundVolume=60,musicMuted,soundMuted;
#include "pause_draw.h"
static unsigned gw=400,gh=400;
static float height_at(float x,float y){(void)x;(void)y;return 0;}
#include "damage_draw.h"
int main(void){float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;skin_init();Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16]={1,0,0,0,0,1,0,0};combat_number(&g,320,240,246,2,0);g.time=.05f;damage_draw(&g,m);assert(whiteDigits==3&&yellowDigits==3&&yellowValue==123);whiteDigits=yellowDigits=yellowValue=0;batch.count=0;g.time=.11f;damage_draw(&g,m);assert(whiteDigits==6&&yellowValue==246&&yellowBottom<whiteTop);whiteDigits=yellowDigits=yellowValue=0;batch.count=0;g.damageNext=0;combat_number(&g,320,240,1000,10,0);g.time+=.89f;damage_draw(&g,m);assert(yellowValue==900&&whiteDigits>0);whiteDigits=yellowDigits=yellowValue=0;batch.count=0;whiteTop=9999;yellowBottom=-9999;g.time+=.02f;damage_draw(&g,m);assert(yellowValue==1000&&whiteDigits==30&&yellowBottom<whiteTop);g.damageNext=0;whiteDigits=yellowDigits=yellowValue=0;batch.count=0;unsigned token=0;combat_number(&g,320,240,115,1,0);combat_combo(&g,&token,320,240,115);assert(token==2);g.time+=.5f;combat_number(&g,320,240,115,1,0);unsigned seed=g.rng;combat_combo(&g,&token,320,240,230);assert(token==2&&g.damageNext==3&&g.damage[1].value==230&&g.damage[1].at==g.time);damage_draw(&g,m);assert(yellowValue==230&&g.rng==seed);for(int i=0;i<20;i++)combat_number(&g,320,240,1,1,0);combat_combo(&g,&token,320,240,345);assert(token==g.damageNext&&g.damage[(token-1)%DAMAGE_EVENTS].value==345);assert(batch.count<HUD_BATCH_QUADS);free(skinTexture);puts("PASS actual damage renderer: yellow starts with first hit, grows 123 to 246 and 900 to 1000, retains separation; persistent field readout updates in place, ring recycling and gameplay RNG isolation");}
