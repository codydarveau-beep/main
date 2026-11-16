/* Exact production chapter/party bridge. */
static void campaign_killed200(Combat*g,const CombatMob*m){rescue_killed200(&campaignRescue200,g,m);campaign_encounter_killed198(g,m);party_gain_exp200(g,m);}
