#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include "skin_layout.h"
static float minX,minY,maxX,maxY;static unsigned count;static FILE*record;
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){assert(w>0&&h>0&&isfinite(x)&&isfinite(y));if(x<minX)minX=x;if(y<minY)minY=y;if(x+w>maxX)maxX=x+w;if(y+h>maxY)maxY=y+h;count++;if(record)fprintf(record,"Q %f %f %f %f %f %f %f %f\n",x,y,w,h,u,v,uw,vh);}
static void hud_panel(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
#include "ui_context.h"
#include "compact_font.h"
static void reset(void){minX=minY=1e9f;maxX=maxY=-1e9f;count=0;}
int main(int argc,char**argv){assert(argc==2);for(unsigned old=7;old<=11;old++){float scale=old/11.f;unsigned expected=old<10?old+1:old;assert(ui_native_size65(scale)==expected);for(unsigned c=32;c<128;c++)assert(ui_native_advance65(c,scale)==nativeAdvance65[expected-7][c-32]);float s=scale;for(unsigned i=0;ui_native_size65(s)>8;i++){assert(i<4);float smaller=ui_font_smaller200(s);assert(ui_native_size65(smaller)<ui_native_size65(s));s=smaller;}}
 record=fopen(argv[1],"w");assert(record);reset();ui_hint_center200(48,419,544,22,.85f,"D-pad: slots   LB/RB: page   A: play/create   X: delete   B: back");assert(minY>=420&&maxY<=440&&fabsf((minY+maxY)*.5f-430)<=1&&fabsf((minX+maxX)*.5f-320)<=2);fprintf(stderr,"Instructions ink bounds %.0f,%.0f -> %.0f,%.0f\n",minX,minY,maxX,maxY);reset();ui_fit47(30,40,110,.8f,"An extremely long equipment name which must fit");assert(count&&maxX<=141);reset();char lines[8][96];int n=ui_wrap("A compact message needs clearer text and correct measured wrapping.",lines,150,.75f);assert(n>1);for(int i=0;i<n;i++){assert(ui_text_width(lines[i],.75f)<=150);ui_scaled(30,100+i*16,.75f,"%s",lines[i]);}reset();ui_exp_text(25,76,"BASE EXP: MAX");assert(minY>=76&&maxY<=88);ui_exp_text(25,96,"JOB EXP: MAX");assert(maxY<=108);fclose(record);puts("PASS native7/8/9 ->8/9/10 exact atlas sizes/metrics, stable fit-down floor, measured wraps, EXP ink/bar gaps and centered character instructions inside panel body.");}
