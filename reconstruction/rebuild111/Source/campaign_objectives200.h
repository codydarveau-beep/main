/* MIT. Concrete directions derived from durable scene proof, not dialogue timers. */
#ifndef MYRO_CAMPAIGN_OBJECTIVES200_H
#define MYRO_CAMPAIGN_OBJECTIVES200_H
#include "chapter1_data200.h"
#include "chapter2_gates200.h"
static const char*campaign_objective_text200(const Campaign200*c){
 if(c->cursor==36&&(c->objectives&UINT32_C(0x80000000)))return "Developer story sandbox. All campaign objectives count as completed. Native NPC quests remain available for testing.";
 if(c->cursor==0){if(c->checkpoint<CHAPTER1_RESCUE_GATE200)return campaignQuests200[0].objective;if(!(c->objectives&4))return "Defeat the two Porings near the stalled cart. Help the driver first.";if(!(c->objectives&1))return "Speak with the driver. Stay close as he walks back to Nera.";if(!(c->objectives&2))return "Recover the blue-cord parcel beside the cart.";return "Return to Nera and hear what the parcel contains.";}
 if(c->cursor==3){if(c->checkpoint<CHAPTER2_WITNESS_GATE200)return "Meet Nera and Judia beside the Payon Cave approach in Archer Village.";if(!(c->objectives&1))return "Ask Monster Scholar Vuicokk on northern Payon's road about Undead Monsters.";if(!(c->objectives&2))return "Speak with the young man in southern Payon about his grandfather.";if(!(c->objectives&4))return "Compare the old burial register beside Nera and Judia near Payon Cave.";return "Return to Judia near Payon Cave and compare the three accounts.";}
 if(c->cursor==4){if(c->checkpoint<CHAPTER2_LEDGER_GATE200)return "Meet Maya and Veyr inside the southwestern Alberta warehouse.";return(c->objectives&1)?"Return to Maya and Veyr with the dispatch-ledger comparison.":"Examine the open dispatch ledger beside Maya and Veyr in the warehouse.";}
 if(c->cursor==5){if(!c->guild[0])return "Meet the group at Alberta's northwestern inn. Choose and confirm your guild's name.";return(c->objectives&1)?"Finish the guild's first conversation at the Alberta inn.":"Speak with Maya and Judia at the Alberta inn about travelling together.";}
 return c->cursor<36?campaignQuests200[c->cursor].objective:"The campaign is complete. Explore remaining side quests.";
}
#endif
