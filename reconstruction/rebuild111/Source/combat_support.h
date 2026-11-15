/* MIT. Concealment, reveal and limited-catalog steal; no persistent world mutation. */
static void combat_reveal(Combat*g,float radius,int holy){
 int hit=0;for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!m->enabled||m->hp<=0||!m->hidden||combat_dist(g->x,g->y,m->x,m->y)>radius||(g->canAim&&!g->canAim(g->world,g->x,g->y,m->x,m->y)))continue;
  m->hidden=0;if(holy){int power=24+6*g->level+(stat_value(g,3)-1)*3;int damage=power*145/100*mobHolyRate[m->kind]/100;if(damage>0){skill_hit(g,i,damage,0);hit=1;}}
 }if(hit)combat_sound(g,0);
}
static void combat_support_tick(Combat*g,float dt){
 if(g->hp<=0){combat_support_clear(g);return;}
 if(g->hideLeft>0){g->hideLeft-=dt;g->hideDrain+=dt;float interval=g->hideRank+3;
  if(g->hideDrain>=interval){g->hideDrain-=interval;if(g->sp>0)g->sp--;if(g->sp<=0){g->hideLeft=0;combat_message(g,"Hiding ended: out of SP.");}}
  if(g->hideLeft<0)g->hideLeft=0;
 }
 if(g->concentrateLeft>0){g->concentrateLeft-=dt;if(g->concentrateLeft<0)g->concentrateLeft=0;}
 if(g->sightLeft>0){g->sightLeft-=dt;if(g->sightLeft<0)g->sightLeft=0;}
 if(g->ruwachLeft>0){g->ruwachLeft-=dt;if(g->ruwachLeft<0)g->ruwachLeft=0;}
 g->revealTick-=dt;if(g->revealTick<=0){g->revealTick=.2f;if(g->ruwachLeft>0)combat_reveal(g,16,1);if(g->sightLeft>0)combat_reveal(g,24,0);}
}
static void combat_steal(Combat*g,int target,int rank){CombatMob*m=&g->mobs[target];if(m->stolen||m->training||combat_status_boss(m)||m->stoneLeft>0||m->frozenLeft>0){combat_message(g,"This target cannot be stolen from.");return;}int rate=(stat_value(g,4)-mobSourceDex[m->kind])/2+rank*6+4;m->aggro=(mobSpecs[m->kind].flags&2)!=0;const uint16_t*table=mobLoot52[m->kind];if(rate>0)for(unsigned i=0;i<table[1];i++){unsigned index=table[0]+i,source=mobLootEntries52[index].source;if(item_rule52(source)->kind==OWNED_CARD52)continue;int chance=(int)mobLootEntries52[index].rate*rate/100;if(combat_random(g)%10000>=(unsigned)(chance>10000?10000:chance))continue;m->stolen=1;if(inventory_drop52(g,source))combat_message(g,"Stole %s.",itemDefs[inventory_catalog52(source)].name);else combat_message(g,"No room for the stolen item.");return;}combat_message(g,"Steal failed. You may try again.");}

