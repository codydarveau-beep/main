/* MIT. One pending targeted skill, costs committed only by skill_apply in range. */
static int skill_apply(Combat*g,unsigned id,float x,float y,int release);
static float skill_approach_range53(const Combat*g,unsigned id,int rank){return id>=127?class_range50(g,id,rank):id>=89?class_range48(g,id,rank):(id==17||id==59)?combat_attack_range(g):skillDefs[id].range;}
static int skill_approach_queue53(Combat*g,unsigned id,int rank,int target){
 g->route53.state=0;g->approachSkill53=id;g->approachRank53=rank;g->approachTarget53=target;g->approachLife53=g->mobs[target].life;g->approachMap53=g->mapId;g->approachJob53=g->jobId;g->approachStuck53=0;g->target=target;
 combat_notice(g,POP_SKILLS,"Approaching %s for %s. B or movement cancels.",mobSpecs[g->mobs[target].kind].name,skillDefs[id].name);return 1;
}
static int skill_approach_tick53(Combat*g,float dt){
 unsigned id=g->approachSkill53;int target=g->approachTarget53;
 if(!id)return 0;
 if(g->hp<=0||g->jobId!=g->approachJob53||g->mapId!=g->approachMap53||g->sitting||g->hideLeft>0||g->silenceLeft>0||inventory_overweight(g,90)||skill_rank(g,id)!=g->approachRank53||!combat_valid_target(g,target)||g->mobs[target].life!=g->approachLife53||g->target!=target||combat_dist(g->x,g->y,g->mobs[target].x,g->mobs[target].y)>192.f){g->approachSkill53=0;combat_notice(g,POP_SKILLS,"Queued skill cancelled; target or player changed. Resources kept.");return 0;}
 if(g->attackPaused52||g->utilityMenu||combat_casting(g)||g->moveLock45>0||g->class50.rootUntil>g->time||g->hitStun>0||g->castDelay>0||class_active50(g,153)||class_active50(g,SK52_HP_BASILICA)||class_active50(g,SK52_PA_GOSPEL)||class_active50(g,SK52_HW_GRAVITATION))return 1;
 CombatMob*m=g->mobs+target;float dx=m->x-g->x,dy=m->y-g->y,d=sqrtf(dx*dx+dy*dy),range=skill_approach_range53(g,id,g->approachRank53);int clear=skill_target_clear(g,id,m->x,m->y);
 if(d<=range&&clear){g->approachSkill53=0;skill_apply(g,id,m->x,m->y,0);return 1;}
 if(g->time-g->attackAt<COMBAT_ATTACK_ANIMATION53)return 1;
 if(d<.001f){g->approachSkill53=0;combat_notice(g,POP_SKILLS,"Cannot reach that target; resources kept.");return 0;}
 int route=player_route_step53(g,target,range,id,dt);g->moving=route==1;
 if(route)g->approachStuck53=0;else g->approachStuck53+=dt;
 if(g->approachStuck53>.75f){g->approachSkill53=0;combat_notice(g,POP_SKILLS,"Path blocked; skill resources kept.");}
 return 1;
}
