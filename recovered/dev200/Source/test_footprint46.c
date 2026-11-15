/* MIT. Actual clearance helper against blocked source cells. */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "walk_footprint46.h"
int main(void){unsigned char mask[16*16];memset(mask,1,sizeof(mask));mask[8*16+8]=0;
 assert(!walk_footprint46(mask,16,16,68,68));
 assert(!walk_footprint46(mask,16,16,63,68));
 assert(walk_footprint46(mask,16,16,61,68));
 assert(!walk_footprint46(mask,16,16,62,62));
 assert(walk_footprint46(mask,16,16,61,61));
 assert(!walk_footprint46(mask,16,16,NAN,68));assert(!walk_footprint46(mask,16,16,-1,68));
 memset(mask,0,sizeof(mask));for(int y=1;y<15;y++)mask[y*16+6]=1;
 for(float y=12;y<116;y+=.25f)assert(walk_footprint46(mask,16,16,52,y));
 memset(mask,1,sizeof(mask));PropCell46 prop={8*16+8,0x0660,0};propCells46=&prop;propCount46=1;assert(!walk_footprint46(mask,16,16,68,68));assert(walk_footprint46(mask,16,16,60,68));propCount46=0;propCells46=NULL;assert(walk_footprint46(mask,16,16,68,68));
 puts("PASS46 blocked-cell interior/edge/rounded corner clearance, finite/bounds guards, one-cell passage preserved.");}
