/* Actual streamed-map loader: all regions, current-area residency and save IDs. */
#define main old_world43_main
#include "test_world43.c"
#undef main
#include "menu_groups48.h"
int main(void){
 static Combat g;unsigned maxBytes=0,maxMap=0;world_blob_init();assert(WORLD_MAP_COUNT==409&&MYRO_MAP_COUNT43==409);
 for(unsigned map=0;map<WORLD_MAP_COUNT;map++){
  assert(world_activate(map)&&activeMap==map&&allocated==4);assert(allowed(spawnx,spawny));
  if(bytesNow>maxBytes){maxBytes=bytesNow;maxMap=map;}
  assert(world_activate(map)&&allocated==4);
  combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=map;world_town(&g);assert(!!g.peaceful==!!peacefulMaps51[map]);
  unsigned expected=0,actual=0;for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].map==map)expected+=spawnDefs[j].count;
  for(unsigned j=0;j<MOB_COUNT;j++)if(g.mobs[j].enabled){actual++;assert(g.mobs[j].kind<MOB_SPEC_COUNT);assert(allowed(g.mobs[j].x,g.mobs[j].y));}assert(actual==expected);
  SavedCharacter save;save_capture(&save,&g,1);unsigned char disk[SAVE_BYTES];save_encode(disk,&save);assert(save_decode(&save,disk)==1&&save.mapId==map);
  int group=travel_group48(map),row=travel_row51(map);assert(travelGroups48[group][row]==map&&travel_step48(travel_step48(map,1),-1)==(int)map);
  assert(travel_region48(travel_region48(map,1),-1)==travelGroups48[group][0]);
  if(map%25==0)printf("PASS map%u %s GPU%u\n",map,mapNames[map],bytesNow);
 }
 world_release();assert(!allocated&&!bytesNow);printf("PASS409 actual map loads and full source populations, camps, town flags, save IDs>255 and paged travel; peak world GPU%u at %s; complete teardown.\n",maxBytes,mapNames[maxMap]);
}
