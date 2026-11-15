/* Original OnTouchNPC events for ordinary creatures, independent of race motion. */
#include "npc_touch_data172.h"
static void npc_game_monster_touch172(NpcGame55*g){
 if(g->ms<g->touchAt172)return;g->touchAt172=g->ms+100;Combat*game=g->player.game;if(game->mapId>=MYRO_MAP_COUNT43)return;
 unsigned start=npcMapSpans55[game->mapId].start,count=npcMapSpans55[game->mapId].count;
 /* Iterate only this map. Compiled entry lookup never reads scripts from disc. */
 int has=0;for(unsigned n=0;n<count&&!has;n++)for(unsigned t=0;t<sizeof(npcTouchEntries172)/sizeof(*npcTouchEntries172);t++)if(npcTouchEntries172[t].record==npcMapRecords55[start+n]){has=1;break;}if(!has)return;
 for(unsigned i=0;i<MOB_COUNT;i++){CombatMob*mob=game->mobs+i;if(!mob->enabled||mob->hp<=0||combat_racer_kind164(mob->kind))continue;unsigned touched=0;
  for(unsigned n=0;n<count;n++){unsigned id=npcMapRecords55[start+n];const NpcRecord55*r=npcRecords55+id;if((r->flags&2)||!npc_scene_available64(&g->scene,id)||(g->scene.flags[id]&(N55_NPC_DISABLED|N55_NPC_HIDDEN))||!(g->scene.flags[id]&N55_NPC_INIT_DONE)||fabsf(mob->x-npc_scene_x64(&g->scene,id))>r->rx+4||fabsf(mob->y-npc_scene_y64(&g->scene,id))>r->ry+4)continue;
   for(unsigned t=0;t<sizeof(npcTouchEntries172)/sizeof(*npcTouchEntries172);t++)if(npcTouchEntries172[t].record==id){touched=id+1;if(mob->raceTouch164!=touched&&!npc_game_schedule55(g,id,npcTouchEntries172[t].entry,0,N55_EVENT_MONSTER172|((i+1)<<16)))touched=0;break;}if(touched)break;
  }mob->raceTouch164=touched;
 }
}
