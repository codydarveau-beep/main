/* MIT. One-player job-exam waiting rooms, retaining source capacities/events. */
#ifndef MYRO_NPC_WAITING55_H
#define MYRO_NPC_WAITING55_H
#define NPC_WAITING_LIMIT55 64u
typedef struct{unsigned npc,eventNpc,eventEntry,capacity,trigger,enabled,joined,pending,fee64,minLevel64,maxLevel64;char title[96];}NpcWaitingRoom55;
typedef struct{NpcWaitingRoom55 rooms[NPC_WAITING_LIMIT55];unsigned count;}NpcWaiting55;
static NpcWaitingRoom55*npc_waiting_find55(NpcWaiting55*s,unsigned npc){for(unsigned i=0;i<s->count;i++)if(s->rooms[i].npc==npc)return s->rooms+i;return NULL;}
#endif
