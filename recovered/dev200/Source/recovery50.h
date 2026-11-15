/* MIT. Pre-renewal Hercules 21b27966: status_calc_regen_pc / status_natural_heal.
 * See RECOVERY50.md for source, formulas and the supported status mapping. */
#ifndef MYRO_RECOVERY50_H
#define MYRO_RECOVERY50_H
static int recovery_learned50(const Combat*g,unsigned id){
 int k=skill_rank_index(id);
 return k>=0&&job_owns_skill48(g->jobId,learnJobs[k],id)?g->ranks[k]:0;
}
static int recovery_add50(unsigned*clock,unsigned elapsed,unsigned interval,int amount,int*value,int maximum){
 if(amount<=0||*value>=maximum)return 0;
 *clock+=elapsed;
 if(*clock<interval)return 0;
 unsigned ticks=*clock/interval;*clock%=interval;
 int64_t total=(int64_t)ticks*amount,missing=maximum-*value;
 int healed=total<missing?(int)total:missing;*value+=healed;
 /* The source suppresses the following skill channel when a natural/sitting
  * heal was clamped. Equality is intentionally not considered a clamped heal. */
 return total>missing;
}
static void combat_recovery_tick50(Combat*g,float dt){
 Recovery50*r=&g->recovery50;
 float elapsed=r->fractionalMS+dt*1000.f;
 unsigned ms=(unsigned)elapsed;r->fractionalMS=elapsed-ms;
 if(!ms||g->hp<=0||g->trickDead55||class_active50(g,SK52_LK_BERSERK)||g->class50.regenBlockedUntil52>g->time||g->hideLeft>0||class_active50(g,130)
    ||(g->poisonLeft>0&&!class_active50(g,190)))return;
 int hpOpen=g->hp<g->maxhp,spOpen=g->sp<g->maxsp;
 int overweight=inventory_overweight(g,50),cadence=job_parent52(g->jobId)==18?recovery_learned50(g,199):0;
 /* Spiritual Cadence is evaluated before weight suppression in the source.
  * Fury/Asura/performances/Maximize Power suppress natural SP only. */
 if(g->sitting&&cadence){
  unsigned interval=overweight?20000:10000;
  if(hpOpen&&recovery_add50(&r->sittingHP,ms,interval,4*cadence+cadence*g->maxhp/500,&g->hp,g->maxhp))hpOpen=0;
  if(spOpen&&recovery_add50(&r->sittingSP,ms,interval,2*cadence+cadence*g->maxsp/500,&g->sp,g->maxsp))spOpen=0;
 }
 int relax=class_active50(g,SK52_LK_TENSIONRELAX);if(overweight&&!relax)return;if(overweight)spOpen=0;
 int vit=stat_value(g,2),intel=stat_value(g,3);
 int hp=1+vit/5+g->maxhp/200,sp=1+intel/6+g->maxsp/100;
 if(intel>=120)sp+=(intel-120)/2+4;sp=sp*(100+3*class_rank50(g,SK52_HP_MEDITATIO))/100;
 hp=hp*(100+g->itemBonuses52.scalar[B52_bHPrecovRate])/100;sp=sp*(100+g->itemBonuses52.scalar[B52_bSPrecovRate])/100;if(g->itemBonuses52.scalar[B52_bNoRegen]&1)hpOpen=0;if(g->itemBonuses52.scalar[B52_bNoRegen]&2)spOpen=0;
 unsigned hpInterval=g->sitting?3000:6000,spInterval=g->sitting?4000:8000;
 if(class_active50(g,192))spInterval/=2; /* Magnificat affects natural SP. */
 if(relax&&!overweight)hpInterval/=3;if(g->moving)hpInterval*=2;
 if(hpOpen&&(!g->moving||recovery_learned50(g,44))
    &&recovery_add50(&r->hp,ms,hpInterval,hp,&g->hp,g->maxhp))hpOpen=0;
 int spBlocked=g->class50.song||class_active50(g,234)
    ||(job_parent52(g->jobId)==18&&(class_active50(g,209)||class_active50(g,210)));
 if(spOpen&&!spBlocked&&recovery_add50(&r->sp,ms,spInterval,sp,&g->sp,g->maxsp))spOpen=0;
 if(g->moving)return;
 int hpRank=recovery_learned50(g,26),spRank=recovery_learned50(g,25)+recovery_learned50(g,SK60_NJ_NINPOU);
 if(hpOpen&&hpRank)recovery_add50(&r->skillHP,ms,relax&&!overweight?3333:10000,5*hpRank+hpRank*g->maxhp/500,&g->hp,g->maxhp);
 if(spOpen&&spRank)recovery_add50(&r->skillSP,ms,10000,3*spRank+spRank*g->maxsp/500,&g->sp,g->maxsp);
}
#endif
