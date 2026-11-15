/* MIT. Resource conservation, production and persistent intrinsic companions. */
#define main preceding_class_tests50
#include "test_classes48.c"
#undef main
static void ready_solo50(Combat*g){g->castDelay=g->hitStun=0;memset(g->skillCD,0,sizeof(g->skillCD));g->sp=g->maxsp;}
static void empty_bag50(Combat*g){memset(g->extraItems,0,sizeof(g->extraItems));g->apples=g->jellopy=g->clover=0;memset(g->equipped46,0,sizeof(g->equipped46));g->equipment=0;}
static void save_solo50(Combat*g){SavedCharacter a,b;unsigned char raw[SAVE_BYTES];save_capture(&a,g,123);assert(save_valid(&a));save_encode(raw,&a);assert(save_decode(&b,raw)==1);assert(!memcmp(&a.persistent50,&b.persistent50,sizeof(a.persistent50)));}
int main(void){Combat g;unsigned recipes=0;
 for(unsigned n=0;n<sizeof(recipes50)/sizeof(*recipes50);n++){
  const Recipe50*r=&recipes50[n];prepare48(&g,r->skill==239?20:19);empty_bag50(&g);memset(g.stats,99,6);stat_refresh(&g);ready_solo50(&g);
  g.utilityMenu=r->skill==239?239:600;g.class50.craftTool=r->level==21?612:612+r->level;
  int tool=item_source50(g.utilityMenu==239?7134:g.class50.craftTool);assert(tool>=0);*inventory_stack(&g,tool)=1;
  for(int i=0;i<r->count;i++)*inventory_stack(&g,r->materials[i][0])=r->materials[i][1]?r->materials[i][1]:1;
  int choice=-1;for(int row=0;row<class_craft_rows50(&g);row++)if(class_recipe50(&g,row)==r)choice=row;assert(choice>=0);
  int missing=r->materials[0][0],before=inventory_count(&g,missing),sp=g.sp;*inventory_stack(&g,missing)=0;uint32_t rng=g.rng;
  assert(!skill_utility_commit(&g,choice)&&inventory_count(&g,tool)==1&&g.sp==sp&&g.rng==rng);*inventory_stack(&g,missing)=before;
  if(!skill_utility_commit(&g,choice)){fprintf(stderr,"recipe %u %s failed: %s weight%lld/%d\n",n,itemDefs[r->product].name,g.log,(long long)inventory_weight(&g),inventory_weight_max(&g));abort();}
  assert(!inventory_count(&g,tool)&&g.sp==sp-(r->skill==239?5:0));
  for(int i=0;i<r->count;i++)if(!r->materials[i][1])assert(inventory_count(&g,r->materials[i][0])==1);
  recipes++;
 }
 prepare48(&g,19);ready_solo50(&g);assert(cast48(&g,231)&&class_active50(&g,231));assert(cast48(&g,232)&&class_active50(&g,232));assert(cast48(&g,233)&&class_active50(&g,233));
 ready_solo50(&g);assert(cast48(&g,234)&&class_active50(&g,234));g.sp=100;g.time=g.class50.next[234-127];class_tick50(&g,0);assert(g.sp==99);ready_solo50(&g);assert(cast48(&g,234)&&!class_active50(&g,234));
 int weapon=inventory_slot46(&g,0);g.brokenWeapon48=weapon+1;inventory_remove46(&g,0);int repair=class_repair_material50(&g);assert(repair>=0);*inventory_stack(&g,repair)=1;ready_solo50(&g);assert(cast48(&g,228)&&!g.brokenWeapon48&&!inventory_count(&g,repair));
 prepare48(&g,20);CombatMob*m=&g.mobs[MOB_COUNT-1];int hp=m->hp;assert(cast48(&g,241)&&m->hp<hp);ready_solo50(&g);g.hp=1;g.useRanks45[242-3]=1;assert(cast48(&g,242)&&g.hp>1);
 ready_solo50(&g);assert(cast48(&g,245)&&class_active50(&g,245));ready_solo50(&g);assert(cast48(&g,240));g.time+=1;class_tick50(&g,0);assert(g.areas50[0].id==240);
 ready_solo50(&g);assert(cast48(&g,243));assert(g.summons50[0].hp>0&&g.summons50[0].kind==4);ready_solo50(&g);g.useRanks45[243-3]=1;int sp=g.sp;assert(!skill_cast(&g,243,g.x+16,g.y)&&g.sp==sp);
 prepare48(&g,20);int embryo=item_source50(7142),count=inventory_count(&g,embryo);assert(cast48(&g,250)&&g.persistent50.homunType>=6001&&g.persistent50.homunType<=6008&&inventory_count(&g,embryo)==count-1);save_solo50(&g);
 ClassPersistent50*p=&g.persistent50;p->homunHP=homun_maxhp50(p);ready_solo50(&g);assert(cast48(&g,251)&&p->homunResting);ready_solo50(&g);count=inventory_count(&g,embryo);assert(cast48(&g,250)&&!p->homunResting&&inventory_count(&g,embryo)==count);
 p->homunHP=0;ready_solo50(&g);assert(cast48(&g,252)&&p->homunHP==homun_maxhp50(p));
 int food=item_source50(homunData50[p->homunType-6001].food);*inventory_stack(&g,food)=3;p->homunHunger=20;unsigned intimacy=p->homunIntimacy;assert(homun_feed50(&g)&&p->homunHunger==30&&p->homunIntimacy==intimacy+100);
 p->homunHunger=95;intimacy=p->homunIntimacy;assert(homun_feed50(&g)&&p->homunIntimacy==intimacy-50&&p->homunHunger==100);
 homun_gain50(&g,homunEXP50[0]+homunEXP50[1]+2);assert(p->homunLevel==3&&p->homunPoints==1);assert(homun_learn50(&g,0)&&!p->homunPoints);save_solo50(&g);
 *inventory_stack(&g,item_source50(12040))=1;p->homunIntimacy=91000;assert(homun_evolve50(&g)&&p->homunType>=6009&&p->homunIntimacy==500);save_solo50(&g);
 /* Personal AI can be hit; the owner's HP is not charged for its damage. */
 m=&g.mobs[MOB_COUNT-1];m->training=0;m->aggro=m->enabled=1;m->cooldown=0;m->class50.companionTarget=1;m->x=g.class50.homunX;m->y=g.class50.homunY;p->homunHP=homun_maxhp50(p);g.class50.homunAttackAt=g.time+100;
 hp=g.hp;unsigned buddyHP=p->homunHP;for(int n=0;n<100&&p->homunHP==buddyHP;n++){m->cooldown=0;class_mob_companion50(&g,MOB_COUNT-1,.01f);}assert(p->homunHP<buddyHP&&g.hp==hp);
 prepare48(&g,13);m=&g.mobs[MOB_COUNT-1];unsigned originalCount=class_count(&g);g.hp=1000;m->castUntil48=g.time;m->castSkill48=3;m->castRank48=10;m->castSP48=30;class_magic_tick48(&g);
 assert(g.persistent50.copySkill==3&&g.persistent50.copyRank==10&&class_count(&g)==originalCount+1&&class_skill(&g,class_count(&g)-2)==3&&class_skill(&g,class_count(&g)-1)==1);
 assert(skill_choose_rank45(&g,3,-1)==9&&skill_cost(&g,3)==28);g.hotbar[0]=3;g.quickKind=1;g.quickId=3;g.rbBinding=3;save_solo50(&g);ready_solo50(&g);assert(cast48(&g,3));
 printf("PASS50 all %u original production recipes, tool/bowl/guide conservation and failed-attempt atomicity; smith buffs/drain/repair; Alchemist attacks, self pitching, coatings and summon limits; persistent Homunculus creation/rest/call/revival/feed/growth/learning/evolution and independent incoming damage.\n",recipes);
}
