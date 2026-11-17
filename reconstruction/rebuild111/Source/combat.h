#include "expanded_state60.h"
#include "appearance_state58.h"
#include "job_map_flags55.h"
#include "item_count46.h"
#include "owned_items52.h"
#include "item_bonus_types52.h"
/* SPDX-License-Identifier: MIT
 * Small offline test simulation. Simplified player formulas/AI, not Hercules combat.
 * Poring/Lunatic base values taken from the supplied pre-re mob database.
 */
#ifndef MYRO_COMBAT_H
#define MYRO_COMBAT_H
#include <math.h>
#include <stdint.h>
#include "game_rates164.h"
#include "bindings50.h"
#include "play_options52.h"
#include "class_sound_data50.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "encounter_data.h"
#include "mvp_balance164.h"
#include "mob_data50.h"
#include "skill_audio180.h"
#include "progression_data.h"
#include "stats_data48.h"
#include "map_limits43.h"
#include "class_mob_traits.h"
#include "mob_control_traits.h"
#include "mob_sand_traits.h"
#include "mob_flame_traits.h"
#include "mob_utility_traits.h"
#include "mob_acolyte_traits.h"
#include "mob_accuracy_traits.h"
#include "mob_range43.h"
#include "mob_stun_traits.h"
#include "mob_motion49.h"
#include "boss_state53.h"
#define SKILL_BURSTS49 128
/* Same transient hit pool:0 free,1 skill packet,2 pending basic contact. */
#define BASIC_CONTACT267 2
typedef struct {int active,target,hits,done,damage,applied,stun,skill,rank,companion50;unsigned life,map,job,combo;float next,gap;} SkillBurst49;
typedef struct {float x,y,at;float hitGap;int value,hits,critical,kind,style;unsigned owner180,life180,spread180;} DamageEvent;
#define PLAYER_ROUTE_POINTS53 192
typedef struct {unsigned state,life,map,mode,count,at;int target;float range,goalX,goalY,retryAt;int16_t points[PLAYER_ROUTE_POINTS53][2];} PlayerRoute53;
#define DAMAGE_EVENTS 16
#define ENERGY_COAT_CAST_SECONDS 5.f
typedef int (*CombatCanMove)(void*,float,float,float,float);
#include "class_state50.h"
#include "recovery_state50.h"
#include "mercenary_state180.h"
typedef struct {float fromX,fromY,toX,toY,launch,impact;int damage,phase;unsigned map,life;} GuardianShot164;
typedef struct {
 GuardianShot164 arrows164[3];unsigned raceTouch164;float raceSpeed164,raceSpeedUntil164;
 ClassMob50 class50;uint16_t bossKey53;uint32_t npcSpawn55;
 float x,y,homeX,homeY,faceX,faceY,cooldown,attackAt,hurtAt,deadAt,wanderAt,wanderUntil;
 unsigned char gustHits164;float gustNext164,vermNext164;float flashAt49;float hitLockUntil49;float castUntil48;int castSkill48,castRank48,castSP48,element48;
 unsigned routeDetour53;float routeSkipUntil53;float slowLeft;int slowRank,crucisRank;float frozenLeft,freezeAt,mobBlind,stoneWait,stoneLeft,stoneTick,stoneNoticeUntil;int stoneNotice;float provokeLeft;int provokeRank;int training,trainingActive,testMaxHP;int hidden,stolen,testTraits;unsigned life;int kind,hp,aggro,moving,enabled,spawnDef,sleeping;float wanderX,wanderY,stun,respawnAt,poisonLeft,poisonTick;float shotLaunch45,shotImpact45,shotFromX45,shotFromY45,shotToX45,shotToY45;int shotDamage45,shotPhase45,returningHome45;
} CombatMob;
#include "class_state48.h"
#define COMBAT_FIELDS 3
typedef struct {float meteorX49[7],meteorY49[7];float createdAt45,triggeredAt45;int triggered45;float x,y,nextAt,fadeUntil;int remaining,power,expected,secondId,rank;float radius;unsigned companionOwner194;unsigned totalEvent[MOB_COUNT];int total[MOB_COUNT];unsigned char hits[MOB_COUNT],shown[MOB_COUNT];float lastX[MOB_COUNT],lastY[MOB_COUNT];} CombatField;
#define COMBAT_BARRIERS 3
typedef struct {float x,y,axisX,axisY,awayX,awayY,expires,nextAt;int hits[3],power;int total[MOB_COUNT];unsigned totalEvent[MOB_COUNT];} CombatBarrier;
#define SAFETY_RADIUS 6.f
#define PNEUMA_RADIUS 12.f
typedef struct {unsigned map;float x,y;} WorldPosition;
typedef struct {float x,y,expires,blockedUntil;int hits;float createdAt49;} SafetyWall;
typedef struct {float x,y,expires;} PneumaField;
typedef struct {float x,y,expires;WorldPosition destination;int uses;} SkillPortal;
typedef struct {int active,target,left,hits,power;unsigned map,life;float nextAt,push;} Jupitel45;
typedef struct {
 Mercenary180 mercenary180;
 ExpandedState60 expanded60;BossState53 bosses53;uint64_t bossSeenUTC53;unsigned died53,superSteelUsed53,superPrayer53;float superSuffragUntil53;
 Recovery50 recovery50;
 ClassPersistent50 persistent50;ClassTransient50 class50;ClassTrap50 traps50[CLASS_TRAPS50];ClassArea50 areas50[CLASS_AREAS50];ClassSummon50 summons50[CLASS_SUMMONS50];
 SafetyWall safety[3];PneumaField pneuma[3];SkillPortal portals[3];
 WorldPosition home,memos[3],travel;unsigned memoCount;int travelRequest,utilityMenu,utilityTestWater,utilityItemRank52;float utilityX,utilityY;
 float blindLeft,silenceLeft,confusionLeft;CombatCanMove inWater;
 float x,y,campX,campY,faceX,faceY,time,attackAt,hurtAt,deadAt,cooldown,lastDamage;
 int hp,maxhp,sp,maxsp,level,joblevel,exp,jexp,kills,jellopy,clover,apples,target,autoAttack,moving;
 int floorTarget58,floorPickup58;unsigned floorGather60;float floorScan60;unsigned selectedAmmo60,lastAmmoElement60,lastAmmoAttack60,ammoShot60,expandedCoins60,ammoDirty60;
 PlayerRoute53 route53;
 unsigned approachSkill53,approachRank53,approachLife53,approachMap53,approachJob53;int approachTarget53;float approachStuck53;
 unsigned autoAttackToggle52,monsterView52;int attackPaused52,debugPlayerInvincible52,trickDead55;unsigned sex55;Appearance58 appearance58;char name56[20];
 ItemBonuses52 itemBonuses52;int calendarDay52,calendarMonth52,itemCasting52,itemVMEvent52,itemProcSkip52;unsigned itemDamageSkill52;int(*canSpecies52)(void*,unsigned);int creatureAssetsChanged52;OwnedItems52 owned52;uint32_t itemActionUID52,cardUID52;int missingStack52;unsigned equipment;unsigned short equipped46[EQUIP_SLOTS46];
 int tooltipsDisabled;unsigned popupDisabled,logCategory;int cartOwned,cartStyle,cartQuantity;float uproarLeft,energyCoatLeft,coatCastLeft;
 /* Pending spells are transient; no Save20 layout change. */
 float moveLock45;float spellCastLeft,spellCastTotal,spellCastX,spellCastY;unsigned spellCastId,spellCastJob,spellCastMap,spellCastLife,spellCastFriendly200,spellCastFriendlyLife200;int spellCastTarget,spellCastRank,spellCastInterruptible;
 SkillBinding50 hotbar[12];unsigned hotSlot,mapId,quickKind,quickId,rbBinding;int diagnosticsOff45;int zeny,peaceful,hotAttack,walkPercent,attackSoundDelayMs,successCircleDiameter;
 unsigned char stats[6];int statPoints,sitting;unsigned jobId,noviceQuest54b,jobSkillCarry55;unsigned carryTraining180;unsigned char ranks[LEARN_COUNT],useRanks45[LEARN_COUNT];int skillPoints;float buffs[3];int shieldHP,shieldHits;unsigned awakeCount,sleepCount;
 float guardFxAt49;float hideLeft,hideDrain,sightLeft,ruwachLeft,concentrateLeft,revealTick;int hideRank,concentrateRank,autoBerserk;
 float classUntil48[38];unsigned char classLevel48[38];ClassArea48 classAreas48[3];int autoSpell48,mounted48,brokenWeapon48,hocusID48,hocusRank48;
 float quickenLeft,counterLeft,sightblasterLeft,magicAmpLeft;int magicAmpRank;float skillCD[SKILL_CAP50],castDelay,lastCast,fxAt,fxX,fxY;int fxSkill,fxRank48;int fxTarget200;unsigned fxLife200;float fxFromX200,fxFromY200;
 float poisonLeft,poisonTick;unsigned char buffLevels[2];
 SkillBurst49 bursts49[SKILL_BURSTS49];DamageEvent damage[DAMAGE_EVENTS];unsigned damageNext;
 CombatMob mobs[MOB_COUNT];uint32_t rng;char log[100];int logIsTip;
 unsigned soundEvents[32],soundRead,soundWrite;float soundDue[32];int debugImmortal,debugFreeze;float hitStun,endureLeft;int endureHits;
 Jupitel45 jupitel45[8];CombatField fields[COMBAT_FIELDS];CombatBarrier barriers[COMBAT_BARRIERS];float angelusLeft;int angelusRank;
 CombatCanMove canMove,canAim;void *world;
} Combat;
#include "travel_admission194.h"
static int mercenary_devotion180(Combat*g,int damage);
static void mercenary_tick180(Combat*g,float dt);
static int mercenary_enemy180(Combat*g,int i,float dt);
static int(*combat_campaign_enemy200)(Combat*,int,float);
static int(*combat_companion_field194)(Combat*,CombatField*,int);
/* Scoped friendly command; delayed casts capture member identity separately. */
static unsigned combat_friendly_target200,combat_friendly_life200;
static int(*combat_friendly_heal200)(Combat*,int,float*,float*);
static int(*combat_friendly_revive_ready200)(Combat*,float*,float*);
static int(*combat_friendly_revive200)(Combat*,int,float*,float*);
static int(*combat_friendly_buff_ready200)(Combat*,float*,float*);
static int(*combat_friendly_buff200)(Combat*,unsigned,int,float*,float*);
static int(*combat_party_recover200)(Combat*,unsigned,unsigned);
static int(*combat_party_needs_recovery200)(const Combat*,unsigned,unsigned);
static int mercenary_menu180(Combat*g,int choice);
static void mercenary_kill180(Combat*g,CombatMob*m);
static int(*combat_merc_item180)(void*,Combat*,unsigned);
static int soullinker_revive60(Combat*g);
static void soullinker_attacked60(Combat*g);
static int soullinker_magic60(Combat*g,int target,int damage,int targeted);
static void(*combat_npc_kill55)(void*,Combat*,CombatMob*);
/* Original player-skill presentation, emitted at the actual hit boundary. */
static void(*combat_skill_effect263)(Combat*,unsigned,float,float);
static void(*combat_campaign_kill200)(Combat*,const CombatMob*);
static void*combat_npc_context55;
static void(*combat_racer_step164)(void*,Combat*,CombatMob*,float);
static int combat_racer_kind164(unsigned kind){return kind<MOB_SPEC_COUNT&&mobSpecs[kind].id>=1725&&mobSpecs[kind].id<=1730;}

static const char*(*combat_npc_name55)(void*,const CombatMob*);
static void combat_support_clear(Combat*g){g->route53.state=0;g->approachSkill53=0;memset(&g->class50,0,sizeof(g->class50));memset(g->traps50,0,sizeof(g->traps50));memset(g->areas50,0,sizeof(g->areas50));memset(g->summons50,0,sizeof(g->summons50));g->guardFxAt49=-1000;memset(g->bursts49,0,sizeof(g->bursts49));memset(g->classUntil48,0,sizeof(g->classUntil48));memset(g->classAreas48,0,sizeof(g->classAreas48));g->autoSpell48=0;g->mounted48=0;g->hocusID48=g->hocusRank48=0;memset(g->safety,0,sizeof(g->safety));memset(g->pneuma,0,sizeof(g->pneuma));memset(g->portals,0,sizeof(g->portals));g->expandedCoins60=0;g->utilityMenu=0;g->spellCastLeft=g->spellCastTotal=0;g->spellCastId=0;g->uproarLeft=g->energyCoatLeft=g->coatCastLeft=0;g->blindLeft=g->silenceLeft=g->confusionLeft=0;g->hideLeft=g->hideDrain=g->sightLeft=g->ruwachLeft=g->concentrateLeft=g->revealTick=0;g->hideRank=g->concentrateRank=g->autoBerserk=0;}
static void combat_number(Combat*g,float x,float y,int value,int hits,int critical){if(value<=0)return;g->damage[g->damageNext++%DAMAGE_EVENTS]=(DamageEvent){x,y,g->time,.2f,value,hits<1?1:hits>10?10:hits>value?value:hits,critical};}
/* Distinguish overlapping enemies without disturbing isolated-target hit layout.
   Stable identity includes respawn generation; this is transient display state. */
static void combat_enemy_tag180(Combat*g,const CombatMob*m,DamageEvent*d){
 d->owner180=(unsigned)(m-g->mobs)+1;d->life180=m->life;
 unsigned n=g->damageNext<DAMAGE_EVENTS?g->damageNext:DAMAGE_EVENTS;
 for(unsigned i=0;i<n;i++){DamageEvent*o=g->damage+i;if(o==d||!o->owner180||o->kind>1)continue;
  float age=g->time-o->at,dx=d->x-o->x,dy=d->y-o->y;
  if(age<0||age>(o->hits-1)*o->hitGap+(o->kind==1?3.f:1.5f)||dx*dx+dy*dy>256)continue;
  if(o->owner180!=d->owner180||o->life180!=d->life180)d->spread180=o->spread180=1;
  else if(o->spread180)d->spread180=1;
 }
}
static void combat_enemy_number180(Combat*g,const CombatMob*m,int value,int hits,int critical){
 if(value<=0)return;combat_number(g,m->x,m->y,value,hits,critical);combat_enemy_tag180(g,m,&g->damage[(g->damageNext-1)%DAMAGE_EVENTS]);
}
/* Damage style: white outgoing, yellow crit/combo, red incoming, green HP, blue SP. */
static void combat_received_number53(Combat*g,int value,int hits){if(value<=0)return;combat_number(g,g->x,g->y,value,hits,0);g->damage[(g->damageNext-1)%DAMAGE_EVENTS].style=2;}
static void combat_recovery_number53(Combat*g,int hp,int sp){if(hp>0){combat_number(g,g->x,g->y,hp,1,0);DamageEvent*d=&g->damage[(g->damageNext-1)%DAMAGE_EVENTS];d->kind=4;d->style=3;}if(sp>0){combat_number(g,g->x,g->y,sp,1,0);DamageEvent*d=&g->damage[(g->damageNext-1)%DAMAGE_EVENTS];d->kind=5;d->style=4;}}
static void combat_guard_number53(Combat*g){DamageEvent*d=&g->damage[g->damageNext++%DAMAGE_EVENTS];*d=(DamageEvent){g->x,g->y,g->time,.2f,0,1,0,3,2};}
static void combat_combo(Combat*g,unsigned*token,float x,float y,int value){
 DamageEvent*d=NULL;if(*token&&*token<=g->damageNext&&g->damageNext-(*token-1)<=DAMAGE_EVENTS){DamageEvent*old=&g->damage[(*token-1)%DAMAGE_EVENTS];if(old->kind==1)d=old;}
 if(!d){combat_number(g,x,y,value,1,0);*token=g->damageNext;d=&g->damage[(*token-1)%DAMAGE_EVENTS];}d->x=x;d->y=y;d->value=value;d->at=g->time;d->kind=1;
}
static int skill_rank_index(unsigned id);
static int class_rank50(const Combat*g,unsigned id){int k=id>=127&&id<254?(int)id-3:id>=254&&id<SKILL_CAP50?skill_rank_index(id):-1;int rank=k>=0?g->ranks[k]:0,grant=id<512?g->itemBonuses52.grant[id]:0;return rank>grant?rank:grant;}
static int class_active50(const Combat*g,unsigned id){if(id==SK52_PA_SACRIFICE)return g->class50.sacrificeHits52>0?g->class50.sacrificeRank52:0;return id>=127&&id<SKILL_CAP50&&g->class50.until[id-127]>g->time?g->class50.level[id-127]:0;}
static unsigned class_combo_source52(const Combat*g){int target=g->class50.comboTarget;return g->class50.comboUntil>g->time&&target>=0&&target<MOB_COUNT&&g->target==target&&g->mobs[target].enabled&&g->mobs[target].hp>0&&g->mobs[target].life==g->class50.comboLife?(unsigned)g->class50.comboSkill:0;}
static int class_combo_action52(const Combat*g,unsigned id){unsigned previous=class_combo_source52(g);return previous&&((id==211&&previous==202)||(id==212&&previous==211)||(id==SK52_CH_TIGERFIST&&previous==212)||(id==SK52_CH_CHAINCRUSH&&previous==SK52_CH_TIGERFIST)||(id==210&&(previous==212||previous==SK52_CH_TIGERFIST||previous==SK52_CH_CHAINCRUSH)));}
static void class_tick50(Combat*g,float dt);
static void class_after_attack50(Combat*g,int target);
static int class_received50(Combat*g,int mob,int damage,int ranged);
static int class_block50(Combat*g,int mob);
static int class_sacrifice_hit52(Combat*g,int target);
static int class_triple50(Combat*g,int target);
static void class_ore_drop50(Combat*g);
static void homun_gain50(Combat*g,unsigned exp);
static int class_mob_companion50(Combat*g,int i,float dt);
static int class_offhand50(const Combat*g);
static int class_weapon_power50(Combat*g,const CombatMob*m,int critical);
static int class_weapon_element50(const Combat*g);
static float class_walk_rate50(const Combat*g);
static int stat_value(const Combat*g,int n);
static int combat_vit_defense(const Combat*g){if(class_active50(g,SK52_LK_BERSERK))return 0;int n=stat_value(g,2);if(class_active50(g,SK60_SG_SUN_COMFORT))n+=(g->level+stat_value(g,4)+stat_value(g,5))/2;if(g->angelusLeft>0)n=n*(100+5*g->angelusRank)/100;n=n*(100+g->itemBonuses52.scalar[B52_bDef2Rate])/100;n-=n*5*class_active50(g,SK52_LK_CONCENTRATION)/100;return n;}
static int combat_dodge_chance(const Combat*g){return (job_first50(g->jobId)==4||g->jobId==J52_SUPER_NOVICE)?3*g->ranks[30]:0;} /* FLEE bonus, not an independent dodge roll. */
static int stat_value(const Combat*g,int n);
static void item_proc_event52(Combat*g,int event,int target,int damage,unsigned skill);
static void item_proc_tick52(Combat*g);
static int item_bonus_match52(const Combat*g,unsigned type,int key,int all);
static int inventory_wtype46(const Combat*g);
static int combat_crit_chance(const Combat*g){int n=10+stat_value(g,5)*10/3+10*g->itemBonuses52.scalar[B52_bCritical],rank=class_active50(g,209);n+=10*class_active50(g,SK52_SN_SIGHT);if(rank)n+=75+25*rank;if(inventory_wtype46(g)==16)n*=2;return n;} /* per1000, before target LUK */
static int combat_hit(const Combat*g){int v=g->level+stat_value(g,4)+g->itemBonuses52.scalar[B52_bHit]+3*class_active50(g,SK52_SN_SIGHT)+10*class_active50(g,SK52_LK_CONCENTRATION)+((job_first50(g->jobId)==5||g->jobId==J52_SUPER_NOVICE)?g->ranks[12]:0)+(job_parent52(g->jobId)==19?2*class_rank50(g,227):0);if(inventory_wtype46(g)>=17&&inventory_wtype46(g)<=21)v+=2*class_rank50(g,SK60_GS_SINGLEACTION)+class_rank50(g,SK60_GS_SNAKEEYE);if(class_active50(g,SK60_GS_INCREASING))v+=20;if(class_active50(g,SK60_GS_ADJUSTMENT))v-=30;v=v*(100+g->itemBonuses52.scalar[B52_bHitRate])/100;return g->blindLeft>0?v-v*25/100:v;}
static int combat_flee(const Combat*g){int v=g->level+stat_value(g,1)+g->itemBonuses52.scalar[B52_bFlee]+(class_active50(g,SK52_SN_WINDWALK)+1)/2+combat_dodge_chance(g)+(job_parent52(g->jobId)==18?class_rank50(g,204)*3/2:0);if(class_active50(g,SK60_SG_MOON_COMFORT))v+=(g->level+stat_value(g,4)+stat_value(g,5))/10;if(class_active50(g,SK60_GS_ADJUSTMENT))v+=30;v-=5*class_active50(g,SK60_GS_GATLINGFEVER);if(v<1)v=1;if(class_active50(g,SK52_LK_BERSERK))v/=2;return g->blindLeft>0?v-v*25/100:v;}
static int combat_hit_rate(int hit,int flee){int n=80+hit-flee;return n<5?5:n>100?100:n;}
static int class_fog_at52(const Combat*g,float x,float y){for(int i=0;i<CLASS_AREAS50;i++){const ClassArea50*a=&g->areas50[i];if(a->id==SK52_PF_FOGWALL&&a->map==g->mapId&&a->until>g->time&&fabsf(x-a->x)<20&&fabsf(y-a->y)<12)return 1;}return 0;}
static int combat_mob_flee(const CombatMob*m){if(m->class50.gospelFlee52>0)return 0;int agi=mobSourceAgi[m->kind];if(m->class50.suitonUntil60>0){agi-=3*((m->class50.suitonRank60+1)/3)-(m->class50.suitonRank60>4);if(agi<1)agi=1;}if(m->slowLeft>0){agi-=2+m->slowRank;if(agi<1)agi=1;}int n=(mobSourceLevel[m->kind]+agi)*(100+m->class50.tarotFlee52)/100;if(m->class50.webRoot52)n/=2;return m->mobBlind>0?n*75/100:n;}
static int item_target_bonus52(const Combat*g,const CombatMob*m,unsigned type);
static int combat_target_crit(const Combat*g,const CombatMob*m){int n=combat_crit_chance(g)+10*item_target_bonus52(g,m,B52_bCriticalAddRace)-2*(m->class50.curseUntil52>g->time?0:mobStatusLuk[m->kind]);return n<0?0:n>1000?1000:n;}
static void combat_miss(Combat*g,float x,float y){DamageEvent*d=&g->damage[g->damageNext++%DAMAGE_EVENTS];memset(d,0,sizeof(*d));d->x=x;d->y=y;d->at=g->time;d->kind=2;d->style=x==g->x&&y==g->y?2:0;d->hits=1;d->hitGap=.1f;}

static int divine_reduction(const Combat*g,int race){return (job_first50(g->jobId)==3||g->jobId==J52_SUPER_NOVICE)&&(race==1||race==6)?3*g->ranks[5]:0;}
/* Prototype derived stats; base stats persist, temporary buffs never do. */
#include "elements48.h"
static int class_element_base48(const CombatMob*m,int attack){int elem=m->element48?m->element48:mobElement48[m->kind][0],level=m->element48?1:mobElement48[m->kind][1];return elementRate48[level-1][elem][attack];}
static int class_element_rate48(const CombatMob*m,int attack){int elem=m->element48?m->element48:mobElement48[m->kind][0],level=m->element48?1:mobElement48[m->kind][1];if(m->frozenLeft>0){elem=1;level=1;}if(m->stoneLeft>0){elem=2;level=1;}return elementRate48[level-1][elem][attack];}
static int class_field_at48(const Combat*g,int id,float x,float y);
static int class_field_bonus48(const Combat*g,int element){int id=element==3?101:element==1?102:element==4?103:0;if(!id)return 0;int rank=class_field_at48(g,id,g->x,g->y);static const unsigned char bonus[5]={10,14,17,19,20};return rank>0&&rank<=5?bonus[rank-1]:0;}
static int class_attack_rate48(const Combat*g,const CombatMob*m,int element){return class_element_rate48(m,element)+class_field_bonus48(g,element);}
static int class_multi_element48(const Combat*g,const CombatMob*m,int attack,int power,int hits){int bonus=class_field_bonus48(g,attack);return power*(class_element_rate48(m,attack)+bonus)/100+(hits>1?power*(class_element_base48(m,attack)+bonus)*(hits-1)/100:0);}
static int class_field_at48(const Combat*g,int id,float x,float y);
static void class_tick48(Combat*g);
static void class_magic_tick48(Combat*g);
static int class_guard48(Combat*g,int mob);
static void class_autospell48(Combat*g,int target);
static int class_rank48(const Combat*g,int id){return id>=89&&id<127?g->ranks[id-3]:0;}
static int class_active48(const Combat*g,int id){return id>=89&&id<127&&g->classUntil48[id-89]>g->time?g->classLevel48[id-89]:0;}
static int class_ice_block48(const Combat*g,float x,float y){for(int i=0;i<3;i++){const ClassArea48*a=&g->classAreas48[i];if(a->id!=89||a->until<=g->time||a->map!=g->mapId)continue;for(int c=0;c<5;c++)if(a->hp[c]>0&&fabsf(x-a->x-(a->axis?0:(c-2)*8))<5&&fabsf(y-a->y-(a->axis?(c-2)*8:0))<5)return 1;}return 0;}
/* Closed segment/AABB test against the original five occupied Ice Wall cells. */
static int class_ice_line_mode200(const Combat*g,float x,float y,float tx,float ty,int allowEnd){if(!isfinite(x)||!isfinite(y)||!isfinite(tx)||!isfinite(ty))return 0;for(int i=0;i<3;i++){const ClassArea48*a=&g->classAreas48[i];if(a->id!=89||a->until<=g->time||a->map!=g->mapId)continue;for(int c=0;c<5;c++)if(a->hp[c]>0){float cx=a->x+(a->axis?0:(c-2)*8),cy=a->y+(a->axis?(c-2)*8:0),low=0,high=1;if(allowEnd&&fabsf(tx-cx)<=4&&fabsf(ty-cy)<=4)continue;int blocked=1;for(int axis=0;axis<2;axis++){float start=axis?y:x,delta=axis?ty-y:tx-x,mid=axis?cy:cx;if(fabsf(delta)<.00001f){if(start<mid-4||start>mid+4){blocked=0;break;}}else{float b=(mid-4-start)/delta,e=(mid+4-start)/delta;if(b>e){float t=b;b=e;e=t;}if(b>low)low=b;if(e<high)high=e;if(low>high){blocked=0;break;}}}if(blocked)return 0;}}return 1;}
static int class_ice_line48(const Combat*g,float x,float y,float tx,float ty){return class_ice_line_mode200(g,x,y,tx,ty,0);}
static int stat_job_bonus48(const Combat*g,int n){if((unsigned)n>=6)return 0;unsigned job=job_valid52(g->jobId)?g->jobId:0;int lv=g->joblevel,cap=progression_job_cap43(job);if(lv<1)lv=1;if(lv>cap)lv=cap;return jobBonus52[job][lv-1][n];}
static int stat_value(const Combat*g,int n){int base=g->stats[n]+stat_job_bonus48(g,n);if(g->jobId==J52_SUPER_NOVICE&&g->joblevel>=70&&!g->died53)base+=10;if(n==0&&job_parent52(g->jobId)==19&&class_rank50(g,225))base++;if(n==5&&class_active50(g,193))base+=30;if(n==3&&job_parent52(g->jobId)==10)base+=(class_rank48(g,100)+1)/2;if((job_first50(g->jobId)==5||g->jobId==J52_SUPER_NOVICE)&&n==4)base+=g->ranks[11];if(n==0&&g->class50.chaseStrengthUntil52>g->time)base+=g->class50.chaseStrength52;static const unsigned bonus[6]={B52_bStr,B52_bAgi,B52_bVit,B52_bInt,B52_bDex,B52_bLuk};int total=base+g->itemBonuses52.scalar[bonus[n]]+g->itemBonuses52.scalar[B52_bAllStats]+(class_active50(g,SK52_SN_SIGHT)?5:0);if(n==0||n==3)total+=class_active50(g,SK60_NJ_NEN);if(n==0&&g->class50.spurtUntil60>g->time)total+=10;if((n==1||n==4)&&class_active50(g,SK60_GS_INCREASING))total+=4;if(n==0&&g->uproarLeft>0)total+=4;if(g->concentrateLeft>0&&(n==1||n==4))total+=base*(2+g->concentrateRank)/100;if(g->buffs[0]>0&&(n==0||n==3||n==4))total+=g->buffLevels[0]?g->buffLevels[0]:10;if(g->buffs[1]>0&&n==1)total+=g->buffLevels[1]?g->buffLevels[1]:12;return total;}
/* Resource ceiling leaves all existing percentage/skill intermediates within signed32;
 * max-resource formulas use64-bit before clamping. */
#define PLAYER_RESOURCE_CAP53 20000000
static int resource_clamp53(int64_t n){return n<1?1:n>PLAYER_RESOURCE_CAP53?PLAYER_RESOURCE_CAP53:(int)n;}
static int stat_maxhp(const Combat*g){int64_t n=solojobHP52[job_valid52(g->jobId)?g->jobId:0][g->level-1];if(g->jobId==J52_SUPER_NOVICE&&g->level>=99)n+=2000;if(job_transcendent52(g->jobId))n+=n/4;int64_t hp=n+n*stat_value(g,2)/100+(job_parent52(g->jobId)==11?200*class_rank48(g,115):0);hp+=g->itemBonuses52.scalar[B52_bMaxHP];hp=hp*(100+(int64_t)g->itemBonuses52.scalar[B52_bMaxHPrate])/100;if(class_active50(g,SK52_LK_BERSERK))hp*=3;return resource_clamp53(hp);}
static int stat_maxsp(const Combat*g){int64_t n=solojobSP52[job_valid52(g->jobId)?g->jobId:0][g->level-1];if(job_transcendent52(g->jobId))n+=n/4;n+=n*stat_value(g,3)/100;if(g->jobId==8)n+=n*2*g->ranks[81]/100;n+=30*class_rank50(g,SK60_SL_KAINA);n+=g->itemBonuses52.scalar[B52_bMaxSP];n=n*(100+(int64_t)g->itemBonuses52.scalar[B52_bMaxSPrate]+class_rank50(g,SK52_HP_MEDITATIO))/100;return resource_clamp53(n);}
static void inventory_reconcile46(Combat*g);
static void stat_refresh(Combat*g){inventory_reconcile46(g);g->maxhp=stat_maxhp(g);g->maxsp=stat_maxsp(g);if(g->hp>g->maxhp)g->hp=g->maxhp;if(g->sp>g->maxsp)g->sp=g->maxsp;}
static int stat_cost(const Combat*g,int n){return 1+(g->stats[n]+9)/10;}
static int stat_spent(const unsigned char*s){int total=0;for(int n=0;n<6;n++)for(int v=1;v<s[n];v++)total+=1+(v+9)/10;return total;}
static int stat_budget(int level){if(level<1)level=1;if(level>TEST_LEVEL_CAP)level=TEST_LEVEL_CAP;return soloStatBudget53[level-1]+(level==TEST_LEVEL_CAP?2:0);}
static int stat_total48(const Combat*g){return stat_budget(g->level)+(job_transcendent52(g->jobId)?52:0);}
static int stat_raise(Combat*g,int n){if(n<0||n>=6||g->stats[n]>=SOLO_STAT_CAP53||g->statPoints<stat_cost(g,n))return 0;g->statPoints-=stat_cost(g,n);g->stats[n]++;stat_refresh(g);return 1;}
static float inventory_cart_speed(const Combat*g);
static float combat_walk_speed(const Combat*g){return (class_active50(g,SK52_LK_BERSERK)?1.25f:1.f)* class_walk_rate50(g)*inventory_cart_speed(g)*(class_active48(g,124)?.6666667f:1.f)*(g->mounted48?1.25f:1.f)*.765f*(g->walkPercent?g->walkPercent:84)*(g->buffs[1]>0?1.25f:1.f);}
static int inventory_wtype46(const Combat*g);
static int stat_amotion48(const Combat*g){int weapon=inventory_wtype46(g);if(weapon<0||weapon>22)weapon=0;int d=g->jobId>=21?jobMotion52[job_valid52(g->jobId)?g->jobId:0][weapon]:g->jobId>=12?classMotion50[g->jobId-12][weapon]:baseMotion48[g->jobId][weapon>12?0:weapon];d-=d*(4*stat_value(g,1)+stat_value(g,4))/1000;int rate=1000-10*g->itemBonuses52.scalar[B52_bAspdRate];d-=10*g->itemBonuses52.scalar[B52_bAspd];if(class_active50(g,207))rate+=250;if(g->mounted48)rate+=500-100*class_rank48(g,113);if(g->quickenLeft>0&&(g->equipment&32))rate-=300;if(class_active50(g,SK52_LK_BERSERK))rate-=300;if(weapon==11)rate-=5*class_rank48(g,90);if(weapon==5&&class_active48(g,125))rate-=200+10*class_active48(g,125);if(class_active48(g,124))rate+=250-50*class_active48(g,124);if(class_active50(g,231)&&(weapon==6||weapon==7||weapon==8))rate-=300;if(weapon>=17&&weapon<=21)rate-=10*((class_rank50(g,SK60_GS_SINGLEACTION)+1)/2);if(class_active50(g,SK60_GS_MADNESSCANCEL))rate-=200;rate-=20*class_active50(g,SK60_GS_GATLINGFEVER);if(class_active50(g,SK60_SG_STAR_COMFORT))rate-=g->level+stat_value(g,4)+stat_value(g,5);if(g->jobId==J60_STAR_GLADIATOR&&g->joblevel>=50)rate-=30*class_rank50(g,SK60_SG_DEVIL);d=d*rate/1000;if(g->spellCastLeft>0&&class_rank48(g,94))d=d*100/(50+5*class_rank48(g,94));if(d<30)d=30;if(d>2000)d=2000;return d;}
static float stat_attack_delay(const Combat*g){return stat_amotion48(g)*.002f;}
static int combat_aspd48(const Combat*g){return 2000-stat_amotion48(g);}
static int combat_mdef48(const Combat*g){return class_active50(g,207)?90:g->itemBonuses52.scalar[B52_bMdef];} /* Current safe catalog has no MDEF scripts. */
static int combat_mdef_soft48(const Combat*g){return stat_value(g,3)+stat_value(g,2)/2;}
static int combat_reduce48(int damage,int hard,int soft){if(hard<0)hard=0;if(hard>100)hard=100;damage=damage*(100-hard)/100-soft;return damage<1?1:damage;}

static const char*job_name(unsigned id){static const char*expanded[]={"Ninja","Gunslinger","Taekwon","Star Gladiator","Soul Linker"};if(id>=J60_NINJA&&id<J52_COUNT)return expanded[id-J60_NINJA];static const char*trans[]={"Lord Knight","Paladin","Professor","High Priest","Champion","Assassin Cross","Stalker","Sniper","Clown","Gypsy","Whitesmith","Creator","High Novice","High Swordsman","High Mage","High Acolyte","High Thief","High Archer","High Merchant"};if(id==J52_SUPER_NOVICE)return "Super Novice";if(id>=21&&id<J52_SUPER_NOVICE)return trans[id-21];static const char*added[]={"Assassin","Rogue","Hunter","Bard","Dancer","Priest","Monk","Blacksmith","Alchemist"};if(id>=12&&id<=20)return added[id-12];return id==9?"Wizard":id==10?"Sage":id==11?"Crusader":id==7?"Knight":id==8?"High Wizard":id==1?"Swordsman":id==2?"Mage":id==3?"Acolyte":id==4?"Thief":id==5?"Archer":id==6?"Merchant":"Novice";}
static int job_cap(const Combat*g){return progression_job_cap43(g->jobId);}
static int job_next(const Combat*g){return g->joblevel<job_cap(g)?progression_job_curve43(g->jobId)[g->joblevel-1]:0;}
/* Stable ordered fixed queue: a future second hit never blocks immediate sounds. */
static void combat_sound_at(Combat*g,unsigned id,float delay){unsigned n=g->soundWrite-g->soundRead;if(n>=32)return;float due=g->time+delay;unsigned j=n;while(j&&due<g->soundDue[(g->soundRead+j-1)%32]){unsigned a=(g->soundRead+j)%32,b=(g->soundRead+j-1)%32;g->soundEvents[a]=g->soundEvents[b];g->soundDue[a]=g->soundDue[b];j--;}unsigned a=(g->soundRead+j)%32;g->soundEvents[a]=id;g->soundDue[a]=due;g->soundWrite++;}
static float combat_attack_delay42(const Combat*g){(void)g;return .020f;}
static void combat_sound(Combat*g,unsigned id){combat_sound_at(g,id,id==0?combat_attack_delay42(g):0);}
/* Source SkillEffect.hideCastAura exceptions among implemented jobs. */
static int skill_cast_aura49(unsigned id){return id!=56&&id!=59&&id!=70&&id!=71&&id!=87&&id!=173&&id!=180;}
static unsigned skill_sound_id49(unsigned skill){return skill==23?52:skill==48?53:skill==116?54:skill==22||skill==88?55:skill==78?56:skill==75?57:skill==86?59:0;}
/* The original fire/ice hit samples are alternatives, not simultaneous layers.
 * Esma's source effect repeats five times at200ms. Cosmetic choice never uses
 * the gameplay RNG and duplicate cast notifications select the same variant. */
static void class_sound_emit50(Combat*g,unsigned skill){for(unsigned i=0;i<sizeof(classSoundSkills50)/sizeof(*classSoundSkills50);i++){const ClassSoundSkill50*s=&classSoundSkills50[i];if(s->skill!=skill)continue;unsigned first=0,last=s->count;if((skill==SK60_NJ_KOUENKA||skill==SK60_NJ_HYOUSENSOU)&&last){first=((unsigned)fmodf(g->time*1000.f,65521.f)+skill*17)%last;last=first+1;}for(unsigned copy=0;copy<(skill==SK60_SL_SMA?5u:1u);copy++)for(unsigned n=first;n<last;n++){float delay=s->delayMS[n]/1000.f+copy*.2f,due=g->time+delay;int duplicate=0;for(unsigned q=g->soundRead;q!=g->soundWrite;q++)if(g->soundEvents[q%32]==s->ids[n]&&fabsf(g->soundDue[q%32]-due)<.00001f)duplicate=1;if(!duplicate)combat_sound_at(g,s->ids[n],delay);}return;}}

static void skill_sound49(Combat*g,unsigned skill){if(skill>=127||skill==7){class_sound_emit50(g,skill);return;}combat_sound(g,skill_sound_id49(skill));}
static int combat_next_sound(Combat*g,unsigned*id){if(g->soundRead==g->soundWrite||g->soundDue[g->soundRead%32]>g->time+.00001f)return 0;*id=g->soundEvents[g->soundRead++%32];return 1;}
static void combat_hit_sound(Combat*g,int hits){if(hits<1)hits=1;if(hits>10)hits=10;for(int j=0;j<hits;j++)combat_sound_at(g,0,combat_attack_delay42(g)+.2f*j);}
static int combat_mob_max(const CombatMob*m){return m->training?m->testMaxHP:mobSpecs[m->kind].hp;}
static int combat_bane_target(const CombatMob*m){return m->training&&m->testTraits?m->testTraits==1||m->testTraits==2:mobBaneTarget[m->kind];}
static int combat_signum_target(const CombatMob*m){return m->training&&m->testTraits?m->testTraits==1||m->testTraits==2:mobSignumTarget[m->kind];}
static int combat_status_boss(const CombatMob*m){if(combat_racer_kind164(m->kind))return 1;return m->training&&m->testTraits?m->testTraits==3:mobUtility[m->kind].blocked;}
static int combat_enemy_defense(const CombatMob*m){int defense=mobSpecs[m->kind].defense;defense=defense*(100+m->class50.tarotDef52)/100;if(m->class50.eskaUntil60>0)return m->class50.eskaDefense60;if(m->class50.eskeUntil60>0)defense/=2;if(m->class50.gospelDef52>0)return 0;if(m->class50.jointUntil52[3]>0||m->class50.jointUntil52[4]>0)defense-=defense*((m->class50.jointUntil52[3]>0?50:0)+(m->class50.jointUntil52[4]>0?25:0))/100;if(m->class50.flingUntil60>0)defense=defense*(100-5*m->class50.flingCoins60)/100;if(m->stoneLeft>0)defense/=2;if(m->provokeLeft>0)defense-=defense*(5+5*m->provokeRank)/100;if(m->crucisRank)defense-=defense*(10+4*m->crucisRank)/100;if(m->class50.stripUntil[1]>0)defense=defense*85/100;return defense;}
static int combat_gravitation_slow52(const Combat*,const CombatMob*);
static float combat_enemy_delay164(const Combat*g,const CombatMob*m){return mobSpecs[m->kind].delay*(100+combat_gravitation_slow52(g,m)+(m->class50.eskaUntil60>g->time?25:0)+(m->class50.gospelSlow52>g->time?25:0)+(m->class50.jointUntil52[1]>g->time?25:0)+(m->class50.jointUntil52[2]>g->time?10:0))/100*(m->class50.danceUntil>g->time?(100+m->class50.danceAttack)/100.f:1.f);}
static int combat_enemy_power(const CombatMob*m,int damage){if(m->class50.gospelAtk52>0)return 0;if(m->class50.eskeUntil60>0)damage*=4;damage=damage*(100+m->class50.tarotAtk52)/100;if(m->class50.curseUntil52>0)damage-=damage/4;if(m->class50.jointUntil52[4]>0)damage-=damage/4;if(m->class50.stripUntil[0]>0)damage=damage*75/100;return m->provokeLeft>0?damage*(102+3*m->provokeRank)/100:damage;}
static int combat_hit_bonus50(Combat*g,CombatMob*m,int damage){if(damage>0&&m->class50.lexUntil>g->time){m->class50.lexUntil=0;return damage>1000000000?2000000000:damage*2;}return damage;}
static void combat_enemy_damage(Combat*g,CombatMob*m,int damage){if(combat_racer_kind164(m->kind))return;if(damage>0){if(g->class50.homunDealing&&m->hp>0)m->class50.homunDamage+=damage>m->hp?m->hp:damage;m->class50.charmUntil=0;m->class50.sleepUntil=0;m->frozenLeft=0;if(m->stoneLeft>0){m->stoneNotice=3;m->stoneNoticeUntil=g->time+2.5f;}m->stoneLeft=m->stoneTick=0;m->hidden=0;}if(m->training&&g->debugImmortal&&damage>=m->hp)m->hp=1;else m->hp-=damage;}

static float combat_safety_center(float value){return value;}
static int combat_safety_cell(float a,float b){return (int)floorf(a/8)==(int)floorf(b/8);}
static int combat_safety_live(const Combat*g,int i){const SafetyWall*w=&g->safety[i];return g->hp>0&&w->expires>g->time&&w->hits>0;}
/* Single authority for HUD footprint/protection and actual incoming damage. */
static int combat_safety_at(const Combat*g,float x,float y){for(int i=0;i<3;i++){const SafetyWall*w=&g->safety[i];if(combat_safety_live(g,i)&&(w->x-x)*(w->x-x)+(w->y-y)*(w->y-y)<=SAFETY_RADIUS*SAFETY_RADIUS)return i;}return -1;}
static int combat_safety_near(const Combat*g){int at=combat_safety_at(g,g->x,g->y);if(at>=0)return at;float distance=32*32;for(int i=0;i<3;i++)if(combat_safety_live(g,i)){float dx=g->safety[i].x-g->x,dy=g->safety[i].y-g->y,d=dx*dx+dy*dy;if(d<distance){distance=d;at=i;}}return at;}

static int combat_safety_slot(const Combat*g,float x,float y){int slot=-1;for(int i=0;i<3;i++){const SafetyWall*w=&g->safety[i];if(w->expires>g->time&&w->hits>0){if((w->x-x)*(w->x-x)+(w->y-y)*(w->y-y)<1)return -2;}else if(slot<0)slot=i;}return slot;}
/* Only call for short-range physical damage; future magic/ranged paths bypass this. */
static int combat_safety_block(Combat*g){int i=combat_safety_at(g,g->x,g->y);if(i<0)return 0;SafetyWall*w=&g->safety[i];w->hits--;w->blockedUntil=g->time+.65f;combat_guard_number53(g);return 1;}
static void combat_stone_tick(Combat*g,CombatMob*m,float dt){
 if(m->hp<=0){m->stoneWait=m->stoneLeft=m->stoneTick=m->stoneNoticeUntil=0;m->stoneNotice=0;return;}
 if(m->stoneWait>0){m->stoneWait-=dt;if(m->stoneWait>0)return;dt=-m->stoneWait;m->stoneWait=0;m->stoneLeft=20;m->stoneTick=0;m->stoneNotice=0;m->moving=0;}
 if(m->stoneLeft>0){float elapsed=dt<m->stoneLeft?dt:m->stoneLeft;m->stoneLeft-=elapsed;m->stoneTick+=elapsed;
 if(m->stoneTick>=5){m->stoneTick-=5;int maxhp=combat_mob_max(m),floor=maxhp/4,loss=maxhp/100;if(loss<1)loss=1;if(loss>m->hp-floor)loss=m->hp-floor;if(loss>0)m->hp-=loss;}if(m->stoneLeft<=0)m->stoneLeft=m->stoneTick=0;}
}
static void combat_spawn_position(Combat*g,CombatMob*m);
static unsigned combat_random(Combat*g){g->rng=g->rng*1664525u+1013904223u;return g->rng^(g->rng>>16);}
#include "taekwon_mission60.h"
#include "expanded_rules60.h"
static float combat_dist(float ax,float ay,float bx,float by){float x=ax-bx,y=ay-by;return sqrtf(x*x+y*y);}
enum{POP_DAMAGE=1,POP_REWARDS=2,POP_SKILLS=4,POP_ITEMS=8,POP_SYSTEM=16,POP_SPEECH=32,POP_LOOT=64,POP_ALL=127};
static int combat_popup_visible(const Combat*g){return g->logIsTip?!g->tooltipsDisabled:!(g->popupDisabled&g->logCategory);}
static void combat_notice(Combat*g,unsigned category,const char*fmt,...){g->logIsTip=0;g->logCategory=category;va_list a;va_start(a,fmt);vsnprintf(g->log,sizeof(g->log),fmt,a);va_end(a);}
static void combat_message(Combat*g,const char*fmt,...){g->logIsTip=0;g->logCategory=POP_SYSTEM;va_list a;va_start(a,fmt);vsnprintf(g->log,sizeof(g->log),fmt,a);va_end(a);}
static void combat_tip(Combat*g,const char*fmt,...){g->logIsTip=1;va_list a;va_start(a,fmt);vsnprintf(g->log,sizeof(g->log),fmt,a);va_end(a);}

static int combat_casting(const Combat*g){return g->spellCastLeft>0||g->coatCastLeft>0;}
static void combat_interrupt_cast(Combat*g){if(combat_casting(g)){g->spellCastLeft=g->coatCastLeft=0;g->spellCastId=0;g->spellCastFriendly200=g->spellCastFriendlyLife200=0;combat_message(g,"Casting interrupted; casting resources kept.");}}
static void combat_damage_interrupt_cast(Combat*g){if(g->spellCastInterruptible&&!g->itemBonuses52.scalar[B52_bNoCastCancel])combat_interrupt_cast(g);}
#include "ground_state58.h"
#include "inventory.h"
static void skill_cast_tick(Combat*g,float dt);
static int skill_approach_tick53(Combat*g,float dt);
#define COMBAT_ATTACK_ANIMATION53 .45f
static void skill_burst_tick49(Combat*g);
static int skill_burst_slot49(const Combat*g);
static void skill_hit_ex(Combat*g,int i,int damage,int stun,int hits);
static void skill_stagger49(Combat*g,CombatMob*m);

static int combat_position_valid(WorldPosition p){return p.map<MYRO_MAP_COUNT43&&isfinite(p.x)&&isfinite(p.y)&&p.x>=8&&p.y>=8&&p.x<mapWidth43[p.map]-8&&p.y<mapHeight43[p.map]-8;}
static int combat_pneuma_at(const Combat*g,float x,float y){for(int i=0;i<3;i++){const PneumaField*p=&g->pneuma[i];if(p->expires>g->time&&combat_dist(x,y,p->x,p->y)<=PNEUMA_RADIUS)return i;}return -1;}
static int combat_pneuma_slot(const Combat*g,float x,float y){int slot=-1;for(int i=0;i<3;i++){const PneumaField*p=&g->pneuma[i];if(p->expires>g->time){if(combat_dist(x,y,p->x,p->y)<PNEUMA_RADIUS*2)return -2;}else if(slot<0)slot=i;}return slot;}
static int combat_portal_slot(const Combat*g){for(int i=0;i<3;i++)if(g->portals[i].expires<=g->time||!g->portals[i].uses)return i;return -1;}
static int combat_portal_near(const Combat*g){if(g->hp<=0)return -1;for(int i=0;i<3;i++)if(g->portals[i].expires>g->time&&g->portals[i].uses&&combat_dist(g->x,g->y,g->portals[i].x,g->portals[i].y)<=10)return i;return -1;}
/* Shared future long-range physical-hit entry. Damage is post-defence; magic bypasses Pneuma. */
static int combat_ranged_hit_from52(Combat*g,int damage,int source){if(g->hp<=0||damage<1||g->debugPlayerInvincible52||g->trickDead55)return 0;if(class_active50(g,SK52_HP_BASILICA)&&(source<0||!combat_status_boss(&g->mobs[source])))return 0;if(class_fog_at52(g,g->x,g->y))damage/=4;int defender48=class_active48(g,124);if(defender48)damage=damage*(95-15*defender48)/100;if(combat_pneuma_at(g,g->x,g->y)>=0){combat_message(g,"Pneuma blocked a ranged physical hit.");return 0;}if(g->buffs[2]>0&&g->shieldHits>0&&g->shieldHP>0){int absorbed=damage<g->shieldHP?damage:g->shieldHP;g->shieldHP-=absorbed;g->shieldHits--;damage-=absorbed;if(!g->shieldHP||!g->shieldHits)g->buffs[2]=0;}damage=class_received50(g,source,damage,1);damage=inventory_energy_hit(g,damage);if(damage>g->hp)damage=g->hp;if(damage){combat_damage_interrupt_cast(g);g->hp-=damage;item_proc_event52(g,2,source,damage,0);g->hurtAt=g->lastDamage=g->time;g->sitting=0;g->hideLeft=0;g->hitStun=.12f;combat_received_number53(g,damage,1);}if(!g->hp&&!soullinker_revive60(g)){g->deadAt=g->time;g->autoAttack=0;combat_support_clear(g);}combat_notice(g,POP_DAMAGE,"Ranged physical hit: %d damage.",damage);return damage;}
static int combat_ranged_hit(Combat*g,int damage){return combat_ranged_hit_from52(g,damage,-1);}

static void combat_memorize(Combat*g){if(!g->ranks[50]){combat_message(g,"Learn Warp Portal before memorizing a location.");return;}WorldPosition p={g->mapId,g->x,g->y};if(!combat_position_valid(p)){combat_message(g,"Cannot remember this location.");return;}for(unsigned i=0;i<g->memoCount;i++)if(g->memos[i].map==p.map){g->memos[i]=p;combat_message(g,"Updated memorized location %u.",i+1);return;}if(g->memoCount<3)g->memos[g->memoCount++]=p;else{g->memos[0]=g->memos[1];g->memos[1]=g->memos[2];g->memos[2]=p;}combat_message(g,"Location remembered. Warp rank limits available destinations.");}

static float combat_attack_range(const Combat*g){int w=inventory_wtype46(g);if(w>=17&&w<=21){const EquipmentRule52*r=equipment_rule52(itemDefs[inventory_slot46(g,0)].id);return((r?r->range:7)+class_rank50(g,SK60_GS_SNAKEEYE))*8.f;}return g->equipment&16?72.f+8*g->ranks[12]:(inventory_wtype46(g)==4||inventory_wtype46(g)==5)?24.f:14.f;}
static int combat_berserk_active(const Combat*g){return (g->jobId==1||g->jobId==7||job_parent52(g->jobId)==11)&&g->ranks[42]&&g->autoBerserk&&g->hp>0&&g->hp*4<g->maxhp;}
static int combat_base_atk48(const Combat*g){int w=inventory_wtype46(g),n=(g->equipment&16)||(w>=17&&w<=21)?4:0,a=stat_value(g,n),b=stat_value(g,n==4?0:4);return a+(a/10)*(a/10)+b/5+stat_value(g,5)/5+(w==0?10*class_rank50(g,SK60_TK_RUN):0)+(class_active50(g,SK60_GS_MADNESSCANCEL)?100:0)+(class_active50(g,SK60_GS_GATLINGFEVER)?20+10*class_active50(g,SK60_GS_GATLINGFEVER):0);}
static int combat_physical(const Combat*g){int power=combat_base_atk48(g)+inventory_attack(g)+(class_active50(g,187)?5*class_active50(g,187):0);power=power*(100+g->itemBonuses52.scalar[B52_bAtkRate]+5*class_active50(g,SK52_LK_CONCENTRATION))/100;return combat_berserk_active(g)?power*132/100:power;}
static int combat_matk_min48(const Combat*g){int n=stat_value(g,3);return inventory_matk46(g,n+(n/7)*(n/7));}
static int combat_matk_max48(const Combat*g){int n=stat_value(g,3);return inventory_matk46(g,n+(n/5)*(n/5));}
static int combat_magic_power48(Combat*g){int low=combat_matk_min48(g),high=combat_matk_max48(g);return low+(high>low?(int)(combat_random(g)%(unsigned)(high-low+1)):0);}
static int combat_magic_def48(const CombatMob*m,int damage,int hits){int k=m->kind,hard=m->stoneLeft>0?mobFreezeMdef[k]*125/100:mobFreezeMdef[k],soft=mobInt48[k]*(m->class50.stripUntil[3]>0?60:100)/100+mobStunVit[k]*(m->class50.stripUntil[2]>0?60:100)/200;if(m->class50.mindUntil52>0)soft-=soft*12*m->class50.mindRank52/100;if(m->class50.eskaUntil60>0)soft=90;if(hits<1)hits=1;return combat_reduce48(damage/hits,hard,soft)*hits;}
static int combat_magic_def52(const Combat*g,const CombatMob*m,int damage,int hits){int k=m->kind,hard=m->stoneLeft>0?mobFreezeMdef[k]*125/100:mobFreezeMdef[k],soft=mobInt48[k]*(m->class50.stripUntil[3]>0?60:100)/100+mobStunVit[k]*(m->class50.stripUntil[2]>0?60:100)/200;int race=mobClassData50[k][0],ignore=g->itemBonuses52.scalar[B52_bIgnoreMdefRate]+item_bonus_match52(g,B52_bIgnoreMdefRate,race,-1)+item_bonus_match52(g,B52_bIgnoreMdefRate,item_boss_key52(m),-1);if(ignore>100)ignore=100;if(g->itemBonuses52.scalar[B52_bIgnoreMdefRace]&item_target_races52(m))hard=soft=0;else hard=hard*(100-ignore)/100;if(m->class50.mindUntil52>g->time)soft-=soft*12*m->class50.mindRank52/100;if(m->class50.eskaUntil60>g->time)soft=90;if(hits<1)hits=1;damage=item_magic_bonus52(g,m,damage,(unsigned)g->fxSkill);return combat_reduce48(damage/hits,hard,soft)*hits;}


/* Source attack motion precedes projectile travel; impact is resolved once. */
static void combat_shot_begin45(Combat*g,CombatMob*m,int damage){if(mobSpecs[m->kind].id==1830){for(unsigned i=0;i<3;i++){GuardianShot164*p=m->arrows164+i;if(p->phase)continue;float launch=g->time+mobSpecs[m->kind].motion;*p=(GuardianShot164){m->x,m->y,g->x,g->y,launch,launch+fmaxf(.12f,fminf(.45f,combat_dist(m->x,m->y,g->x,g->y)/240.f)),damage,1,g->mapId,m->life};return;}combat_ranged_hit_from52(g,damage,(int)(m-g->mobs));return;}m->shotFromX45=m->x;m->shotFromY45=m->y;m->shotToX45=g->x;m->shotToY45=g->y;m->shotLaunch45=g->time+mobSpecs[m->kind].motion;m->shotImpact45=m->shotLaunch45+fmaxf(.12f,fminf(.45f,combat_dist(m->x,m->y,g->x,g->y)/240.f));m->shotDamage45=damage;m->shotPhase45=1;}
static void combat_shot_tick45(Combat*g,CombatMob*m){for(unsigned i=0;i<3;i++){GuardianShot164*p=m->arrows164+i;if(!p->phase)continue;if(g->hp<=0||p->map!=g->mapId||p->life!=m->life){p->phase=0;continue;}if(p->phase==1){if(m->hp<=0||m->stun>0||m->frozenLeft>0||m->stoneLeft>0){p->phase=0;continue;}if(g->time>=p->launch)p->phase=2;}if(p->phase==2&&g->time>=p->impact){int damage=p->damage;p->phase=0;combat_ranged_hit_from52(g,damage,(int)(m-g->mobs));}}
if(!m->shotPhase45)return;if(m->shotPhase45==3&&g->time>m->shotImpact45+.35f){m->shotPhase45=0;return;}if(g->hp<=0){m->shotPhase45=0;return;}if(m->shotPhase45==1){if(m->hp<=0||m->stun>0||m->frozenLeft>0||m->stoneLeft>0){m->shotPhase45=0;return;}if(g->time>=m->shotLaunch45)m->shotPhase45=2;}if(m->shotPhase45==2&&g->time>=m->shotImpact45){int damage=m->shotDamage45;m->shotPhase45=3;combat_ranged_hit_from52(g,damage,(int)(m-g->mobs));}}
static int combat_move(Combat*g,float*x,float*y,float nx,float ny){
 if(class_ice_block48(g,nx,ny)&&!class_ice_block48(g,*x,*y))return 0;int moved=0;if(!g->canMove||g->canMove(g->world,*x,*y,nx,*y)){moved|=nx!=*x;*x=nx;}
 if(!g->canMove||g->canMove(g->world,*x,*y,*x,ny)){moved|=ny!=*y;*y=ny;}return moved;
}
static void combat_face(float*fx,float*fy,float dx,float dy){float d=sqrtf(dx*dx+dy*dy);if(d>.001f){*fx=dx/d;*fy=dy/d;}}
#include "player_route53.h"
#include "ground_loot58.h"
#include "mob_route53.h"
static int combat_gravitation_slow52(const Combat*g,const CombatMob*m){if(combat_status_boss(m))return 0;int rank=0;for(unsigned i=0;i<CLASS_AREAS50;i++){const ClassArea50*a=g->areas50+i;if(a->id==SK52_HW_GRAVITATION&&a->map==g->mapId&&a->until>g->time&&fabsf(m->x-a->x)<20&&fabsf(m->y-a->y)<20&&a->rank>rank)rank=a->rank;}return 5*rank;}
static int combat_mob_move52(Combat*g,CombatMob*m,float nx,float ny){if(m->class50.webRoot52&&m->class50.webUntil52>g->time)return 0;int slow=(m->class50.swooUntil60>g->time?300:0)+(m->class50.suitonUntil60>g->time?50:0)+combat_gravitation_slow52(g,m)+(m->class50.curseUntil52>g->time?300:0)+(m->class50.eskaUntil60>g->time?25:0)+(m->class50.gospelSlow52>g->time?25:0)+(m->class50.jointUntil52[0]>g->time?50:0)+(m->class50.jointUntil52[2]>g->time?30:0);if(slow){nx=m->x+(nx-m->x)*100/(100+slow);ny=m->y+(ny-m->y)*100/(100+slow);}if(class_active50(g,SK52_HP_BASILICA)&&!combat_status_boss(m)&&fabsf(nx-g->class50.basilicaX52)<20&&fabsf(ny-g->class50.basilicaY52)<20)return 0;float step=combat_dist(m->x,m->y,nx,ny);if(m->routeDetour53&&m->aggro){if(player_route_clear53(g,m->x,m->y,g->x,g->y))m->routeDetour53=0;else{if(!mob_flow_step53(g,m,step,&nx,&ny))return 0;float fx=nx-m->x,fy=ny-m->y;int moved=combat_move(g,&m->x,&m->y,nx,ny);if(moved)combat_face(&m->faceX,&m->faceY,fx,fy);return moved;}}if(combat_move(g,&m->x,&m->y,nx,ny))return 1;if(m->aggro)m->routeDetour53=1;if(m->aggro&&mob_flow_step53(g,m,step,&nx,&ny)){float fx=nx-m->x,fy=ny-m->y;int moved=combat_move(g,&m->x,&m->y,nx,ny);if(moved)combat_face(&m->faceX,&m->faceY,fx,fy);return moved;}return 0;}
static void combat_init(Combat*g,float x,float y,CombatCanMove move,void*world){
 memset(g,0,sizeof(*g));ground_clear58();g->floorTarget58=g->floorPickup58=-1;g->sex55=1;memcpy(g->name56,"Novice",7);g->monsterView52=MONSTER_VIEW_DEFAULT53;g->home=(WorldPosition){2,1244,1476};g->debugImmortal=1;g->hotAttack=1;g->walkPercent=100;g->attackSoundDelayMs=20;g->successCircleDiameter=32;g->popupDisabled=POP_DAMAGE;g->rbBinding=BIND_EMPTY50;memset(g->stats,1,6);g->statPoints=stat_budget(1);g->x=g->campX=x;g->y=g->campY=y;g->faceY=1;g->level=g->joblevel=1;
 g->hp=g->maxhp=stat_maxhp(g);g->sp=g->maxsp=stat_maxsp(g);g->apples=3;g->target=-1;g->rng=0x4d79524f;g->canMove=g->canAim=move;g->world=world;
 inventory_starter(g);
 {const SkillBinding50 bar[12]={BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50,BIND_EMPTY50};memcpy(g->hotbar,bar,sizeof(bar));}g->guardFxAt49=-1000;g->lastCast=g->fxAt=-100;
 g->attackAt=g->hurtAt=g->deadAt=-100;
 for(int i=0;i<8;i++){
  CombatMob*m=&g->mobs[i];m->enabled=1;m->spawnDef=-1;m->kind=i<4?0:1;m->faceY=1;m->attackAt=m->hurtAt=m->deadAt=-100;
  // Bounded search for distinct nearby spawns reachable from camp.
  float bestX=x,bestY=y;int found=0;
  for(int k=0;k<160&&!found;k++){
   float a=(i*2.399963f+k*.61f),r=32+(k%6)*12;float nx=x+cosf(a)*r,ny=y+sinf(a)*r;
   int ok=1;if(move)for(int j=1;j<=24;j++)if(!move(world,x+(nx-x)*(j-1)/24,y+(ny-y)*(j-1)/24,x+(nx-x)*j/24,y+(ny-y)*j/24)){ok=0;break;}
   for(int j=0;j<i&&ok;j++)if(combat_dist(nx,ny,g->mobs[j].x,g->mobs[j].y)<14)ok=0;
   if(ok){bestX=nx;bestY=ny;found=1;}
  }
  m->x=m->homeX=bestX;m->y=m->homeY=bestY;m->hp=mobSpecs[m->kind].hp;m->wanderAt=1+i*.3f;
 }
 combat_message(g,"R3: nearest. X: nearer, Y: farther. A: attack.");
}
static void combat_spawn_position(Combat*g,CombatMob*m){
 const SpawnDef*d=&spawnDefs[m->spawnDef];
 for(int k=0;k<2000;k++){
  int cellx=d->x?d->x+(int)(combat_random(g)%(d->rx*2+1))-d->rx:1+combat_random(g)%(mapWidth43[g->mapId]/8-2);
  int celly=d->y?d->y+(int)(combat_random(g)%(d->ry*2+1))-d->ry:1+combat_random(g)%(mapHeight43[g->mapId]/8-2);
  float x=cellx*8+4,y=celly*8+4;
  if(!g->canMove||g->canMove(g->world,x,y,x,y)){m->x=m->homeX=x;m->y=m->homeY=y;return;}
 }
 /* Some old server plant rectangles fall entirely on blocked client cells.
  * Prefer the nearest legal cell around that rectangle over stacking at camp. */
 if(d->x&&d->y){
  for(int radius=0;radius<=64;radius++)for(int yy=-radius;yy<=radius;yy++)for(int xx=-radius;xx<=radius;xx++){
   if(abs(xx)!=radius&&abs(yy)!=radius)continue;float x=(d->x+xx)*8+4,y=(d->y+yy)*8+4;
   if(!g->canMove||g->canMove(g->world,x,y,x,y)){m->x=m->homeX=x;m->y=m->homeY=y;return;}
  }
 }
 m->x=m->homeX=g->campX;m->y=m->homeY=g->campY;
}
static void combat_population(Combat*g,unsigned map){
 ground_map60(g,map);expanded_travel60(g,map);
 memset(g->mobs,0,sizeof(g->mobs));g->target=-1;g->autoAttack=0;unsigned n=0;
 for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].map==map){const SpawnDef*d=&spawnDefs[j];
  for(unsigned k=0;k<d->count&&n<MOB_COUNT-1;k++){
   CombatMob*m=&g->mobs[n++];m->bossKey53=bossKeyBase53[j]==65535?0:bossKeyBase53[j]+k+1;m->enabled=1;m->kind=d->kind;m->spawnDef=j;m->faceY=1;m->hp=mobSpecs[m->kind].hp;
   m->attackAt=m->hurtAt=m->deadAt=-100;m->wanderAt=g->time+1+(combat_random(g)%3000)/1000.f;combat_spawn_position(g,m);if(m->bossKey53&&g->bosses53.until[m->bossKey53-1]>bossNow53){m->hp=0;m->deadAt=-1000;}
  }
 }
}
static int combat_valid_target(Combat*g,int i){return i>=0&&i<MOB_COUNT&&!combat_racer_kind164(g->mobs[i].kind)&&g->mobs[i].enabled&&(!g->mobs[i].hidden||g->itemBonuses52.scalar[B52_bIntravision])&&g->mobs[i].hp>0&&combat_dist(g->x,g->y,g->mobs[i].x,g->mobs[i].y)<480;}
static int combat_target_before45(const Combat*g,int a,int b){const CombatMob*x=&g->mobs[a],*y=&g->mobs[b];if(!!x->aggro!=!!y->aggro)return !!x->aggro;if(x->aggro&&x->hp!=y->hp)return x->hp<y->hp;float dx=(x->x-g->x)*(x->x-g->x)+(x->y-g->y)*(x->y-g->y),dy=(y->x-g->x)*(y->x-g->x)+(y->y-g->y)*(y->y-g->y);return dx==dy?a<b:dx<dy;}
static void combat_select(Combat*g,int direction){int list[MOB_COUNT],n=0,current=-1;for(int i=0;i<MOB_COUNT;i++)if(combat_valid_target(g,i)){int at=n;while(at>0&&combat_target_before45(g,i,list[at-1])){list[at]=list[at-1];at--;}list[at]=i;n++;}for(int i=0;i<n;i++)if(list[i]==g->target)current=i;g->target=n?list[current<0?0:(current+(direction<0?-1:1)+n)%n]:-1;}
static void combat_cancel(Combat*g){g->floorGather60=0;g->floorTarget58=g->floorPickup58=-1;g->route53.state=0;
 if(g->approachSkill53){g->approachSkill53=0;g->autoAttack=0;combat_message(g,"Queued skill cancelled; resources kept.");return;}
 if(g->hocusID48&&!combat_casting(g)){g->hocusID48=g->hocusRank48=0;combat_message(g,"Hocus-pocus choice discarded.");return;}
 if(combat_casting(g)){combat_interrupt_cast(g);return;}if(class_active50(g,SK52_ST_CHASEWALK)){g->class50.until[SK52_ST_CHASEWALK-127]=0;return;}if(g->hideLeft>0){g->hideLeft=g->hideDrain=0;combat_message(g,"Hiding ended.");return;}if(class_active50(g,130)){g->class50.until[130-127]=0;combat_message(g,"Cloaking ended.");return;}g->autoAttack=0;g->target=-1;combat_message(g,"Attack cancelled. Move away to escape a pursuing mob.");}
static void combat_respawn(Combat*g){
 memset(g->fields,0,sizeof(g->fields));memset(g->barriers,0,sizeof(g->barriers));g->angelusLeft=0;g->angelusRank=0;combat_support_clear(g);
 g->x=g->campX;g->y=g->campY;g->poisonLeft=g->poisonTick=0;g->hp=g->maxhp;g->sp=g->maxsp;g->sitting=0;memset(g->buffs,0,sizeof(g->buffs));g->shieldHP=g->shieldHits=0;g->autoAttack=0;g->target=-1;g->cooldown=0;
 for(int i=0;i<MOB_COUNT;i++)g->mobs[i].aggro=0;
 if(combat_position_valid(g->home)){g->travel=g->home;g->travelRequest=1;}
 combat_message(g,"Returned to camp. Progress kept for this session.");
}
static void combat_attack(Combat*g){if(g->trickDead55){combat_message(g,"End Play Dead before attacking.");return;}g->route53.state=0;if(g->autoAttack||g->floorGather60){g->autoAttack=g->floorGather60=0;g->floorPickup58=-1;combat_message(g,"Basic attack off.");return;}if(g->hp>0&&(class_active50(g,SK52_HP_BASILICA)||class_active50(g,SK52_PA_GOSPEL))){combat_notice(g,POP_SKILLS,"Cancel Basilica before attacking.");return;}
 if(combat_casting(g)&&!(job_parent52(g->jobId)==10&&class_rank48(g,94))){combat_message(g,"Casting; B or movement cancels.");return;}
 if(class_active50(g,SK52_HW_GRAVITATION)){combat_message(g,"Gravitational Field prevents attacking.");return;}if(class_active50(g,SK52_ST_CHASEWALK)){combat_message(g,"End Chase Walk before attacking.");return;}if(inventory_overweight(g,90)){combat_message(g,"Weight at 90%%: cannot attack. Store or sell items.");return;}if(g->hideLeft>0){combat_message(g,"B or Hiding: emerge before attacking.");return;}
 if(g->sitting){combat_message(g,"Press L3 to stand before attacking.");return;}
 if(g->hp<=0){if(g->time-g->deadAt>=1.5f)combat_respawn(g);return;}
 int floor=ground_live58(g,g->floorTarget58)?g->floorTarget58:basicFirst60==FIRST_ITEMS60?ground_nearest60(g):-1;
 if(floor>=0){g->target=-1;g->floorPickup58=g->floorTarget58=floor;g->floorGather60=0;g->autoAttack=1;g->floorScan60=0;combat_notice(g,POP_ITEMS,"Basic action: collect nearby loot.");return;}
 if(!combat_valid_target(g,g->target)||combat_dist(g->x,g->y,g->mobs[g->target].x,g->mobs[g->target].y)>192.f){
  float best=192.001f;g->target=-1;for(int i=0;i<MOB_COUNT;i++)if(combat_valid_target(g,i)&&(autoHerbs60||!(mobSpecs[g->mobs[i].kind].flags&16))){float d=combat_dist(g->x,g->y,g->mobs[i].x,g->mobs[i].y);if(d<=192.f&&d<best&&g->mobs[i].routeSkipUntil53<=g->time){best=d;g->target=i;}}
 }
 if(g->target<0){floor=ground_nearest60(g);if(floor>=0){g->floorPickup58=g->floorTarget58=floor;g->floorGather60=0;g->autoAttack=1;g->floorScan60=0;return;}}
 if(g->target>=0){g->autoAttack=1;combat_message(g,"Approaching %s. B cancels; moving cancels auto-attack.",mobSpecs[g->mobs[g->target].kind].name);}
 else {g->autoAttack=g->autoAttackToggle52;combat_message(g,g->autoAttack?"Basic attack on: waiting for a nearby enemy.":"No living monster nearby.");}
}
static void combat_eat(Combat*g){
 inventory_action(g,ITEM_APPLE);
}
/* Linear1x at level1 to30x at90, then constant; integer fixed-point. */
static int solo_exp_rate164(int amount,int level,unsigned cap10){if(amount<=0||!cap10)return 0;if(level<1)level=1;if(level>90)level=90;int rate=10000+(level-1)*((int)cap10*1000-10000)/89;int64_t scaled=(int64_t)amount*rate/10000;return scaled>INT_MAX?INT_MAX:(int)scaled;}
static int solo_exp53(int amount,int level){return solo_exp_rate164(amount,level,gameRates164[0]);}
static void combat_gain_exp(Combat*g,int base,int job){
 int64_t be=(int64_t)g->exp+solo_exp53(base,g->level),je=(int64_t)g->jexp+solo_exp_rate164(job,g->level,gameRates164[1]);g->exp=be>INT_MAX?INT_MAX:(int)be;g->jexp=je>INT_MAX?INT_MAX:(int)je;
 while(g->level<TEST_LEVEL_CAP&&g->exp>=progression_base_curve43(g->jobId)[g->level-1]){g->exp-=progression_base_curve43(g->jobId)[g->level-1];g->level++;if(g->jobId==J52_SUPER_NOVICE){g->superSteelUsed53=0;g->buffs[2]=120;g->shieldHits=5;g->shieldHP=g->maxhp*12/100;g->class50.until[187-127]=g->time+60;g->class50.level[187-127]=1;g->class50.until[192-127]=g->time+30;g->class50.level[192-127]=1;g->class50.until[193-127]=g->time+10;g->class50.level[193-127]=1;g->superSuffragUntil53=g->time+10;}g->statPoints+=stat_budget(g->level)-stat_budget(g->level-1);stat_refresh(g);g->hp=g->maxhp;g->sp=g->maxsp;}
 while(g->joblevel<job_cap(g)&&g->jexp>=job_next(g)){g->jexp-=job_next(g);g->joblevel++;g->skillPoints++;stat_refresh(g);}
 if(g->level==TEST_LEVEL_CAP)g->exp=0;if(g->joblevel==job_cap(g))g->jexp=0;
}
/* Test instructor permits reversible class experiments; items/stats/base EXP stay. */
static int combat_change_job(Combat*g,unsigned job){
 if(!job_valid52(job)||g->hp<=0||job==g->jobId)return 0;g->quickenLeft=g->counterLeft=g->sightblasterLeft=g->magicAmpLeft=0;memset(g->fields,0,sizeof(g->fields));memset(g->barriers,0,sizeof(g->barriers));g->angelusLeft=0;g->angelusRank=0;combat_support_clear(g);
 if((g->jobId==0||g->jobId==J52_HIGH_NOVICE)&&job!=0&&(g->joblevel<10||g->ranks[310]<9)){combat_message(g,"Learn Basic Skill 9 and reach Novice Job 10 first.");return 0;}
 if(g->rbBinding>=8&&g->rbBinding<BIND_ITEM_BASE50)g->rbBinding=BIND_EMPTY50;
 if(g->quickKind==1&&g->quickId>=8){g->quickKind=0;g->quickId=0;}g->trickDead55=0;unsigned firstAid54b=g->ranks[311];g->selectedAmmo60=0;g->expandedCoins60=0;if(job!=J60_TAEKWON)g->expanded60.missionSource=g->expanded60.missionCount=0;g->jobId=job;if(job_parent52(job)!=14)g->persistent50.falcon=0;g->persistent50.copySkill=g->persistent50.copyRank=0;if(job_parent52(job)!=20&&g->persistent50.homunType)g->persistent50.homunResting=1;g->joblevel=1;g->jexp=0;g->skillPoints=0;g->jobSkillCarry55=0;memset(g->ranks,0,sizeof(g->ranks));memset(g->useRanks45,0,sizeof(g->useRanks45));g->ranks[311]=firstAid54b;if(job!=0&&job!=J52_HIGH_NOVICE)g->ranks[310]=9;inventory_reconcile46(g);g->poisonLeft=g->poisonTick=0;memset(g->buffs,0,sizeof(g->buffs));g->shieldHP=g->shieldHits=0;g->endureLeft=g->hitStun=0;memset(&g->recovery50,0,sizeof(g->recovery50));g->endureHits=0;g->sitting=0;memset(g->skillCD,0,sizeof(g->skillCD));g->castDelay=0;g->autoAttack=0;g->target=-1;g->statPoints=stat_total48(g)-stat_spent(g->stats);if(g->statPoints<0){memset(g->stats,1,6);g->statPoints=stat_total48(g);}stat_refresh(g);
 for(int i=0;i<12;i++)if(g->hotbar[i]>=8&&g->hotbar[i]<BIND_ITEM_BASE50)g->hotbar[i]=BIND_EMPTY50;
 combat_message(g,"Now %s. Job skills reset; stats/items/base level kept.",job_name(job));return 1;
}
#include "mob_loot52.h"
#include "item_access52.h"
static unsigned solo_drop_rate53(unsigned rate,unsigned source,int mvp,int modifier){const OwnedRule52*r=item_rule52(source);/* Fixed rates in 1/100000 units: cards2x/7.5x, equipment2x, common5x. */(void)modifier;unsigned mult10=r&&r->kind==OWNED_CARD52?(mvp?gameRates164[5]:gameRates164[4]):r&&owned_gear52(r)?gameRates164[3]:gameRates164[2];uint64_t n=(uint64_t)rate*mult10;return n>100000?100000:(unsigned)n;}
static int solo_zeny53(Combat*g,uint64_t commonSell){uint64_t n=commonSell/20;if(n<=1)n=1+combat_random(g)%5;unsigned room=1000000000-g->zeny;unsigned credited=n<room?(unsigned)n:room;g->zeny+=credited;return credited;}
static int combat_loot52(Combat*g,CombatMob*m,char*text,unsigned capacity){
 int added=0;unsigned pos=0;uint64_t commonSell=0;const uint16_t*table=mobLoot52[m->kind];int mvp=table[3]>0,mod=item_personal_status52(g,259);
 for(unsigned i=0;i<table[1];i++){unsigned index=table[0]+i,source=mobLootEntries52[index].source;if(combat_random(g)%100000>=solo_drop_rate53(mobLootEntries52[index].rate,source,mvp,mod))continue;
  int item=inventory_catalog52(source);const OwnedRule52*r=item_rule52(source);if(item>=0&&r&&r->kind==OWNED_MISC52)commonSell+=shopSell[item];
  int floor58=0;if(!ground_loot58(g,source,m->x,m->y,&floor58))continue;added++;if(item>=0&&pos<capacity){int n=snprintf(text+pos,capacity-pos,", %.20s%s",itemDefs[item].name,floor58?" (ground)":"");if(n>0)pos+=(unsigned)n;if(pos>=capacity)pos=capacity;}
 }
 unsigned order[3]={0,1,2};for(unsigned i=2;i>0;i--){unsigned j=combat_random(g)%(i+1),swap=order[i];order[i]=order[j];order[j]=swap;}
 for(unsigned n=0;n<3;n++){unsigned index=table[2]+order[n];if(index>=table[2]+table[3])continue;unsigned source=mobLootEntries52[index].source;if(combat_random(g)%100000<solo_drop_rate53(mobLootEntries52[index].rate,source,1,mod)){int floor58=0;if(ground_loot58(g,source,m->x,m->y,&floor58))added++;break;}}
 int zeny=solo_zeny53(g,commonSell);if(zeny){combat_number(g,m->x,m->y,zeny,1,0);g->damage[(g->damageNext-1)%DAMAGE_EVENTS].kind=7;}return added;
}
static void combat_reward(Combat*g,CombatMob*m){
 if(!m->training)mercenary_kill180(g,m);
 if(!m->training&&combat_campaign_kill200)combat_campaign_kill200(g,m);
 if(!m->training&&combat_npc_kill55)combat_npc_kill55(combat_npc_context55,g,m);
 if(m->training){combat_sound(g,(mob_art_kind55(m->kind)<50?2+mob_art_kind55(m->kind):SOUND_TOTAL50+mob_art_kind55(m->kind)-50));combat_notice(g,POP_REWARDS,"Practice target defeated. No rewards.");return;}
 if(m->bossKey53&&g->bosses53.until[m->bossKey53-1]<=bossNow53)g->bosses53.until[m->bossKey53-1]=bossNow53+600;const MobSpec*s=&mobSpecs[m->kind];g->kills++;taekwon_mission_reward60(g,m);item_proc_event52(g,4,(int)(m-g->mobs),0,g->itemDamageSkill52);class_ore_drop50(g);
 char lootText[72]={0};combat_loot52(g,m,lootText,sizeof(lootText));
 combat_sound(g,(mob_art_kind55(m->kind)<50?2+mob_art_kind55(m->kind):SOUND_TOTAL50+mob_art_kind55(m->kind)-50));
 int oldLevel=g->level;int homunEXP=(int)((int64_t)s->exp*m->class50.homunDamage/s->hp);if(homunEXP>s->exp)homunEXP=s->exp;homun_gain50(g,homunEXP);int expBonus=stargladiator_exp60(g,m)+item_target_bonus52(g,m,B52_bExpAddRace)+item_personal_status52(g,258);int jobBonus=expBonus+item_personal_status52(g,293);combat_gain_exp(g,(int)((int64_t)(s->exp-homunEXP)*(100+expBonus)/100),(int)((int64_t)s->jexp*(100+jobBonus)/100));
 int showExp=!(g->popupDisabled&POP_REWARDS),showLoot=!(g->popupDisabled&POP_LOOT);char expText[48]={0};if(showExp)snprintf(expText,sizeof(expText),": +%d EXP%s",s->exp,oldLevel!=g->level?" | LEVEL UP!":"");
 combat_notice(g,showExp?POP_REWARDS:POP_LOOT,"%s defeated%s%s",s->name,expText,showLoot?lootText:"");
}
static void combat_support_tick(Combat*g,float dt);
static void combat_reveal(Combat*g,float radius,int holy);
static void combat_steal(Combat*g,int target,int rank);
static void combat_fields_tick(Combat*g);
static void combat_barriers_tick(Combat*g);
static int combat_barrier_slot(const Combat*g);
static void combat_barrier_start(Combat*g,float x,float y,int rank);
static void combat_knockback(Combat*g,int i,float dx,float dy,float distance);
static int combat_field_slot(const Combat*g);
static void combat_field_start(Combat*g,float x,float y,int rank,int power);
static void combat_jupitel_tick45(Combat*g);
static void combat_recovery_tick50(Combat*g,float dt);
static void super_death53(Combat*g);
/* Reconstructed normal-swing contact: damage, hit cues, procs and rewards
 * resolve together. The surviving attack animation is450ms; contact is60%
 * through it, matching the recovered Bash contact phase. Not a recovered
 * generic-melee timeline. No allocations or save-format changes.
 * Pending basic packets use rank=critical, stun=miss, gap=launch time. */
static void combat_basic_impact267(Combat*g,SkillBurst49 hit){
 CombatMob*m=&g->mobs[hit.target];
 if(hit.stun){combat_miss(g,m->x,m->y);m->aggro=!m->training&&(mobSpecs[m->kind].flags&2)!=0;combat_notice(g,POP_DAMAGE,"Missed %s.",mobSpecs[m->kind].name);return;}
 int damage=hit.damage,doubled=hit.hits==2,special=class_triple50(g,hit.target);
 if(special){}else if(doubled){int old=g->fxSkill;g->fxSkill=0;skill_hit_ex(g,hit.target,damage,0,2);g->fxSkill=old;}
 else{damage=combat_hit_bonus50(g,m,damage);combat_enemy_number180(g,m,damage,1,hit.rank);combat_hit_sound(g,1);g->itemDamageSkill52=0;combat_enemy_damage(g,m,damage);skill_stagger49(g,m);}
 if(!special)item_proc_event52(g,0,hit.target,damage,0);
 m->hurtAt=g->time;m->aggro=!m->training&&(mobSpecs[m->kind].flags&2)!=0;
 if(g->class50.comboUntil>g->time&&g->cooldown<g->class50.comboUntil-g->time)g->cooldown=g->class50.comboUntil-g->time;
 if(m->hp<=0){m->hp=0;m->deadAt=g->time;m->respawnAt=0;m->provokeLeft=0;m->provokeRank=0;m->aggro=0;
  if(!doubled&&!special)combat_reward(g,m);
  /* Resolving an earlier target must not clear a newly selected target. */
  if(g->target==hit.target){if(!g->autoAttackToggle52)g->autoAttack=0;g->target=-1;g->floorScan60=0;}
 }else{combat_notice(g,POP_DAMAGE,doubled?"Double Attack: %s for %d.":"Hit %s for %d.",mobSpecs[m->kind].name,damage);class_autospell48(g,hit.target);class_after_attack50(g,hit.target);}
}
static void combat_tick(Combat*g,float dt,float moveX,float moveY){
 if(dt<=0)return;g->ammoShot60=0;if(g->ammoDirty60){g->ammoDirty60=0;item_script_refresh52(g);}if(g->floorTarget58>=0&&(!ground_live58(g,g->floorTarget58)||combat_dist(g->x,g->y,groundItems58[g->floorTarget58].x,groundItems58[g->floorTarget58].y)>192)){g->floorTarget58=g->floorPickup58=-1;}boss_tick_state53(&g->bosses53,&g->bossSeenUTC53);
 if(moveX*moveX+moveY*moveY>.02f){g->floorGather60=0;g->floorPickup58=-1;g->autoAttack=0;g->approachSkill53=0;g->route53.state=0;}
 if(dt>.05f)dt=.05f;if(g->trickDead55){moveX=moveY=0;g->autoAttack=0;g->approachSkill53=0;g->route53.state=0;}
 soullinker_revive60(g);super_death53(g);if(g->hp<=0){g->floorGather60=0;g->floorPickup58=-1;g->died53=1;}g->time+=dt;ground_expire60(g);class_tick50(g,dt);mercenary_tick180(g,dt);skill_burst_tick49(g);class_tick48(g);class_magic_tick48(g);combat_jupitel_tick45(g);if(g->quickenLeft>0)g->quickenLeft=fmaxf(0,g->quickenLeft-dt);if(g->counterLeft>0)g->counterLeft=fmaxf(0,g->counterLeft-dt);if(g->sightblasterLeft>0)g->sightblasterLeft=fmaxf(0,g->sightblasterLeft-dt);if(g->magicAmpLeft>0)g->magicAmpLeft=fmaxf(0,g->magicAmpLeft-dt);for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].mobBlind>0)g->mobs[i].mobBlind=fmaxf(0,g->mobs[i].mobBlind-dt);if(g->blindLeft>0)g->blindLeft=fmaxf(0,g->blindLeft-dt);if(g->silenceLeft>0)g->silenceLeft=fmaxf(0,g->silenceLeft-dt);if(g->confusionLeft>0){g->confusionLeft=fmaxf(0,g->confusionLeft-dt);moveX=-moveX;moveY=-moveY;}combat_support_tick(g,dt);combat_fields_tick(g);combat_barriers_tick(g);if(g->angelusLeft>0){g->angelusLeft-=dt;if(g->angelusLeft<0)g->angelusLeft=0;}g->moving=0;if(g->hitStun>0)g->hitStun-=dt;if(g->endureLeft>0)g->endureLeft-=dt;if(g->endureLeft<=0)g->endureHits=0;if(g->hitStun>0){moveX=moveY=0;}
 if(g->hp>0&&!g->trickDead55&&g->poisonLeft>0){g->poisonLeft-=dt;if(!class_active50(g,190))g->poisonTick+=dt;if(g->poisonTick>=1){g->poisonTick-=1;int floor=g->maxhp/4;if(floor<1)floor=1;int loss=g->maxhp/50;if(loss<1)loss=1;if(loss>g->hp-floor)loss=g->hp-floor;if(loss>0){g->hp-=loss;g->hideLeft=0;g->sitting=0;g->lastDamage=g->hurtAt=g->time;}}}if(g->uproarLeft>0)g->uproarLeft=fmaxf(0,g->uproarLeft-dt);if(g->energyCoatLeft>0)g->energyCoatLeft=fmaxf(0,g->energyCoatLeft-dt);if(inventory_overweight(g,90))g->autoAttack=0;if(g->cooldown>0)g->cooldown-=dt;
 for(int b=0;b<3;b++){g->buffs[b]-=dt;if(g->buffs[b]<0)g->buffs[b]=0;}if(g->buffs[2]<=0)g->shieldHP=g->shieldHits=0;g->maxhp=stat_maxhp(g);g->maxsp=stat_maxsp(g);if(g->hp>g->maxhp)g->hp=g->maxhp;if(g->sp>g->maxsp)g->sp=g->maxsp;
 for(int i=0;i<SKILL_CAP50;i++){g->skillCD[i]-=dt;if(g->skillCD[i]<0)g->skillCD[i]=0;}g->castDelay-=dt;if(g->castDelay<0)g->castDelay=0;
 g->moveLock45=fmaxf(0,g->moveLock45-dt);if(g->time-g->attackAt<COMBAT_ATTACK_ANIMATION53||g->time-g->lastCast<.45f||g->moveLock45>0||g->class50.rootUntil>g->time||class_active50(g,153)||class_active50(g,SK52_HP_BASILICA)||class_active50(g,SK52_PA_GOSPEL)||class_active50(g,SK52_HW_GRAVITATION)||class_active50(g,SK60_GS_MADNESSCANCEL))moveX=moveY=0;int manual=(!g->hideLeft||(job_parent52(g->jobId)==13&&class_rank50(g,143)))&&!g->sitting&&moveX*moveX+moveY*moveY>.02f;if(g->sitting||g->hideLeft>0)g->autoAttack=0;
 if(g->hp>0){
  if(g->autoAttack&&g->floorPickup58<0&&g->moveLock45<=0&&g->time-g->lastCast>=.45f&&g->time-g->attackAt>=COMBAT_ATTACK_ANIMATION53&&(!combat_valid_target(g,g->target)||(g->target>=0&&g->mobs[g->target].routeSkipUntil53>g->time)||combat_dist(g->x,g->y,g->mobs[g->target].x,g->mobs[g->target].y)>192.f)){
   g->target=-1;if(!g->autoAttackToggle52)g->autoAttack=0;
   else if(g->time>=g->floorScan60){g->floorScan60=g->time+.2f;int floor=basicFirst60==FIRST_ITEMS60?ground_nearest60(g):-1;if(floor<0){float best=192.001f;for(int i=0;i<MOB_COUNT;i++)if(combat_valid_target(g,i)&&(autoHerbs60||!(mobSpecs[g->mobs[i].kind].flags&16))){float d=combat_dist(g->x,g->y,g->mobs[i].x,g->mobs[i].y);if(d<=192.f&&d<best&&g->mobs[i].routeSkipUntil53<=g->time){best=d;g->target=i;}}if(g->target<0)floor=ground_nearest60(g);}if(floor>=0){g->floorPickup58=g->floorTarget58=floor;g->route53.state=0;}}
  }
  if(manual){if(!(job_parent52(g->jobId)==10&&class_rank48(g,94)))combat_interrupt_cast(g);g->autoAttack=0;combat_face(&g->faceX,&g->faceY,moveX,moveY);g->moving=combat_move(g,&g->x,&g->y,g->x+moveX*combat_walk_speed(g)*dt*(combat_casting(g)?(25+5*class_rank48(g,94))/100.f:1.f),g->y+moveY*combat_walk_speed(g)*dt*(combat_casting(g)?(25+5*class_rank48(g,94))/100.f:1.f));}
  else if((g->floorPickup58>=0||g->floorGather60)&&!g->attackPaused52){g->moving=ground_pickup_tick58(g,dt);}
  else if(g->approachSkill53&&skill_approach_tick53(g,dt)){}
  else if(g->moveLock45<=0&&!class_active50(g,SK60_GS_MADNESSCANCEL)&&g->class50.rootUntil<=g->time&&g->hitStun<=0&&!g->attackPaused52&&!g->utilityMenu&&!combat_casting(g)&&g->castDelay<=0&&g->autoAttack&&combat_valid_target(g,g->target)){
   CombatMob*m=&g->mobs[g->target];float dx=m->x-g->x,dy=m->y-g->y,d=sqrtf(dx*dx+dy*dy);if(g->time-g->attackAt>=COMBAT_ATTACK_ANIMATION53)combat_face(&g->faceX,&g->faceY,dx,dy);
   float reach=combat_attack_range(g);int clear53=class_ice_line48(g,g->x,g->y,m->x,m->y)&&(!g->canMove||g->canMove(g->world,g->x,g->y,m->x,m->y));if((d>reach||!clear53)&&g->time-g->attackAt<COMBAT_ATTACK_ANIMATION53){}else if(d>reach||!clear53){g->moving=player_route_step53(g,g->target,reach,0,dt)==1;}
   else if(g->cooldown<=0&&class_ice_line48(g,g->x,g->y,m->x,m->y)&&(!g->canMove||g->canMove(g->world,g->x,g->y,m->x,m->y))){
    if(class_sacrifice_hit52(g,g->target)){}else if(skill_burst_slot49(g)>=0){
     int contactSlot267=skill_burst_slot49(g);
    if(inventory_wtype46(g)>=17&&inventory_wtype46(g)<=21&&!ammo_attack60(g,1)){g->autoAttack=0;return;}if(g->equipment&16){if(!inventory_count(g,ITEM_ARROW)){g->autoAttack=0;combat_message(g,"Out of Arrows. Buy or craft more.");return;}--*inventory_stack(g,ITEM_ARROW);}
    int damage=combat_physical(g)+(int)(combat_random(g)%5);for(int e=96;e<=99;e++)if(g->jobId<12&&class_active48(g,e))damage=damage*class_attack_rate48(g,m,(int[]){3,1,4,2}[e-96])/100;int doubleRank=g->ranks[8]>g->itemBonuses52.grant[12]?g->ranks[8]:g->itemBonuses52.grant[12],doubleRate=5*doubleRank;if(inventory_wtype46(g)==17&&doubleRate<5*class_rank50(g,SK60_GS_CHAINACTION))doubleRate=5*class_rank50(g,SK60_GS_CHAINACTION);if(doubleRate<g->itemBonuses52.scalar[B52_bDoubleRate])doubleRate=g->itemBonuses52.scalar[B52_bDoubleRate];int doubled=(((job_first50(g->jobId)==4||g->jobId==J52_SUPER_NOVICE)&&inventory_wtype46(g)==1)||(inventory_wtype46(g)==17&&class_rank50(g,SK60_GS_CHAINACTION))||g->itemBonuses52.grant[12]||g->itemBonuses52.scalar[B52_bDoubleRate])&&combat_random(g)%100<(unsigned)doubleRate;int critical=!doubled&&combat_random(g)%1000<(unsigned)combat_target_crit(g,m);int missed267=!critical&&combat_random(g)%100>=(unsigned)g->itemBonuses52.scalar[B52_bPerfectHitRate]&&combat_random(g)%100>=(unsigned)combat_hit_rate(combat_hit(g),combat_mob_flee(m));
     if(!missed267){if(g->jobId>=12){damage=class_weapon_power50(g,m,critical)*class_attack_rate48(g,m,class_weapon_element50(g))/100;damage=damage*(100+20*class_active50(g,SK52_WS_OVERTHRUSTMAX)+50*(class_active50(g,SK52_ASC_EDP)?class_active50(g,SK52_ASC_EDP)+1:0)+5*class_active50(g,233)+(class_active50(g,SK52_LK_BERSERK)?100:0))/100;if(class_offhand50(g)>=0)damage=damage*(50+10*class_rank50(g,127))/100;}damage=damage*(100+2*class_active50(g,SK52_SN_SIGHT))/100;damage=item_physical_bonus52(g,m,damage,0);if(doubled)damage*=2;if(critical)damage=damage*(140+g->itemBonuses52.scalar[B52_bCritAtkRate])/100;damage=mobSpecs[m->kind].flags&16?1:item_normal_def52(g,m,damage,critical);if(!(mobSpecs[m->kind].flags&16)&&(job_first50(g->jobId)==3||g->jobId==J52_SUPER_NOVICE)&&combat_bane_target(m))damage+=(int)(g->ranks[38]*(3+g->level/20.f));if(!(mobSpecs[m->kind].flags&16))damage+=20*class_active50(g,SK52_LK_AURABLADE);if(damage<1)damage=1;}
     g->bursts49[contactSlot267]=(SkillBurst49){.active=BASIC_CONTACT267,.target=g->target,.hits=doubled?2:1,.damage=damage,.stun=missed267,.rank=critical,.life=m->life,.map=g->mapId,.job=g->jobId,.next=g->time+COMBAT_ATTACK_ANIMATION53*.6f,.gap=g->time};
     g->attackAt=g->time;g->cooldown=stat_attack_delay(g);
    }
   }
  }
 }

 item_proc_tick52(g);
 mob_flow_tick53(g);g->awakeCount=g->sleepCount=0;unsigned char assistAggro45[MOB_SPEC_COUNT]={0};for(int j=0;j<MOB_COUNT;j++)if(g->mobs[j].enabled&&g->mobs[j].hp>0&&g->mobs[j].aggro)assistAggro45[g->mobs[j].kind]=1;
 if(!g->peaceful)for(int i=0;i<MOB_COUNT;i++){
  CombatMob*m=&g->mobs[i];if(!m->enabled)continue;if(m->class50.cropUntil52>0&&(m->class50.cropUntil52<=g->time||(m->hp<=0&&g->time>m->deadAt+2))){m->enabled=0;g->creatureAssetsChanged52=1;continue;}const MobSpec*s=&mobSpecs[m->kind];m->moving=0;combat_shot_tick45(g,m);combat_stone_tick(g,m,dt);if(m->slowLeft>0){m->slowLeft-=dt;if(m->slowLeft<=0){m->slowLeft=0;m->slowRank=0;}}if(m->frozenLeft>0){m->frozenLeft-=dt;if(m->frozenLeft<0)m->frozenLeft=0;}if(m->provokeLeft>0)m->provokeLeft-=dt;if((m->training&&(!m->trainingActive||m->hp<=0))||m->hidden||(g->debugFreeze&&!m->training))continue;
  if(m->hp>0&&m->poisonLeft>0){m->poisonLeft-=dt;m->poisonTick+=dt;if(m->poisonTick>=1){m->poisonTick-=1;int floor=s->hp/4;if(floor<1)floor=1;int loss=s->hp/50;if(loss<1)loss=1;if(loss>m->hp-floor)loss=m->hp-floor;if(loss>0){m->hp-=loss;m->frozenLeft=0;combat_enemy_number180(g,m,loss,1,0);}}}if(m->cooldown>0)m->cooldown-=dt;
  if(m->hp<=0){
   if(m->spawnDef==-2){if(g->time>m->deadAt+2){m->enabled=0;g->creatureAssetsChanged52=1;}continue;}
   if(m->bossKey53){uint64_t*u=&g->bosses53.until[m->bossKey53-1];if(*u>bossNow53)continue;*u=0;m->respawnAt=g->time;}
   if(m->respawnAt==0){float delay=8;if(m->spawnDef>=0){const SpawnDef*d=&spawnDefs[m->spawnDef];delay=d->delay/1000.f+(d->variance?combat_random(g)%(d->variance+1)/1000.f:0);if(delay<5)delay=5;}m->respawnAt=m->deadAt+delay;}
   if(g->time>=m->respawnAt){if(m->spawnDef>=0){if(m->kind!=spawnDefs[m->spawnDef].kind){m->kind=spawnDefs[m->spawnDef].kind;s=&mobSpecs[m->kind];g->creatureAssetsChanged52=1;}combat_spawn_position(g,m);}else{m->x=m->homeX;m->y=m->homeY;}m->routeSkipUntil53=0;m->life++;memset(&m->class50,0,sizeof(m->class50));m->gustHits164=0;m->gustNext164=m->vermNext164=0;m->hitLockUntil49=0;m->castUntil48=0;m->castSkill48=m->castRank48=m->castSP48=m->element48=0;m->shotPhase45=0;memset(m->arrows164,0,sizeof(m->arrows164));m->hp=s->hp;m->aggro=0;m->stun=0;m->hidden=m->stolen=0;m->slowLeft=0;m->slowRank=m->crucisRank=0;m->mobBlind=m->frozenLeft=m->stoneWait=m->stoneLeft=m->stoneTick=m->stoneNoticeUntil=0;m->stoneNotice=0;m->cooldown=.5f;m->attackAt=m->hurtAt=-100;m->wanderAt=g->time+2;m->respawnAt=0;m->poisonLeft=m->poisonTick=0;}continue;
  }
  /* Hysteresis covers the whole view at the existing maximum zoom-out.
   * Boss/mini-boss Vocal, combat and targeted actors always remain awake. */
  float ds=(g->x-m->x)*(g->x-m->x)+(g->y-m->y)*(g->y-m->y);
  int always=s->id==1088||m->aggro||g->target==i;
  if(always||ds<864.f*864.f)m->sleeping=0;
  else if(ds>1008.f*1008.f)m->sleeping=1;
  if(m->sleeping){g->sleepCount++;if(m->stun>0){m->stun-=dt;if(m->stun<0)m->stun=0;}continue;}
  g->awakeCount++;
  if(m->frozenLeft>0||m->stoneLeft>0||m->hitLockUntil49>g->time||m->class50.sleepUntil>g->time||m->class50.bladeUntil>g->time)continue;
  if(m->stun>0){m->stun-=dt;continue;}
  if(m->class50.charmUntil>g->time){m->aggro=0;continue;}
  if(m->class50.confuseUntil>g->time){if(m->class50.rootUntil<=g->time&&m->class50.closeUntil<=g->time){if(g->time>=m->wanderAt){float a=combat_random(g)%6283/1000.f;m->wanderX=cosf(a);m->wanderY=sinf(a);m->wanderAt=g->time+.6f;}combat_face(&m->faceX,&m->faceY,m->wanderX,m->wanderY);m->moving=combat_mob_move52(g,m,m->x+m->wanderX*s->speed*dt,m->y+m->wanderY*s->speed*dt);}continue;}
  if(combat_racer_kind164(m->kind)){if(combat_racer_step164)combat_racer_step164(combat_npc_context55,g,m,dt);continue;}
  if(combat_campaign_enemy200&&combat_campaign_enemy200(g,i,dt))continue;
  if(class_mob_companion50(g,i,dt))continue;
  int seesPlayer=!g->trickDead55&&((g->hideLeft<=0&&!class_active50(g,130))||mobUtility[m->kind].detect)&&(!class_active50(g,SK52_ST_CHASEWALK)||combat_status_boss(m));if(!seesPlayer)m->aggro=0;
  if(g->hp<=0)m->aggro=0;
  if(!(s->flags&2))m->aggro=0;
  if((s->flags&4)&&seesPlayer&&g->hp>0&&combat_dist(g->x,g->y,m->x,m->y)<s->view)m->aggro=1;
  if((s->flags&8)&&seesPlayer&&!m->aggro&&g->hp>0&&assistAggro45[m->kind]){for(int j=0;j<MOB_COUNT;j++)if(g->mobs[j].enabled&&g->mobs[j].kind==m->kind&&g->mobs[j].hp>0&&g->mobs[j].aggro&&(m->x-g->mobs[j].x)*(m->x-g->mobs[j].x)+(m->y-g->mobs[j].y)*(m->y-g->mobs[j].y)<s->view*s->view){m->aggro=1;break;}}
  if(m->training&&m->trainingActive)m->aggro=seesPlayer&&g->hp>0;
  float d=combat_dist(g->x,g->y,m->x,m->y);
  /* Spawn rectangles choose initial/respawn positions, never a combat leash.
   * Lose pursuit only when the target actually gets out of chase range. */
  if(m->aggro&&d>s->chase+48)m->aggro=0;
  if(m->aggro){
   assistAggro45[m->kind]=1;m->returningHome45=0;combat_face(&m->faceX,&m->faceY,g->x-m->x,g->y-m->y);
   if(d>mobRange43[m->kind]){if(m->class50.rootUntil<=g->time&&m->class50.closeUntil<=g->time)m->moving=combat_mob_move52(g,m,m->x+m->faceX*s->speed*(m->slowLeft>0?.8f:1.f)*(m->class50.danceUntil>g->time?100.f/(100+m->class50.danceMove):1.f)*dt,m->y+m->faceY*s->speed*(m->slowLeft>0?.8f:1.f)*(m->class50.danceUntil>g->time?100.f/(100+m->class50.danceMove):1.f)*dt);}
   else if(m->cooldown<=0&&class_ice_line48(g,m->x,m->y,g->x,g->y)&&(!g->canMove||g->canMove(g->world,m->x,m->y,g->x,g->y))){
    soullinker_attacked60(g);int lucky53=combat_random(g)%1000<(unsigned)(10+stat_value(g,5)+10*g->itemBonuses52.scalar[B52_bFlee2]);if(lucky53||combat_random(g)%100>=(unsigned)combat_hit_rate((mobSourceLevel[m->kind]+mobSourceDex[m->kind])*(100+m->class50.tarotHit52)/100*(m->mobBlind>0?75:100)/100,combat_flee(g))){combat_miss(g,g->x,g->y);if(lucky53)g->damage[(g->damageNext-1)%DAMAGE_EVENTS].kind=6;m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);combat_notice(g,POP_DAMAGE,"Dodged %s.",s->name);continue;}
    int hard=inventory_defense(g),soft=combat_vit_defense(g);if(combat_berserk_active(g)){hard=hard*45/100;soft=soft*45/100;}int damage=combat_reduce48(combat_enemy_power(m,s->amin+(int)(combat_random(g)%(unsigned)(s->amax-s->amin+1))),hard,soft);damage-=divine_reduction(g,mobProtectedRace[m->kind]);if(damage<1)damage=1;
    if(class_guard48(g,i)||class_block50(g,i)){m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);continue;}if(mobRange43[m->kind]>24){combat_shot_begin45(g,m,damage);m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);continue;}
    if(g->counterLeft>0){g->counterLeft=0;int d=combat_hit_bonus50(g,m,combat_physical(g)*2);combat_enemy_number180(g,m,d,1,1);combat_enemy_damage(g,m,d);combat_hit_sound(g,1);if(m->hp<=0){combat_reward(g,m);m->deadAt=g->time;}m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);continue;}if(g->sightblasterLeft>0){g->sightblasterLeft=0;int d=combat_hit_bonus50(g,m,24+6*g->level);combat_enemy_damage(g,m,d);combat_enemy_number180(g,m,d,1,0);combat_hit_sound(g,1);if(m->hp<=0){combat_reward(g,m);m->deadAt=g->time;continue;}}if(combat_safety_block(g)){m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);combat_notice(g,POP_DAMAGE,"Safety Wall blocked a melee hit.");continue;}
    if(g->buffs[2]>0&&g->shieldHits>0&&g->shieldHP>0){int absorbed=damage<g->shieldHP?damage:g->shieldHP;damage-=absorbed;g->shieldHP-=absorbed;g->shieldHits--;if(!g->shieldHits||!g->shieldHP)g->buffs[2]=0;}
    int reflect48=class_active48(g,119);if(reflect48&&damage>0){int rd=damage*(10+3*reflect48)/100;if(rd>0){combat_enemy_damage(g,m,rd);combat_enemy_number180(g,m,rd,1,0);if(m->hp<=0){combat_reward(g,m);m->deadAt=g->time;}}}damage=class_received50(g,i,damage,0);damage=inventory_energy_hit(g,damage);if(g->debugPlayerInvincible52||g->trickDead55)damage=0;if(damage>0){combat_damage_interrupt_cast(g);g->hideLeft=0;g->sitting=0;}g->hp-=damage;combat_received_number53(g,damage,1);item_proc_event52(g,2,i,damage,0);g->lastDamage=g->time;if(damage>0){if(g->endureLeft>0&&g->endureHits>0){g->endureHits--;if(!g->endureHits)g->endureLeft=0;}else{g->hurtAt=g->time;g->hitStun=.12f;}}m->attackAt=g->time;m->cooldown=combat_enemy_delay164(g,m);
    if(g->hp<=0&&!soullinker_revive60(g)){combat_support_clear(g);memset(g->safety,0,sizeof(g->safety));g->hp=0;g->deadAt=g->time;g->autoAttack=0;memset(g->buffs,0,sizeof(g->buffs));g->shieldHP=g->shieldHits=0;g->endureLeft=0;g->endureHits=0;combat_message(g,"Knocked out. Wait a moment, then press A to respawn.");}
    else combat_notice(g,POP_DAMAGE,"%s hit you for %d. LB: quick slot.",s->name,damage);
   }
  }else if((s->flags&1)&&m->class50.rootUntil<=g->time&&m->class50.closeUntil<=g->time){
   m->returningHome45=0;
   if(g->time>=m->wanderAt){float a=(combat_random(g)%6283)/1000.f;m->wanderX=cosf(a);m->wanderY=sinf(a);m->wanderUntil=g->time+.8f;m->wanderAt=g->time+2+(combat_random(g)%3000)/1000.f;}
   else if(g->time<m->wanderUntil){combat_face(&m->faceX,&m->faceY,m->wanderX,m->wanderY);m->moving=combat_mob_move52(g,m,m->x+m->wanderX*s->speed*(m->slowLeft>0?.8f:1.f)*(m->class50.danceUntil>g->time?100.f/(100+m->class50.danceMove):1.f)*dt,m->y+m->wanderY*s->speed*(m->slowLeft>0?.8f:1.f)*(m->class50.danceUntil>g->time?100.f/(100+m->class50.danceMove):1.f)*dt);}
  }
 }
 combat_recovery_tick50(g,dt);
 skill_cast_tick(g,dt);
 if(g->target>=0&&!combat_valid_target(g,g->target)){g->target=-1;if(!g->autoAttackToggle52)g->autoAttack=0;}

soullinker_revive60(g);super_death53(g);if(g->hp<=0)g->died53=1;}
#include "skills.h"
#include "recovery50.h"
#include "combat_fields.h"
#include "combat_barriers.h"
#include "combat_support.h"
#include "item_use52.h"
#include "mercenary_combat180.h"
static void super_death53(Combat*g){if(g->hp>0||g->jobId!=J52_SUPER_NOVICE||g->superSteelUsed53)return;int next=g->level<TEST_LEVEL_CAP?progression_base_curve43(g->jobId)[g->level-1]:progression_base_curve43(g->jobId)[g->level-2];if(next<=0||(int64_t)g->exp*100<(int64_t)next*99)return;g->superSteelUsed53=1;g->hp=g->maxhp;g->sp=g->maxsp;g->sitting=0;g->class50.until[207-127]=g->time+30;g->class50.level[207-127]=1;g->fxAt=g->lastCast=g->time;g->fxX=g->x;g->fxY=g->y;g->fxSkill=207;g->fxRank48=1;combat_notice(g,POP_SKILLS,"Your guardian angel saved you! Steel Body for30seconds.");}
#endif
