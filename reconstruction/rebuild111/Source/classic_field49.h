/* GPL-3.0-or-later. Source EF79/142/312/315/336 geometry parameters.
 * Pure draw functions; no random-number mutation or combat state writes.
 */
static void classic_horn49(const float*m,float x,float y,unsigned seed,float age,int drive){
 if(age<0||age>=1||x<8||y<8||x>=gw*8-8||y>=gh*8-8)return;
 float h=(drive?.75f:.95f)+ice_unit48(seed)*.45f,s=(.4f+ice_unit48(seed+1)*.3f)*8;
 float rise=fminf(1,age/(drive?.25f:.12f));if(age>.75f)rise*=fmaxf(0,(1-age)/.25f);h*=rise*8;
 float z=height_at(x,y)-.8f,a=ice_unit48(seed+2)*6.2831853f,c=cosf(a),sn=sinf(a),ox=x+1.6f,oy=y+1.6f;
 static const float corners[4][2]={{-1,1},{1,1},{1,-1},{-1,-1}};
 static const float tex[4][8]={{0,0,128,0,128,128,128,128},{0,0,128,128,0,128,0,128},{128,0,128,128,0,128,0,128},{128,0,0,128,0,0,0,0}};
 for(int face=0;face<4;face++){SpellPoint41 q[4]={{ox,oy,z+2*h}};for(int v=1;v<3;v++){int k=(face+v-1)&3;float ax=corners[k][0]*s,ay=corners[k][1]*s;q[v]=(SpellPoint41){ox+c*ax-sn*ay,oy+sn*ax+c*ay,z};}q[3]=q[2];field_quad48(m,q,tex[face]);}
}
static void classic_guard49(const Combat*g,const float*m,float age){
 float fade=field_fade48(age,.6f);if(fade<=0)return;field_bind48(6,(int)(9*fade+.5f),0);float angle=atan2f(g->faceX,g->faceY)+1.9634954f;
 for(int layer=0;layer<2;layer++)for(int i=0;i<5;i++){float a=angle+i*.78539816f,b=a+.78539816f,z=height_at(g->x,g->y)+8*(layer?1:2.14f),top=layer?12:8,h=8*(layer?1.14f:.7f);SpellPoint41 q[4]={{g->x+sinf(a)*12,g->y+cosf(a)*12,z},{g->x+sinf(a)*top,g->y+cosf(a)*top,z+h},{g->x+sinf(b)*top,g->y+cosf(b)*top,z+h},{g->x+sinf(b)*12,g->y+cosf(b)*12,z}};float uv[8]={0,64,0,0,64,0,64,64};field_quad48(m,q,uv);}
}
#include "class_field50.h"
static void classic_field49(const Combat*g,const Art39State*s,const float*m){
 safety_draw50(g,m,0);
 spell_world_begin41();uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);
 class_field_draw50(g,s,m);classic_guard49(g,m,g->time-g->guardFxAt49);
 for(int i=0;i<ART39_EVENTS;i++){const Art39Event*e=&s->events[i];float age=g->time-e->at;if(e->skill!=10||age<0||age>=1.5f)continue;field_bind48(5,(int)(3*field_fade48(age,1.5f)+.5f),0);for(int n=0;n<2;n++)field_cylinder48(m,g->x,g->y,8*(.95f+n*.05f),8*(.95f+n*.05f),64*fminf(1,age/.3f),g->time+n,20,0);}
 p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);
 for(int i=0;i<ART39_EVENTS;i++){const Art39Event*e=&s->events[i];float age=g->time-e->at;if((e->skill!=4&&e->skill!=81)||age<0||age>=1)continue;field_bind48(7,15,0);if(e->skill==4)for(int y=-2;y<=2;y++)for(int x=-2;x<=2;x++)classic_horn49(m,e->x+x*8,e->y+y*8,(y+2)*5+x+2,age,1);else for(int n=0;n<3;n++)classic_horn49(m,e->x+(n-1)*3,e->y,71+n,age,0);}
}
