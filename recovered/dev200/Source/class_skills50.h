/* MIT. Bounded solo second-class execution; source requirements checked twice. */
#include "class_common50.h"
#include "item_actions52.h"
#include "class_craft50.h"
#include "class_blacksmith50.h"
#include "class_alchemist50.h"
#include "class_homunculus50.h"
#include "class_assassin_rogue50.h"
#include "class_hunter50.h"
#include "class_priest50.h"
#include "class_monk50.h"
#include "class_performer50.h"
#include "class_lord_knight52.h"
#include "class_paladin52.h"
#include "class_professor52.h"
#include "class_sniper52.h"
#include "class_shadow52.h"
#include "class_high_wizard52.h"
#include "class_whitesmith52.h"
#include "class_creator52.h"
#include "class_tarot52.h"
#include "class_gear52.h"
#include "class_gunslinger60.h"
#include "class_ninja60.h"
#include "class_taekwon60.h"
#include "class_stargladiator60.h"
#include "class_soullinker60.h"
#include "expanded_mechanics60.h"
static int class_ready50(Combat*g,unsigned id,float x,float y,int target){
 if(id>=EXPANDED_FIRST60&&id<EXPANDED_LAST60&&!expanded_mechanics60(id)){combat_notice(g,POP_SKILLS,"This expanded skill is not integrated yet.");return 0;}
 if(id>=TRANS_FIRST52&&id<TRANS_LAST52&&!trans_skill_ready52(id)){combat_notice(g,POP_SKILLS,"This skill is not available in the current build.");return 0;}
 if(id==SKG52_NPC_EARTHQUAKE&&class_area_slot50(g)<0)return 0;
 if(id>=SK60_GS_GLITTERING&&id<=SK60_GS_GROUNDDRIFT&&!gunslinger_ready60(g,id,target,x,y))return 0;
 int rank=skill_rank(g,id);const ClassSkill50*d=class_skill_data50(id);
 if(!d||!rank||d->passive)return 0;
 if(id>=SK60_SL_KAIZEL&&id<=SK60_SL_SKA&&!soullinker_ready60(g,id,target))return 0;
 if(id>=SK60_SG_FEEL&&id<=SK60_SG_FUSION){int ready=stargladiator_ready60(g,id,rank,target);if(ready!=1)return ready;}
 if(id>=SK60_TK_READYSTORM&&id<=SK60_TK_MISSION&&!taekwon_ready60(g,id,target))return 0;
 if(id>=SK60_NJ_TOBIDOUGU&&id<=SK60_NJ_ISSEN&&!ninja_ready60(g,id,rank,target,x,y))return 0;
 if(id==SK52_CG_ARROWVULCAN&&skill_burst_slot49(g)<0)return 0;
 if(id==SK52_CR_CULTIVATION){if(class_crop_slot52(g)<0)return 0;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],x,y,4))return 0;}
 if(id==SK52_CR_FULLPROTECTION&&inventory_slot46(g,0)<0&&inventory_slot46(g,3)<0&&inventory_slot46(g,2)<0&&inventory_slot46(g,4)<0)return 0;
 if(id==SK52_CR_ACIDDEMONSTRATION&&skill_burst_slot49(g)<0)return 0;
 if(id==SK52_HW_GRAVITATION&&class_area_slot50(g)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire.");return 0;}
 if(id==SK52_ASC_CDP&&!class_poison_craft_ready52(g)){combat_notice(g,POP_SKILLS,"Need all seven poison ingredients and room for a bottle; resources kept.");return 0;}
 if(id==SK52_PF_HPCONVERSION&&(g->sp>=g->maxsp||g->hp<=g->maxhp/10)){combat_notice(g,POP_SKILLS,"Need spare HP and room for SP; resources kept.");return 0;}
 if(id==SK52_PF_SOULCHANGE&&(target<0||g->mobs[target].class50.soulChanged52)){combat_notice(g,POP_SKILLS,"Soul Change can recover SP once from each monster.");return 0;}
 if(id==SK52_PF_FOGWALL&&class_area_slot50(g)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire.");return 0;}
 if(id==SK52_KN_PIERCE&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for the active skill hits; resources kept.");return 0;}
 if(id==SK52_PA_SHIELDCHAIN&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for the active skill hits; resources kept.");return 0;}
 if(id==SK52_LK_SPIRALPIERCE&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for the active skill hits; resources kept.");return 0;}
 if(id==SK52_HP_BASILICA){for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].enabled&&g->mobs[i].hp>0&&fabsf(g->mobs[i].x-g->x)<20&&fabsf(g->mobs[i].y-g->y)<20){combat_notice(g,POP_SKILLS,"Basilica needs a clear area around you; resources kept.");return 0;}}
 if(id==SK52_CH_PALMSTRIKE&&(!class_active50(g,209)||class_palm_slot52(g)<0)){combat_notice(g,POP_SKILLS,"Palm Strike requires Fury and room for its delayed impact.");return 0;}
 if((id==SK52_CH_TIGERFIST||id==SK52_CH_CHAINCRUSH)&&!class_combo_action52(g,id)){combat_notice(g,POP_SKILLS,"Continue the preceding combo against the same monster.");return 0;}
 if(id==SK52_CH_CHAINCRUSH&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for the active skill hits; resources kept.");return 0;}
 if(id==210&&g->class50.comboUntil>g->time&&!class_combo_action52(g,id)){combat_notice(g,POP_SKILLS,"Finish this combo against the same monster.");return 0;}
 if(id==SK52_WS_WEAPONREFINE){g->utilityMenu=id;if(!inventory_action_rows52(g)){g->utilityMenu=0;combat_notice(g,POP_ITEMS,"No eligible weapon below the learned refinement limit.");return 0;}g->sp-=skill_cost(g,id);g->castDelay=.35f;g->autoAttack=0;return 2;}
 if(id==239){g->utilityMenu=239;g->autoAttack=0;return 2;}
 if(id==228&&(class_repair_material50(g)<0||!inventory_count(g,class_repair_material50(g)))){combat_notice(g,POP_SKILLS,"Need a damaged weapon and its repair material; SP kept.");return 0;}
 if(!class_resources50(g,id,rank,0))return 0;
 if(id==250&&g->persistent50.homunType&&!g->persistent50.homunResting){if(!g->persistent50.homunHP){combat_notice(g,POP_SKILLS,"Use Homunculus Resurrection for your defeated companion.");return 0;}g->utilityMenu=500;g->autoAttack=0;return 2;}
 if(id==251&&(!homun_alive50(g)||100*g->persistent50.homunHP<80*homun_maxhp50(&g->persistent50))){combat_notice(g,POP_SKILLS,"Vaporize requires a living Homunculus with at least 80%% HP; SP kept.");return 0;}
 if(id==252&&(!g->persistent50.homunType||g->persistent50.homunResting||g->persistent50.homunHP)){combat_notice(g,POP_SKILLS,"Choose a defeated, active Homunculus; SP kept.");return 0;}
 if((id==174||id==181||id==183)&&g->class50.song){combat_notice(g,POP_SKILLS,"A performance is already active.");return 0;}
 if(id==176&&(!g->class50.song||g->time-g->class50.songStarted<5)){combat_notice(g,POP_SKILLS,"Amp requires a performance active for five seconds.");return 0;}
 if(id==177&&(!g->class50.lastSong||g->class50.song||!class_song_weapon50(g,g->class50.lastSong))){combat_notice(g,POP_SKILLS,"Perform a song or dance before using Encore.");return 0;}
 if(id==207&&class_active50(g,207)){combat_notice(g,POP_SKILLS,"Steel Body is already active.");return 0;}
 if(id==201&&!g->class50.spheres&&(target<0||combat_status_boss(&g->mobs[target]))){combat_notice(g,POP_SKILLS,"Absorb your spheres or choose a non-boss monster.");return 0;}
 if(id==210&&!class_active50(g,209)){combat_notice(g,POP_SKILLS,"Asura requires Fury.");return 0;}
 if(id==211||id==212){int previous=id==211?202:211;if(g->class50.comboUntil<=g->time||g->class50.comboSkill!=previous||target!=g->class50.comboTarget||g->mobs[target].life!=g->class50.comboLife){combat_notice(g,POP_SKILLS,"Continue the preceding Monk combo while its window is open.");return 0;}}
 if(g->class50.rootUntil>g->time&&!((id==206&&g->class50.rootRank>=3)||(id==209&&g->class50.rootRank>=4)||(id==210&&g->class50.rootRank>=5))){combat_notice(g,POP_SKILLS,"Root holds you; this skill cannot be used.");return 0;}
 if((id==132||id==144)&&g->hideLeft<=0){combat_notice(g,POP_SKILLS,"Use Hiding first; resources kept.");return 0;}
 if(id==130&&rank<3&&!class_active50(g,id)){
  int near=0;for(int axis=0;axis<4;axis++){float dx=(int[]){-8,8,0,0}[axis],dy=(int[]){0,0,-8,8}[axis];if(g->canMove&&!g->canMove(g->world,g->x,g->y,g->x+dx,g->y+dy))near=1;}
  if(!near){combat_notice(g,POP_SKILLS,"Cloaking ranks 1-2 require a wall nearby.");return 0;}
 }
 if((id==243||id==244)&&!class_summon_ready50(g,id,rank)){combat_notice(g,POP_SKILLS,"Wait for your summons; plant types cannot be mixed.");return 0;}
 if(id==135||id==150||id==189||id==197||id==240){if(class_area_slot50(g)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire.");return 0;}}
 if(id>=154&&id<=163){
  if(class_trap_slot50(g)<0){combat_notice(g,POP_SKILLS,"Twelve traps are already placed.");return 0;}
  if(g->canMove&&!g->canMove(g->world,x,y,x,y)){combat_notice(g,POP_SKILLS,"A trap needs clear ground.");return 0;}
  for(int n=0;n<CLASS_TRAPS50;n++){ClassTrap50*t=&g->traps50[n];if(t->map==g->mapId&&t->until>g->time&&fabsf(t->x-x)<12&&fabsf(t->y-y)<12){combat_notice(g,POP_SKILLS,"Another trap occupies this ground.");return 0;}}
  for(int n=0;n<MOB_COUNT;n++)if(class_in_area50(g,&g->mobs[n],x,y,12)){combat_notice(g,POP_SKILLS,"Place the trap away from occupied cells.");return 0;}
 }
 if(id==139||id==169){if(class_nearest_trap50(g,id,rank)<0){combat_notice(g,POP_SKILLS,"No untriggered trap within reach.");return 0;}if(id==139&&!inventory_can_add(g,item_source50(1065),1)){combat_notice(g,POP_SKILLS,"No room to recover the trap.");return 0;}}
 if(id>=167&&id<=169&&!class_falcon_ready50(g)){combat_notice(g,POP_SKILLS,"A trained Falcon is required.");return 0;}
 if((id==185||id==195)&&(target<0||!class_undead50(&g->mobs[target]))){combat_notice(g,POP_SKILLS,"Choose an Undead target for this skill.");return 0;}
 if(id==191&&target<0){combat_notice(g,POP_SKILLS,"Choose a monster for Recovery; resources kept.");return 0;}
 if(id==196&&target>=0&&(g->mobs[target].frozenLeft>0||g->mobs[target].stoneLeft>0)){combat_notice(g,POP_SKILLS,"A frozen or petrified target cannot receive Lex Aeterna.");return 0;}
 if(target>=0){CombatMob*m=&g->mobs[target];
  if(id==136&&(combat_status_boss(m)||(int64_t)m->hp*4>(int64_t)combat_mob_max(m)*3)){combat_notice(g,POP_SKILLS,"Venom Splasher needs a non-boss below 75%% HP.");return 0;}
  if(id==141&&(m->training||combat_status_boss(m)||m->class50.coinStolen||m->stoneLeft>0||m->frozenLeft>0)){combat_notice(g,POP_SKILLS,"Cannot steal Zeny from this target.");return 0;}
  if(id==142&&((g->x-m->x)*m->faceX+(g->y-m->y)*m->faceY>=0)){combat_notice(g,POP_SKILLS,"Move behind the target to Backstab.");return 0;}
  if((id>=145&&id<=149||id==153)&&combat_status_boss(m)){combat_notice(g,POP_SKILLS,"That boss resists this skill.");return 0;}
 }
 int hits=id==131?8:id==167?rank:id==171?2:id==206?g->class50.spheres: id==211?4:1;
 if(hits>1&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for active skill hits; resources kept.");return 0;}
 return 1;
}
static void class_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 int before=g->class50.spheres;if(!class_resources50(g,id,rank,1))return;
 if(id>=SK60_SL_KAIZEL&&id<=SK60_SL_SKA)soullinker_execute60(g,id,rank,target);
 else if(id>=SK60_SG_FEEL&&id<=SK60_SG_FUSION)stargladiator_execute60(g,id,rank,target);
 else if(id>=SK60_TK_READYSTORM&&id<=SK60_TK_MISSION)taekwon_execute60(g,id,rank,target,x,y);
 else if(id>=SK60_NJ_TOBIDOUGU&&id<=SK60_NJ_ISSEN)ninja_execute60(g,id,rank,target,x,y);
 else if(id>=SK60_GS_GLITTERING&&id<=SK60_GS_GROUNDDRIFT)gunslinger_execute60(g,id,rank,target,x,y);
 else if(id>=GEAR_SKILL_FIRST52)class_gear_execute52(g,id,rank,target,x,y);
 else if(id>=SK52_KN_PIERCE&&id<=SK52_KN_BRANDISHSPEAR)class_knight_spear52(g,id,rank,target);
 else if(id==SK52_CG_TAROTCARD)class_tarot_execute52(g,rank,target);
 else if(id==SK52_CG_ARROWVULCAN)skill_hit_ex(g,target,class_physical50(g,&g->mobs[target],200+100*rank,0,-1),0,9);
 else if(id>=SK52_CR_SLIMPITCHER&&id<=SK52_CR_CULTIVATION)class_creator_execute52(g,id,rank,target,x,y);
 else if(id>=SK52_WS_MELTDOWN&&id<=SK52_WS_OVERTHRUSTMAX)class_whitesmith_execute52(g,id,rank,target);
 else if(id==SK52_HW_GANBANTEIN||id==SK52_HW_GRAVITATION)class_high_wizard_execute52(g,id,rank,x,y);
 else if(id>=SK52_ASC_KATAR&&id<=SK52_ST_FULLSTRIP)class_shadow_execute52(g,id,rank,target);
 else if(id>=SK52_SN_SIGHT&&id<=SK52_SN_WINDWALK)class_sniper_execute52(g,id,rank,target);
 else if(id>=SK52_PF_HPCONVERSION&&id<=SK52_PF_DOUBLECASTING)class_professor_execute52(g,id,rank,target,x,y);
 else if(id>=SK52_PA_PRESSURE&&id<=SK52_PA_SHIELDCHAIN)class_paladin_execute52(g,id,rank,target);
 else if(id>=SK52_LK_AURABLADE&&id<=SK52_LK_JOINTBEAT)class_lord_knight_execute52(g,id,rank,target);
 else if(id==SK52_HP_ASSUMPTIO||id==SK52_HP_BASILICA)class_high_priest_execute52(g,id,rank);
 else if(id>=SK52_CH_PALMSTRIKE&&id<=SK52_CH_SOULCOLLECT)class_champion_execute52(g,id,rank,target);
 else if(id>=130&&id<=138)class_assassin_execute50(g,id,rank,target,x,y);
 else if(id>=141&&id<=153)class_rogue_execute50(g,id,rank,target,x,y);
 else if(id>=173&&id<=184)class_performer_execute50(g,id,rank,target,x,y);
 else if(id>=250&&id<=252)homun_execute50(g,id,rank);
 else if(id>=240&&id<=248)class_alchemist_execute50(g,id,rank,target,x,y);
 else if(id>=228&&id<=236)class_blacksmith_execute50(g,id,rank,x,y);
 else if(id>=200&&id<=213)class_monk_execute50(g,id,rank,target,x,y,before-g->class50.spheres);
 else if(id>=185&&id<=197)class_priest_execute50(g,id,rank,target,x,y);
 else class_hunter_execute50(g,id,rank,target,x,y);
}
static int class_block50(Combat*g,int mob){
 int rank=class_active50(g,208);if(!rank||mob<0||mob>=MOB_COUNT)return 0;CombatMob*m=&g->mobs[mob];
 if(combat_status_boss(m)||mobRange43[m->kind]>15)return 0;
 g->class50.until[208-127]=0;m->class50.closeUntil=g->time+class_duration50(208,rank,1);
 g->class50.rootUntil=m->class50.bladeUntil=m->class50.closeUntil;g->class50.rootTarget=mob;g->class50.rootRank=rank;g->class50.rootLife=m->life;g->autoAttack=0;class_fx50(g,208,rank,g->x,g->y);return 1;
}
static int class_received50(Combat*g,int mob,int damage,int ranged){
 soullinker_attacked60(g);damage=soullinker_kaupe60(g,damage);
 damage=taekwon_received60(g,mob,damage,ranged);
 damage=ninja_received60(g,mob,damage,ranged);
 if(ranged&&class_active50(g,SK60_GS_ADJUSTMENT))damage=damage*80/100;
 damage=item_received_bonus52(g,mob>=0&&mob<MOB_COUNT?&g->mobs[mob]:NULL,damage,ranged,0,0);
 int reject=class_active50(g,SK52_ST_REJECTSWORD);if(damage>0&&reject&&g->class50.rejectHits52>0&&mob>=0&&mob<MOB_COUNT&&class_chance50(g,15*reject,100)){damage/=2;skill_hit(g,mob,damage,0);if(!--g->class50.rejectHits52)g->class50.until[SK52_ST_REJECTSWORD-127]=0;}
 int parry=class_active50(g,SK52_LK_PARRYING);if(damage>0&&parry&&inventory_wtype46(g)==3&&class_chance50(g,20+3*parry,100)){combat_guard_number53(g);return 0;}
 if(damage>0&&class_active50(g,SK52_HP_BASILICA)&&(mob<0||!combat_status_boss(&g->mobs[mob])))return 0;
 if(damage>0&&class_active50(g,SK52_HP_ASSUMPTIO))damage/=2;

 int rank=class_active50(g,134);if(damage>0&&rank&&mob>=0&&mob<MOB_COUNT){CombatMob*m=&g->mobs[mob];
  if(m->hp>0&&(mobElement48[m->kind][0]==5||class_chance50(g,50,100))){
   class_fx50(g,mobElement48[m->kind][0]==5?134:13,rank,m->x,m->y);
   if(mobElement48[m->kind][0]==5){skill_hit(g,mob,class_physical50(g,m,100+30*rank,0,-1),0);g->class50.until[134-127]=0;}
   else{skill_hit(g,mob,class_physical50(g,m,100,0,-1)+75,0);if(m->hp>0)class_poison50(g,m,50,35);if(--g->class50.next[134-127]<=0)g->class50.until[134-127]=0;}
  }
 }
 if(damage>0&&job_parent52(g->jobId)==19)damage=damage*(100-class_rank50(g,229))/100;
 if(damage>0)g->class50.until[130-127]=0;
 if(damage>0&&!ranged&&mob>=0&&mob<MOB_COUNT&&g->itemBonuses52.scalar[B52_bShortWeaponDamageReturn]){int old=g->fxSkill;g->fxSkill=119;g->itemProcSkip52=1;skill_hit_now49(g,mob,damage*g->itemBonuses52.scalar[B52_bShortWeaponDamageReturn]/100,0,1);g->itemProcSkip52=0;g->fxSkill=old;}
 (void)ranged;return mercenary_devotion180(g,damage);
}
static void class_after_attack50(Combat*g,int target){
 if(target<0||target>=MOB_COUNT||g->mobs[target].hp<=0)return;CombatMob*m=&g->mobs[target];
 taekwon_after_attack60(g,target);stargladiator_hit60(g);
 int offhand=class_offhand50(g);if(offhand>=0){int old=g->fxSkill;g->fxSkill=0;skill_hit(g,target,class_offhand_damage50(g,m),0);g->fxSkill=old;if(m->hp<=0)return;}
 int weapon=inventory_slot46(g,0);if(class_active50(g,233)&&!g->itemBonuses52.scalar[B52_bUnbreakableWeapon]&&weapon>=0&&inventory_wtype46(g)!=6&&inventory_wtype46(g)!=7&&inventory_wtype46(g)!=8&&!class_active50(g,245)&&class_chance50(g,1,1000)){g->brokenWeapon48=weapon+1;const OwnedItem52*piece=inventory_instance52(g,0);if(piece){OwnedItem52*mutable=owned_find52(&g->owned52,0,piece->uid);mutable->flags|=OWNED_BROKEN52;}inventory_remove46(g,0);combat_notice(g,POP_ITEMS,"Overthrust damaged your weapon. Repair it before equipping it.");}
 int melt=class_active50(g,SK52_WS_MELTDOWN);if(melt&&!combat_status_boss(m)){if(class_chance50(g,100*melt,10000))m->class50.stripUntil[0]=g->time+5;if(class_chance50(g,70*melt,10000))m->class50.stripUntil[2]=g->time+5;}
 int deadly=class_active50(g,SK52_ASC_EDP);if(deadly)class_poison50(g,m,deadly+2,class_duration50(SK52_ASC_EDP,deadly,1));
 int poison=class_active50(g,133);if(poison)class_poison50(g,m,2+poison/2,class_duration50(133,poison,1));
 if(job_parent52(g->jobId)==13&&inventory_wtype46(g)!=10&&class_rank50(g,140)&&!m->stolen&&!m->training&&class_chance50(g,15*class_rank50(g,140)+55+10*skill_rank(g,37),1000))combat_steal(g,target,skill_rank(g,37));
 if(class_falcon_ready50(g)&&inventory_wtype46(g)==10&&class_rank50(g,167)&&skill_burst_slot49(g)>=0&&class_chance50(g,3*stat_value(g,5)+1,1000))class_blitz50(g,target,class_rank50(g,167),1);
}
static void class_tick50(Combat*g,float dt){
 (void)dt;
 gunslinger_tick60(g);ninja_tick60(g);stargladiator_tick60(g);soullinker_tick60(g);
 class_champion_tick52(g);
 class_lord_knight_tick52(g);
 class_paladin_tick52(g);
 class_professor_tick52(g);
 class_shadow_tick52(g);
 class_gravitation_tick52(g);class_gear_tick52(g,dt);
 if(class_active50(g,SK52_HP_BASILICA)&&(fabsf(g->x-g->class50.basilicaX52)>.01f||fabsf(g->y-g->class50.basilicaY52)>.01f))g->class50.until[SK52_HP_BASILICA-127]=0;
 if(class_active50(g,153)){int target=g->class50.comboTarget;if(target<0||target>=MOB_COUNT||g->mobs[target].hp<=0||g->mobs[target].class50.closeUntil<=g->time)g->class50.until[153-127]=0;}
 if(g->class50.rootUntil>g->time){int target=g->class50.rootTarget;if(target<0||target>=MOB_COUNT||g->mobs[target].hp<=0||g->mobs[target].life!=g->class50.rootLife)g->class50.rootUntil=0;}
 int n=0;for(int i=0;i<g->class50.spheres;i++)if(g->class50.sphereUntil[i]>g->time)g->class50.sphereUntil[n++]=g->class50.sphereUntil[i];g->class50.spheres=n;
 int rank=class_active50(g,130);if(rank&&rank<3&&!class_near_wall50(g)){g->class50.until[130-127]=0;rank=0;}if(rank&&g->time>=g->class50.next[130-127]){if(g->sp<=0)g->class50.until[130-127]=0;else{g->sp--;g->class50.next[130-127]+=class_duration50(130,rank,0);}}
 int maximize=class_active50(g,234);if(maximize&&g->time>=g->class50.next[234-127]){if(g->sp<=0)g->class50.until[234-127]=0;else{g->sp--;g->class50.next[234-127]+=class_duration50(234,maximize,0);}}
 class_traps_tick50(g);class_performer_tick50(g);class_summons_tick50(g);homun_tick50(g,dt);
 for(int i=0;i<CLASS_AREAS50;i++){ClassArea50*a=&g->areas50[i];if(a->map!=g->mapId){a->until=0;continue;}if(a->until<=g->time||a->next>g->time)continue;if(a->id==135){class_poison_area50(g,a->x,a->y,a->rank);a->next=g->time+1;}else if(a->id==189||a->id==197)class_priest_tick50(g,a);else if(a->id==240)class_alchemist_tick50(g,a);}
 for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(m->class50.suitonUntil60<=g->time)m->class50.suitonUntil60=0;if(m->class50.flingUntil60<=g->time)m->class50.flingUntil60=0;if(m->class50.tarotUntil52<=g->time)m->class50.tarotAtk52=m->class50.tarotMatk52=m->class50.tarotHit52=m->class50.tarotFlee52=m->class50.tarotDef52=0;if(m->enabled&&m->hp>0&&m->class50.bleedUntil>g->time&&m->class50.bleedNext<=g->time){int loss=200+combat_random(g)%600;if(loss>=m->hp)loss=m->hp-1;if(loss>0){m->hp-=loss;combat_enemy_number180(g,m,loss,1,0);}m->class50.bleedNext+=10;}for(int k=0;k<4;k++)if(m->class50.stripUntil[k]<=g->time)m->class50.stripUntil[k]=0;if(!m->enabled||m->hp<=0||m->class50.splasherUntil<=0||m->class50.splasherUntil>g->time)continue;
  int rank=m->class50.splasherRank;m->class50.splasherUntil=0;float x=m->x,y=m->y;class_fx50(g,136,rank,x,y);
  int count=0;for(int j=0;j<MOB_COUNT;j++)if(class_in_area50(g,&g->mobs[j],x,y,12))count++;
  for(int j=0;j<MOB_COUNT;j++)if(class_in_area50(g,&g->mobs[j],x,y,20))skill_hit(g,j,class_physical50(g,&g->mobs[j],500+50*rank+20*class_rank50(g,134),0,-1)/(count?count:1),0);
 }
}
