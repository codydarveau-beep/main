/* MIT. Original NPC input semantics; presentation is supplied by the game UI. */
#ifndef MYRO_NPC_INPUT55_H
#define MYRO_NPC_INPUT55_H
#include "npc_vm55.h"
typedef struct{NpcValue55 target;char name[256];int32_t minimum,maximum;uint32_t active,string;}NpcInput55;
static int npc_input_command55(NpcInput55*i,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 if(strcmp(name,"input"))return -1;*out=npc_vm_number55(0);
 if(i->active||count<1||count>3||args[0].kind!=N55_REFERENCE_KIND||!args[0].text)return N55_ERROR;
 size_t length=strlen(args[0].text);if(!length||length>=sizeof(i->name))return N55_ERROR;
 int32_t limits[2]={0,10000000};for(uint32_t n=1;n<count;n++){NpcValue55 v;if(!npc_vm_value55(m,args[n],&v)||v.kind!=N55_NUMBER_KIND||v.number<INT32_MIN||v.number>INT32_MAX)return N55_ERROR;limits[n-1]=(int32_t)v.number;}
 if(limits[0]>limits[1])return N55_ERROR;
 i->target=args[0];memcpy(i->name,args[0].text,length+1);i->target.text=i->name;i->minimum=limits[0];i->maximum=limits[1];i->string=i->name[length-1]=='$';i->active=1;return N55_WAIT;
}
/* Strings are stored intact even when outside the requested length range. */
static int npc_input_answer55(NpcInput55*i,NpcMachine55*m,int64_t number,const char*text,int cancel){
 if(!i->active||m->status!=N55_WAIT)return 0;
 if(cancel){npc_vm_cancel55(m);memset(i,0,sizeof(*i));return 1;}
 if(!m->api.write)return 0;NpcValue55 value;int result;
 if(i->string){if(!text||strlen(text)>4095)return 0;size_t length=strlen(text);result=(int64_t)length<i->minimum?-1:(int64_t)length>i->maximum?1:0;value=npc_vm_string55(text);}
 else{if(number<INT32_MIN||number>INT32_MAX)return 0;result=number<i->minimum?-1:number>i->maximum?1:0;value=npc_vm_number55(number<i->minimum?i->minimum:number>i->maximum?i->maximum:number);}
 if(!m->api.write(m->api.context,&i->target,&value))return 0;
 if(!npc_vm_resume55(m,npc_vm_number55(result)))return 0;memset(i,0,sizeof(*i));return 1;
}
#endif
