/* Actual streamed-map loader with tracked host GPU allocations. */
#define main unused_world_residency234
#include "test_world43.c"
#undef main
int main(void){setvbuf(stdout,NULL,_IONBF,0);unsigned peak=0,peakMap=0,failed=0;for(unsigned map=0;map<WORLD_MAP_COUNT;map++){if(!world_activate(map)){fprintf(stderr,"Map %u could not load\n",map);failed++;continue;}unsigned expected=2u+!!sceneMesh+!!sceneTexture;assert(allocated==expected&&bytesNow>0);if(bytesNow>peak){peak=bytesNow;peakMap=map;}printf("MAP %u GPU %u grid %u %u terrain %u %u\n",map,bytesNow,gw,gh,mw,mh);}world_release();assert(!allocated&&!bytesNow&&!failed);printf("PASS all %u streamed maps, GPU peak %u on map %u. CPU-backed GPU recorder only; excludes full native heap/framebuffers/audio/caches and is not Xbox residency evidence.\n",WORLD_MAP_COUNT,peak,peakMap);return 0;}
