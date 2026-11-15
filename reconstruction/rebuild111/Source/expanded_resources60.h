/* Source resource checks; one preflight aggregates materials and ammunition.
 * Skill SP and fixed HP costs are charged by the shared casting pipeline. */
#ifndef MYRO_EXPANDED_RESOURCES60_H
#define MYRO_EXPANDED_RESOURCES60_H
#include "expanded_requirements60.h"
static int expanded_resources60(Combat*g,unsigned id,int rank,int consume){
 const ClassSkill50*d=class_skill_data50(id);const ExpandedRequirement60*r=expanded_requirement60(id);if(!d||!r||rank<1||rank>d->maxRank)return 0;unsigned k=(unsigned)rank-1,w=inventory_wtype46(g);
 if(r->weapons&&(w>=32||!(r->weapons&(1u<<w)))){combat_notice(g,POP_SKILLS,"Equip the weapon required by %s; resources kept.",d->name);return 0;}
 if((r->state==1&&g->hideLeft<=0)||(r->state==2&&(g->hitStun>0||g->class50.rootUntil>g->time))){combat_notice(g,POP_SKILLS,"The stance required by %s is not active.",d->name);return 0;}
 unsigned coins=r->coins[k];if(id==SK60_GS_FLING&&g->expandedCoins60&&coins>g->expandedCoins60)coins=g->expandedCoins60;
 if(coins>g->expandedCoins60||r->zeny[k]>(unsigned)g->zeny){combat_notice(g,POP_SKILLS,"Not enough coins or Zeny; resources kept.");return 0;}
 int64_t hp=r->hpRate<0?(int64_t)g->hp*(-r->hpRate)/100:(int64_t)g->maxhp*r->hpRate/100;if(hp>=g->hp){combat_notice(g,POP_SKILLS,"Not enough HP; resources kept.");return 0;}
 unsigned sources[5]={0},amounts[5]={0},count=0;const AmmoRule60*ammo=NULL;
 if(r->ammo&&r->ammoCount[k]){unsigned mask=r->ammo,weaponMask=ammo_weapon_mask60(w);if(id>=SK60_GS_GLITTERING&&id<=SK60_GS_GROUNDDRIFT){if(w<17||w>21){combat_notice(g,POP_SKILLS,"Equip a gun before using this skill.");return 0;}mask&=weaponMask;}ammo=ammo_current60(g,mask);if(!ammo){combat_notice(g,POP_ITEMS,"Compatible ammunition is missing; resources kept.");return 0;}sources[count]=ammo->source;amounts[count++]=r->ammoCount[k];}
 for(unsigned i=0;i<r->count;i++){unsigned source=r->items[i].source,amount=r->items[i].amount[k];if(!amount)continue;unsigned j=0;while(j<count&&sources[j]!=source)j++;if(j==count){if(count>=5)return 0;sources[count]=source;amounts[count++]=0;}if(amount>INT_MAX-amounts[j])return 0;amounts[j]+=amount;}
 for(unsigned j=0;j<count;j++){uint64_t available=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(p->sourceID==sources[j]&&!p->equipped)available+=p->quantity;}if(available<amounts[j]){int item=inventory_catalog52(sources[j]);combat_notice(g,POP_ITEMS,"Need %s; resources kept.",item>=0?itemDefs[item].name:"the required material");return 0;}}
 if(!consume)return 1;
 for(unsigned j=0;j<count;j++)if(!inventory_consume_source60(g,sources[j],amounts[j]))return 0;
 g->zeny-=(int)r->zeny[k];g->hp-=(int)hp;g->class50.flingSpent60=coins;g->expandedCoins60-=coins;if(coins)memmove(g->class50.coinUntil60,g->class50.coinUntil60+coins,g->expandedCoins60*sizeof(float));g->ammoShot60=ammo!=NULL;if(ammo){g->lastAmmoAttack60=ammo->attack;g->lastAmmoElement60=ammo->element;}return 1;
}
#endif
