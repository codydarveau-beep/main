/* SPDX-License-Identifier: MIT. Controller-only front end; no world or disk IO. */
#ifndef MYRO_FRONTEND_STATE56_H
#define MYRO_FRONTEND_STATE56_H
#include <stdint.h>
#include <string.h>
enum { F56_PRESS, F56_HOME, F56_SETTINGS, F56_CHARACTERS, F56_CREATE,
       F56_DEVELOPER, F56_PLAY, F56_PAGES };
enum { F56_NONE, F56_ENTER_GAME, F56_CREATE_CHARACTER, F56_OPEN_CHARACTER,
       F56_OPEN_DEVELOPER, F56_DELETE_CHARACTER };
enum { F56_EMPTY, F56_COMPATIBLE, F56_INCOMPATIBLE, F56_UNREADABLE };
enum { F56_SLOTS=9, F56_FADE_MS=180 };
typedef struct {
 unsigned page, nextPage, fade, fadeMs, opaque, row, slot, code, unlocked;
 unsigned pendingAction, readyAction, deleteConfirm;
 unsigned char slots[F56_SLOTS];
} Frontend56;
static void frontend_init56(Frontend56 *f) {
 memset(f,0,sizeof(*f));f->page=f->nextPage=F56_PRESS;
}
static int frontend_goto56(Frontend56 *f,unsigned page,unsigned action) {
 if(f->fade||page>=F56_PAGES)return 0;
 f->nextPage=page;f->pendingAction=action;f->fade=1;f->fadeMs=0;
 return 1;
}
/* The midpoint yields actions while fully black. Consumers may do loading IO
 * there; the next tick begins fading in once the new screen is prepared. */
static unsigned frontend_tick56(Frontend56 *f,unsigned ms) {
 if(ms>F56_FADE_MS)ms=F56_FADE_MS;
 if(f->fade){
  unsigned total=f->fadeMs+ms;
  f->fadeMs=total>F56_FADE_MS?F56_FADE_MS:total;
  if(f->fade==1){
   f->opaque=f->fadeMs*255/F56_FADE_MS;
   if(f->fadeMs==F56_FADE_MS){
    f->page=f->nextPage;f->row=0;f->deleteConfirm=0;
    f->readyAction=f->pendingAction;f->pendingAction=0;
    f->fade=2;f->fadeMs=0;
   }
  }else{
   f->opaque=255-f->fadeMs*255/F56_FADE_MS;
   if(f->fadeMs==F56_FADE_MS){f->fade=0;f->opaque=0;}
  }
 }
 unsigned action=f->readyAction;f->readyAction=0;return action;
}
static void frontend_input56(Frontend56 *f,unsigned pressed) {
 if(f->fade)return;
 const unsigned nav=1024|2048|4096|8192;
 const unsigned relevant=nav|2|4|8|16|1|256|32|512;
 unsigned p=pressed&relevant;if(!p)return;
 if(f->page==F56_PRESS){
  static const unsigned sequence[10]={1024,1024,2048,2048,4096,8192,4096,8192,4,2};
  /* Chords are not sequence steps; repeated held buttons are never passed as
   * fresh presses. Consume the last A so unlocking cannot also choose Start. */
  if(p==sequence[f->code]){
   if(++f->code==10){f->code=0;f->unlocked=1;frontend_goto56(f,F56_HOME,F56_NONE);}
   return;
  }
  f->code=p==sequence[0]?1:0;
  if(p==2)frontend_goto56(f,F56_HOME,F56_NONE);
  return;
 }
 if(f->page==F56_HOME){
  unsigned count=2;if(f->row>=count)f->row=0;
  if(p&1024)f->row=(f->row+count-1)%count;
  else if(p&2048)f->row=(f->row+1)%count;
  else if(p&4)frontend_goto56(f,F56_PRESS,F56_NONE);
  else if(p&(2|8192))frontend_goto56(f,f->row==0?F56_CHARACTERS:F56_SETTINGS,F56_NONE);
  return;
 }
 if(f->page==F56_CHARACTERS){
  if(f->deleteConfirm){
   if(p&4)f->deleteConfirm=0;
   else if(p&2){f->deleteConfirm=0;f->readyAction=F56_DELETE_CHARACTER;}
   return;
  }
  if(p&4){frontend_goto56(f,F56_HOME,F56_NONE);return;}
  if(p&32){if(f->slot>=3)f->slot-=3;}
  else if(p&512){if(f->slot+3<F56_SLOTS)f->slot+=3;}
  else if(p&1024){if(f->slot>=3)f->slot-=3;}
  else if(p&2048){if(f->slot+3<F56_SLOTS)f->slot+=3;}
  else if(p&4096){if(f->slot)f->slot--;}
  else if(p&8192){if(f->slot+1<F56_SLOTS)f->slot++;}
  else if((p&8)&&f->slots[f->slot]!=F56_EMPTY)f->deleteConfirm=1;
  else if(p&2){
   if(f->slots[f->slot]==F56_EMPTY)frontend_goto56(f,F56_CREATE,F56_NONE);
   else if(f->slots[f->slot]==F56_COMPATIBLE)frontend_goto56(f,F56_PLAY,F56_OPEN_CHARACTER);
  }
  return;
 }
 if(f->page==F56_DEVELOPER&&(p&(2|8192))){frontend_goto56(f,F56_CHARACTERS,F56_NONE);return;}
 if(f->page==F56_SETTINGS||f->page==F56_DEVELOPER){
  if(p&(4|4096))frontend_goto56(f,F56_HOME,F56_NONE);
 }else if(f->page==F56_CREATE){
  if(p&4)frontend_goto56(f,F56_CHARACTERS,F56_NONE);
  /* Creation form explicitly submits only after its name/appearance checks. */
 }
}
static int frontend_create56(Frontend56 *f) {
 if(f->page!=F56_CREATE||f->slots[f->slot]!=F56_EMPTY)return 0;
 return frontend_goto56(f,F56_PLAY,F56_CREATE_CHARACTER);
}
#endif
