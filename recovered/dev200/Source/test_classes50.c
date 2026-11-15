/* MIT. Real controller skill entry points, class ownership and stable persistence. */
#define main previous_class48_tests
#include "test_classes48.c"
#undef main
#include "shop.h"
#include "actor_data.h"
static void wait_class50(Combat*g,int ticks){for(int i=0;i<ticks;i++)combat_tick(g,.01f,0,0);}
static void ready_class50(Combat*g){g->sp=g->maxsp;g->castDelay=g->hitStun=0;memset(g->skillCD,0,sizeof(g->skillCD));}
int main(void){Combat g,h;
 const int weapons[]={16,1,10,14,15,9,13,6,6};
 for(int job=12;job<=20;job++){
  prepare48(&g,job);assert(g.jobId==(unsigned)job&&g.level==99&&g.joblevel==50&&g.skillPoints==0);
  assert(inventory_wtype46(&g)==weapons[job-12]);assert(class_actor_id50(job,0)==(unsigned)job+1);
  assert(g.maxhp>0&&g.maxsp>0&&g.statPoints>=0);
  SavedCharacter a,b;unsigned char bytes[SAVE_BYTES];save_capture(&a,&g,10+job);if(!save_valid(&a)){fprintf(stderr,"invalid preset %s\n",job_name(job));abort();}save_encode(bytes,&a);assert(save_decode(&b,bytes)==1);save_restore(&h,&b,1500,1500,NULL,NULL);
  assert(h.jobId==g.jobId&&!memcmp(h.ranks,g.ranks,LEARN_COUNT)&&inventory_wtype46(&h)==weapons[job-12]);
 }
 prepare48(&g,12);CombatMob*m=&g.mobs[MOB_COUNT-1];int hp=m->hp,sp=g.sp;
 assert(skill_cast(&g,131,m->x,m->y)&&g.sp==sp-34);assert(m->hp<hp);wait_class50(&g,160);assert(g.damageNext>=8&&!g.bursts49[0].active);
 ready_class50(&g);inventory_remove46(&g,0);inventory_add(&g,ITEM_KNIFE,1);inventory_action(&g,ITEM_KNIFE);assert(inventory_wtype46(&g)==1);sp=g.sp;assert(!skill_cast(&g,131,m->x,m->y)&&g.sp==sp);
 prepare48(&g,12);m=&g.mobs[MOB_COUNT-1];int knife=item_source50(1771),knives=inventory_count(&g,knife);assert(skill_cast(&g,138,m->x,m->y)&&inventory_count(&g,knife)==knives-1);
 prepare48(&g,13);m=&g.mobs[MOB_COUNT-1];m->faceX=1;m->faceY=0;hp=m->hp;assert(skill_cast(&g,142,m->x,m->y)&&m->hp<hp&&m->faceX<0);ready_class50(&g);sp=g.sp;assert(!skill_cast(&g,142,m->x,m->y)&&g.sp==sp);
 prepare48(&g,13);g.hideLeft=100;g.hideRank=10;assert(skill_cast(&g,144,g.x,g.y)&&!g.hideLeft);
 prepare48(&g,14);m=&g.mobs[MOB_COUNT-1];int traps=item_source50(1065),before=inventory_count(&g,traps);assert(skill_cast(&g,156,g.x+24,g.y)&&inventory_count(&g,traps)==before-1);
 m->x=g.x+24;wait_class50(&g,20);assert(m->class50.rootUntil>g.time&&g.traps50[0].triggered);
 prepare48(&g,14);m=&g.mobs[MOB_COUNT-1];hp=m->hp;assert(cast48(&g,167));wait_class50(&g,100);assert(m->hp<hp&&g.damageNext>=5);
 prepare48(&g,17);m=&g.mobs[MOB_COUNT-1];assert(cast48(&g,196)&&m->class50.lexUntil>g.time);hp=m->hp;g.fxSkill=3;skill_hit_ex(&g,MOB_COUNT-1,800,0,8);wait_class50(&g,150);assert(m->hp==hp-1600&&!m->class50.lexUntil);
 prepare48(&g,17);assert(cast48(&g,7)&&g.shieldHP==g.maxhp*30/100&&g.shieldHits==10&&g.buffs[2]==120);
 prepare48(&g,18);for(int i=0;i<5;i++){ready_class50(&g);assert(cast48(&g,200));}assert(g.class50.spheres==5);
 ready_class50(&g);assert(cast48(&g,209)&&!g.class50.spheres&&class_active50(&g,209));for(int i=0;i<5;i++){ready_class50(&g);assert(cast48(&g,200));}
 ready_class50(&g);m=&g.mobs[MOB_COUNT-1];hp=m->hp;assert(cast48(&g,210)&&m->hp<hp&&g.sp==0&&!g.class50.spheres&&class_active50(&g,210)&&!class_active50(&g,209));wait_class50(&g,800);assert(!g.sp);
 prepare48(&g,18);int triple=0;for(int n=0;n<100&&!triple;n++)triple=class_triple50(&g,MOB_COUNT-1);assert(triple&&g.class50.comboSkill==202&&g.class50.comboUntil>g.time);
 ready_class50(&g);assert(skill_cast(&g,211,g.x,g.y)&&g.class50.comboSkill==211);g.class50.spheres=1;g.class50.sphereUntil[0]=g.time+60;ready_class50(&g);assert(skill_cast(&g,212,g.x,g.y)&&g.class50.comboSkill==212&&!g.class50.spheres);
 prepare48(&g,15);m=&g.mobs[MOB_COUNT-1];hp=m->hp;assert(skill_cast(&g,174,g.x,g.y));wait_class50(&g,1);assert(g.class50.song==174&&m->hp==hp-110);
 ready_class50(&g);sp=g.sp;assert(!skill_cast(&g,176,g.x,g.y)&&g.sp==sp);wait_class50(&g,510);ready_class50(&g);assert(skill_cast(&g,176,g.x,g.y)&&!g.class50.song);ready_class50(&g);sp=g.sp;assert(skill_cast(&g,177,g.x,g.y)&&g.class50.song==174&&g.sp==sp-16);
 prepare48(&g,16);m=&g.mobs[MOB_COUNT-1];int arrows=inventory_count(&g,ITEM_ARROW);assert(cast48(&g,180)&&inventory_count(&g,ITEM_ARROW)==arrows-1);
 printf("PASS50 nine presets/source parents and weapons, Save50 class round trips, original eight-hit Sonic/5-hit Falcon, weapon/ammo gates, Backstab/Raid, trap rooting, full-packet Lex, Priest Kyrie, Monk spheres/combos/Asura/SP penalty, songs/Amp/Encore and Dancer ammunition. Combat=%u bytes.\n",(unsigned)sizeof(Combat));
}
