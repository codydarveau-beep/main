/* SPDX-License-Identifier: MIT
 * Alternating-slot transaction: never overwrite the newest valid slot.
 * The exact decision/verification path is shared with failure-injection tests.
 */
#ifndef MYRO_SAVE_STORE_H
#define MYRO_SAVE_STORE_H
#include "save_format.h"
enum { SLOT_IO=-1,SLOT_MISSING=0,SLOT_RAW=1,SLOT_BAD_SIZE=2 };
typedef int (*SaveRead)(void*,int,unsigned char*);
typedef int (*SaveWrite)(void*,int,const unsigned char*);
typedef int (*SavePrepare)(void*,unsigned,float*,float*);
typedef struct {
 SavePrepare prepare;
 void*ctx;SaveRead read;SaveWrite write;
 int recoverToCamp;int newest,valid[2],missing[2],bad,blocked;uint32_t sequence,sequenceFloor56;
 SavedCharacter character[2];char status[100];
 SavedCharacter cleanCharacter;int hasClean,operationResult58;char errorDetail58[100];
 int(*extensionLoaded)(void*,int);void(*extensionClean)(void*);int(*extensionDirty)(void*);int(*extensionCanSave)(void*);
} SaveStore;
static void save_scan(SaveStore*s){
 s->newest=-1;s->sequence=0;s->bad=s->blocked=0;
 for(int i=0;i<2;i++){
  static unsigned char raw[SAVE_BYTES];int state=s->read(s->ctx,i,raw);s->valid[i]=s->missing[i]=0;
  if(state==SLOT_MISSING){s->missing[i]=1;continue;}
  if(state==SLOT_IO){s->blocked=1;continue;}
  if(state==SLOT_BAD_SIZE){s->bad=1;continue;}
  int decoded=save_decode(&s->character[i],raw);
  if(decoded<0){s->blocked=1;continue;}
  if(!decoded){s->bad=1;continue;}
  s->valid[i]=1;
  if(s->newest<0||s->character[i].sequence>s->sequence){s->newest=i;s->sequence=s->character[i].sequence;}
 }
 if(s->newest<0&&s->bad)s->blocked=1;
 if(s->blocked)snprintf(s->status,sizeof(s->status),"Save files unreadable/unsupported; writes disabled.");
 else if(s->newest<0)snprintf(s->status,sizeof(s->status),"No saved character yet. START then A saves.");
 else if(s->bad)snprintf(s->status,sizeof(s->status),"Recovered older valid save #%lu.",(unsigned long)s->sequence);
 else snprintf(s->status,sizeof(s->status),"Save #%lu ready.",(unsigned long)s->sequence);
}
static void save_mark_clean(SaveStore*s,const Combat*g){save_capture(&s->cleanCharacter,g,1);s->hasClean=1;if(s->extensionClean)s->extensionClean(s->ctx);}
static int save_dirty(const SaveStore*s,const Combat*g){if(!s->hasClean||(s->extensionDirty&&s->extensionDirty(s->ctx)))return 1;static SavedCharacter c;save_capture(&c,g,1);c.rng=s->cleanCharacter.rng;return memcmp(&c,&s->cleanCharacter,sizeof(c))!=0;}
static int save_load_impl58(SaveStore*s,Combat*g,float campX,float campY,CombatCanMove move,void*world){
 save_scan(s);if(s->newest<0)return 0;
 static SavedCharacter c;c=s->character[s->newest];if(s->recoverToCamp)c.mapId=0;
 if(s->prepare&&!s->prepare(s->ctx,c.mapId,&campX,&campY)){snprintf(s->status,sizeof(s->status),"Saved map unavailable; character not loaded.");return 0;}
 if(s->recoverToCamp){c.x=campX;c.y=campY;}
 if(s->extensionLoaded&&!s->extensionLoaded(s->ctx,s->newest)){snprintf(s->status,sizeof(s->status),"Quest save state unavailable; character not loaded.");return 0;}
 save_restore(g,&c,campX,campY,move,world);
 int relocated=move&&!move(world,g->x,g->y,g->x,g->y);
 if(relocated){g->x=campX;g->y=campY;}
 save_mark_clean(s,g);
 if(s->blocked)snprintf(s->status,sizeof(s->status),"Loaded #%lu; other file unreadable. Writes disabled.",(unsigned long)s->sequence);
 else snprintf(s->status,sizeof(s->status),"%s #%lu%s.",s->bad?"Recovered save":"Loaded save",(unsigned long)s->sequence,relocated?" at camp":"");
 return 1;
}
static int save_commit_impl58(SaveStore*s,const Combat*g){
 if(s->extensionCanSave&&!s->extensionCanSave(s->ctx)){snprintf(s->status,sizeof(s->status),"Finish the NPC interaction before saving.");return 0;}
 save_scan(s);if(s->blocked)return 0;if(s->sequence<s->sequenceFloor56)s->sequence=s->sequenceFloor56;
 if(s->sequence==UINT32_MAX){snprintf(s->status,sizeof(s->status),"Save sequence limit reached; files preserved.");return 0;}
 static SavedCharacter c;save_capture(&c,g,s->sequence+1);
 if(!save_valid(&c)){snprintf(s->status,sizeof(s->status),"Save rejected: invalid character data.");return 0;}
 int target=s->newest<0?0:1-s->newest;static unsigned char raw[SAVE_BYTES],verify[SAVE_BYTES];save_encode(raw,&c);
 if(!s->write(s->ctx,target,raw)){
  if(s->newest>=0)snprintf(s->status,sizeof(s->status),"Save failed writing %c; previous save kept.",'A'+target);
  else snprintf(s->status,sizeof(s->status),"First save failed; progress is still session-only.");
  return 0;
 }
 static SavedCharacter checked;
 if(s->read(s->ctx,target,verify)!=SLOT_RAW||memcmp(raw,verify,SAVE_BYTES)||save_decode(&checked,verify)!=1){
  snprintf(s->status,sizeof(s->status),"Save verification failed; %s.",s->newest>=0?"previous copy kept":"no save confirmed");return 0;
 }
 s->newest=target;s->sequence=c.sequence;s->valid[target]=1;s->character[target]=c;s->bad=0;save_mark_clean(s,g);
 snprintf(s->status,sizeof(s->status),"Saved #%lu to HDD; read-back verified.",(unsigned long)c.sequence);return 1;
}
/* Keep the last failed operation visible until an actual successful save/load. */
static int save_load(SaveStore*s,Combat*g,float x,float y,CombatCanMove move,void*world){int ok=save_load_impl58(s,g,x,y,move,world);s->operationResult58=ok?1:-1;if(ok)s->errorDetail58[0]=0;else snprintf(s->errorDetail58,sizeof(s->errorDetail58),"%s",s->status);return ok;}
static int save_commit(SaveStore*s,const Combat*g){int busy=s->extensionCanSave&&!s->extensionCanSave(s->ctx);int ok=save_commit_impl58(s,g);s->operationResult58=ok?1:busy?0:-1;if(ok)s->errorDetail58[0]=0;else if(!busy)snprintf(s->errorDetail58,sizeof(s->errorDetail58),"%s",s->status);return ok;}
#endif
