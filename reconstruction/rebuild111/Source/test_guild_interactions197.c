/* Actual controller/menu logic with recorded warp adapter. Packed floor and
 * true-world warp/collision are independently exercised by world197 checks. */
#define world_script_warp55 legacy_world_script_warp197
#define main legacy_guild_ui197
#include "test_guild_ui194.c"
#undef main
#undef world_script_warp55
#include "guild_layout194.h"
static unsigned warps197;
static int world_script_warp55(void*c,Combat*g,unsigned map,float x,float y,int random,int clean){warps197++;return legacy_world_script_warp197(c,g,map,x,y,random,clean);}
#include "guild_world194.h"
#include "guild_interact197.h"
int main(void){combat_init(&game,128,1444,NULL,NULL);game.mapId=494;game.zeny=12345;Campaign200 c={.cursor=36,.route=1,.lineage=1};strcpy(c.guild,"Original");assert(campaign_store200(&state,&c));quest_journal_bind65(&logState,&state);
 for(unsigned mask=0;mask<64;mask++)for(unsigned door=0;door<8;door++){Guild194 hall={mask,mask,0,{0}};assert(guild_store194(&state,&hall));const GuildDoor194*d=guildDoors194+door;game.mapId=494;game.x=d->x;game.y=d->y;unsigned calls=warps197,revision=state.revision;assert(guild_world_near197(&game)==(int)door);assert(guild_world_interact197(&game));int locked=d->any&&!(mask&d->any);assert(warps197==calls+(locked?0u:1u));assert(game.zeny==12345&&state.revision==revision);if(locked)assert(game.mapId==494&&game.x==d->x&&game.y==d->y);else assert(game.mapId==d->map&&game.x==d->toX&&game.y==d->toY);}
 Guild194 hall={4095,4095,0,{0}};assert(guild_store194(&state,&hall));for(unsigned i=0;i<6;i++){game.mapId=494;game.x=1332;game.y=464+i*88;game.utilityMenu=0;unsigned revision=state.revision,calls=warps197;assert(guild_world_near197(&game)==100+(int)i);assert(guild_world_interact197(&game)&&game.utilityMenu==504&&guildUI194.page==4&&guildUI194.cabinet==i);assert(game.zeny==12345&&state.revision==revision&&warps197==calls);guild_ui_input194(&game,4,16);}
 npc_state_clear55(&state);npc_state_clear55(&logState);puts("PASS actual guild door controls, locked-room preservation, free physical passages and six cabinet interactions; host warp recorder only.");return 0;}
