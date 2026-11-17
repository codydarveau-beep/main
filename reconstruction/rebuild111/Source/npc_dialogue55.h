/* MIT. Original mes/next/close/select flow, separate from controller rendering. */
#ifndef MYRO_NPC_DIALOGUE55_H
#define MYRO_NPC_DIALOGUE55_H
#include "npc_vm55.h"
#include "tutorial_text264.h"
#define NPC_DIALOGUE_TEXT55 12288u
#define NPC_DIALOGUE_CHOICES55 254u
enum{N55_DIALOGUE_HIDDEN,N55_DIALOGUE_PAGE,N55_DIALOGUE_NEXT,N55_DIALOGUE_CLOSE,N55_DIALOGUE_CLOSE_CONTINUE,N55_DIALOGUE_SELECT,N55_DIALOGUE_PROMPT};
typedef struct{char text[NPC_DIALOGUE_TEXT55],options[NPC_DIALOGUE_TEXT55];uint16_t offsets[NPC_DIALOGUE_CHOICES55],ordinals[NPC_DIALOGUE_CHOICES55];uint32_t used,optionUsed,count,mode;}NpcDialogue55;
static int npc_dialogue_append55(NpcDialogue55*d,const char*text){size_t n=strlen(text);if(n+1>=NPC_DIALOGUE_TEXT55-d->used)return 0;memcpy(d->text+d->used,text,n);d->used+=(uint32_t)n;d->text[d->used++]='\n';d->text[d->used]=0;d->mode=N55_DIALOGUE_PAGE;return 1;}
static int npc_dialogue_option55(NpcDialogue55*d,const char*text,size_t length,uint32_t ordinal){if(!length)return 1;if(d->count>=NPC_DIALOGUE_CHOICES55||length+1>NPC_DIALOGUE_TEXT55-d->optionUsed||ordinal>=255)return 0;d->offsets[d->count]=(uint16_t)d->optionUsed;d->ordinals[d->count++]=(uint16_t)ordinal;memcpy(d->options+d->optionUsed,text,length);d->optionUsed+=(uint32_t)length;d->options[d->optionUsed++]=0;return 1;}
/* -1 means another subsystem, otherwise the usual interpreter handler status. */
static int npc_dialogue_command55(NpcDialogue55*d,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 *out=npc_vm_number55(0);
 if(!strcmp(name,"mes")){NpcValue55 text;if(!count)return npc_dialogue_append55(d,"")?N55_READY:N55_ERROR;if(!npc_vm_value55(m,args[0],&text))return N55_ERROR;char number[24];const char*message=text.kind==N55_NUMBER_KIND?npc_vm_decimal55(text.number,number):text.text;return npc_dialogue_append55(d,tutorial_text264(m->owner,d->text,message))?N55_READY:N55_ERROR;}
 if(!strcmp(name,"mesclear")){if(count)return N55_ERROR;d->used=0;d->text[0]=0;return N55_READY;}
 if(!strcmp(name,"next")){if(count)return N55_ERROR;if(!npc_dialogue_visible264(m->owner,d->text)){d->used=0;d->text[0]=0;d->mode=N55_DIALOGUE_PAGE;return N55_READY;}d->mode=N55_DIALOGUE_NEXT;return N55_WAIT;}
 if(!strcmp(name,"close")||!strcmp(name,"close2")){if(count)return N55_ERROR;int cont=!strcmp(name,"close2");if(d->mode==N55_DIALOGUE_HIDDEN||!npc_dialogue_visible264(m->owner,d->text)){d->used=0;d->text[0]=0;d->mode=N55_DIALOGUE_HIDDEN;return cont?N55_READY:N55_DONE;}d->mode=cont?N55_DIALOGUE_CLOSE_CONTINUE:N55_DIALOGUE_CLOSE;return N55_WAIT;}
 if(!strcmp(name,"end")){memset(d,0,sizeof(*d));return N55_DONE;}
 if(strcmp(name,"select")&&strcmp(name,"prompt"))return-1;
 if(!count)return N55_ERROR;d->count=d->optionUsed=0;uint32_t ordinal=0;
 for(uint32_t i=0;i<count;i++){NpcValue55 v;if(!npc_vm_value55(m,args[i],&v)||v.kind!=N55_STRING_KIND)return N55_ERROR;const char*start=v.text,*p=start;for(;;p++){if(*p==':'||!*p){size_t length=(size_t)(p-start);ordinal++;const char*shown=tutorial_option264(m->owner,start,&length);if(shown&&!npc_dialogue_option55(d,shown,length,ordinal))return N55_ERROR;if(!*p)break;start=p+1;}}}
 if(!d->count)return N55_ERROR;d->mode=!strcmp(name,"prompt")?N55_DIALOGUE_PROMPT:N55_DIALOGUE_SELECT;return N55_WAIT;
}
/* choice is a visible zero-based row; cancel is the controller's B action. */
static int npc_dialogue_answer55(NpcDialogue55*d,NpcMachine55*m,uint32_t choice,int cancel){if(m->status!=N55_WAIT)return 0;uint32_t mode=d->mode;NpcValue55 result=npc_vm_number55(0);
 if(cancel){if(mode==N55_DIALOGUE_PROMPT)result=npc_vm_number55(255);else{npc_vm_cancel55(m);memset(d,0,sizeof(*d));return 1;}}
 else if(mode==N55_DIALOGUE_SELECT||mode==N55_DIALOGUE_PROMPT){if(choice>=d->count)return 0;result=npc_vm_number55(d->ordinals[choice]);}
 else if(mode==N55_DIALOGUE_CLOSE){npc_vm_cancel55(m);memset(d,0,sizeof(*d));return 1;}
 else if(mode!=N55_DIALOGUE_NEXT&&mode!=N55_DIALOGUE_CLOSE_CONTINUE)return 0;
 if((mode==N55_DIALOGUE_SELECT||mode==N55_DIALOGUE_PROMPT)&&m->api.write){NpcValue55 ref={0};ref.kind=N55_REFERENCE_KIND;ref.text="@menu";ref.owner=m->owner;ref.frame=m->frame;if(!m->api.write(m->api.context,&ref,&result))return 0;}
 if(mode==N55_DIALOGUE_NEXT||mode==N55_DIALOGUE_CLOSE_CONTINUE){d->used=0;d->text[0]=0;d->mode=mode==N55_DIALOGUE_NEXT?N55_DIALOGUE_PAGE:N55_DIALOGUE_HIDDEN;}else d->mode=d->used?N55_DIALOGUE_PAGE:N55_DIALOGUE_HIDDEN;
 d->count=d->optionUsed=0;return npc_vm_resume55(m,result);
}
#endif
