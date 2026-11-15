/* MIT. Original script variable lifetimes for the single-player NPC interpreter. */
#ifndef MYRO_NPC_VARIABLES55_H
#define MYRO_NPC_VARIABLES55_H
#include "npc_vm55.h"
#include "npc_state55.h"
enum{N55_VAR_CHARACTER,N55_VAR_ACCOUNT,N55_VAR_WORLD,N55_VAR_CHARACTER_TEMP,N55_VAR_WORLD_TEMP,N55_VAR_NPC,N55_VAR_INSTANCE,N55_VAR_DOMAINS};
typedef struct NpcLocals55{uint32_t frame;NpcState55 state;struct NpcLocals55*next;}NpcLocals55;
typedef struct{NpcState55 domain[N55_VAR_DOMAINS];NpcState55*shared;NpcLocals55*locals;uint32_t localCount;uint64_t instance;}NpcVariables55;
static uint64_t npc_variable_key55(const char*name,uint64_t owner){uint64_t hash=UINT64_C(14695981039346656037);for(unsigned i=0;i<8;i++){hash^=(unsigned char)(owner>>(i*8));hash*=UINT64_C(1099511628211);}for(;*name;name++){hash^=(unsigned char)*name;hash*=UINT64_C(1099511628211);}return hash?hash:1;}
static NpcState55*npc_variable_domain55(NpcVariables55*v,const NpcValue55*ref,int create,uint64_t*key){
 if(!v||!ref||ref->kind!=N55_REFERENCE_KIND||!ref->text||!*ref->text||ref->index>=NPC_STATE_INDEX55)return NULL;
 const char*n=ref->text;uint64_t owner=0;unsigned domain=N55_VAR_CHARACTER;
 if(n[0]=='.'&&n[1]=='@'){
  if(!ref->frame)return NULL;NpcLocals55*local=v->locals;while(local&&local->frame!=ref->frame)local=local->next;
  if(!local&&create){if(v->localCount>=NPC_VM_FRAMES55+1)return NULL;local=calloc(1,sizeof(*local));if(!local)return NULL;local->frame=ref->frame;local->next=v->locals;v->locals=local;v->localCount++;}
  *key=npc_variable_key55(n,0);return local?&local->state:NULL;
 }
 if(n[0]=='.'){domain=N55_VAR_NPC;owner=ref->owner;if(!owner)return NULL;}
 else if(n[0]=='\''){domain=N55_VAR_INSTANCE;owner=v->instance;if(!owner)return NULL;}
 else if(n[0]=='@')domain=N55_VAR_CHARACTER_TEMP;
 else if(n[0]=='$')domain=n[1]=='@'?N55_VAR_WORLD_TEMP:N55_VAR_WORLD;
 else if(n[0]=='#')domain=N55_VAR_ACCOUNT;
 *key=npc_variable_key55(n,owner);return (v->shared?v->shared:v->domain)+domain;
}
static int npc_variable_read55(void*opaque,const NpcValue55*ref,NpcValue55*out){
 NpcVariables55*v=opaque;uint64_t key=0;NpcState55*s=npc_variable_domain55(v,ref,0,&key);
 if(!key)return 0;size_t len=strlen(ref->text);int string=ref->text[len-1]=='$';const NpcVariable55*stored=s?npc_state_get55(s,key,ref->index):NULL;
 if(stored&&(string?stored->kind!=NPC_STATE_STRING_KIND55:stored->kind!=NPC_STATE_NUMBER55))return 0;
 *out=string?npc_vm_string55(stored?stored->text:""):npc_vm_number55(stored?stored->number:0);return 1;
}
static int npc_variable_write55(void*opaque,const NpcValue55*ref,const NpcValue55*value){
 uint64_t key=0;NpcState55*s=npc_variable_domain55(opaque,ref,1,&key);if(!s||!key||!value)return 0;size_t len=strlen(ref->text);
 if(ref->text[len-1]=='$')return value->kind==N55_STRING_KIND&&value->text&&npc_state_set_text55(s,key,ref->index,value->text,(uint32_t)strlen(value->text));
 return value->kind==N55_NUMBER_KIND&&npc_state_set_number55(s,key,ref->index,value->number);
}
static void npc_variable_release_frame55(void*opaque,uint32_t frame){NpcVariables55*v=opaque;NpcLocals55**link=&v->locals;while(*link){NpcLocals55*local=*link;if(local->frame==frame){*link=local->next;npc_state_clear55(&local->state);free(local);v->localCount--;return;}link=&local->next;}}
static void npc_variables_clear55(NpcVariables55*v){while(v->locals)npc_variable_release_frame55(v,v->locals->frame);for(unsigned i=0;i<N55_VAR_DOMAINS;i++)npc_state_clear55(v->domain+i);}
/* Session/server reset, never a map transition: retain persistent quest flags. */
static void npc_variables_reset_transient55(NpcVariables55*v){while(v->locals)npc_variable_release_frame55(v,v->locals->frame);if(!v->shared)for(unsigned i=N55_VAR_CHARACTER_TEMP;i<N55_VAR_DOMAINS;i++)npc_state_clear55(v->domain+i);}
#endif
