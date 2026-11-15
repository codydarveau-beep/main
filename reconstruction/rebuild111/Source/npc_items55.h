/* MIT. Script item transactions preserve original ordinary-item-first priority. */
#ifndef MYRO_NPC_ITEMS55_H
#define MYRO_NPC_ITEMS55_H
#include "npc_vm55.h"
#include "npc_identity55.h"
static uint64_t npc_item_count55(const Combat*g,uint32_t source){uint64_t amount=0;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].sourceID==source)amount+=g->owned52.items[i].quantity;return amount;}
static int npc_item_plain55(const OwnedItem52*p){return!p->equipped&&!p->refine&&!(p->cards[0]|p->cards[1]|p->cards[2]|p->cards[3]);}
/* Original delitem may consume equipped/refined gear if ordinary copies run out. */
static int npc_item_take55(Combat*g,uint32_t source,uint32_t amount){
 if(!amount)return 1;if(!item_rule52(source)||npc_item_count55(g,source)<amount)return 0;OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;uint32_t left=amount;
 for(unsigned pass=0;pass<2&&left;pass++)for(unsigned i=0;i<trial->count[0]&&left;){OwnedItem52*p=trial->items+i;if(p->sourceID!=source||(pass==0?!npc_item_plain55(p):npc_item_plain55(p))){i++;continue;}uint32_t uid=p->uid,n=p->quantity<left?p->quantity:left;int erased=n==p->quantity;if(p->equipped)owned_unequip52(trial,uid);if(owned_remove52(trial,0,uid,n)!=OWNED_OK52){free(trial);return 0;}left-=n;if(!erased)i++;}
 if(left){free(trial);return 0;}g->owned52=*trial;free(trial);inventory_sync_gear52(g);stat_refresh(g);return 1;
}
/* Whole prospective reward is checked together; no inventory mutation. */
static int npc_items_fit55(const Combat*g,const uint32_t*sources,const uint32_t*amounts,uint32_t count){
 if(!count||count>NPC_VM_STACK55/2)return 0;OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;inventory_compact52(trial);int64_t weight=inventory_weight(g);int result=1;
 for(uint32_t i=0;i<count;i++){const OwnedRule52*r=item_rule52(sources[i]);if(!r||!amounts[i]||amounts[i]>INT_MAX||(uint64_t)weight+(uint64_t)r->weight*amounts[i]>(uint64_t)inventory_weight_max(g)||owned_add52(trial,0,sources[i],amounts[i],item_rule52)!=OWNED_OK52){result=0;break;}weight+=(int64_t)r->weight*amounts[i];}free(trial);return result;
}
static int npc_item_skill_level55(const Combat*g,unsigned source){if(source==681)return g->carryTraining180>10?10:g->carryTraining180;int native=npc_native_skill55(source);if(native<0)return 0;int k=skill_rank_index((unsigned)native),rank=k>=0?g->ranks[k]:0;if(native<512&&g->itemBonuses52.grant[native]>rank)rank=g->itemBonuses52.grant[native];return rank;}
#endif
