#include "world_gate_state64.h"
/* Lightweight world-depth portal rings: one plane, one strip, no allocations. */
#ifndef MYRO_PORTAL_DRAW52_H
#define MYRO_PORTAL_DRAW52_H
static const float portalUnit52[33][2]={
{1.000000000f,0.000000000f},
{0.980785280f,0.195090322f},
{0.923879533f,0.382683432f},
{0.831469612f,0.555570233f},
{0.707106781f,0.707106781f},
{0.555570233f,0.831469612f},
{0.382683432f,0.923879533f},
{0.195090322f,0.980785280f},
{0.000000000f,1.000000000f},
{-0.195090322f,0.980785280f},
{-0.382683432f,0.923879533f},
{-0.555570233f,0.831469612f},
{-0.707106781f,0.707106781f},
{-0.831469612f,0.555570233f},
{-0.923879533f,0.382683432f},
{-0.980785280f,0.195090322f},
{-1.000000000f,0.000000000f},
{-0.980785280f,-0.195090322f},
{-0.923879533f,-0.382683432f},
{-0.831469612f,-0.555570233f},
{-0.707106781f,-0.707106781f},
{-0.555570233f,-0.831469612f},
{-0.382683432f,-0.923879533f},
{-0.195090322f,-0.980785280f},
{-0.000000000f,-1.000000000f},
{0.195090322f,-0.980785280f},
{0.382683432f,-0.923879533f},
{0.555570233f,-0.831469612f},
{0.707106781f,-0.707106781f},
{0.831469612f,-0.555570233f},
{0.923879533f,-0.382683432f},
{0.980785280f,-0.195090322f},
{1.000000000f,-0.000000000f},
};
static int portal_marker52(const float*m,float x,float y,float ringRadius,unsigned color,int*begun){
 if(!isfinite(x)||!isfinite(y)||x<0||y<0||x>=gw*8.f||y>=gh*8.f)return 0;
 float z=height_at(x,y)+.2f,sx,sy;world_project(m,x,y,z,&sx,&sy);
 float rx=(ringRadius+1.f)*(fabsf(m[0])+fabsf(m[1])),ry=(ringRadius+1.f)*(fabsf(m[4])+fabsf(m[5]));
 if(sx+rx<0||sx-rx>640||sy+ry<0||sy-ry>480)return 0;
 if(!*begun){spell_world_begin41();*begun=1;}
 float u=0,v=0;unsigned palette=0;for(;palette<sizeof(skinColors)/sizeof(skinColors[0]);palette++)if(skinColors[palette]==color)break;
 if(palette==sizeof(skinColors)/sizeof(skinColors[0]))fail("Portal palette color missing");hud_solid_uv(palette,&u,&v);
 uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,6);
 for(unsigned i=0;i<=32;i++)for(unsigned side=0;side<2;side++){
  float radius=ringRadius+(side?-.75f:.75f),xx=x+portalUnit52[i][0]*radius,yy=y+portalUnit52[i][1]*radius;
  world_project(m,xx,yy,z,&sx,&sy);float depth=m[8]*xx+m[9]*yy+m[10]*z+m[11]-16.f;
  p=vertex(p,sx,sy,depth,u,v);
 }
 p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);return 1;
}
static unsigned portal_draw52(const Combat*g,const float*m,unsigned map){
 if(map>=WORLD_MAP_COUNT)return 0;int begun=0;unsigned drawn=0;
 for(unsigned i=0;i<WORLD_GATE_COUNT;i++)if(worldGates[i].source==map&&world_gate_enabled64(i))drawn+=portal_marker52(m,worldGates[i].x,worldGates[i].y,12.f,(world_destination_ready44(worldGates[i].destination)&&world_gate_open199(i))?0xff65dffau:0xffff4848u,&begun);
 for(unsigned i=0;i<PENDING_WARP_COUNT;i++)if(pendingWarps[i].map==map)drawn+=portal_marker52(m,pendingWarps[i].x,pendingWarps[i].y,12.f,0xffff4848u,&begun);
 for(unsigned i=0;i<3;i++){const SkillPortal*w=g->portals+i;if(w->expires>g->time&&w->uses)drawn+=portal_marker52(m,w->x,w->y,6.f,0xff65dffau,&begun);}
 return drawn;
}
#endif
