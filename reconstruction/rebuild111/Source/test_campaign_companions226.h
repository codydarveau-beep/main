/* Actual chapter/party bridge with explicit ordinary-enemy arena fixtures. */
#include "campaign_battle200.h"
static NpcState55*questPins65;
#include "../Validation/actual_party_bind223.inc"
#include "../Validation/actual_campaign_killed226.inc"
static unsigned recruitSeen226,combatSeen226,chapterRewards226,combatKills226;
static void sequence_companions_begin226(void){combat_init(&player200,0,0,NULL,NULL);memset(player200.mobs,0,sizeof player200.mobs);player200.hp=player200.maxhp=1000;player200.faceY=1;questPins65=&character200;campaignRosterState200=&character200;memset(&campaignParty200,0,sizeof campaignParty200);party_config_default200(&campaignConfig200,0);combat_campaign_kill200=campaign_killed200;combat_companion_field194=party_wizard_hit194;}
static void sequence_companions_frame226(int modal){campaign_party_bind200(&player200);CampaignFollow200 before=campaignParty200;campaign_battle_tick200(&player200,.016f,modal);campaign_follow_tick200(&campaignParty200,&player200,.016f,modal);if(modal)assert(!memcmp(&before,&campaignParty200,sizeof before));Campaign200 c;assert(campaign_load200(&character200,&c)==1);recruitSeen226|=c.recruits;}
static void sequence_companions_advance226(void){
 Campaign200 story;assert(campaign_load200(&character200,&story)==1);questPins65=&character200;campaign_party_bind200(&player200);recruitSeen226|=story.recruits;
 unsigned ids[19],n=0;for(unsigned id=0;id<19;id++)if(story.recruits&(1u<<id))ids[n++]=id;
 recruitSeen226|=story.recruits;
 if(story.cursor>=3&&n){
  memset(campaignConfig200.active,255,3);for(unsigned i=0;i<n&&i<3;i++)campaignConfig200.active[i]=(unsigned char)ids[(story.cursor+i)%n];assert(party_config_store200(&character200,&campaignConfig200,story.recruits));campaign_party_bind200(&player200);
  /* Isolate an ordinary native-spec enemy from scene-owned encounters. */
  size_t bytes=sizeof player200.mobs;CombatMob*saved=malloc(bytes);assert(saved);memcpy(saved,player200.mobs,bytes);memset(player200.mobs,0,bytes);int oldTarget=player200.target,peaceful=player200.peaceful;player200.target=0;player200.peaceful=0;CombatMob*enemy=player200.mobs;enemy->enabled=1;enemy->kind=0;enemy->life=100000+story.cursor;enemy->hp=mobSpecs[0].hp;enemy->x=player200.x+12;enemy->y=player200.y;
  unsigned char before[640],after[640];assert(party_progress_load200(&character200,before)==1);unsigned eligible=0;for(unsigned i=0;i<campaignParty200.count;i++){CampaignFollower200*m=campaignParty200.members+i;m->map=player200.mapId;m->x=player200.x;m->y=player200.y;m->regenAt=player200.time+1000;if(m->hp)eligible|=1u<<m->id;}
  unsigned kills=player200.kills;for(unsigned tick=0;enemy->hp>0&&tick<1200;tick++){player200.time+=.05f;campaign_party_bind200(&player200);campaign_battle_tick200(&player200,.05f,0);combat_fields_tick(&player200);}
  assert(eligible&&enemy->hp<=0&&player200.kills==kills+1);combatKills226++;combatSeen226|=eligible;assert(party_progress_load200(&character200,after)==1);
  for(unsigned id=0;id<19;id++){PartyGrowth200 a,b;party_growth_read200(before+16+id*32,&a);party_growth_read200(after+16+id*32,&b);if(eligible&(1u<<id))assert(b.level!=a.level||b.exp!=a.exp||b.jobLevel!=a.jobLevel||b.jobExp!=a.jobExp);else assert(!memcmp(before+16+id*32,after+16+id*32,32));}
  memcpy(player200.mobs,saved,bytes);free(saved);player200.target=oldTarget;player200.peaceful=peaceful;memset(player200.fields,0,sizeof player200.fields);
 }
 for(unsigned i=0;i<campaignParty200.count;i++){CampaignFollower200*m=campaignParty200.members+i;m->map=player200.mapId;m->x=player200.x;m->y=player200.y;}
 for(unsigned i=0;i<36;i++)campaign_progress_reward200(&player200);unsigned char b[640];assert(party_progress_load200(&character200,b)==1&&npc_state_u32_55(b+12)==story.cursor);unsigned revision=character200.revision;int exp=player200.exp,level=player200.level,jexp=player200.jexp;campaign_progress_reward200(&player200);assert(character200.revision==revision&&player200.exp==exp&&player200.level==level&&player200.jexp==jexp);chapterRewards226++;
}
