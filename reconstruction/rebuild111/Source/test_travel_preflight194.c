/* Host integration: actual released bytecode + native VM/player/world adapters. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "world_data.h"
#include "npc_game55.h"
#include "npc_registry_data55.h"
#include "npc_world55.h"
#include "career_warp194.h"
#include "campaign_access194.h"
#include "story_departure193.h"
#include "npc_travel_preflight194.h"
static Combat game,beforeGame;
static NpcRuntime55 runtime,beforeRuntime;
static NpcPlayer55 player;
static NpcState55 shared[N55_VAR_DOMAINS],quests;
static NpcWorld55 world;
static unsigned rootProgram;
static FILE*scriptFile;
static char errorText[160];
static NpcGame55 inputContext;
static const NpcInstruction55 callerCode[]={
 {N55_STRING,1,0},{N55_INT,0,0},{N55_STRING,12,0},{N55_CALL,20,3},{N55_STOP,0,0}
};
static const char callerStrings[]="\0F_KafTele\0\0[Kafra]\0callfunc\0";
static NpcProgram55 caller={callerCode,5,callerStrings,sizeof(callerStrings),NULL,NULL,0,0,123456};
static int readProgram(void*c,uint32_t id,unsigned char**out,uint32_t*bytes){
 (void)c;if(!id||id>NPC_PROGRAM_COUNT55)return 0;
 unsigned at=npcProgramFiles55[id-1].offset,n=npcProgramFiles55[id-1].bytes;
 *out=malloc(n);if(!*out)return 0;*bytes=n;
 return !fseek(scriptFile,at,SEEK_SET)&&fread(*out,1,n,scriptFile)==n;
}
static uint32_t functionId(void*c,const char*n){(void)c;return npc_function_id55(n);}
static int command(void*c,NpcMachine55*m,const char*n,const NpcValue55*a,uint32_t count,NpcValue55*out){
 (void)c;int status=npc_player_command55(&player,m,n,a,count,out);if(status>=0)return status;
 if(!strcmp(n,"cutin")||!strcmp(n,"emotion")){*out=npc_vm_number55(0);return N55_READY;}
 status=npc_career_world194(&world,m,runtime.attached,rootProgram,shared,n,a,count,out);
 if(status<0)fprintf(stderr,"unsupported %s\n",n);return status;
}
static const char*admit(Combat*g,unsigned destination){
 if(story_departure193(shared,g->mapId,destination))destination=0;
 unsigned result=campaign_access194(shared,destination,campaign_sandbox193(shared));
 return result==ACCESS_OPEN194?NULL:campaign_access_message194(result);
}
static void redirect(Combat*g,unsigned*map,float*x,float*y){
 if(story_departure193(shared,g->mapId,*map)){*map=0;*x=1460;*y=2804;}
}
static void story(unsigned cursor){Campaign200 c={0};c.cursor=cursor;if(cursor>1){c.route=1;c.lineage=1;}assert(campaign_store200(shared,&c));}
static uint32_t stateHash(void){
 uint32_t h=0;unsigned char*bytes=malloc(NPC_STATE_FILE55);assert(bytes);
 for(unsigned i=0;i<N55_VAR_DOMAINS;i++){
  assert(npc_state_encode55(shared+i,bytes,NPC_STATE_FILE55));h=crc32(h,bytes,npc_state_wire_bytes55(shared+i));h=crc32(h,(unsigned char*)&shared[i].revision,sizeof(unsigned));
 }
 assert(npc_state_encode55(&quests,bytes,NPC_STATE_FILE55));h=crc32(h,bytes,npc_state_wire_bytes55(&quests));
 for(NpcLocals55*l=runtime.variables.locals;l;l=l->next){assert(npc_state_encode55(&l->state,bytes,NPC_STATE_FILE55));h=crc32(h,bytes,npc_state_wire_bytes55(&l->state));h=crc32(h,(unsigned char*)&l->state.revision,sizeof(unsigned));}
 free(bytes);return h;
}
static void setText(const char*name,unsigned index,const char*value){
 NpcValue55 ref={0},v=npc_vm_string55(value);ref.kind=N55_REFERENCE_KIND;ref.text=name;ref.index=index;
 assert(npc_variable_write55(&runtime.variables,&ref,&v));
}
static void setNumber(const char*name,unsigned index,int64_t number){
 NpcValue55 ref={0},v=npc_vm_number55(number);ref.kind=N55_REFERENCE_KIND;ref.text=name;ref.index=index;
 assert(npc_variable_write55(&runtime.variables,&ref,&v));
}
static void setup(void){
 npc_runtime_clear55(&runtime);for(unsigned i=0;i<N55_VAR_DOMAINS;i++)npc_state_clear55(shared+i);npc_state_clear55(&quests);
 combat_init(&game,1000,1000,NULL,NULL);game.zeny=5000;game.mapId=2;game.level=99;
 game.home=(WorldPosition){2,1000,1000};player=(NpcPlayer55){&game,1,"Tester",1,1};
 NpcRuntimeApi55 api={readProgram,functionId,NULL,npc_player_read55,npc_player_write55,command,NULL,&player};
 npc_runtime_init55(&runtime,api,&quests,shared);world=(NpcWorld55){&game,mapNames,mapWidth43,mapHeight43,MYRO_MAP_COUNT43};
 npcTravelAdmission194=admit;npcTravelRedirect193=redirect;errorText[0]=0;story(1);
 assert(npc_state_set_number55(shared,npc_variable_key55("job_acolyte_q",0),0,3));
 assert(npc_state_set_number55(&quests,1014,0,1));
}
static void drive(int selectWanted){
 for(unsigned i=0;i<10000;i++){
  int status=npc_runtime_step55(&runtime,4096);
  if(world.pending)return;
  if(status==N55_ERROR){fprintf(stderr,"VM: %s pc=%u\n",runtime.machine.error,runtime.machine.pc);assert(0);}
  if(status==N55_DONE)return;
  if(status==N55_WAIT){
   if(runtime.dialogue.mode==N55_DIALOGUE_SELECT||runtime.dialogue.mode==N55_DIALOGUE_PROMPT){if(selectWanted)return;assert(0);}
   assert(npc_runtime_answer55(&runtime,0,0));
  }
 }
 assert(!"VM did not settle");
}
static void start(unsigned id){rootProgram=id;assert(npc_runtime_start55(&runtime,1,id,NULL,1,1000));drive(1);assert(runtime.dialogue.mode==N55_DIALOGUE_SELECT);}
static void deny(unsigned choice){
 beforeGame=game;beforeRuntime=runtime;NpcWorld55 oldWorld=world;uint32_t oldState=stateHash();
 for(unsigned i=0;i<10;i++){
  assert(!npc_travel_preflight194(&game,&runtime,&world,choice,errorText,sizeof(errorText)));
  assert(!memcmp(&game,&beforeGame,sizeof(game))&&!memcmp(&runtime,&beforeRuntime,sizeof(runtime)));
  assert(!memcmp(&world,&oldWorld,sizeof(world))&&stateHash()==oldState&&*errorText&&strlen(errorText)<sizeof(errorText));
 }
}
static void accept(unsigned choice){assert(npc_travel_preflight194(&game,&runtime,&world,choice,errorText,sizeof(errorText)));assert(npc_runtime_answer55(&runtime,choice,0));drive(0);}
static void kafra(void){
 setup();rootProgram=1;setText("@wrpC$",0,"Morroc");setText("@wrpD$",0,"Morroc");setNumber("@wrpP",0,1000);
 setText("@wrpC$",1,"Cancel");setText("@wrpD$",1,"Cancel");
 int64_t ticket=0;assert(npc_constant55("Warp_Free_Ticket",&ticket));assert(npc_item_give55(&game,(unsigned)ticket,1,1,NULL,NULL));
 /* A real global-helper call frame supplies the native mode/title arguments. */
 runtime.attached=1;NpcApi55 api={npc_runtime_read55,npc_runtime_write55,npc_runtime_call55,npc_runtime_resolve55,npc_runtime_release55,&runtime};
 assert(npc_vm_start55(&runtime.machine,&caller,0,caller.owner,api));drive(1);deny(0);
 /* Exercise the actual production A-button hook as well as its pure helper. */
 memset(&inputContext,0,sizeof(inputContext));inputContext.player.game=&game;
 inputContext.ui=0;inputContext.pendingTalk=inputContext.lobby=inputContext.storage64.slot=inputContext.book64.slot=-1;
 inputContext.vm[0]=runtime;inputContext.world[0]=world;
 uint32_t beforeState=stateHash();beforeGame=game;beforeRuntime=runtime;
 char reason[160]={0};
 for(unsigned i=0;i<10;i++){
  npc_game_input55(&inputContext,2);assert(!memcmp(&inputContext.vm[0],&beforeRuntime,sizeof(runtime)));
  assert(!memcmp(&game,&beforeGame,sizeof(game))&&stateHash()==beforeState&&!inputContext.world[0].pending);
  assert(inputContext.vm[0].dialogue.count==2&&inputContext.vm[0].dialogue.ordinals[0]==1&&inputContext.vm[0].dialogue.ordinals[1]==2);
  if(i)assert(!strcmp(reason,inputContext.error));else snprintf(reason,sizeof(reason),"%s",inputContext.error);
 }
 assert(npc_travel_preflight194(&game,&runtime,&world,1,errorText,sizeof(errorText))); /* Cancel stays original. */
 story(35);assert(npc_item_take55(&game,(unsigned)ticket,1));accept(0);
 assert(world.pending&&world.map==127&&game.zeny==4000);
 puts("PASS actual F_KafTele: ten denials preserve complete VM/character/state and free ticket; admitted native fare is 1000 Zeny");
}
int main(int argc,char**argv){
 assert(argc==2);scriptFile=fopen(argv[1],"rb");assert(scriptFile);
 kafra();setup();start(696);assert(runtime.machine.pc==85);deny(3);story(35);accept(3);
 assert(world.pending&&world.map==127&&game.zeny==3200);
 puts("PASS actual Airship Representative: denied Morroc preserves resources; native admitted fare is 1800 Zeny");
 setup();game.jobId=J52_HIGH_NOVICE;start(3604);assert(runtime.machine.pc==68);accept(1);
 assert(world.pending&&world.map==126&&game.home.map==126&&game.home.x==1204&&game.home.y==940&&game.zeny==5000);
 puts("PASS actual Valkyrie: Morroc selection and savepoint use outpost 126; money unchanged");
 setup();game.mapId=453;story(0);start(3866);
 /* Advance the first service menu into the original destination menu. */
 assert(npc_runtime_answer55(&runtime,0,0));drive(1);
 assert(runtime.machine.pc==164||runtime.machine.pc==442);accept(1);
 assert(world.pending&&world.map==0&&game.home.map==0);
 puts("PASS actual Training Kafra: first-departure destination is preflighted and redirected into the opening");
 npc_runtime_clear55(&runtime);for(unsigned i=0;i<N55_VAR_DOMAINS;i++)npc_state_clear55(shared+i);npc_state_clear55(&quests);fclose(scriptFile);
 puts("HOST integration only; no native build or Xbox/Xemu playtest");
}
