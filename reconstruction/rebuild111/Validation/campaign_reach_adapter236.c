#include "combat.h"
#include "world_data.h"
#include "native_admission194.h"
static NpcState55*questPins65;
#include "story_routes199.h"
#include "../Validation/actual_career_gate236.inc"
void reach236(unsigned cursor,unsigned objectives,unsigned char*maps,unsigned char*npcs,unsigned char*gates){NpcState55 state={0};questPins65=&state;Campaign200 c={0};c.cursor=cursor;c.objectives=objectives;if(cursor>1)c.route=c.lineage=1;if(!campaign_store200(&state,&c))abort();NativeAdmissionCache194 cache;native_admission_refresh194(&cache,&state,0);for(unsigned i=0;i<497;i++)maps[i]=cache.map[i]==ACCESS_OPEN194;for(unsigned i=0;i<NPC_RECORD_COUNT55;i++)npcs[i]=!native_admission_reason194(&cache,i);for(unsigned i=0;i<WORLD_GATE_COUNT;i++)gates[i]=campaign_career_gate194(i)&&campaign_story_gate_open199(i);npc_state_clear55(&state);questPins65=NULL;}
