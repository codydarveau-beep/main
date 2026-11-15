/* MIT. Per-copy card insertion and weapon upgrade menus. */
#include "refine_rates52.h"
static const OwnedItem52*inventory_action_row52(const Combat*g,int ordinal){
 const OwnedItem52*card=owned_find52((OwnedItems52*)&g->owned52,0,g->cardUID52);const OwnedRule52*c=card?item_rule52(card->sourceID):NULL;
 for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(!p->quantity)continue;const OwnedRule52*r=item_rule52(p->sourceID);if(!owned_gear52(r)||!p->identified||(p->flags&OWNED_RESERVED_CARDS52))continue;
  int eligible=0;
  if(g->utilityMenu==700&&c&&!p->equipped&&(r->location&c->location)&&!(r->kind==OWNED_WEAPON52&&c->location==32)){for(unsigned n=0;n<r->slots;n++)if(!p->cards[n])eligible=1;}
  else if(g->utilityMenu==SK52_WS_WEAPONREFINE){const EquipmentRule52*e=equipment_rule52(p->sourceID);eligible=e&&r->kind==OWNED_WEAPON52&&r->refineable&&e->weaponLevel>=1&&e->weaponLevel<=4&&p->refine<10&&p->refine<class_rank50(g,SK52_WS_WEAPONREFINE);}
  if(eligible&&ordinal--==0)return p;
 }return NULL;
}
static int inventory_action_rows52(const Combat*g){int n=0;while(inventory_action_row52(g,n))n++;return n;}
static int inventory_action_commit52(Combat*g,int choice){
 const OwnedItem52*p=inventory_action_row52(g,choice);if(!p)return 0;uint32_t uid=p->uid;
 if(g->utilityMenu==700){int result=owned_insert_card52(&g->owned52,uid,g->cardUID52,item_rule52,NULL);if(result!=OWNED_OK52)return 0;g->utilityMenu=0;g->cardUID52=0;combat_notice(g,POP_ITEMS,"Card inserted.");stat_refresh(g);return 1;}
 const EquipmentRule52*e=equipment_rule52(p->sourceID);int material=e->weaponLevel==1?1002:e->weaponLevel==2?1003:984,item=inventory_catalog52(material);if(item<0||!inventory_count(g,item)){combat_notice(g,POP_ITEMS,"Need %s; weapon kept.",material==1002?"Phracon":material==1003?"Emveretarcon":"Oridecon");return 0;}
 int chance=10*refineChances52[e->weaponLevel-1][p->refine]+5*(g->joblevel-50);--*inventory_stack(g,item);OwnedItem52*gear=owned_find52(&g->owned52,0,uid);if(combat_random(g)%1000<(unsigned)(chance<0?0:chance)){gear->refine++;combat_notice(g,POP_ITEMS,"Upgraded %s to +%u.",e->name,gear->refine);}else{gear->equipped=0;owned_remove52(&g->owned52,0,uid,1);combat_notice(g,POP_ITEMS,"Refinement failed. The weapon was destroyed.");}g->utilityMenu=0;stat_refresh(g);return 1;
}
