#include <assert.h>
#include <stdio.h>
#include "npc_dialogue55.h"
#include "npc_variables55.h"
#include "vm_fixtures55.h"
static NpcMachine55 machine;static NpcDialogue55 dialogue;static NpcVariables55 variables;
static int read55(void*c,const NpcValue55*r,NpcValue55*out){(void)c;return npc_variable_read55(&variables,r,out);}
static int write55(void*c,const NpcValue55*r,const NpcValue55*v){(void)c;return npc_variable_write55(&variables,r,v);}
static void release55(void*c,uint32_t frame){(void)c;npc_variable_release_frame55(&variables,frame);}
static int handler(void*c,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){(void)c;int status=npc_dialogue_command55(&dialogue,m,name,args,count,out);return status<0?N55_ERROR:status;}
static int run(void){int status;do status=npc_vm_run55(&machine,3);while(status==N55_YIELD);return status;}
static int64_t number(const char*name){NpcValue55 r={0},v;r.kind=N55_REFERENCE_KIND;r.text=name;r.frame=1;r.owner=7;assert(npc_variable_read55(&variables,&r,&v));return v.number;}
static void start(const NpcProgram55*p){npc_variables_clear55(&variables);memset(&dialogue,0,sizeof(dialogue));NpcApi55 api={read55,write55,handler,NULL,release55,NULL};assert(npc_vm_start55(&machine,p,0,7,api));}
int main(void){start(&prog_dialogue);assert(run()==N55_WAIT&&dialogue.mode==N55_DIALOGUE_NEXT&&strstr(dialogue.text,"^FF0000Original^000000"));assert(npc_dialogue_answer55(&dialogue,&machine,0,0));assert(run()==N55_WAIT&&dialogue.mode==N55_DIALOGUE_SELECT&&dialogue.count==2&&!strcmp(dialogue.options+dialogue.offsets[1],"Third"));assert(!npc_dialogue_answer55(&dialogue,&machine,2,0));assert(npc_dialogue_answer55(&dialogue,&machine,1,0));assert(number("@menu")==3);assert(run()==N55_WAIT&&dialogue.mode==N55_DIALOGUE_CLOSE_CONTINUE&&strstr(dialogue.text,"3\n"));assert(!number("after"));assert(npc_dialogue_answer55(&dialogue,&machine,0,0));assert(run()==N55_WAIT&&dialogue.mode==N55_DIALOGUE_CLOSE&&number("after")==1&&!strcmp(dialogue.text,"Final\n"));assert(npc_dialogue_answer55(&dialogue,&machine,0,0)&&machine.status==N55_DONE&&number("after")==1);
 start(&prog_promptcancel);assert(run()==N55_WAIT);assert(npc_dialogue_answer55(&dialogue,&machine,0,1)&&number("@menu")==255);assert(run()==N55_WAIT&&number("answer")==255);assert(npc_dialogue_answer55(&dialogue,&machine,0,0)&&machine.status==N55_DONE);
 start(&prog_dialogue);assert(run()==N55_WAIT);assert(npc_dialogue_answer55(&dialogue,&machine,0,1)&&machine.status==N55_DONE&&!dialogue.used);npc_variables_clear55(&variables);puts("PASS original NPC dialogue compiler/runtime: copied pages/color markup, next page clearing, blank option ordinals/@menu, close terminates, close2 waits then continues, prompt cancel255, controller cancellation and bounded choices");}
