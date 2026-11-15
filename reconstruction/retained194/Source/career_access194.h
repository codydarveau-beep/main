/* MIT. Access receipts come from the original career quests, not story grants. */
#ifndef MYRO_CAREER_ACCESS194_H
#define MYRO_CAREER_ACCESS194_H
#include "npc_variables55.h"

#define CAREER_PILGRIMAGE_KEY194 UINT64_C(0xeca1940070696c67)

static int career_pilgrimage194(const NpcState55*s){
 if(!s)return 0;

 const NpcVariable55*permit=
  npc_state_get55(s,CAREER_PILGRIMAGE_KEY194,0);

 if(permit&&permit->kind==NPC_STATE_NUMBER55&&permit->number==1)
  return 1;

 const NpcVariable55*v=
  npc_state_get55(s,npc_variable_key55("job_acolyte_q",0),0);

 if(v&&v->kind==NPC_STATE_NUMBER55&&
    (v->number==3||v->number==7))
  return 1;

 v=npc_state_get55(s,npc_variable_key55("PRIEST_Q",0),0);

 return v&&v->kind==NPC_STATE_NUMBER55&&
        (v->number==2||v->number==3);
}
#endif
