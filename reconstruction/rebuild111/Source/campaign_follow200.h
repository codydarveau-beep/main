/* MIT. Three bounded followers; combat can own movement for the current frame. */
#ifndef MYRO_CAMPAIGN_FOLLOW200_H
#define MYRO_CAMPAIGN_FOLLOW200_H
#include "campaign_companions200.h"
#include "campaign_party_state200.h"
#define CAMPAIGN_PARTY_SLOTS200 3
#define CAMPAIGN_NO_MEMBER200 255u
typedef struct{unsigned id,map,moving,ownsMove,level,hp,sp,maxHP,maxSP,life,initialized;unsigned char stats[6],buffRank[2];float buffUntil[3];unsigned shieldHP,shieldHits;int target,pendingTarget,healTarget;unsigned targetLife,pendingLife,pendingSkill,pendingRank,lastSkill,blockedTarget,blockedLife;float x,y,faceX,faceY,stuck,elapsed,attackAt,attackUntil,nextAttack,impactAt,castUntil,hurtAt,skillAt,regenAt,thinkAt,blockedUntil;unsigned exp,jobLevel,jobExp,job,remainingHits204;float groundX205,groundY205;}CampaignFollower200;
typedef struct{CampaignFollower200 members[CAMPAIGN_PARTY_SLOTS200];unsigned count;}CampaignFollow200;
static CampaignFollow200 campaignParty200;
static int party_stat200(const CampaignFollower200*m,unsigned n,float now){int value=m->stats[n];if(m->buffUntil[0]>now&&(n==0||n==3||n==4))value+=m->buffRank[0];if(m->buffUntil[1]>now&&n==1)value+=2+m->buffRank[1];return value;}
static float party_walk_speed200(const CampaignFollower200*m,float now){return m->buffUntil[1]>now?100.f:80.f;}
/* Caller supplies selected recruited IDs; reject duplicates and reserve-only IDs. */
static int campaign_follow_select200(CampaignFollow200*f,unsigned recruits,const unsigned*ids,unsigned count){if(count>3||(!ids&&count)||recruits>=(1u<<19))return 0;unsigned mask=0;for(unsigned i=0;i<count;i++){if(ids[i]>=19||!(recruits&(1u<<ids[i]))||(mask&(1u<<ids[i])))return 0;mask|=1u<<ids[i];}CampaignFollow200 next={0};next.count=count;for(unsigned i=0;i<count;i++){next.members[i].id=ids[i];next.members[i].map=~0u;for(unsigned k=0;k<f->count;k++)if(f->members[k].id==ids[i])next.members[i]=f->members[k];}*f=next;return 1;}
/* Warp only onto a tested clear point near the player; never invent a walkable
 * location on another floor or teleport onto a quest's restricted ledge. */
static int campaign_follow_place200(CampaignFollower200*m,const Combat*g,unsigned slot){static const float offsets[][2]={{-12,-12},{12,-12},{0,-20},{-8,0},{8,0},{0,0}};for(unsigned k=0;k<6;k++){unsigned j=(k+slot)%6;float x=g->x+offsets[j][0],y=g->y+offsets[j][1];if(g->canMove&&!g->canMove(g->world,g->x,g->y,x,y))continue;m->x=x;m->y=y;m->map=g->mapId;m->faceX=g->faceX;m->faceY=g->faceY;m->moving=0;m->stuck=0;m->pendingSkill=0;m->target=m->pendingTarget=-1;m->attackUntil=m->castUntil=0;return 1;}m->moving=0;return 0;}
static void campaign_follow_tick200(CampaignFollow200*f,Combat*g,float dt,int paused){if(g->hp<=0){for(unsigned i=0;i<f->count;i++)f->members[i].moving=0;return;}if(paused||dt<=0||!isfinite(dt)||!isfinite(g->x)||!isfinite(g->y))return;if(dt>.05f)dt=.05f;for(unsigned i=0;i<f->count;i++){CampaignFollower200*m=f->members+i;if(m->ownsMove)continue;m->moving=0;if(m->initialized&&(!m->hp||g->time<m->attackUntil||g->time<m->castUntil))continue;if(m->map!=g->mapId){campaign_follow_place200(m,g,i);continue;}float dx=g->x-m->x,dy=g->y-m->y,d=sqrtf(dx*dx+dy*dy);if(d>192||m->stuck>=2){campaign_follow_place200(m,g,i);continue;}if(d<=20){m->stuck=0;continue;}float speed=party_walk_speed200(m,g->time),step=fminf(speed*dt,d-20),x=m->x,y=m->y;combat_face(&m->faceX,&m->faceY,dx,dy);m->moving=combat_move(g,&m->x,&m->y,x+dx/d*step,y+dy/d*step);if(m->moving){float remaining=combat_dist(g->x,g->y,m->x,m->y);if(d-remaining>step*.1f)m->stuck=0;else m->stuck+=dt;m->elapsed+=dt;}else m->stuck+=dt;}}
#endif
