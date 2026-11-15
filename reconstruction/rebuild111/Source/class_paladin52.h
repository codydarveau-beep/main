/* MIT. Solo Gospel retains original monster outcomes and excludes the caster. */
static void class_paladin_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_PA_SACRIFICE){g->class50.sacrificeRank52=rank;g->class50.sacrificeHits52=5;return;}
 if(id==SK52_PA_GOSPEL){int mount=g->mounted48;combat_support_clear(g);g->mounted48=mount;memset(g->buffs,0,sizeof(g->buffs));g->quickenLeft=g->energyCoatLeft=g->angelusLeft=g->poisonLeft=g->blindLeft=g->silenceLeft=g->hideLeft=0;g->shieldHP=g->shieldHits=0;class_buff50(g,id,rank);g->class50.gospelX52=g->x;g->class50.gospelY52=g->y;g->class50.next[id-127]=g->time+10;g->autoAttack=0;return;}
 CombatMob*m=&g->mobs[target];
 if(id==SK52_PA_PRESSURE){if(!m->class50.initialized){m->class50.initialized=1;m->class50.sp=mobClassData50[m->kind][2];}m->class50.sp-=mobClassData50[m->kind][2]*(15+5*rank)/100;if(m->class50.sp<0)m->class50.sp=0;skill_hit_now49(g,target,500+300*rank,0,1);return;}
 if(id==SK52_PA_SHIELDCHAIN){int left=inventory_slot46(g,3);const OwnedItem52*shield=inventory_instance52(g,3);int extra=left>=0?itemWeights[left]/10+(shield?4*shield->refine:0):0;int per=(class_weapon_power50(g,m,0)+extra)*(100+30*rank)/100;per=combat_reduce48(per,combat_enemy_defense(m),mobStunVit[m->kind]);int slot=skill_burst_slot49(g);if(slot<0)return;g->bursts49[slot]=(SkillBurst49){.active=1,.target=target,.hits=5,.damage=combat_hit_bonus50(g,m,per*5),.skill=(int)id,.rank=rank,.life=m->life,.map=g->mapId,.job=g->jobId,.next=g->time+stat_amotion48(g)*.001f,.gap=.2f};}
}
static int class_sacrifice_hit52(Combat*g,int target){
 int rank=class_active50(g,SK52_PA_SACRIFICE);if(!rank)return 0;CombatMob*m=&g->mobs[target];int cost=g->maxhp*9/100,damage=cost*(90+10*rank)/100;
 g->class50.sacrificeHits52--;class_fx50(g,SK52_PA_SACRIFICE,rank,m->x,m->y);skill_hit(g,target,damage,0);g->hp-=cost;if(g->hp<=0){g->hp=0;g->deadAt=g->time;g->autoAttack=0;combat_support_clear(g);}g->attackAt=g->time;g->cooldown=stat_attack_delay(g);return 1;
}
static void class_paladin_tick52(Combat*g){
 int rank=class_active50(g,SK52_PA_GOSPEL);
 if(rank){if(fabsf(g->x-g->class50.gospelX52)>.01f||fabsf(g->y-g->class50.gospelY52)>.01f)g->class50.until[SK52_PA_GOSPEL-127]=0;
  else{float*next=&g->class50.next[SK52_PA_GOSPEL-127];if(g->time>=*next){int hp=rank>5?45:30,sp=rank>5?35:20;if(g->hp<=hp||g->sp<sp)g->class50.until[SK52_PA_GOSPEL-127]=0;else{g->hp-=hp;g->sp-=sp;*next+=10;}}
   if(class_active50(g,SK52_PA_GOSPEL))for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];float x=fabsf(m->x-g->x),y=fabsf(m->y-g->y);if(!m->enabled||m->hp<=0||x>=28||y>=28||(x>=12&&y>=12)||g->time<m->class50.gospelNext52)continue;m->class50.gospelNext52=g->time+10;if(!class_chance50(g,rank*10+1,100))continue;
    int roll=combat_random(g)%9;float until=g->time+60;if(roll==0){int old=g->fxSkill;g->fxSkill=SK52_PA_GOSPEL;skill_hit(g,i,1+combat_random(g)%9999,0);g->fxSkill=old;continue;}if(combat_status_boss(m))continue;
    switch(roll){case 1:m->class50.curseUntil52=until;break;case 2:m->mobBlind=60;break;case 3:class_poison50(g,m,100,60);break;case 4:m->provokeRank=10;m->provokeLeft=60;break;case 5:m->class50.gospelDef52=until;break;case 6:m->class50.gospelAtk52=until;break;case 7:m->class50.gospelFlee52=until;break;case 8:m->class50.gospelSlow52=until;break;}
   }
  }
 }
 for(int i=0;i<MOB_COUNT;i++){ClassMob50*c=&g->mobs[i].class50;float*p[5]={&c->gospelDef52,&c->gospelAtk52,&c->gospelFlee52,&c->gospelSlow52,&c->curseUntil52};for(unsigned n=0;n<5;n++)if(*p[n]<=g->time)*p[n]=0;}
}
