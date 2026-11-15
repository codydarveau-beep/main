/* SPDX-License-Identifier: MIT
 * Versioned little-endian save format. Never serialize Combat pointers/timers.
 */
#ifndef MYRO_SAVE_FORMAT_H
#define MYRO_SAVE_FORMAT_H
#include "combat.h"
#include "owned_codec52.h"
#include "job_save_rules55.h"
#define SAVE_BYTES 40960
#define SAVE_OWNED52 8192
#define SAVE_EXPANDED60 7952
typedef char SaveExpandedBounds60[(SAVE_EXPANDED60>=6000+1945&&SAVE_EXPANDED60+64<=SAVE_OWNED52)?1:-1];
enum { SAVE_ITEM_CAP50=256, SAVE_RANK_CAP50=512, SAVE_EXTRA50=512, SAVE_STORAGE50=1536, SAVE_CART50=2560, SAVE_EQUIP50=3584, SAVE_RANKS50=3648, SAVE_USE_RANKS50=4160, SAVE_HOTBAR50=4672, SAVE_CLASS50=4704 };
typedef char SaveCapacity50[(LEARN_COUNT<=SAVE_RANK_CAP50&&EQUIP_SLOTS46<=16)?1:-1];
#define SAVE_MAP 0x10f17d52u
#define SAVE_WORLD43 0x10f17d43u /* fixed world-set identifier; mapId selects a resident field */
typedef struct {
 char name56[20];Appearance58 appearance58;unsigned noviceQuest54b;BossState53 bosses53;unsigned died53,superSteelUsed53;
 ExpandedState60 expanded60;ClassPersistent50 persistent50;
 uint32_t sequence,rng;int brokenWeapon48,mounted48;
 float x,y,faceX,faceY;
 int hp,sp,level,joblevel,exp,jexp,kills,jellopy,clover,apples;
 OwnedItems52 owned52;unsigned selectedAmmo60;unsigned autoAttackToggle52,monsterView52;int tooltipsDisabled;unsigned popupDisabled;unsigned equipment;unsigned short equipped46[EQUIP_SLOTS46];int cartOwned,cartStyle;WorldPosition home,memos[3];unsigned memoCount;
 SkillBinding50 hotbar[12];unsigned hotSlot,mapId,quickKind,quickId,rbBinding;int zeny;unsigned char stats[6];int statPoints;unsigned jobId,jobSkillCarry55,sex55;unsigned char ranks[LEARN_COUNT],useRanks45[LEARN_COUNT];int skillPoints;int walkPercent45,diagnosticsOff45;
} SavedCharacter;
static uint32_t save_u32(const unsigned char*p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void save_put(unsigned char*p,uint32_t n){p[0]=n;p[1]=n>>8;p[2]=n>>16;p[3]=n>>24;}
#include "boss_codec53.h"
static float save_float(const unsigned char*p){uint32_t u=save_u32(p);float f;memcpy(&f,&u,4);return f;}
static void save_put_float(unsigned char*p,float f){uint32_t u;memcpy(&u,&f,4);save_put(p,u);}
static uint32_t save_crc(const unsigned char*p,unsigned n){
 uint32_t c=~0u;for(unsigned i=0;i<n;i++){c^=p[i];for(int k=0;k<8;k++)c=(c>>1)^(0xedb88320u&-(c&1u));}return ~c;
}
static void save_capture(SavedCharacter*s,const Combat*g,uint32_t seq){
 memset(s,0,sizeof(*s));s->sequence=seq;s->rng=g->rng;s->died53=g->died53||g->hp<=0;s->superSteelUsed53=g->superSteelUsed53;boss_capture53(&s->bosses53,&g->bosses53);s->expanded60=g->expanded60;s->persistent50=g->persistent50;s->owned52=g->owned52;inventory_compact52(&s->owned52);
 s->x=g->x;s->y=g->y;s->faceX=g->faceX;s->faceY=g->faceY;
 s->hp=g->hp;s->sp=g->sp;s->level=g->level;s->joblevel=g->joblevel;s->exp=g->exp;s->jexp=g->jexp;
 s->brokenWeapon48=g->brokenWeapon48;s->mounted48=g->mounted48;s->kills=g->kills;s->jellopy=inventory_count(g,ITEM_JELLOPY);s->clover=inventory_count(g,ITEM_CLOVER);s->apples=inventory_count(g,ITEM_APPLE);
 s->selectedAmmo60=g->selectedAmmo60;s->appearance58=g->appearance58;memcpy(s->name56,g->name56,20);s->sex55=g->sex55;s->jobSkillCarry55=g->jobSkillCarry55;s->noviceQuest54b=g->noviceQuest54b;s->autoAttackToggle52=g->autoAttackToggle52;s->monsterView52=g->monsterView52;s->tooltipsDisabled=g->tooltipsDisabled;s->popupDisabled=g->popupDisabled;s->equipment=g->equipment;memcpy(s->equipped46,g->equipped46,sizeof(s->equipped46));s->cartOwned=g->cartOwned;s->cartStyle=g->cartStyle;memcpy(s->hotbar,g->hotbar,sizeof(s->hotbar));s->hotSlot=g->hotSlot;s->mapId=g->mapId;s->zeny=g->zeny;memcpy(s->stats,g->stats,6);s->statPoints=g->statPoints;s->jobId=g->jobId;memcpy(s->ranks,g->ranks,LEARN_COUNT);s->skillPoints=g->skillPoints;s->walkPercent45=g->walkPercent;s->diagnosticsOff45=g->diagnosticsOff45;memcpy(s->useRanks45,g->useRanks45,LEARN_COUNT);s->quickKind=g->quickKind;s->quickId=g->quickId;s->rbBinding=g->rbBinding;s->home=g->home;s->memoCount=g->memoCount;memcpy(s->memos,g->memos,sizeof(s->memos));
 WorldPosition savedPosition55=job_save_position55(g);s->mapId=savedPosition55.map;s->x=savedPosition55.x;s->y=savedPosition55.y;
}
static int save_class_valid50(const SavedCharacter*s){
 const ClassPersistent50*c=&s->persistent50;
 if(c->falcon>1||(c->falcon&&(job_parent52(s->jobId)!=14||!s->ranks[165-3])))return 0;
 if(c->copySkill){int k=skill_rank_index(c->copySkill);if(job_parent52(s->jobId)!=13||k<0||!class_copyable50(c->copySkill)||!c->copyRank||c->copyRank>learnMax[k]||c->copyRank>s->ranks[152-3])return 0;}
 else if(c->copyRank)return 0;
 if(!c->homunType){ClassPersistent50 empty=*c;empty.falcon=empty.copySkill=empty.copyRank=0;ClassPersistent50 zero={0};return !memcmp(&empty,&zero,sizeof(empty));}
 if(c->homunType<6001||c->homunType>6016||c->homunLevel<1||c->homunLevel>99||c->homunExp>1000000000||c->homunPoints>1000||c->homunHunger>100||c->homunIntimacy>100000||c->homunResting>1)return 0;
 if(!c->homunMaxHP||c->homunMaxHP>1000000||!c->homunMaxSP||c->homunMaxSP>1000000||c->homunHP>homun_maxhp50(c)||c->homunSP>homun_maxsp50(c))return 0;
 for(int i=0;i<6;i++)if(!c->homunStats[i]||c->homunStats[i]>1000)return 0;
 unsigned spent=0;for(int i=0;i<16;i++){if(!c->homunSkills[i])continue;const unsigned*t=NULL;for(unsigned n=0;n<sizeof(homunTree50)/sizeof(*homunTree50);n++)if(homunTree50[n][0]==c->homunType&&homunTree50[n][1]==(unsigned)i)t=homunTree50[n];if(!t||c->homunSkills[i]>t[2])return 0;for(int k=3;k<13;k+=2)if(t[k]!=65535&&c->homunSkills[t[k]]<t[k+1])return 0;spent+=c->homunSkills[i];}if(spent+c->homunPoints!=c->homunLevel/3)return 0;
 return 1;
}
static int save_valid(const SavedCharacter*s){if(s->expanded60.missionCount>99||s->expanded60.missionScore>1000000000||(s->expanded60.missionSource&&expanded_mob_kind60(s->expanded60.missionSource)<0))return 0;for(int i=0;i<3;i++)if(s->expanded60.feelMaps[i]>MYRO_MAP_COUNT43||(s->expanded60.hateSources[i]&&expanded_mob_kind60(s->expanded60.hateSources[i])<0))return 0;if(s->selectedAmmo60&&!ammo_rule60(s->selectedAmmo60))return 0;if(!appearance_valid58(s->appearance58))return 0;if(!memchr(s->name56,0,20))return 0;for(unsigned i=0;s->name56[i];i++)if((unsigned char)s->name56[i]<32||(unsigned char)s->name56[i]>126)return 0;if(s->sex55>1)return 0;if(s->jobSkillCarry55>49||((s->jobId<=6||(s->jobId>=J60_NINJA&&s->jobId<=J60_TAEKWON)||job_high_first52(s->jobId)||s->jobId==J52_SUPER_NOVICE)&&s->jobSkillCarry55))return 0;if(s->noviceQuest54b>2)return 0;if(!save_class_valid50(s))return 0;if(s->brokenWeapon48<0||s->brokenWeapon48>ITEM_COUNT||s->mounted48<0||s->mounted48>1||(s->mounted48&&((job_parent52(s->jobId)!=7&&job_parent52(s->jobId)!=11)||!s->ranks[112-3])))return 0;
 if((s->walkPercent45&&(s->walkPercent45<50||s->walkPercent45>125))||s->diagnosticsOff45<0||s->diagnosticsOff45>1)return 0;for(int k=0;k<LEARN_COUNT;k++)if(s->useRanks45[k]>(learnIds[k]==s->persistent50.copySkill?s->persistent50.copyRank:s->ranks[k]))return 0;
 if(s->level<1||s->level>TEST_LEVEL_CAP||s->joblevel<1||s->joblevel>TEST_JOB_CAP||!job_valid52(s->jobId))return 0;
 for(int i=0;i<6;i++)if(s->stats[i]<1||s->stats[i]>SOLO_STAT_CAP53)return 0;
 if(s->statPoints<0||s->statPoints>(stat_budget(s->level)+(job_transcendent52(s->jobId)?52:0))||s->statPoints+stat_spent(s->stats)!=(stat_budget(s->level)+(job_transcendent52(s->jobId)?52:0)))return 0;
 if(!combat_position_valid(s->home)||s->memoCount>3)return 0;for(unsigned i=0;i<s->memoCount;i++)if(!combat_position_valid(s->memos[i]))return 0;
 if(!job_valid52(s->jobId))return 0;int spent=0;for(int i=0;i<LEARN_COUNT;i++){if(s->ranks[i]>learnMax[i]||(s->ranks[i]&&!job_owns_skill48(s->jobId,learnJobs[i],learnIds[i])))return 0;if(!skill_quest(learnIds[i])&&(learnIds[i]!=338||s->jobId==0||s->jobId==J52_HIGH_NOVICE))spent+=s->ranks[i];}
 if(!skill_prereqs_for48(s->ranks,s->jobId)||!class_valid_prereqs48(s->jobId,s->ranks))return 0;
 int preset=s->jobId&&s->level==TEST_LEVEL_CAP&&s->joblevel==progression_job_cap43(s->jobId)&&s->skillPoints==0;for(int i=0;i<LEARN_COUNT&&preset;i++)if(!skill_quest(learnIds[i])&&job_owns_skill48(s->jobId,learnJobs[i],learnIds[i])&&s->ranks[i]!=learnMax[i])preset=0;if(s->skillPoints<0||s->skillPoints>TEST_JOB_CAP+49||(!preset&&spent+s->skillPoints!=(s->joblevel-1+(int)s->jobSkillCarry55)))return 0;
 if(s->quickKind>2||(s->quickKind==2&&s->quickId!=0)||(s->quickKind==0?!binding_valid(BIND_ITEM_BASE50+s->quickId):s->quickKind==1?!binding_valid(s->quickId):0))return 0;
 if(!binding_valid(s->rbBinding))return 0;
 if(s->zeny<0||s->zeny>1000000000)return 0;
 if(!s->sequence||s->level<1||s->level>TEST_LEVEL_CAP||s->joblevel<1||s->joblevel>progression_job_cap43(s->jobId))return 0;
 if(s->hp<0||s->hp>PLAYER_RESOURCE_CAP53||s->sp<0||s->sp>PLAYER_RESOURCE_CAP53)return 0; /* Current stats/buffs clamp on restore. */
 if(s->exp<0||s->jexp<0)return 0;
 if(s->level==TEST_LEVEL_CAP?s->exp!=0:s->exp>=progression_base_curve43(s->jobId)[s->level-1])return 0;
 if(s->joblevel==progression_job_cap43(s->jobId)?s->jexp!=0:s->jexp>=progression_job_curve43(s->jobId)[s->joblevel-1])return 0;
 if(s->kills<0||s->kills>1000000000||s->jellopy<0||s->jellopy>1000000000||s->clover<0||s->clover>1000000000||s->apples<0||s->apples>1000000000)return 0;
 if(!isfinite(s->x)||!isfinite(s->y)||s->x<8||s->y<8||s->mapId>=MYRO_MAP_COUNT43||s->x>=mapWidth43[s->mapId]-8||s->y>=mapHeight43[s->mapId]-8)return 0;
 if(!isfinite(s->faceX)||!isfinite(s->faceY))return 0;
 if(s->hotSlot>=12||s->mapId>=MYRO_MAP_COUNT43)return 0;
 for(int i=0;i<12;i++)if(!binding_valid(s->hotbar[i]))return 0;
 if(!owned_valid52(&s->owned52,item_rule52))return 0;
 int64_t cartWeight=0;for(unsigned box=0;box<3;box++){unsigned base=owned_base52(box);for(unsigned i=0;i<s->owned52.count[box];i++){const OwnedItem52*p=s->owned52.items+base+i;const OwnedRule52*r=item_rule52(p->sourceID);if(box==1)cartWeight+=(int64_t)p->quantity*r->weight;if(!box&&p->equipped&&!equipment_allowed52(equipment_rule52(p->sourceID),s->jobId,(s->jobId>=J60_NINJA?s->sex55:((s->jobId==16||s->jobId==J52_GYPSY)?0:1)),s->level))return 0;}}
 if(s->cartOwned<0||s->cartOwned>1||s->cartStyle<0||s->cartStyle>4||(!s->cartOwned&&(s->cartStyle||s->owned52.count[1]))||cartWeight>CART_WEIGHT_MAX)return 0;
 if(s->autoAttackToggle52>1||s->monsterView52>=MONSTER_VIEW_COUNT53)return 0;
 if(s->popupDisabled&~POP_ALL||s->tooltipsDisabled<0||s->tooltipsDisabled>1)return 0;
 float len=s->faceX*s->faceX+s->faceY*s->faceY;
 return len>.9f&&len<1.1f;
}
/* Fixed capacity sections permit appended skills/items without overlap.
 * Header stores actual catalog lengths; a reader refuses future longer catalogs.
 * All integer fields use explicit little endian writes, independent of C padding. */
static void save_payload50(unsigned char*p,const SavedCharacter*s){
 memset(p,0,SAVE_BYTES);save_put(p+5948,s->appearance58.hair);save_put(p+5952,s->appearance58.colour);save_put(p+5956,s->appearance58.cloth);boss_encode53(p+SAVE_BOSSES53,&s->bosses53);memcpy(p+5980,s->name56,20);save_put(p+5976,s->sex55+1);save_put(p+5972,s->jobSkillCarry55);save_put(p+5968,s->noviceQuest54b);save_put(p+5960,s->died53);save_put(p+5964,s->superSteelUsed53);memcpy(p,"MYROSV52",8);save_put(p+8,52);save_put(p+12,SAVE_BYTES);save_put(p+20,SAVE_WORLD43);
 save_put(p+SAVE_EXPANDED60,0x30365058u);save_put(p+SAVE_EXPANDED60+4,s->selectedAmmo60);for(int i=0;i<3;i++){save_put(p+SAVE_EXPANDED60+8+4*i,s->expanded60.feelMaps[i]);save_put(p+SAVE_EXPANDED60+20+4*i,s->expanded60.hateSources[i]);}save_put(p+SAVE_EXPANDED60+32,s->expanded60.missionSource);save_put(p+SAVE_EXPANDED60+36,s->expanded60.missionCount);save_put(p+SAVE_EXPANDED60+40,s->expanded60.missionScore);save_put(p+84,ITEM_COUNT);save_put(p+88,LEARN_COUNT);save_put(p+92,EQUIP_SLOTS46);save_put(p+108,1);
 save_put(p+16,s->sequence);
 save_put_float(p+24,s->x);
 save_put_float(p+28,s->y);
 save_put_float(p+32,s->faceX);
 save_put_float(p+36,s->faceY);
 save_put(p+40,s->hp);
 save_put(p+44,s->sp);
 save_put(p+48,s->level);
 save_put(p+52,s->joblevel);
 save_put(p+56,s->exp);
 save_put(p+60,s->jexp);
 save_put(p+64,s->kills);
 save_put(p+68,s->jellopy);
 save_put(p+72,s->clover);
 save_put(p+76,s->apples);
 save_put(p+80,s->rng);
 save_put(p+104,s->equipment);
 save_put(p+120,s->hotSlot);
 save_put(p+124,s->mapId);
 save_put(p+128,s->zeny);
 save_put(p+140,s->statPoints);
 save_put(p+144,s->jobId);
 save_put(p+148,s->skillPoints);
 save_put(p+168,s->quickKind);
 save_put(p+172,s->quickId);
 save_put(p+200,s->rbBinding);
 save_put(p+208,s->brokenWeapon48);
 save_put(p+212,s->mounted48);
 save_put(p+216,s->walkPercent45);
 save_put(p+220,s->diagnosticsOff45);
 save_put(p+260,s->memoCount);
 save_put(p+344,s->popupDisabled);
 save_put(p+424,s->cartOwned);
 save_put(p+428,s->cartStyle);
 save_put(p+504,s->tooltipsDisabled);save_put(p+508,s->autoAttackToggle52|(s->monsterView52<<8));
 memcpy(p+132,s->stats,6);
 save_put(p+248,s->home.map);save_put_float(p+252,s->home.x);save_put_float(p+256,s->home.y);
 for(int i=0;i<3;i++){save_put(p+264+i*12,s->memos[i].map);save_put_float(p+268+i*12,s->memos[i].x);save_put_float(p+272+i*12,s->memos[i].y);}
 for(int i=0;i<EQUIP_SLOTS46;i++)save_put(p+SAVE_EQUIP50+i*4,s->equipped46[i]);
 memcpy(p+SAVE_RANKS50,s->ranks,LEARN_COUNT);memcpy(p+SAVE_USE_RANKS50,s->useRanks45,LEARN_COUNT);
 for(int i=0;i<12;i++){p[SAVE_HOTBAR50+2*i]=s->hotbar[i];p[SAVE_HOTBAR50+2*i+1]=s->hotbar[i]>>8;}
 save_put(p+112,1);
 save_put(p+SAVE_CLASS50+0,s->persistent50.falcon);
 save_put(p+SAVE_CLASS50+4,s->persistent50.copySkill);
 save_put(p+SAVE_CLASS50+8,s->persistent50.copyRank);
 save_put(p+SAVE_CLASS50+12,s->persistent50.homunType);
 save_put(p+SAVE_CLASS50+16,s->persistent50.homunLevel);
 save_put(p+SAVE_CLASS50+20,s->persistent50.homunExp);
 save_put(p+SAVE_CLASS50+24,s->persistent50.homunPoints);
 save_put(p+SAVE_CLASS50+28,s->persistent50.homunHunger);
 save_put(p+SAVE_CLASS50+32,s->persistent50.homunIntimacy);
 save_put(p+SAVE_CLASS50+36,s->persistent50.homunResting);
 save_put(p+SAVE_CLASS50+40,s->persistent50.homunHP);
 save_put(p+SAVE_CLASS50+44,s->persistent50.homunSP);
 save_put(p+SAVE_CLASS50+48,s->persistent50.homunMaxHP);
 save_put(p+SAVE_CLASS50+52,s->persistent50.homunMaxSP);
 save_put(p+SAVE_CLASS50+56,s->persistent50.homunStats[0]);
 save_put(p+SAVE_CLASS50+60,s->persistent50.homunStats[1]);
 save_put(p+SAVE_CLASS50+64,s->persistent50.homunStats[2]);
 save_put(p+SAVE_CLASS50+68,s->persistent50.homunStats[3]);
 save_put(p+SAVE_CLASS50+72,s->persistent50.homunStats[4]);
 save_put(p+SAVE_CLASS50+76,s->persistent50.homunStats[5]);
 memcpy(p+SAVE_CLASS50+80,s->persistent50.homunSkills,16);
 unsigned ownedBytes=owned_encode52(p+SAVE_OWNED52,SAVE_BYTES-SAVE_OWNED52-4,&s->owned52,item_rule52);save_put(p+224,ownedBytes);
}
/* Disk checksums are generated only for an actual write, never for HUD dirtiness. */
static void save_encode(unsigned char*p,const SavedCharacter*s){save_payload50(p,s);save_put(p+SAVE_BYTES-4,save_crc(p,SAVE_BYTES-4));}
/* 1 valid, 0 corrupt/invalid, -1 unrecognized format: preserve without writes. */
static int save_decode(SavedCharacter*s,const unsigned char*p){
 if(memcmp(p,"MYROSV52",8)||save_u32(p+8)!=52||save_u32(p+12)!=SAVE_BYTES||save_u32(p+20)!=SAVE_WORLD43)return -1;
 if(save_crc(p,SAVE_BYTES-4)!=save_u32(p+SAVE_BYTES-4)||save_u32(p+108)!=1)return 0;
 unsigned items=save_u32(p+84),ranks=save_u32(p+88),slots=save_u32(p+92);
 if(items>ITEM_COUNT||ranks>LEARN_COUNT||slots>EQUIP_SLOTS46)return -1;
 if(items<3||!ranks||slots!=EQUIP_SLOTS46)return 0;
 static SavedCharacter t;memset(&t,0,sizeof(t));
 if(!boss_decode53(&t.bosses53,p+SAVE_BOSSES53))return 0;t.appearance58=(Appearance58){save_u32(p+5948),save_u32(p+5952),save_u32(p+5956)};if(!appearance_valid58(t.appearance58))return 0;memcpy(t.name56,p+5980,20);unsigned sex55=save_u32(p+5976);if(sex55>2)return 0;t.sex55=sex55?sex55-1:1;t.jobSkillCarry55=save_u32(p+5972);t.noviceQuest54b=save_u32(p+5968);t.superSteelUsed53=save_u32(p+5964);if(t.superSteelUsed53>1)return 0;t.died53=save_u32(p+5960);if(t.died53>1)return 0;t.sequence=save_u32(p+16);
 t.x=save_float(p+24);
 t.y=save_float(p+28);
 t.faceX=save_float(p+32);
 t.faceY=save_float(p+36);
 t.hp=save_u32(p+40);
 t.sp=save_u32(p+44);
 t.level=save_u32(p+48);
 t.joblevel=save_u32(p+52);
 t.exp=save_u32(p+56);
 t.jexp=save_u32(p+60);
 t.kills=save_u32(p+64);
 t.jellopy=save_u32(p+68);
 t.clover=save_u32(p+72);
 t.apples=save_u32(p+76);
 t.rng=save_u32(p+80);
 t.equipment=save_u32(p+104);
 t.hotSlot=save_u32(p+120);
 t.mapId=save_u32(p+124);
 t.zeny=save_u32(p+128);
 t.statPoints=save_u32(p+140);
 t.jobId=save_u32(p+144);
 t.skillPoints=save_u32(p+148);
 t.quickKind=save_u32(p+168);
 t.quickId=save_u32(p+172);
 t.rbBinding=save_u32(p+200);
 t.brokenWeapon48=save_u32(p+208);
 t.mounted48=save_u32(p+212);
 t.walkPercent45=save_u32(p+216);
 t.diagnosticsOff45=save_u32(p+220);
 t.memoCount=save_u32(p+260);
 t.popupDisabled=save_u32(p+344);
 t.cartOwned=save_u32(p+424);
 t.cartStyle=save_u32(p+428);
 t.tooltipsDisabled=save_u32(p+504);{unsigned v=save_u32(p+508);if(v&~0x3f01u)return 0;t.autoAttackToggle52=v&1;t.monsterView52=v>>8;}
 memcpy(t.stats,p+132,6);t.home=(WorldPosition){save_u32(p+248),save_float(p+252),save_float(p+256)};
 for(int i=0;i<3;i++)t.memos[i]=(WorldPosition){save_u32(p+264+i*12),save_float(p+268+i*12),save_float(p+272+i*12)};
 for(unsigned i=0;i<slots;i++){unsigned eq=save_u32(p+SAVE_EQUIP50+i*4);if(eq>items)return 0;t.equipped46[i]=eq;}
 memcpy(t.ranks,p+SAVE_RANKS50,ranks);memcpy(t.useRanks45,p+SAVE_USE_RANKS50,ranks);
 for(int i=0;i<12;i++)t.hotbar[i]=(unsigned)p[SAVE_HOTBAR50+2*i]|(unsigned)p[SAVE_HOTBAR50+2*i+1]<<8;
 if(save_u32(p+112)>1)return -1;
 if(save_u32(p+112)){
  t.persistent50.falcon=save_u32(p+SAVE_CLASS50+0);
  t.persistent50.copySkill=save_u32(p+SAVE_CLASS50+4);
  t.persistent50.copyRank=save_u32(p+SAVE_CLASS50+8);
  t.persistent50.homunType=save_u32(p+SAVE_CLASS50+12);
  t.persistent50.homunLevel=save_u32(p+SAVE_CLASS50+16);
  t.persistent50.homunExp=save_u32(p+SAVE_CLASS50+20);
  t.persistent50.homunPoints=save_u32(p+SAVE_CLASS50+24);
  t.persistent50.homunHunger=save_u32(p+SAVE_CLASS50+28);
  t.persistent50.homunIntimacy=save_u32(p+SAVE_CLASS50+32);
  t.persistent50.homunResting=save_u32(p+SAVE_CLASS50+36);
  t.persistent50.homunHP=save_u32(p+SAVE_CLASS50+40);
  t.persistent50.homunSP=save_u32(p+SAVE_CLASS50+44);
  t.persistent50.homunMaxHP=save_u32(p+SAVE_CLASS50+48);
  t.persistent50.homunMaxSP=save_u32(p+SAVE_CLASS50+52);
  t.persistent50.homunStats[0]=save_u32(p+SAVE_CLASS50+56);
  t.persistent50.homunStats[1]=save_u32(p+SAVE_CLASS50+60);
  t.persistent50.homunStats[2]=save_u32(p+SAVE_CLASS50+64);
  t.persistent50.homunStats[3]=save_u32(p+SAVE_CLASS50+68);
  t.persistent50.homunStats[4]=save_u32(p+SAVE_CLASS50+72);
  t.persistent50.homunStats[5]=save_u32(p+SAVE_CLASS50+76);
  memcpy(t.persistent50.homunSkills,p+SAVE_CLASS50+80,16);
 }
 unsigned ownedBytes=save_u32(p+224);if(ownedBytes>SAVE_BYTES-SAVE_OWNED52-4||owned_decode52(&t.owned52,p+SAVE_OWNED52,ownedBytes,item_rule52)!=1)return 0;
 if(ranks<312){if(t.jobId==0||t.jobId==J52_HIGH_NOVICE)t.skillPoints=t.joblevel-1;else t.ranks[310]=9;}
 if(save_u32(p+SAVE_EXPANDED60)&&save_u32(p+SAVE_EXPANDED60)!=0x30365058u)return -1;t.selectedAmmo60=save_u32(p+SAVE_EXPANDED60)?save_u32(p+SAVE_EXPANDED60+4):0;if(save_u32(p+SAVE_EXPANDED60)){for(int i=0;i<3;i++){t.expanded60.feelMaps[i]=save_u32(p+SAVE_EXPANDED60+8+4*i);t.expanded60.hateSources[i]=save_u32(p+SAVE_EXPANDED60+20+4*i);}t.expanded60.missionSource=save_u32(p+SAVE_EXPANDED60+32);t.expanded60.missionCount=save_u32(p+SAVE_EXPANDED60+36);t.expanded60.missionScore=save_u32(p+SAVE_EXPANDED60+40);}
 /* Apply the two cap-only points to the exact prior budget once on decode. */
 if(t.level==TEST_LEVEL_CAP&&job_valid52(t.jobId)&&t.statPoints>=0){int safe200=1;for(unsigned i=0;i<6;i++)if(t.stats[i]<1||t.stats[i]>SOLO_STAT_CAP53)safe200=0;if(safe200&&t.statPoints+stat_spent(t.stats)==stat_budget(t.level)+(job_transcendent52(t.jobId)?52:0)-2)t.statPoints+=2;}
 if(!save_valid(&t))return 0;*s=t;return 1;
}
static void save_restore(Combat*g,const SavedCharacter*s,float campX,float campY,CombatCanMove canMove,void*world){
 combat_init(g,campX,campY,canMove,world);
 boss_capture53(&g->bosses53,&s->bosses53);g->bossSeenUTC53=bossNow53;g->died53=s->died53;g->superSteelUsed53=s->superSteelUsed53;g->persistent50=s->persistent50;g->owned52=s->owned52;g->x=s->x;g->y=s->y;g->faceX=s->faceX;g->faceY=s->faceY;
 g->hp=s->hp;g->sp=s->sp;g->level=s->level;g->joblevel=s->joblevel;
 memcpy(g->stats,s->stats,6);g->statPoints=s->statPoints;g->jobId=s->jobId;g->walkPercent=s->walkPercent45?s->walkPercent45:100;g->diagnosticsOff45=s->diagnosticsOff45;memcpy(g->useRanks45,s->useRanks45,LEARN_COUNT);memcpy(g->name56,s->name56,20);if(!g->name56[0])memcpy(g->name56,"Novice",7);g->expanded60=s->expanded60;g->selectedAmmo60=s->selectedAmmo60;g->appearance58=s->appearance58;g->sex55=s->sex55;g->jobSkillCarry55=s->jobSkillCarry55;g->skillPoints=s->skillPoints;memcpy(g->ranks,s->ranks,LEARN_COUNT);
 g->maxhp=stat_maxhp(g);g->maxsp=stat_maxsp(g);g->exp=s->exp;g->jexp=s->jexp;
 g->brokenWeapon48=s->brokenWeapon48;g->mounted48=s->mounted48;g->kills=s->kills;g->jellopy=s->jellopy;g->clover=s->clover;g->apples=s->apples;g->rng=s->rng;
 /* Session timers and enemies start fresh; KO is preserved, with A available. */
 g->deadAt=-2;g->lastDamage=0;
 g->noviceQuest54b=s->noviceQuest54b;g->autoAttackToggle52=s->autoAttackToggle52;g->monsterView52=s->monsterView52;g->tooltipsDisabled=s->tooltipsDisabled;g->popupDisabled=s->popupDisabled;g->equipment=s->equipment;memcpy(g->equipped46,s->equipped46,sizeof(g->equipped46));g->cartOwned=s->cartOwned;g->cartStyle=s->cartStyle;memcpy(g->hotbar,s->hotbar,sizeof(g->hotbar));g->hotSlot=s->hotSlot;g->mapId=s->mapId;g->zeny=s->zeny;g->quickKind=s->quickKind;g->quickId=s->quickId;g->rbBinding=s->rbBinding;g->home=s->home;g->memoCount=s->memoCount;memcpy(g->memos,s->memos,sizeof(g->memos));expanded_login60(g);stat_refresh(g);
}
/* Test builds intentionally start fresh when the schema changes. */
#endif
