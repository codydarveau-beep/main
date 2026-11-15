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
static unsigned whiteDigits,yellowDigits;static float whiteX[800];static float whiteTop=9999,yellowBottom=-9999;
static void*skinTexture,*currentTexture;static HudBatch batch;
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
static void*gpu_alloc(unsigned n){return malloc(n);}
static unsigned char*inflateasset(const char*n,const unsigned char*s,unsigned sz,unsigned raw){(void)n;unsigned char*p=malloc(raw);uLongf len=raw;if(uncompress(p,&len,s,sz)||len!=raw)fail("inflate");return p;}
static void hud_setup(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){(void)w;(void)h;(void)pitch;(void)format;(void)blend;currentTexture=t;}
static void pb_fill(int x,int y,int w,int h,unsigned c){unsigned i=0;for(;i<sizeof(skinColors)/sizeof(skinColors[0]);i++)if(skinColors[i]==c)break;if(i==sizeof(skinColors)/sizeof(skinColors[0]))fail("missing palette");if(!hud_batch_add(&batch,x,y,w,h,286+i%28*8,102+i/28*8,0,0))fail("batch overflow");printf("F %d %d %d %d %u\n",x,y,w,h,c);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){if(v==144){whiteX[whiteDigits]=x;whiteDigits++;if(y<whiteTop)whiteTop=y;}if(v==162){yellowDigits++;if(y+h>yellowBottom)yellowBottom=y+h;}if(!hud_batch_add(&batch,x,y,w,h,u,v,uw,vh))fail("batch overflow");printf("Q %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",x,y,w,h,u,v,uw,vh);}
#include "hud_theme.h"
static void hud_text(int x,int y,const char*f,...){char line[160];va_list a;va_start(a,f);vsnprintf(line,sizeof(line),f,a);va_end(a);for(unsigned i=0;line[i]&&x<622;i++){unsigned c=(unsigned char)line[i];if(c<32||c>127)c='?';unsigned k=c-32;if(c!=' ')hud_quad(x,y,16,16,(k%16)*16,(k/16)*16,16,16);x+=fontWidths[k]+1;}}
static void hud_bar(int x,int y,int w,int n,int max,unsigned c){pb_fill(x,y,w,8,0xff101711);if(max>0&&n>0)pb_fill(x+1,y+1,(w-2)*n/max,6,c);}
#include "window_draw.h"
static int musicVolume=50,soundVolume=60,musicMuted,soundMuted;
#include "pause_draw.h"
static unsigned gw=400,gh=400;
static float height_at(float x,float y){(void)x;(void)y;return 0;}
#include "damage_draw.h"
int main(void){float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;skin_init();Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16]={1,0,0,0,0,1,0,0};combat_number(&g,320,240,246,2,0);g.time=.05f;damage_draw(&g,m);assert(whiteDigits==3&&yellowDigits==0);whiteDigits=yellowDigits=0;batch.count=0;g.time=.11f;damage_draw(&g,m);assert(whiteDigits==6&&yellowDigits==3&&yellowBottom<whiteTop);whiteDigits=yellowDigits=0;batch.count=0;g.damageNext=0;combat_number(&g,320,240,1000,10,0);g.time+=.89f;damage_draw(&g,m);assert(yellowDigits==0&&whiteDigits>0);whiteDigits=yellowDigits=0;batch.count=0;whiteTop=9999;yellowBottom=-9999;g.time+=.02f;damage_draw(&g,m);assert(yellowDigits==4&&whiteDigits==30&&yellowBottom<whiteTop);g.damageNext=0;whiteDigits=yellowDigits=0;batch.count=0;combat_number(&g,320,240,1155,5,0);g.time+=.41f;damage_draw(&g,m);assert(whiteDigits==15&&yellowDigits==4);for(int i=0;i<5;i++)for(int j=i+1;j<5;j++)assert(whiteX[i*3]!=whiteX[j*3]);assert(batch.count<HUD_BATCH_QUADS);g.damageNext=0;whiteDigits=yellowDigits=0;batch.count=0;combat_number(&g,320,240,777,1,0);g.damage[0].kind=1;unsigned seed=g.rng;damage_draw(&g,m);assert(whiteDigits==0&&yellowDigits==3&&g.rng==seed);free(skinTexture);puts("PASS actual damage renderer: 100ms spacing, yellow total separate above every white digit, ten-hit final total timing and bounded drawing");}
