/* MIT. Inspect original SELECT ordinals before native fees/quest mutations.
 * Reads character-temp arrays directly: no VM evaluation, allocation or write. */
#ifndef MYRO_NPC_TRAVEL_PREFLIGHT194_H
#define MYRO_NPC_TRAVEL_PREFLIGHT194_H
#include "npc_travel_data194.h"
static int npc_travel_label194(const char*label,unsigned*out){
 for(unsigned i=0;i<sizeof(npcTravelRoutes194)/sizeof(*npcTravelRoutes194);i++)
  if(!strcmp(label,npcTravelRoutes194[i].label)){*out=npcTravelRoutes194[i].map;return 1;}
 return 0;
}
static int npc_travel_temp194(NpcRuntime55*r,const char*name,unsigned index,NpcValue55*out){
 NpcValue55 ref={0};ref.kind=N55_REFERENCE_KIND;ref.text=name;
 ref.index=index;ref.owner=r->machine.owner;ref.frame=r->machine.frame;
 return npc_variable_read55(&r->variables,&ref,out)&&out->kind==N55_STRING_KIND;
}
static int npc_travel_preflight194(Combat*game,NpcRuntime55*r,NpcWorld55*world,
 unsigned choice,char*error,size_t errorBytes){
 if(!game||!r||!world||!error||!errorBytes)return 0;
 unsigned mode=r->dialogue.mode;
 if(mode!=N55_DIALOGUE_SELECT&&mode!=N55_DIALOGUE_PROMPT)return 1;
 if(!r->attached||r->machine.status!=N55_WAIT||choice>=r->dialogue.count)return 0;
 const NpcProgram55*program=r->machine.program;if(!program)return 0;
 unsigned ordinal=r->dialogue.ordinals[choice],destination=0;
 const char*label=r->dialogue.options+r->dialogue.offsets[choice];
 int managed=0;
 if(program->owner==npcProgramFiles55[843].owner){
  managed=1;NpcValue55 display,target;
  if(!ordinal||!npc_travel_temp194(r,"@wrpC$",ordinal-1,&display)||
     !npc_travel_temp194(r,"@wrpD$",ordinal-1,&target))goto unavailable;
  if(!strcmp(display.text,"Cancel")){error[0]=0;return 1;}
  if(!*display.text||!*target.text||!npc_travel_label194(target.text,&destination))goto unavailable;
 }else if(program->owner==npcProgramFiles55[695].owner&&r->machine.pc==85){
  managed=1;if(!strcmp(label,"Cancel")){error[0]=0;return 1;}
  if(!npc_travel_label194(label,&destination))goto unavailable;
 }else if(program->owner==npcProgramFiles55[3603].owner&&r->machine.pc==68){
  managed=1;if(!npc_travel_label194(label,&destination))goto unavailable;
  if(destination==127)destination=126; /* Same remap as career_warp194.h. */
 }else if(program->owner==npcProgramFiles55[3865].owner&&
          (r->machine.pc==164||r->machine.pc==442)){
  managed=1;
  if(!strcmp(label,"Field Combat Course")){
   int map=npc_world_map55(world,"new_1-2");if(map<0)goto unavailable;destination=(unsigned)map;
  }else if(!npc_travel_label194(label,&destination))goto unavailable;
 }
 if(!managed)return 1;
 if(!npcTravelAdmission194)goto unavailable;
 const char*reason=npcTravelAdmission194(game,destination);
 if(reason){snprintf(error,errorBytes,"%s",reason);return 0;}
 error[0]=0;return 1;
unavailable:
 snprintf(error,errorBytes,"This destination could not be verified. Travel was not applied.");return 0;
}
#endif
