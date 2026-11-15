/* MIT. User-priced reset service; costs and material removal commit together. */
#ifndef MYRO_RESET_SERVICE55_H
#define MYRO_RESET_SERVICE55_H
enum{RESET_STATS55,RESET_SKILLS55,RESET_BOTH55,RESET_COUNT55};
static const unsigned resetZeny55[RESET_COUNT55]={5000,2500,7000};
static const unsigned resetJellopy55[RESET_COUNT55]={200,50,225};
static int reset_material55(const OwnedItem52*p){return p->sourceID==909&&p->quantity&&p->identified&&!p->equipped&&!p->bound&&!p->refine&&!(p->flags&~OWNED_LEGACY_STACK52)&&!(p->cards[0]|p->cards[1]|p->cards[2]|p->cards[3]);}
static unsigned reset_material_count55(const Combat*g){unsigned n=0;for(unsigned i=0;i<g->owned52.count[0];i++)if(reset_material55(g->owned52.items+i))n+=g->owned52.items[i].quantity;return n;}
static void reset_skills55(Combat*g){
 for(unsigned i=0;i<LEARN_COUNT;i++){if(skill_quest(learnIds[i])||(learnIds[i]==338&&g->jobId!=0&&g->jobId!=J52_HIGH_NOVICE))continue;g->ranks[i]=g->useRanks45[i]=0;}
 g->skillPoints=g->joblevel-1+g->jobSkillCarry55;g->persistent50.falcon=0;g->persistent50.copySkill=g->persistent50.copyRank=0;if(g->persistent50.homunType)g->persistent50.homunResting=1;g->mounted48=0;
 /* Returning an occupied cart is refused before payment; no stored item is lost. */
 g->cartOwned=g->cartStyle=0;g->quickenLeft=g->counterLeft=g->sightblasterLeft=g->magicAmpLeft=0;memset(g->fields,0,sizeof(g->fields));memset(g->barriers,0,sizeof(g->barriers));combat_support_clear(g);g->angelusLeft=0;g->angelusRank=0;g->endureLeft=0;g->endureHits=0;memset(g->buffs,0,sizeof(g->buffs));memset(g->buffLevels,0,sizeof(g->buffLevels));g->shieldHP=g->shieldHits=0;memset(g->skillCD,0,sizeof(g->skillCD));g->castDelay=0;combat_interrupt_cast(g);g->autoAttack=0;g->approachSkill53=0;g->route53.state=0;
 for(unsigned i=0;i<12;i++){unsigned id=g->hotbar[i];if(id<SKILL_COUNT&&id&&!skill_rank(g,id))g->hotbar[i]=BIND_EMPTY50;}if(g->rbBinding<SKILL_COUNT&&g->rbBinding&&!skill_rank(g,g->rbBinding))g->rbBinding=BIND_EMPTY50;if(g->quickKind==1&&g->quickId&&!skill_rank(g,g->quickId)){g->quickKind=2;g->quickId=0;}inventory_reconcile46(g);
}
static int reset_apply55(Combat*g,unsigned choice){
 if(choice>=RESET_COUNT55||g->hp<=0)return 0;
 if(g->zeny<(int)resetZeny55[choice]){combat_notice(g,POP_ITEMS,"Need %u Zeny. Nothing spent.",resetZeny55[choice]);return 0;}
 if(choice!=RESET_STATS55&&g->owned52.count[1]){combat_notice(g,POP_ITEMS,"Store the items in your cart before resetting skills.");return 0;}
 if(reset_material_count55(g)<resetJellopy55[choice]){combat_notice(g,POP_ITEMS,"Need %u plain Jellopies. Nothing spent.",resetJellopy55[choice]);return 0;}
 OwnedItems52*trial=malloc(sizeof(*trial));if(!trial){combat_notice(g,POP_ITEMS,"Cannot prepare reset. Nothing spent.");return 0;}*trial=g->owned52;unsigned left=resetJellopy55[choice];
 while(left){OwnedItem52*p=NULL;for(unsigned i=0;i<trial->count[0];i++)if(reset_material55(trial->items+i)){p=trial->items+i;break;}if(!p){free(trial);return 0;}unsigned n=p->quantity<left?p->quantity:left;if(owned_remove52(trial,0,p->uid,n)!=OWNED_OK52){free(trial);return 0;}left-=n;}
 g->owned52=*trial;free(trial);g->zeny-=resetZeny55[choice];if(choice!=RESET_SKILLS55){memset(g->stats,1,sizeof(g->stats));g->statPoints=stat_total48(g);}if(choice!=RESET_STATS55)reset_skills55(g);stat_refresh(g);combat_notice(g,POP_ITEMS,"Mmm,yummy Jellopies! Your %s feel brand new!",choice==RESET_STATS55?"stats":choice==RESET_SKILLS55?"skills":"stats and skills");return 1;
}
#endif
