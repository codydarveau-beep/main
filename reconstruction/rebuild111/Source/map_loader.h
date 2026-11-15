/* SPDX-License-Identifier: MIT. One validated terrain/collision load at a time. */
#include "walk_surface.h"
#include "prop_clearance46.h"
#include "world_disc.h"
#include "normal_towns52.h"
#ifndef MYRO_HOST
static void world_terrain_gpu171(unsigned map);
static void world_geometry_gpu171(unsigned map);
#endif
#include "guild_room_geometry194.h"
static void load(unsigned map){
 if(map>=WORLD_MAP_COUNT)fail("Unknown map ID");surfaceMap=map;const WorldBlob*b=worldBlobs[map];
 unsigned char*p;
#ifndef MYRO_HOST
 if(strcmp(mapNames[map],"brasilis"))world_terrain_gpu171(map);else
#endif
 {p=world_expand(map,0,"terrain");
 if(b[0].raw<8)fail("Truncated terrain atlas");memcpy(&tw,p,4);memcpy(&th,p+4,4);
 if(!tw||tw>4096||!th||th>4096||b[0].raw!=8+tw*th*2)fail("Terrain atlas mismatch");terrain=(uint16_t*)(p+8);
 }
 p=world_expand(map,1,"collision");if(b[1].raw<8)fail("Truncated collision");memcpy(&gw,p,4);memcpy(&gh,p+4,4);
 if(gw!=mapWidths[map]*2||gh!=mapHeights[map]*2||b[1].raw<12+gw*gh)fail("Collision dimensions mismatch");walk=p+8;
 for(unsigned i=0;i<gw*gh;i++)if(walk[i]>1)fail("Invalid walk flag");
 memcpy(&surfaceCount45,walk+gw*gh,4);if(surfaceCount45>gw*gh||b[1].raw<16+gw*gh+surfaceCount45*12)fail("Collision surface layout mismatch");surfaceCells45=(const WalkSurface*)(walk+gw*gh+4);for(unsigned i=0;i<surfaceCount45;i++)if(surfaceCells45[i].cell>=gw*gh||(i&&surfaceCells45[i-1].cell>=surfaceCells45[i].cell)||!walk[surfaceCells45[i].cell])fail("Invalid collision surface directory");
 unsigned propOffset46=12+gw*gh+surfaceCount45*12;memcpy(&propCount46,p+propOffset46,4);if(propCount46>gw*gh||b[1].raw!=propOffset46+4+propCount46*8)fail("Solid base directory mismatch");propCells46=(const PropCell46*)(p+propOffset46+4);for(unsigned i=0;i<propCount46;i++)if(propCells46[i].cell>=gw*gh||!propCells46[i].bits||propCells46[i].pad||(i&&propCells46[i-1].cell>=propCells46[i].cell))fail("Invalid solid base record");
 p=world_expand(map,2,"camp");if(b[2].raw!=8)fail("Camp size mismatch");memcpy(&spawnx,p,4);memcpy(&spawny,p+4,4);free(p);
 if(!isfinite(spawnx)||!isfinite(spawny)||spawnx<8||spawny<8||spawnx>=gw*8-8||spawny>=gh*8-8)fail("Camp bounds invalid");
#ifndef MYRO_HOST
 world_geometry_gpu171(map);
#else
 p=world_expand(map,3,"geometry");meshRaw=p;if(b[3].raw<12)fail("Truncated terrain geometry");memcpy(&mw,p,4);memcpy(&mh,p+4,4);memcpy(&nverts,p+8,4);
 if(mw!=mapWidths[map]||mh!=mapHeights[map]||nverts>1000000||nverts%3||b[3].raw!=12+(mw*mh+1)*4+mw*mh*16+nverts*20)fail("Geometry dimensions mismatch");
 cellStarts=malloc((mw*mh+1)*4);groundHeights=malloc(mw*mh*16);if(!cellStarts||!groundHeights)fail("Geometry metadata allocation failed");memcpy(cellStarts,p+12,(mw*mh+1)*4);memcpy(groundHeights,p+12+(mw*mh+1)*4,mw*mh*16);meshVertices=(float*)(p+12+(mw*mh+1)*4+mw*mh*16);
 if(cellStarts[mw*mh]!=nverts)fail("Geometry directory mismatch");for(unsigned i=0;i<mw*mh;i++)if(cellStarts[i]>cellStarts[i+1]||cellStarts[i]%3)fail("Invalid geometry directory");
 for(unsigned i=0;i<mw*mh*4;i++)if(!isfinite(groundHeights[i]))fail("Invalid ground height");
#endif
 if(map==494)guild_floor_capture197();
 if(!ordinary_collision52(map,&propCount46,propCells46))fail("Ordinary town collision override invalid");
}
