/* MIT. Exercise actual bounded effect overlays through draw-call assertions. */
#include <assert.h>
#include "combat.h"
#include "projection.h"
static unsigned gw=400,gh=400,quads;
static float height_at(float x,float y){assert(isfinite(x)&&isfinite(y)&&x>=0&&y>=0&&x<3200&&y<3200);return 0;}
static void pb_fill(int x,int y,int w,int h,unsigned color){(void)color;assert(x>=0&&y>=0&&x+w<=640&&y+h<=480);quads++;}
#include "skills_ui.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16];world_camera(m,1500,1500,0,0,.8f,1);for(int w=0;w<3;w++){CombatBarrier*f=&g.barriers[w];f->x=1500+w*20;f->y=1500;f->axisY=1;f->expires=5;for(int j=0;j<3;j++)f->hits[j]=5;}skill_expansion_overlay(&g,m);assert(quads==108);quads=0;g.fxSkill=32;g.fxAt=0;g.time=.125f;g.fxX=1540;g.fxY=1500;skill_expansion_overlay(&g,m);assert(quads==113);quads=0;g.time=10;skill_expansion_overlay(&g,m);assert(!quads);quads=0;skill_overlay(&g,m,1,31,1540,1500);assert(quads==96);puts("PASS three-wall 108-quad bound, arrow fan 5-quad bound, expiry, three-cell targeting and screen/map clipping");}
