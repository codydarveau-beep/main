/* SPDX-License-Identifier: MIT. Economy edge cases and persistence. */
#include <assert.h>
#include "combat.h"
#include "shop.h"
#include "save_store.h"
int main(void){
 Combat g;combat_init(&g,2100,1636,NULL,NULL);int apples=g.apples;assert(!shop_trade(&g,0,1,0)&&g.apples==apples&&g.zeny==0);
 assert(inventory_add(&g,ITEM_JELLOPY,10));assert(shop_trade(&g,ITEM_JELLOPY,10,1)&&g.zeny==30&&g.jellopy==0);
 assert(shop_trade(&g,ITEM_APPLE,2,0)&&g.zeny==0&&g.apples==apples+2);Combat before=g;
 assert(!shop_trade(&g,ITEM_APPLE,0,0));assert(!shop_trade(&g,ITEM_APPLE,-1,0));assert(!shop_trade(&g,ITEM_APPLE,101,0));assert(!shop_trade(&g,-1,1,0));assert(!shop_trade(&g,ITEM_COUNT,1,1));assert(g.zeny==before.zeny&&g.apples==before.apples);
 assert(!shop_trade(&g,ITEM_JELLOPY,1,0));g.equipment|=1;assert(!shop_trade(&g,ITEM_KNIFE,1,1)&&g.extraItems[1]==1);g.equipment&=~1u;assert(shop_trade(&g,ITEM_KNIFE,1,1)&&g.extraItems[1]==0&&g.zeny==25);
 g.zeny=ZENY_MAX;g.jellopy=1;assert(!shop_trade(&g,ITEM_JELLOPY,1,1)&&g.jellopy==1&&g.zeny==ZENY_MAX);g.apples=ITEM_STACK_MAX;assert(!shop_trade(&g,ITEM_APPLE,1,0)&&g.zeny==ZENY_MAX);
 g.hp=0;assert(!shop_trade(&g,ITEM_RED_POTION,1,0));g.hp=g.maxhp;g.apples=5;g.zeny=12345;g.mapId=2;SavedCharacter c;save_capture(&c,&g,1);unsigned char b[SAVE_BYTES];save_encode(b,&c);assert(save_decode(&c,b)==1);Combat h;save_restore(&h,&c,1000,1000,NULL,NULL);assert(h.zeny==12345&&h.apples==5&&h.mapId==2);
 SaveStore s={0};save_mark_clean(&s,&h);assert(!save_dirty(&s,&h));h.zeny++;assert(save_dirty(&s,&h));c.zeny=-1;assert(!save_valid(&c));c.zeny=ZENY_MAX+1;assert(!save_valid(&c));
 puts("PASS shop insufficient funds, quantities, absent stock, equipped sale, overflow/stack guards, atomic exchanges, Zeny save roundtrip and dirty detection");return 0;
}
