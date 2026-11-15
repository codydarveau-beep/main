/* Preserve original magenta cutouts without doubling terrain GPU memory.
 * Opaque maps keep their exact RGB565 data. Keyed maps use A1R5G5B5;
 * their green channel is reduced from6 to5 bits to make room for alpha. */
#ifndef MYRO_TERRAIN_KEY52_H
#define MYRO_TERRAIN_KEY52_H
#include <stdint.h>
#define TERRAIN_RGB565_52 0x0001112au
#define TERRAIN_ARGB1555_52 0x0001102au
static unsigned groundTextureFormat52=TERRAIN_RGB565_52;
static int terrain_magenta52(uint16_t v){return(v>>11)>=29&&((v>>5)&63)<5&&(v&31)>=29;}
static unsigned terrain_prepare52(uint16_t*p,unsigned count){
 unsigned i=0;for(;i<count;i++)if(terrain_magenta52(p[i]))break;
 if(i==count)return TERRAIN_RGB565_52;
 for(i=0;i<count;i++){unsigned v=p[i];p[i]=terrain_magenta52(v)?0:(uint16_t)(0x8000u|((v>>11)<<10)|(((v>>6)&31)<<5)|(v&31));}
 return TERRAIN_ARGB1555_52;
}
#endif
