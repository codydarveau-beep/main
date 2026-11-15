#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static int failSave198;
static void*allocSave198(size_t n){return failSave198?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 allocSave198
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "npc_monsters55.h"
#include "campaign_stage200.h"
#include "campaign_encounter198.h"
#include "../Validation/encounter_fixtures198.h"
static Combat game;
static NpcState55 state;
static NpcMonsters55 monsters;
int main(void){unsigned sampled[42]={0},runs=0;for(unsigned z=0;z<sizeof(encounterFixtures198)/sizeof(*encounterFixtures198);z++){
 const unsigned*f=encounterFixtures198[z];const CampaignStageDefinition200*d=f[0]<9?campaignStages200+f[0]:campaignLaterStages197+f[0]-9;Campaign200 c={0};c.cursor=d->cursor;c.route=1;c.lineage=1;c.checkpoint=f[1];c.objectives=f[2];unsigned plans=0;
 for(unsigned k=0;k<3;k++){CampaignEncounterPlan198 p;int active=campaign_encounter_plan198(d,&c,k,&p);const unsigned*expected=f+3+k*5;assert(active==(expected[0]!=0));if(active){unsigned xx,yy;memcpy(&xx,&p.x,4);memcpy(&yy,&p.y,4);assert(p.source==expected[0]&&p.tag==expected[1]&&p.bit==expected[2]&&xx==expected[3]&&yy==expected[4]);plans++;}}
 if(!plans||sampled[f[0]]||d->map>=sizeof(mapWidth43)/sizeof(*mapWidth43))continue;sampled[f[0]]=1;assert(campaign_store200(&state,&c));game.mapId=d->map;game.hp=100;game.zeny=12345;game.x=d->x;game.y=d->y;campaignStage200=(CampaignStage200){&game,&state,d,1};unsigned revision=state.revision;
 campaign_encounter_tick198(&game,&monsters,&state,1);assert(!monsters.count&&state.revision==revision);
 for(unsigned k=0;k<MOB_COUNT-1;k++)game.mobs[k].enabled=1;campaign_encounter_tick198(&game,&monsters,&state,0);assert(!monsters.count&&state.revision==revision);memset(game.mobs,0,sizeof game.mobs);
 game.x=d->x+193;campaign_encounter_tick198(&game,&monsters,&state,0);assert(!monsters.count);game.x=d->x;
 campaign_encounter_tick198(&game,&monsters,&state,0);assert(monsters.count==plans&&state.revision==revision&&game.zeny==12345);
 unsigned count=monsters.count;campaign_encounter_tick198(&game,&monsters,&state,0);assert(monsters.count==count);
 NpcMonster55*first=monsters.rows;assert(first->slot>=0);CombatMob*mob=game.mobs+first->slot;mob->hp=0;unsigned life=mob->life;mob->life++;campaign_encounter_killed198(&game,mob);assert(state.revision==revision);mob->life=life;
 failSave198=1;campaign_encounter_killed198(&game,mob);failSave198=0;assert(state.revision==revision&&campaignEncounter198.pending);Campaign200 after;assert(campaign_load200(&state,&after)==1&&!memcmp(&c,&after,sizeof c));unsigned pending=campaignEncounter198.pending;first->alive=0;first->hp=0;
 campaign_encounter_tick198(&game,&monsters,&state,0);assert(!campaignEncounter198.pending&&campaign_load200(&state,&after)==1&&after.objectives==(c.objectives|pending)&&after.cursor==c.cursor&&after.checkpoint==c.checkpoint&&game.zeny==12345);assert(monsters.count==count);
 campaignStage200.active=0;campaign_encounter_tick198(&game,&monsters,&state,0);for(unsigned k=0;k<monsters.count;k++)if(campaign_encounter_owned198(monsters.rows+k))assert(!monsters.rows[k].alive);for(unsigned k=0;k<MOB_COUNT;k++)assert(!game.mobs[k].enabled);npc_monsters_clear55(&monsters);memset(&game,0,sizeof game);runs++;
 }
 npc_state_clear55(&state);printf("PASS original spawn fixtures and %u actual encounter lifecycles, pause/range/capacity limits, serial ownership, failed-save retry and cleanup. Full scene activation and Xbox execution remain pending.\n",runs);}
