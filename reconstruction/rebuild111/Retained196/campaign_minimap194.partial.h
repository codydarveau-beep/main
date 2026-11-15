static void campaign_minimap194(const Combat*g){
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
    (c.objectives&d->forbidden194))
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
  c.cursor>=12?campaign_proof_gate194(c.cursor):
  c.cursor==3?CHAPTER2_WITNESS_GATE200:
  c.cursor==4?CHAPTER2_LEDGER_GATE200:
  c.cursor==6?CHAPTER3_OBSERVE193:
  c.cursor==9?CHAPTER4_MANIFEST193:
  c.cursor==10?CHAPTER4_ANCHOR193:65535;

 if(c.cursor==34)
  gate=CAMPAIGN_FINAL_BINDINGS194;

 if(c.checkpoint!=gate)return;

 unsigned kills=
  c.cursor==34?768:campaign_battle_mask194(d);

 if(kills&&(c.objectives&kills)!=kills)
  return;

 for(unsigned k=0;k<d->docs193;k++){
  unsigned bit=
   c.cursor>=12?d->docBit194+k:
   c.cursor==3?2:
   c.cursor==4||c.cursor==9?0:
   c.cursor==10?(k==2?0:k+4):k;

  if(bit>=31||(c.objectives&(1u<<bit)))
   continue;

  float x=d->docX+
   ((float)k-(d->docs193-1)*.5f)*24;

  minimap_marker(x,d->docY,0xff000000,5);
  minimap_marker(x,d->docY,0xffffdf56,3);
 }
}
