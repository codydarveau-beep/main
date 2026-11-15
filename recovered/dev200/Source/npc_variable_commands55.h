/* MIT. Dynamic variable references used by original NPC test/course scripts. */
#ifndef MYRO_NPC_VARIABLE_COMMANDS55_H
#define MYRO_NPC_VARIABLE_COMMANDS55_H
#include "npc_builtins55.h"
#include "npc_variables55.h"
static int npc_dynamic_ref55(NpcMachine55*m,const char*name,NpcValue55*out){
 if(!name||!*name)return 0;size_t n=0;while(name[n]&&name[n]!='['){unsigned char c=(unsigned char)name[n];if(!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='_'||c=='.'||c=='@'||c=='$'||c=='#'||c=='\''))return 0;n++;}if(!n||n>255)return 0;
 uint32_t index=0;if(name[n]){size_t at=n+1;if(name[at]<'0'||name[at]>'9')return 0;while(name[at]>='0'&&name[at]<='9'){unsigned digit=name[at++]-'0';if(index>(NPC_STATE_INDEX55-1-digit)/10)return 0;index=index*10+digit;}if(name[at]!=']'||name[at+1])return 0;}
 NpcValue55 copy;if(!npc_text_copy55(m,name,n,&copy))return 0;*out=copy;out->kind=N55_REFERENCE_KIND;out->index=index;out->owner=m->owner;out->frame=m->frame;return 1;
}
static int npc_variable_command55(NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out,uint64_t(*npcOwner)(void*,const char*),void*context){
 int get=!strcmp(name,"getd"),set=!strcmp(name,"setd"),other=!strcmp(name,"getvariableofnpc");if(!get&&!set&&!other)return-1;if(count!=(get?1:2))return N55_ERROR;NpcValue55 text,ref;
 if(other){if(args[0].kind!=N55_REFERENCE_KIND||!args[0].text||args[0].text[0]!='.'||args[0].text[1]=='@'||!npc_vm_value55(m,args[1],&text)||text.kind!=N55_STRING_KIND||!npcOwner)return N55_ERROR;uint64_t owner=npcOwner(context,text.text);if(!owner)return N55_ERROR;ref=args[0];ref.owner=owner;*out=ref;return N55_READY;}
 if(!npc_vm_value55(m,args[0],&text)||text.kind!=N55_STRING_KIND||!npc_dynamic_ref55(m,text.text,&ref))return N55_ERROR;
 if(get){*out=ref;return N55_READY;}NpcValue55 value;if(!npc_vm_value55(m,args[1],&value)||!m->api.write||!m->api.write(m->api.context,&ref,&value))return N55_ERROR;*out=npc_vm_number55(0);return N55_READY;
}
#endif
