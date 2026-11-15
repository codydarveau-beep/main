/* Original pre-renewal common-status resistance; transient monster state only. */
static int skill_status_rate_bp164(const Combat*g,const CombatMob*m,int chance,int defense){
 int targetLevel=mobSourceLevel[m->kind],casterLevel=g->level;
 if(targetLevel>99)targetLevel=99;if(casterLevel>99)casterLevel=99;
 int rate=chance*100-chance*defense/100-mobStatusLuk[m->kind]*10-(targetLevel-casterLevel)*10;
 if(rate>0&&rate%10)rate+=10-rate%10;
 return rate<0?0:rate>10000?10000:rate;
}
static int skill_status_rate164(const Combat*g,const CombatMob*m,int chance,int defense){return skill_status_rate_bp164(g,m,chance,defense*100);}
static int skill_status_roll164(Combat*g,CombatMob*m,int chance,int defense){return !combat_status_boss(m)&&combat_random(g)%10000<(unsigned)skill_status_rate164(g,m,chance,defense);}
static float skill_status_duration164(int milliseconds,int defense,int extra){int n=milliseconds-milliseconds*defense/100-extra;return(n<1?1:n)/1000.f;}
static int skill_freeze164(Combat*g,CombatMob*m,int chance,int milliseconds){if(m->hp<=0||mobFreezeImmune[m->kind]||m->frozenLeft>0||m->stun>0||m->stoneLeft>0||m->class50.sleepUntil>g->time||!skill_status_roll164(g,m,chance,mobFreezeMdef[m->kind]))return 0;m->freezeAt=g->time;m->frozenLeft=skill_status_duration164(milliseconds,mobFreezeMdef[m->kind],-stat_value(g,5)*10);m->moving=0;return 1;}
static void skill_wizard_status164(Combat*g,CombatMob*m,int id,int rank){
 if(m->hp<=0||combat_status_boss(m))return;
 if(id==75&&m->stun<=0&&skill_status_roll164(g,m,3*rank,mobStunVit[m->kind]))m->stun=skill_status_duration164(5000,mobStunVit[m->kind],mobStatusLuk[m->kind]*10);
 if(id==77&&m->mobBlind<=0){int defense=(mobStunVit[m->kind]+mobInt48[m->kind])*50;if(combat_random(g)%10000<(unsigned)skill_status_rate_bp164(g,m,4*rank,defense)){int ms=5000+500*rank;ms-=ms*defense/10000+mobStatusLuk[m->kind]*10;m->mobBlind=(ms<1?1:ms)/1000.f;}}
 if(id==80){if(m->gustHits164<250)m->gustHits164++;else m->gustHits164=1;
  if(m->gustHits164>=3&&skill_freeze164(g,m,150,12000))m->gustHits164=0;
 }
}
