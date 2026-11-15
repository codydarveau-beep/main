#include "interior_rooms181.h"
/* MIT. Same eight nearest source NPCs used by the actual sprite renderer. */
#ifndef MYRO_NPC_VISIBILITY180_H
#define MYRO_NPC_VISIBILITY180_H
static unsigned npc_select180(const NpcScene55*s,const Combat*game,const float*matrix,int*nearest,float(*height)(float,float)){
 float distances[SCRIPT_NPC_SLOTS55];for(unsigned i=0;i<SCRIPT_NPC_SLOTS55;i++){nearest[i]=-1;distances[i]=1e30f;}if(game->mapId>=MYRO_MAP_COUNT43)return 0;
 unsigned start=npcMapSpans55[game->mapId].start,n=npcMapSpans55[game->mapId].count,selected=0;
 for(unsigned j=0;j<n;j++){unsigned id=npcMapRecords55[start+j];const NpcRecord55*r=npcRecords55+id;float px=npc_scene_x64(s,id),py=npc_scene_y64(s,id);
  if(!rooms_point181(&interiorRooms181,px,py)||!npc_scene_available64(s,id)||(r->flags&2)||(s->flags[id]&(N55_NPC_DISABLED|N55_NPC_HIDDEN|N55_NPC_CORE))||npc_scene_model55(s,id)<0||!monster_visible52(npcView64,px-game->x,py-game->y))continue;
  float z=height(px,py),x=matrix[0]*px+matrix[1]*py+matrix[3],y=matrix[4]*px+matrix[5]*py+matrix[6]*z+matrix[7];if(x< -80||x>720||y< -160||y>560)continue;
  float dx=px-game->x,dy=py-game->y,d=dx*dx+dy*dy;
  for(unsigned k=0;k<SCRIPT_NPC_SLOTS55;k++)if(d<distances[k]){for(unsigned t=SCRIPT_NPC_SLOTS55-1;t>k;t--){distances[t]=distances[t-1];nearest[t]=nearest[t-1];}distances[k]=d;nearest[k]=(int)id;if(selected<SCRIPT_NPC_SLOTS55)selected++;break;}
 }return selected;
}
#endif
