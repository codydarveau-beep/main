/* Per-instance storage transfers preserve cards, refinement, ownership and UIDs. */
#ifndef MYRO_NPC_STORAGE64_H
#define MYRO_NPC_STORAGE64_H
typedef struct{int slot;unsigned box,row,quantity;}NpcStorage64;
static unsigned npc_storage_count64(const Combat*g,unsigned box){unsigned n=0,base=owned_base52(box);for(unsigned i=0;i<g->owned52.count[box];i++)n+=g->owned52.items[base+i].quantity!=0;return n;}
static const OwnedItem52*npc_storage_item64(const Combat*g,unsigned box,unsigned row){unsigned base=owned_base52(box);for(unsigned i=0;i<g->owned52.count[box];i++){const OwnedItem52*p=g->owned52.items+base+i;if(p->quantity&&!row--)return p;}return NULL;}
static int npc_storage_transfer64(Combat*g,unsigned box,uint32_t uid,unsigned amount){if((box!=0&&box!=2)||!amount)return 0;OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;inventory_compact52(trial);int ok=owned_transfer52(trial,box,box?0:2,uid,amount,item_rule52)==OWNED_OK52;if(ok&&box){int64_t weight=0;for(unsigned i=0;i<trial->count[0];i++){const OwnedItem52*p=trial->items+i;const OwnedRule52*r=item_rule52(p->sourceID);if(r)weight+=(int64_t)r->weight*p->quantity;}if(weight>inventory_weight_max(g))ok=0;}if(ok&&owned_valid52(trial,item_rule52)){g->owned52=*trial;inventory_sync_gear52(g);stat_refresh(g);}else ok=0;free(trial);return ok;}
#endif
