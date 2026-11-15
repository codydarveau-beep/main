/* MIT. Original quest log semantics, independent of rendering and frame rate. */
#ifndef MYRO_NPC_QUESTS55_H
#define MYRO_NPC_QUESTS55_H
#include "npc_state55.h"
typedef struct{uint32_t mob,count,minLevel,maxLevel;int32_t size,race,element;const char*map;}NpcQuestTarget55;
typedef struct{uint32_t item,rate,mob;}NpcQuestDrop55;
typedef struct{uint32_t id,time,start,count,dropStart,dropCount;const char*name;}NpcQuestDefinition55;
typedef struct{uint32_t source,level;int32_t size,race,element;const char*map;}NpcQuestKill55;
#include "npc_quest_data55.h"
static const NpcQuestDefinition55*npc_quest_definition55(uint32_t id){uint32_t lo=0,hi=sizeof(npcQuestDefinitions55)/sizeof(*npcQuestDefinitions55);while(lo<hi){uint32_t mid=lo+(hi-lo)/2;if(npcQuestDefinitions55[mid].id<id)lo=mid+1;else hi=mid;}return lo<sizeof(npcQuestDefinitions55)/sizeof(*npcQuestDefinitions55)&&npcQuestDefinitions55[lo].id==id?npcQuestDefinitions55+lo:NULL;}
/* State values are stored plus one, reserving sparse zero for an absent quest. */
static int npc_quest_status55(const NpcState55*s,uint32_t id){int64_t n=npc_state_number55(s,id,0);return n>=1&&n<=3?(int)n-1:-1;}
static int npc_quest_validate55(const NpcState55*s){for(uint32_t i=0;i<s->count;i++){const NpcVariable55*v=s->entries+i;if(v->key>UINT32_MAX||v->kind!=NPC_STATE_NUMBER55||v->number<0)return 0;const NpcQuestDefinition55*d=npc_quest_definition55((uint32_t)v->key);if(!d||npc_quest_status55(s,d->id)<0||v->index>d->count+1)return 0;if(v->index>=2&&(uint64_t)v->number>npcQuestTargets55[d->start+v->index-2].count)return 0;}return 1;}
static int64_t npc_quest_deadline55(const NpcQuestDefinition55*d,int64_t now,int64_t override){if(override)return override;return d->time?(now>INT64_MAX-d->time?INT64_MAX:now+d->time):0;}
static int npc_quest_add55(NpcState55*s,uint32_t id,int64_t now,int64_t override){const NpcQuestDefinition55*d=npc_quest_definition55(id);if(!d||now<0||override<0||npc_quest_status55(s,id)>=0||!npc_state_reserve55(s,s->count+2))return 0;return npc_state_set_number55(s,id,0,2)&&npc_state_set_number55(s,id,1,npc_quest_deadline55(d,now,override));}
static int npc_quest_erase55(NpcState55*s,uint32_t id){int found;uint32_t at=npc_state_find55(s,id,0,&found);if(!found)return 0;while(at<s->count&&s->entries[at].key==id)if(!npc_state_set_number55(s,id,s->entries[at].index,0))return 0;return 1;}
static int npc_quest_change55(NpcState55*s,uint32_t oldId,uint32_t newId,int64_t now){const NpcQuestDefinition55*d=npc_quest_definition55(newId);int state=npc_quest_status55(s,oldId);if(!d||state<0||state>=2||npc_quest_status55(s,newId)>=0||now<0||!npc_state_reserve55(s,s->count+2))return 0;/* All following numeric writes fit preflighted capacity. */npc_quest_erase55(s,oldId);return npc_state_set_number55(s,newId,0,2)&&npc_state_set_number55(s,newId,1,npc_quest_deadline55(d,now,0));}
static int npc_quest_set_status55(NpcState55*s,uint32_t id,unsigned state){int current=npc_quest_status55(s,id);return state<=2&&current>=0&&current<2&&npc_state_set_number55(s,id,0,state+1);}
static int npc_quest_check55(const NpcState55*s,uint32_t id,unsigned type,int64_t now){int state=npc_quest_status55(s,id);if(state<0)return-1;if(type==0)return state;int64_t deadline=npc_state_number55(s,id,1);if(type==1)return deadline<now?2:state==2?1:0;if(type==2){if(state<2){const NpcQuestDefinition55*d=npc_quest_definition55(id);if(!d)return-1;uint32_t i;for(i=0;i<d->count;i++)if(npc_state_number55(s,id,i+2)<npcQuestTargets55[d->start+i].count)break;if(i==d->count)return 2;if(deadline<now)return 1;}return 0;}return-1;}
static int npc_quest_progress55(const NpcState55*s,uint32_t id,unsigned type,int64_t now){int result=npc_quest_check55(s,id,type,now);return result<0?0:result<=1?1:2;}
static int npc_quest_matches55(const NpcQuestTarget55*t,const NpcQuestKill55*k){return(!t->mob||t->mob==k->source)&&(!t->minLevel||t->minLevel<=k->level)&&(!t->maxLevel||t->maxLevel>=k->level)&&(t->size<0||t->size==k->size)&&(t->race<0||t->race==k->race)&&(t->element<0||t->element==k->element)&&(!*t->map||(k->map&&!strcmp(t->map,k->map)));}
/* Called on a credited kill, not per frame. Drops follow the source's unscaled quest rates. */
static int npc_quest_kill55(NpcState55*s,const NpcQuestKill55*k,uint32_t(*random10000)(void*),void(*giveItem)(void*,uint32_t),void*context){
 if(!s||!k)return 0;for(uint32_t at=0;at<s->count;at++){NpcVariable55 entry=s->entries[at];if(entry.index||entry.kind!=NPC_STATE_NUMBER55||entry.number!=2)continue;const NpcQuestDefinition55*d=npc_quest_definition55((uint32_t)entry.key);if(!d)return 0;
  if(!npc_state_reserve55(s,s->count+d->count))return 0;
  for(uint32_t j=0;j<d->count;j++){const NpcQuestTarget55*t=npcQuestTargets55+d->start+j;int64_t n=npc_state_number55(s,d->id,j+2);if(n<t->count&&npc_quest_matches55(t,k))if(!npc_state_set_number55(s,d->id,j+2,n+1))return 0;}
  if(random10000&&giveItem)for(uint32_t j=0;j<d->dropCount;j++){const NpcQuestDrop55*drop=npcQuestDrops55+d->dropStart+j;if((!drop->mob||drop->mob==k->source)&&random10000(context)%10000<drop->rate)giveItem(context,drop->item);}
 }return 1;
}
#endif
