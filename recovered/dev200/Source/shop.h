/* SPDX-License-Identifier: MIT. Atomic in-memory transactions; persistence uses SaveStore. */
#ifndef MYRO_SHOP_H
#define MYRO_SHOP_H
#define ZENY_MAX 1000000000
#include "item_access52.h"
static int shop_rate(const Combat*g,int selling){int r=(job_first50(g->jobId)==6||g->jobId==J52_SUPER_NOVICE)?g->ranks[selling?15:14]:0,rate=r?(r==10?24:5+2*r):0;if(!selling&&g->jobId==13&&class_rank50(g,151)){int rogue=5+4*class_rank50(g,151);if(rogue>rate)rate=rogue;}return rate;}
static int shop_price(const Combat*g,int item,int selling){if(item<0||item>=ITEM_COUNT)return 0;int base=selling?shopSell[item]:shopBuy[item];if(!base)return 0;int price=(int)((int64_t)base*(100+(selling?1:-1)*shop_rate(g,selling))/100);return price<1?1:price;}
static int shop_sellable55(const OwnedItem52*p){return p&&p->quantity&&p->identified&&!p->equipped&&!p->bound;}
/* The selected instance, not every item sharing its catalog name. */
static int shop_sell_uid55(Combat*g,uint32_t uid,unsigned quantity){OwnedItem52*p=owned_find52(&g->owned52,0,uid);if(!shop_sellable55(p)||!quantity||quantity>p->quantity||quantity>100||g->hp<=0){combat_notice(g,POP_ITEMS,"This item cannot be sold. Nothing changed.");return 0;}int item=item_source50(p->sourceID),price=shop_price(g,item,1);int64_t total=(int64_t)price*quantity;if(price<=0||total>ZENY_MAX-g->zeny){combat_notice(g,POP_ITEMS,"Sale unavailable or Zeny limit reached. Item kept.");return 0;}if(owned_remove52(&g->owned52,0,uid,quantity)!=OWNED_OK52)return 0;g->zeny+=(int)total;combat_notice(g,POP_ITEMS,"Sold %u %s for %d Zeny.",quantity,itemDefs[item].name,(int)total);return 1;}
static int shop_plain_sale55(const OwnedItem52*p){return shop_sellable55(p)&&!p->refine&&!(p->flags&~OWNED_LEGACY_STACK52)&&!(p->cards[0]|p->cards[1]|p->cards[2]|p->cards[3]);}
/* One press buys/sells one, with optional 10/100 quantity selected explicitly. */
static int shop_trade(Combat*g,int item,int quantity,int selling){
 if(g->hp<=0||item<0||item>=ITEM_COUNT||quantity<1||quantity>100){combat_notice(g,POP_ITEMS,"Invalid transaction.");return 0;}
 int price=shop_price(g,item,selling);
 if(price<=0){combat_notice(g,POP_ITEMS,"This item is not sold here.");return 0;}
 int64_t total=(int64_t)price*quantity;
 if(selling){
  unsigned available=0,source=itemDefs[item].id;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].sourceID==source&&shop_plain_sale55(g->owned52.items+i))available+=g->owned52.items[i].quantity;
  if(available<(unsigned)quantity){combat_notice(g,POP_ITEMS,"Not enough plain,unequipped items. Special gear kept.");return 0;}
  if(total>ZENY_MAX-g->zeny){combat_notice(g,POP_ITEMS,"Zeny limit reached. Items kept.");return 0;}
  OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;unsigned remaining=quantity;while(remaining){OwnedItem52*p=NULL;for(unsigned i=0;i<trial->count[0];i++)if(trial->items[i].sourceID==source&&shop_plain_sale55(trial->items+i)){p=trial->items+i;break;}if(!p){free(trial);return 0;}unsigned amount=p->quantity<remaining?p->quantity:remaining;if(owned_remove52(trial,0,p->uid,amount)!=OWNED_OK52){free(trial);return 0;}remaining-=amount;}g->owned52=*trial;free(trial);g->zeny+=(int)total;
 }else{
  if(total>g->zeny){combat_notice(g,POP_ITEMS,"Not enough Zeny.");return 0;}
  if(!inventory_can_add(g,item,quantity)){combat_notice(g,POP_ITEMS,"Item weight or stack limit reached.");return 0;}
  if(!inventory_add(g,item,quantity))return 0;g->zeny-=(int)total;
 }
 combat_notice(g,POP_ITEMS,"%s %d %s for %d Zeny.",selling?"Sold":"Bought",quantity,itemDefs[item].name,(int)total);return 1;
}
#endif
