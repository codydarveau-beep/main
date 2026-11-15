/* GPL-3.0-or-later. Textured native Ice Wall geometry. Integer texture/register sizes. */
#include "ice_texture48.h"
#include "ice_geometry48.h"
static void*iceTexture48;
static void ice_draw48(const Combat*g,const float*m){int any=0;for(int i=0;i<3;i++)if(g->classAreas48[i].id==89&&g->classAreas48[i].until>g->time&&g->classAreas48[i].map==g->mapId)any=1;if(!any)return;
 if(!iceTexture48){iceTexture48=gpu_alloc(65536);unsigned char*raw=inflateasset("Ice Wall texture",iceTexturePacked48,sizeof(iceTexturePacked48),65536);memcpy(iceTexture48,raw,65536);free(raw);}
 spell_world_begin41();bindTexture(iceTexture48,128u,128u,512u,0x0001122au);uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_DEPTH_MASK,1);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_FUNC,0x204);p=pb_push1(p,NV097_SET_ALPHA_REF,16);pb_end(p);
 for(int i=0;i<3;i++){const ClassArea48*a=&g->classAreas48[i];if(a->id!=89||a->until<=g->time||a->map!=g->mapId)continue;float sx,sy;world_project(m,a->x,a->y,height_at(a->x,a->y),&sx,&sy);if(sx< -120||sx>760||sy< -160||sy>640)continue;float age=g->time-(a->until-classDuration48[0][a->rank-1]/1000.f);
 for(int cell=0;cell<5;cell++){if(a->hp[cell]<=0)continue;float x=a->x+(a->axis?0:(cell-2)*8),y=a->y+(a->axis?(cell-2)*8:0);if(x<8||y<8||x>=gw*8-8||y>=gh*8-8)continue;for(int horn=0;horn<3;horn++)for(int side=0;side<4;side++){SpellPoint41 q[3];float uv[6];ice_face48(x,y,height_at(x,y),i*1009+cell*103+g->mapId*19,horn,side,age,q,uv);p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,5);for(int v=0;v<3;v++){world_project(m,q[v].x,q[v].y,q[v].z,&sx,&sy);float depth=m[8]*q[v].x+m[9]*q[v].y+m[10]*q[v].z+m[11]-WORLD_SPRITE_BIAS*2;p=vertex(p,sx,sy,depth,uv[v*2],uv[v*2+1]);}p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);}}}
 p=pb_begin();p=pb_push1(p,NV097_SET_DEPTH_MASK,0);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);pb_end(p);
}
