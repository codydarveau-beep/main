/* MIT. Original quest log plus independent per-character HUD tracking. */
#ifndef MYRO_QUEST_JOURNAL65_H
#define MYRO_QUEST_JOURNAL65_H
#include "npc_quests55.h"
#include "npc_variables55.h"
#include "campaign_state200.h"
#include "campaign_data200.h"
typedef struct{uint32_t id;const char*title,*description,*summary;}QuestText65;
#include "quest_journal_data65.h"
static NpcState55 *questLog65,*questPins65;
static void(*campaignSessionReset200)(void);
static unsigned alwaysShowQuests65=1;
static uint32_t questIDs65[sizeof(npcQuestDefinitions55)/sizeof(*npcQuestDefinitions55)],questRevision65;static unsigned questCached65,questCacheValid65;
static void quest_journal_bind65(NpcState55*log,NpcState55*pins){if(campaignSessionReset200)campaignSessionReset200();questLog65=log;questPins65=pins;questCacheValid65=0;}
static const QuestText65*quest_text65(uint32_t id){unsigned lo=0,hi=sizeof(questTexts65)/sizeof(*questTexts65);while(lo<hi){unsigned mid=lo+(hi-lo)/2;if(questTexts65[mid].id<id)lo=mid+1;else hi=mid;}return lo<sizeof(questTexts65)/sizeof(*questTexts65)&&questTexts65[lo].id==id?questTexts65+lo:NULL;}
static void quest_refresh65(void){if(questCacheValid65&&questLog65&&questRevision65==questLog65->revision)return;questCached65=0;questCacheValid65=1;questRevision65=questLog65?questLog65->revision:0;if(!questLog65)return;for(unsigned i=0;i<questLog65->count;i++){const NpcVariable55*v=questLog65->entries+i;if(v->index||v->key>UINT32_MAX||v->kind!=NPC_STATE_NUMBER55||v->number<1||v->number>2||!npc_quest_definition55((uint32_t)v->key))continue;if(questCached65<sizeof(questIDs65)/sizeof(*questIDs65))questIDs65[questCached65++]=(uint32_t)v->key;}}
static int quest_campaign200(Campaign200*c){return questPins65&&campaign_load200(questPins65,c)==1;}
static uint32_t quest_at65(unsigned ordinal){quest_refresh65();Campaign200 c;if(quest_campaign200(&c)){if(!ordinal)return CAMPAIGN_QUEST200;ordinal--;}return ordinal<questCached65?questIDs65[ordinal]:0;}
static unsigned quest_count65(void){quest_refresh65();Campaign200 c;return questCached65+(quest_campaign200(&c)?1u:0u);}
static uint64_t quest_pin_key65(uint32_t id){char name[48];snprintf(name,sizeof(name),"myro_quest_track65_%u",id);return npc_variable_key55(name,0);}
static int quest_tracked65(uint32_t id){if(id==CAMPAIGN_QUEST200){Campaign200 c;return quest_campaign200(&c)&&c.cursor<36&&npc_state_number55(questPins65,quest_pin_key65(id),0)!=2;}return questLog65&&questPins65&&npc_quest_status55(questLog65,id)>=0&&npc_quest_status55(questLog65,id)<2&&npc_state_number55(questPins65,quest_pin_key65(id),0)==1;}
static int quest_toggle65(uint32_t id){if(id==CAMPAIGN_QUEST200){Campaign200 c;if(!quest_campaign200(&c)||c.cursor==36)return 0;return npc_state_set_number55(questPins65,quest_pin_key65(id),0,quest_tracked65(id)?2:0);}if(!questPins65||!questLog65||!npc_quest_definition55(id)||npc_quest_status55(questLog65,id)<0||npc_quest_status55(questLog65,id)>=2)return 0;return npc_state_set_number55(questPins65,quest_pin_key65(id),0,quest_tracked65(id)?0:1);}
/* Only source-defined counters produce a bar; dialogue quests never show invented progress. */
static int quest_progress65(uint32_t id,uint64_t*done,uint64_t*total){*done=*total=0;if(id==CAMPAIGN_QUEST200){Campaign200 c;if(!quest_campaign200(&c))return 0;if(c.cursor==0){*total=2;*done=!!(c.objectives&1)+!!(c.objectives&2);}else if(c.cursor==3){*total=3;*done=!!(c.objectives&1)+!!(c.objectives&2)+!!(c.objectives&4);}else if(c.cursor==4){*total=1;*done=!!(c.objectives&1);}else if(c.cursor==5){*total=2;*done=!!c.guild[0]+!!(c.objectives&1);}return *total!=0;}const NpcQuestDefinition55*d=npc_quest_definition55(id);if(!d||!questLog65)return 0;for(unsigned i=0;i<d->count;i++){uint32_t need=npcQuestTargets55[d->start+i].count;int64_t have=npc_state_number55(questLog65,id,i+2);*total+=need;if(have>0)*done+=(uint64_t)have>need?need:(uint64_t)have;}return *total!=0;}
static const char*quest_title65(uint32_t id){if(id==CAMPAIGN_QUEST200){Campaign200 c;if(!quest_campaign200(&c))return "Campaign unavailable";return c.cursor<36?campaignQuests200[c.cursor].title:"The Names We Keep - Complete";}const QuestText65*t=quest_text65(id);if(t)return t->title;const NpcQuestDefinition55*d=npc_quest_definition55(id);return d?d->name:"Quest";}
static const char*quest_objective65(uint32_t id){if(id==CAMPAIGN_QUEST200){Campaign200 c;if(!quest_campaign200(&c))return "Campaign state could not be read.";return campaign_objective_text200(&c);}const QuestText65*t=quest_text65(id);return t?t->description:"Speak with the quest giver to continue.";}
#endif
