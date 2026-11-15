/* MIT. Bounded visual events; never affect damage, timing, saves or collision. */
#ifndef MYRO_ART_VISUAL39_H
#define MYRO_ART_VISUAL39_H
#include "art_catalog40.h"
#include "class_art50.h"
#define ART39_EVENTS 8
#define ART39_DRAW_LIMIT 40 /*32 Sight Rasher rays plus concurrent impacts; fixed2.5MiB GPU cap*/
typedef struct{int clip;float x,y,at;int follow,skill,bolts;float lead,startX,startY;int target45;unsigned life45;} Art39Event;
typedef struct{Art39Event events[ART39_EVENTS];float lastCast,lastTime;unsigned map,next;int initialized,lastPending;} Art39State;
static int art39_skill_clip(int id){if(id>=127||id==7)return class_art_clip50(id);switch(id){case 93:return 27;case 105:return 28;case 92:return 29;case 120:return 30;case 125:return 31;case 96:return 32;case 97:return 33;case 98:return 34;case 99:return 35;case 117:return 36;case 73:case 77:case 80:case 82:return -1;case 75:return 5;case 76:return 26;case 78:return 44;case 79:return 2;case 23:return 43;case 10:return 45;case 36:case 74:return 42;case 48:return -1;case 118:return 47;case 81:case 4:return -1;case 88:return 46;case 71:return 25;case 72:return -1;case 8:return 21;case 87:case 67:return 0;case 50:return 1;case 29:case 9:return 2;case 51:return 3;case 3:case 24:return 5;case 21:return 6;case 49:return 8;case 64:return 9;default:return -1;}}
static void art39_observe(Art39State*s,const Combat*g,unsigned map){
 if(!s->initialized||s->map!=map||g->time<s->lastTime){memset(s,0,sizeof(*s));for(int i=0;i<ART39_EVENTS;i++)s->events[i].clip=-1;s->initialized=1;s->map=map;s->lastCast=g->fxAt;}
 s->lastTime=g->time;
 if(s->lastCast!=g->fxAt){s->lastCast=g->fxAt;int clip=art39_skill_clip(g->fxSkill);if(g->fxSkill==136&&g->target>=0&&g->target<MOB_COUNT&&g->mobs[g->target].class50.splasherUntil>g->time)clip=-1;{Art39Event*e=&s->events[s->next++%ART39_EVENTS];*e=(Art39Event){clip,g->fxX,g->fxY,g->fxAt,g->fxSkill==67||g->fxSkill==50||g->fxSkill==92||g->fxSkill==125||(g->fxSkill>=96&&g->fxSkill<=99),g->fxSkill,art_air_clip40(g->fxSkill)>=0?(g->fxRank48?g->fxRank48:skill_rank(g,g->fxSkill)):0,0,g->x,g->y};if((g->fxSkill==76||g->fxSkill==23||g->fxSkill==78||(g->fxSkill>=127&&skill_cast_targeted(g->fxSkill)))&&g->target>=0&&g->target<MOB_COUNT){e->target45=g->target;e->life45=g->mobs[g->target].life;}if(g->fxSkill==210)e->follow=1;if(g->fxSkill>=127&&!skill_ground(g->fxSkill)&&!skill_cast_targeted(g->fxSkill))e->follow=1;if(g->fxSkill==23){e->target45=g->fxTarget200;e->life45=g->fxLife200;e->startX=g->fxFromX200;e->startY=g->fxFromY200;}if(g->fxSkill==23)e->bolts=((g->fxRank48?g->fxRank48:skill_rank(g,23))+1)/2;if(g->fxSkill==78||g->fxSkill==206){e->bolts=1;for(int k=0;k<SKILL_BURSTS49;k++)if(g->bursts49[k].active&&g->bursts49[k].skill==g->fxSkill&&g->bursts49[k].target==g->target)e->bolts=g->bursts49[k].hits;}if(e->bolts&&s->lastPending==g->fxSkill)e->lead=.4f;if(g->fxSkill==24&&s->lastPending==24)e->lead=.35f;}}
 s->lastPending=combat_casting(g)?g->spellCastId:0;
}
/* Equal integer cell widths and1px gaps. Half-second segments, capped12. */
#include "cast_layout43.h"
#endif
