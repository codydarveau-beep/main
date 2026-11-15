/* MIT. Source SkillAction[AS_SONICBLOW]: one normal attack, then seven
 * attack actions at 30 ms per source frame. Damage cadence stays 200 ms.
 * Keep the game's existing normal-attack duration for the first action. */
static int sonic_pose50c(const Combat*g,const SparseSprite*s,int dir,float*elapsed,float*duration){
 if(g->hp<=0||g->moving||g->fxSkill!=131||g->attackAt>g->lastCast||dir<0||dir>7||s->actions<24)return 0;
 float age=g->time-g->lastCast;if(age<0)return 0;
 unsigned count=s->meta[(16+dir)*3+1];if(!count)return 0;
 if(age<.45f){*elapsed=age;*duration=.45f;return 1;}
 float fast=count*.030f,remaining=age-.45f;
 if(remaining>=7*fast)return 0;
 *elapsed=fmodf(remaining,fast);*duration=fast;return 1;
}
