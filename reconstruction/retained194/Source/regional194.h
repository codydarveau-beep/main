/* MIT. Optional guild dispatches introduce existing solo regions. The source
 * NPC quests, equipment checks and dungeon entry conditions remain intact. */
#ifndef MYRO_REGIONAL194_H
#define MYRO_REGIONAL194_H
#include "campaign_access194.h"
#include "guild194.h"

#define REGIONAL_QUEST194 2000000200u
#define REGIONAL_COUNT194 9u

typedef struct{
 unsigned region,map;
 float x,y,noteX,noteY;
 unsigned item[2],amount[2],fare;
 const char*title,*pitch,*letter;
}RegionalJourney194;

static const RegionalJourney194 regionalJourneys194[REGIONAL_COUNT194]={
 {
  1,386,1196,1436,1196,1484,{1019,914},{12,8},1000,
  "Winter mail road",
  "Nera: The northern post is waiting for dry packing cloth and a replacement sled runner. Snow is charming until it gets into somebody else's letters.",
  "[The northern post]\nThe runner arrived in one piece. The postmaster insists this is a new record. Lutie and the Toy Factory have their own troubles; ask the residents what needs doing. There is room beside the stove for travellers who intend to help.\n\nA parcel has been left for the guild: one Old Blue Box."
 },
 {
  2,377,1596,1604,1596,1652,{1019,909},{16,12},3000,
  "Moscovia passage",
  "Maya: Our harbour contact needs timber and sealing paste before the next shipment. We can carry supplies without pretending to understand every story told about the sea.",
  "[A harbour receipt]\nThe crate is dry. The dock is loud. Someone has already told three different stories about the same whale. Speak to the people of Moscovia and decide which account deserves a voyage. The guild's courier passage does not settle any local quest for you.\n\nOur thanks: one Old Blue Box."
 },
 {
  3,376,1596,1596,1596,1644,{914,511},{12,8},3000,
  "Brasilis dispatch",
  "Yuufa: Bandages and herbs travel better when somebody packs them carefully. The people at Brasilis asked for both. No, a box marked 'probably medicine' will not do.",
  "[A clinic's note]\nThe herbs were labelled correctly. Please tell your healer that this was noticed and appreciated. The town's ordinary errands are a good place to start; the forest's stories are best heard from people who live beside it.\n\nA small contribution to your travels: one Old Blue Box."
 },
 {
  8,405,1636,1540,1684,1540,{914,1019},{16,12},9000,
  "Splendide frontier",
  "Nera: With the expedition's first report safely filed, we can send a letter instead of a rumour. The Splendide contact asked for cloth and timber, not another armed delegation.",
  "[A carefully copied reply]\nYour supplies have been received. Your introduction is a beginning, not permission to speak for us. Listen to the residents of Splendide before drawing conclusions about this frontier. Their requests and customs remain their own.\n\nThe courier's return parcel contains one Old Blue Box."
 },
 {
  9,395,1532,1548,1484,1548,{999,1019},{10,16},9000,
  "Manuk frontier",
  "Dagna: Tools do not improve because we argue about borders. Iron and timber will make this shipment useful. The expedition contact has agreed to introduce our courier.",
  "[A workshop's acknowledgement]\nThe materials are sound. The people who sent them may yet prove equally dependable. Ask what work is needed in Manuk; do not assume a stamped introduction replaces anybody's trust.\n\nPayment for the delivery: one Old Blue Box."
 },
 {
  11,396,1660,1676,1700,1708,{914,511},{20,12},9000,
  "Expedition road",
  "Nera: The road beyond the dimensional wound needs a record of its own. Take medical supplies to the expedition. We will begin with names, needs, and an honest first report.",
  "[The expedition register]\nCourier arrived. Supplies counted. Nobody listed as 'expendable'. It is a modest beginning, but a useful one. Speak to the expedition staff about the frontier before visiting either neighbouring settlement. Their original investigations still need doing.\n\nA courier's allowance: one Old Blue Box."
 },
 {
  12,143,1196,1196,1196,1244,{1019,909},{18,10},3000,
  "Turtle Island passage",
  "Maya: A boat with sound boards is preferable to a boat with optimistic passengers. Bring timber and sealing paste; our courier can then arrange the island passage.",
  "[An island landing note]\nBoat intact. Cargo intact. Courier only mildly offended by the sand. The island's inhabitants are less interested in paperwork. Prepare for the dungeons before heading deeper; this introduction has not made them tame.\n\nOne Old Blue Box has been set aside for the guild."
 },
 {
  13,139,1380,1388,1428,1388,{914,511},{10,6},3000,
  "An overdue holiday",
  "Yuufa: A seaside first-aid parcel is still useful work. Taking a quiet afternoon afterwards is allowed. I have checked with the guild leader. That would be you.",
  "[A seaside thank-you]\nThe parcel reached Jawaii safely. Please accept a little hospitality without producing an invoice for every pleasant minute. Travelling here does not require a wedding, and resting does not require an excuse.\n\nThere is one Old Blue Box for the courier. Try opening it somewhere dry."
 },
 {
  14,247,1596,1596,1636,1564,{1019,914},{14,10},3000,
  "Kiel Hyre inquiry",
  "Nera: The academy's outer road requested repair supplies. Deliver them first, then ask about the academy's own affairs. An introduction is not a key to somebody else's locked rooms.",
  "[An academy delivery docket]\nTimber and cloth received on the road outside the academy. Further enquiries should begin with the academy staff and the residents nearby. Their original tasks, keys and investigations remain necessary; this delivery opens no private laboratory.\n\nThe guild's parcel contains one Old Blue Box."
 }
};

static int regional_index194(unsigned region){
 for(unsigned i=0;i<REGIONAL_COUNT194;i++)
  if(regionalJourneys194[i].region==region)return(int)i;
 return-1;
}

static int regional_quest194(uint32_t id){
 return id>=REGIONAL_QUEST194&&id<REGIONAL_QUEST194+17?
  regional_index194(id-REGIONAL_QUEST194+1):-1;
}

static unsigned regional_bit194(unsigned index){
 return 1u<<(regionalJourneys194[index].region-1);
}

static int regional_available194(
 const NpcState55*s,unsigned index
){
 Campaign200 c;
 CampaignRegions194 r;

 if(index>=REGIONAL_COUNT194||
    !guild_open194(s)||
    campaign_load200(s,&c)!=1||
    !campaign_regions_load194(s,&r))
  return 0;

 unsigned region=regionalJourneys194[index].region;

 return c.cursor>=campaignRegionMinimum194[region-1]&&
  ((region!=8&&region!=9)||(r.completed&(1u<<10)));
}

static int regional_accept194(
 NpcState55*s,unsigned index
){
 CampaignRegions194 r;

 if(!regional_available194(s,index)||
    !campaign_regions_load194(s,&r))
  return 0;

 unsigned bit=regional_bit194(index);

 if(r.accepted&bit)return 1;

 r.accepted|=bit;
 return campaign_regions_store194(s,&r);
}

/* Stage the inventory before committing the sparse ledger.
 * No yield/save/callback/native quest operation occurs between commits. */
static int regional_deliver194(
 NpcState55*s,Combat*g,unsigned index
){
 CampaignRegions194 r;

 if(!g||
    !regional_available194(s,index)||
    !campaign_regions_load194(s,&r))
  return 0;

 unsigned bit=regional_bit194(index);

 if(!(r.accepted&bit)||(r.unlocked&bit))
  return 0;

 const RegionalJourney194*p=regionalJourneys194+index;

 OwnedItems52*bag=malloc(sizeof(*bag));
 if(!bag)return 0;
 *bag=g->owned52;

 for(unsigned k=0;k<2;k++){
  unsigned left=p->amount[k];

  for(unsigned i=0;i<bag->count[0]&&left;){
   OwnedItem52*o=bag->items+i;

   if(o->sourceID!=p->item[k]||o->equipped||o->bound){
    i++;
    continue;
   }

   unsigned amount=o->quantity<left?o->quantity:left;
   unsigned uid=o->uid;
   int erased=amount==o->quantity;

   if(owned_remove52(bag,0,uid,amount)!=OWNED_OK52){
    free(bag);
    return 0;
   }

   left-=amount;
   if(!erased)i++;
  }

  if(left){
   free(bag);
   return 0;
  }
 }

 r.unlocked|=bit;

 if(!campaign_regions_store194(s,&r)){
  free(bag);
  return 0;
 }

 g->owned52=*bag;
 free(bag);
 return 1;
}

static int regional_collect194(
 NpcState55*s,Combat*g,unsigned index
){
 CampaignRegions194 r;

 if(!g||index>=REGIONAL_COUNT194||
    !campaign_regions_load194(s,&r))
  return 0;

 const RegionalJourney194*p=regionalJourneys194+index;
 unsigned bit=regional_bit194(index);

 if(!(r.unlocked&bit)||(r.completed&bit)||
    g->mapId!=p->map||
    combat_dist(g->x,g->y,p->noteX,p->noteY)>24)
  return 0;

 const OwnedRule52*reward=item_rule52(603);

 if(!reward||
    inventory_weight(g)+reward->weight>inventory_weight_max(g))
  return 0;

 OwnedItems52*bag=malloc(sizeof(*bag));
 if(!bag)return 0;

 *bag=g->owned52;
 inventory_compact52(bag);

 if(owned_add52(bag,0,603,1,item_rule52)!=OWNED_OK52){
  free(bag);
  return 0;
 }

 r.completed|=bit;

 if(!campaign_regions_store194(s,&r)){
  free(bag);
  return 0;
 }

 g->owned52=*bag;
 free(bag);
 return 1;
}

static int regional_near194(
 const NpcState55*s,const Combat*g
){
 CampaignRegions194 r;

 if(!g||g->hp<=0||!campaign_regions_load194(s,&r))
  return-1;

 for(unsigned i=0;i<REGIONAL_COUNT194;i++){
  const RegionalJourney194*p=regionalJourneys194+i;
  unsigned bit=regional_bit194(i);

  if((r.unlocked&bit)&&g->mapId==p->map&&
     combat_dist(g->x,g->y,p->noteX,p->noteY)<=24&&
     (!g->canMove||
      g->canMove(g->world,g->x,g->y,p->noteX,p->noteY)))
   return(int)i;
 }

 return-1;
}
#endif
