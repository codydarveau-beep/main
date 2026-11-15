/* Original ammunition selected from carried stacks; no synthetic equipment copy. */
#ifndef MYRO_AMMO60_H
#define MYRO_AMMO60_H
#include "ammo_data60.h"
static int ammo_allowed60(const Combat*g,const AmmoRule60*r){return r&&g->level>=(int)r->minLevel&&(g->jobId<J60_NINJA||job_mask_has52(r->jobs,g->jobId));}
static const AmmoRule60*ammo_current60(const Combat*g,unsigned mask){
 if(g->selectedAmmo60){const AmmoRule60*r=ammo_rule60(g->selectedAmmo60);int item=inventory_catalog52(g->selectedAmmo60);return ammo_allowed60(g,r)&&(mask&(1u<<r->kind))&&item>=0&&inventory_count(g,item)>0?r:NULL;}
 for(unsigned i=0;i<sizeof(ammoRules60)/sizeof(*ammoRules60);i++){const AmmoRule60*r=ammoRules60+i;if(!ammo_allowed60(g,r)||!(mask&(1u<<r->kind)))continue;int item=inventory_catalog52(r->source);if(item>=0&&inventory_count(g,item)>0)return r;}return NULL;
}
static int inventory_consume_source60(Combat*g,unsigned source,unsigned amount){
 if(!amount)return 1;uint64_t count=0;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].sourceID==source&&!g->owned52.items[i].equipped)count+=g->owned52.items[i].quantity;if(count<amount)return 0;
 for(unsigned i=0;i<g->owned52.count[0]&&amount;){OwnedItem52*p=g->owned52.items+i;if(p->sourceID!=source||p->equipped){i++;continue;}unsigned take=p->quantity<amount?p->quantity:amount,uid=p->uid;int removed=take==p->quantity;int status=owned_remove52(&g->owned52,0,uid,take);if(status!=OWNED_OK52)return 0;amount-=take;if(!removed)i++;}if(ammo_rule60(source))g->ammoDirty60=1;return 1;
}
static unsigned ammo_weapon_mask60(unsigned weapon){return weapon>=17&&weapon<=20?1u<<3:weapon==21?1u<<5:weapon==10?1u<<1:0;}
static int ammo_attack60(Combat*g,int consume){unsigned mask=ammo_weapon_mask60(inventory_wtype46(g));if(!mask)return 1;const AmmoRule60*r=ammo_current60(g,mask);if(!r){combat_notice(g,POP_ITEMS,"No compatible ammunition. Select ammunition in Items.");return 0;}g->lastAmmoElement60=r->element;g->lastAmmoAttack60=r->attack;g->ammoShot60=!!consume;return!consume||inventory_consume_source60(g,r->source,1);}
#endif
