/* MIT. Fixed-capacity solo class state; persistent fields are serialized by name. */
#ifndef MYRO_CLASS_STATE50_H
#define MYRO_CLASS_STATE50_H
#include "class_ids50.h"
typedef struct {uint32_t uid,script;float until;} ItemTrigger52;
typedef struct {uint32_t key;float next;} ItemPulse52;
typedef struct {int status,bonus,value;uint32_t source;float until;} ItemUseBuff52;
#define CLASS_TRAPS50 12
#define CLASS_AREAS50 6
#define CLASS_SUMMONS50 8
#define CLASS_DELAYED52 8
typedef struct {unsigned skill,rank,map,job,life;int target;float at;} ClassDelayed52;
typedef struct {unsigned falcon,copySkill,copyRank,homunType,homunLevel,homunExp,homunPoints;
 unsigned homunHunger,homunIntimacy,homunResting,homunHP,homunSP,homunMaxHP,homunMaxSP,homunStats[6];
 unsigned char homunSkills[16];} ClassPersistent50;
typedef struct {float until[SKILL_CAP50-127],next[SKILL_CAP50-127];unsigned char level[SKILL_CAP50-127];
 ItemUseBuff52 itemUseBuffs52[16];ItemTrigger52 itemTriggers52[16];ItemPulse52 itemPulses52[32];float itemElementUntil52;int itemElement52;
 ClassDelayed52 delayed52[CLASS_DELAYED52],doubleBolt52[CLASS_DELAYED52],itemSpells52[8];int memorizeCasts52,rejectHits52,chaseStrength52;float chaseStrengthUntil52;
 float runFaceX52,runFaceY52;float basilicaX52,basilicaY52,regenBlockedUntil52;int berserkWas52,sacrificeRank52,sacrificeHits52;float gospelX52,gospelY52;
 float rootUntil;int rootTarget,rootRank;unsigned rootLife;
 float esmaUntil60,kaahiAt60,expandedStunUntil60;
 float sgMiracleUntil60,sgChoiceUntil60;unsigned sgChoiceSkill60,sgChoiceRank60,sgChoiceValue60,sgKnowledgeMap60;
 float tkComboUntil60,spurtUntil60;unsigned tkComboSkill60,tkComboLife60;int tkComboTarget60;
 unsigned char ninjaCells60[CLASS_AREAS50][25];
 float coinUntil60[10];unsigned flingSpent60;
 float sphereUntil[5],comboUntil,regen,songUntil,songNext,songStarted,songDrain,homunHungerAt,homunAttackAt,homunRegenAt;
 int spheres,comboSkill,comboTarget,song,songRank,lastSong,lastSongRank,homunTarget,craftTool;unsigned comboLife;
 float homunX,homunY,homunFaceX,homunFaceY,homunHurtAt,homunLastAttack;
 unsigned homunMoving;float homunBuffUntil[16],homunCooldown[16],homunFxAt,homunSPRegenAt;int homunFx,homunHold,homunDealing;unsigned homunMap;} ClassTransient50;
typedef struct {int id,rank,triggered;unsigned map;float x,y,until,next,created;unsigned mercenary180,dex180,int180,atk180;float originX180,originY180;} ClassTrap50;
typedef struct {int id,rank,hits,power;unsigned map;float x,y,until,next,created;} ClassArea50;
typedef struct {int kind,rank,hp,target,triggered;unsigned map;float x,y,until,next,created,hurtAt,attackAt;} ClassSummon50;
typedef struct {float swooUntil60,eskeUntil60,eskaUntil60,eskaNext60;unsigned eskaDefense60;float suitonUntil60;unsigned suitonRank60;float flingUntil60;unsigned flingCoins60;float sleepUntil,rootUntil,lexUntil,closeUntil,splasherUntil,stripUntil[4];int splasherRank,sp;unsigned initialized,coinStolen;float silenceUntil,confuseUntil,charmUntil,bladeUntil,danceUntil;int danceMove,danceAttack;float bleedUntil,bleedNext,jointUntil52[6],gospelNext52,gospelDef52,gospelAtk52,gospelFlee52,gospelSlow52,curseUntil52;float tarotUntil52,tarotVisualAt52;int tarotVisual52,tarotVisualSelf52,tarotAtk52,tarotMatk52,tarotHit52,tarotFlee52,tarotDef52;float criticalWoundUntil52,slowCastUntil52;int criticalWoundRank52,slowCastRank52;float cropUntil52,mindUntil52,webUntil52;int mindRank52,webRoot52,webStacks52,soulChanged52;int companionTarget;unsigned homunDamage;} ClassMob50;
static unsigned homun_maxhp50(const ClassPersistent50*p){return p->homunMaxHP+p->homunMaxHP*2*p->homunSkills[6]/100;}
static unsigned homun_maxsp50(const ClassPersistent50*p){unsigned r=p->homunSkills[2];return p->homunMaxSP+(r?(1+r/2-r/4+r/5)*p->homunMaxSP/100:0);}
#endif
