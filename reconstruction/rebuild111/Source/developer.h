/* SPDX-License-Identifier: MIT. Explicit test tools; transient targets never enter saves. */
#ifndef MYRO_DEVELOPER_H
#define MYRO_DEVELOPER_H
#include "art_catalog40.h"
typedef struct {int tab,row,classGroup,base,job,species,scale,confirm,ailment,itemGroup,itemQuantity,preview,previewRequest,rangedRequest;char status[96];} DeveloperUI;
#include "item_access52.h"
static const char*devItemGroups52[9]={"Weapons","Armour","Accessories","Headgear","Cards","Consumables","Materials","Ammunition","Pet items"};
static int dev_item_row52(unsigned group,int ordinal){for(int i=0;i<ITEM_COUNT;i++)if(itemGroup52[i]==group&&ordinal--==0)return i;return -1;}
static int dev_item_count52(unsigned group){int n=0;for(int i=0;i<ITEM_COUNT;i++)n+=itemGroup52[i]==group;return n;}
static void dev_clear_feedback(Combat*g){g->soundRead=g->soundWrite=0;g->damageNext=0;}
static void dev_reset_skills(Combat*g){g->persistent50.falcon=0;g->persistent50.copySkill=g->persistent50.copyRank=0;g->quickenLeft=g->counterLeft=g->sightblasterLeft=g->magicAmpLeft=0;memset(g->fields,0,sizeof(g->fields));memset(g->barriers,0,sizeof(g->barriers));g->angelusLeft=0;g->angelusRank=0;combat_support_clear(g);if(g->rbBinding>=8&&g->rbBinding<BIND_ITEM_BASE50)g->rbBinding=BIND_EMPTY50;memset(g->ranks,0,sizeof(g->ranks));memset(g->useRanks45,0,sizeof(g->useRanks45));g->skillPoints=g->joblevel-1+g->jobSkillCarry55;if(g->jobId!=0&&g->jobId!=J52_HIGH_NOVICE)g->ranks[310]=9;memset(g->buffs,0,sizeof(g->buffs));memset(g->buffLevels,0,sizeof(g->buffLevels));memset(g->skillCD,0,sizeof(g->skillCD));g->endureLeft=g->hitStun=0;memset(&g->recovery50,0,sizeof(g->recovery50));g->endureHits=0;g->shieldHP=g->shieldHits=0;g->castDelay=0;for(int i=0;i<12;i++)if(g->hotbar[i]>=8&&g->hotbar[i]<BIND_ITEM_BASE50)g->hotbar[i]=BIND_EMPTY50;if(g->quickKind==1&&g->quickId>=8){g->quickKind=0;g->quickId=0;}g->autoAttack=0;}
static void dev_reset_stats(Combat*g){memset(g->stats,1,6);g->statPoints=stat_total48(g);stat_refresh(g);g->autoAttack=0;}
static void dev_restore(Combat*g){for(unsigned i=0;i<g->owned52.count[0];i++)g->owned52.items[i].flags&=(uint8_t)~OWNED_BROKEN52;g->brokenWeapon48=0;stat_refresh(g);g->hp=g->maxhp;g->sp=g->maxsp;g->poisonLeft=g->poisonTick=g->blindLeft=g->silenceLeft=g->confusionLeft=0;g->hurtAt=g->deadAt=-100;}
static void dev_open(DeveloperUI*u,const Combat*g){memset(u,0,sizeof(*u));u->base=g->level;u->job=g->joblevel;u->itemQuantity=1;snprintf(u->status,sizeof(u->status),"Testing tools: changes to your build can be saved.");}
static void dev_remove(Combat*g){if(combat_casting(g)&&g->spellCastTarget==MOB_COUNT-1)combat_interrupt_cast(g);for(int w=0;w<COMBAT_BARRIERS;w++){g->barriers[w].total[MOB_COUNT-1]=0;g->barriers[w].totalEvent[MOB_COUNT-1]=0;}for(int f=0;f<COMBAT_FIELDS;f++){g->fields[f].total[MOB_COUNT-1]=0;g->fields[f].totalEvent[MOB_COUNT-1]=0;g->fields[f].hits[MOB_COUNT-1]=g->fields[f].shown[MOB_COUNT-1]=0;}memset(&g->mobs[MOB_COUNT-1],0,sizeof(CombatMob));if(g->target==MOB_COUNT-1)g->target=-1;g->autoAttack=0;dev_clear_feedback(g);}
static int dev_spawn(Combat*g,int species,int scale){
 if(g->peaceful||g->hp<=0||species<0||species>=MOB_SPEC_COUNT||scale<0||scale>3)return 0;float x=0,y=0;int found=0;
 for(int k=0;k<96&&!found;k++){float a=k*.61f,r=24+(k%4)*8;float nx=g->x+cosf(a)*r,ny=g->y+sinf(a)*r;int ok=1;for(int j=1;j<=16&&ok;j++)if(g->canMove&&!g->canMove(g->world,g->x+(nx-g->x)*(j-1)/16,g->y+(ny-g->y)*(j-1)/16,g->x+(nx-g->x)*j/16,g->y+(ny-g->y)*j/16))ok=0;if(ok){x=nx;y=ny;found=1;}}
 if(!found)return 0;dev_remove(g);CombatMob*m=&g->mobs[MOB_COUNT-1];m->training=m->enabled=1;m->spawnDef=-1;m->kind=species;m->x=m->homeX=x;m->y=m->homeY=y;m->faceY=1;m->attackAt=m->hurtAt=m->deadAt=-100;int factor=scale==0?1:scale==1?10:scale==2?100:1000;int hp=mobSpecs[species].hp;hp=hp>1000000/factor?1000000:hp*factor;m->hp=m->testMaxHP=hp;g->target=MOB_COUNT-1;return 1;
}
/* Developer presets replace carried test supplies; normal job changes keep items.
 * Storage and cart contents remain owned. Keep kits below recovery weight. */
static void dev_kit_item50a(Combat*g,int source,int quantity){int item=item_source50(source);if(item>=0&&inventory_count(g,item)<quantity)inventory_add(g,item,quantity-inventory_count(g,item));}
static void dev_expanded_kit60(Combat*g,unsigned job){
 g->selectedAmmo60=0;unsigned weapon=job==J60_NINJA?1201:job==J60_GUNSLINGER?13100:job==J60_STAR_GLADIATOR?1550:job==J60_SOUL_LINKER?1601:0;
 if(weapon){dev_kit_item50a(g,weapon,1);int item=inventory_catalog52(weapon);if(item>=0)inventory_equip_slot50(g,item,0);}
 if(job==J60_GUNSLINGER){unsigned guns[]={13150,13154,13157,13160};for(unsigned i=0;i<4;i++)dev_kit_item50a(g,guns[i],1);dev_kit_item50a(g,13200,100);for(unsigned i=0;i<sizeof(ammoRules60)/sizeof(*ammoRules60);i++)if(ammoRules60[i].kind==5&&ammo_allowed60(g,ammoRules60+i)){dev_kit_item50a(g,ammoRules60[i].source,20);break;}}
 if(job==J60_NINJA){dev_kit_item50a(g,13300,1);unsigned seen=0;for(unsigned i=0;i<sizeof(ammoRules60)/sizeof(*ammoRules60);i++){const AmmoRule60*r=ammoRules60+i;if((r->kind==6||r->kind==7)&&!(seen&(1u<<r->kind))&&ammo_allowed60(g,r)){dev_kit_item50a(g,r->source,20);seen|=1u<<r->kind;}}}
 for(unsigned i=0;i<sizeof(expandedRequirements60)/sizeof(*expandedRequirements60);i++){const ExpandedRequirement60*r=expandedRequirements60+i;if(!job_owns_skill48(job,0,r->id))continue;for(unsigned j=0;j<r->count;j++)dev_kit_item50a(g,r->items[j].source,10);}
 stat_refresh(g);
}
static void dev_class_kit50a(Combat*g,unsigned job){
 g->apples=g->jellopy=g->clover=0;memset(g->owned52.items,0,OWNED_BAG52*sizeof(OwnedItem52));g->owned52.count[0]=0;
 g->equipment=0;memset(g->equipped46,0,sizeof(g->equipped46));g->brokenWeapon48=0;
 dev_kit_item50a(g,512,3);dev_kit_item50a(g,501,3);dev_kit_item50a(g,2301,1);dev_kit_item50a(g,2401,1);
 inventory_equip_slot50(g,ITEM_SHIRT,1);inventory_equip_slot50(g,ITEM_SANDALS,2);
 if(job>=J60_NINJA){dev_expanded_kit60(g,job);return;}
 static const unsigned short weapon[21]={1201,1116,1601,1501,1201,1701,1301,1116,1601,1601,1201,1101,1252,1201,1701,1901,1950,1601,1801,1301,1301};
 int item=item_source50(weapon[job_parent52(job)]);dev_kit_item50a(g,weapon[job_parent52(job)],1);if(item>=0)inventory_equip_slot50(g,item,0);
 if(job==J52_SUPER_NOVICE){dev_kit_item50a(g,717,10);dev_kit_item50a(g,716,10);dev_kit_item50a(g,713,10);}
 unsigned parent=job_first50(job);
 if(parent==2){dev_kit_item50a(g,717,40);dev_kit_item50a(g,716,40);}
 if(parent==3){dev_kit_item50a(g,717,40);dev_kit_item50a(g,713,20);dev_kit_item50a(g,523,20);}
 if(parent==4)dev_kit_item50a(g,7049,20);
 if(parent==5){dev_kit_item50a(g,1750,200);dev_kit_item50a(g,1701,1);dev_kit_item50a(g,909,10);dev_kit_item50a(g,902,10);}
 if(parent==6){dev_kit_item50a(g,902,20);}
 if(job_parent52(job)==10){for(int i=100;i<114;i++)dev_kit_item50a(g,itemDefs[i].id,10);dev_kit_item50a(g,1550,1);}
 if(job_parent52(job)==7||job_parent52(job)==11){dev_kit_item50a(g,1401,1);dev_kit_item50a(g,1451,1);}
 if(job_parent52(job)==11){dev_kit_item50a(g,2101,1);inventory_equip_slot50(g,ITEM_GUARD,3);}
 if(job>=12){
  for(unsigned i=0;i<sizeof(classItems50)/sizeof(*classItems50);i++){const unsigned short*r=classItems50[i];const ClassSkill50*d=class_skill_data50(r[0]);if(d&&job_mask_inherits52(d->owners,job)&&r[0]!=253)dev_kit_item50a(g,itemDefs[r[1]].id,5);}
  if(job_parent52(job)==12)dev_kit_item50a(g,1771,20);
  if(job_parent52(job)==14)g->persistent50.falcon=1;
  if(job_parent52(job)==19)for(int source=612;source<=618;source++)dev_kit_item50a(g,source,1);
  if(job_transcendent52(job))for(unsigned i=0;i<sizeof(transRequirements52)/sizeof(*transRequirements52);i++){const TransRequirement52*r=transRequirements52+i;if(!job_owns_skill48(job,0,r->id))continue;for(unsigned j=0;j<r->count;j++){int max=0;for(int k=0;k<10;k++)if(r->items[j].amount[k]>max)max=r->items[j].amount[k];if(max)dev_kit_item50a(g,r->items[j].source,max*5);}}
 }
}
static void dev_class_preset(Combat*g,unsigned job){if(job_parent52(job)==16||job==J52_GYPSY)g->sex55=0;else if(job_parent52(job)==15||job==J52_CLOWN)g->sex55=1;g->jobSkillCarry55=0;if(g->zeny<1000000)g->zeny=1000000;
 if(!job_valid52(job))return;if(g->hp<=0)g->hp=1;if(g->jobId==0||g->jobId==J52_HIGH_NOVICE){g->joblevel=10;g->ranks[310]=9;}
 if(g->jobId!=job)combat_change_job(g,job);g->level=TEST_LEVEL_CAP;g->joblevel=job_cap(g);g->exp=g->jexp=0;dev_reset_skills(g);dev_reset_stats(g);
 int attr[4]={0,1,2,4},goal[4]={90,80,40,40};if(job_first50(job)==2||job_first50(job)==3||job==J60_NINJA||job==J60_SOUL_LINKER){attr[0]=3;attr[1]=4;attr[2]=2;attr[3]=1;goal[0]=99;goal[1]=90;goal[2]=25;goal[3]=20;}if(job_first50(job)==5||job==J60_GUNSLINGER){attr[0]=4;attr[1]=1;attr[2]=2;attr[3]=3;goal[0]=99;goal[1]=90;goal[2]=25;goal[3]=20;}for(int k=0;k<4;k++)while(g->stats[attr[k]]<goal[k]&&stat_raise(g,attr[k])){}

 for(int i=0;i<LEARN_COUNT;i++)if(job_owns_skill48(job,learnJobs[i],learnIds[i]))g->ranks[i]=learnMax[i];g->skillPoints=0;stat_refresh(g);
 for(int i=0;i<12;i++)g->hotbar[i]=BIND_EMPTY50;g->hotSlot=0;g->hotAttack=1;int n=0;for(int pass=0;pass<2;pass++)for(int i=0;i<LEARN_COUNT&&n<12;i++)if(job_owns_skill48(job,learnJobs[i],learnIds[i])&&!skill_passive(learnIds[i])&&((pass==0)==(learnJobs[i]==job)))g->hotbar[n++]=learnIds[i];
 if(job==3){const SkillBinding50 testBar[12]={50,51,52,53,54,55,10,5,6,40,41,43};memcpy(g->hotbar,testBar,sizeof(testBar));}
 if(job==J60_SOUL_LINKER){const SkillBinding50 bar[]={SK60_SL_STIN,SK60_SL_STUN,SK60_SL_SMA,SK60_SL_SKE,SK60_SL_SWOO,SK60_SL_SKA,SK60_SL_KAIZEL,SK60_SL_KAAHI,SK60_SL_KAUPE,SK60_SL_KAITE,SK60_TK_SEVENWIND,SK60_TK_HIGHJUMP};memcpy(g->hotbar,bar,sizeof(bar));}
 dev_class_kit50a(g,job);if(job_parent52(job)!=7&&job_parent52(job)!=11)g->mounted48=0;
 if(g->zeny<10000)g->zeny=10000;g->sitting=0;dev_restore(g);g->target=-1;dev_clear_feedback(g);
}
static const char*devClassGroups48[]={"First Classes","Second Classes","Transcendent First","Transcendent Second","Expanded Classes"};
static const unsigned char devClassIDs48[5][13]={{0,40,1,2,3,4,5,6},{7,11,9,10,12,13,14,15,16,17,18,19,20},{33,34,35,36,37,38,39},{21,22,8,23,24,25,26,27,28,29,30,31,32},{41,42,43,44,45}};
static const unsigned char devClassCounts48[]={8,13,7,13,5};
static int dev_class_job48(const DeveloperUI*u){return devClassIDs48[u->classGroup][u->row];}
static int dev_rows(int tab){return tab==0?9:tab==1?11:tab==4?6:8;}
/* Returns 1 to close tools. A second A confirms build resets; B always cancels first. */
static int dev_input(DeveloperUI*u,Combat*g,unsigned p){
 if(u->confirm){if(p&4){u->confirm=0;return 0;}if(p&2){int op=u->confirm;u->confirm=0;if(op==1){g->level=u->base;g->joblevel=u->job;g->exp=g->jexp=0;dev_reset_stats(g);dev_reset_skills(g);dev_restore(g);}else if(op==2)dev_reset_stats(g);else dev_reset_skills(g);dev_clear_feedback(g);snprintf(u->status,sizeof(u->status),"Build updated. Save normally to keep these changes.");}return 0;}
 if(p&4)return 1;
 if(p&(32|512)){u->tab=(u->tab+((p&32)?4:1))%5;u->row=0;return 0;}
 if(u->tab==3){if(p&(4096|8192)){u->itemGroup=(u->itemGroup+((p&8192)?1:8))%9;u->row=0;return 0;}int count=dev_item_count52(u->itemGroup);if(p&1024)u->row=(u->row+count-1)%count;if(p&2048)u->row=(u->row+1)%count;if(p&8)u->row=u->row>=7?u->row-7:0;if(p&16){u->row+=7;if(u->row>=count)u->row=count-1;}if(p&64)u->itemQuantity=u->itemQuantity==1?10:u->itemQuantity==10?100:1;if(p&2){int item=dev_item_row52(u->itemGroup,u->row);if(item>=0){int quantity=item_rule52(itemDefs[item].id)->stackLimit==1?1:u->itemQuantity;if(inventory_add(g,item,quantity))snprintf(u->status,sizeof(u->status),"Added %d %.65s.",quantity,itemDefs[item].name);else snprintf(u->status,sizeof(u->status),"Bag or weight limit reached. Nothing added.");}}return 0;}
 if(u->tab==2&&(p&(4096|8192))){u->classGroup=(u->classGroup+((p&8192)?1:4))%5;u->row=0;return 0;}
 int n=u->tab==2?devClassCounts48[u->classGroup]:dev_rows(u->tab);if(p&1024){u->row=(u->row+n-1)%n;return 0;}if(p&2048){u->row=(u->row+1)%n;return 0;}
 int delta=(p&8192)?1:(p&4096)?-1:0;
 if(u->tab==4){unsigned*v=gameRates164+u->row;if(delta){int value=(int)*v+delta*5;*v=value<0?0:value>1000?1000:(unsigned)value;gameRatesDirty164=1;}if(p&2){*v=gameRateDefaults164[u->row];gameRatesDirty164=1;}snprintf(u->status,sizeof(u->status),"Rates apply globally. A restores the selected default.");return 0;}
 if(u->tab==0){if(u->row==8&&(delta||(p&2))){g->sex55=!g->sex55;return 0;}if(delta&&u->row==6){g->walkPercent+=delta;if(g->walkPercent<50)g->walkPercent=50;if(g->walkPercent>125)g->walkPercent=125;}if(delta&&u->row<2){int*v=u->row?&u->job:&u->base;int cap=u->row?job_cap(g):TEST_LEVEL_CAP;*v+=delta;if(*v<1)*v=1;if(*v>cap)*v=cap;}if(p&2){if(u->row==7){if((job_parent52(g->jobId)==7||job_parent52(g->jobId)==11)&&class_rank48(g,112)){g->mounted48=!g->mounted48;combat_interrupt_cast(g);}else snprintf(u->status,sizeof(u->status),"Knight or Crusader with Riding required.");}else if(u->row==6)g->walkPercent=100;else if(u->row<=2)u->confirm=1;else if(u->row==3){dev_restore(g);snprintf(u->status,sizeof(u->status),"HP/SP restored; poison removed.");}else if(u->row>=4&&u->row<=5)u->confirm=u->row==4?2:3;}}
 else if(u->tab==1){if(u->row==10){if(p&2){CombatMob*m=&g->mobs[MOB_COUNT-1];if(m->enabled&&m->hp>0){m->castUntil48=g->time+3;m->castSkill48=3;m->castRank48=3;m->castSP48=16;snprintf(u->status,sizeof(u->status),"Practice Fire Bolt in 3s after resume. Counter it.");}else snprintf(u->status,sizeof(u->status),"Spawn a living practice target first.");}return 0;}if(u->row==9){if(delta)u->ailment=(u->ailment+delta+3)%3;if(p&2){if(u->ailment==0)g->blindLeft=30;else if(u->ailment==1)g->silenceLeft=30;else g->confusionLeft=30;snprintf(u->status,sizeof(u->status),"Applied 30s ailment. Resume; use Cure or wait.");}return 0;}if(u->row==8){CombatMob*m=&g->mobs[MOB_COUNT-1];if((p&2)||delta){if(m->enabled&&m->hp>0){m->trainingActive=!m->trainingActive;m->aggro=m->trainingActive;m->moving=0;snprintf(u->status,sizeof(u->status),"Practice behaviour: %s (still no rewards/respawn).",m->trainingActive?"active: chases and attacks":"idle");}else snprintf(u->status,sizeof(u->status),"Spawn a living practice target first.");}return 0;}if(delta&&u->row==0)u->species=(u->species+delta+MOB_SPEC_COUNT)%MOB_SPEC_COUNT;if(delta&&u->row==1)u->scale=(u->scale+delta+4)%4;if((p&2)||delta){if(u->row==2)g->debugImmortal=!g->debugImmortal;else if(u->row==5)g->debugFreeze=!g->debugFreeze;else if((p&2)&&u->row==3)snprintf(u->status,sizeof(u->status),"%s",dev_spawn(g,u->species,u->scale)?"Passive target spawned. No rewards; no auto-respawn.":"Use a field, alive, with clear ground nearby.");else if(u->row==7){CombatMob*m=&g->mobs[MOB_COUNT-1];if(m->enabled&&m->hp>0){m->testTraits=(m->testTraits+(delta<0?3:1))%4;m->slowLeft=0;m->slowRank=m->crucisRank=0;snprintf(u->status,sizeof(u->status),"Practice-only type override. Natural monster data stays unchanged.");}else snprintf(u->status,sizeof(u->status),"Spawn a living practice target first.");}else if((p&2)&&u->row==6){CombatMob*m=&g->mobs[MOB_COUNT-1];if(m->enabled&&m->hp>0){m->hidden=!m->hidden;if(m->hidden&&g->target==MOB_COUNT-1)g->target=-1;snprintf(u->status,sizeof(u->status),"Practice target: %s",m->hidden?"hidden; use a reveal skill":"visible");}else snprintf(u->status,sizeof(u->status),"Spawn a living practice target first.");}else if((p&2)&&u->row==4){dev_remove(g);snprintf(u->status,sizeof(u->status),"Practice target removed.");}}}
 else if(u->tab==2){if(p&2){dev_class_preset(g,dev_class_job48(u));u->base=g->level;u->job=g->joblevel;snprintf(u->status,sizeof(u->status),"%s: skills ready; carried items replaced with class kit.",job_name(g->jobId));}}


 return 0;
}
#endif
