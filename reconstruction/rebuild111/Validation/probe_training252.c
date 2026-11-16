#include <stdio.h>
#include "combat.h"
#include "world_data.h"
#include "native_admission194.h"
static NpcState55 state;
int main(void){NativeAdmissionCache194 cache;for(unsigned checkpoint=0;checkpoint<4;checkpoint++){Campaign200 c={0};c.checkpoint=checkpoint;campaign_store200(&state,&c);native_admission_refresh194(&cache,&state,0);for(unsigned i=0;i<NPC_RECORD_COUNT55;i++)if(npcRecords55[i].map==455&&npcRecords55[i].program){const NpcRecord55*n=npcRecords55+i;printf("NPC %u %s program %u checkpoint %u reason %s\n",i,n->name,n->program,checkpoint,native_admission_reason194(&cache,i));if(n->program==3875)for(unsigned j=npcAccessOffsets194[n->program-1];j<npcAccessOffsets194[n->program];j++)printf("  target %u %s access %u redirected %u\n",npcAccessMaps194[j],mapNames[npcAccessMaps194[j]],cache.map[npcAccessMaps194[j]],story_departure_maps193(n->map,npcAccessMaps194[j]));}}npc_state_clear55(&state);}
