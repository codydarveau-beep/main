/* Existing streamed NPC emote frames and shared bounded texture/draw slots. */
#ifndef MYRO_CAMPAIGN_EMOTE_DRAW225_H
#define MYRO_CAMPAIGN_EMOTE_DRAW225_H
static void campaign_emote_draw225(const Combat*g,const float*matrix,float zoom){
 for(unsigned i=0;i<4;i++){const CampaignEmoteEvent225*e=campaignEmotes225.events+i;if(!e->kind||e->map!=g->mapId||!rooms_point181(&interiorRooms181,e->x,e->y))continue;
  unsigned clip=65536u+e->id,age=(unsigned)(e->age*1000.f);for(unsigned j=0;j<sizeof(npcFxClips172)/sizeof(*npcFxClips172);j++)if(npcFxClips172[j].id==clip)npc_fx_one172(npcFxClips172+j,age,matrix,e->x,e->y,zoom);
 }
}
#endif
