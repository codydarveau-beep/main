#ifndef MYRO_CAMPAIGN_NATIVE_FX212_H
#define MYRO_CAMPAIGN_NATIVE_FX212_H
/* Companion-native effects keep their original eight-entry queue and share the
 * established effect reader/frame budgets, after ordinary NPC effects reset them. */
static void campaign_native_sound212(Combat*g,unsigned effect){for(unsigned i=0;i<sizeof(npcFxSounds172)/sizeof(*npcFxSounds172);i++)if(npcFxSounds172[i].effect==effect)combat_sound_at(g,SOUND_NPC_FIRST64+npcFxSounds172[i].clip,0);}
static void combat_native_effect263(Combat*g,unsigned effect,float x,float y){combatNativeFx263[combatNativeFxNext263++%8]=(CampaignNativeFx212){effect,g->mapId,0,0,g->time,x,y,height_at(x,y),1};campaign_native_sound212(g,effect);}
static void campaign_native_fx_draw212(const Combat*g,const float*m,float zoom){
 for(unsigned i=0;i<16;i++){
  CampaignNativeFx212*f=i<8?campaignNativeFx212+i:combatNativeFx263+i-8;if(!f->id||f->map!=g->mapId)continue;
  float seconds=g->time-f->at;if(seconds<0)continue;unsigned age=(unsigned)(seconds*1000),duration=npc_cylinder_lifetime180(f->id),n=npc_particle_lifetime180(f->id);if(n>duration)duration=n;n=npc_special_lifetime180(f->id);if(n>duration)duration=n;n=npc_legacy_lifetime181(f->id);if(n>duration)duration=n;
  for(unsigned c=0;c<sizeof(npcFxClips172)/sizeof(*npcFxClips172);c++)if(npcFxClips172[c].id==f->id){n=npcFxClips172[c].count*npcFxClips172[c].ms;if(n>duration)duration=n;}
  if(!duration)duration=4000;if(age>=duration){f->id=0;continue;}
  float x=f->x,y=f->y;if(i<8){CampaignFollower200*owner=party_member200(f->member);if(!owner||!owner->initialized||!owner->hp||owner->life!=f->life||owner->map!=g->mapId)continue;x=owner->x;y=owner->y;}if(!rooms_point181(&interiorRooms181,x,y))continue;
  if(!f->positioned){f->x=x;f->y=y;f->z=height_at(x,y);f->positioned=1;}
  unsigned created=(unsigned)(f->at*1000),seed=created^(f->member+1);
  npc_cylinder_draw180(f->id,age,seed,m,x,y);npc_particle_draw180(f->id,age,created,seed,m,x,y,f->x,f->y,f->z);npc_special_draw180(f->id,age,seed,m,f->id==200?x:f->x,f->id==200?y:f->y);npc_legacy_draw181(g,f->id,age,seed,m,x,y);
  for(unsigned c=0;c<sizeof(npcFxClips172)/sizeof(*npcFxClips172);c++)if(npcFxClips172[c].id==f->id&&(created^((f->member+1)*2654435761u))%npcFxClips172[c].variants==npcFxClips172[c].variant)npc_fx_one172(npcFxClips172+c,age,m,x,y,zoom);
 }
}
#endif
