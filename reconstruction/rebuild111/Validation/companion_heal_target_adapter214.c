#define MYRO_HOST 1
#include "combat.h"
#include "campaign_battle200.h"
static Combat healGame214;
static int blocked214(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
unsigned target214(unsigned preference,unsigned hp,unsigned maxhp,unsigned blocked,const unsigned*rows){
 Combat*g=&healGame214;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=hp;g->maxhp=maxhp;g->time=10;if(blocked)g->canAim=blocked214;
 memset(&campaignParty200,0,sizeof campaignParty200);campaignParty200.count=3;
 for(unsigned i=0;i<3;i++){CampaignFollower200*m=campaignParty200.members+i;const unsigned*r=rows+i*8;m->id=r[0];m->map=r[1];m->initialized=r[2];m->hp=r[3];m->maxHP=r[4];memcpy(&m->x,r+5,4);memcpy(&m->y,r+6,4);}
 campaignConfig200.priority[COMP200_PIP]=preference;return(unsigned)party_heal_target200(g,campaignParty200.members+1);
}
