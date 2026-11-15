/* MIT. Source-compatible integer/string helpers used by ordinary NPC quests. */
#ifndef MYRO_NPC_BUILTINS55_H
#define MYRO_NPC_BUILTINS55_H
#include "npc_vm55.h"
static unsigned char npc_ascii_lower55(unsigned char c){return c>='A'&&c<='Z'?(unsigned char)(c+32):c;}
static int npc_text_copy55(NpcMachine55*m,const char*text,size_t length,NpcValue55*out){if(length>=NPC_VM_TEXT55-m->textUsed)return npc_vm_error55(m,"NPC temporary text limit");char*p=m->text+m->textUsed;memmove(p,text,length);p[length]=0;m->textUsed+=(uint32_t)length+1;*out=npc_vm_string55(p);return 1;}
#include "npc_string59.h"
static int npc_builtin55(NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out,uint32_t(*random)(void*),void*context){
 int extended=npc_string_command59(m,name,args,count,out);if(extended>=0)return extended;int min=!strcmp(name,"min"),max=!strcmp(name,"max");if(min||max){if(!count)return N55_ERROR;int64_t result;if(!npc_vm_integer55(m,args[0],&result))return N55_ERROR;for(uint32_t i=1;i<count;i++){int64_t n;if(!npc_vm_integer55(m,args[i],&n))return N55_ERROR;if(min?n<result:n>result)result=n;}*out=npc_vm_number55(result);return N55_READY;}
 if(!strcmp(name,"rand")){int64_t a,b;if(count<1||count>2||!npc_vm_integer55(m,args[0],&a)||a<INT32_MIN||a>INT32_MAX)return N55_ERROR;if(count==1){b=a-1;a=0;}else if(!npc_vm_integer55(m,args[1],&b)||b<INT32_MIN||b>INT32_MAX)return N55_ERROR;else if(b<a){int64_t t=a;a=b;b=t;}if(b<=a){*out=npc_vm_number55(a);return N55_READY;}if(!random)return N55_ERROR;uint64_t span=(uint64_t)(b-a)+1;*out=npc_vm_number55(a+(int64_t)((uint64_t)random(context)%span));return N55_READY;}
 int length=!strcmp(name,"getstrlen"),lower=!strcmp(name,"strtolower"),substr=!strcmp(name,"substr"),compare=!strcmp(name,"compare"),atoiCommand=!strcmp(name,"atoi"),identity=(!strcmp(name,"_")||!strcmp(name,"_$"));if(!length&&!lower&&!substr&&!compare&&!atoiCommand&&!identity)return-1;
 if(!count||count!=(substr?3:compare?2:1))return N55_ERROR;NpcValue55 text;if(!npc_vm_value55(m,args[0],&text)||text.kind!=N55_STRING_KIND)return N55_ERROR;size_t n=strlen(text.text);
 if(identity){*out=text;return N55_READY;}if(length){*out=npc_vm_number55((int64_t)n);return N55_READY;}
 if(lower){if(!npc_text_copy55(m,text.text,n,out))return N55_ERROR;char*p=(char*)out->text;for(size_t i=0;i<n;i++)p[i]=(char)npc_ascii_lower55((unsigned char)p[i]);return N55_READY;}
 if(substr){int64_t first,last;if(!npc_vm_integer55(m,args[1],&first)||!npc_vm_integer55(m,args[2],&last))return N55_ERROR;if(first<0||last<first||(uint64_t)last>=n){*out=npc_vm_string55("");return N55_READY;}return npc_text_copy55(m,text.text+first,(size_t)(last-first+1),out)?N55_READY:N55_ERROR;}
 if(compare){NpcValue55 needle;if(!npc_vm_value55(m,args[1],&needle)||needle.kind!=N55_STRING_KIND)return N55_ERROR;size_t size=strlen(needle.text);int found=0;if(size<=n)for(size_t i=0;i<=n-size;i++){size_t j;for(j=0;j<size;j++)if(npc_ascii_lower55((unsigned char)text.text[i+j])!=npc_ascii_lower55((unsigned char)needle.text[j]))break;if(j==size){found=1;break;}}*out=npc_vm_number55(found);return N55_READY;}
 /* atoi is a 32-bit source command. Clamp hostile/overflow input instead of wrapping. */
 const unsigned char*p=(const unsigned char*)text.text;while(*p==' '||*p=='\t'||*p=='\r'||*p=='\n'||*p=='\v'||*p=='\f')p++;int negative=*p=='-';if(*p=='-'||*p=='+')p++;uint64_t value=0,limit=negative?UINT64_C(2147483648):INT32_MAX;while(*p>='0'&&*p<='9'){unsigned digit=*p++-'0';if(value>(limit-digit)/10){value=limit;while(*p>='0'&&*p<='9')p++;break;}value=value*10+digit;}*out=npc_vm_number55(negative?-(int64_t)value:(int64_t)value);return N55_READY;
}
#endif
