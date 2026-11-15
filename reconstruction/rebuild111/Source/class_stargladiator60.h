/* GPL-3.0-or-later. Permanent Feel/Hate choices and original solo effects. */
static int stargladiator_warm60(unsigned id){return id>=SK60_SG_SUN_WARM&&id<=SK60_SG_STAR_WARM;}
static int stargladiator_slot60(const Combat*g){for(int i=0;i<CLASS_AREAS50;i++)if(stargladiator_warm60(g->areas50[i].id)&&g->areas50[i].until>g->time&&g->areas50[i].map==g->mapId)return i;return class_area_slot50(g);}
static int stargladiator_ready60(Combat*g,unsigned id,int rank,int target){
 if(id==SK60_SG_FEEL||id==SK60_SG_HATE){if(rank<1||rank>3)return 0;unsigned choice=rank-1,value=id==SK60_SG_FEEL?g->mapId+1:target>=0&&target<MOB_COUNT?(unsigned)mobSpecs[g->mobs[target].kind].id:0;
  if(!value)return 0;unsigned stored=id==SK60_SG_FEEL?g->expanded60.feelMaps[choice]:g->expanded60.hateSources[choice];if(stored){combat_notice(g,POP_SKILLS,"This aspect is already assigned; it cannot be replaced.");return 0;}
  if(id==SK60_SG_HATE){int kind=g->mobs[target].kind;if(mobClassData50[kind][1]!=(int)choice||(choice==1&&mobSpecs[kind].hp<6000)||(choice==2&&mobSpecs[kind].hp<20000)){combat_notice(g,POP_SKILLS,"Sun: Small; Moon: Medium6000+HP; Stars: Large20000+HP.");return 0;}}
  if(g->class50.sgChoiceUntil60<=g->time||g->class50.sgChoiceSkill60!=id||g->class50.sgChoiceRank60!=(unsigned)rank||g->class50.sgChoiceValue60!=value){g->class50.sgChoiceUntil60=g->time+5;g->class50.sgChoiceSkill60=id;g->class50.sgChoiceRank60=rank;g->class50.sgChoiceValue60=value;combat_notice(g,POP_SKILLS,"Permanent choice. Use %s again within5seconds to confirm.",skillDefs[id].name);return 2;}
 }
 if(stargladiator_warm60(id)){if(!stargladiator_feel60(g,id-SK60_SG_SUN_WARM)){combat_notice(g,POP_SKILLS,"Use this Warmth on its Feeling map.");return 0;}if(stargladiator_slot60(g)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire.");return 0;}}
 if(id>=SK60_SG_SUN_COMFORT&&id<=SK60_SG_STAR_COMFORT){unsigned aspect=id-SK60_SG_SUN_COMFORT;if(!stargladiator_feel60(g,aspect)||(g->class50.sgMiracleUntil60<=g->time&&!stargladiator_day60(aspect))){combat_notice(g,POP_SKILLS,"Comfort requires its Feeling map and matching calendar day.");return 0;}}
 return 1;
}
static void stargladiator_execute60(Combat*g,unsigned id,int rank,int target){
 if(id==SK60_SG_FEEL||id==SK60_SG_HATE){if(id==SK60_SG_FEEL)g->expanded60.feelMaps[rank-1]=g->mapId+1;else if(target>=0&&target<MOB_COUNT)g->expanded60.hateSources[rank-1]=mobSpecs[g->mobs[target].kind].id;g->class50.sgChoiceUntil60=0;return;}
 if(stargladiator_warm60(id)){ClassArea50*a=&g->areas50[stargladiator_slot60(g)];*a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=g->x,.y=g->y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time};return;}
 if(id>=SK60_SG_SUN_COMFORT&&id<=SK60_SG_STAR_COMFORT)class_buff50(g,id,rank);
}
static void stargladiator_tick60(Combat*g){
 if(g->class50.sgKnowledgeMap60==g->mapId+1&&class_active50(g,SK60_SG_KNOWLEDGE))g->class50.until[SK60_SG_KNOWLEDGE-127]=g->time+86400;
 for(int k=0;k<CLASS_AREAS50;k++){ClassArea50*a=&g->areas50[k];if(!stargladiator_warm60(a->id))continue;if(a->map!=g->mapId){a->until=0;continue;}if(a->until<=g->time||a->next>g->time)continue;a->x=g->x;a->y=g->y;int old=g->fxSkill;g->fxSkill=a->id;for(unsigned pulse=0;pulse<4&&a->next<=g->time&&a->next<a->until;pulse++){a->next+=.1f;
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,a->x,a->y,12))continue;if(g->sp<2){a->until=0;break;}g->sp-=2;
   if(class_chance50(g,combat_hit_rate(combat_hit(g),combat_mob_flee(m)),100)){skill_hit(g,i,class_physical50(g,m,100,0,-1),0);if(m->hp>0)combat_knockback(g,i,m->x-a->x,m->y-a->y,16);}else{g->sp-=g->sp<8?g->sp:8;combat_miss(g,m->x,m->y);}
  }}g->fxSkill=old;
 }
}
