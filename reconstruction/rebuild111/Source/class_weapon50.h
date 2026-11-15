/* MIT. Source weapon variance, size correction and personal weapon elements. */
static int class_offhand50(const Combat*g){int left=inventory_slot46(g,3);return job_parent52(g->jobId)==12&&left>=0&&itemDefs[left].slot==0&&inventory_fits50(g,left,3)?left:-1;}
static unsigned class_dual_gear50(const Combat*g){int left=class_offhand50(g);if(left<0)return 0;int a=inventory_wtype46(g),b=itemDefs[left].wtype;if(a>b){int n=a;a=b;b=n;}return a==b?(a==1?201:a==2?202:203):a==1?(b==2?204:205):206;}
static int class_offhand_damage50(Combat*g,const CombatMob*m){int left=class_offhand50(g);if(left<0)return 0;const ItemDef*d=&itemDefs[left];int lo=stat_value(g,4)*(80+20*d->weaponLv)/100,hi=d->attack;if(lo>hi)lo=hi;int raw=combat_base_atk48(g)+lo+(hi>lo?combat_random(g)%(hi-lo):0);raw=raw*(30+10*class_rank50(g,128))/100;raw=item_physical_hand_bonus52(g,m,raw,0,1);return combat_reduce48(raw*class_attack_rate48(g,m,class_weapon_element50(g))/100,combat_enemy_defense(m),mobStunVit[m->kind]);}
static int class_weapon_element50(const Combat*g){int wind=class_active50(g,SK60_TK_SEVENWIND);if(wind>=1&&wind<=7)return (int[]){2,4,1,3,8,7,6}[wind-1];if(class_active50(g,188))return 6;if(class_active50(g,133))return 5;for(int id=96;id<=99;id++)if(class_active48(g,id))return (int[]){3,1,4,2}[id-96];if(g->ammoShot60&&(ammo_weapon_mask60(inventory_wtype46(g))||g->fxSkill==SK60_NJ_KUNAI||g->fxSkill==SK60_NJ_SYURIKEN))return g->lastAmmoElement60;return g->itemBonuses52.scalar[B52_bAtkEle];}
static int class_weapon_power50(Combat*g,const CombatMob*m,int critical){
 int item=inventory_slot46(g,0),power=combat_physical(g);if(item<0)return power*(100+stargladiator_anger60(g,m))/100;
 const ItemDef*d=&itemDefs[item];int maximum=d->attack,minimum=stat_value(g,4)*(80+20*d->weaponLv)/100;if(minimum>maximum)minimum=maximum;
 if(critical||class_active50(g,234))minimum=maximum;
 int roll=minimum+(maximum>minimum?combat_random(g)%(maximum-minimum):0);
 static const unsigned char sizeRate[3][17]={{100,100,75,75,75,75,50,50,75,100,100,100,100,100,75,75,75},{100,75,100,75,75,75,75,75,100,100,100,100,100,75,100,100,100},{100,50,75,100,100,100,100,100,100,100,75,50,100,50,75,50,75}};
 int size=mobClassData50[m->kind][1];if(size>2)size=1;
 if(!class_active50(g,232)&&!g->itemBonuses52.scalar[B52_bNoSizeFix]&&d->wtype<17)roll=roll*sizeRate[size][d->wtype]/100;
 power+=(roll-maximum)*(100+5*class_active50(g,SK52_LK_CONCENTRATION))/100;
 if(job_parent52(g->jobId)==14&&(mobClassData50[m->kind][0]==2||mobClassData50[m->kind][0]==4))power+=4*class_rank50(g,164);
 power=power*(100+stargladiator_anger60(g,m))/100;
 if(d->wtype==16&&g->fxSkill!=SK52_ASC_BREAKER){int rank=class_rank50(g,SK52_ASC_KATAR);if(rank)power=power*(110+2*rank)/100;}return power>0?power:1;
}
static int class_near_wall50(const Combat*g){for(int i=0;i<4;i++){float dx=(int[]){-8,8,0,0}[i],dy=(int[]){0,0,-8,8}[i];if(g->canMove&&!g->canMove(g->world,g->x,g->y,g->x+dx,g->y+dy))return 1;}return 0;}
static float class_walk_rate50(const Combat*g){
 float rate=1;if(class_active50(g,SK60_GS_GATLINGFEVER))rate*=.5f;int itemSpeed=g->itemBonuses52.scalar[B52_bSpeedRate]+g->itemBonuses52.scalar[B52_bSpeedAddRate];if(class_active50(g,SKG52_TK_RUN)&&itemSpeed<55)itemSpeed=55;if(itemSpeed>90)itemSpeed=90;rate*=100.f/(100-itemSpeed);if(class_active50(g,SK52_WS_CARTBOOST))rate*=100.f/80;int chase=class_active50(g,SK52_ST_CHASEWALK);if(chase)rate*=100.f/(135-5*chase);int wind=class_active50(g,SK52_SN_WINDWALK);if(wind&&g->buffs[1]<=0)rate*=100.f/(100-2*wind);int cloak=class_active50(g,130);
 if(g->hideLeft>0&&job_parent52(g->jobId)==13)rate*=100.f/(220-6*class_rank50(g,143));
 if(g->class50.song)rate*=100.f/(600-40*class_rank50(g,job_parent52(g->jobId)==16?179:172));
 if(cloak){if(class_near_wall50(g))rate*=100.f/(100-(cloak>=10?25:3*cloak-3));else rate*=100.f/(cloak<3?400:130-3*cloak);}
 if(job_parent52(g->jobId)==20&&g->class50.homunBuffUntil[1]>g->time)rate*=100.f/(100-10*g->persistent50.homunSkills[1]);
 if(class_active50(g,207))rate*=.75f;
 return rate;
}
