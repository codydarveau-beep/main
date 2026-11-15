/* MIT. Existing single-player character services for original NPC scripts. */
#ifndef MYRO_NPC_PLAYER55_H
#define MYRO_NPC_PLAYER55_H
#include "npc_runtime55.h"
#include "npc_items55.h"
#include "npc_item_commands55.h"
#include "npc_job_change55.h"
#include "npc_appearance59.h"
#include "npc_equipment59.h"
typedef struct{Combat*game;unsigned sex;const char*name;uint32_t characterId,accountId;NpcItemOverflow55 overflow;void*itemContext;}NpcPlayer55;
static int npc_player_read55(void*context,const NpcValue55*ref,NpcValue55*out){NpcPlayer55*p=context;Combat*g=p->game;const char*n=ref->text;int64_t value;
 if(!strcmp(n,"Class"))value=job_source52(g->jobId);else if(!strcmp(n,"BaseJob"))value=npc_base_job55(g->jobId,p->sex);else if(!strcmp(n,"BaseClass"))value=npc_base_class55(g->jobId);else if(!strcmp(n,"Upper"))value=job_transcendent52(g->jobId)?1:0;else if(!strcmp(n,"Sex"))value=p->sex;
 else if(!strcmp(n,"Zeny"))value=g->zeny;else if(!strcmp(n,"BaseLevel"))value=g->level;else if(!strcmp(n,"JobLevel"))value=g->joblevel;else if(!strcmp(n,"StatusPoint"))value=g->statPoints;else if(!strcmp(n,"SkillPoint"))value=g->skillPoints;
 else if(!strcmp(n,"Hp"))value=g->hp;else if(!strcmp(n,"MaxHp"))value=g->maxhp;else if(!strcmp(n,"Sp"))value=g->sp;else if(!strcmp(n,"MaxSp"))value=g->maxsp;else if(!strcmp(n,"Weight"))value=inventory_weight(g);else if(!strcmp(n,"MaxWeight"))value=inventory_weight_max(g);
 else if(!strcmp(n,"BaseExp"))value=g->exp;else if(!strcmp(n,"JobExp"))value=g->jexp;else if(!strcmp(n,"NextBaseExp"))value=g->level<TEST_LEVEL_CAP?progression_base_curve43(g->jobId)[g->level-1]:0;else if(!strcmp(n,"NextJobExp"))value=job_next(g);else return-1;
 if(ref->index)return 0;*out=npc_vm_number55(value);return 1;
}
static int npc_player_write55(void*context,const NpcValue55*ref,const NpcValue55*v){NpcPlayer55*p=context;Combat*g=p->game;const char*n=ref->text;
 if(strcmp(n,"Zeny")&&strcmp(n,"BaseLevel")&&strcmp(n,"JobLevel")&&strcmp(n,"StatusPoint")&&strcmp(n,"SkillPoint")&&strcmp(n,"Hp")&&strcmp(n,"Sp")&&strcmp(n,"BaseExp")&&strcmp(n,"JobExp")){NpcValue55 ignored;return npc_player_read55(context,ref,&ignored)>=0?0:-1;}
 if(ref->index||v->kind!=N55_NUMBER_KIND||v->number<0||v->number>INT_MAX)return 0;int value=(int)v->number;
 if(!strcmp(n,"Zeny"))g->zeny=value>1000000000?1000000000:value;
 else if(!strcmp(n,"Hp"))g->hp=value>g->maxhp?g->maxhp:value;else if(!strcmp(n,"Sp"))g->sp=value>g->maxsp?g->maxsp:value;
 else if(!strcmp(n,"StatusPoint"))g->statPoints=value;else if(!strcmp(n,"SkillPoint"))g->skillPoints=value;
 else if(!strcmp(n,"BaseExp")){if((int64_t)g->statPoints+stat_budget(TEST_LEVEL_CAP)-stat_budget(g->level)>INT_MAX||(int64_t)g->skillPoints+job_cap(g)-g->joblevel>INT_MAX)return 0;g->exp=value;combat_gain_exp(g,0,0);}else if(!strcmp(n,"JobExp")){if((int64_t)g->statPoints+stat_budget(TEST_LEVEL_CAP)-stat_budget(g->level)>INT_MAX||(int64_t)g->skillPoints+job_cap(g)-g->joblevel>INT_MAX)return 0;g->jexp=value;combat_gain_exp(g,0,0);}
 else if(!strcmp(n,"BaseLevel")){if(value<1)return 0;if(value>TEST_LEVEL_CAP)value=TEST_LEVEL_CAP;if(value>g->level){int delta=stat_budget(value)-stat_budget(g->level);if((int64_t)g->statPoints+delta>INT_MAX)return 0;g->statPoints+=delta;}g->level=value;g->exp=0;stat_refresh(g);}
 else{if(value<1)return 0;if(value>job_cap(g))value=job_cap(g);if(value>=g->joblevel){int delta=value-g->joblevel;if((int64_t)g->skillPoints+delta>INT_MAX)return 0;g->skillPoints+=delta;}g->joblevel=value;g->jexp=0;stat_refresh(g);}return 1;
}
static int npc_player_skill_id55(NpcMachine55*m,NpcValue55 arg,uint32_t*out){NpcValue55 value;int64_t source;if(!npc_vm_value55(m,arg,&value))return 0;if(value.kind==N55_STRING_KIND){if(!npc_constant55(value.text,&source))return 0;}else source=value.number;if(source<0||source>UINT32_MAX)return 0;*out=(uint32_t)source;return 1;}
/* -1 delegates map, NPC metadata, presentation and additional systems to their adapters. */
static int npc_player_command55(NpcPlayer55*p,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){Combat*g=p->game;int64_t a,b;int equipment59=npc_equipment_command59(g,m,name,args,count,out);if(equipment59>=0)return equipment59;int appearance59=npc_appearance_command59(g,m,name,args,count,out);if(appearance59>=0)return appearance59;*out=npc_vm_number55(0);int itemStatus=npc_item_command55(g,p->accountId,m,name,args,count,out,p->overflow,p->itemContext);if(itemStatus>=0)return itemStatus;
 if(!strcmp(name,"checkmount")||!strcmp(name,"hascashmount")||!strcmp(name,"checkcart")||!strcmp(name,"checkfalcon")){if(count)return N55_ERROR;*out=npc_vm_number55(!strcmp(name,"checkmount")?!!g->mounted48:!strcmp(name,"checkcart")?(g->cartOwned?g->cartStyle+1:0):!strcmp(name,"checkfalcon")?!!g->persistent50.falcon:0);return N55_READY;}
 if(!strcmp(name,"setcart")){a=1;if(count>1||(count&&!npc_vm_integer55(m,args[0],&a))||a<0||a>9)return N55_ERROR;if(!a){if(g->owned52.count[1])return N55_ERROR;g->cartOwned=g->cartStyle=0;}else{if(!skill_rank(g,63))return N55_ERROR;g->cartOwned=1;g->cartStyle=(unsigned)a-1;}return N55_READY;}
 if(!strcmp(name,"isequipped")){if(!count)return N55_ERROR;for(unsigned j=0;j<count;j++){if(!npc_vm_integer55(m,args[j],&a)||a<=0||a>UINT32_MAX)return N55_ERROR;int found=0;for(unsigned i=0;i<g->owned52.count[0]&&!found;i++){const OwnedItem52*item=g->owned52.items+i;if(!item->equipped)continue;if(item->sourceID==(uint32_t)a)found=1;for(unsigned k=0;k<4;k++)if(item->cards[k]==(uint32_t)a)found=1;}if(!found)return N55_READY;}*out=npc_vm_number55(1);return N55_READY;}
 if(!strcmp(name,"resetlvl")){if(count!=1||!npc_vm_integer55(m,args[0],&a)||a!=1)return N55_ERROR;g->level=g->joblevel=1;g->exp=g->jexp=g->skillPoints=g->jobSkillCarry55=0;for(unsigned i=0;i<6;i++)g->stats[i]=1;memset(g->ranks,0,sizeof(g->ranks));memset(g->useRanks45,0,sizeof(g->useRanks45));g->statPoints=stat_total48(g);g->mounted48=0;g->persistent50.falcon=0;combat_support_clear(g);if(g->jobId==J52_HIGH_NOVICE){int first=skill_rank_index(1);if(first>=0)g->ranks[first]=1;g->ranks[312]=1;}inventory_reconcile46(g);stat_refresh(g);g->hp=g->maxhp;g->sp=g->maxsp;return N55_READY;}
 if(!strcmp(name,"playerattached")){if(count)return N55_ERROR;*out=npc_vm_number55(p->accountId);return N55_READY;}
 if(!strcmp(name,"getskilllv")){uint32_t source;if(count!=1||!npc_player_skill_id55(m,args[0],&source))return N55_ERROR;*out=npc_vm_number55(npc_item_skill_level55(g,source));return N55_READY;}
 if(!strcmp(name,"jobchange")){if(count<1||count>2||!npc_vm_integer55(m,args[0],&a)||a<0||a>65535)return N55_ERROR;b=0;if(count==2&&(!npc_vm_integer55(m,args[1],&b)||b<0||b>2))return N55_ERROR;if(b==2)return N55_ERROR;if(b==1&&a<4001)a+=4001;int native=npc_native_job55((unsigned)a);return native>=0&&npc_change_job55(g,(unsigned)native)?N55_READY:N55_ERROR;}
 if(!strcmp(name,"skill")){uint32_t source;int64_t flag=1;if(count<2||count>3||!npc_player_skill_id55(m,args[0],&source)||!npc_vm_integer55(m,args[1],&a)||a<0||a>255||(count==3&&!npc_vm_integer55(m,args[2],&flag)))return N55_ERROR;if(source==681){if(flag!=3||a>10)return N55_ERROR;g->carryTraining180=(unsigned)a;return N55_READY;}int native=npc_native_skill55(source),k=native>=0?skill_rank_index((unsigned)native):-1;if(k<0||flag||a>learnMax[k]||!skill_quest((unsigned)native))return N55_ERROR;g->ranks[k]=(unsigned char)a;if(g->useRanks45[k]>a)g->useRanks45[k]=(unsigned char)a;stat_refresh(g);return N55_READY;}
 if(!strcmp(name,"jobname")){if(count!=1||!npc_vm_integer55(m,args[0],&a)||a<0||a>65535)return N55_ERROR;int native=npc_native_job55((unsigned)a);*out=npc_vm_string55(native>=0?job_name((unsigned)native):"Unknown");return N55_READY;}
 if(!strcmp(name,"getgroupid")||!strcmp(name,"getgmlevel")){if(count)return N55_ERROR;return N55_READY;}
 if(!strcmp(name,"getcharid")){if(count!=1||!npc_vm_integer55(m,args[0],&a)||a<0||a>3)return N55_ERROR;*out=npc_vm_number55(a==0?p->characterId:a==3?p->accountId:0);return N55_READY;}
 if(!strcmp(name,"strcharinfo")){if(count!=1||!npc_vm_integer55(m,args[0],&a)||a<0||a>3)return N55_ERROR;if(a==3)return-1;*out=npc_vm_string55(a==0?(p->name?p->name:"Adventurer"):"");return N55_READY;}
 if(!strcmp(name,"getexp")){if(count!=2||!npc_vm_integer55(m,args[0],&a)||!npc_vm_integer55(m,args[1],&b)||a<0||a>INT_MAX||b<0||b>INT_MAX)return N55_ERROR;if((int64_t)g->statPoints+stat_budget(TEST_LEVEL_CAP)-stat_budget(g->level)>INT_MAX||(int64_t)g->skillPoints+job_cap(g)-g->joblevel>INT_MAX)return N55_ERROR;combat_gain_exp(g,(int)a,(int)b);return N55_READY;}
 if(!strcmp(name,"percentheal")||!strcmp(name,"heal")){if(count!=2||!npc_vm_integer55(m,args[0],&a)||!npc_vm_integer55(m,args[1],&b)||a<INT32_MIN||a>INT32_MAX||b<INT32_MIN||b>INT32_MAX)return N55_ERROR;unsigned partyHP=!strcmp(name,"percentheal")&&a>=100,partySP=!strcmp(name,"percentheal")&&b>=100;if((partyHP||partySP)&&combat_party_recover200&&!combat_party_recover200(g,partyHP,partySP))return N55_ERROR;if(!strcmp(name,"percentheal")){a=(int64_t)g->maxhp*a/100;b=(int64_t)g->maxsp*b/100;}a+=g->hp;b+=g->sp;g->hp=(int)(a<0?0:a>g->maxhp?g->maxhp:a);g->sp=(int)(b<0?0:b>g->maxsp?g->maxsp:b);return N55_READY;}
 return-1;
}
#endif
