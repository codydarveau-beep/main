/* Shared host fixture setup; no production behavior is mirrored here. */
#ifndef MYRO_TEST_COMPANION_FIXTURE205_H
#define MYRO_TEST_COMPANION_FIXTURE205_H
#define main legacy_growth_fixture205
#include "test_companion_runtime200.c"
#undef main
static CampaignFollower200*prepare201(unsigned jobLevel){
 npc_state_clear55(&record201);memset(&campaignParty200,0,sizeof campaignParty200);combat_init(&player201,100,100,NULL,NULL);player201.mapId=3;player201.time=10;player201.level=100;player201.hp=player201.maxhp=1000;player201.sp=77;player201.peaceful=1;campaignPartyState200=&record201;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={20,0,jobLevel,0,3,0,0};unsigned char stats[6];assert(party_growth_stats200(COMP200_YUUFA,p.job,p.level,stats,&p.hp,&p.sp));assert(party_progress_put200(b,COMP200_YUUFA,&p)&&party_progress_commit200(&record201,b));unsigned id=COMP200_YUUFA;select201(1u<<id,&id,1);party_config_default200(&campaignConfig200,1u<<id);campaignConfig200.skills[id]=1;campaignConfig200.mode[id]=PARTY_ASSIST200;CampaignFollower200*m=campaignParty200.members;m->map=3;m->x=m->y=100;m->regenAt=1000;return m;
}
static void enemy201(void){memset(player201.mobs,0,sizeof player201.mobs);CombatMob*e=player201.mobs;e->enabled=1;e->kind=0;e->hp=100000;e->x=112;e->y=100;e->life=123;player201.target=0;player201.peaceful=0;}

static CampaignFollower200*mage204(void){prepare201(2);unsigned char b[640],stats[6];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 p={20,0,50,0,2,0,0};assert(party_growth_stats200(COMP200_TAKIUS,2,20,stats,&p.hp,&p.sp));assert(party_progress_put200(b,COMP200_TAKIUS,&p)&&party_progress_commit200(&record201,b));unsigned id=COMP200_TAKIUS;select201((1u<<COMP200_YUUFA)|(1u<<id),&id,1);CampaignFollower200*m=campaignParty200.members;m->map=3;m->x=m->y=100;m->regenAt=1000;party_config_default200(&campaignConfig200,1u<<id);campaignConfig200.skills[id]=1;campaignConfig200.mode[id]=PARTY_ASSIST200;enemy201();player201.mobs[0].x=160;return m;}

#endif
