static void(*campaignCosmeticReset194)(void);

static void campaign_reset200(void){
 memset(&campaignNativeAccess194,0,sizeof(campaignNativeAccess194));

 if(campaignCosmeticReset194)
  campaignCosmeticReset194();

 campaign_encounter_clear193();

 while(pb_busy()){}

 scene_ui_release200();
 memset(&campaignStage200,0,sizeof(campaignStage200));
 campaignStageModal200=0;

 campaignRosterState200=NULL;
 campaignPartyState200=NULL;
 campaignCommandTarget200=-1;

 party_config_default200(&campaignConfig200,0);

 memset(campaignShots200,0,sizeof(campaignShots200));
 memset(partyArrows193,0,sizeof(partyArrows193));
 memset(campaignFx200,0,sizeof(campaignFx200));
 memset(&campaignParty200,0,sizeof(campaignParty200));

 rescue_reset200(&campaignRescue200);
 campaign_actor_release200();
}
