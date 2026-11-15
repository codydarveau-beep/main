/* MIT. Exercise new real skill entry points, resource gates and source-derived class state. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "save_format.h"
#include "travel_status45.h"
static int clear48(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
static void prepare48(Combat*g,int job){combat_init(g,1500,1500,clear48,0);dev_class_preset(g,job);memset(g->mobs,0,sizeof(g->mobs));assert(dev_spawn(g,0,3));CombatMob*m=&g->mobs[MOB_COUNT-1];m->x=g->x+6;m->y=g->y;m->testMaxHP=m->hp=1000000;g->target=MOB_COUNT-1;g->time=1;g->hitStun=0;}
static int cast48(Combat*g,int id){int ok=skill_cast(g,id,g->x+16,g->y);if(!ok)return 0;for(int n=0;combat_casting(g)&&n<2000;n++)combat_tick(g,.01f,0,0);assert(!combat_casting(g));return 1;}
int main(void){Combat g;int tested=0;
 for(int id=89;id<127;id++){int job=id==89?9:id<112?10:11;prepare48(&g,job);if(skill_passive(id)||id==91||id==106||id==122||id==123)continue;if(id==93){g.mobs[MOB_COUNT-1].castUntil48=100;g.mobs[MOB_COUNT-1].castSkill48=3;g.mobs[MOB_COUNT-1].castRank48=10;}if(id==125){int spear=-1;for(int i=0;i<ITEM_COUNT;i++)if(itemDefs[i].id==1451)spear=i;assert(spear>=0);inventory_add(&g,spear,1);inventory_action(&g,spear);assert(inventory_wtype46(&g)==5);}int sp=g.sp,cost=skill_cost(&g,id);if(!cast48(&g,id)){fprintf(stderr,"new skill %d failed: %s\n",id,g.log);abort();}if(id==95){assert(g.utilityMenu==95&&skill_utility_rows(&g)==7);assert(skill_utility_commit(&g,1));assert(class_active48(&g,95));}else if(id==107){assert(g.utilityMenu==107&&g.sp==sp);int material=class_item48(7006),before=inventory_count(&g,material);assert(skill_utility_commit(&g,0));assert(inventory_count(&g,material)==before-3);assert(g.sp==sp-30);}else if(id!=93)assert(g.sp<=sp-cost);if(id==117||id==118||id==120)assert(g.mobs[MOB_COUNT-1].hp<1000000);if(id>=108&&id<=111)assert(g.mobs[MOB_COUNT-1].element48==id-107);if(id==89){assert(class_ice_block48(&g,g.x+16,g.y));float x=g.x,y=g.y;assert(!combat_move(&g,&x,&y,g.x+16,g.y));}tested++;}
 prepare48(&g,10);int before=g.sp;assert(skill_cast(&g,3,g.x,g.y));assert(combat_casting(&g));assert(skill_cast(&g,91,g.x,g.y));assert(!combat_casting(&g)&&g.sp<before);before=g.sp;assert(!skill_cast(&g,91,g.x,g.y)&&g.sp==before);
 prepare48(&g,10);assert(skill_cast(&g,3,g.x,g.y));float x=g.x;for(int i=0;i<25;i++)combat_tick(&g,.01f,1,0);assert(g.x>x&&combat_casting(&g));
 prepare48(&g,11);assert(!job_owns_skill48(11,11,122)&&!job_owns_skill48(11,11,123));assert(class_rank48(&g,115)==10);int hp=g.maxhp;g.ranks[115-3]=0;assert(hp-stat_maxhp(&g)==2000);
 prepare48(&g,11);assert(cast48(&g,116));TravelStatus45 status=travel_capture45(&g);g.time=100;memset(g.classUntil48,0,sizeof(g.classUntil48));travel_restore45(&g,&status);assert(class_active48(&g,116)==10&&g.classUntil48[116-89]>100);
 prepare48(&g,10);g.useRanks45[126-3]=0;SavedCharacter a,b;save_capture(&a,&g,1);assert(save_valid(&a));unsigned char bytes[SAVE_BYTES];save_encode(bytes,&a);assert(save_decode(&b,bytes)==1);assert(!memcmp(a.ranks,b.ranks,LEARN_COUNT)&&!memcmp(a.useRanks45,b.useRanks45,LEARN_COUNT));bytes[SAVE_RANKS50]^=1;assert(!save_decode(&b,bytes));
 printf("PASS48 %d new active skill paths; class ownership, personal buff zoning, Free Cast, Cast Cancel, source Faith, reagents/crafting, shields, Ice Wall collision and expanded save integrity.\n",tested);
}
