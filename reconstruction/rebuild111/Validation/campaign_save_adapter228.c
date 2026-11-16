#define main legacy_save_world228
#include "../Source/test_world43.c"
#undef main
#include "campaign_battle200.h"
#include "campaign_career200.h"
#include "story_departure193.h"
#include "campaign_data200.h"
#include "campaign_objectives200.h"
static NpcState55*questPins65;
#include "../Validation/actual_job_guard228.inc"
void save228(const unsigned char*text,unsigned bytes,unsigned job,unsigned*out){
 NpcState55 state={0};Combat*g=calloc(1,sizeof(*g));assert(g);combat_init(g,100,100,NULL,NULL);questPins65=&state;campaignPartyState200=&state;memset(&campaignParty200,0,sizeof campaignParty200);if(bytes)assert(npc_state_set_text55(&state,CAMPAIGN_KEY200,0,(const char*)text,bytes));Campaign200 c={0};int loaded=campaign_load200(&state,&c);out[0]=(unsigned)loaded;out[1]=campaign_sandbox_state228(&state);out[2]=campaign_sandbox193(&state);out[3]=campaign_job_guard200(g,job);out[4]=loaded==1&&!strncmp(campaign_objective_text200(&c),"Developer story sandbox.",24);if(out[1]){unsigned revision=state.revision;int exp=g->exp,level=g->level,jexp=g->jexp;campaign_progress_reward200(g);assert(state.revision==revision&&g->exp==exp&&g->level==level&&g->jexp==jexp);}out[4]=loaded==1&&!strncmp(campaign_objective_text200(&c),"Developer story sandbox.",24);
 if(out[1]){unsigned revision=state.revision;int exp=g->exp,jexp=g->jexp,level=g->level;for(unsigned i=0;i<40;i++)campaign_progress_reward200(g);assert(state.revision==revision&&g->exp==exp&&g->jexp==jexp&&g->level==level);}
 if(loaded==1){unsigned wireBytes=npc_state_wire_bytes55(&state);unsigned char*wire=malloc(wireBytes);NpcState55 reloaded={0};assert(wire&&npc_state_encode55(&state,wire,wireBytes)&&npc_state_decode55(&reloaded,wire,wireBytes));Campaign200 after;assert(campaign_load200(&reloaded,&after)==1&&!memcmp(&after,&c,sizeof c));assert(campaign_sandbox_state228(&reloaded)==(int)out[1]);free(wire);npc_state_clear55(&reloaded);}
 npc_state_clear55(&state);free(g);questPins65=NULL;campaignPartyState200=NULL;
}
