/* Include after save_format.h. Does not alter the legacy decoder or save files. */
#ifndef MYRO_OWNED_SAVE50_ADAPTER52_H
#define MYRO_OWNED_SAVE50_ADAPTER52_H
#include "owned_import52.h"
typedef char LegacyCatalogSize52[(ITEM_COUNT==LEGACY_ITEMS52&&EQUIP_SLOTS46==LEGACY_SLOTS52)?1:-1];
static int owned_import_saved50_52(OwnedItems52*out,const SavedCharacter*saved,OwnedImportReport52*report){
 if(!saved||!save_valid(saved))return OWNED_IMPORT_BAD52;
 LegacyOwned52*old=malloc(sizeof(*old));if(!old)return OWNED_IMPORT_MEMORY52;memset(old,0,sizeof(*old));
 old->broken=(uint16_t)saved->brokenWeapon48;
 for(unsigned i=0;i<LEGACY_ITEMS52;i++){
  old->quantity[0][i]=i==0?saved->apples:i==1?saved->jellopy:i==2?saved->clover:saved->extraItems[i-3];
  old->quantity[1][i]=saved->cartItems[i];old->quantity[2][i]=saved->storageItems[i];
 }
 const int fallback[6]={ITEM_KATANA,ITEM_BOW,ITEM_KNIFE,ITEM_SHIRT,ITEM_SANDALS,ITEM_GUARD};
 for(unsigned slot=0;slot<LEGACY_SLOTS52;slot++){
  old->selected[slot]=saved->equipped46[slot]?(int16_t)(saved->equipped46[slot]-1):-1;
  if(old->selected[slot]>=0)continue;
  for(unsigned k=0;k<6;k++){int id=fallback[k];if(itemDefs[id].slot==slot&&(saved->equipment&itemDefs[id].equipBit)){old->selected[slot]=(int16_t)id;break;}}
 }
 int result=owned_import_legacy52(out,old,report);free(old);return result;
}
#endif
