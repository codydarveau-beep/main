/* MIT. Fixed-capacity solo skill helpers. Original numeric data is separate. */
#include "item_data50.h"
#include "class_requirements50.h"
#include "mob_data50.h"
#include "class_weapon50.h"
static float class_range50(const Combat*g,unsigned id,int rank){const ClassSkill50*d=class_skill_data50(id);int cells=d?d->range[rank-1]:0;float range=(cells<0?-cells:cells)*8.f;if(id==SK60_GS_PIERCINGSHOT||id==SK60_GS_RAPIDSHOWER||id==SK60_GS_FULLBUSTER||id==SK60_GS_SPREADATTACK||id==SK60_GS_GROUNDDRIFT)range+=8*class_rank50(g,SK60_GS_SNAKEEYE);return range;}
static float class_duration50(unsigned id,int rank,int secondary){const ClassSkill50*d=class_skill_data50(id);return d?(secondary?d->duration2[rank-1]:d->duration[rank-1])*.001f:0;}
static void class_buff50(Combat*g,unsigned id,int rank){g->class50.level[id-127]=rank;g->class50.until[id-127]=g->time+class_duration50(id,rank,0);}
static void class_fx50(Combat*g,unsigned id,int rank,float x,float y){g->fxSkill=id;g->fxRank48=rank;g->fxX=x;g->fxY=y;g->fxAt=g->time;if(id!=SK52_CG_TAROTCARD)class_sound_emit50(g,id);}
static int class_chance50(Combat*g,int chance,int denominator){return chance>0&&(chance>=denominator||(int)(combat_random(g)%(unsigned)denominator)<chance);}
static int class_reachable50(const Combat*g,float x,float y,float tx,float ty){return class_ice_line48(g,x,y,tx,ty)&&(!g->canAim||g->canAim(g->world,x,y,tx,ty));}
static int class_in_area50(const Combat*g,const CombatMob*m,float x,float y,float radius){return m->enabled&&m->hp>0&&fabsf(m->x-x)<=radius&&fabsf(m->y-y)<=radius&&class_reachable50(g,x,y,m->x,m->y);}
static int class_area_slot50(const Combat*g){for(int i=0;i<CLASS_AREAS50;i++)if(g->areas50[i].until<=g->time||g->areas50[i].map!=g->mapId)return i;return -1;}
static int class_trap_slot50(const Combat*g){for(int i=0;i<CLASS_TRAPS50;i++)if(g->traps50[i].until<=g->time||g->traps50[i].map!=g->mapId)return i;return -1;}
static int class_summon_slot50(const Combat*g){for(int i=0;i<CLASS_SUMMONS50;i++)if(g->summons50[i].until<=g->time||g->summons50[i].map!=g->mapId)return i;return -1;}
static int class_nearest_trap50(const Combat*g,unsigned id,int rank){int found=-1;float nearest=class_range50(g,id,rank)+.01f;for(int i=0;i<CLASS_TRAPS50;i++){const ClassTrap50*t=&g->traps50[i];float d=combat_dist(g->x,g->y,t->x,t->y);if(t->map==g->mapId&&t->until>g->time&&!t->triggered&&d<nearest&&class_reachable50(g,g->x,g->y,t->x,t->y)){nearest=d;found=i;}}return found;}
static int class_poison50(Combat*g,CombatMob*m,int chance,float duration){if(combat_status_boss(m)||mobPoisonImmune[m->kind]||mobSpecs[m->kind].flags&16)return 0;if(!class_chance50(g,chance*(100-mobStunVit[m->kind])/100,100))return 0;m->poisonLeft=duration*(100-mobStunVit[m->kind])/100;if(m->poisonLeft<1)m->poisonLeft=1;m->poisonTick=0;return 1;}
static int class_stun50(Combat*g,CombatMob*m,int chance,float duration){if(m->hp<=0||m->frozenLeft>0||m->stoneLeft>0||m->class50.sleepUntil>g->time||!skill_status_roll164(g,m,chance,mobStunVit[m->kind]))return 0;m->stun=skill_status_duration164((int)(duration*1000),mobStunVit[m->kind],mobStatusLuk[m->kind]*10);return 1;}
static int class_physical_add60(Combat*g,CombatMob*m,int ratio,int ignoreDefense,int element,int extra){int64_t power=((int64_t)class_weapon_power50(g,m,0)+extra)*(ratio+20*class_active50(g,SK52_WS_OVERTHRUSTMAX)+5*class_active50(g,233))/100;power=power*(100+2*class_active50(g,SK52_SN_SIGHT))/100;if(element<0)element=class_weapon_element50(g);if(element>=0)power=power*class_attack_rate48(g,m,element)/100;if(g->fxSkill!=136&&g->fxSkill!=SK52_ASC_BREAKER&&g->fxSkill!=SK52_ASC_METEORASSAULT){int edp=class_active50(g,SK52_ASC_EDP);if(edp)power=power*(100+50*(edp+1))/100;}if(power>1000000000)power=1000000000;power=item_physical_bonus52(g,m,(int)power,(unsigned)g->fxSkill);int race=mobClassData50[m->kind][0],defense=combat_enemy_defense(m),soft=mobStunVit[m->kind],ignore=g->itemBonuses52.scalar[B52_bIgnoreDefRate]+item_bonus_match52(g,B52_bIgnoreDefRate,race,-1)+item_bonus_match52(g,B52_bIgnoreDefRate,item_boss_key52(m),-1);if(ignore>100)ignore=100;defense=defense*(100-ignore)/100;if(g->itemBonuses52.scalar[B52_bIgnoreDefRace]&item_target_races52(m))ignoreDefense=1;if(g->itemBonuses52.scalar[B52_bDefRatioAtkRace]&item_target_races52(m)){power=power*(combat_enemy_defense(m)+soft)/100;ignoreDefense=1;}int damage=ignoreDefense?(int)power:combat_reduce48((int)power,defense,soft);return damage+(g->fxSkill==SK52_LK_SPIRALPIERCE?0:20*class_active50(g,SK52_LK_AURABLADE));}
static int class_physical50(Combat*g,CombatMob*m,int ratio,int ignoreDefense,int element){return class_physical_add60(g,m,ratio,ignoreDefense,element,0);}
#include "trans_resources52.h"
#include "expanded_resources60.h"
static int class_resources50(Combat*g,unsigned id,int rank,int consume){
 if(id>=EXPANDED_FIRST60&&id<EXPANDED_LAST60)return expanded_resources60(g,id,rank,consume);
 if(g->itemCasting52)return 1;
 if(id>=GEAR_SKILL_FIRST52)return 1;
 if(id>=254)return trans_resources52(g,id,rank,consume);
 const ClassSkill50*d=class_skill_data50(id);
 if(!d||rank<1||rank>d->maxRank)return 0;
 const unsigned*req=classReq50[id-127];
 if(!consume&&req[1]&&!(req[1]&(1u<<inventory_wtype46(g)))){combat_notice(g,POP_SKILLS,"Equip the weapon required by %s.",skillDefs[id].name);return 0;}
 if(!consume&&req[5]){combat_notice(g,POP_SKILLS,"Requires a Soul Link; resources kept.");return 0;}
 if(req[2]){int item=item_source50(req[2]);if(!consume&&(item<0||inventory_count(g,item)<(int)req[3])){combat_notice(g,POP_SKILLS,"Required ammunition is missing; resources kept.");return 0;}if(consume)*inventory_stack(g,item)-=req[3];}
 int spheres=d->spheres[rank-1];if(id==203&&class_active50(g,209))spheres=0;
 if(id==210&&class_combo_action52(g,id)){unsigned previous=class_combo_source52(g);spheres=previous==212?4:previous==SK52_CH_TIGERFIST?3:g->class50.spheres?g->class50.spheres:1;}
 if(id==206&&spheres>g->class50.spheres)spheres=g->class50.spheres;
 if(!consume&&((id==206&&!spheres)||spheres>g->class50.spheres)){combat_notice(g,POP_SKILLS,"Not enough Spirit Spheres; resources kept.");return 0;}
 if(!consume&&g->hp<=(int)d->hp[rank-1]){combat_notice(g,POP_SKILLS,"Not enough HP; resources kept.");return 0;}
 if(!consume&&req[4]&&g->sp<skill_cost(g,id)+(int)(g->sp*req[4]/100)){combat_notice(g,POP_SKILLS,"Not enough SP; resources kept.");return 0;}
 for(unsigned i=0;i<sizeof(classItems50)/sizeof(*classItems50);i++){const unsigned short*r=classItems50[i];if(r[0]!=id)continue;if(id==250&&g->persistent50.homunType)continue;int amount=inventory_gem_cost52(g,id,itemDefs[r[1]].id,r[rank+1]);if(!consume&&inventory_count(g,r[1])<amount){combat_notice(g,POP_SKILLS,"Need %s; resources kept.",itemDefs[r[1]].name);return 0;}}
 if(!consume)return 1;
 if(req[4])g->sp-=g->sp*req[4]/100;
 if(spheres){for(int s=0;s<spheres;s++)g->class50.sphereUntil[s]=0;int n=0;for(int s=spheres;s<g->class50.spheres;s++)g->class50.sphereUntil[n++]=g->class50.sphereUntil[s];g->class50.spheres=n;}
 for(unsigned i=0;i<sizeof(classItems50)/sizeof(*classItems50);i++){const unsigned short*r=classItems50[i];if(r[0]==id&&!(id==250&&g->persistent50.homunType))if(inventory_gem_cost52(g,id,itemDefs[r[1]].id,r[rank+1]))*inventory_stack(g,r[1])-=inventory_gem_cost52(g,id,itemDefs[r[1]].id,r[rank+1]);}
 return 1;
}
