/* Native NPC transitions must cover empty campaign aliases safely. */
#define main native_jobs_fixture242
#include "test_native_first_jobs231.c"
#undef main
#define SCRIPT_NPC_SLOTS55 8
#include "npc_visibility180.h"
static float height242(float x,float y){(void)x;(void)y;return 0;}
int main(void){setup();unsigned maps[]={2,495,496,0};for(unsigned k=0;k<4;k++){unsigned map=maps[k];game.mapId=map;context231.presentation172.events[0].kind=1;context231.inside[0]=1;mapMarkers64[0].active=1;npc_game_map55(&context231,map);assert(context231.map==map);if(map>=495){assert(!npcMapSpans55[map].count&&!context231.presentation172.events[0].kind&&!context231.inside[0]&&!mapMarkers64[0].active);assert(npc_game_near55(&context231)==-1);npc_game_touch55(&context231);context231.ms+=200;npc_game_monster_touch172(&context231);float matrix[16]={0};matrix[0]=matrix[5]=matrix[10]=matrix[15]=1;int nearest[SCRIPT_NPC_SLOTS55];assert(!npc_select180(&context231.scene,&game,matrix,nearest,height242));for(unsigned i=0;i<SCRIPT_NPC_SLOTS55;i++)assert(nearest[i]==-1);}}npc_game_clear55(&context231);npc_variables_clear55(&variables231);npc_state_clear55(&quests);puts("PASS native NPC map transitions, near/touch/monster-touch/visibility on both empty campaign aliases, presentation/inside/marker reset and ordinary-map return. No native environment NPC scripts imported; host only.");return 0;}
