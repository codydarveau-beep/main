#include <assert.h>
#include <limits.h>
#include "save_store.h"
#include "developer.h"
#include "pause_ui.h"
static int blocked(void*w,float a,float b,float x,float y){return 0;}
static void valid(Combat*g){SavedCharacter s;save_capture(&s,g,1);assert(save_valid(&s));}
int main(void){
 Combat g,h;combat_init(&g,1500,1500,NULL,NULL);DeveloperUI u;dev_open(&u,&g);PauseUI p={3,0};assert(pause_input(&p,2)==PA_DEV);assert(pause_input(&p,512)==PA_NONE&&p.tab==0);
 u.base=20;u.job=10;u.row=2;assert(!dev_input(&u,&g,2)&&u.confirm==1&&g.level==1);dev_input(&u,&g,4);assert(!u.confirm&&g.level==1);dev_input(&u,&g,2);dev_input(&u,&g,2);assert(g.level==20&&g.joblevel==10&&g.skillPoints==0&&g.statPoints==88);valid(&g);
 assert(combat_change_job(&g,4));u.job=20;u.base=1;u.row=2;dev_input(&u,&g,2);dev_input(&u,&g,2);assert(g.skillPoints==19&&g.statPoints==12);g.ranks[8]=10;g.skillPoints=9;g.hotbar[0]=12;g.quickKind=1;g.quickId=12;g.buffs[0]=10;u.row=5;dev_input(&u,&g,2);dev_input(&u,&g,2);assert(g.skillPoints==19&&!g.ranks[8]&&g.hotbar[0]==255&&!g.quickKind&&!g.buffs[0]);valid(&g);
 int kills=g.kills,exp=g.exp;assert(dev_spawn(&g,0,3));CombatMob*m=&g.mobs[MOB_COUNT-1];assert(m->hp==50000&&combat_mob_max(m)==50000);g.target=MOB_COUNT-1;g.autoAttack=1;g.cooldown=0;m->x=g.x+8;m->y=g.y;m->hp=1;combat_tick(&g,.05f,0,0);assert(m->hp==1&&g.kills==kills&&g.exp==exp);g.debugImmortal=0;g.cooldown=0;combat_tick(&g,.05f,0,0);assert(!m->hp&&g.kills==kills&&g.exp==exp);combat_tick(&g,20,0,0);assert(!m->hp);
 assert(dev_spawn(&g,0,0));int oldhp=m->hp;g.canMove=blocked;assert(!dev_spawn(&g,1,0)&&m->hp==oldhp&&m->kind==0);g.canMove=NULL;g.peaceful=1;assert(!dev_spawn(&g,1,0));g.peaceful=0;
 SavedCharacter s;save_capture(&s,&g,1);save_restore(&h,&s,1500,1500,NULL,NULL);assert(!h.mobs[MOB_COUNT-1].enabled&&!h.debugFreeze);
 dev_clear_feedback(&g);g.time=10;combat_hit_sound(&g,2);combat_sound(&g,7);unsigned id;assert(combat_next_sound(&g,&id)&&id==0);assert(combat_next_sound(&g,&id)&&id==7);assert(!combat_next_sound(&g,&id));g.time=10.099f;assert(!combat_next_sound(&g,&id));g.time=10.1f;assert(combat_next_sound(&g,&id)&&id==0);assert(!combat_next_sound(&g,&id));
 g.soundRead=g.soundWrite=UINT_MAX-2;for(int i=0;i<40;i++)combat_sound_at(&g,i,.1f);assert(g.soundWrite-g.soundRead==32);g.time+=.1f;for(int i=0;i<32;i++){assert(combat_next_sound(&g,&id)&&id==(unsigned)i);}assert(!combat_next_sound(&g,&id));
 combat_number(&g,1,1,99,2,0);assert(g.damage[(g.damageNext-1)%DAMAGE_EVENTS].hitGap==.1f);

 dev_remove(&g);assert(!m->enabled&&g.target==-1&&g.soundRead==g.soundWrite&&!g.damageNext);
 puts("PASS Test20 confirmation/cancel, level budgets, skill refunds/bindings, Save10, isolated immortal/killable target, blocked spawn, no rewards/respawn, ordered bounded/wrapping sound queue, 100ms timing");
}
