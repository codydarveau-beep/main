/* SPDX-License-Identifier: MIT
 * Small fixed item catalog, using supplied pre-re item IDs and base values.
 * Included by combat.h after Combat and its RNG/message helpers are defined.
 */
#ifndef MYRO_INVENTORY_H
#define MYRO_INVENTORY_H
#include "equipment_data52.h"
#include "owned_equip52.h"

#define ITEM_STACK_MAX 1000000000
#define STORAGE_STACK_MAX 30000
enum { ITEM_APPLE,ITEM_JELLOPY,ITEM_CLOVER,ITEM_RED_POTION,ITEM_KNIFE,ITEM_SHIRT,ITEM_SANDALS,ITEM_GUARD,ITEM_BOW,ITEM_BLUE_GEM,ITEM_RED_GEM,ITEM_EMPTY_BOTTLE,ITEM_HOLY_WATER,ITEM_STONE,ITEM_ARROW,ITEM_TREE_ROOT,ITEM_KATANA,ITEM_UNIDENTIFIED };
typedef struct {int id;const char*name;const char*description;int healMin,healMax,attack,defense;unsigned equipBit,jobs,minLevel,slot,wtype,twoHand,matk,spMin,spMax,weaponLv;} ItemDef;
static const ItemDef itemDefs[ITEM_COUNT]={
#include "item_catalog_rows52.inc"
};
/* Owned quantities are sparse; returned stack pointers are only short-lived.
 * Existing skill code consumes a known stack immediately. Empty records are
 * removed before additions/transfers and from the saved snapshot. */
static void inventory_compact52(OwnedItems52*b){for(unsigned box=0;box<3;box++){unsigned base=owned_base52(box);for(unsigned i=0;i<b->count[box];)if(!b->items[base+i].quantity)owned_erase52(b,box,b->items+base+i);else i++;}}
static int inventory_box_count52(const Combat*g,unsigned box,int item){if(box>=3||item<0||item>=ITEM_COUNT)return 0;uint32_t source=(uint32_t)itemDefs[item].id;int n=0;unsigned base=owned_base52(box);for(unsigned i=0;i<g->owned52.count[box];i++)if(g->owned52.items[base+i].sourceID==source)n+=(int)g->owned52.items[base+i].quantity;return n;}
static const OwnedItem52*inventory_broken52(const Combat*g){for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity&&(g->owned52.items[i].flags&OWNED_BROKEN52))return g->owned52.items+i;return NULL;}
static int inventory_repair52(Combat*g,uint32_t uid){OwnedItem52*p=owned_find52(&g->owned52,0,uid);if(!p||!(p->flags&OWNED_BROKEN52))return 0;p->flags&=(uint8_t)~OWNED_BROKEN52;g->brokenWeapon48=0;return 1;}
static unsigned inventory_gem_cost52(const Combat*g,unsigned skill,unsigned source,unsigned amount){if(source>=715&&source<=717&&g->itemBonuses52.scalar[B52_bNoGemStone]&&skill!=SK52_HW_GANBANTEIN)return skill==106?(amount>1?amount-1:1):0;return amount;}
static int inventory_count(const Combat*g,int item){return inventory_box_count52(g,0,item);}
static int*inventory_stack(Combat*g,int item){
 if(item<0||item>=ITEM_COUNT)return NULL;uint32_t source=(uint32_t)itemDefs[item].id;
 for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].sourceID==source&&g->owned52.items[i].quantity)return(int*)&g->owned52.items[i].quantity;
 /* A few original crafting paths increment a preflighted output stack. */
 if(g->owned52.count[0]<OWNED_BAG52&&g->owned52.nextUID&&g->owned52.nextUID<UINT32_MAX){OwnedItem52*p=g->owned52.items+g->owned52.count[0]++;memset(p,0,sizeof(*p));p->sourceID=source;p->uid=g->owned52.nextUID++;p->identified=1;return(int*)&p->quantity;}
 g->missingStack52=0;return &g->missingStack52;
}
/* Pre-renewal weights in tenths; bounded catalog/cart, not generic item instances. */
static const int itemWeights[ITEM_COUNT]={
#include "item_weights52.inc"
};
static const unsigned inventorySlotBits52[EQUIP_SLOTS46]={2,16,64,32,4|8192,256|1024,8,128,512|2048,1|4096};
static const OwnedItem52*inventory_instance52(const Combat*g,int slot){if(slot<0||slot>=EQUIP_SLOTS46)return NULL;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity&&(g->owned52.items[i].equipped&inventorySlotBits52[slot]))return g->owned52.items+i;return NULL;}
static const uint16_t itemCatalogIndex52[ITEM_COUNT]={
#include "item_index52.inc"
};
static int inventory_catalog52(uint32_t source){const OwnedRule52*r=item_rule52(source);return r?(int)itemCatalogIndex52[r-itemRules52]:-1;}
static int inventory_slot46(const Combat*g,int slot){const OwnedItem52*p=inventory_instance52(g,slot);return p?inventory_catalog52(p->sourceID):-1;}
static void item_script_refresh52(Combat*g);
static void inventory_sync_gear52(Combat*g){g->equipment=0;for(int slot=0;slot<EQUIP_SLOTS46;slot++){int id=inventory_slot46(g,slot);g->equipped46[slot]=id<0?0:id+1;if(id>=0)g->equipment|=itemDefs[id].equipBit;}item_script_refresh52(g);}
static int inventory_equipped46(const Combat*g,int item){if(item<0||item>=ITEM_COUNT)return 0;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity&&g->owned52.items[i].equipped&&g->owned52.items[i].sourceID==(uint32_t)itemDefs[item].id)return 1;return 0;}
static int inventory_can_equip46(const Combat*g,int item){if(item<0||item>=ITEM_COUNT)return 0;const ItemDef*d=&itemDefs[item];return d->equipBit&&equipment_allowed52(equipment_rule52((uint32_t)d->id),g->jobId,(g->jobId>=J60_NINJA?g->sex55:((job_parent52(g->jobId)==16||g->jobId==J52_GYPSY)?0:1)),(unsigned)g->level);}
/* Assassin off-hand weapons share the shield destination, without changing saved slot IDs. */
static int inventory_weapon_hand50(unsigned type){return type==1||type==2||type==6;}
static int inventory_fits50(const Combat*g,int item,int slot){if(!inventory_can_equip46(g,item))return 0;const ItemDef*d=&itemDefs[item];const OwnedRule52*r=item_rule52((uint32_t)d->id);if(r&&r->kind==OWNED_ARMOR52&&(r->location&inventorySlotBits52[slot]))return 1;if(d->slot==(unsigned)slot)return 1;if(job_parent52(g->jobId)!=12||slot!=3||d->slot!=0||d->twoHand||!inventory_weapon_hand50(d->wtype))return 0;int right=inventory_slot46(g,0);return right>=0&&!itemDefs[right].twoHand&&inventory_weapon_hand50(itemDefs[right].wtype)&&(right!=item||inventory_count(g,item)>=2);}
static void inventory_remove46(Combat*g,int slot){const OwnedItem52*p=inventory_instance52(g,slot);if(p){owned_unequip52(&g->owned52,p->uid);inventory_sync_gear52(g);}}
static int inventory_equip_uid52(Combat*g,uint32_t uid,int slot){if(class_active50(g,SK52_LK_BERSERK)||slot<0||slot>=EQUIP_SLOTS46)return 0;OwnedItem52*p=owned_find52(&g->owned52,0,uid);if(!p)return 0;unsigned position=inventorySlotBits52[slot],allowed=item_rule52(p->sourceID)->location;position&=allowed;if(slot==3&&owned_gear52(item_rule52(p->sourceID))&&item_rule52(p->sourceID)->kind==OWNED_WEAPON52)position=32;if(!position)return 0;position&=0u-position;int result=owned_equip52(&g->owned52,uid,g->jobId,(g->jobId>=J60_NINJA?g->sex55:((g->jobId==16||g->jobId==J52_GYPSY)?0:1)),g->level,position,NULL);if(result!=OWNED_OK52)return 0;inventory_sync_gear52(g);return 1;}
static int inventory_equip_slot50(Combat*g,int item,int slot){if(!inventory_fits50(g,item,slot))return 0;for(unsigned i=0;i<g->owned52.count[0];i++){OwnedItem52*p=g->owned52.items+i;if(p->quantity&&p->sourceID==(uint32_t)itemDefs[item].id&&!p->equipped&&!(p->flags&OWNED_BROKEN52))return inventory_equip_uid52(g,p->uid,slot);}return 0;}
static void inventory_reconcile46(Combat*g){for(unsigned i=0;i<g->owned52.count[0];i++){OwnedItem52*p=g->owned52.items+i;if(p->equipped&&(!p->quantity||(p->flags&OWNED_BROKEN52)||!equipment_allowed52(equipment_rule52(p->sourceID),g->jobId,(g->jobId>=J60_NINJA?g->sex55:((g->jobId==16||g->jobId==J52_GYPSY)?0:1)),g->level)))p->equipped=0;}inventory_sync_gear52(g);}
static int inventory_wtype46(const Combat*g){int id=inventory_slot46(g,0);return id>=0?itemDefs[id].wtype:0;}
static int inventory_matk46(const Combat*g,int power){return (power+g->itemBonuses52.scalar[B52_bMatk])*(100+g->itemBonuses52.scalar[B52_bMatkRate])/100;}
#define CART_WEIGHT_MAX 80000
static int64_t inventory_box_weight52(const Combat*g,unsigned box){int64_t weight=0;unsigned base=owned_base52(box);for(unsigned i=0;i<g->owned52.count[box];i++){const OwnedItem52*p=g->owned52.items+base+i;const OwnedRule52*r=item_rule52(p->sourceID);if(r)weight+=(int64_t)p->quantity*r->weight;}return weight;}
static int64_t inventory_weight(const Combat*g){return inventory_box_weight52(g,0);}
static int64_t inventory_cart_weight(const Combat*g){return inventory_box_weight52(g,1);}
static int inventory_weight_max(const Combat*g){static const int base[12]={20000,28000,22000,24000,24000,26000,28000,28000,22000,22000,24000,28000};int weight=(g->jobId>=J60_NINJA&&g->jobId<J52_COUNT?(int)expandedWeight60[g->jobId-J60_NINJA]:base[job_first50(g->jobId)])+300*g->stats[0]+((job_first50(g->jobId)==6||g->jobId==J52_SUPER_NOVICE)?2000*g->ranks[57]:0);weight+=2000*(g->carryTraining180>10?10:g->carryTraining180);return weight+weight*class_active50(g,SK60_SG_KNOWLEDGE)/10;}
static int inventory_overweight(const Combat*g,int percent){return inventory_weight(g)*100>=(int64_t)inventory_weight_max(g)*percent;}
static float inventory_cart_speed(const Combat*g){return g->cartOwned&&(job_first50(g->jobId)==6||g->jobId==J52_SUPER_NOVICE)?100.f/(150-5*g->ranks[59]):1.f;}
static int inventory_can_add(const Combat*g,int item,int amount){if(item<0||item>=ITEM_COUNT||amount<=0)return 0;const OwnedRule52*r=item_rule52((uint32_t)itemDefs[item].id);if(!r||inventory_weight(g)+(int64_t)r->weight*amount>inventory_weight_max(g))return 0;uint64_t room=0;unsigned used=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(!p->quantity)continue;used++;if(!owned_gear52(r)&&p->sourceID==r->sourceID&&p->identified&&!p->bound&&!p->flags&&p->quantity<r->stackLimit)room+=r->stackLimit-p->quantity;}uint64_t rest=amount>room?amount-room:0,stack=owned_gear52(r)?1:r->stackLimit;return stack&&((rest+stack-1)/stack)<=OWNED_BAG52-used;}
/* Pre-renewal physical-only coat: exact 20% boundaries, integer SP costs.
 * Like the reference, the last covered hit is reduced if the drain ends the coat. */
static int inventory_energy_hit(Combat*g,int damage){if(damage<=0||g->energyCoatLeft<=0||g->maxsp<=0)return damage;int band=(100*g->sp/g->maxsp-1)/20;if(band<0)band=0;if(band>4)band=4;int cost=(10+5*band)*g->maxsp/1000;if(g->sp<cost)g->energyCoatLeft=0;else g->sp-=cost;return damage-damage*(6*(1+band))/100;}
static int inventory_transfer52(Combat*g,unsigned from,unsigned to,int item,int quantity){if(item<0||item>=ITEM_COUNT||quantity<=0||inventory_box_count52(g,from,item)<quantity)return 0;if(to==0&&!inventory_can_add(g,item,quantity))return 0;const OwnedRule52*r=item_rule52((uint32_t)itemDefs[item].id);if(to==1&&inventory_cart_weight(g)+(int64_t)r->weight*quantity>CART_WEIGHT_MAX)return 0;OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;inventory_compact52(trial);unsigned base=owned_base52(from);int remaining=quantity;while(remaining>0){OwnedItem52*p=NULL;for(unsigned i=0;i<trial->count[from];i++)if(trial->items[base+i].sourceID==r->sourceID&&!trial->items[base+i].equipped){p=trial->items+base+i;break;}if(!p)break;unsigned amount=p->quantity<(unsigned)remaining?p->quantity:(unsigned)remaining;if(owned_transfer52(trial,from,to,p->uid,amount,item_rule52)!=OWNED_OK52)break;remaining-=amount;}if(!remaining)g->owned52=*trial;free(trial);return remaining==0;}
static int inventory_cart_transfer(Combat*g,int item,int take){if(!g->cartOwned)return 0;int quantity=g->cartQuantity?g->cartQuantity:1;if(quantity!=1&&quantity!=10&&quantity!=100)return 0;return inventory_transfer52(g,take?1:0,take?0:1,item,quantity);}
static int inventory_storage_transfer(Combat*g,int item,int quantity,int take){if(quantity!=1&&quantity!=10&&quantity!=100)return 0;return inventory_transfer52(g,take?2:0,take?0:2,item,quantity);}
static int inventory_add(Combat*g,int item,int amount){if(!inventory_can_add(g,item,amount))return 0;inventory_compact52(&g->owned52);return owned_add52(&g->owned52,0,(uint32_t)itemDefs[item].id,(uint32_t)amount,item_rule52)==OWNED_OK52;}
static int inventory_drop52(Combat*g,unsigned source){int item=inventory_catalog52(source);if(item<0)return 0;uint32_t first=g->owned52.nextUID;if(!inventory_add(g,item,1))return 0;const OwnedRule52*r=item_rule52(source);if(owned_gear52(r))for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].uid>=first)g->owned52.items[i].identified=0;return 1;}
static const OwnedItem52*inventory_unidentified52(const Combat*g,int row){for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(p->quantity&&!p->identified&&owned_gear52(item_rule52(p->sourceID))&&row--==0)return p;}return NULL;}
static int inventory_unidentified_count52(const Combat*g){int n=0;while(inventory_unidentified52(g,n))n++;return n;}
static void inventory_starter(Combat*g){owned_init52(&g->owned52);inventory_add(g,ITEM_APPLE,3);inventory_add(g,ITEM_RED_POTION,3);for(int i=ITEM_KNIFE;i<=ITEM_GUARD;i++)inventory_add(g,i,1);g->equipment=0;}
static unsigned ammo_attack_value60(const Combat*g);
static int inventory_attack(const Combat*g){int id=inventory_slot46(g,0);if(id<0)return job_parent52(g->jobId)==18?3*class_rank50(g,198):job_parent52(g->jobId)==19?2*class_rank50(g,227)+(class_rank50(g,225)?4:0):0;const OwnedItem52*piece=inventory_instance52(g,0);int w=itemDefs[id].wtype,p=itemDefs[id].attack+g->itemBonuses52.scalar[B52_bBaseAtk];if(piece){int lv=itemDefs[id].weaponLv;if(lv>=1&&lv<=4)p+=piece->refine*(int[]){0,2,3,5,7}[lv];}if(job_parent52(g->jobId)==18&&w==13)p+=3*class_rank50(g,198);if(job_parent52(g->jobId)==12&&w==16)p+=3*class_rank50(g,129);if(job_parent52(g->jobId)==15&&w==14)p+=3*class_rank50(g,172);if(job_parent52(g->jobId)==16&&w==15)p+=3*class_rank50(g,179);if(job_parent52(g->jobId)==17&&w==8)p+=3*class_rank50(g,186);if(job_parent52(g->jobId)==20&&(w==6||w==7))p+=3*class_rank50(g,237);if(job_parent52(g->jobId)==19)p+=2*class_rank50(g,227)+(class_rank50(g,225)?4:0);if(job_parent52(g->jobId)==10&&w==11)p+=3*class_rank48(g,90);if(job_parent52(g->jobId)==11&&(w==4||w==5))p+=(g->mounted48?5:4)*class_rank48(g,114);if(w==10)p+=inventory_count(g,ITEM_ARROW)>0?25:0;if(w>=17&&w<=21)p+=(int)ammo_attack_value60(g);if((g->jobId==1||g->jobId==7||job_parent52(g->jobId)==11||job_parent52(g->jobId)==13)&&(w==1||w==2))p+=4*g->ranks[31];if((g->jobId==1||g->jobId==7||job_parent52(g->jobId)==11)&&w==3)p+=4*g->ranks[64];return p;}
static int inventory_defense(const Combat*g){if(class_active50(g,SK52_LK_BERSERK))return 0;if(class_active50(g,207))return 90;int n=0,refine=0;uint32_t seen[EQUIP_SLOTS46]={0};unsigned seenCount=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(p->equipped&&item_rule52(p->sourceID)->kind==OWNED_ARMOR52)refine+=p->refine;}n+=refine*7/10;for(int s=1;s<EQUIP_SLOTS46;s++){int id=inventory_slot46(g,s);if(id>=0&&itemDefs[id].slot!=0){const OwnedItem52*p=inventory_instance52(g,s);int duplicate=0;for(unsigned k=0;k<seenCount;k++)if(seen[k]==p->uid)duplicate=1;if(!duplicate){seen[seenCount++]=p->uid;n+=itemDefs[id].defense;}}}if(job_parent52(g->jobId)==20&&g->class50.homunBuffUntil[5]>g->time)n+=2*g->persistent50.homunSkills[5];n+=g->itemBonuses52.scalar[B52_bDef];n=n*(100+g->itemBonuses52.scalar[B52_bDefRate])/100;n-=n*5*class_active50(g,SK52_LK_CONCENTRATION)/100;return n;}
static int item_use52(Combat*g,unsigned source);
#include "ammo60.h"
static unsigned ammo_attack_value60(const Combat*g){if(g->ammoShot60)return g->lastAmmoAttack60;const AmmoRule60*r=ammo_current60(g,ammo_weapon_mask60(inventory_wtype46(g)));return r?r->attack:0;}
static void inventory_action(Combat*g,int item){if(g->jobId>=J60_NINJA&&item>=0&&item<ITEM_COUNT&&ammo_rule60(itemDefs[item].id)){const AmmoRule60*r=ammo_rule60(itemDefs[item].id);if(!ammo_allowed60(g,r)){combat_notice(g,POP_ITEMS,"This ammunition does not match your class or level.");return;}g->selectedAmmo60=g->selectedAmmo60==r->source?0:r->source;stat_refresh(g);combat_notice(g,POP_ITEMS,g->selectedAmmo60?"Selected %s ammunition.":"Ammunition selection: automatic.",itemDefs[item].name);return;}if(item>=0&&item<ITEM_COUNT&&((itemDefs[item].id==601&&job_noteleport55(g->mapId))||(itemDefs[item].id==602&&job_noreturn55(g->mapId)))){combat_notice(g,POP_ITEMS,"This exam room prevents that teleport item.");return;}
if(g->trickDead55){combat_notice(g,POP_ITEMS,"End Play Dead before using items.");return;}if(class_active50(g,SK52_LK_BERSERK)){combat_notice(g,POP_ITEMS,"Berserk prevents using items or changing gear.");return;}
 if(item<0||item>=ITEM_COUNT)return;
 const ItemDef*d=&itemDefs[item];uint32_t actionUID=g->itemActionUID52;g->itemActionUID52=0;OwnedItem52*action=actionUID?owned_find52(&g->owned52,0,actionUID):NULL;int*n=inventory_stack(g,item);
 if(g->hideLeft>0){combat_notice(g,POP_ITEMS,"B or Hiding: emerge before using items.");return;}
 if(g->hp<=0){combat_notice(g,POP_ITEMS,"Return to camp before using or equipping items.");return;}
 if(*n<=0){combat_notice(g,POP_ITEMS,"You do not have any %s.",d->name);return;}
 if(item_rule52((uint32_t)d->id)->kind==OWNED_CARD52){if(!action)for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity&&g->owned52.items[i].sourceID==(uint32_t)d->id){action=g->owned52.items+i;break;}if(action){g->cardUID52=action->uid;g->utilityMenu=700;g->autoAttack=0;}return;}
 if(item_use52(g,(unsigned)d->id))return;
 if(d->healMin||d->spMin){
  if((!d->healMin||g->hp>=g->maxhp)&&(!d->spMin||g->sp>=g->maxsp)){combat_notice(g,POP_ITEMS,"HP/SP already full. Item kept.");return;}
  int heal=d->healMin+(int)(combat_random(g)%(unsigned)(d->healMax-d->healMin+1));heal=heal*(100+2*stat_value(g,2))/100;int hpRankIndex=skill_rank_index(26),spRankIndex=skill_rank_index(25);heal=heal*(100+(hpRankIndex>=0?10*g->ranks[hpRankIndex]:0)+5*class_rank50(g,238)+item_bonus_match52(g,B52_bAddItemHealRate,d->id,-1))/100;if(heal>g->maxhp-g->hp)heal=g->maxhp-g->hp;
  g->hp+=heal;int oldsp53=g->sp;int sp=d->spMin+(d->spMax>d->spMin?combat_random(g)%(d->spMax-d->spMin+1):0);sp=sp*(100+2*stat_value(g,3))/100;sp=sp*(100+(spRankIndex>=0?10*g->ranks[spRankIndex]:0)+5*class_rank50(g,238))/100;g->sp+=sp;if(g->sp>g->maxsp)g->sp=g->maxsp;combat_recovery_number53(g,heal,g->sp-oldsp53);--*n;combat_notice(g,POP_ITEMS,"Used %s: +%d HP. Remaining: %d",d->name,heal,*n);
 }else if(d->id>=612&&d->id<=615&&job_parent52(g->jobId)==19){g->utilityMenu=600;g->class50.craftTool=d->id;g->autoAttack=0;}else if(d->equipBit){
  if(!inventory_can_equip46(g,item)){combat_notice(g,POP_ITEMS,"%s requires another job or base level %u.",d->name,d->minLevel);return;}
  int slot=d->slot;if(action){if(action->equipped){owned_unequip52(&g->owned52,action->uid);inventory_sync_gear52(g);}else inventory_equip_uid52(g,action->uid,slot);stat_refresh(g);return;}if(inventory_equipped46(g,item)){for(int worn=0;worn<EQUIP_SLOTS46;worn++)if(inventory_slot46(g,worn)==item){inventory_remove46(g,worn);break;}combat_notice(g,POP_ITEMS,"Removed %s.",d->name);return;}
  inventory_equip_slot50(g,item,slot);combat_notice(g,POP_ITEMS,"Equipped %s.",d->name);
 }else combat_notice(g,POP_ITEMS,item>=ITEM_BLUE_GEM?"%s: consumed automatically by its matching skill.":"%s is loot; no use action yet.",d->name);
}
#include "item_script_runtime52.h"
#endif
