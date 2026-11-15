/* Recovered authored interaction rules. Pure decisions precede durable writes. */
#ifndef MYRO_CAMPAIGN_STAGE_RULES198_H
#define MYRO_CAMPAIGN_STAGE_RULES198_H
#include "campaign_stage_proof_data198.h"
typedef struct{unsigned write,objectives,message,talk;}CampaignStageDecision198;
static unsigned campaign_stage_gate198(unsigned cursor){if(cursor==34)return 8;if(cursor<12)return cursor==3||cursor==6||cursor==9?9:7;return cursor<36?campaignStageGates198[cursor]:65535;}
static unsigned campaign_stage_enemies198(const CampaignStageDefinition200*d){unsigned n=d->recoveredFields197[1],shift=d->recoveredFields197[3]+(d->cursor==10||d->cursor>=12?8:0);return n&&n<32&&shift<32?((1u<<n)-1)<<shift:0;}
/* The released world offers one lead contact, except the guild scene's third
 * actor. Other actors remain visible and retain their authored dialogue roles. */
static unsigned campaign_stage_lead198(const CampaignStageDefinition200*d){return d->cursor==5?2:0;}
static void campaign_stage_document198(const CampaignStageDefinition200*d,unsigned index,float*x,float*y){unsigned n=d->cursor<6?1:d->recoveredFields197[0];*x=d->docX+(d->cursor>=6?((float)index-((float)n-1)*.5f)*24.f:0);*y=d->docY;}
static const CampaignStageDefinition200*campaign_stage_select198(unsigned cursor,unsigned map,unsigned objectives){for(unsigned i=0;i<sizeof(campaignLaterStages197)/sizeof(*campaignLaterStages197);i++){const CampaignStageDefinition200*d=campaignLaterStages197+i;if(d->cursor==cursor&&d->map==map&&(objectives&d->recoveredFields197[7])==d->recoveredFields197[7])return d;}if(cursor>=3&&cursor<12&&campaignStages200[cursor-3].map==map)return campaignStages200+cursor-3;return NULL;}
static CampaignStageDecision198 campaign_stage_decide198(const CampaignStageDefinition200*d,const Campaign200*c,int who){
 CampaignStageDecision198 r={0,c->objectives,0,0};unsigned cursor=c->cursor,index=(unsigned)who-110,bit=0;const unsigned*f=d->recoveredFields197;
 if(cursor!=d->cursor||who<100)return r;
 if(who<110){if((unsigned)(who-100)>=d->count)return r;if(cursor>=12&&(c->objectives&f[8]))r.message=0xb90c85;else r.talk=1;return r;}
 if(cursor<6){if(who!=110)return r;if(cursor==3){if(c->checkpoint!=9||(c->objectives&3)!=3){r.message=0xb705e4;return r;}bit=2;}else if(cursor==4){if(c->checkpoint!=7){r.message=0xb515bd;return r;}bit=0;}else return r;
  if(c->objectives&(1u<<bit)){r.message=0xb74554;return r;}r.write=1;r.objectives|=1u<<bit;r.message=cursor==3?0xbb6c10:0xb6d9b8;return r;}
 if(index>=f[0])return r;
 if(c->checkpoint!=campaign_stage_gate198(cursor)){r.message=cursor<12?0xb6903d:0xba4165;return r;}
 if(cursor==10){
  if((c->objectives&0x300)!=0x300){r.message=0xb514b9;return r;}
  if(c->objectives&1){r.message=0xbb6d24;return r;}
  unsigned expected=c->objectives&32?2:(c->objectives>>4)&1;r.write=1;
  if(index!=expected){r.objectives=(c->objectives&0xbfffffceu)|0x40000000u;r.message=0xb6ea8a;return r;}
  r.objectives=(c->objectives&0xbffffffeu)|(index==0?16:index==1?32:1);r.message=index==0?0xb9d50c:index==1?0xb6e948:0xbb6d49;return r;
 }
 if(cursor<12){bit=cursor==9?0:index;r.write=1;r.objectives|=1u<<bit;r.message=cursor==9?0xbb6d78:campaignStageEarlyMessages198[index];return r;}
 unsigned enemies=cursor==34?0x300:campaign_stage_enemies198(d);
 if((c->objectives&enemies)!=enemies){r.message=0xb7b440;return r;}
 if(cursor==31||cursor==34){
  if(c->route<1||c->route>3)return r;unsigned route=cursor==34?0:c->route-1,expected=0;
  for(;expected<3;expected++)if(!(c->objectives&(1u<<(f[2]+campaignStageOrder198[route][expected]))))break;
  if(expected==3){r.message=0xb7458c;return r;}
  if(index!=campaignStageOrder198[route][expected]){r.write=1;r.objectives=(cursor==34?c->objectives&0xbffffff1u:c->objectives)|0x40000000u;r.message=cursor==34?0xb6ea9b:campaignStageWrongOrder198[campaignStageOrder198[route][expected]];return r;}
 }
 bit=f[2]+index;if(bit>30)return r;if(c->objectives&(1u<<bit)){r.message=0xbb1649;return r;}
 r.write=1;r.objectives=(c->objectives&0xbfffffffu)|(1u<<bit);
 if(cursor==18){unsigned findings=0;for(unsigned k=1;k<=4;k++)findings+=(r.objectives>>k)&1;if(findings>=3)r.objectives|=32;}
 r.message=cursor==35?0xb829a1:cursor==18&&(r.objectives&32)?0xb4f726:cursor==34?0xb5e89e:0xb7450f;return r;
}
#endif
