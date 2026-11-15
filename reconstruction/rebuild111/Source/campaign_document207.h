/* Preserved evidence paper presentation; native helper 0x117850 and callers.
 * No new art, choreography, persistent state or per-frame allocation. */
#ifndef MYRO_CAMPAIGN_DOCUMENT207_H
#define MYRO_CAMPAIGN_DOCUMENT207_H
static void campaign_document_one207(const float*m,float zoom,float slope,float x,float y){if(!rooms_point181(&interiorRooms181,x,y))return;float z=height_at(x,y),sx,sy;world_project(m,x,y,z,&sx,&sy);if(sx< -30||sx>670||sy< -30||sy>510)return;int item=inventory_catalog52(1550);if(item<0)return;item_icon_begin52();int icon=itemIcons[item];const unsigned short*r=icon>=ITEM_ICON_BASE52?item_icon_rect52(icon):icon>=0?skinRects[icon]:NULL;if(!r)return;float depth=m[8]*x+m[9]*y+m[10]*z+m[11]-WORLD_SPRITE_BIAS,w=5*zoom,h=w,left=sx-w*.5f,top=sy-h,zt=sprite_upright_cached50(depth,top,sy,slope);hud_setup_direct(skinTexture,512,SKIN_H,2048,0x0001122a,1);uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,0);pb_end(p);ground_quad58(left,top,w,h,zt,depth,r[0],r[1],r[2],r[3]);}
static void campaign_document_draw200(const Combat*g,const float*m,float zoom,float slope){
 Campaign200 c;
 if(campaign_load200(questPins65,&c)==1&&c.cursor>=9&&c.guild[0]&&g->mapId==132)
  campaign_document_one207(m,zoom,slope,188,1116);
 if(!campaignStage200.active||!campaignStage200.definition)return;
 const CampaignStageDefinition200*d=campaignStage200.definition;
 unsigned count=d->cursor<5?1:d->recoveredFields197[0];
 for(unsigned i=0;i<count;i++){
  float x=d->docX+((float)i-((float)count-1)*.5f)*24.f;
  campaign_document_one207(m,zoom,slope,x,d->docY);
 }
}
#endif
