/* MIT. Regression: real incoming damage and natural Lunatic AI, not just helpers. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
static int clear(void*w,float x,float y,float nx,float ny){return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
static int centerOnly(void*w,float x,float y,float nx,float ny){return !(nx==1500&&ny==1500);}
static void ready(Combat*g){g->sp=g->maxsp;g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));}
static void mage(Combat*g){combat_init(g,1502.9f,1501.1f,clear,NULL);dev_class_preset(g,2);memset(g->mobs,0,sizeof(g->mobs));g->peaceful=0;}
static CombatMob*lunatic(Combat*g){CombatMob*m=&g->mobs[0];memset(m,0,sizeof(*m));m->enabled=m->aggro=1;m->spawnDef=-1;m->kind=1;m->hp=60;m->x=m->homeX=g->x+8;m->y=m->homeY=g->y;m->faceY=1;m->attackAt=m->hurtAt=m->deadAt=-100;g->target=0;return m;}
int main(void){Combat g;mage(&g);CombatMob*m=lunatic(&g);int hp=g.hp;float x=1502.9f,y=1501.1f;skill_ground_snap(48,&x,&y);assert(x==1500&&y==1500);assert(skill_cast(&g,48,1502.9f,1501.1f));assert(g.safety[0].x==x&&g.safety[0].y==y&&combat_safety_at(&g,g.x,g.y)==0);
 // Every interior sub-cell sample is protected; edge/right cell is not.
 for(int ix=0;ix<8;ix++)for(int iy=0;iy<8;iy++)assert(combat_safety_at(&g,1496+ix+.1f,1496+iy+.1f)==0);
 assert(combat_safety_at(&g,1496,1496)==0&&combat_safety_at(&g,1504,1500)<0&&combat_safety_at(&g,1500,1504)<0);
 // Real melee loop: landed attacks consume wall hits without HP loss/stagger/Kyrie.
 g.buffs[2]=60;g.shieldHP=100;g.shieldHits=5;for(int i=0;i<140;i++)combat_tick(&g,.05f,0,0);assert(g.hp==hp&&g.safety[0].hits<11&&g.safety[0].hits>0&&g.shieldHits==5&&g.hitStun<=0);assert(g.safety[0].blockedUntil>0);
 g.x=1505;g.y=1500;m->x=1510;m->y=1500;g.buffs[2]=0;for(int i=0;i<150&&g.hp==hp;i++){m->cooldown=0;combat_tick(&g,.05f,0,0);}assert(g.hp<hp&&combat_safety_at(&g,g.x,g.y)<0&&combat_safety_near(&g)==0);
 // Invalid center is rejected even when raw aim was just outside that center.
 mage(&g);g.canMove=centerOnly;int sp=g.sp,gem=inventory_count(&g,ITEM_BLUE_GEM);assert(!skill_ground_point(&g,48,1502.9f,1501.1f)&&!skill_cast(&g,48,1502.9f,1501.1f)&&g.sp==sp&&inventory_count(&g,ITEM_BLUE_GEM)==gem);
 mage(&g);m=lunatic(&g);int successes=0,failures=0;for(int i=0;i<100;i++){ready(&g);m->stoneWait=m->stoneLeft=0;assert(skill_cast(&g,49,0,0));if(m->stoneWait>0){successes++;assert(!m->stoneNotice);}else{failures++;assert(m->stoneNotice==1&&m->stoneNoticeUntil>g.time);}}assert(successes>20&&failures>20);
 // Full simulation confirms natural Lunatic stops attacking/moving after incubation.
 m->stoneWait=5;m->stoneLeft=0;for(int i=0;i<103;i++)combat_tick(&g,.05f,0,0);assert(m->stoneWait==0&&m->stoneLeft>19&&m->stoneLeft<=20&&!m->moving);float mx=m->x,my=m->y,attack=m->attackAt;for(int i=0;i<100;i++)combat_tick(&g,.05f,0,0);assert(m->x==mx&&m->y==my&&m->attackAt==attack&&!m->moving&&m->stoneLeft>14);
 combat_enemy_damage(&g,m,1);assert(!m->stoneLeft&&m->stoneNotice==3&&m->stoneNoticeUntil>g.time);m->stoneWait=3;ready(&g);assert(skill_cast(&g,49,0,0)&&!m->stoneWait&&!m->stoneLeft&&m->stoneNotice==2);
 SavedCharacter a,b;unsigned char buf[SAVE_BYTES];save_capture(&a,&g,1);assert(save_valid(&a));save_encode(buf,&a);assert(save_decode(&b,buf)==1);
 printf("PASS snapped wall center/footprint, real Lunatic melee blocked inside/damages outside, no shield/stagger consumption, snapped collision guard; Lunatic Stone successes%d/resists%d, actual5s incubation->AI arrest, break/recast notices; Save17 unchanged.\n",successes,failures);
}
