/* MIT. Original quest command adapter. Returns -1 for another subsystem. */
#ifndef MYRO_NPC_QUEST_COMMANDS55_H
#define MYRO_NPC_QUEST_COMMANDS55_H
#include "npc_vm55.h"
#include "npc_quests55.h"
static int npc_quest_command55(NpcMachine55*m,NpcState55*state,int64_t now,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 int action=!strcmp(name,"setquest")?1:!strcmp(name,"erasequest")?2:!strcmp(name,"completequest")?3:!strcmp(name,"changequest")?4:!strcmp(name,"questprogress")?5:!strcmp(name,"checkquest")?6:!strcmp(name,"questactive")?7:0;if(!action)return-1;
 if(!count||count>2||((action==4)&&count!=2)||((action==7)&&count!=1))return 0;
 int64_t first,second=0;if(!npc_vm_integer55(m,args[0],&first)||first<=0||first>UINT32_MAX)return 0;if(count==2&&!npc_vm_integer55(m,args[1],&second))return 0;
 *out=npc_vm_number55(0);
 if(action==1){if(second<0||!npc_quest_definition55((uint32_t)first))return 0;if(npc_quest_status55(state,(uint32_t)first)>=0)return 1;return npc_quest_add55(state,(uint32_t)first,now,second);}
 if(action==4){if(second<=0||second>UINT32_MAX||!npc_quest_definition55((uint32_t)second))return 0;if(npc_quest_status55(state,(uint32_t)first)<0||npc_quest_status55(state,(uint32_t)first)>=2||npc_quest_status55(state,(uint32_t)second)>=0)return 1;return npc_quest_change55(state,(uint32_t)first,(uint32_t)second,now);}
 if(action==5||action==6){if(second<0||second>2)return 0;*out=npc_vm_number55(action==5?npc_quest_progress55(state,(uint32_t)first,(unsigned)second,now):npc_quest_check55(state,(uint32_t)first,(unsigned)second,now));return 1;}
 if(action==7){*out=npc_vm_number55(npc_quest_status55(state,(uint32_t)first)==1);return 1;}
 /* The original two-ID command range excludes its upper endpoint. */
 if(count==2){if(second<first||second>UINT32_MAX)return 0;}else second=first+1;
 for(uint32_t at=0;at<state->count;){NpcVariable55 entry=state->entries[at];if(entry.index||entry.key<(uint64_t)first||entry.key>=(uint64_t)second){at++;continue;}if(action==2)npc_quest_erase55(state,(uint32_t)entry.key);else{npc_quest_set_status55(state,(uint32_t)entry.key,2);at++;}}return 1;
}
#endif
