/* Restored retained marker function; adapters only rename recovered fields. */
#ifndef MYRO_CAMPAIGN_MINIMAP200_H
#define MYRO_CAMPAIGN_MINIMAP200_H
static void campaign_minimap200(const Combat*g){
 const CampaignStage200*r=&campaignStage200;
 Campaign200 c;

 if(!r->active||
    !r->definition||
    !quest_tracked65(CAMPAIGN_QUEST200)||
    campaign_load200(r->state,&c)!=1)
  return;

 const CampaignStageDefinition200*d=r->definition;

 if(g->mapId!=d->map||
    c.cursor!=d->cursor||
    (c.objectives&d->recoveredFields197[8]))
  return;

 if(d->count){
  unsigned actor=c.cursor==5?2:0;

  if(actor<d->count){
   minimap_marker(
    d->actor[actor].x,d->actor[actor].y,0xff000000,6);
   minimap_marker(
    d->actor[actor].x,d->actor[actor].y,0xffffdf56,4);
  }
 }

 unsigned gate=
  c.cursor>=12?campaign_stage_gate198(c.cursor):
  c.cursor==3?9:
  c.cursor==4?7:
  c.cursor==6?9:
  c.cursor==9?9:
  c.cursor==10?7:65535;

 if(c.cursor==34)
  gate=8;

 if(c.checkpoint!=gate)return;

 unsigned kills=
  c.cursor==34?768:campaign_stage_enemies198(d);

 if(kills&&(c.objectives&kills)!=kills)
  return;

 unsigned docs=d->cursor==3||d->cursor==4?1:d->recoveredFields197[0];
 for(unsigned k=0;k<docs;k++){
  unsigned bit=
   c.cursor>=12?d->recoveredFields197[2]+k:
   c.cursor==3?2:
   c.cursor==4||c.cursor==9?0:
   c.cursor==10?(k==2?0:k+4):k;

  if(bit>=31||(c.objectives&(1u<<bit)))
   continue;

  float x=d->docX+
   ((float)k-(docs-1)*.5f)*24;

  minimap_marker(x,d->docY,0xff000000,5);
  minimap_marker(x,d->docY,0xffffdf56,3);
 }
}

#endif
