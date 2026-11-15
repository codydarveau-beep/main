/* MIT. Bounded integer VM for validated original item-script expressions. */
static int skill_rank(const Combat*g,unsigned id);
#include "item_script_words52.h"
#include "item_groups52.h"
#include "item_event_constants52.h"
#include "item_skill_map52.h"
static int item_clamp52(int64_t n){return n>1000000000?1000000000:n<-1000000000?-1000000000:(int)n;}
static int item_script_native52(unsigned source){unsigned lo=0,hi=sizeof(itemSkillMap52)/sizeof(*itemSkillMap52);while(lo<hi){unsigned m=(lo+hi)/2;if(itemSkillMap52[m][0]<source)lo=m+1;else hi=m;}return lo<sizeof(itemSkillMap52)/sizeof(*itemSkillMap52)&&itemSkillMap52[lo][0]==source?itemSkillMap52[lo][1]:-1;}
static int item_script_slot52(int eqi){static const int slots[15]={-1,5,1,3,0,4,2,7,6,8,9,9,8,5,4};return eqi>=0&&eqi<15?slots[eqi]:-1;}
static int item_script_fn52(Combat*g,const OwnedItem52*piece,unsigned fn,const int*a,int count){
 int arg=count?a[0]:0;
 if(fn==0)return piece?piece->refine:0;
 if(fn==1){if(arg>=13&&arg<=18)return g->stats[arg-13];return arg==6?g->maxhp:arg==7?g->maxsp:0;}
 if(fn==2){int native=item_script_native52((unsigned)arg);if(native<0)return 0;int k=skill_rank_index(native),rank=k>=0?g->ranks[k]:0;return native<512&&g->itemBonuses52.grant[native]>rank?g->itemBonuses52.grant[native]:rank;}
 if(fn==3){const OwnedRule52*r=item_rule52((uint32_t)arg);const EquipmentRule52*e=equipment_rule52((uint32_t)arg);int field=count>1?a[1]:-1;static const int sourceWeapon[23]={0,1,2,3,4,5,6,7,8,10,11,15,23,12,13,14,16,17,18,19,20,21,22};return field==5&&r?(int)r->location:field==6&&r?(int)r->weight:field==7&&e?e->attack:field==8&&e?e->defense:field==9&&e?e->range:field==10&&r?r->slots:field==11&&e&&e->weapon<23?sourceWeapon[e->weapon]:field==12&&e?e->minLevel:field==13&&e?e->weaponLevel:0;}
 if(fn==4||fn==5){const OwnedItem52*p=inventory_instance52(g,item_script_slot52(arg));return p?(fn==4?(int)p->sourceID:p->refine):fn==4?-1:0;}
 if(fn==6)return count>1?(a[0]>a[1]?a[0]:a[1]):arg;
 if(fn==7)return arg==5?g->calendarDay52:arg==6?g->calendarMonth52:0;
 if(fn==8)return 0;/* Character/map text does not participate in the supplied equipment bonus conditions. */
 if(fn==9){for(int n=0;n<count;n++){int found=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(!p->equipped)continue;if(p->sourceID==(uint32_t)a[n])found=1;for(unsigned c=0;c<4;c++)if(p->cards[c]==(uint32_t)a[n])found=1;}if(!found)return 0;}return 1;}
 if(fn==12){int low=count>1?a[0]:0,high=count>1?a[1]:arg-1;if(high<low){int v=low;low=high;high=v;}uint32_t range=(uint32_t)((int64_t)high-low+1);return low+(range?combat_random(g)%range:0);}
 if(fn==13){int item=inventory_catalog52((uint32_t)arg);return item>=0?inventory_count(g,item):0;}
 if(fn==10)return count>1?(a[0]<a[1]?a[0]:a[1]):arg;
 return 0;
}
/* Source map_race_id2mask: RC_All is Boss|NonBoss, not every base race. */
static unsigned item_race_mask52(int key){unsigned ordinary=(1u<<10)-1,nonDemi=ordinary&~(1u<<7);return key>=0&&key<=12?1u<<key:key==14?nonDemi|(1u<<10):key==15?ordinary:key==16?(1u<<7)|(1u<<10):key==17?nonDemi:key==255?(1u<<11)|(1u<<12):0;}
static int item_is_race_bonus52(unsigned type){return type==B52_bAddRace||type==B52_bSubRace||type==B52_bMagicAddRace||type==B52_bIgnoreDefRate||type==B52_bIgnoreMdefRate||type==B52_bCriticalAddRace||type==B52_bExpAddRace||type==B52_bSPDrainValueRace||type==B52_bSPGainRaceAttack||type==B52_bSPGainRace;}
static unsigned item_target_races52(const CombatMob*m){int boss=m->training&&m->testTraits?m->testTraits==3:mobUtility[m->kind].blocked;return (1u<<mobClassData50[m->kind][0])|(1u<<(boss?11:12));}
static void item_script_bonus52(Combat*g,const OwnedItem52*piece,unsigned type,const int*a,unsigned count){
 if(type>=B52_COUNT||!count)return;
 if(count==1&&type!=B52_bAddMonsterDropChainItem){int value=a[0];switch(type){case B52_bIgnoreDefRace:case B52_bIgnoreMdefRace:case B52_bDefRatioAtkRace:g->itemBonuses52.scalar[type]|=item_race_mask52(value);return;case B52_bAtkEle:case B52_bDefEle:g->itemBonuses52.scalar[type]=value;return;case B52_bNoGemStone:case B52_bNoKnockback:case B52_bNoSizeFix:case B52_bNoCastCancel:case B52_bRestartFullRecover:case B52_bIntravision:case B52_bUnbreakableWeapon:case B52_bUnbreakableArmor:case B52_bUnbreakableHelm:case B52_bUnbreakableShield:case B52_bUnbreakableShoes:case B52_bUnbreakableGarment:value=1;break;default:break;}g->itemBonuses52.scalar[type]=item_clamp52((int64_t)g->itemBonuses52.scalar[type]+value);return;}
 if(type==B52_bHPDrainRate||type==B52_bSPDrainRate){for(unsigned i=0;i<g->itemBonuses52.count;i++){ItemEffect52*p=g->itemBonuses52.effects+i;if(p->type==type&&p->count==count){p->args[0]+=a[0];p->args[1]+=a[1];return;}}}
 if(count>5||g->itemBonuses52.count>=ITEM_EFFECTS52)return;ItemEffect52*p=g->itemBonuses52.effects+g->itemBonuses52.count++;memset(p,0,sizeof(*p));p->type=type;p->count=count;p->pieceUID=piece?piece->uid:0;p->hand=piece&&piece->equipped==32&&owned_gear52(item_rule52(piece->sourceID))&&item_rule52(piece->sourceID)->kind==OWNED_WEAPON52;memcpy(p->args,a,count*sizeof(int));
}
static int item_script_binary52(int op,int a,int b){switch(op){case 0:return item_clamp52((int64_t)a+b);case 1:return item_clamp52((int64_t)a-b);case 2:return item_clamp52((int64_t)a*b);case 3:return b?a/b:0;case 4:return b?a%b:0;case 5:return(int)((uint32_t)a<<(b<0?0:b>31?31:b));case 6:return a>>(b<0?0:b>31?31:b);case 7:return a&b;case 8:return a|b;case 9:return a^b;case 10:return a==b;case 11:return a!=b;case 12:return a<b;case 13:return a<=b;case 14:return a>b;case 15:return a>=b;case 16:return a&&b;case 17:return a||b;case 18:{int n=1;if(b<0)return 0;if(b>31)b=31;for(int i=0;i<b;i++)n=item_clamp52((int64_t)n*a);return n;}}return 0;}
static void item_use_plan52(Combat*g,unsigned command,const int*args,unsigned count);
static int item_script_run52(Combat*g,const OwnedItem52*piece,const int32_t*code,unsigned length){
 int stack[64],sp=0,local=0;unsigned pc=0,steps=0;
 while(pc<length&&steps++<4096){unsigned op=code[pc++];if(op==10)return 1;
  if(op==0||op==1){if(pc>=length||sp>=64)return 0;int value=code[pc++];if(op==1)value=value==0?g->level:value==1?g->joblevel:value==2?(int)job_source52(g->jobId):value==3?(int)job_source52(job_first50(g->jobId)):value==4?(int)job_source52(job_parent52(g->jobId)):local;stack[sp++]=value;continue;}
  if(op==3){if(pc>=length||sp<1)return 0;int kind=code[pc++],v=stack[sp-1];stack[sp-1]=kind==0?!v:kind==1?-v:kind==3?~v:v;continue;}
  if(op==4){if(pc>=length||sp<2)return 0;int kind=code[pc++],b=stack[--sp];stack[sp-1]=item_script_binary52(kind,stack[sp-1],b);continue;}
  if(op==5||op==6){if(pc>=length)return 0;unsigned jump=code[pc++];if(jump>=length)return 0;if(op==6)pc=jump;else{if(sp<1)return 0;if(!stack[--sp])pc=jump;}continue;}
  if(op==9){if(pc>=length||sp<1)return 0;pc++;local=stack[--sp];continue;}
  unsigned type=0,count=0;if(op==2||op==7||op==13||op==14){if(pc+1>=length)return 0;type=code[pc++];count=code[pc++];}else if(op==8||op==11||op==12){if(pc>=length)return 0;count=code[pc++];}else return 0;
  if(count>8||count>(unsigned)sp)return 0;int args[8]={0};for(unsigned i=0;i<count;i++)args[i]=stack[sp-count+i];sp-=count;
  if(op==14)item_use_plan52(g,type,args,count);
  else if(op==2){if(sp>=64)return 0;stack[sp++]=item_script_fn52(g,piece,type,args,(int)count);}
  else if(op==7||op==13)item_script_bonus52(g,piece,type,args,count);
  else if(op==8&&count>=2){int native=item_script_native52((unsigned)args[0]);if(native>0&&native<512&&args[1]>0&&args[1]<=10&&g->itemBonuses52.grant[native]<args[1])g->itemBonuses52.grant[native]=args[1];}
  else if(op==11&&g->itemVMEvent52&&count>=3&&args[0]==I52_SC_PROPERTYWIND){g->class50.itemElement52=4;g->class50.itemElementUntil52=g->time+args[1]*.001f;}
  else if(op==12&&g->itemVMEvent52&&count>=2){g->hp+=args[0];g->sp+=args[1];if(g->hp>g->maxhp)g->hp=g->maxhp;if(g->sp>g->maxsp)g->sp=g->maxsp;}
 }
 return 0;
}
static void item_script_execute52(Combat*g,const OwnedItem52*piece,uint32_t source){
 unsigned lo=0,hi=sizeof(itemScripts52)/sizeof(*itemScripts52);while(lo<hi){unsigned mid=(lo+hi)/2;if(itemScripts52[mid].source<source)lo=mid+1;else hi=mid;}if(lo>=sizeof(itemScripts52)/sizeof(*itemScripts52)||itemScripts52[lo].source!=source)return;
 const ItemScript52*script=itemScripts52+lo;item_script_run52(g,piece,itemScriptWords52+script->start,script->count);
}
static void item_script_refresh52(Combat*g){memset(&g->itemBonuses52,0,sizeof(g->itemBonuses52));for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(!p->quantity||!p->equipped||!p->identified)continue;item_script_execute52(g,p,p->sourceID);if(!(p->flags&OWNED_RESERVED_CARDS52))for(unsigned c=0;c<4;c++)if(p->cards[c])item_script_execute52(g,p,p->cards[c]);}const AmmoRule60*ammo=g->jobId>=J60_NINJA?ammo_current60(g,ammo_weapon_mask60(inventory_wtype46(g))):NULL;if(ammo)for(unsigned ai=0;ai<g->owned52.count[0];ai++){const OwnedItem52*p=g->owned52.items+ai;if(p->sourceID==ammo->source&&p->quantity){item_script_execute52(g,p,p->sourceID);break;}}for(unsigned i=0;i<16;i++){ItemTrigger52*t=g->class50.itemTriggers52+i;if(t->until<=g->time)continue;const OwnedItem52*p=owned_find52(&g->owned52,0,t->uid);if(p&&p->equipped)item_script_execute52(g,p,t->script);else t->until=0;}int stone=class_active50(g,SKG52_NPC_STONESKIN),anti=class_active50(g,SKG52_NPC_ANTIMAGIC);g->itemBonuses52.scalar[B52_bDef]+=20*(stone-anti);g->itemBonuses52.scalar[B52_bMdef]+=20*(anti-stone);g->itemBonuses52.scalar[B52_bMagicDamageReturn]+=20*class_active50(g,SKG52_NPC_MAGICMIRROR);for(unsigned i=0;i<16;i++){const ItemUseBuff52*b=g->class50.itemUseBuffs52+i;if(b->until>g->time&&b->bonus>=0&&b->bonus<B52_COUNT)g->itemBonuses52.scalar[b->bonus]+=b->value;}}
static int item_bonus_match_hand52(const Combat*g,unsigned type,int key,int all,int hand){int value=0;for(unsigned i=0;i<g->itemBonuses52.count;i++){const ItemEffect52*p=g->itemBonuses52.effects+i;if(p->type!=type||(hand>=0&&p->hand!=hand))continue;int match=item_is_race_bonus52(type)&&key>=0&&key<=12?(item_race_mask52(p->args[0])&(1u<<key))!=0:(p->args[0]==key||p->args[0]==all);if(match)value+=p->args[1];}return value;}
static int item_bonus_match52(const Combat*g,unsigned type,int key,int all){return item_bonus_match_hand52(g,type,key,all,-1);}
static unsigned item_script_source52(unsigned native){return native<sizeof(itemNativeSources52)/sizeof(*itemNativeSources52)?itemNativeSources52[native]:0;}
static int item_factor52(int factor,int rate){return rate<=-100?0:item_clamp52((int64_t)factor*(100+rate)/100);}
static int item_boss_key52(const CombatMob*m){return item_target_races52(m)&(1u<<11)?11:12;}
static int item_target_bonus52(const Combat*g,const CombatMob*m,unsigned type){return item_bonus_match52(g,type,mobClassData50[m->kind][0],-1)+item_bonus_match52(g,type,item_boss_key52(m),-1);}
static int item_physical_hand_bonus52(const Combat*g,const CombatMob*m,int damage,unsigned skill,int hand){
 int race=mobClassData50[m->kind][0],size=mobClassData50[m->kind][1],element=m->element48?m->element48:mobElement48[m->kind][0],factor=1000;
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddRace,race,-1,hand));
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddEle,element,255,hand));
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddSize,size,255,hand));
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddRace2,item_mob_race2_52(mobSpecs[m->kind].id),255,hand));
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddRace,item_boss_key52(m),-1,hand));
 factor=item_factor52(factor,item_bonus_match_hand52(g,B52_bAddDamageClass,mobSpecs[m->kind].id,-1,hand));
 if(inventory_wtype46(g)==10)factor=item_factor52(factor,g->itemBonuses52.scalar[B52_bLongAtkRate]);
 if(skill)factor=item_factor52(factor,item_bonus_match52(g,B52_bSkillAtk,(int)item_script_source52(skill),-1));
 return item_clamp52((int64_t)damage*factor/1000);
}
static int item_physical_bonus52(const Combat*g,const CombatMob*m,int damage,unsigned skill){return item_physical_hand_bonus52(g,m,damage,skill,0);}
static int item_magic_bonus52(const Combat*g,const CombatMob*m,int damage,unsigned skill){int factor=1000;factor=item_factor52(factor,item_bonus_match52(g,B52_bMagicAddRace,mobClassData50[m->kind][0],-1));factor=item_factor52(factor,item_bonus_match52(g,B52_bMagicAddRace,item_boss_key52(m),-1));if(skill)factor=item_factor52(factor,item_bonus_match52(g,B52_bSkillAtk,(int)item_script_source52(skill),-1));return item_clamp52((int64_t)damage*factor/1000);}
static int item_normal_def52(const Combat*g,const CombatMob*m,int damage,int critical){int hard=combat_enemy_defense(m),soft=mobStunVit[m->kind];unsigned races=item_target_races52(m);if(g->itemBonuses52.scalar[B52_bDefRatioAtkRace]&races)return item_clamp52((int64_t)damage*(hard+soft)/100);if(critical||(g->itemBonuses52.scalar[B52_bIgnoreDefRace]&races))return damage;int ignore=g->itemBonuses52.scalar[B52_bIgnoreDefRate]+item_target_bonus52(g,m,B52_bIgnoreDefRate);if(ignore>100)ignore=100;hard=hard*(100-ignore)/100;return item_clamp52((int64_t)damage*(100-hard)/100);}
static int item_personal_status52(const Combat*g,int status){int value=0;for(unsigned i=0;i<16;i++){const ItemUseBuff52*b=g->class50.itemUseBuffs52+i;if(b->status==status&&b->until>g->time)value=b->value;}return value;}
static int item_received_bonus52(const Combat*g,const CombatMob*m,int damage,int ranged,int magic,int element){int factor=1000;if(!magic){int armor=g->class50.itemElementUntil52>g->time?g->class50.itemElement52:g->itemBonuses52.scalar[B52_bDefEle];if(armor>=0&&armor<10&&element>=0&&element<10)factor=factor*elementRate48[0][armor][element]/100;}
 factor=item_factor52(factor,-item_bonus_match52(g,B52_bSubEle,element,255));
 if(m){factor=item_factor52(factor,-item_bonus_match52(g,B52_bSubSize,mobClassData50[m->kind][1],255));factor=item_factor52(factor,-item_bonus_match52(g,B52_bSubRace2,item_mob_race2_52(mobSpecs[m->kind].id),255));factor=item_factor52(factor,-item_bonus_match52(g,B52_bSubRace,mobClassData50[m->kind][0],-1));factor=item_factor52(factor,-item_bonus_match52(g,B52_bSubRace,item_boss_key52(m),-1));factor=item_factor52(factor,-item_bonus_match52(g,B52_bAddDefClass,mobSpecs[m->kind].id,-1));}
 if(ranged&&!magic)factor=item_factor52(factor,-g->itemBonuses52.scalar[B52_bLongAtkDef]);if(magic)factor=item_factor52(factor,-g->itemBonuses52.scalar[B52_bNoMagicDamage]);int result=item_clamp52((int64_t)damage*factor/1000);return m&&mobMvpSolo164[m->kind]?result/2:result;
}
