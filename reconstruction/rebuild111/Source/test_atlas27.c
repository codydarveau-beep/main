#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "skin_data.h"
#include "minimap.h"
extern const unsigned char skin_image[];extern const unsigned int skin_image_raw,skin_image_size;
int main(void){uint32_t *p=malloc(skin_image_raw),*original=malloc(skin_image_raw);uLongf n=skin_image_raw;assert(uncompress((void*)original,&n,skin_image,skin_image_size)==Z_OK&&n==512*256*4);unsigned char*grid=malloc(400*400);memset(grid,1,400*400);unsigned dims[][2]={{400,400},{400,400},{312,392},{268,268},{380,340},{400,400},{400,400}};for(unsigned k=0;k<7;k++){memcpy(p,original,n);minimap_raster(p,512,288,144,grid,dims[k][0],dims[k][1]);for(unsigned i=0;i<58;i++){const unsigned short*r=skinRects[i];assert(r[0]+r[2]<=512&&r[1]+r[3]<=256);assert(r[0]+r[2]<=288||r[0]>=384||r[1]+r[3]<=144||r[1]>=216);for(int y=0;y<r[3];y++)assert(!memcmp(p+(r[1]+y)*512+r[0],original+(r[1]+y)*512+r[0],r[2]*4));}}free(p);free(original);free(grid);puts("PASS 58 atlas rectangles and icon pixels survive all seven minimap raster updates");}
