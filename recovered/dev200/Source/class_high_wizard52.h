/* MIT. Source ground cancellation and fixed-damage Gravitational Field. */
static int class_dispel_square52(float x,float y,float tx,float ty){return fabsf(x-tx)<12&&fabsf(y-ty)<12;}
static void class_high_wizard_execute52(Combat*g,unsigned id,int rank,float x,float y){
 if(id==SK52_HW_GANBANTEIN){if(!class_chance50(g,80,100))return;
  for(int i=0;i<CLASS_AREAS50;i++)if(class_dispel_square52(x,y,g->areas50[i].x,g->areas50[i].y))g->areas50[i].until=0;
  for(int i=0;i<CLASS_TRAPS50;i++)if(class_dispel_square52(x,y,g->traps50[i].x,g->traps50[i].y))g->traps50[i].until=0;
  for(int i=0;i<3;i++){if(class_dispel_square52(x,y,g->classAreas48[i].x,g->classAreas48[i].y))g->classAreas48[i].until=0;if(class_dispel_square52(x,y,g->safety[i].x,g->safety[i].y))g->safety[i].expires=0;if(class_dispel_square52(x,y,g->pneuma[i].x,g->pneuma[i].y))g->pneuma[i].expires=0;if(class_dispel_square52(x,y,g->portals[i].x,g->portals[i].y))g->portals[i].expires=0;}
  for(int i=0;i<COMBAT_FIELDS;i++)if(class_dispel_square52(x,y,g->fields[i].x,g->fields[i].y))g->fields[i].remaining=0;
  for(int i=0;i<COMBAT_BARRIERS;i++)if(class_dispel_square52(x,y,g->barriers[i].x,g->barriers[i].y))g->barriers[i].expires=0;
  return;
 }
 int slot=class_area_slot50(g);if(slot<0)return;g->areas50[slot]=(ClassArea50){.id=(int)id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time};class_buff50(g,id,rank);g->autoAttack=0;
}
static void class_gravitation_tick52(Combat*g){for(int i=0;i<CLASS_AREAS50;i++){ClassArea50*a=&g->areas50[i];if(a->id!=SK52_HW_GRAVITATION||a->map!=g->mapId||a->until<=g->time||a->next>g->time)continue;if(g->hp<=0){a->until=0;continue;}a->next+=1;int old=g->fxSkill;g->fxSkill=a->id;for(int n=0;n<MOB_COUNT;n++){CombatMob*m=&g->mobs[n];if(class_in_area50(g,m,a->x,a->y,20))skill_hit_now49(g,n,200+200*a->rank,0,1);}g->fxSkill=old;}}
