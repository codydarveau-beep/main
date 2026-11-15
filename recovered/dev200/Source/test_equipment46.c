/* MIT. Expanded source-backed catalog, selection, trade and persistent ownership. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "developer.h"
#include "shop.h"
#include "save_format.h"
static int find(int id){for(int i=0;i<ITEM_COUNT;i++)if(itemDefs[i].id==id)return i;return -1;}
int main(void){assert(ITEM_COUNT==255&&SAVE_BYTES==8192);unsigned checked=0;
 for(int job=0;job<21;job++)for(int i=18;i<ITEM_COUNT;i++){
  Combat g;combat_init(&g,1200,1200,NULL,NULL);dev_class_preset(&g,job);g.level=99;g.jobId=job;g.statPoints=stat_total48(&g)-stat_spent(g.stats);stat_refresh(&g);g.zeny=1000000;*inventory_stack(&g,i)=2;if(inventory_equipped46(&g,i))inventory_remove46(&g,itemDefs[i].slot);unsigned old=g.equipment;int ok=inventory_can_equip46(&g,i);inventory_action(&g,i);
  if(!ok){assert(g.equipment==old&&!inventory_equipped46(&g,i));continue;}
  assert(inventory_equipped46(&g,i));assert(inventory_slot46(&g,itemDefs[i].slot)==i);if(itemDefs[i].slot==0){assert(inventory_attack(&g)>=itemDefs[i].attack);if(itemDefs[i].twoHand)assert(inventory_slot46(&g,3)<0);}
  SavedCharacter a,b;save_capture(&a,&g,1);assert(save_valid(&a));unsigned char raw[SAVE_BYTES];save_encode(raw,&a);assert(save_decode(&b,raw)==1);Combat restored;save_restore(&restored,&b,1200,1200,NULL,NULL);assert(inventory_equipped46(&restored,i)&&inventory_count(&restored,i)==2);assert(!shop_trade(&g,i,1,1));inventory_action(&g,i);assert(!inventory_equipped46(&g,i));if(shop_price(&g,i,1)){assert(shop_trade(&g,i,1,1));assert(inventory_count(&g,i)==1);}else{assert(!shop_trade(&g,i,1,1));assert(inventory_count(&g,i)==2);}checked++;
 }
 Combat g;combat_init(&g,1200,1200,NULL,NULL);dev_class_preset(&g,7);int spear=find(1401),rod=find(1601);assert(spear>=0&&rod>=0);*inventory_stack(&g,spear)=1;inventory_action(&g,spear);assert(inventory_wtype46(&g)==4&&combat_attack_range(&g)==24);assert(inventory_add(&g,ITEM_GUARD,1));inventory_action(&g,ITEM_GUARD);assert(inventory_equipped46(&g,ITEM_GUARD));inventory_action(&g,ITEM_KATANA);assert(inventory_slot46(&g,3)<0);combat_change_job(&g,2);*inventory_stack(&g,rod)=1;inventory_action(&g,rod);assert(inventory_matk46(&g,100)==115);
 SavedCharacter a,b;save_capture(&a,&g,4);assert(save_valid(&a));a.equipped46[0]=ITEM_COUNT+1;assert(!save_valid(&a));a.equipped46[0]=rod+1;unsigned char raw[SAVE_BYTES];save_encode(raw,&a);raw[SAVE_EXTRA50]^=1;assert(save_decode(&b,raw)==0);
 printf("PASS46 %u legal job/equipment combinations,255-item catalog,job guards,slot replacement,two-hand/shield exclusion,spear range,staffMATK,sale safety and8192-byte save roundtrips/corruption.\n",checked);
}
