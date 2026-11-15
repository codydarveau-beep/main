/* Uses the existing utility window skin and controller navigation. */
static void ui_mercenary180(const Combat*g,int choice){const Mercenary180*m=&g->mercenary180;const MercenaryData180*d=mercenary_data180(m->source);ui_panel(100,76,440,328,"Mercenary",1,-1);if(!d){ui_scaled(114,112,.9f,"No mercenary is currently hired.");ui_scaled(114,140,.85f,"Hire at Prontera,Payon Archer Village or Izlude.");ui_hint64(114,365,.8f,"B: close");return;}
 ui_scaled(114,108,.9f,"%s | Level %u | %u:%02u remaining",d->name,d->level,m->remaining/60000,m->remaining/1000%60);ui_scaled(114,134,.85f,"HP %u/%u   SP %u/%u",m->hp,mercenary_maxhp180(m),m->sp,mercenary_maxsp180(m));ui_scaled(114,157,.8f,"Kills %u | Loyalty %u",m->kills,m->faith[mercenary_guild180(m->source)]);
 unsigned rows=skill_utility_rows(g);for(unsigned i=0;i<rows;i++){int y=190+i*24;ui_cell(110,y-2,420,23,choice==(int)i);if(i<2)ui_scaled(120,y,.85f,"%s",i?"Dismiss mercenary":m->hold?"Follow only (select to assist)":"Assist your target (select to hold fire)");else{unsigned id=d->skill[i-2],rank=d->rank[i-2];const MercenarySkill180*s=mercenarySkills180+id-8201;ui_scaled(120,y,.85f,"%s %u - %d SP",s->name,rank,s->sp[rank-1]);}}
 ui_hint64(114,350,.8f,"A: command / use skill   B: close");ui_fit47(114,377,410,.75f,g->log);
}

/* Uses the existing utility window skin and controller navigation. */
#include "campaign_state200.h"
#include "campaign_companions200.h"
static void(*campaignPartyDraw200)(const Combat*,int);
static void ui_companions191(const Combat*g,int choice){if(campaignPartyDraw200){campaignPartyDraw200(g,choice);return;}(void)g;(void)choice;Campaign200 c;int ready=campaignRosterState200&&campaign_load200(campaignRosterState200,&c)==1;unsigned count=0;if(ready)for(unsigned id=0;id<19;id++)count+=(c.recruits>>id)&1;unsigned rows=count<3?count:3;int height=rows?62+(int)rows*42:110;ui_panel(140,130,360,height,"Companions",1,-1);if(!rows){ui_scaled(158,168,1,"No companions have joined your journey.");ui_hint64(158,130+height-25,.9f,"B: close");return;}unsigned row=0;for(unsigned id=0;id<19&&row<rows;id++)if(c.recruits&(1u<<id)){int y=161+(int)row*42;pb_fill(151,y-2,338,37,0xffe9eff5);ui_scaled(158,y,1,"%s",campaignCompanions200[id].name);ui_scaled(158,y+17,.9f,"%s path",job_name(campaignCompanions200[id].career));row++;}ui_hint64(158,130+height-25,.9f,"B: close");}
