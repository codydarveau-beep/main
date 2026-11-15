/* MIT. A guild courier is an alternative journey, never a native quest grant. */
#ifndef MYRO_REGIONAL_WORLD194_H
#define MYRO_REGIONAL_WORLD194_H
#include "regional194.h"

static int regional_world_visit194(
 Combat*g,unsigned index
){
 CampaignRegions194 r;

 if(!g||index>=REGIONAL_COUNT194||
    !guild_near194(g)||
    !campaign_regions_load194(questPins65,&r)||
    !(r.unlocked&regional_bit194(index)))
  return 0;

 const RegionalJourney194*p=regionalJourneys194+index;

 if(g->zeny<(int)p->fare||
    campaign_access194(questPins65,p->map,0)!=ACCESS_OPEN194)
  return 0;

 if(!world_script_warp55(
     NULL,g,p->map,p->x,p->y,0,1))
  return 0;

 g->zeny-=(int)p->fare;

 combat_message(
  g,"Courier passage: %u Zeny. Look for the notice near your arrival.",
  p->fare);

 return 1;
}

static int regional_world_return194(
 Combat*g,unsigned index
){
 if(index>=REGIONAL_COUNT194||
    regional_near194(questPins65,g)!=(int)index)
  return 0;

 return world_script_warp55(NULL,g,132,188,1116,0,1);
}
#endif
