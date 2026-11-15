/* MIT. Source class-independent target-lock rules and exact source clocks. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "lockon_geometry49.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);assert(lockon_target49(&g)==-1);g.spellCastLeft=g.spellCastTotal=2;g.spellCastTarget=0;g.spellCastLife=7;g.mobs[0].enabled=1;g.mobs[0].hp=100;g.mobs[0].life=7;
 for(unsigned job=0;job<12;job++){g.jobId=job;assert(lockon_target49(&g)==0);}g.mobs[0].life++;assert(lockon_target49(&g)==-1);g.mobs[0].life=7;g.mobs[0].hp=0;assert(lockon_target49(&g)==-1);g.mobs[0].hp=100;g.spellCastLeft=0;assert(lockon_target49(&g)==-1);g.spellCastLeft=1;g.spellCastTarget=-1;assert(lockon_target49(&g)==-1);
 assert(lockon_width49(0)==120&&lockon_width49(.05f)==120&&lockon_width49(.1f)==96&&lockon_width49(.25f)==24&&lockon_width49(10)==24);assert(lockon_pulse49(0)==20);for(int t=0;t<10000;t++){unsigned p=lockon_pulse49(t*.001f);assert(p>=1&&p<=20);}
 assert(skill_cast_aura49(3)&&skill_cast_aura49(10)&&skill_cast_aura49(121));assert(!skill_cast_aura49(56)&&!skill_cast_aura49(59)&&!skill_cast_aura49(70)&&!skill_cast_aura49(71)&&!skill_cast_aura49(87));
 puts("PASS49 all12 classes share source timed-target lock; instant/completed/self-ground/missing/dead/new-life targets excluded; source250ms shrink,24-unit final width and20-state opaque colour pulse.");}
