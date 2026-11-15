#include <assert.h>
#include "combat.h"
static int open(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>0&&ny>0&&nx<3200&&ny<3200;}
static void fixture(Combat*g,int kind){combat_init(g,1000,1000,open,NULL);memset(g->mobs,0,sizeof(g->mobs));CombatMob*m=&g->mobs[0];m->enabled=1;m->spawnDef=-1;m->kind=kind;m->hp=mobSpecs[kind].hp;m->x=m->homeX=1012;m->y=m->homeY=1000;m->faceY=1;m->attackAt=m->hurtAt=m->deadAt=-100;m->wanderAt=1000;g->target=0;}
int main(void){Combat g;
 for(int k=0;k<MOB_SPEC_COUNT;k++){
  fixture(&g,k);CombatMob*m=&g.mobs[0];float x=m->x,y=m->y;int hp=g.hp;
  if(!(mobSpecs[k].flags&1)){m->aggro=1;for(int j=0;j<100;j++)combat_tick(&g,.05f,0,0);assert(m->x==x&&m->y==y&&g.hp==hp);}
  fixture(&g,k);m=&g.mobs[0];int old=m->hp;skill_hit(&g,0,10000,0);
  if(mobSpecs[k].flags&16)assert(m->hp==old-1);else{assert(m->hp==0&&g.kills==1);assert(g.soundWrite==1&&g.soundEvents[0]==(unsigned)(k+2));}
 }
 fixture(&g,10);combat_tick(&g,.05f,0,0);assert(g.mobs[0].aggro); // Vocal aggression.
 fixture(&g,0);combat_tick(&g,.05f,0,0);assert(!g.mobs[0].aggro);skill_hit(&g,0,1,0);assert(g.mobs[0].aggro); // Poring retaliation.
 fixture(&g,5);g.mobs[1]=g.mobs[0];g.mobs[1].x+=12;g.mobs[1].aggro=1;combat_tick(&g,.05f,0,0);assert(g.mobs[0].aggro); // Assist.
 fixture(&g,0);g.mobs[0].hp=1;g.autoAttack=1;combat_tick(&g,.05f,0,0);assert(g.soundWrite==2&&g.soundEvents[0]==0&&g.soundEvents[1]==2);
 for(int i=0;i<100;i++)combat_sound(&g,0);assert(g.soundWrite-g.soundRead==32);
 fixture(&g,10);g.mobs[0].spawnDef=17; // Explicitly choose the actual Vocal spawn below.
 for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].kind==10)g.mobs[0].spawnDef=j;
 skill_hit(&g,0,10000,0);combat_tick(&g,.05f,0,0);assert(g.mobs[0].respawnAt>=1800&&g.mobs[0].respawnAt<=3000);
 puts("PASS stationary eggs/plants, plant one-damage rule, Vocal aggression, retaliation, assist, attack/death event order, queue bound and source mini-boss respawn interval");
}
