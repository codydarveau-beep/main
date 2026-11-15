/* MIT. Sparse original-script arrays; failed edits leave the original store intact. */
#ifndef MYRO_NPC_ARRAYS55_H
#define MYRO_NPC_ARRAYS55_H
#include "npc_variables55.h"
#include "npc_builtins55.h"
static uint32_t npc_array_size55(const NpcState55*s,uint64_t key){if(!s)return 0;int found;uint32_t at=npc_state_find55(s,key,0,&found),size=0;while(at<s->count&&s->entries[at].key==key)size=s->entries[at++].index+1;return size;}
static int npc_state_clone55(NpcState55*out,const NpcState55*source){uint32_t bytes=npc_state_wire_bytes55(source);unsigned char*wire=malloc(bytes);if(!wire)return 0;int result=npc_state_encode55(source,wire,bytes)&&npc_state_decode55(out,wire,bytes);free(wire);return result;}
static int npc_array_string55(const NpcValue55*r){size_t n=strlen(r->text);return n&&r->text[n-1]=='$';}
static int npc_array_store_value55(NpcState55*s,uint64_t key,uint32_t index,int string,NpcValue55 v){return string?v.kind==N55_STRING_KIND&&v.text&&npc_state_set_text55(s,key,index,v.text,(uint32_t)strlen(v.text)):v.kind==N55_NUMBER_KIND&&npc_state_set_number55(s,key,index,v.number);}
static void npc_array_delete55(NpcState55*s,uint64_t key,uint32_t start,uint32_t count){int found;uint32_t at=npc_state_find55(s,key,start,&found);uint32_t end=count>NPC_STATE_INDEX55-start?NPC_STATE_INDEX55:start+count;while(at<s->count&&s->entries[at].key==key&&s->entries[at].index<end){NpcVariable55*v=s->entries+at;s->textBytes-=v->length;NPC_STATE_FREE55(v->text);memmove(v,v+1,(s->count-at-1)*sizeof(*v));s->count--;s->revision++;}for(;at<s->count&&s->entries[at].key==key;at++){s->entries[at].index-=end-start;s->revision++;}}
static int npc_array_action55(const char*name){return!strcmp(name,"getarraysize")?1:!strcmp(name,"getelementofarray")?2:!strcmp(name,"setarray")?3:!strcmp(name,"copyarray")?4:!strcmp(name,"deletearray")?5:!strcmp(name,"implode")?6:0;}
static int npc_array_command55(NpcMachine55*m,NpcVariables55*variables,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 int action=npc_array_action55(name);if(!action)return-1;
 if(!count||args[0].kind!=N55_REFERENCE_KIND||!args[0].text)return N55_ERROR;NpcValue55 ref=args[0];uint64_t key=0;NpcState55*s=npc_variable_domain55(variables,&ref,action>=3&&action<=5,&key);if(!key)return N55_ERROR;
 *out=npc_vm_number55(0);if(action==1){if(count!=1)return N55_ERROR;*out=npc_vm_number55(npc_array_size55(s,key));return N55_READY;}
 if(action==2){int64_t index;if(count!=2||!npc_vm_integer55(m,args[1],&index)||index<0||index>=NPC_STATE_INDEX55)return N55_ERROR;ref.index=(uint32_t)index;*out=ref;return N55_READY;}
 if(action==6){
  if(count>2||!npc_array_string55(&ref))return N55_ERROR;NpcValue55 glue=npc_vm_string55("");if(count==2&&(!npc_vm_value55(m,args[1],&glue)||glue.kind!=N55_STRING_KIND))return N55_ERROR;
  unsigned size=npc_array_size55(s,key);if(!size){*out=npc_vm_string55("NULL");return N55_READY;}size_t length=0,glueLen=strlen(glue.text),room=NPC_VM_TEXT55-m->textUsed;
  for(unsigned i=0;i<size;i++){const NpcVariable55*v=s?npc_state_get55(s,key,i):NULL;size_t add=(v?v->length:0)+(i?glueLen:0);if(add>=room||length>=room-add)return N55_ERROR;length+=add;}
  char*p=m->text+m->textUsed;size_t used=0;for(unsigned i=0;i<size;i++){const NpcVariable55*v=s?npc_state_get55(s,key,i):NULL;if(i){memmove(p+used,glue.text,glueLen);used+=glueLen;}if(v){memmove(p+used,v->text,v->length);used+=v->length;}}p[used]=0;m->textUsed+=(uint32_t)used+1;*out=npc_vm_string55(p);return N55_READY;
 }
 if(!s)return N55_ERROR;int string=npc_array_string55(&ref);int64_t amount=0;uint64_t sourceKey=0;NpcState55*source=NULL;NpcValue55 sourceRef={0};
 if(action==3){if(count<2||count-1>NPC_STATE_INDEX55-ref.index)return N55_ERROR;amount=count-1;}
 else if(action==4){if(count!=3||args[1].kind!=N55_REFERENCE_KIND||!args[1].text||npc_array_string55(args+1)!=string||!npc_vm_integer55(m,args[2],&amount)||amount<0||amount>NPC_STATE_INDEX55-ref.index||amount>NPC_STATE_INDEX55-args[1].index)return N55_ERROR;sourceRef=args[1];source=npc_variable_domain55(variables,&sourceRef,0,&sourceKey);if(!sourceKey)return N55_ERROR;}
 else{if(count>2)return N55_ERROR;amount=NPC_STATE_INDEX55-ref.index;if(count==2&&(!npc_vm_integer55(m,args[1],&amount)||amount<0||amount>NPC_STATE_INDEX55-ref.index))return N55_ERROR;}
 if(!amount)return N55_READY;NpcState55 trial={0};if(!npc_state_clone55(&trial,s))return N55_ERROR;int ok=1;
 if(action==5)npc_array_delete55(&trial,key,ref.index,(uint32_t)amount);
 else for(uint32_t i=0;i<(uint32_t)amount&&ok;i++){NpcValue55 v;
  if(action==4){const NpcVariable55*stored=source?npc_state_get55(source,sourceKey,sourceRef.index+i):NULL;v=string?npc_vm_string55(stored?stored->text:""):npc_vm_number55(stored?stored->number:0);}
  else{NpcValue55 input=args[i+1];uint64_t inputKey=0;NpcState55*inputState=input.kind==N55_REFERENCE_KIND?npc_variable_domain55(variables,&input,0,&inputKey):NULL;
   if(inputState==s&&inputKey){const NpcVariable55*stored=npc_state_get55(&trial,inputKey,input.index);v=npc_array_string55(&input)?npc_vm_string55(stored?stored->text:""):npc_vm_number55(stored?stored->number:0);}else if(!npc_vm_value55(m,input,&v)){ok=0;break;}}
  ok=npc_array_store_value55(&trial,key,ref.index+i,string,v);
 }
 if(!ok){npc_state_clear55(&trial);return N55_ERROR;}npc_state_clear55(s);*s=trial;return N55_READY;
}
#endif
