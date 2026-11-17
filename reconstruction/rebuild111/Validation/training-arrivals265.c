#define main prior_world265
#include "../Source/test_world43.c"
#undef main
#define main prior_job265
#include "../Source/test_native_first_jobs231.c"
#undef main
int main(int argc,char**argv){assert(argc==2);scriptFile=fopen(argv[1],"rb");assert(scriptFile);setup();for(unsigned id=3858;id<=3876;id++){const NpcProgram55*p=npc_program_cached55(&context231.programs,NULL,id);assert(p);for(unsigned i=0;i<p->count;i++){const NpcInstruction55*c=p->code+i;if(c->op!=N55_STRING||strcmp(p->strings+c->a,"new_1-4"))continue;printf("PROGRAM%u MAPREFERENCE%u\n",id,i);for(unsigned j=i;j<i+7&&j<p->count;j++){c=p->code+j;printf(" op%u a%u b%u %s\n",c->op,c->a,c->b,c->op==N55_STRING||c->op==N55_CALL?p->strings+c->a:"");}}}npc_game_clear55(&context231);npc_variables_clear55(&variables231);npc_state_clear55(&quests);fclose(scriptFile);}
