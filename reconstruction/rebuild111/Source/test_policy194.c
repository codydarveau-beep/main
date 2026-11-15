#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "world_data.h"
#include "npc_registry_data55.h"
#include "campaign_access194.h"
#include "native_admission194.h"
static NpcState55 state;
static NativeAdmissionCache194 cache;
static void story(unsigned cursor){Campaign200 c={0};c.cursor=cursor;if(cursor>1){c.route=1;c.lineage=1;}strcpy(c.guild,"Recovery");assert(campaign_store200(&state,&c));}
int main(void){
 unsigned previous[497]={0},mapCases=0,npcCases=0;
 CampaignRegions194 regions={0};unsigned active=(1u<<0)|(1u<<1)|(1u<<2)|(1u<<7)|(1u<<8)|(1u<<10)|(1u<<11)|(1u<<12)|(1u<<13);
 regions.accepted=regions.unlocked=regions.completed=active;assert(campaign_regions_store194(&state,&regions));
 for(unsigned cursor=0;cursor<=36;cursor++){
  story(cursor);unsigned revision=state.revision;
  for(unsigned map=0;map<497;map++){
   unsigned result=campaign_access194(&state,map,0),sandbox=campaign_access194(&state,map,1);
   assert(result!=ACCESS_RECORD194);if(campaignMapExcluded194[map])assert(result==ACCESS_DESTINATION194&&sandbox==ACCESS_DESTINATION194);
   else{assert(sandbox==ACCESS_OPEN194);assert(!previous[map]||result==ACCESS_OPEN194);previous[map]=result==ACCESS_OPEN194;}
   mapCases++;
  }
  assert(state.revision==revision);native_admission_refresh194(&cache,&state,0);
  for(unsigned n=0;n<NPC_RECORD_COUNT55;n++){(void)native_admission_reason194(&cache,n);npcCases++;}
  assert(state.revision==revision);
 }
 story(1);assert(campaign_access194(&state,108,0)==ACCESS_STORY194);
 assert(npc_state_set_number55(&state,npc_variable_key55("job_acolyte_q",0),0,3));assert(campaign_access194(&state,108,0)==ACCESS_OPEN194);
 assert(npc_state_set_number55(&state,CAREER_PILGRIMAGE_KEY194,0,1));assert(npc_state_set_number55(&state,npc_variable_key55("job_acolyte_q",0),0,0));
 assert(campaign_access194(&state,108,0)==ACCESS_OPEN194&&campaign_access194(&state,127,0)==ACCESS_STORY194);
 native_admission_refresh194(&cache,&state,0);assert(!native_admission_reason194(&cache,7350)&&!native_admission_reason194(&cache,7587));
 assert(npcRecords55[7350].id==7351&&npcRecords55[7350].map==126&&npcRecords55[7350].x==1244&&npcRecords55[7350].y==1028);
 assert(npcRecords55[7587].id==7588&&npcRecords55[7587].map==406&&npcRecords55[7587].x==340&&npcRecords55[7587].y==548);
 unsigned found[2]={0};for(unsigned m=0;m<495;m++)for(unsigned j=0;j<npcMapSpans55[m].count;j++){
  unsigned id=npcMapRecords55[npcMapSpans55[m].start+j];assert(npcRecords55[id].map==m);if(id==7350)found[0]++;if(id==7587)found[1]++;
 }assert(found[0]==1&&found[1]==1);
 CampaignRegions194 bad=regions;bad.completed|=1u<<16;unsigned rev=state.revision;assert(!campaign_regions_store194(&state,&bad)&&state.revision==rev);
 assert(npc_state_set_number55(&state,CAMPAIGN_REGION_KEY194,0,INT64_C(1)<<51));assert(!campaign_regions_load194(&state,&regions));assert(campaign_access194(&state,2,0)==ACCESS_RECORD194);
 assert(npc_state_set_number55(&state,CAMPAIGN_REGION_KEY194,0,-1));assert(!campaign_regions_load194(&state,&regions));
 assert(campaign_access194(&state,497,1)==ACCESS_DESTINATION194);
 npc_state_clear55(&state);printf("PASS HOST: %u map/milestone decisions; %u NPC/cache reads; no read-side mutations; pilgrimage persistence, 51-bit corruption, exclusions and exact relocated memberships\n",mapCases,npcCases);
}
