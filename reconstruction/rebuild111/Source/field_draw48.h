#include "effect_cache171.h"
/* GPL-3.0-or-later. Source PropertyGround, LPEffect and Cylinder geometry.
 * roBrowserLegacy 2dc0d1538edbb2a35f06b184552d8579d27b6639.
 * Fixed opacity levels avoid rewriting textures still in use by the GPU.
 */
#include "field_textures48.h"
static void*fieldTextures48[FIELD_TEXTURE_COUNT50][16][2];
static void field_bind48(int index,int level,int threshold){if(level<1)level=1;if(level>15)level=15;unsigned side=fieldTexDefs48[index].side,bytes=side*side*4;void**slot=&fieldTextures48[index][level][threshold];if(effect_cache_prepare171(slot,bytes)){unsigned char*raw=inflateasset("Class field texture",fieldTexDefs48[index].p,fieldTexDefs48[index].packed,bytes);for(unsigned p=0;p<bytes;p+=4){if(threshold&&(raw[p]<128||raw[p+1]<128||raw[p+2]<128))raw[p+3]=0;else if(threshold)raw[p+3]=raw[p+3]?17*level:0;else raw[p+3]=raw[p+3]*level/15;}memcpy(*slot,raw,bytes);free(raw);}bindTexture(*slot,side,side,side*4u,0x0001122au);}
static void field_quad48(const float*m,const SpellPoint41*q,const float*uv){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,8);for(int i=0;i<4;i++){float sx,sy;world_project(m,q[i].x,q[i].y,q[i].z,&sx,&sy);float depth=m[8]*q[i].x+m[9]*q[i].y+m[10]*q[i].z+m[11]-WORLD_SPRITE_BIAS*2;p=vertex(p,sx,sy,depth,uv[i*2],uv[i*2+1]);}p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);}
static void field_cylinder48(const float*m,float x,float y,float radius,float top,float h,float angle,int sides,int stagger){if(x<40||y<40||x>=gw*8-40||y>=gh*8-40)return;float z=height_at(x,y)+.12f;for(int i=0;i<sides;i++){float a=angle+i*6.2831853f/sides,b=angle+(i+1)*6.2831853f/sides,d=stagger?3.1415927f/sides:0;SpellPoint41 q[4]={{x+sinf(a)*radius,y+cosf(a)*radius,z},{x+sinf(a+d)*top,y+cosf(a+d)*top,z+h},{x+sinf(b+d)*top,y+cosf(b+d)*top,z+h},{x+sinf(b)*radius,y+cosf(b)*radius,z}};float u=i*64.f/sides,v=(i+1)*64.f/sides,uv[8]={u,64,u,0,v,0,v,64};field_quad48(m,q,uv);}}
#include "grandcross_geometry52.h"
static void grandcross_cylinder52(const float*m,float x,float y,const GrandCylinder52*c,float age){
 x+=c->x;y+=c->y;if(x<8||y<8||x>=gw*8-8||y>=gh*8-8)return;float z=height_at(x,y)+.12f;
 for(int i=0;i<c->sides;i++){float a=c->angle+i*6.2831853f/c->total,b=c->angle+(i+1)*6.2831853f/c->total;SpellPoint41 q[4]={{x+sinf(a)*c->r,y+cosf(a)*c->r,z},{x+sinf(a)*c->top,y+cosf(a)*c->top,z+c->h*age},{x+sinf(b)*c->top,y+cosf(b)*c->top,z+c->h*age},{x+sinf(b)*c->r,y+cosf(b)*c->r,z}};float u=i*64.f/c->total,v=(i+1)*64.f/c->total,uv[8]={u,64,u,0,v,0,v,64};field_quad48(m,q,uv);}
}
static float field_fade48(float age,float duration){if(age<0||age>=duration)return 0;float phase=age/duration;return phase<.25f?phase*4:phase>.75f?(1-phase)*4:1;}
#include "safety_draw50.h"
#include "classic_field49.h"
#include "lockon_draw49.h"
static void field_draw48(const Combat*g,const Art39State*s,const float*m){
 int begun=0;for(int i=0;i<3;i++){const ClassArea48*a=&g->classAreas48[i];if(a->id<101||a->id>104||a->until<=g->time||a->map!=g->mapId)continue;float sx,sy;world_project(m,a->x,a->y,height_at(a->x,a->y),&sx,&sy);if(sx< -140||sx>780||sy< -180||sy>660)continue;if(!begun){spell_world_begin41();begun=1;}
 if(a->id<104){field_bind48(a->id-101,6,1);for(int yy=-3;yy<=3;yy++)for(int xx=-3;xx<=3;xx++){unsigned local=(yy+3)*7+xx+3;if(a->id==102&&(a->waterUsed49[local/32]&(1u<<(local%32))))continue;unsigned cell=i*49+local;float mult=sinf(g->time*1000/(360*3.1415927f)+ice_unit48(cell+409)*10);if(mult<.5f)mult=.5f;field_cylinder48(m,a->x+xx*8,a->y+yy*8,8*mult,24*mult,16,(cell%16)*.39269908f+g->time*2.18166156f,20,1);}}

 else{field_bind48(4,10,1);int extent=2+(a->rank+1)/2;for(int yy=-extent;yy<=extent;yy++)for(int xx=-extent;xx<=extent;xx++){float x=a->x+xx*8,y=a->y+yy*8;if(x<8||y<8||x>=gw*8-8||y>=gh*8-8)continue;float r=8*(.8f+.05f*sinf(((xx+yy)&1)*3.1415927f+g->time*1000/(540*3.1415927f))),z=height_at(x,y)+.15f;SpellPoint41 q[4]={{x-r,y-r,z},{x+r,y-r,z},{x+r,y+r,z},{x-r,y+r,z}};float uv[8]={0,0,128,0,128,128,0,128};field_quad48(m,q,uv);}}
 }
 for(int i=0;i<ART39_EVENTS;i++){const Art39Event*e=&s->events[i];float age=g->time-e->at;if(age<0||age>=3||(e->skill!=119&&e->skill!=124&&e->skill!=121))continue;if(!begun){spell_world_begin41();begun=1;}if(e->skill==121){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);for(int pulse=0;pulse<3;pulse++){float t=age-pulse*.5f,fade=field_fade48(t,1);if(fade<=0)continue;field_bind48(0,(int)(1.5f*fade+.5f),0);for(unsigned cell=0;cell<sizeof(grandCylinders52)/sizeof(*grandCylinders52);cell++)grandcross_cylinder52(m,e->x,e->y,grandCylinders52+cell,t);}p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);}
 else{float fade=field_fade48(age,3);if(fade>0){field_bind48(e->skill==119?2:3,(int)(9*fade+.5f),0);field_cylinder48(m,g->x,g->y,12,12,80*fminf(1,age),g->time,20,0);}}
 }
 classic_field49(g,s,m);lockon_draw49(g,m);
}
