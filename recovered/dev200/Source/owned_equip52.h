/* Source equipment permissions applied to individual owned copies.
 * No stat recalculation here: the live combat adapter must apply item scripts. */
#ifndef MYRO_OWNED_EQUIP52_H
#define MYRO_OWNED_EQUIP52_H
#include "item_rules52.h"
#include "equipment_data52.h"
static int owned_dual_weapon52(unsigned type){return type==1||type==2||type==6;}
static int owned_unequip52(OwnedItems52*b,uint32_t uid){OwnedItem52*p=owned_find52(b,0,uid);if(!p)return OWNED_BAD_ITEM52;p->equipped=0;return OWNED_OK52;}
/* requested is one original EQP slot bit; a multi-position item claims them all.
 * Conflicting pieces return to the bag. Failed attempts change nothing. */
static int owned_equip52(OwnedItems52*b,uint32_t uid,unsigned job,unsigned sex,unsigned level,uint32_t requested,uint32_t*equippedUID){
 if(!b||b->count[0]>OWNED_BAG52||!requested||(requested&(requested-1)))return OWNED_BAD_ITEM52;
 OwnedItem52*p=owned_find52(b,0,uid);if(!p)return OWNED_BAD_ITEM52;
 const OwnedRule52*r=item_rule52(p->sourceID);const EquipmentRule52*e=equipment_rule52(p->sourceID);
 if(!owned_gear52(r)||!equipment_allowed52(e,job,sex,level)||(p->flags&OWNED_BROKEN52))return OWNED_RESTRICTED52;
 if(!p->identified)return OWNED_UNIDENTIFIED52;if(!p->quantity)return OWNED_BAD_QUANTITY52;
 uint32_t position=r->location;
 if(r->kind==OWNED_WEAPON52){
  if(requested!=2&&requested!=32)return OWNED_RESTRICTED52;
  if(requested==32){
   if((job!=12&&job!=J52_ASSASSIN_CROSS)||!owned_dual_weapon52(e->weapon)||(r->flags&OWNED_TWO_HAND52))return OWNED_RESTRICTED52;
   const EquipmentRule52*main=0;for(unsigned i=0;i<b->count[0];i++)if((b->items[i].equipped&2)&&b->items[i].uid!=uid)main=equipment_rule52(b->items[i].sourceID);
   if(!main||!owned_dual_weapon52(main->weapon))return OWNED_RESTRICTED52;
  }
  position=r->flags&OWNED_TWO_HAND52?34:requested;
 }else{
  if(!(requested&r->location))return OWNED_RESTRICTED52;
  if(r->location==136)position=requested;
 }
 int split=p->quantity>1;if(split){
  if(!(p->flags&OWNED_LEGACY_STACK52)||p->equipped)return OWNED_BAD_QUANTITY52;
  if(b->count[0]==OWNED_BAG52)return OWNED_FULL52;if(!b->nextUID||b->nextUID==UINT32_MAX)return OWNED_UID_LIMIT52;
 }
 if(split){OwnedItem52 copy=*p;p->quantity--;copy.uid=b->nextUID++;copy.quantity=1;copy.flags&=(uint8_t)~OWNED_LEGACY_STACK52;b->items[b->count[0]++]=copy;p=b->items+b->count[0]-1;}
 for(unsigned i=0;i<b->count[0];i++){
  OwnedItem52*other=b->items+i;
  if(other->equipped&position)other->equipped=0;
  /* Switching the right hand to a non-dual weapon also releases a left weapon. */
  if(requested==2&&r->kind==OWNED_WEAPON52&&!owned_dual_weapon52(e->weapon)&&other->equipped==32){const OwnedRule52*left=item_rule52(other->sourceID);if(left&&left->kind==OWNED_WEAPON52)other->equipped=0;}
 }
 p->equipped=position;if(equippedUID)*equippedUID=p->uid;return OWNED_OK52;
}
#endif
