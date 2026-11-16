/* Additional review 1: actual session reset and reused character state address. */
#define CAMPAIGN_LIVE_COMPANIONS226 1
#define CAMPAIGN_SEQUENCE_ENTRY226 unused_scene_sequences245
#include "../Source/test_campaign_sequence200.c"
#include "actual_session_reset245.inc"
static void setup245(unsigned cursor,unsigned id,unsigned hp,unsigned sp,unsigned exp){
 Campaign200 c={0};c.cursor=cursor;c.route=1;c.lineage=1;c.recruits=(1u<<19)-1;assert(campaign_store200(&character200,&c));
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={30,exp,2,0,partyInitialJobs200[id],hp,sp};assert(party_progress_put200(b,id,&p)&&party_progress_commit200(&character200,b));
 party_config_default200(&campaignConfig200,c.recruits);memset(campaignConfig200.active,255,3);campaignConfig200.active[0]=id;campaignConfig200.mode[id]=id%3;assert(party_config_store200(&character200,&campaignConfig200,c.recruits));
}
static void bind245(unsigned id,unsigned hp,unsigned sp,unsigned exp){
 quest_journal_bind65(&quests200,&character200);assert(!campaignPartyState200&&!campaignRosterState200&&!campaignParty200.count&&!campaignNativeAccess194.valid&&!campaignStage200.active&&!campaignRescue200.active&&!campaignEncounter198.pending&&!scene_ui_modal200());
 for(unsigned i=0;i<4;i++)assert(!campaignSprites200[i].raw&&!entityTextures[CAMPAIGN_TEXTURE200+i]&&!campaignEmotes225.events[i].kind);
 for(unsigned i=0;i<PARTY_SHOTS200;i++)assert(!campaignShots200[i].active);
 assert(campaignCommandTarget200==-1);campaign_party_bind200(&player200);assert(campaignParty200.count==1);const CampaignFollower200*m=campaignParty200.members;assert(m->id==id&&m->hp==hp&&m->sp==sp&&m->exp==exp&&m->level==30&&campaignConfig200.mode[id]==id%3);
}
int main(void){
 campaignSessionReset200=campaign_reset200;combat_init(&player200,100,100,NULL,NULL);player200.level=30;player200.mapId=3;player200.hp=player200.maxhp=1000;
 setup245(15,7,17,9,1234);NpcState55 a=character200;memset(&character200,0,sizeof character200);setup245(3,1,11,4,765);NpcState55 b=character200;character200=a;
 bind245(7,17,9,1234);campaignNativeAccess194.valid=1;campaignStage200.active=1;campaignStageModal200=1;campaignRescue200.active=1;campaignCommandTarget200=4;campaignShots200[0].active=1;campaignEncounter198.pending=1;campaignEmotes225.events[0].kind=1;
 for(unsigned i=0;i<4;i++){campaignSprites200[i].raw=malloc(16);assert(campaignSprites200[i].raw);entityTextures[CAMPAIGN_TEXTURE200+i]=gpu_alloc(16);}
 a=character200;character200=b;bind245(1,11,4,765);b=character200;character200=a;bind245(7,17,9,1234);a=character200;character200=b;bind245(1,11,4,765);npc_state_clear55(&character200);npc_state_clear55(&a);npc_state_clear55(&quests200);campaign_reset200();assert(!allocated&&!bytesNow);
 puts("PASS additional review: actual journal/session reset clears transient party, effects, access cache and CPU/GPU actor resources across characters at the same state address; each retains own growth, vitals and settings. Host only.");return 0;
}
