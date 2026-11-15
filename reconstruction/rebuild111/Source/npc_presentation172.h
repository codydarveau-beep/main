/* MIT. Fixed-size cosmetic requests; separate from quest/combat state. */
#ifndef MYRO_NPC_PRESENTATION172_H
#define MYRO_NPC_PRESENTATION172_H
#define NPC_VISUAL_CAP172 32u
#define NPC_VISUAL_TTL172 30000u
#define NPC_MOB_ENTITY172 2000000u
enum{NPC_VISUAL_EMOTE172=1,NPC_VISUAL_EFFECT172=2};
typedef struct{uint32_t kind,id,entity,life,map;uint64_t created;float fixedX180,fixedY180,fixedZ180;unsigned positioned180,processed180;}NpcVisual172;
typedef struct{NpcVisual172 events[NPC_VISUAL_CAP172];unsigned next,dropped;}NpcPresentation172;
static void npc_visual_queue172(NpcPresentation172*p,unsigned kind,unsigned id,unsigned entity,unsigned life,unsigned map,uint64_t ms){if(!entity)return;if(kind==NPC_VISUAL_EMOTE172)for(unsigned i=0;i<NPC_VISUAL_CAP172;i++)if(p->events[i].kind==kind&&p->events[i].entity==entity&&p->events[i].map==map){p->events[i]=(NpcVisual172){kind,id,entity,life,map,ms};return;}unsigned slot=NPC_VISUAL_CAP172;for(unsigned i=0;i<NPC_VISUAL_CAP172;i++)if(!p->events[i].kind||ms-p->events[i].created>=NPC_VISUAL_TTL172){slot=i;break;}if(slot==NPC_VISUAL_CAP172){slot=p->next++%NPC_VISUAL_CAP172;p->dropped++;}p->events[slot]=(NpcVisual172){kind,id,entity,life,map,ms};}
#endif
