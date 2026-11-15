#include "projection.h"
/* SPDX-License-Identifier: MIT. World skill targeting/effect overlays. */
static void skill_ring(const float*m,float x,float y,float radius,unsigned color){
 for(int i=0;i<32;i++){
  float a=i*6.28318530718f/32,xx=x+cosf(a)*radius,yy=y+sinf(a)*radius;
  if(xx<0||yy<0||xx>=gw*8||yy>=gh*8)continue;
  float zz=height_at(xx,yy);int sx=m[0]*xx+m[1]*yy+m[3],sy=m[4]*xx+m[5]*yy+m[6]*zz+m[7];
  if(sx>3&&sx<636&&sy>82&&sy<414)pb_fill(sx-1,sy-1,3,3,color);
 }
}
static void skill_square(const float*m,float x,float y,float radius,unsigned color){
 for(int i=0;i<32;i++){int edge=i/8;float t=(i%8)/8.f,xx=x,yy=y;
  if(edge==0){xx=x-radius+2*radius*t;yy=y-radius;}else if(edge==1){xx=x+radius;yy=y-radius+2*radius*t;}else if(edge==2){xx=x+radius-2*radius*t;yy=y+radius;}else{xx=x-radius;yy=y+radius-2*radius*t;}
  if(xx<0||yy<0||xx>=gw*8||yy>=gh*8)continue;float zz=height_at(xx,yy);int sx=m[0]*xx+m[1]*yy+m[3],sy=m[4]*xx+m[5]*yy+m[6]*zz+m[7];if(sx>3&&sx<636&&sy>82&&sy<414)pb_fill(sx-1,sy-1,3,3,color);
 }
}
/* Continuous circle uses the same world coordinates and radius as protection. */
/* Project a continuous circle around its sampled centre, on one local ground
 * plane. Sampling every rim height deforms a one-cell wall at terrain seams.
 * The player contact and all centre marks use this same world-to-screen map. */
static void skill_contact(const float*m,float x,float y,unsigned color){float z=height_at(x,y),sx,sy;world_project(m,x,y,z,&sx,&sy);int px=(int)(sx+.5f),py=(int)(sy+.5f);if(px>3&&px<636&&py>82&&py<448){pb_fill(px-2,py,5,1,color);pb_fill(px,py-2,1,5,color);}}
static void skill_small_ring(const float*m,float x,float y,float radius,unsigned color){float z=height_at(x,y),zx=(height_at(x+1,y)-height_at(x-1,y))*.5f,zy=(height_at(x,y+1)-height_at(x,y-1))*.5f,cx=m[0]*x+m[1]*y+m[3],cy=m[4]*x+m[5]*y+m[6]*z+m[7];for(int i=0;i<64;i++){float a=i*6.28318530718f/64,dx=cosf(a)*radius,dy=sinf(a)*radius;int sx=(int)(cx+m[0]*dx+m[1]*dy+.5f),sy=(int)(cy+(m[4]+m[6]*zx)*dx+(m[5]+m[6]*zy)*dy+.5f);if(sx>3&&sx<636&&sy>82&&sy<448)pb_fill(sx,sy,1,1,color);}}
/* Colour shares the actual radial protection predicate. */
static void skill_safety_overlay(const Combat*g,const float*m){(void)g;(void)m;}
static void skill_overlay(const Combat*g,const float*m,int aiming,unsigned aimedSkill,float aimX,float aimY){
 if(aiming&&(aimedSkill==48||aimedSkill==53||aimedSkill==54||aimedSkill==31)){unsigned c=skill_ground_point(g,aimedSkill,aimX,aimY)?0xff76e6a5:0xffff6666;if(aimedSkill==48){skill_small_ring(m,aimX,aimY,SAFETY_RADIUS,c);skill_contact(m,aimX,aimY,c);skill_contact(m,g->x,g->y,0xffffffff);}else if(aimedSkill==53||aimedSkill==54)skill_small_ring(m,aimX,aimY,aimedSkill==53?PNEUMA_RADIUS:6,c);else if(aimedSkill==30||aimedSkill==32||aimedSkill>=69){}else if(aimedSkill==31){int vertical=fabsf(aimX-g->x)>=fabsf(aimY-g->y);for(int j=-1;j<=1;j++){float x=aimX+(vertical?0:j*8),y=aimY+(vertical?j*8:0);unsigned color=(!g->canMove||g->canMove(g->world,x,y,x,y))?c:0xffff6666;(void)color;}}else skill_ring(m,aimX,aimY,44,c);}

}
/* Small procedural lightning placeholder, bounded to five short columns.
 * Original effect-frame import is a later task; no additional textures. */
static void skill_control_overlay(const Combat*g,const float*m){
 for(int fno=0;fno<COMBAT_FIELDS;fno++){const CombatField*f=&g->fields[fno];if(!f->remaining&&g->time>=f->fadeUntil)continue;
 skill_square(m,f->x,f->y,20,0xff65dffa);float t=g->time-(f->nextAt-.5f);if(t<0||t>.15f)continue;
 for(int i=0;i<5;i++){
  float a=i*2.399963f,x=f->x+cosf(a)*15,y=f->y+sinf(a)*15;
  if(x<0||y<0||x>=gw*8||y>=gh*8)continue;
  float z=height_at(x,y);int px=m[0]*x+m[1]*y+m[3],py=m[4]*x+m[5]*y+m[6]*z+m[7];
  if(px<8||px>632||py<110||py>414)continue;
  int phase=(int)(t*30)+i;
  for(int j=0;j<8;j++){int xx=px+((j+phase)%3-1)*3,yy=py-32+j*4;pb_fill(xx,yy,2,5,0xff8fd1ff);}
 }
 }
}

/* Compact procedural flame columns and a short arrow fan; no new textures. */
static void skill_expansion_overlay(const Combat*g,const float*m){
#ifndef MYRO_ORIGINAL_ART39
 for(int w=0;w<COMBAT_BARRIERS;w++){const CombatBarrier*f=&g->barriers[w];if(f->expires<=g->time)continue;
  for(int c=0;c<3;c++)if(f->hits[c]>0){float x=f->x+(c-1)*f->axisX*8,y=f->y+(c-1)*f->axisY*8;if(x<0||y<0||x>=gw*8||y>=gh*8)continue;float z=height_at(x,y);int px=m[0]*x+m[1]*y+m[3],py=m[4]*x+m[5]*y+m[6]*z+m[7];if(px<12||px>628||py<112||py>414)continue;for(int j=0;j<6;j++){int phase=((int)(g->time*14)+c+j)%3;pb_fill(px-5+phase,py-4-j*3,8-phase,3,0xffff8c38);pb_fill(px-2,py-4-j*3,3,3,0xffffdf56);}}
 }
#endif
 if(g->fxSkill==32){float t=g->time-g->fxAt;if(t>=0&&t<.25f){float u=t/.25f;for(int i=0;i<5;i++){float x=g->x+(g->fxX-g->x)*u+(i-2)*3,y=g->y+(g->fxY-g->y)*u;if(x<0||y<0||x>=gw*8||y>=gh*8)continue;float z=height_at(x,y);int px=m[0]*x+m[1]*y+m[3],py=m[4]*x+m[5]*y+m[6]*z+m[7]-10;if(px>8&&px<630&&py>90&&py<410)pb_fill(px-1,py-4,2,7,0xffffdf56);}}}
}

static void skill_utility_overlay(const Combat*g,const float*m){(void)g;(void)m;}

static void skill_acolyte_overlay(const Combat*g,const float*m){for(int i=0;i<3;i++){const PneumaField*p=&g->pneuma[i];if(p->expires>g->time)skill_small_ring(m,p->x,p->y,PNEUMA_RADIUS,0xff76e6a5);}}
