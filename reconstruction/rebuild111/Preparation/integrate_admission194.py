from pathlib import Path
S=Path(__file__).resolve().parent.parent/'Source'
def edit(name,changes):
 p=S/name;s=p.read_text()
 for before,after in changes:
  assert before in s,(name,before[:100]);s=s.replace(before,after,1)
 p.write_text(s)
edit('npc_scene55.h',[
 ('static int npc_scene_available64(', 'static int npc_scene_interactive194(unsigned index){return !npcNativeAdmission194||!npcNativeAdmission194(index);}\nstatic int npc_scene_available64('),
 ('if(!npc_scene_available64(s,i)||','if(!npc_scene_available64(s,i)||!npc_scene_interactive194(i)||'),
])
edit('npc_visibility180.h',[
 ('!npc_scene_available64(s,id)||','!npc_scene_available64(s,id)||!npc_scene_interactive194(id)||'),
])
edit('npc_game55.h',[
 ('#include "npc_world55.h"','#include "npc_world55.h"\n#include "career_warp194.h"\n#include "npc_travel_preflight194.h"'),
 ('static int npc_game_schedule55(NpcGame55*g,unsigned index,unsigned entry,uint64_t delay,unsigned kind){',
  'static int npc_game_schedule55(NpcGame55*g,unsigned index,unsigned entry,uint64_t delay,unsigned kind){if((kind&N55_EVENT_ATTACHED)&&((kind&255)!=N55_EVENT_INIT)&&!npc_scene_interactive194(index))return 0;'),
 ('!npc_scene_available64(&g->scene,id)||','!npc_scene_available64(&g->scene,id)||!npc_scene_interactive194(id)||'),
 ('n->map!=game->mapId||(n->flags&2))continue;','n->map!=game->mapId||(n->flags&2)||!npc_scene_interactive194(r->npc))continue;'),
 ('status=npc_world_command55(g->world+slot,m,r->attached,name,args,count,out);',
  'unsigned root194=r->npc&&r->npc<=NPC_RECORD_COUNT55?npcRecords55[r->npc-1].program:0;status=npc_career_world194(g->world+slot,m,r->attached,root194,npc_game_character_state55(g),name,args,count,out);'),
 ('static int npc_game_open55(NpcGame55*g,unsigned npc){','static int npc_game_open55(NpcGame55*g,unsigned npc){if(!npc_scene_interactive194(npc))return 0;'),
 ('else if(buttons&2)npc_runtime_answer55(r,g->choice,0);',
  'else if((buttons&2)&&npc_travel_preflight194(g->player.game,r,g->world+g->ui,g->choice,g->error,sizeof(g->error)))npc_runtime_answer55(r,g->choice,0);'),
 ('int inside=npc_scene_available64(&g->scene,npc)&&','int inside=npc_scene_available64(&g->scene,npc)&&npc_scene_interactive194(npc)&&'),
 ('if(npc<NPC_RECORD_COUNT55&&npc_scene_available64(&g->scene,npc)&&(((event.kind&255)',
  'if(npc<NPC_RECORD_COUNT55&&npc_scene_available64(&g->scene,npc)&&(!(event.kind&N55_EVENT_ATTACHED)||((event.kind&255)==N55_EVENT_INIT)||npc_scene_interactive194(npc))&&(((event.kind&255)'),
])
edit('npc_game_xbox55.h',[
 ('return record>=0&&(npcGame55.scene.flags[record]&','return record>=0&&(!npc_scene_interactive194((unsigned)record)||(npcGame55.scene.flags[record]&'),
 ('N55_NPC_DISABLED|N55_NPC_HIDDEN));}','N55_NPC_DISABLED|N55_NPC_HIDDEN)));}'),
])
edit('npc_world55.h',[
 (' if(!warp){w->game->home=',
  ' unsigned target194=(unsigned)map;if(npcTravelRedirect193)npcTravelRedirect193(w->game,&target194,&wx,&wy);if(target194>=w->count)return N55_ERROR;if(target194!=(unsigned)map)random=0;map=(int)target194;\n if(npcTravelAdmission194){const char*reason=npcTravelAdmission194(w->game,(unsigned)map);if(reason)return N55_ERROR;}\n if(!warp){w->game->home='),
])
edit('native_admission194.h',[
 ('sandbox?ACCESS_OPEN194:', 'sandbox?campaign_access_decide194(NULL,0,map,1):'),
])
edit('world_maps.h',[
 ('int k=world_gate(g);if(k<0)return;WorldGate gate=worldGates[k];',
  'int k=world_gate(g);if(k<0)return;WorldGate gate=worldGates[k];if(combatTravelAdmission194){const char*reason=combatTravelAdmission194(g,gate.destination);if(reason){combat_message(g,"%s",reason);return;}}'),
 (' (void)context;(void)clean;if(destination>=WORLD_MAP_COUNT',
  ' (void)context;(void)clean;if(combatTravelAdmission194){const char*reason=combatTravelAdmission194(g,destination);if(reason){combat_message(g,"%s",reason);return 0;}}if(destination>=WORLD_MAP_COUNT'),
])
edit('acolyte_skills.h',[
 (' WorldPosition dest=g->home;float x=g->utilityX,y=g->utilityY;',
  ' WorldPosition dest=(id==54&&choice)?g->memos[choice-1]:g->home;float x=g->utilityX,y=g->utilityY;\n unsigned destination194=(id==52&&choice==0)?g->mapId:dest.map;if(combatTravelAdmission194){const char*reason=combatTravelAdmission194(g,destination194);if(reason){combat_message(g,"%s",reason);return 0;}}'),
])
edit('main.c',[
 ('game.travel=game.portals[k].destination;game.portals[k].uses--;game.travelRequest=1;aiming=0;',
  'const char*reason194=combatTravelAdmission194?combatTravelAdmission194(&game,game.portals[k].destination.map):NULL;if(reason194)combat_message(&game,"%s",reason194);else{game.travel=game.portals[k].destination;game.portals[k].uses--;game.travelRequest=1;}aiming=0;'),
])
print('Integrated admission before native SELECT, open/touch/events, script state changes, road RNG, skill costs, and portal uses')
