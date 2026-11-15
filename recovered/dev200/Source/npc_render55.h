/* MIT. Eight visible original NPC poses; independently bounded compressed cache. */
#ifndef MYRO_NPC_RENDER55_H
#define MYRO_NPC_RENDER55_H
#include "npc_procedural180.h"
#include "npc_direction191.h"
#define SCRIPT_NPC_SLOTS55 8u
#define SCRIPT_NPC_KIND55 (MOB_SPEC_COUNT+10)
#define SCRIPT_NPC_TEXTURE55 (RENDER_MOBS+16)
#include "npc_visibility180.h"
static SparseSprite scriptNpcSprites55[SCRIPT_NPC_SLOTS55];
static unsigned scriptNpcFrames55[SCRIPT_NPC_SLOTS55];
static int scriptNpcRecords55[SCRIPT_NPC_SLOTS55],scriptNpcModels55[SCRIPT_NPC_SLOTS55];
static int scriptNpcReady55;
static void npc_render_release171(void){for(unsigned i=0;i<SCRIPT_NPC_SLOTS55;i++){unsigned slot=SCRIPT_NPC_TEXTURE55+i;free(scriptNpcSprites55[i].raw);memset(scriptNpcSprites55+i,0,sizeof(SparseSprite));scriptNpcFrames55[i]=UINT32_MAX;scriptNpcRecords55[i]=scriptNpcModels55[i]=-1;uploadedSource[slot]=NULL;uploadedFrames[slot]=UINT32_MAX;}scriptNpcReady55=1;}
static float npc_actor_scale55(int kind,float zoom){if(kind>=SCRIPT_NPC_KIND55&&kind<SCRIPT_NPC_KIND55+SCRIPT_NPC_SLOTS55){int model=scriptNpcModels55[kind-SCRIPT_NPC_KIND55];if(model>=0&&npcModels55[model].scale>0)return zoom/(3.f*npcModels55[model].scale);}return zoom/3.f;}
static void npc_render_actors55(const Combat*game,const float*matrix,float co,float si,DrawActor*actors,int*count){if(!scriptNpcReady55){for(unsigned i=0;i<SCRIPT_NPC_SLOTS55;i++){scriptNpcFrames55[i]=UINT32_MAX;scriptNpcRecords55[i]=scriptNpcModels55[i]=-1;}scriptNpcReady55=1;}if(game->mapId>=MYRO_MAP_COUNT43)return;
 int nearest[SCRIPT_NPC_SLOTS55];npc_select180(&npcGame55.scene,game,matrix,nearest,height_at);
 for(unsigned slot=0;slot<SCRIPT_NPC_SLOTS55;slot++){int id=nearest[slot];unsigned texture=SCRIPT_NPC_TEXTURE55+slot;if(id<0){if(scriptNpcSprites55[slot].raw){while(pb_busy()){}free(scriptNpcSprites55[slot].raw);memset(scriptNpcSprites55+slot,0,sizeof(SparseSprite));uploadedSource[texture]=NULL;uploadedFrames[texture]=UINT32_MAX;scriptNpcFrames55[slot]=UINT32_MAX;}scriptNpcRecords55[slot]=scriptNpcModels55[slot]=-1;continue;}
  const NpcRecord55*r=npcRecords55+id;float px64=npc_scene_x64(&npcGame55.scene,id),py64=npc_scene_y64(&npcGame55.scene,id);int model=npc_scene_model55(&npcGame55.scene,(unsigned)id);unsigned direction=npc_direction191(npc_scene_direction55(&npcGame55.scene,(unsigned)id),co,si);direction=npc_proc_direction180(&npcGame55,NPC_ENTITY_BASE55+id+1,0,direction);uint64_t elapsed=(uint64_t)(game->time*1000.f)+(uint64_t)id*17;unsigned frame=npc_disc_pose55((unsigned)model,direction,elapsed);if(frame>=NPC_FRAME_COUNT55)fail("Invalid NPC pose index");
  if(scriptNpcFrames55[slot]!=frame){const NpcArtFrame55*f=npcFrames55+frame;const unsigned char*packed=npc_disc_art55(&npcGame55.disc,frame);if(!packed)fail("NPC pose data missing or corrupt");while(pb_busy()){}free(scriptNpcSprites55[slot].raw);memset(scriptNpcSprites55+slot,0,sizeof(SparseSprite));sprite_load(scriptNpcSprites55+slot,"NPC pose",packed,f->packed,f->raw);scriptNpcFrames55[slot]=frame;uploadedSource[texture]=NULL;uploadedFrames[texture]=UINT32_MAX;}
  scriptNpcRecords55[slot]=id;scriptNpcModels55[slot]=model;float z=height_at(px64,py64),x=matrix[0]*px64+matrix[1]*py64+matrix[3],y=matrix[4]*px64+matrix[5]*py64+matrix[6]*z+matrix[7],depth=matrix[8]*px64+matrix[9]*py64+matrix[10]*z+matrix[11]-WORLD_SPRITE_BIAS;actors[(*count)++]=(DrawActor){(int)texture,(int)(SCRIPT_NPC_KIND55+slot),0,x,y,depth,y};
 }
}
#endif
