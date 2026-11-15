/* SPDX-License-Identifier: MIT. Gameplay, item persistence and v1 conversion. */
#include <assert.h>
#include <stdio.h>
#include "save_format.h"
#include "save_legacy.h"
static int openworld(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>=8&&nx<3192&&ny>=8&&ny<3192;}
static void one(Combat*g){combat_init(g,2100,1636,openworld,NULL);g->target=0;g->mobs[0].x=2112;g->mobs[0].y=1636;g->mobs[0].homeX=2112;g->mobs[0].homeY=1636;for(int i=1;i<MOB_COUNT;i++)g->mobs[i].aggro=0;}
int main(void){
 Combat g;one(&g);assert(g.apples==3&&g.extraItems[0]==3&&!g.equipment);for(int i=1;i<5;i++)assert(g.extraItems[i]==1);
 Combat unarmed=g,armed=g;armed.equipment=15;combat_attack(&unarmed);combat_attack(&armed);combat_tick(&unarmed,.05f,0,0);combat_tick(&armed,.05f,0,0);
 assert(unarmed.mobs[0].hp-armed.mobs[0].hp==17);assert(armed.hp>=unarmed.hp); /* Pre-re armour is percent DEF, not flat reduction. */assert(inventory_attack(&armed)==17&&inventory_defense(&armed)==5);
 for(int i=4;i<8;i++)inventory_action(&g,i);assert(g.equipment==15);for(int i=4;i<8;i++)inventory_action(&g,i);assert(!g.equipment);for(int i=4;i<8;i++)assert(inventory_count(&g,i)==1);
 g.hp=1;inventory_action(&g,ITEM_RED_POTION);assert(g.hp==g.maxhp&&g.extraItems[0]==2);
 g.hp=g.maxhp;uint32_t rng=g.rng;inventory_action(&g,ITEM_RED_POTION);assert(g.extraItems[0]==2&&g.rng==rng);
 g.hp=g.maxhp-1;inventory_action(&g,ITEM_APPLE);assert(g.hp==g.maxhp&&g.apples==2);
 g.hp=1;g.extraItems[0]=0;rng=g.rng;inventory_action(&g,ITEM_RED_POTION);assert(g.hp==1&&g.rng==rng);
 g.hp=0;inventory_action(&g,ITEM_APPLE);inventory_action(&g,ITEM_KNIFE);assert(g.apples==2&&!g.equipment);
 g.hp=g.maxhp;g.jellopy=7;inventory_action(&g,ITEM_JELLOPY);assert(g.jellopy==7);
 g.clover=ITEM_STACK_MAX;assert(!inventory_add(&g,ITEM_CLOVER,1)&&g.clover==ITEM_STACK_MAX);assert(!inventory_add(&g,-1,1)&&!inventory_add(&g,ITEM_APPLE,-1));
 g.equipment=15;SavedCharacter c,parsed;save_capture(&c,&g,18);unsigned char bytes[SAVE_BYTES];save_encode(bytes,&c);assert(save_decode(&parsed,bytes)==1);
 Combat restored;save_restore(&restored,&parsed,2100,1636,openworld,NULL);assert(restored.equipment==15&&restored.extraItems[0]==0&&restored.apples==2&&restored.jellopy==7&&restored.clover==ITEM_STACK_MAX);
 for(int i=1;i<5;i++)assert(restored.extraItems[i]==1); /* loading never refills potions */
 c.extraItems[1]=0;save_encode(bytes,&c);assert(save_decode(&parsed,bytes)==0);c.extraItems[1]=1;c.equipment=16;save_encode(bytes,&c);assert(save_decode(&parsed,bytes)==0);
 /* Version 1 remains a 96-byte format, including original CRC offset. */
 g.sp=10; /* Fixture must obey the original v1 SP cap. */ LegacyCharacter old;legacy_capture(&old,&g,99);unsigned char v1[LEGACY_BYTES],original[LEGACY_BYTES];legacy_encode(v1,&old);memcpy(original,v1,LEGACY_BYTES);LegacyCharacter imported;assert(legacy_decode(&imported,v1)==1);
 legacy_restore(&restored,&imported,2100,1636,openworld,NULL);assert(restored.apples==2&&restored.jellopy==7&&restored.clover==ITEM_STACK_MAX&&!restored.equipment&&restored.extraItems[0]==3);
 assert(!memcmp(v1,original,LEGACY_BYTES));save_capture(&c,&restored,1);save_encode(bytes,&c);assert(save_decode(&parsed,bytes)==1);
 puts("PASS: gear damage/defence, reversible equip, healing/no waste/KO, stack bounds, persistent empty stacks/loadout, semantic rejection, read-only v1 conversion");return 0;
}
