#include "world_gate_state64.h"
#include "interior_rooms181.h"
/* SPDX-License-Identifier: MIT. Exactly one map's terrain/scenery is resident. */
#ifndef MYRO_WORLD_MAPS_H
#define MYRO_WORLD_MAPS_H
#include "campaign_access_data194.h"
#include "world_availability44.h"
#include "travel_status45.h"
#include "visual_cache50.h"
#include "world_regions51.h"
static unsigned activeMap=~0u;
static void(*worldHeapTrim183)(void);
static void(*worldWaterRelease190)(void);
static void(*worldSceneRelease200)(void);
static void scenery_load(unsigned id);
static void scenery_release(void);
static void world_release(void){
 while(pb_busy()){}if(worldSceneRelease200)worldSceneRelease200();if(worldWaterRelease190)worldWaterRelease190();rooms_clear181(&interiorRooms181);if(visualCacheRelease50)visualCacheRelease50();scenery_release();
#ifndef MYRO_HOST
 sprite_release_enemies();gpu_stream_reset51();guardian_reset51();
#endif
 if(gpuTerrain)MmFreeContiguousMemory(gpuTerrain);if(gpuMesh)MmFreeContiguousMemory(gpuMesh);gpuTerrain=gpuMesh=NULL;
 guild_floor_release197();if(walk)free(walk-8);if(cellStarts)free(cellStarts);if(groundHeights)free(groundHeights);walk=NULL;cellStarts=NULL;groundHeights=NULL;surfaceCells45=NULL;surfaceCount45=0;propCells46=NULL;propCount46=0;if(worldHeapTrim183)worldHeapTrim183();
}
static int world_activate(unsigned id){
 if(!world_destination_ready44(id))return 0;if(id==activeMap)return 1;
 char stage[90];snprintf(stage,sizeof(stage),"Travelling to %s - releasing previous area",mapLabels[id]);world_loading(stage);world_release();
#ifndef MYRO_HOST
 snprintf(stage,sizeof(stage),"%s - reserving map graphics",mapLabels[id]);world_loading(stage);world_gpu_reserve171(id);
#endif
 snprintf(stage,sizeof(stage),"%s - loading terrain and collision",mapLabels[id]);world_loading(stage);load(id);gpu_memory();rooms_build181(&interiorRooms181,mapNames[id],walk,gw,gh);if(id==494)guild_floor_apply197();
 snprintf(stage,sizeof(stage),"%s - loading scenery",mapLabels[id]);world_loading(stage);scenery_load(id);activeMap=id;
#ifndef MYRO_HOST
 snprintf(stage,sizeof(stage),"%s - loading current-map enemies",mapLabels[id]);world_loading(stage);sprite_load_map(id);sound_music_map(id);snprintf(stage,sizeof(stage),"%s - preparing minimap",mapLabels[id]);world_loading(stage);minimap_upload();
#endif
 world_loading_end();return 1;
}
static int world_prepare(void*unused,unsigned id,float*campX,float*campY){(void)unused;if(!world_activate(id))return 0;*campX=spawnx;*campY=spawny;return 1;}
static void world_safe(float*x,float*y){
 if(allowed(*x,*y))return;float ox=*x,oy=*y;
 for(int r=1;r<=48;r++)for(int yy=-r;yy<=r;yy++)for(int xx=-r;xx<=r;xx++){if(abs(xx)!=r&&abs(yy)!=r)continue;float nx=ox+xx*8,ny=oy+yy*8;if(allowed(nx,ny)){*x=nx;*y=ny;return;}}
 *x=spawnx;*y=spawny;
}
static void world_town(Combat*g){
#ifndef MYRO_HOST
 g->canAim=world_can_cast;g->inWater=world_in_water;
#endif
 combat_population(g,activeMap);
 g->peaceful=activeMap<WORLD_MAP_COUNT&&peacefulMaps51[activeMap];if(g->peaceful){g->autoAttack=0;g->target=-1;for(int i=0;i<MOB_COUNT;i++){g->mobs[i].hp=0;g->mobs[i].deadAt=-1000;}}
}
static int world_gate(const Combat*g){
 if(g->hp<=0)return -1;for(unsigned i=0;i<WORLD_GATE_COUNT;i++){const WorldGate*w=&worldGates[i];if(w->source==activeMap&&world_gate_enabled64(i)&&world_destination_ready44(w->destination)&&fabsf(g->x-w->x)<=w->rx&&fabsf(g->y-w->y)<=w->ry)return i;}return -1;
}
static int world_near_gate(const Combat*g){return world_gate(g)>=0;}
static void world_travel(Combat*g){
 int k=world_gate(g);if(k<0)return;if(!world_gate_open199((unsigned)k)){combat_message(g,"This passage is not open yet. Continue your current objective.");return;}WorldGate gate=worldGates[k];if(combatTravelAdmission194){const char*reason=combatTravelAdmission194(g,gate.destination);if(reason){combat_message(g,"%s",reason);return;}}if(gate.source==16&&gate.destination==17){static const float arrivals[4][2]={{1612,1636},{1516,348},{348,324},{276,1620}};unsigned choice=combat_random(g)%4;gate.destX=arrivals[choice][0];gate.destY=arrivals[choice][1];}
#ifndef MYRO_HOST
 sound_play(1);
#endif
 TravelStatus45 status45=travel_capture45(g);SavedCharacter c;save_capture(&c,g,1);c.mapId=gate.destination;c.x=gate.destX;c.y=gate.destY;
 if(!world_activate(gate.destination)){combat_message(g,"Destination unavailable.");return;}world_safe(&c.x,&c.y);save_restore(g,&c,spawnx,spawny,world_can_move,NULL);travel_restore45(g,&status45);world_town(g);combat_message(g,"Arrived in %s.",mapLabels[activeMap]);
}
/* Developer travel uses the same state-preserving restore as road warps. */
static int world_test_warp(Combat*g,unsigned destination){
 if(destination>=WORLD_MAP_COUNT||campaignMapExcluded194[destination])return 0;
 int revive50c=g->hp<=0;
 TravelStatus45 status45=travel_capture45(g);SavedCharacter c;save_capture(&c,g,1);c.mapId=destination;
 
#ifndef MYRO_HOST
 sound_play(1);
#endif
 if(!world_activate(destination))return 0;
 c.x=spawnx;c.y=spawny;world_safe(&c.x,&c.y);
 save_restore(g,&c,spawnx,spawny,world_can_move,NULL);if(revive50c){g->hp=g->maxhp;g->sp=g->maxsp;}else travel_restore45(g,&status45);world_town(g);
 combat_message(g,revive50c?"Revived at %s with full HP/SP.":"Test warp: %s.",mapLabels[activeMap]);return 1;
}
/* Script warps preserve character state; same-map moves preserve the live population. */
static int world_script_warp55(void*context,Combat*g,unsigned destination,float x,float y,int random,int clean){
 (void)context;(void)clean;if(combatTravelAdmission194){const char*reason=combatTravelAdmission194(g,destination);if(reason){combat_message(g,"%s",reason);return 0;}}if(destination>=WORLD_MAP_COUNT||(!random&&(!isfinite(x)||!isfinite(y)||x<8||y<8||x>=mapWidth43[destination]-8||y>=mapHeight43[destination]-8)))return 0;
 int same=destination==activeMap;TravelStatus45 status=travel_capture45(g);SavedCharacter c;save_capture(&c,g,1);c.mapId=destination;
 if(!world_activate(destination))return 0;
 if(random){x=spawnx;y=spawny;for(unsigned i=0;i<256;i++){float xx=(combat_random(g)%(gw-2)+1)*8+4,yy=(combat_random(g)%(gh-2)+1)*8+4;if(allowed(xx,yy)){x=xx;y=yy;break;}}}
 world_safe(&x,&y);if(same){g->x=x;g->y=y;g->autoAttack=0;g->target=-1;g->approachSkill53=0;g->route53.state=0;g->sitting=0;combat_interrupt_cast(g);}
 else{c.x=x;c.y=y;c.rng=g->rng;save_restore(g,&c,spawnx,spawny,world_can_move,NULL);travel_restore45(g,&status);world_town(g);}
 return 1;
}
static void world_merchant(float*x,float*y){*x=spawnx+40;*y=spawny;world_safe(x,y);}
static int world_near_merchant(const Combat*g){float x,y;if(activeMap!=2||g->hp<=0)return 0;world_merchant(&x,&y);return combat_dist(x,y,g->x,g->y)<28;}
#endif

static void world_instructor(float*x,float*y){*x=spawnx-40;*y=spawny;world_safe(x,y);}
static void world_stylist(float*x,float*y){*x=spawnx;*y=spawny+48;world_safe(x,y);}
static int world_near_stylist(const Combat*g){float x,y;if(activeMap!=2||g->hp<=0)return 0;world_stylist(&x,&y);return combat_dist(x,y,g->x,g->y)<28;}
static int world_near_instructor(const Combat*g){float x,y;if(activeMap!=2||g->hp<=0)return 0;world_instructor(&x,&y);return combat_dist(x,y,g->x,g->y)<28;}

/* Spell travel uses the same streamed world as road warps. Same-map jumps need no load. */
static int world_skill_travel(Combat*g){if(!g->travelRequest)return 0;WorldPosition p=g->travel;g->travelRequest=0;if(!combat_position_valid(p))return 0;
#ifndef MYRO_HOST
 sound_play(1);
#endif
 if(p.map==activeMap){g->x=p.x;g->y=p.y;world_safe(&g->x,&g->y);g->autoAttack=0;g->target=-1;for(int i=0;i<MOB_COUNT;i++)g->mobs[i].aggro=0;return 1;}TravelStatus45 status45=travel_capture45(g);SavedCharacter c;save_capture(&c,g,1);c.mapId=p.map;c.x=p.x;c.y=p.y;if(!world_activate(p.map))return 0;world_safe(&c.x,&c.y);save_restore(g,&c,spawnx,spawny,world_can_move,NULL);travel_restore45(g,&status45);world_town(g);combat_message(g,"Arrived by spell in %s.",mapLabels[activeMap]);return 1;}
