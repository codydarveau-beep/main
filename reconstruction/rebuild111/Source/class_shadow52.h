/* MIT. Original pre-renewal Assassin Cross / Stalker solo interactions. */
static const unsigned shadowPoisonMaterials52[7]={937,952,939,7033,972,657,713};
static int class_poison_craft_ready52(Combat*g){int out=item_source50(678);if(out<0||!inventory_can_add(g,out,1))return 0;for(unsigned i=0;i<7;i++){int item=item_source50(shadowPoisonMaterials52[i]);if(item<0||inventory_count(g,item)<1)return 0;}return 1;}
static void class_shadow_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_ASC_EDP||id==SK52_ST_PRESERVE){class_buff50(g,id,rank);return;}
 if(id==SK52_ST_REJECTSWORD){class_buff50(g,id,rank);g->class50.rejectHits52=3;return;}
 if(id==SK52_ST_CHASEWALK){g->class50.until[id-127]=g->time+2147483.f;g->class50.level[id-127]=rank;g->class50.next[id-127]=g->time+10;g->autoAttack=0;return;}
 if(id==SK52_ASC_CDP){for(unsigned i=0;i<7;i++)--*inventory_stack(g,item_source50(shadowPoisonMaterials52[i]));if(class_chance50(g,2000+40*stat_value(g,4)+20*stat_value(g,5),10000))inventory_add(g,item_source50(678),1);else{g->hp-=g->maxhp/4;if(g->hp<0)g->hp=0;if(!g->hp){g->deadAt=g->time;combat_support_clear(g);}}return;}
 if(id==SK52_ASC_METEORASSAULT){for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,g->x,g->y,20))continue;skill_hit(g,i,class_physical50(g,m,40+40*rank,0,0),0);if(m->hp<=0||combat_status_boss(m))continue;int effect=combat_random(g)%3,chance=5+5*rank;if(effect==1)class_stun50(g,m,chance,5);else if(class_chance50(g,chance,100)){if(!effect)m->mobBlind=10;else{m->class50.bleedUntil=g->time+120;m->class50.bleedNext=g->time+10;}}}return;}
 CombatMob*m=&g->mobs[target];
 if(id==SK52_ASC_BREAKER){int damage=500+combat_random(g)%500+5*rank*stat_value(g,3);if(class_chance50(g,combat_hit_rate(combat_hit(g),combat_mob_flee(m)),100))damage+=class_physical50(g,m,100*rank,0,-1);skill_hit(g,target,damage,0);return;}
 if(id==SK52_ST_FULLSTRIP){if(combat_status_boss(m))return;int delta=stat_value(g,4)-mobSourceDex[m->kind],chance=5+2*rank+delta/5;if(chance<5)chance=5;if(class_chance50(g,chance,100)){float duration=class_duration50(id,rank,0)+delta*.5f;if(duration<0)duration=0;for(int i=0;i<4;i++)m->class50.stripUntil[i]=g->time+duration;}return;}
}
static void class_shadow_tick52(Combat*g){int rank=class_active50(g,SK52_ST_CHASEWALK);if(rank&&g->time>=g->class50.next[SK52_ST_CHASEWALK-127]){int cost=10+2*rank;if(g->sp<cost)g->class50.until[SK52_ST_CHASEWALK-127]=0;else{g->sp-=cost;g->class50.next[SK52_ST_CHASEWALK-127]+=10;if(g->class50.chaseStrengthUntil52<=g->time){g->class50.chaseStrengthUntil52=g->time+30;g->class50.chaseStrength52=1<<(rank-1);}}}}
