/* MIT. User-observable choices, restart persistence, Off, timing and failures. */
#include <assert.h>
#include <stdio.h>
#include "autosave50b.h"
#include "pause_ui.h"
typedef struct {unsigned char bytes[2][24];int state[2],fail,writes;} Disk50b;
static int read50b(void*x,int slot,unsigned char*out){Disk50b*d=x;if(d->state[slot]==1)memcpy(out,d->bytes[slot],24);return d->state[slot];}
static int write50b(void*x,int slot,const unsigned char*in){Disk50b*d=x;d->writes++;if(d->fail==1)return 0;memcpy(d->bytes[slot],in,24);d->state[slot]=1;if(d->fail==2){d->bytes[slot][20]^=1;return 0;}return 1;}
int main(void){Disk50b disk={0};Autosave50b s={.ctx=&disk,.read=read50b,.write=write50b};autosave_load50b(&s);assert(s.choice==1&&s.writable&&s.newest==-1);
 PauseUI menu={.tab=0,.row=4};assert(pause_count(0)==5&&pause_input(&menu,4096)==PA_AUTOSAVE_DOWN50B&&pause_input(&menu,8192)==PA_AUTOSAVE_UP50B);menu.row=3;assert(pause_input(&menu,2)==PA_RESUME);menu.row=0;assert(pause_input(&menu,2)==PA_SAVE);
 const unsigned minutes[]={0,1,3,5,10,15,30};for(unsigned choice=0;choice<7;choice++){
  while(s.choice>choice)assert(autosave_change50b(&s,-1,100));while(s.choice<choice)assert(autosave_change50b(&s,1,100));assert(autosave_commit50b(&s));
  Autosave50b reload={.ctx=&disk,.read=read50b,.write=write50b};autosave_load50b(&reload);assert(reload.choice==choice);unsigned ms=minutes[choice]*60000u;assert(autosave_interval50b(choice)==ms);
  if(!choice){assert(!autosave_due50b(choice,UINT32_MAX,0));continue;}assert(!autosave_due50b(choice,ms-1,0)&&autosave_due50b(choice,ms,0)&&autosave_due50b(choice,ms+1,0));assert(autosave_due50b(choice,(uint32_t)(UINT32_MAX-10+ms),UINT32_MAX-10));
 }
 assert(!autosave_change50b(&s,1,100));autosave_change50b(&s,-1,UINT32_MAX-100);assert(!autosave_pending50b(&s,200,0)&&autosave_pending50b(&s,300,0)&&!autosave_pending50b(&s,300,1));
 unsigned previous=s.sequence;int newest=s.newest;unsigned char good[24];memcpy(good,disk.bytes[newest],24);
 for(disk.fail=1;disk.fail<=2;disk.fail++){assert(!autosave_commit50b(&s)&&s.sessionOnly&&s.sequence==previous&&s.newest==newest&&!memcmp(good,disk.bytes[newest],24));Autosave50b reload={.ctx=&disk,.read=read50b,.write=write50b};autosave_load50b(&reload);assert(reload.choice==6);}
 disk.fail=0;memcpy(disk.bytes[1-newest],"MYROAS02",8);disk.state[1-newest]=1;Autosave50b future={.ctx=&disk,.read=read50b,.write=write50b};autosave_load50b(&future);assert(!future.writable);int writes=disk.writes;assert(!autosave_commit50b(&future)&&disk.writes==writes);
 puts("PASS50b all seven autosave choices including Off across restart, exact interval boundaries/clock wrap, slider endpoints/controls, debounced writes, failed-write recovery and future-settings preservation.");}
