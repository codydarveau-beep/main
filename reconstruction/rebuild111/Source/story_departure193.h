/* MIT. Reconstructed first-departure redirect; ordinary NPC quests stay intact. */
#ifndef MYRO_STORY_DEPARTURE193_H
#define MYRO_STORY_DEPARTURE193_H
#include "campaign_state200.h"
static int campaign_sandbox193(const NpcState55*s){
 /* Reconstructed key. Never infer conversion from an unlocked developer menu. */
 return s&&npc_state_number55(s,UINT64_C(0xeca1930073616e64),0)==1;
}
static int story_departure_maps193(unsigned from,unsigned destination){
 if(from>=MYRO_MAP_COUNT43||strncmp(mapNames[from],"new_",4))return 0;
 if(destination>=MYRO_MAP_COUNT43)return 0;
 const char*n=mapNames[destination];
 return !strcmp(n,"prontera")||!strcmp(n,"morocc")||!strcmp(n,"payon")||
  !strcmp(n,"alberta")||!strcmp(n,"geffen");
}
static int story_departure193(const NpcState55*s,unsigned from,unsigned destination){
 Campaign200 c;
 return !campaign_sandbox193(s)&&campaign_load200(s,&c)==1&&
  !c.cursor&&!c.checkpoint&&!c.route&&story_departure_maps193(from,destination);
}
#endif
