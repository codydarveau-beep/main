/* GPL-3.0-or-later. Source Safety Wall cylinders, with native actor compositing. */
#include "safety_geometry50.h"
static void safety_draw50(const Combat*g,const float*m,int front){
 int begun=0;for(int i=0;i<3;i++)if(combat_safety_live(g,i)){const SafetyWall*w=&g->safety[i];if(w->x<8||w->y<8||w->x>=gw*8-8||w->y>=gh*8-8)continue;
 if(!begun){spell_world_begin41();uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);begun=1;}
 float fade=fminf(1,w->expires-g->time);field_bind48(8,(int)(6*fade+.5f),0);float z=height_at(w->x,w->y)+.12f;
 for(int n=0;n<3;n++){float angle=g->time+n,r=8*(.6f+n*.05f),h=8*(n==1?6:7);for(int f=0;f<20;f++){if(safety_actor_front52(m,w->x,w->y,g->x,g->y,angle,f)!=front)continue;float a=angle+f*6.2831853f/20,b=angle+(f+1)*6.2831853f/20;SpellPoint41 q[4]={{w->x+sinf(a)*r,w->y+cosf(a)*r,z},{w->x+sinf(a)*r,w->y+cosf(a)*r,z+h},{w->x+sinf(b)*r,w->y+cosf(b)*r,z+h},{w->x+sinf(b)*r,w->y+cosf(b)*r,z}};float u=f*64.f/20,v=(f+1)*64.f/20,uv[8]={u,64,u,0,v,0,v,64};field_quad48(m,q,uv);}}
 }
 if(begun){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);}
}
