/* MIT. Shared conversation runtime; platform/game operations use explicit adapters. */
#ifndef MYRO_NPC_RUNTIME55_H
#define MYRO_NPC_RUNTIME55_H
#include "npc_program_cache55.h"
#include "npc_arrays55.h"
#include "npc_variable_commands55.h"
#include "npc_dialogue55.h"
#include "npc_input55.h"
#include "npc_quest_commands55.h"
#include "npc_constants_data55.h"
#include "npc_format55.h"
typedef struct{NpcProgramRead55 readProgram;uint32_t(*functionId)(void*,const char*);uint64_t(*npcOwner)(void*,const char*);NpcRead55 readPlayer;NpcWrite55 writePlayer;NpcCall55 command;uint32_t(*random)(void*);void*context;}NpcRuntimeApi55;
/* Keep this on the heap or in static storage: the bounded VM/text buffers are large. */
typedef struct{NpcMachine55 machine;NpcVariables55 variables;NpcDialogue55 dialogue;NpcInput55 input;NpcProgramCache55 programs;NpcProgramCache55*sharedPrograms;NpcState55*quests;NpcRuntimeApi55 api;int64_t utc;uint32_t npc,attached;}NpcRuntime55;
static int npc_runtime_player_variable55(const char*name){return*name!='.'&&*name!='$'&&*name!='\'';}
/* Player adapters return -1 for an ordinary script variable, 0 on failure, 1 on success. */
static int npc_runtime_read55(void*context,const NpcValue55*ref,NpcValue55*out){NpcRuntime55*r=context;int64_t constant;
 if(r->api.readPlayer){int handled=r->api.readPlayer(r->api.context,ref,out);if(handled>=0)return r->attached&&handled;}
 if(npc_constant55(ref->text,&constant)){*out=npc_vm_number55(constant);return 1;}if(!r->attached&&npc_runtime_player_variable55(ref->text))return 0;return npc_variable_read55(&r->variables,ref,out);
}
static int npc_runtime_write55(void*context,const NpcValue55*ref,const NpcValue55*value){NpcRuntime55*r=context;int64_t constant;
 if(r->api.writePlayer){if(!r->attached&&npc_runtime_player_variable55(ref->text))return 0;int handled=r->api.writePlayer(r->api.context,ref,value);if(handled>=0)return handled;}
 if(npc_constant55(ref->text,&constant)||(!r->attached&&npc_runtime_player_variable55(ref->text)))return 0;return npc_variable_write55(&r->variables,ref,value);
}
static const NpcProgram55*npc_runtime_resolve55(void*context,const char*name){NpcRuntime55*r=context;uint32_t id=r->api.functionId?r->api.functionId(r->api.context,name):0;return id?npc_program_cached55(r->sharedPrograms?r->sharedPrograms:&r->programs,&r->machine,id):NULL;}
static void npc_runtime_release55(void*context,uint32_t frame){NpcRuntime55*r=context;npc_variable_release_frame55(&r->variables,frame);}
static int npc_runtime_quest_command55(const char*name){return!strcmp(name,"setquest")||!strcmp(name,"erasequest")||!strcmp(name,"completequest")||!strcmp(name,"changequest")||!strcmp(name,"questprogress")||!strcmp(name,"checkquest")||!strcmp(name,"questactive");}
/* Commands here require a character even when called from an OnInit/global event. */
static int npc_runtime_player_command55(const char*name){static const char*const names[]={"getskilllv","jobchange","skill","getgroupid","getgmlevel","getcharid","strcharinfo","getexp","percentheal","heal","getitem","delitem","countitem","checkweight","getequipid","isequipped","checkmount","hascashmount","checkcart","checkfalcon","setcart","resetlvl","getlook","setlook","readparam","getequipname","getequipisequiped","getequipisenableref","getequipisidentify","getequiprefinerycnt","getequipweaponlv","getequippercentrefinery","successrefitem","failedrefitem","downrefitem","getbrokenid","getbrokencount","repair","repairall"};for(unsigned i=0;i<sizeof(names)/sizeof(*names);i++)if(!strcmp(name,names[i]))return 1;return 0;}
static int npc_runtime_call55(void*context,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){NpcRuntime55*r=context;int status;
 if(!r->attached&&npc_array_action55(name)&&count&&args[0].kind==N55_REFERENCE_KIND&&npc_runtime_player_variable55(args[0].text))return N55_ERROR;
 status=npc_array_command55(m,&r->variables,name,args,count,out);if(status>=0)return status;
 status=npc_variable_command55(m,name,args,count,out,r->api.npcOwner,r->api.context);if(status>=0)return status;
 if(!strcmp(name,"_$")){if(count!=1||!npc_vm_value55(m,args[0],out)||out->kind!=N55_STRING_KIND)return N55_ERROR;return N55_READY;}
 if(!strcmp(name,"sprintf")||!strcmp(name,"mesf")){status=npc_format55(m,args,count,out);if(status!=N55_READY||!strcmp(name,"sprintf"))return status;NpcValue55 text=*out;return npc_dialogue_command55(&r->dialogue,m,"mes",&text,1,out);}
 status=npc_builtin55(m,name,args,count,out,r->api.random,r->api.context);if(status>=0)return status;
 if(!strcmp(name,"input")){if(!r->attached)return N55_ERROR;return npc_input_command55(&r->input,m,name,args,count,out);}
 status=npc_dialogue_command55(&r->dialogue,m,name,args,count,out);if(status>=0)return status;
 if(npc_runtime_quest_command55(name)){if(!r->attached||!r->quests)return N55_ERROR;status=npc_quest_command55(m,r->quests,r->utc,name,args,count,out);return status>0?N55_READY:N55_ERROR;}
 if(!strcmp(name,"playerattached")){if(count)return N55_ERROR;*out=npc_vm_number55(r->attached?1:0);if(r->attached&&r->api.command)return r->api.command(r->api.context,m,name,args,count,out);return N55_READY;}
 if(!r->attached&&npc_runtime_player_command55(name))return N55_ERROR;
 if(r->api.command)return r->api.command(r->api.context,m,name,args,count,out);return N55_ERROR;
}
static void npc_runtime_init55(NpcRuntime55*r,NpcRuntimeApi55 api,NpcState55*quests,NpcState55*shared){memset(r,0,sizeof(*r));r->api=api;r->quests=quests;r->variables.shared=shared;r->programs.read=api.readProgram;r->programs.context=api.context;r->machine.status=N55_DONE;}
static void npc_runtime_cancel55(NpcRuntime55*r){npc_vm_cancel55(&r->machine);while(r->variables.locals)npc_variable_release_frame55(&r->variables,r->variables.locals->frame);memset(&r->dialogue,0,sizeof(r->dialogue));memset(&r->input,0,sizeof(r->input));}
static int npc_runtime_start55(NpcRuntime55*r,uint32_t npc,uint32_t program,const char*label,int attached,int64_t utc){npc_runtime_cancel55(r);const NpcProgram55*p=npc_program_cached55(r->sharedPrograms?r->sharedPrograms:&r->programs,NULL,program);if(!p)return 0;uint32_t entry=0;if(label&&*label&&!npc_vm_entry55(p,p->labels,p->labelCount,label,&entry))return 0;r->npc=npc;r->attached=!!attached;r->utc=utc;NpcApi55 api={npc_runtime_read55,npc_runtime_write55,npc_runtime_call55,npc_runtime_resolve55,npc_runtime_release55,r};return npc_vm_start55(&r->machine,p,entry,p->owner,api);}
static int npc_runtime_start_at55(NpcRuntime55*r,uint32_t npc,uint32_t program,uint32_t entry,int attached,int64_t utc){npc_runtime_cancel55(r);const NpcProgram55*p=npc_program_cached55(r->sharedPrograms?r->sharedPrograms:&r->programs,NULL,program);if(!p||entry>=p->count)return 0;r->npc=npc;r->attached=!!attached;r->utc=utc;NpcApi55 api={npc_runtime_read55,npc_runtime_write55,npc_runtime_call55,npc_runtime_resolve55,npc_runtime_release55,r};return npc_vm_start55(&r->machine,p,entry,p->owner,api);}
static int npc_runtime_step55(NpcRuntime55*r,uint32_t budget){int result=npc_vm_run55(&r->machine,budget);if(result==N55_DONE)memset(&r->dialogue,0,sizeof(r->dialogue));return result;}
static int npc_runtime_answer55(NpcRuntime55*r,uint32_t choice,int cancel){return npc_dialogue_answer55(&r->dialogue,&r->machine,choice,cancel);}
static int npc_runtime_input55(NpcRuntime55*r,int64_t number,const char*text,int cancel){return npc_input_answer55(&r->input,&r->machine,number,text,cancel);}
static void npc_runtime_clear55(NpcRuntime55*r){npc_runtime_cancel55(r);npc_program_cache_clear55(&r->programs);npc_variables_clear55(&r->variables);memset(r,0,sizeof(*r));}
#endif
