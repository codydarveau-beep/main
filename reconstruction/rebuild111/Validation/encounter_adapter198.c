#include "combat.h"
#include "npc_monsters55.h"
#include "campaign_stage200.h"
#include "campaign_encounter198.h"
void encounter_plans198(unsigned row,unsigned checkpoint,unsigned objectives,unsigned out[15]){const CampaignStageDefinition200*d=row<9?campaignStages200+row:campaignLaterStages197+row-9;Campaign200 c={0};c.cursor=d->cursor;c.route=1;c.lineage=1;c.checkpoint=checkpoint;c.objectives=objectives;memset(out,0,15*4);for(unsigned k=0;k<3;k++){CampaignEncounterPlan198 p;if(!campaign_encounter_plan198(d,&c,k,&p))continue;out[k*5]=p.source;out[k*5+1]=p.tag;out[k*5+2]=p.bit;memcpy(out+k*5+3,&p.x,4);memcpy(out+k*5+4,&p.y,4);}}
