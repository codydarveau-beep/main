/* MIT. Bounded original Zeny-trader stock, shared by source-script duplicates. */
#ifndef MYRO_NPC_SHOP55_H
#define MYRO_NPC_SHOP55_H
#include "npc_item_commands55.h"
#define NPC_SHOP_ROWS55 8192u
typedef struct{uint32_t owner,item,price;}NpcShopRow55;
typedef struct{NpcShopRow55*rows;unsigned count,capacity;}NpcShop55;
static int npc_shop_set55(NpcShop55*s,uint32_t owner,uint32_t item,uint32_t price){
 for(unsigned i=0;i<s->count;i++)if(s->rows[i].owner==owner&&s->rows[i].item==item){s->rows[i].price=price;return 1;}
 if(s->count>=NPC_SHOP_ROWS55)return 0;if(s->count==s->capacity){unsigned capacity=s->capacity?s->capacity*2:64;if(capacity>NPC_SHOP_ROWS55)capacity=NPC_SHOP_ROWS55;void*p=realloc(s->rows,capacity*sizeof(*s->rows));if(!p)return 0;s->rows=p;s->capacity=capacity;}s->rows[s->count++]=(NpcShopRow55){owner,item,price};return 1;
}
static int npc_shop_command55(NpcShop55*s,uint32_t owner,NpcMachine55*m,const char*name,const NpcValue55*args,unsigned count,NpcValue55*out){
 if(strcmp(name,"sellitem"))return-1;if(count<1||count>2||!owner)return N55_ERROR;uint32_t source;int identified;if(!npc_item_source55(m,args[0],0,&source,&identified))return N55_ERROR;int item=item_source50(source);if(item<0)return N55_ERROR;
 int64_t price=-1;if(count==2&&!npc_vm_integer55(m,args[1],&price))return N55_ERROR;if(price==-1)price=shopBuy[item];if(price<0||price>1000000000)return N55_ERROR;*out=npc_vm_number55(0);return npc_shop_set55(s,owner,(uint32_t)item,(uint32_t)price)?N55_READY:N55_ERROR;
}
static void npc_shop_clear55(NpcShop55*s){free(s->rows);memset(s,0,sizeof(*s));}
#endif
