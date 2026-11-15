#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "projection.h"
static unsigned gw=400,gh=400,quads;static int xmin,xmax;
static float height_at(float x,float y){assert(isfinite(x)&&isfinite(y)&&x>=0&&y>=0&&x<3200&&y<3200);return 0;}
static void pb_fill(int x,int y,int w,int h,unsigned color){(void)color;assert(x>=0&&y>=0&&x+w<=640&&y+h<=480);if(x<xmin)xmin=x;if(x>xmax)xmax=x;quads++;}
#include "skills_ui.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16];world_camera(m,1500,1500,0,0,.8f,1);xmin=1000;xmax=-1;skill_overlay(&g,m,1,30,1500,1500);assert(quads==32&&xmin==299&&xmax==339);quads=0;g.fields[0].remaining=2;g.fields[0].nextAt=.5f;g.fields[0].x=g.fields[0].y=1500;skill_control_overlay(&g,m);assert(quads==72);quads=0;g.fields[0].remaining=0;g.fields[0].fadeUntil=1;g.time=2;skill_control_overlay(&g,m);assert(!quads);g.time=0;skill_overlay(&g,m,1,30,2,2);assert(!quads);puts("PASS square targeting matches 5x5-cell coverage; bounded 72-quad lightning marker, expiry and screen/map clipping");}
