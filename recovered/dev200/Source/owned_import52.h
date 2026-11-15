/* Read-only migration of the frozen Test50/51 inventory layout.
 * No disk access; callers must decode/validate the old character first.
 * Kept independent of live ITEM_COUNT and LEARN_COUNT for future catalogs. */
#ifndef MYRO_OWNED_IMPORT52_H
#define MYRO_OWNED_IMPORT52_H
#include <stdlib.h>
#include "item_rules52.h"
#define LEGACY_ITEMS52 255
#define LEGACY_SLOTS52 10
typedef struct {
 int32_t quantity[3][LEGACY_ITEMS52]; /* bag, cart, storage */
 int16_t selected[LEGACY_SLOTS52]; /* catalog index, -1 for empty */
 uint16_t broken; /* old catalog index + 1; zero means none */
} LegacyOwned52;
typedef struct {uint32_t movedToStorage[2],equippedCopies;uint64_t quantities[3];} OwnedImportReport52;
enum {OWNED_IMPORT_BAD52=0,OWNED_IMPORT_OK52=1,OWNED_IMPORT_MEMORY52=-1};
static uint32_t owned_legacy_position52(unsigned slot,const OwnedRule52*r){
 static const uint32_t positions[LEGACY_SLOTS52]={2,16,64,32,4,256,8,128,512,1};
 return slot==0&&(r->flags&OWNED_TWO_HAND52)?34:positions[slot];
}
static int owned_legacy_record52(OwnedItems52*b,unsigned box,unsigned oldID,uint32_t quantity,uint32_t equipped,unsigned broken){
 if(b->count[box]>=owned_capacity52(box))return 0;
 const OwnedRule52*r=item_rule52(legacyItemSources52[oldID]);if(!r)return 0;
 OwnedItem52*p=b->items+owned_base52(box)+b->count[box]++;memset(p,0,sizeof(*p));
 p->uid=b->nextUID++;p->sourceID=r->sourceID;p->quantity=quantity;p->equipped=equipped;p->identified=oldID!=17;
 if(quantity>(owned_gear52(r)?1:r->stackLimit))p->flags|=OWNED_LEGACY_STACK52;
 if(broken==oldID+1&&owned_gear52(r))p->flags|=OWNED_BROKEN52;
 return 1;
}
/* Overflow from the old unbounded bag/cart goes to storage, reported explicitly.
 * Historical stack quantities remain intact until individual copies are split.
 * A failure leaves both output and report untouched. Staging stays off Xbox stack. */
static int owned_import_legacy52(OwnedItems52*out,const LegacyOwned52*old,OwnedImportReport52*report){
 if(!out||!old||old->broken>LEGACY_ITEMS52)return OWNED_IMPORT_BAD52;
 for(unsigned box=0;box<3;box++)for(unsigned i=0;i<LEGACY_ITEMS52;i++)if(old->quantity[box][i]<0||old->quantity[box][i]>1000000000)return OWNED_IMPORT_BAD52;
 unsigned worn[LEGACY_ITEMS52]={0};uint32_t occupied=0;
 for(unsigned slot=0;slot<LEGACY_SLOTS52;slot++){
  int id=old->selected[slot];if(id==-1)continue;if(id<0||id>=LEGACY_ITEMS52||old->broken==(unsigned)id+1)return OWNED_IMPORT_BAD52;
  const OwnedRule52*r=item_rule52(legacyItemSources52[id]);if(!owned_gear52(r))return OWNED_IMPORT_BAD52;
  uint32_t position=owned_legacy_position52(slot,r),allowed=r->location;if(r->kind==OWNED_WEAPON52)allowed|=32;
  if((position&~allowed)||(occupied&position)||(slot==3&&(r->flags&OWNED_TWO_HAND52))||++worn[id]>(unsigned)old->quantity[0][id])return OWNED_IMPORT_BAD52;
  occupied|=position;
 }
 OwnedItems52*b=malloc(sizeof(*b));if(!b)return OWNED_IMPORT_MEMORY52;owned_init52(b);OwnedImportReport52 result={0};int ok=1;
 for(unsigned slot=0;slot<LEGACY_SLOTS52&&ok;slot++){int id=old->selected[slot];if(id<0)continue;const OwnedRule52*r=item_rule52(legacyItemSources52[id]);ok=owned_legacy_record52(b,0,(unsigned)id,1,owned_legacy_position52(slot,r),old->broken);result.equippedCopies++;}
 /* Reserve original storage first, then use its remaining space for overflow. */
 static const unsigned order[3]={2,0,1};
 for(unsigned pass=0;pass<3&&ok;pass++){unsigned box=order[pass];for(unsigned i=0;i<LEGACY_ITEMS52&&ok;i++){
  uint32_t quantity=(uint32_t)old->quantity[box][i];result.quantities[box]+=quantity;
  if(box==0)quantity-=worn[i];if(!quantity)continue;unsigned destination=box;
  if(b->count[box]==owned_capacity52(box)&&box!=2){destination=2;result.movedToStorage[box]++;}
  ok=owned_legacy_record52(b,destination,i,quantity,0,old->broken);
 }}
 if(ok)ok=owned_valid52(b,item_rule52);
 if(ok){memcpy(out,b,sizeof(*b));if(report)*report=result;}free(b);return ok?OWNED_IMPORT_OK52:OWNED_IMPORT_BAD52;
}
#endif
