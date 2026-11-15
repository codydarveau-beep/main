/* GPL-3.0-or-later. Original pre-renewal self Ka spells and monster Es spells. */
static int soullinker_ready60(Combat*g,unsigned id,int target){
 if(id==SK60_SL_SMA&&g->class50.esmaUntil60<=g->time){combat_notice(g,POP_SKILLS,"Use rank7+ Estin/Estun or Eske before Esma.");return 0;}
 if(id>=SK60_SL_STIN&&id<=SK60_SL_SKA&&(target<0||target>=MOB_COUNT||!g->mobs[target].enabled||g->mobs[target].hp<=0))return 0;
 if(id==SK60_SL_SMA&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for active spell hits; resources kept.");return 0;}
 return 1;
}
static int soullinker_element60(const Combat*g){int wind=class_active50(g,SK60_TK_SEVENWIND);if(wind>=1&&wind<=7)return (int[]){2,4,1,3,8,7,6}[wind-1];if(class_active50(g,188))return 6;if(class_active50(g,133))return 5;for(int i=96;i<=99;i++)if(class_active48(g,i))return (int[]){3,1,4,2}[i-96];return 0;}
static void soullinker_execute60(Combat*g,unsigned id,int rank,int target){
 if(id>=SK60_SL_KAIZEL&&id<=SK60_SL_KAITE){class_buff50(g,id,rank);if(id==SK60_SL_KAITE)g->class50.next[id-127]=1+rank/5;return;}
 if(target<0||target>=MOB_COUNT)return;CombatMob*m=&g->mobs[target];
 if(id==SK60_SL_SWOO){if(m->class50.swooUntil60>g->time){m->class50.swooUntil60=0;g->class50.expandedStunUntil60=g->time+10;g->moveLock45=10;combat_notice(g,POP_SKILLS,"Recasting Eswoo cancels it and stuns you for10seconds.");}else m->class50.swooUntil60=g->time+class_duration50(id,rank,0)/(combat_status_boss(m)?5:1);return;}
 if(id==SK60_SL_SKE){m->class50.eskeUntil60=g->time+class_duration50(id,rank,0);g->class50.esmaUntil60=g->time+class_duration50(SK60_SL_SMA,rank,0);return;}
 if(id==SK60_SL_SKA){m->class50.eskaUntil60=g->time+class_duration50(id,rank,0);m->class50.eskaNext60=g->time+1;m->class50.eskaDefense60=combat_random(g)%100;return;}
 int size=mobClassData50[m->kind][1],hits=id==SK60_SL_SMA?rank:1,ratio=id==SK60_SL_SMA?40+g->level:id==SK60_SL_STIN?(size==0?100+10*rank:1):(size!=2?100+5*rank:1);
 int power=combat_magic_power48(g)*ratio/100;if(power<1)power=1;int element=soullinker_element60(g);int damage=class_multi_element48(g,m,element,power,hits);if(damage<=0&&class_attack_rate48(g,m,element)>0)damage=hits;
 skill_magic_hit_ex48(g,target,damage,0,hits);
 if(id==SK60_SL_SMA)g->class50.esmaUntil60=0;
 else{if(rank>=7)g->class50.esmaUntil60=g->time+class_duration50(SK60_SL_SMA,rank,0);if(m->hp>0&&id==SK60_SL_STIN)combat_knockback(g,target,m->x-g->x,m->y-g->y,16);if(m->hp>0&&id==SK60_SL_STUN&&size==1)class_stun50(g,m,30+10*rank,class_duration50(id,rank,0));}
}
static int soullinker_kaupe60(Combat*g,int damage){int rank=class_active50(g,SK60_SL_KAUPE);if(damage>0&&rank&&class_chance50(g,rank==3?100:33*rank,100)){g->class50.until[SK60_SL_KAUPE-127]=0;combat_guard_number53(g);return 0;}return damage;}
static void soullinker_attacked60(Combat*g){int rank=class_active50(g,SK60_SL_KAAHI);if(rank&&g->hp>0&&g->hp<g->maxhp&&g->class50.kaahiAt60<=0)g->class50.kaahiAt60=g->time+class_duration50(SK60_SL_KAAHI,rank,1);}
static int soullinker_magic60(Combat*g,int target,int damage,int targeted){
 int rank=class_active50(g,SK60_SL_KAITE);
 if(damage>0&&targeted&&rank&&target>=0&&target<MOB_COUNT&&mobSourceLevel[g->mobs[target].kind]<=80){int old=g->fxSkill;g->fxSkill=SK60_SL_KAITE;g->itemProcSkip52=1;skill_magic_hit_ex48(g,target,damage,0,1);g->itemProcSkip52=0;g->fxSkill=old;if(--g->class50.next[SK60_SL_KAITE-127]<=0)g->class50.until[SK60_SL_KAITE-127]=0;return 0;}
 return soullinker_kaupe60(g,damage);
}
static int soullinker_revive60(Combat*g){
 if(g->hp>0)return 0;int rank=class_active50(g,SK60_SL_KAIZEL);if(!rank)return 0;
 int hp=(int)((int64_t)g->maxhp*10*rank/100);g->hp=hp>0?hp:1;combat_support_clear(g);memset(g->buffs,0,sizeof(g->buffs));g->poisonLeft=g->poisonTick=0;g->sitting=0;g->autoAttack=0;g->target=-1;g->deadAt=-100;g->hitStun=0;
 g->buffs[2]=class_duration50(SK60_SL_KAIZEL,rank,1);g->shieldHP=g->maxhp*30/100;g->shieldHits=10;g->fxSkill=SK60_SL_KAIZEL;g->fxRank48=rank;g->fxAt=g->time;g->fxX=g->x;g->fxY=g->y;combat_notice(g,POP_SKILLS,"Kaizel revived you. Kyrie protects you briefly.");return 1;
}
static void soullinker_tick60(Combat*g){
 if(g->class50.kaahiAt60>0&&g->class50.kaahiAt60<=g->time){g->class50.kaahiAt60=0;int rank=class_active50(g,SK60_SL_KAAHI),cost=5*rank;if(rank&&g->hp>0&&g->hp<g->maxhp&&g->sp>=cost){g->sp-=cost;int healed=200*rank;if(healed>g->maxhp-g->hp)healed=g->maxhp-g->hp;g->hp+=healed;combat_recovery_number53(g,healed,0);}}
 if(g->class50.expandedStunUntil60>g->time){float left=g->class50.expandedStunUntil60-g->time;if(g->moveLock45<left)g->moveLock45=left;}
 for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(m->class50.eskeUntil60<=g->time)m->class50.eskeUntil60=0;if(m->class50.swooUntil60<=g->time)m->class50.swooUntil60=0;if(m->class50.eskaUntil60<=g->time)m->class50.eskaUntil60=0;else if(m->class50.eskaNext60<=g->time){m->class50.eskaNext60=g->time+1;m->class50.eskaDefense60=combat_random(g)%100;}}
}
