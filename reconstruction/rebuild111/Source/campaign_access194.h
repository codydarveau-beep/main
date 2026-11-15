/* MIT. Shared, side-effect-free campaign admission and atomic regional receipts.
 * All travel adapters must preflight BEFORE charging or changing native quests.
 * This module does not itself activate world or NPC restrictions. */
#ifndef MYRO_CAMPAIGN_ACCESS194_H
#define MYRO_CAMPAIGN_ACCESS194_H
#include "campaign_state200.h"
#include "campaign_access_data194.h"
#include "career_access194.h"

#define CAMPAIGN_REGION_KEY194 UINT64_C(0xeca194007265676e)
#define CAMPAIGN_REGION_MASK194 ((1u<<CAMPAIGN_REGIONS194)-1u)

typedef struct{
 unsigned unlocked,accepted,completed;
}CampaignRegions194;

enum{
 ACCESS_OPEN194,
 ACCESS_STORY194,
 ACCESS_REGION194,
 ACCESS_RECORD194,
 ACCESS_DESTINATION194
};

static int campaign_regions_load194(
 const NpcState55*s,CampaignRegions194*out
){
 if(!s||!out)return 0;
 memset(out,0,sizeof(*out));

 const NpcVariable55*v=
  npc_state_get55(s,CAMPAIGN_REGION_KEY194,0);

 if(!v)return 1;

 if(v->kind!=NPC_STATE_NUMBER55||
    v->number<0||
    (uint64_t)v->number>=(UINT64_C(1)<<51))
  return 0;

 uint64_t bits=(uint64_t)v->number;

 out->unlocked=(unsigned)bits&CAMPAIGN_REGION_MASK194;

 out->accepted=
  ((unsigned)(bits>>17)&CAMPAIGN_REGION_MASK194)|
  out->unlocked;

 out->completed=
  (unsigned)(bits>>34)&CAMPAIGN_REGION_MASK194;

 return !(out->completed&~out->unlocked);
}

static int campaign_regions_store194(
 NpcState55*s,const CampaignRegions194*r
){
 if(!s||!r||
    ((r->unlocked|r->accepted|r->completed)&
     ~CAMPAIGN_REGION_MASK194)||
    (r->unlocked&~r->accepted)||
    (r->completed&~r->unlocked))
  return 0;

 uint64_t bits=
  r->unlocked|
  ((uint64_t)r->accepted<<17)|
  ((uint64_t)r->completed<<34);

 return npc_state_set_number55(
  s,CAMPAIGN_REGION_KEY194,0,(int64_t)bits);
}

static int campaign_regions_read194(
 const NpcState55*s,unsigned*out
){
 CampaignRegions194 r;
 if(!out||!campaign_regions_load194(s,&r))return 0;
 *out=r.unlocked;
 return 1;
}

static unsigned campaign_access_decide194(
 const Campaign200*c,unsigned regions,
 unsigned destination,int sandbox
){
 if(destination>=CAMPAIGN_ACCESS_MAPS194)
  return ACCESS_DESTINATION194;

 if(campaignMapExcluded194[destination])return ACCESS_DESTINATION194;
 if(sandbox)return ACCESS_OPEN194;

 if(!campaign_valid200(c)||regions>CAMPAIGN_REGION_MASK194)
  return ACCESS_RECORD194;

 if(c->cursor<campaignMapMinimum194[destination])
  return ACCESS_STORY194;

 unsigned region=campaignMapRegion194[destination];

 return region&&!(regions&(1u<<(region-1)))?
  ACCESS_REGION194:ACCESS_OPEN194;
}

static unsigned campaign_access194(
 const NpcState55*s,unsigned destination,int sandbox
){
 if(destination>=CAMPAIGN_ACCESS_MAPS194)
  return ACCESS_DESTINATION194;

 if(campaignMapExcluded194[destination])return ACCESS_DESTINATION194;
 if(sandbox)return ACCESS_OPEN194;

 Campaign200 c;
 unsigned regions;

 if(campaign_load200(s,&c)!=1||
    !campaign_regions_read194(s,&regions))
  return ACCESS_RECORD194;

 /* The native Sister visit and its saved return point remain usable.
    This admits only her field, never Morroc or the breach. */
 if(destination==108&&c.cursor>=1&&career_pilgrimage194(s))
  return ACCESS_OPEN194;

 return campaign_access_decide194(&c,regions,destination,0);
}

static int campaign_region_commit194(
 NpcState55*s,unsigned region
){
 Campaign200 c;
 CampaignRegions194 r;

 if(!region||region>CAMPAIGN_REGIONS194||
    campaign_load200(s,&c)!=1||
    !campaign_regions_load194(s,&r)||
    c.cursor<campaignRegionMinimum194[region-1])
  return 0;

 unsigned bit=1u<<(region-1);

 if(r.unlocked&bit)return 1;

 r.accepted|=bit;
 r.unlocked|=bit;
 return campaign_regions_store194(s,&r);
}

static const char*campaign_access_message194(unsigned result){
 switch(result){
 case ACCESS_STORY194:
  return "Follow your current main quest before taking this road.";
 case ACCESS_REGION194:
  return "This passage needs a local introduction. Check the regional noticeboard.";
 case ACCESS_RECORD194:
  return "Your story record could not be read. Travel was not applied.";
 case ACCESS_DESTINATION194:
  return "This destination is unavailable.";
 default:
  return "";
 }
}
#endif
