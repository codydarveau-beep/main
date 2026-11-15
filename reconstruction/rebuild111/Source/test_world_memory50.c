/* MIT. Map-release hook executes before allocation of the next map. */
#define main old_world_memory50_main
#include "test_world43.c"
#undef main
static unsigned releases50;
static void release_probe50(void){releases50++;assert(gpuTerrain||!allocated);}
int main(void){
 world_blob_init();visualCacheRelease50=release_probe50;
 unsigned baseline[WORLD_MAP_COUNT]={0};
 for(unsigned i=0;i<90;i++){
  unsigned map=(i%3==0)?3:(i%3==1)?2:7;unsigned before=releases50;
  assert(world_activate(map));assert(releases50==before+1&&allocated==4);
  if(!baseline[map])baseline[map]=bytesNow;assert(bytesNow==baseline[map]);
  assert(world_activate(map)&&releases50==before+1);
 }
 world_release();assert(!bytesNow&&!allocated&&releases50==91);
 printf("PASS50 90 Izlude/Prontera/Sograt loads: visual release precedes new allocations, stable per-map GPU residency and complete final teardown. Izlude world GPU bytes %u.\n",baseline[3]);
}
