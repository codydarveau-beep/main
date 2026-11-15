/* MIT. Fit the real native monster frame crops at every direction and zoom. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned sz,unsigned raw){(void)n;unsigned char*d=malloc(raw);assert(d);uLongf len=raw;assert(uncompress(d,&len,p,sz)==Z_OK&&len==raw);return d;}
#define MYRO_HOST 1
#include "sprites.h"
#include "target_geometry41.h"
int main(void){enemy_blob_init();unsigned cases=0;for(int k=0;k<MOB_SPEC_COUNT;k++){SparseSprite s={0};sprite_load(&s,"target",enemyData[k],enemySize[k],enemyRaw[k]);TargetTrack41 track={0};for(int zoom=0;zoom<3;zoom++)for(unsigned f=0;f<s.frames;f++){unsigned*d=s.directory+f*5;if(!d[2]||!d[3])continue;float scale=(zoom==0?.85f:zoom==1?1.2f:1.8f)/3;TargetBounds41 b;assert(target_bounds41(&track,k,1,d,s.anchorX,s.anchorY,320,240,scale,.016f,&b));float x0=320+(d[0]-(float)s.anchorX)*scale,y0=240+(d[1]-(float)s.anchorY)*scale;assert(b.x0<=x0-2.999f&&b.y0<=y0-2.999f&&b.x1>=x0+d[2]*scale+2.999f&&b.y1>=y0+d[3]*scale+2.999f);cases++;}free(s.raw);}printf("PASS41 %u actual enemy frame/zoom crops fit with three-pixel padding and breathing bounds\n",cases);}
