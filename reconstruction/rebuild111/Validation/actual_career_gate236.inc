/* Exact production career gate. */
static int campaign_career_gate194(unsigned gate){
 if(gate>=STORY_GATE_START199)return campaign_story_gate_visible199(gate);if(gate<CAREER_GATE_START194)return 1;if(gate>=WORLD_GATE_COUNT)return 0;Campaign200 c;
 if(campaign_load200(questPins65,&c)!=1||c.cursor<1)return 0;
 return gate<CAREER_GATE_START194+6||career_pilgrimage194(questPins65);
}

