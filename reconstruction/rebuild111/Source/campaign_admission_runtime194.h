/* MIT. Shared callbacks; cache invalidation follows actual character revision. */
#ifndef MYRO_CAMPAIGN_ADMISSION_RUNTIME194_H
#define MYRO_CAMPAIGN_ADMISSION_RUNTIME194_H
#include "native_admission194.h"
static NativeAdmissionCache194 campaignNativeAccess194;
static void campaign_admission_reset194(void){memset(&campaignNativeAccess194,0,sizeof(campaignNativeAccess194));}
static const char*campaign_native_admission194(unsigned npc){
 if(!campaignNativeAccess194.valid||campaignNativeAccess194.state!=questPins65||
    campaignNativeAccess194.revision!=(questPins65?questPins65->revision:0))
  native_admission_refresh194(&campaignNativeAccess194,questPins65,campaign_sandbox193(questPins65));
 return native_admission_reason194(&campaignNativeAccess194,npc);
}
static const char*campaign_npc_admission194(Combat*g,unsigned destination){
 if(destination>=WORLD_MAP_COUNT||!world_destination_ready44(destination))return "This destination is unavailable.";
 (void)g;unsigned result=campaign_access194(questPins65,destination,campaign_sandbox193(questPins65));
 return result==ACCESS_OPEN194?NULL:campaign_access_message194(result);
}
static const char*campaign_npc_choice_admission194(Combat*g,unsigned destination){
 if(g&&story_departure193(questPins65,g->mapId,destination))destination=0;
 return campaign_npc_admission194(g,destination);
}
static void campaign_departure_redirect193(Combat*g,unsigned*destination,float*x,float*y){
 if(story_departure193(questPins65,g->mapId,*destination)){
  *destination=0;*x=1460;*y=2804;
 }
}
static int campaign_career_gate194(unsigned gate){
 if(gate<CAREER_GATE_START194)return 1;if(gate>=WORLD_GATE_COUNT)return 0;Campaign200 c;
 if(campaign_load200(questPins65,&c)!=1||c.cursor<1)return 0;
 return gate<CAREER_GATE_START194+6||career_pilgrimage194(questPins65);
}
static void campaign_admission_install194(void){
 campaign_admission_reset194();worldCareerGateAvailable194=campaign_career_gate194;npcTravelAdmission194=campaign_npc_choice_admission194;
 npcNativeAdmission194=campaign_native_admission194;combatTravelAdmission194=campaign_npc_admission194;
 npcTravelRedirect193=campaign_departure_redirect193;
}
#endif
