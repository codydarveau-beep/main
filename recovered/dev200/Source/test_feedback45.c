/* MIT. Actual UI rank controls, timing, targeting, settings and roam regressions. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "window_ui.h"
#include "save_store.h"
#include "travel_status45.h"
#include "facing45.h"
#include "sprite_slots45.h"
static int clear45(void*c,float x,float y,float nx,float ny){(void)c;(void)x;(void)y;return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
int main(void){Combat g,h;combat_init(&g,1500,1500,clear45,NULL);assert(g.walkPercent==100&&skill_rank(&g,3)==1);dev_class_preset(&g,8);WindowUI u={.open=8,.active=1,.inside=1,.focus=7,.skillPage=1};for(unsigned k=0;k<class_count(&g);k++)if(class_skill(&g,k)==3)u.choice[3]=k;int index=skill_rank_index(3),learned=g.ranks[index];assert(learned==10);int high=skill_cost(&g,3);for(int i=0;i<15;i++)ui_input(&u,&g,32);assert(skill_rank(&g,3)==1&&g.ranks[index]==10&&skill_cost(&g,3)<high);for(int i=0;i<3;i++)ui_input(&u,&g,512);assert(skill_rank(&g,3)==4);g.diagnosticsOff45=1;g.walkPercent=100;SavedCharacter s,t;save_capture(&s,&g,1);assert(save_valid(&s));unsigned char disk[SAVE_BYTES];save_encode(disk,&s);assert(save_decode(&t,disk)==1);save_restore(&h,&t,1500,1500,clear45,NULL);assert(skill_rank(&h,3)==4&&h.ranks[index]==10&&h.walkPercent==100&&h.diagnosticsOff45);assert(h.maxsp==stat_maxsp(&h)&&h.maxhp==stat_maxhp(&h));dev_reset_skills(&h);assert(!h.useRanks45[index]);
/* Full learned prerequisite still counts after choosing a lower cast rank. */
assert(skill_prereqs(g.ranks));int passive=skill_rank(&g,85);assert(!skill_choose_rank45(&g,85,-1)&&skill_rank(&g,85)==passive);
/* Teleport works on every available map, preserving resources on a failed search. */
for(unsigned map=0;map<MYRO_MAP_COUNT43;map++){combat_init(&g,1500,1500,clear45,NULL);dev_class_preset(&g,3);g.mapId=map;g.utilityMenu=52;int before=g.sp;assert(skill_utility_commit(&g,0));assert(g.utilityMenu==0&&g.sp==before-skill_cost(&g,52));assert(g.x>=8&&g.y>=8&&g.x<mapWidth43[map]-8&&g.y<mapHeight43[map]-8);}
/* Priority: attacking low HP first, then distance; wrap in both directions. */
combat_init(&g,1500,1500,clear45,NULL);memset(g.mobs,0,sizeof(g.mobs));for(int i=0;i<4;i++){g.mobs[i].enabled=1;g.mobs[i].hp=100;g.mobs[i].x=1500+10*(i+1);g.mobs[i].y=1500;}g.mobs[2].aggro=g.mobs[3].aggro=1;g.mobs[3].hp=10;g.target=-1;int want[5]={3,2,0,1,3};for(int i=0;i<5;i++){combat_select(&g,1);assert(g.target==want[i]);}combat_select(&g,-1);assert(g.target==1);
/* Source-motion windup and flight precede one and only one incoming hit. */
combat_init(&g,1500,1500,clear45,NULL);CombatMob*m=&g.mobs[0];m->hp=100;m->x=1460;m->y=1500;g.hp=g.maxhp=100;g.time=1;combat_shot_begin45(&g,m,20);float impact=m->shotImpact45;g.time=impact-.001f;combat_shot_tick45(&g,m);assert(g.hp==100);g.time=impact;combat_shot_tick45(&g,m);assert(g.hp==80&&m->shotPhase45==3);combat_shot_tick45(&g,m);assert(g.hp==80);g.time+=1;combat_shot_tick45(&g,m);assert(!m->shotPhase45);
/* Home threshold no longer toggles a roaming creature back every frame. */
combat_init(&g,1900,1500,clear45,NULL);memset(g.mobs,0,sizeof(g.mobs));m=&g.mobs[0];m->enabled=1;m->hp=100;m->x=1545.1f;m->y=m->homeY=1500;m->homeX=1500;m->wanderX=1;m->wanderAt=m->wanderUntil=100;m->attackAt=-100;int flips=0,prev=0;for(int i=0;i<60;i++){combat_tick(&g,.05f,0,0);int dir=m->faceX>0?1:-1;if(prev&&dir!=prev)flips++;prev=dir;}assert(flips<=1&&m->x>1545.1f&&fabsf(m->x-m->homeX)>45);
Facing45 f={0};int dir=facing_stable45(&f,0,1,-sinf(.38f),-cosf(.38f),1,0);for(int i=0;i<1000;i++){float a=.39269908f+(i&1?.005f:-.005f);assert(facing_stable45(&f,0,1,-sinf(a),-cosf(a),1,0)==dir);}assert(facing_stable45(&f,0,1,-sinf(.6f),-cosf(.6f),1,0)!=dir);
/* Reordered visibility keeps each existing entity's cached GPU slot. */
SpriteSlots45 slots={0};int ids[3]={5,7,9},out[3],reordered[3]={9,5,7},next[3];unsigned life[3]={1,1,1};sprite_slots45(&slots,0,ids,life,3,out);sprite_slots45(&slots,0,reordered,life,3,next);assert(next[0]==out[2]&&next[1]==out[0]&&next[2]==out[1]);
puts("PASS45 rank UI/cost/save/prerequisites, all18 random Teleports, source derived maxSP, target priority/wrap, delayed one-shot incoming hits, roam/octant hysteresis and stable entity GPU slots.");}
