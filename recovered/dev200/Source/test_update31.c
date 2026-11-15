/* MIT. Reagent transactions, bounded defence/status, save and developer coverage. */
#include <assert.h>
#include "save_store.h"
#include "shop.h"
#include "developer.h"
#include "sprite_tint.h"
static int clear(void*w,float x,float y,float nx,float ny){return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
static int blocked(void*w,float x,float y,float nx,float ny){return 0;}
static void ready(Combat*g){g->sp=g->maxsp;g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));}
static void mage(Combat*g){combat_init(g,1500,1500,clear,NULL);dev_class_preset(g,2);memset(g->mobs,0,sizeof(g->mobs));}
static CombatMob*target(Combat*g){CombatMob*m=&g->mobs[0];memset(m,0,sizeof(*m));m->enabled=m->training=1;m->testMaxHP=m->hp=10000;m->kind=0;m->x=g->x+8;m->y=g->y;g->target=0;return m;}
int main(void){uint16_t px[65536];for(unsigned i=0;i<65536;i++)px[i]=i;sprite_stone(px,65536,2);for(unsigned i=0;i<65536;i++){assert((px[i]&0x8000)==(i&0x8000));if(i&0x8000)assert((px[i]&31)==(px[i]>>5&31)&&(px[i]&31)==(px[i]>>10&31));else assert(px[i]==i);}
 Combat g;mage(&g);assert(LEARN_COUNT==46&&SKILL_COUNT==50);assert(inventory_count(&g,ITEM_BLUE_GEM)==100&&inventory_count(&g,ITEM_RED_GEM)==100);
 int sp=g.sp;*inventory_stack(&g,ITEM_BLUE_GEM)=0;assert(!skill_cast(&g,48,g.x,g.y)&&g.sp==sp&&g.skillCD[47]==0);inventory_add(&g,ITEM_BLUE_GEM,10);g.canMove=blocked;assert(!skill_cast(&g,48,g.x,g.y)&&g.sp==sp&&inventory_count(&g,ITEM_BLUE_GEM)==10);g.canMove=clear;assert(!skill_cast(&g,48,3000,3000)&&g.sp==sp);assert(skill_cast(&g,48,g.x,g.y)&&g.sp==sp-40&&inventory_count(&g,ITEM_BLUE_GEM)==9);assert(g.safety[0].hits==11);ready(&g);sp=g.sp;assert(!skill_cast(&g,48,g.x,g.y)&&g.sp==sp&&inventory_count(&g,ITEM_BLUE_GEM)==9);
 float x=g.x;g.x+=8;assert(!combat_safety_block(&g));g.x=x;for(int i=0;i<11;i++)assert(combat_safety_block(&g));assert(!combat_safety_block(&g));ready(&g);assert(skill_cast(&g,48,g.x,g.y));g.time+=51;assert(!combat_safety_block(&g));ready(&g);assert(skill_cast(&g,48,g.x,g.y));ready(&g);assert(skill_cast(&g,48,g.x+8,g.y));ready(&g);assert(skill_cast(&g,48,g.x+16,g.y));ready(&g);sp=g.sp;int blue=inventory_count(&g,ITEM_BLUE_GEM);assert(!skill_cast(&g,48,g.x+24,g.y)&&g.sp==sp&&inventory_count(&g,ITEM_BLUE_GEM)==blue);combat_support_clear(&g);for(int i=0;i<3;i++)assert(!g.safety[i].hits);
 CombatMob*m=target(&g);ready(&g);sp=g.sp;*inventory_stack(&g,ITEM_RED_GEM)=0;assert(!skill_cast(&g,49,0,0)&&g.sp==sp);inventory_add(&g,ITEM_RED_GEM,1000);m->testTraits=3;assert(!skill_cast(&g,49,0,0)&&g.sp==sp&&inventory_count(&g,ITEM_RED_GEM)==1000);m->testTraits=2;assert(!skill_cast(&g,49,0,0)&&g.sp==sp);m->testTraits=0;
 int succeeded=0,failed=0;for(int i=0;i<100;i++){ready(&g);m->stoneWait=m->stoneLeft=0;int before=inventory_count(&g,ITEM_RED_GEM);assert(skill_cast(&g,49,0,0)&&g.sp==g.maxsp-16);if(m->stoneWait){succeeded++;assert(inventory_count(&g,ITEM_RED_GEM)==before-1);}else{failed++;assert(inventory_count(&g,ITEM_RED_GEM)==before);}}assert(succeeded&&failed);
 // Waiting is not a freeze; only full stone breaks on damage. Low rank failures spend a gem.
 m->stoneWait=5;m->stoneLeft=0;combat_enemy_damage(&g,m,1);assert(m->stoneWait==5);combat_stone_tick(&g,m,4);assert(m->stoneWait==1&&!m->stoneLeft);combat_stone_tick(&g,m,1);assert(!m->stoneWait&&m->stoneLeft==20);int hp=m->hp;combat_stone_tick(&g,m,5);assert(m->hp==hp-100&&m->stoneLeft==15);combat_enemy_damage(&g,m,1);assert(!m->stoneLeft);g.ranks[45]=1;ready(&g);int red=inventory_count(&g,ITEM_RED_GEM);assert(skill_cast(&g,49,0,0)&&inventory_count(&g,ITEM_RED_GEM)==red-1);
 mage(&g);*inventory_stack(&g,ITEM_BLUE_GEM)=0;int money=g.zeny;assert(shop_trade(&g,ITEM_BLUE_GEM,10,0)&&g.zeny==money-6000&&inventory_count(&g,ITEM_BLUE_GEM)==10);assert(shop_trade(&g,ITEM_RED_GEM,10,1)&&g.zeny==money-3000);int held=inventory_count(&g,ITEM_RED_GEM);assert(!shop_trade(&g,ITEM_RED_GEM,100,0)&&inventory_count(&g,ITEM_RED_GEM)==held);
 SavedCharacter a,b;unsigned char bytes[SAVE_BYTES];save_capture(&a,&g,1);assert(save_valid(&a));save_encode(bytes,&a);assert(save_decode(&b,bytes)==1&&b.extraItems[6]==10&&b.extraItems[7]==90&&b.ranks[44]==10&&b.ranks[45]==10);bytes[232]^=1;assert(!save_decode(&b,bytes));
 // New ordinary skills are not free quest unlocks; Safety Wall needs both dependencies.
 mage(&g);g.ranks[44]=g.ranks[45]=0;g.skillPoints=0;assert(!skill_learn(&g,49));g.skillPoints=1;assert(skill_learn(&g,49)&&!g.skillPoints);g.skillPoints=1;g.ranks[18]=6;assert(!skill_learn(&g,48)&&g.skillPoints==1);g.ranks[18]=7;assert(skill_learn(&g,48)&&!g.skillPoints);
 DeveloperUI u;dev_open(&u,&g);assert(dev_rows(2)==6);dev_input(&u,&g,512);dev_input(&u,&g,512);assert(u.tab==2);dev_input(&u,&g,512);assert(!u.tab);dev_input(&u,&g,32);assert(u.tab==2);
 printf("PASS Test31: reagent cost/guards/refunds; SafetyWall cells/hit budget/expiry/cap/clear; Stone incubation/drain/break/immunity; shop/save CRC; learning points/prerequisites;3 developer tabs. Combat bytes=%zu\n",sizeof(Combat));
}
