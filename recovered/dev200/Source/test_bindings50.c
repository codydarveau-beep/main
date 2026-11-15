/* MIT. Expanded shortcuts, disjoint save sections and frozen-save migration. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
#include "quick_slot.h"
#include "travel_status45.h"
static void checksum50(unsigned char*p){save_put(p+SAVE_BYTES-4,save_crc(p,SAVE_BYTES-4));}
int main(void){
 Combat g,h;SavedCharacter a,b;unsigned char raw[SAVE_BYTES],again[SAVE_BYTES];
 assert(sizeof(g.hotbar[0])==2&&BIND_ITEM_BASE50>SKILL_CAP50);
 assert(SAVE_EXTRA50+4*SAVE_ITEM_CAP50==SAVE_STORAGE50);
 assert(SAVE_STORAGE50+4*SAVE_ITEM_CAP50==SAVE_CART50);
 assert(SAVE_CART50+4*SAVE_ITEM_CAP50==SAVE_EQUIP50);
 assert(SAVE_RANKS50+SAVE_RANK_CAP50==SAVE_USE_RANKS50);
 assert(SAVE_USE_RANKS50+SAVE_RANK_CAP50==SAVE_HOTBAR50);
 combat_init(&g,1500,1500,NULL,NULL);
 for(unsigned id=0;id<SKILL_CAP50;id++){g.hotbar[0]=id;assert(g.hotbar[0]==id&&binding_item(id)<0);}
 assert(!binding_valid(65536)&&!binding_valid(BIND_ITEM_BASE50+ITEM_COUNT));
 for(unsigned id=0;id<ITEM_COUNT;id++){
  unsigned bind=BIND_ITEM_BASE50+id;assert(binding_item(bind)==(int)id);
  int usable=itemDefs[id].healMin||itemDefs[id].spMin||itemDefs[id].equipBit;
  assert(binding_valid(bind)==!!usable);
  if(usable){assert(bar_bind_item(&g,11,id)&&g.hotbar[11]==bind);assert(quick_bind_to(&g,1,bind)&&quick_binding(&g,1)==bind);dev_reset_skills(&g);assert(g.hotbar[11]==bind&&quick_binding(&g,1)==bind);}
 }
 for(int job=0;job<=11;job++){
  char path[120];snprintf(path,sizeof(path),"fixtures50/save48-job%02d.dat",job);
  FILE*f=fopen(path,"rb");assert(f);unsigned char old[SAVE48_BYTES50],protected[SAVE48_BYTES50];assert(fread(old,1,sizeof(old),f)==sizeof(old));assert(fgetc(f)==EOF&&!fclose(f));memcpy(protected,old,sizeof(old));
  assert(save_decode48_50(&a,old)==1&&a.jobId==(unsigned)job&&a.sequence==(unsigned)(500+job));
  assert(a.rbBinding==BIND_ITEM_BASE50&&a.hotbar[9]==BIND_ITEM_BASE50&&a.hotbar[10]==BIND_EMPTY50&&a.hotbar[11]>=BIND_ITEM_BASE50);
  assert(a.storageItems[114]==123&&a.storageItems[0]==700&&a.apples==42);
  assert(!memcmp(old,protected,sizeof(old)));save_encode(raw,&a);assert(save_decode(&b,raw)==1&&!memcmp(&a,&b,sizeof(a)));
  save_restore(&h,&b,1500,1500,NULL,NULL);assert(!memcmp(h.hotbar,a.hotbar,sizeof(h.hotbar))&&h.rbBinding==a.rbBinding);
  /* Every original byte is covered by the old checksum; decode does not mutate output. */
  for(unsigned at=0;at<sizeof(old);at+=4){old[at]^=1;SavedCharacter untouched=a;assert(save_decode48_50(&untouched,old)!=1&&!memcmp(&untouched,&a,sizeof(a)));old[at]^=1;}
 }
 combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,10);
 g.hotbar[8]=BIND_EMPTY50;assert(bar_bind_item(&g,10,ITEM_APPLE));g.rbBinding=BIND_ITEM_BASE50;
 for(int i=0;i<ITEM_COUNT;i++)g.storageItems[i]=i+73;
 g.cartOwned=1;g.cartItems[ITEM_JELLOPY]=9;g.tooltipsDisabled=1;g.popupDisabled=POP_ALL;g.walkPercent=76;g.diagnosticsOff45=1;
 save_capture(&a,&g,900);assert(save_valid(&a));save_encode(raw,&a);assert(save_decode(&b,raw)==1&&!memcmp(&a,&b,sizeof(a)));save_encode(again,&b);assert(!memcmp(raw,again,SAVE_BYTES));
 SaveStore s={0};save_mark_clean(&s,&g);g.rng++;assert(!save_dirty(&s,&g));g.hotbar[10]=BIND_EMPTY50;assert(save_dirty(&s,&g));
 /* A high skill ID survives a 16-bit write, and is rejected until actually supported. */
 a.hotbar[0]=SKILL_CAP50-1;save_encode(raw,&a);assert(raw[SAVE_HOTBAR50]==255&&raw[SAVE_HOTBAR50+1]==1);assert(save_decode(&b,raw)==0);
 a.hotbar[0]=BIND_EMPTY50;save_encode(raw,&a);assert(save_decode(&b,raw)==1);
 const unsigned badOff[]={40,44,48,52,56,60,64,68,72,76,128,SAVE_EXTRA50,SAVE_STORAGE50,SAVE_CART50,SAVE_EQUIP50,SAVE_RANKS50,SAVE_USE_RANKS50};
 for(unsigned i=0;i<sizeof(badOff)/sizeof(*badOff);i++){memcpy(again,raw,SAVE_BYTES);save_put(again+badOff[i],UINT32_MAX);checksum50(again);assert(save_decode(&b,again)==0);}
 for(unsigned at=0;at<SAVE_BYTES;at++){memcpy(again,raw,SAVE_BYTES);again[at]^=1;assert(save_decode(&b,again)!=1);}
 memcpy(again,raw,SAVE_BYTES);save_put(again+84,ITEM_COUNT+1);checksum50(again);assert(save_decode(&b,again)==-1);
 /* Zoning copies every cooldown, including the expanded range. */
 g.skillCD[SKILL_CAP50-1]=8.5f;TravelStatus45 t=travel_capture45(&g);combat_init(&h,1500,1500,NULL,NULL);travel_restore45(&h,&t);assert(h.skillCD[SKILL_CAP50-1]==8.5f);for(int i=0;i<10;i++)combat_tick(&h,.05f,0,0);assert(fabsf(h.skillCD[SKILL_CAP50-1]-8)<.0001f);
 puts("PASS50: 16-bit skill/item isolation, all usable item shortcuts, read-only twelve-class Save48 migration, 8192-byte round trips/checksums/semantic bounds, dirty tracking and expanded zoning cooldowns.");
}
