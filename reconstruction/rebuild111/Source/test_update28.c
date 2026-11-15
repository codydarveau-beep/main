/* MIT. Gameplay and actual menu input regressions for Test28. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
#include "window_ui.h"
#include "pause_ui.h"
#include "input_repeat.h"
static void ready(Combat*g){g->sp=g->maxsp;g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));}
static void mob(Combat*g,int kind){memset(g->mobs,0,sizeof(g->mobs));CombatMob*m=&g->mobs[0];m->kind=kind;m->enabled=1;m->hp=100000;m->x=m->homeX=g->x+30;m->y=m->homeY=g->y;m->spawnDef=-1;g->target=0;}
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);float x=g.x;combat_tick(&g,.05f,1,0);assert(fabsf(g.x-x-81.9f*.05f)<.001f);
 for(unsigned job=1;job<=6;job++){dev_class_preset(&g,job);assert(g.jobId==job&&g.level==20&&g.joblevel==50&&g.skillPoints==0&&g.statPoints>=0);for(int i=0;i<LEARN_COUNT;i++)assert(g.ranks[i]==(learnJobs[i]==job?learnMax[i]:0));SavedCharacter s;save_capture(&s,&g,1);assert(save_valid(&s));unsigned char bytes[SAVE_BYTES];save_encode(bytes,&s);assert(save_decode(&s,bytes)==1);}
 dev_class_preset(&g,3);assert(skill_passive(42)&&skill_cost(&g,41)==33&&skill_cost(&g,43)==35);g.debugFreeze=1;mob(&g,0);int tries=0;do{ready(&g);assert(skill_cast(&g,41,0,0));}while(!g.mobs[0].slowLeft&&++tries<100);assert(g.mobs[0].slowLeft==130&&g.mobs[0].hp==100000);g.mobs[0].slowLeft=.01f;combat_tick(&g,.05f,0,0);assert(g.mobs[0].slowLeft==0);
 int boss=-1,demon=-1;for(int k=0;k<MOB_SPEC_COUNT;k++){if(mobUtility[k].blocked)boss=k;if(mobSignumTarget[k])demon=k;}mob(&g,0);g.mobs[0].training=1;g.mobs[0].testTraits=3;ready(&g);int sp=g.sp;assert(!skill_cast(&g,41,0,0)&&g.sp==sp);
 demon=5;mob(&g,demon);g.mobs[0].training=1;g.mobs[0].testTraits=1;tries=0;do{ready(&g);assert(skill_cast(&g,43,0,0));}while(!g.mobs[0].crucisRank&&++tries<100);assert(g.mobs[0].crucisRank==10);int def=mobSpecs[demon].defense;assert(combat_enemy_defense(&g.mobs[0])==def-def/2);mob(&g,0);ready(&g);assert(skill_cast(&g,43,0,0)&&!g.mobs[0].crucisRank);
 dev_class_preset(&g,3);mob(&g,5);g.mobs[0].x=g.x+8;g.mobs[0].training=1;g.mobs[0].testTraits=1;g.debugFreeze=1;g.cooldown=0;Combat h=g;g.ranks[38]=0;g.autoAttack=h.autoAttack=1;combat_tick(&g,.05f,0,0);combat_tick(&h,.05f,0,0);assert(g.mobs[0].hp-h.mobs[0].hp==40);
 WindowUI u={0};ui_open(&u,3,1);u.skillPage=1;u.choice[3]=0;g.hotSlot=0;ui_input(&u,&g,2);assert(u.placing&&u.dropSlot==0);ui_input(&u,&g,8192);ui_input(&u,&g,2);assert(!u.placing&&u.dropSlot==1);ui_input(&u,&g,2);assert(u.placing&&u.dropSlot==1);ui_close(&u,3);assert(!u.active&&!u.open);ui_tick(&u,&g,.05f);assert(!u.dropRemember);ui_open(&u,3,1);ui_input(&u,&g,2);assert(u.dropSlot==0);
 PauseUI p={.tab=0,.row=2};assert(pause_count(0)==3&&pause_input(&p,2)==PA_RESUME);p.tab=3;p.row=1;assert(pause_input(&p,2)==PA_TRAVEL);
 InputRepeat r={0};assert(!input_repeat(&r,2048,15360,1,.05f));int count=0;for(int i=0;i<50;i++)count+=!!input_repeat(&r,2048,15360,1,.05f);assert(count>20);assert(!input_repeat(&r,2048,15360,2,.05f));
 puts("PASS six complete class presets/current codec; 9% slower walking; Decrease AGI/resists/expiry; Signum eligibility/DEF; assignment memory/reset; last-window exit; moved travel; held navigation");}
