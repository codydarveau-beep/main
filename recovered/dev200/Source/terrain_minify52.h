/* Loading-time minification filter for Brasilis's two fine stone pavements.
 * The original wave design remains; no per-frame work, new GPU texture, or
 * persistent CPU buffer is added. Profiles match the immutable source atlas. */
#ifndef MYRO_TERRAIN_MINIFY52_H
#define MYRO_TERRAIN_MINIFY52_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
static unsigned terrain_minify52(uint16_t*p,unsigned width,unsigned height,const char*map){
 if(!p||!map||strcmp(map,"brasilis")||width!=1312||height!=1300)return 0;
 static const unsigned slots[2]={20,21};
 static const uint32_t checksums[2]={0x9f7ccb5du,0x1d22a6cfu};
 static const unsigned weight[4]={1,3,3,1};unsigned changed=0;
 uint16_t*source=malloc(256u*256u*2u);if(!source)return 0;
 for(unsigned t=0;t<2;t++){
  unsigned x0=slots[t]%5u*260u+2u,y0=slots[t]/5u*260u+2u;
  for(unsigned y=0;y<256;y++)memcpy(source+y*256,p+(y0+y)*width+x0,512);
  if(crc32(0,(const Bytef*)source,131072)!=checksums[t])continue;
  for(unsigned y=0;y<256;y++)for(unsigned x=0;x<256;x++){
   unsigned r=0,g=0,b=0;
   for(unsigned dy=0;dy<4;dy++)for(unsigned dx=0;dx<4;dx++){
    unsigned v=source[((y+dy-1)&255)*256+((x+dx-1)&255)],w=weight[dy]*weight[dx];
    r+=(v>>11)*w;g+=((v>>5)&63)*w;b+=(v&31)*w;
   }
   p[(y0+y)*width+x0+x]=(uint16_t)((((r+32)/64)<<11)|(((g+32)/64)<<5)|((b+32)/64));
  }
  /* Refresh only this tile's two-pixel sampling gutter. */
  for(unsigned y=0;y<256;y++){
   uint16_t*row=p+(y0+y)*width+x0;row[-1]=row[-2]=row[0];row[256]=row[257]=row[255];
  }
  for(unsigned k=1;k<=2;k++){
   memcpy(p+(y0-k)*width+x0-2,p+y0*width+x0-2,520);
   memcpy(p+(y0+255+k)*width+x0-2,p+(y0+255)*width+x0-2,520);
  }
  changed++;
 }
 free(source);return changed;
}
#endif
