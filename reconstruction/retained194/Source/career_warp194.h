/* MIT. Existing Ninja quest travel uses its classroom while regions are locked.
 * The original script has already checked level/consent/materials. Only its
 * destination changes; no item, quest, promotion or reward is fabricated. */
#ifndef MYRO_CAREER_WARP194_H
#define MYRO_CAREER_WARP194_H
#include "npc_world55.h"
#include "career_access194.h"

static int npc_career_world194(
 NpcWorld55*w,NpcMachine55*m,int attached,unsigned program,
 NpcState55*state,const char*command,const NpcValue55*args,
 uint32_t count,NpcValue55*out
){
 if(attached&&program==3821&&!strcmp(command,"savepoint")&&count==3){
  NpcValue55 destination;
  int64_t x,y;

  if(!npc_world_args55(m,args,&destination,&x,&y))
   return N55_ERROR;

  if(!strcmp(destination.text,"moc_fild07")){
   if(!career_pilgrimage194(state))
    return N55_ERROR;

   WorldPosition home=w->game->home;
   int status=
    npc_world_command55(w,m,attached,command,args,count,out);

   if(status==N55_READY&&
      !npc_state_set_number55(state,CAREER_PILGRIMAGE_KEY194,0,1)){
    w->game->home=home;
    return N55_ERROR;
   }

   return status;
  }
 }

 int ninja=program==3884||program==3885||program==3886;
 int valkyrie=program==3604;

 if(attached&&
    ((ninja&&!strcmp(command,"warp"))||
     (valkyrie&&
      (!strcmp(command,"warp")||!strcmp(command,"savepoint"))))&&
    count>=3&&count<=4){

  NpcValue55 destination;
  int64_t sourceX,sourceY;

  if(!npc_world_args55(m,args,&destination,&sourceX,&sourceY))
   return N55_ERROR;

  if(destination.kind==N55_STRING_KIND&&
     ((ninja&&!strcmp(destination.text,"amatsu"))||
      (valkyrie&&!strcmp(destination.text,"morocc")))){

   NpcValue55 adjusted[4];
   memcpy(adjusted,args,count*sizeof(*args));

   adjusted[0]=npc_vm_string55(ninja?"que_ng":"moc_ruins");
   adjusted[1]=npc_vm_number55(ninja?37:150);
   adjusted[2]=npc_vm_number55(ninja?68:117);

   return npc_world_command55(
    w,m,attached,command,adjusted,count,out);
  }
 }

 return npc_world_command55(
  w,m,attached,command,args,count,out);
}
#endif
