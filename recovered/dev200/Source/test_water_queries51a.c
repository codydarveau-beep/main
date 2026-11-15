/* Actual source-derived rendering/wading table: every map and bad IDs. */
#define main old_water_renderer_test
#include "test_water23.c"
#undef main
#include "combat.h"
static unsigned activeMap;static float testGround51a;
static int allowed(float x,float y){return x>=0&&y>=0;}
static float height_at(float x,float y){(void)x;(void)y;return testGround51a;}
#include "water_query.h"
int main(void){unsigned checked=0;
 for(unsigned map=0;map<WORLD_MAP_COUNT;map++){activeMap=map;assert(water_map_valid51a(map));
  if(!waterMaps[map].count){assert(!world_in_water(NULL,1,1,1,1));continue;}
  const unsigned short*r=waterRects[waterMaps[map].start];float x=(r[0]+r[2])*.5f,y=(r[1]+r[3])*.5f;
  testGround51a=waterMaps[map].z-.2f;assert(world_in_water(NULL,x,y,x,y));testGround51a=waterMaps[map].z+1;assert(!world_in_water(NULL,x,y,x,y));checked++;
 }
 for(unsigned i=0;i<3;i++){activeMap=(unsigned[]){WORLD_MAP_COUNT,WORLD_MAP_COUNT+1,~0u}[i];assert(!water_map_valid51a(activeMap)&&!world_in_water(NULL,1,1,1,1));static Combat g;assert(!world_test_water(&g));}
 printf("PASS409 bounded water queries; %u wet maps/bridge-height exclusion; invalid IDs rejected.\n",checked);
}
