/* MIT. Run the original solo invasion; only a dead boss's UTC deadline persists.
   Replace the source server's133-minute spawn timer with the user's10-minute
   dead-boss rule. Original seven spawn sites, escorts and death cleanup remain
   in the original compiled script. */
#define NIF_CONTROLLER180 7581u
#define NIF_MAP180 193u
static uint64_t npc_nif_key180(void){return npc_variable_key55("__myroNiflheimDeadUntil180",0);}
static void npc_nif_dead180(NpcGame55*g,const NpcMonster55*r){if(r->npc!=NIF_CONTROLLER180||r->map!=NIF_MAP180||mobSpecs[r->kind].id!=1373)return;if(!npc_state_set_number55(npc_game_character_state55(g),npc_nif_key180(),0,(int64_t)(g->utc+600))){g->failures++;snprintf(g->error,sizeof(g->error),"Cannot record the Niflheim boss deadline.");}}
static void npc_nif_tick180(NpcGame55*g){
 Combat*game=g->player.game;if(game->mapId!=NIF_MAP180||game->hp<=0)return;
 for(unsigned i=0;i<g->monsters.count;i++){const NpcMonster55*r=g->monsters.rows+i;if(r->alive&&r->npc==NIF_CONTROLLER180&&r->map==NIF_MAP180&&mobSpecs[r->kind].id==1373){g->nifRetryAt180=0;return;}}
 NpcState55*s=npc_game_character_state55(g);int64_t until=npc_state_number55(s,npc_nif_key180(),0);if(until>(int64_t)(g->utc+600)){until=(int64_t)(g->utc+600);npc_state_set_number55(s,npc_nif_key180(),0,until);}if(until>(int64_t)g->utc||g->ms<g->nifRetryAt180)return;
 if(until)npc_state_set_number55(s,npc_nif_key180(),0,0);unsigned npc,entry;g->nifRetryAt180=g->ms+3000;
 if(!npc_game_event_target55(g,"NifInvasion::OnTimer7980000",&npc,&entry)||!npc_game_schedule55(g,npc,entry,0,N55_EVENT_CALL)){g->failures++;snprintf(g->error,sizeof(g->error),"Cannot start the original Niflheim invasion.");}
}
