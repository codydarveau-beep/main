/* Original Maya red-potion support: one atomic companion-record commit before
 * live HP/SP or inventory changes. No Combat/inventory clone or new heap cache. */
#ifndef MYRO_COMPANION_POTION215_H
#define MYRO_COMPANION_POTION215_H
typedef void(*PartyPotionNumber215)(Combat*,float,float,int);
static unsigned party_potion_amount215(unsigned research,unsigned vitality,unsigned missing){unsigned amount=((275*research+6050)/100)*(100+2*vitality)/100;return amount<missing?amount:missing;}
static int party_maya_support215(Combat*g,CampaignFollower200*m,unsigned slot,PartyPotionNumber215 number,PartyBoltCue204 cue){
 if(!campaignConfig200.skills[m->id]||g->time<m->skillAt||!party_skill_rank193(m,242)||g->owned52.count[0]>OWNED_BAG52)return 0;
 OwnedItem52*potion=NULL;for(unsigned i=0;i<g->owned52.count[0];i++){OwnedItem52*p=g->owned52.items+i;if(p->sourceID==501&&p->quantity&&!p->equipped){potion=p;break;}}
 if(!potion)return 0;
 int target=party_heal_target200(g,m);if(target==-2)return 0;CampaignFollower200*recipient=target>=0?party_member200((unsigned)target):NULL;
 float x=recipient?recipient->x:g->x,y=recipient?recipient->y:g->y;
 if(combat_dist(m->x,m->y,x,y)>64){m->ownsMove=1;party_walk_to200(g,m,x,y,64,.05f,slot,-1);return 1;}
 if(!party_line200(g,m->x,m->y,x,y))return 0;
 unsigned cost=party_skill_cost200(242,1);if(m->sp<cost)return 0;
 unsigned missing=recipient?recipient->maxHP-recipient->hp:(unsigned)(g->maxhp-g->hp),vitality=recipient?recipient->stats[2]:(unsigned)stat_value(g,2),amount=party_potion_amount215(party_skill_rank193(m,238),vitality,missing);if(!amount)return 0;
 unsigned char b[640];if(party_progress_load200(campaignPartyState200,b)<0||!party_vitals_put200(b,m->id,m->level,m->hp+(recipient==m?amount:0),m->sp-cost))return 0;
 if(recipient&&recipient!=m&&!party_vitals_put200(b,recipient->id,recipient->level,recipient->hp+amount,recipient->sp))return 0;
 unsigned uid=potion->uid;
 if(!party_progress_commit200(campaignPartyState200,b))return 0;
 /* Preflight holds this exact valid unequipped stack; commit has no inventory
  * side effects and there is no intervening gameplay callback. */
 owned_remove52(&g->owned52,0,uid,1);m->sp-=cost;
 if(recipient)recipient->hp+=amount;else g->hp+=(int)amount;
 m->lastSkill=242;m->attackAt=g->time;m->attackUntil=g->time+.6f;m->nextAttack=m->skillAt=g->time+1;m->ownsMove=1;m->moving=0;
 number(g,x,y,(int)amount);cue(g,SKILL_HEAL,x,y);return 1;
}
#endif
