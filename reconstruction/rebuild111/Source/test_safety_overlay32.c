/* MIT. Target marker and deployed footprint must share cell, size and predicate. */
#include <assert.h>
#include "combat.h"
static unsigned gw=400,gh=400;static int calls,minX,minY,maxX,maxY;static unsigned lastColor;
static float height_at(float x,float y){return 0;}
static void pb_fill(int x,int y,int w,int h,unsigned color){calls++;if(x<minX)minX=x;if(y<minY)minY=y;if(x>maxX)maxX=x;if(y>maxY)maxY=y;lastColor=color;}
#include "skills_ui.h"
static void reset(void){calls=0;minX=minY=10000;maxX=maxY=-10000;}
int main(void){Combat g;combat_init(&g,1501,1502,NULL,NULL);g.fxAt=-100;float m[16]={0};m[0]=m[5]=4;m[3]=320-6000;m[7]=240-6000;reset();skill_overlay(&g,m,1,48,1502.9f,1501.1f);assert(calls==32&&minX==303&&maxX==335&&minY==223&&maxY==255);int xx=minX,yy=minY;g.safety[0]=(SafetyWall){1500,1500,50,0,11};reset();skill_safety_overlay(&g,m);assert(calls==32&&minX==xx&&minY==yy&&lastColor==0xff76e6a5);g.x+=8;reset();skill_safety_overlay(&g,m);assert(lastColor==0xffb8a4ff);g.x-=8;g.safety[0].blockedUntil=1;reset();skill_safety_overlay(&g,m);assert(lastColor==0xffffffff);puts("PASS one-cell aim/deployed marker exact projected bounds; protection green/outside violet/block white follow gameplay");}
