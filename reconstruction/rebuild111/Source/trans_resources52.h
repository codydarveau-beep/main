/* MIT. Preflight source resources before any inventory mutation. */
#include "trans_req_data52.h"
static int trans_resources52(Combat*g,unsigned id,int rank,int consume){
 const ClassSkill50*d=class_skill_data50(id);const TransRequirement52*r=trans_requirement52(id);if(!d||!r||rank<1||rank>d->maxRank)return 0;
 unsigned type=inventory_wtype46(g);if(r->weapons&&(type>=32||!(r->weapons&(1u<<type)))){combat_notice(g,POP_SKILLS,"Equip the weapon required by %s.",d->name);return 0;}
 int state=r->state,left=inventory_slot46(g,3);
 if((state==1&&!g->mounted48)||(state==2&&!g->cartOwned)||(state==3&&(!g->cartOwned||!class_active50(g,SK52_WS_CARTBOOST)))||(state==4&&!class_active50(g,209))||(state==5&&!g->persistent50.falcon)||(state==6&&(left<0||itemDefs[left].slot!=3))){combat_notice(g,POP_SKILLS,"The required equipment or active state is missing.");return 0;}
 int spheres=d->spheres[rank-1];if(spheres>g->class50.spheres||g->zeny<(int)r->zeny[rank-1]){combat_notice(g,POP_SKILLS,"Not enough Spirit Spheres or Zeny; resources kept.");return 0;}
 int item[8];for(unsigned i=0;i<r->count;i++){item[i]=-1;if(!inventory_gem_cost52(g,id,r->items[i].source,r->items[i].amount[rank-1]))continue;item[i]=item_source50(r->items[i].source);if(item[i]<0||inventory_count(g,item[i])<(int)inventory_gem_cost52(g,id,r->items[i].source,r->items[i].amount[rank-1])){combat_notice(g,POP_SKILLS,"Required skill material is missing; resources kept.");return 0;}}
 int ammo=r->ammo?item_source50(1750):-1;if(r->ammo&&(ammo<0||inventory_count(g,ammo)<r->ammoCount)){combat_notice(g,POP_SKILLS,"Required arrows are missing; resources kept.");return 0;}
 if(!consume)return 1;g->zeny-=r->zeny[rank-1];
 for(int i=spheres;i<g->class50.spheres;i++)g->class50.sphereUntil[i-spheres]=g->class50.sphereUntil[i];g->class50.spheres-=spheres;
 for(unsigned i=0;i<r->count;i++)if(inventory_gem_cost52(g,id,r->items[i].source,r->items[i].amount[rank-1]))*inventory_stack(g,item[i])-=inventory_gem_cost52(g,id,r->items[i].source,r->items[i].amount[rank-1]);if(r->ammo)*inventory_stack(g,ammo)-=r->ammoCount;return 1;
}
