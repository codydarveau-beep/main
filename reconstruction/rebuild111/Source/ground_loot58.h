#ifndef MYRO_GROUND_LOOT58_H
#define MYRO_GROUND_LOOT58_H
static int ground_cell60(float x,float y,float xx,float yy){return(int)floorf(x/8)==(int)floorf(xx/8)&&(int)floorf(y/8)==(int)floorf(yy/8);}
static int ground_live58(const Combat*g,int i){return i>=0&&(unsigned)i<groundUsed58&&groundItems58[i].count&&groundItems58[i].map==g->mapId&&g->time-groundItems58[i].createdAt60<60;}
static void ground_expire60(Combat*g){for(unsigned i=0;i<groundUsed58;i++)if(groundItems58[i].count&&(groundItems58[i].map!=g->mapId||g->time-groundItems58[i].createdAt60>=60))memset(groundItems58+i,0,sizeof(*groundItems58));while(groundUsed58&&!groundItems58[groundUsed58-1].count)groundUsed58--;if(!ground_live58(g,g->floorTarget58))g->floorTarget58=-1;if(!ground_live58(g,g->floorPickup58))g->floorPickup58=-1;}
static void ground_map60(Combat*g,unsigned map){for(unsigned i=0;i<groundUsed58;i++)if(groundItems58[i].count&&groundItems58[i].map!=map){ground_clear58();break;}g->floorTarget58=g->floorPickup58=-1;g->floorGather60=0;g->floorScan60=0;}
static int ground_flash60(const Combat*g,const GroundItem58*p){float age=g->time-p->createdAt60;return age>=50&&age<60&&age-floorf(age)<.1f;}
static int ground_add_quantity64(Combat*g,unsigned source,float x,float y,unsigned amount){
 if(!amount||amount>1000000000u||inventory_catalog52(source)<0||!isfinite(x)||!isfinite(y))return 0;ground_expire60(g);int freeSlot=-1;
 for(unsigned i=0;i<groundUsed58;i++){GroundItem58*p=groundItems58+i;if(!p->count){if(freeSlot<0)freeSlot=(int)i;continue;}/* Merge one drop event only, never refresh older loot's lifetime. */
  if(p->source==source&&p->map==g->mapId&&ground_cell60(x,y,p->x,p->y)&&g->time-p->createdAt60<.1f&&p->count<=1000000000u-amount){p->count+=amount;return 1;}}
 if(freeSlot<0&&groundUsed58<GROUND_ITEMS58)freeSlot=(int)groundUsed58++;if(freeSlot<0){combat_notice(g,POP_SYSTEM,"Ground item limit reached. Pick up existing loot before fighting.");return 0;}
 groundItems58[freeSlot]=(GroundItem58){source,amount,g->mapId,++groundLife58,x,y,g->time,0};return 1;
}
static int ground_add58(Combat*g,unsigned source,float x,float y){return ground_add_quantity64(g,source,x,y,1);}
static int ground_loot58(Combat*g,unsigned source,float x,float y,int*floor){*floor=0;if(!autoLootOff58&&inventory_drop52(g,source))return 1;*floor=1;return ground_add58(g,source,x,y);}
static int ground_transfer61(Combat*g,int index){GroundItem58*p=groundItems58+index;int item=inventory_catalog52(p->source);const OwnedRule52*r=item_rule52(p->source);unsigned taken=0;if(item<0)return 0;if(r&&owned_gear52(r)){while(taken<p->count&&inventory_drop52(g,p->source))taken++;}else{unsigned lo=0,hi=p->count;while(lo<hi){unsigned mid=lo+(hi-lo+1)/2;if(inventory_can_add(g,item,(int)mid))lo=mid;else hi=mid-1;}if(lo&&inventory_add(g,item,(int)lo))taken=lo;}if(!taken){p->skipUntil60=g->time+3;combat_notice(g,POP_ITEMS,"Cannot carry %s. It stays on the ground.",itemDefs[item].name);return 0;}p->count-=taken;combat_notice(g,POP_ITEMS,"Picked up %u %s%s",taken,itemDefs[item].name,p->count?"; some remain on the ground.":".");if(p->count)p->skipUntil60=g->time+3;if(!p->count&&g->floorTarget58==index)g->floorTarget58=-1;return 1;}
static int ground_take58(Combat*g,int index){if(!ground_live58(g,index)||g->hp<=0)return 0;GroundItem58*p=groundItems58+index;if(combat_dist(g->x,g->y,p->x,p->y)>12||!player_route_clear53(g,g->x,g->y,p->x,p->y))return 0;return ground_transfer61(g,index);}
static int ground_scoop60(Combat*g,int index){if(!ground_live58(g,index)||g->hp<=0)return 0;float x=groundItems58[index].x,y=groundItems58[index].y;if(combat_dist(g->x,g->y,x,y)>12||!player_route_clear53(g,g->x,g->y,x,y))return 0;int taken=0;for(unsigned i=0;i<groundUsed58;i++)if(ground_live58(g,(int)i)&&ground_cell60(x,y,groundItems58[i].x,groundItems58[i].y))taken+=ground_transfer61(g,(int)i);return taken;}
static int ground_nearest60(const Combat*g){int best=-1;float distance=192*192+.01f;for(unsigned i=0;i<groundUsed58;i++){const GroundItem58*p=groundItems58+i;if(!ground_live58(g,(int)i)||p->skipUntil60>g->time)continue;int item=inventory_catalog52(p->source);if(item<0||!inventory_can_add(g,item,1))continue;float dx=p->x-g->x,dy=p->y-g->y,d=dx*dx+dy*dy;if(d<=192*192&&d<distance){distance=d;best=(int)i;}}return best;}
static int ground_activate58(Combat*g){
 if(!ground_live58(g,g->floorTarget58))return 0;g->autoAttack=0;g->approachSkill53=0;
 if(g->hp<=0||g->sitting||combat_casting(g)){combat_notice(g,POP_ITEMS,"Stand and finish casting before picking up loot.");return 1;}
 GroundItem58*p=groundItems58+g->floorTarget58;if(combat_dist(g->x,g->y,p->x,p->y)>192){combat_notice(g,POP_ITEMS,"That item is outside24cells.");return 1;}
 g->floorGather60=g->autoAttackToggle52;g->floorPickup58=g->floorTarget58;g->route53.state=0;g->floorScan60=0;return 1;
}
static int ground_pickup_tick58(Combat*g,float dt){
 if(g->hp<=0||g->sitting){g->floorGather60=0;g->floorPickup58=-1;return 0;}
 if(g->time-g->attackAt<COMBAT_ATTACK_ANIMATION53||g->time-g->lastCast<.45f||g->moveLock45>0||g->class50.rootUntil>g->time||g->hitStun>0||combat_casting(g))return 0;
 int id=g->floorPickup58;if(!ground_live58(g,id)){g->floorPickup58=-1;if(!g->floorGather60||g->time<g->floorScan60)return 0;g->floorScan60=g->time+.2f;id=ground_nearest60(g);if(id<0)return 0;g->floorTarget58=g->floorPickup58=id;g->route53.state=0;}
 GroundItem58*p=groundItems58+id;
 if(combat_dist(g->x,g->y,p->x,p->y)<=12&&player_route_clear53(g,g->x,g->y,p->x,p->y)){ground_scoop60(g,id);g->floorPickup58=-1;g->route53.state=0;g->floorScan60=0;if(!g->autoAttackToggle52)g->autoAttack=0;return 0;}
 if(combat_dist(g->x,g->y,p->x,p->y)>192){g->floorPickup58=-1;return 0;}
 int moved=player_route_position58(g,-id-1,p->life,p->x,p->y,12,0,dt);if(g->route53.state==3){p->skipUntil60=g->time+3;g->floorPickup58=-1;combat_notice(g,POP_ITEMS,"Cannot reach that item. It stays on the ground.");}return moved==1;
}
#endif
