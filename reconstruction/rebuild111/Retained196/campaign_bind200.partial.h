static void campaign_killed200(Combat*g,const CombatMob*m){
 rescue_killed200(&campaignRescue200,g,m);
 campaign_encounter_killed193(g,m);
 party_gain_exp193(g,m);
}

static void campaign_party_bind200(Combat*g){
 Campaign200 c;
 unsigned ids[3],count=0;

 campaignPartyState200=questPins65;

 if(campaign_load200(questPins65,&c)!=1||c.cursor<3){
  campaignParty200.count=0;
  return;
 }

 int found=party_config_load200(
  questPins65,&campaignConfig200,c.recruits);

 if(!found){
  party_config_default200(&campaignConfig200,c.recruits);

  if(!party_config_store200(
      questPins65,&campaignConfig200,c.recruits))
   found=-1;
 }

 if(found<0){
  campaignParty200.count=0;
  campaignPartyState200=NULL;
  return;
 }

 if(!party_seed_recruits193(questPins65,c.recruits,g)||
    !party_promote194(questPins65,c.cursor)){
  campaignParty200.count=0;
  campaignPartyState200=NULL;
  return;
 }

 for(unsigned k=0;k<3;k++){
  unsigned id=campaignConfig200.active[k];

  if(id<19&&campaignCompanions200[id].sceneActor!=255)
   ids[count++]=id;
 }

 if(count>diagCompanionLimit194)
  count=diagCompanionLimit194;

 if(!campaign_follow_select200(
     &campaignParty200,c.recruits,ids,count)){
  campaignParty200.count=0;
  return;
 }

 for(unsigned i=0;i<count;i++){
  if(!party_init_vital200(campaignParty200.members+i,g)){
   campaignParty200.count=0;
   campaignPartyState200=NULL;
   return;
  }
 }
}

static void campaign_world_bind200(Combat*g){
 campaignRosterState200=questPins65;
 campaign_party_bind200(g);

 campaign_stage_bind200(
  &campaignStage200,g,questPins65,campaign_art_ready200());

 campaign_job_proof200(questPins65,g->jobId);

 rescue_bind200(
  &campaignRescue200,g,&npcGame55.monsters,
  questPins65,campaign_art_ready200());
}
