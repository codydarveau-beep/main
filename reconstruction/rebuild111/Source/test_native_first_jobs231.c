/* Real released quest final branches via full NPC open/dispatcher/VM.
 * Earlier quest progress, items and completed OnInit are explicit fixtures. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#ifndef WORLD_MAP_COUNT
#include "world_data.h"
#endif
#include "npc_game55.h"
#include "native_admission194.h"
#include "campaign_career200.h"
static Combat game;
static NpcVariables55 variables231;
static NpcState55 quests,*questPins65;
#define shared variables231.domain
static NpcGame55 context231;
static NativeAdmissionCache194 access231;
static FILE*scriptFile;
#include "../Validation/actual_job_guard228.inc"
static int read231(void*ctx,unsigned kind,uint32_t at,unsigned char*out,uint32_t bytes){(void)ctx;return kind==0&&!fseek(scriptFile,at,SEEK_SET)&&fread(out,1,bytes,scriptFile)==bytes;}
static const char*admission231(unsigned id){return native_admission_reason194(&access231,id);}
static void setup(void){npc_game_clear55(&context231);npc_variables_clear55(&variables231);npc_state_clear55(&quests);combat_init(&game,1000,1000,NULL,NULL);game.zeny=5000;game.level=99;game.statPoints=stat_budget(game.level)-stat_spent(game.stats);npc_game_init55(&context231,&game,&variables231,&quests,read231,NULL,NULL,NULL,0);Campaign200 c={0};c.cursor=1;assert(campaign_store200(shared,&c));npcNativeAdmission194=admission231;}
static void setNumber(const char*name,unsigned index,int64_t value){NpcValue55 ref={0},number=npc_vm_number55(value);ref.kind=N55_REFERENCE_KIND;ref.text=name;ref.index=index;assert(npc_variable_write55(&context231.vm[0].variables,&ref,&number));}
static unsigned steps231,choice231;
static void give231(const char*name,unsigned n){int64_t source;assert(npc_constant55(name,&source)&&npc_item_give55(&game,(unsigned)source,n,1,NULL,NULL));}
static unsigned source231(const char*name){int64_t source;assert(npc_constant55(name,&source));return(unsigned)source;}
static void run231(unsigned program){unsigned npc=NPC_RECORD_COUNT55;for(unsigned i=0;i<NPC_RECORD_COUNT55;i++)if(npcRecords55[i].program==program&&npcRecords55[i].map<MYRO_MAP_COUNT43){npc=i;break;}assert(npc<NPC_RECORD_COUNT55);game.mapId=npcRecords55[npc].map;game.x=npcRecords55[npc].x;game.y=npcRecords55[npc].y;native_admission_refresh194(&access231,shared,0);assert(!native_admission_reason194(&access231,npc));/* Prior OnInit completion is explicit; its lifecycle is tested separately. */context231.scene.flags[npc]|=N55_NPC_INIT_DONE;assert(npc_game_open55(&context231,npc));for(unsigned i=0;i<10000;i++){int status=npc_runtime_step55(context231.vm,4096);steps231++;if(status==N55_ERROR){fprintf(stderr,"Native job %u error %s pc %u\n",program,context231.vm[0].machine.error,context231.vm[0].machine.pc);assert(0);}if(status==N55_DONE)return;if(status==N55_WAIT)assert(npc_runtime_answer55(context231.vm,context231.vm[0].dialogue.mode==N55_DIALOGUE_SELECT?choice231:0,0));}assert(!"native job did not settle");}
int main(int argc,char**argv){setvbuf(stdout,NULL,_IONBF,0);assert(argc==2);scriptFile=fopen(argv[1],"rb");assert(scriptFile);unsigned programs[]={3833,3824,3819,3856,3823,3827},jobs[]={1,2,3,4,5,6},quests231[]={1014,1005,1017,1013,1004,1009};const char*flags[]={"job_sword_q","job_magician_q","job_acolyte_q","job_thief_q","job_archer_q","job_merchant_q"};unsigned ready[]={4,1,7,3,1,7};
 /* Completed Thief/Merchant interview/delivery flags already certify Basic 9;
 * do not combine those flags with an impossible earlier skill state. */
 for(unsigned c=0;c<6;c++)for(unsigned variant=0;variant<4;variant++){if((variant==1&&(c==3||c==5))||(variant==2&&c!=1&&c!=3&&c!=4&&c!=5)||(variant==3&&c!=5))continue;setup();choice231=variant==3;game.joblevel=10;game.ranks[310]=variant==1?8:9;game.skillPoints=0;game.mapId=c==0?4:c==1?42:c==2?9:c==3?128:c==4?12:132;questPins65=shared;campaignJobGuard200=campaign_job_guard200;setNumber(flags[c],0,ready[c]);assert(npc_state_set_number55(&quests,quests231[c],0,1));if(c==1&&variant!=2)give231("Mage_Test_1",1);if(c==3)give231("Mushroom_Of_Thief_1",variant==2?8:10);if(c==4)give231("Tree_Of_Archer_1",variant==2?4:10);if(c==5&&variant==2)game.zeny=499;unsigned money=game.zeny;OwnedItems52 owned=game.owned52;run231(programs[c]);if(variant){if(game.jobId||game.zeny!=money||memcmp(&owned,&game.owned52,sizeof owned))fprintf(stderr,"Rejected native branch program %u variant %u job %u money %u/%u pc %u\n",programs[c],variant,game.jobId,game.zeny,money,context231.vm[0].machine.pc);assert(game.jobId==0&&game.zeny==money&&!memcmp(&owned,&game.owned52,sizeof owned)&&!campaign_job_proof200(shared,0));continue;}if(game.jobId!=jobs[c])fprintf(stderr,"Native job %u stayed job %u pc %u\n",programs[c],game.jobId,context231.vm[0].machine.pc);assert(game.jobId==jobs[c]);assert(campaign_job_proof200(shared,game.jobId));Campaign200 story231;assert(campaign_load200(shared,&story231)==1&&story231.cursor==1&&(story231.objectives&1)&&!story231.route);if(game.zeny!=money+(c==1?50:c==3?350:0)-(c==5?500:0))fprintf(stderr,"Native job %u money before %u after %u\n",programs[c],money,game.zeny);assert(game.zeny==money+(c==1?50:c==3?350:0)-(c==5?500:0));if(c==1)assert(!npc_item_count55(&game,source231("Mage_Test_1")));if(c==3)assert(!npc_item_count55(&game,source231("Mushroom_Of_Thief_1")));if(c==4)assert(!npc_item_count55(&game,source231("Tree_Of_Archer_1"))&&npc_item_count55(&game,source231("Bow_"))==1);money=game.zeny;owned=game.owned52;unsigned revision=shared[0].revision;run231(programs[c]);assert(game.jobId==jobs[c]&&game.zeny==money&&!memcmp(&owned,&game.owned52,sizeof owned));assert(campaign_job_proof200(shared,game.jobId)&&shared[0].revision==revision);printf("PASS native final quest branch program %u -> job %u; campaign proof and original fee/material/reward path.\n",programs[c],jobs[c]);}
 npc_game_clear55(&context231);npc_variables_clear55(&variables231);npc_state_clear55(&quests);fclose(scriptFile);printf("PASS native first-job runtime integration (%u VM steps). Prior quest prerequisites are fixtures, not complete native quest playthroughs or Xbox testing.\n",steps231);return 0;}
