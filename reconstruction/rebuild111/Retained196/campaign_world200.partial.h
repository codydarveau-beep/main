static int campaign_world_near200(void){
 int near=campaign_stage_near200(&campaignStage200);
 return near>=0?near:rescue_near200(&campaignRescue200);
}

static void campaign_world_interact200(void){
 int who=campaign_world_near200();
 if(who<0)return;

 if(who>=100){
  if(campaign_stage_interact200(&campaignStage200,who)==1){
   if(!scene_ui_open200(questPins65)){
    combat_message(
     campaignStage200.player,
     "The conversation could not be loaded. Please try again.");
   }else if(scene_ui_tick200()==SC200_WAIT){
    Campaign200 c;

    if(campaign_load200(questPins65,&c)==1)
     combat_message(
      campaignStage200.player,
      "%s",campaign_objective_text200(&c));

    scene_ui_release200();
   }
  }
  return;
 }

 if(rescue_interact200(&campaignRescue200,(unsigned)who)){
  if(!scene_ui_open200(questPins65)){
   combat_message(
    campaignRescue200.player,
    "The conversation could not be loaded. Please try again.");
  }else{
   unsigned recommended=campaign_recommended_role200(
    campaign_career_root200(campaignRescue200.player->jobId));

   if(recommended)
    campaignUI200.role=recommended-1;
  }
 }
}

static int campaign_native_page200(
 Combat*g,const NpcRecord55*n,const char*text
){
 if(campaign_investigation_page200(
     questPins65,g->mapId,n->map,n->unique,text))
  return 1;

 combat_message(
  g,"The witness account could not be saved. Please try again.");

 return 0;
}

static int campaign_job_guard200(Combat*g,unsigned job){
 if(!questPins65||campaign_sandbox193(questPins65))
  return 1;

 Campaign200 c;
 int found=campaign_load200(questPins65,&c);

 if(!found)return 1;

 if(found<0){
  combat_message(
   g,"Your story record could not be read. Job change was not applied.");
  return 0;
 }

 if(campaign_career_allows200(c.lineage,job))
  return 1;

 combat_message(
  g,"Your chosen career is permanent. Promotions within that path remain available.");

 return 0;
}
