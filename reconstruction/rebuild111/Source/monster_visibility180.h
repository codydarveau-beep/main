#include "interior_rooms181.h"
/* MIT. Shared native/host selection: choose nearest on-screen eligible actors. */
#ifndef MYRO_MONSTER_VISIBILITY180_H
#define MYRO_MONSTER_VISIBILITY180_H
static int monster_select180(const Combat*g,const float*m,float focusX,float focusY,int*out,float(*height)(float,float)){
 int count=0;float distances[RENDER_MOBS];
 if(!g->peaceful)for(int i=0;i<MOB_COUNT;i++){
  const CombatMob*a=g->mobs+i;if(!a->enabled||(a->hidden&&!g->itemBonuses52.scalar[B52_bIntravision])||(a->hp<=0&&g->time-a->deadAt>1.2f))continue;
  if(!monster_visible52(g->monsterView52,a->x-focusX,a->y-focusY)||!rooms_point181(&interiorRooms181,a->x,a->y))continue;
  float z=height(a->x,a->y),px=m[0]*a->x+m[1]*a->y+m[3],py=m[4]*a->x+m[5]*a->y+m[6]*z+m[7];
  if(px< -100||px>740||py< -100||py>580)continue;
  float d=combat_dist(focusX,focusY,a->x,a->y);if(i==g->target)d=-1;
  int at=count;while(at>0&&distances[at-1]>d)at--;
  if(at>=RENDER_MOBS)continue;if(count<RENDER_MOBS)count++;
  for(int k=count-1;k>at;k--){out[k]=out[k-1];distances[k]=distances[k-1];}out[at]=i;distances[at]=d;
 }return count;
}
#endif
