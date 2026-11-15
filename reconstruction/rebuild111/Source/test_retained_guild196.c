#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "guild194.h"
static Combat game,before;
int main(void){unsigned checks=0;static const unsigned char after[19]={8,2,8,15,2,14,11,13,5,13,13,16,5,8,18,16,13,23,23};
 combat_init(&game,188,1116,NULL,NULL);game.zeny=12345;before=game;
 for(unsigned cursor=0;cursor<=36;cursor++)for(unsigned id=0;id<19;id++){
  NpcState55 s={0};Campaign200 c={.cursor=cursor,.route=1,.lineage=1};strcpy(c.guild,"Retained");assert(campaign_store200(&s,&c));unsigned revision=s.revision;int expected=cursor>=9&&cursor>after[id];assert(guild_invite194(&s,id)==expected);Campaign200 got;assert(campaign_load200(&s,&got)==1);assert(got.cursor==cursor&&got.recruits==(expected?(1u<<id):0));
  assert(!memcmp(&game,&before,sizeof game));if(!expected)assert(s.revision==revision);else{revision=s.revision;assert(guild_invite194(&s,id)&&s.revision==revision);}npc_state_clear55(&s);checks++;
 }
 assert(guild_met_mask194(12)==((1u<<0)|(1u<<1)|(1u<<2)|(1u<<4)|(1u<<6)|(1u<<8)|(1u<<12)|(1u<<13)));
 NpcState55 state={0};Campaign200 c={.cursor=36,.route=1,.lineage=1};strcpy(c.guild,"Retained");assert(campaign_store200(&state,&c));assert(guild_accept194(&state,0));assert(owned_add52(&game.owned52,0,1019,40,item_rule52)==OWNED_OK52);assert(owned_add52(&game.owned52,0,914,10,item_rule52)==OWNED_OK52);for(unsigned i=0;i<game.owned52.count[0];i++)if(game.owned52.items[i].sourceID==1019)game.owned52.items[i].bound=1;
 assert(guild_material_count194(&game,1019)==40);assert(guild_build194(&state,&game,0));assert(game.zeny==12345&&guild_material_count194(&game,1019)==0&&guild_material_count194(&game,914)==0);Guild194 g;assert(guild_load194(&state,&g)==1&&g.completed==1);npc_state_clear55(&state);
 printf("PASS retained guild invitation chronology/idempotence/no charges across %u cases and deployed bound-material semantics. HOST ONLY.\n",checks);return 0;}
