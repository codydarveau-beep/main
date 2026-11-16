#define main prior_world_test252
#include "../Source/test_world43.c"
#undef main
#define main prior_job_test252
#include "../Source/test_native_first_jobs231.c"
#undef main
#include "quest_journal65.h"
#include "campaign_admission_runtime194.h"
int main(int argc,char**argv){setvbuf(stdout,NULL,_IONBF,0);assert(argc==2);scriptFile=fopen(argv[1],"rb");assert(scriptFile);setup();questPins65=shared;campaign_admission_install194();Campaign200 c={0};assert(campaign_store200(shared,&c));game.stats[0]=99;game.mapId=455;unsigned npc=7575;assert(npcRecords55[npc].program==3875);game.x=npcRecords55[npc].x;game.y=npcRecords55[npc].y;assert(!campaign_native_admission194(npc));setNumber("nov_3_swordman",0,20);setNumber("nov_1st_cos",0,2);setNumber("nov_2nd_cos",0,2);context231.scene.flags[npc]|=N55_NPC_INIT_DONE;assert(npc_game_open55(&context231,npc));unsigned menus=0;for(unsigned i=0;i<1000;i++){int status=npc_runtime_step55(context231.vm,4096);assert(status!=N55_ERROR);fprintf(stderr,"STATE %d text %.180s\n",status,context231.vm[0].dialogue.text);if(context231.world[0].pending||status==N55_DONE)break;if(status==N55_WAIT){if(context231.vm[0].dialogue.mode==N55_DIALOGUE_SELECT){printf("MENU %u pc %u %s\n",menus++,context231.vm[0].machine.pc,context231.vm[0].dialogue.options);}assert(npc_runtime_answer55(context231.vm,0,0));}}printf("PENDING %u map %u menus %u\n",context231.world[0].pending,context231.world[0].map,menus);assert(context231.world[0].pending&&context231.world[0].map==0);assert(game.jobId==0);npc_game_clear55(&context231);npc_variables_clear55(&variables231);npc_state_clear55(&quests);fclose(scriptFile);puts("PASS actual Hanson NPC open/unchanged native VM graduation routes to campaign opening; no early job grant. Host only.");}
