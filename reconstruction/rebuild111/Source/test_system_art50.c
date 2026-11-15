/* MIT. Actual native sparse decoder and bounded system disc reader. */
#define MYRO_HOST 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned size,unsigned raw){(void)n;unsigned char*out=malloc(raw);assert(out);uLongf length=raw;assert(uncompress(out,&length,p,size)==Z_OK&&length==raw);return out;}
#include "sprites.h"
#include "system_disc50.h"
int main(void){unsigned frames=0,maximum=0;
 for(unsigned i=0;i<23;i++){unsigned char*p=system_packed50(i);SparseSprite shape={0};const SystemBlob50*b=&systemBlobs50[i];sprite_load(&shape,"source companion",p,b->packed,b->raw);free(p);assert(shape.alpha4444&&shape.bytesPerPixel==2&&shape.actions==40&&shape.h==256);if(b->raw>maximum)maximum=b->raw;for(unsigned a=0;a<40;a++)for(unsigned k=0;k<shape.meta[a*3+1];k++){unsigned frame=shape.sequence[shape.meta[a*3]+k];assert(frame<shape.frames);frames++;}for(unsigned d=0;d<8;d++)for(unsigned xy=0;xy<2;xy++)assert(isfinite(companionContact50[i][d][xy])&&fabsf(companionContact50[i][d][xy])<128);free(shape.raw);}
 unsigned char*p=system_expand50(23);unsigned w,h;memcpy(&w,p,4);memcpy(&h,p+4,4);assert(w==1024&&h==512&&systemBlobs50[23].raw==8+w*h*2);free(p);
 p=system_expand50(24);unsigned models,n;memcpy(&models,p,4);memcpy(&n,p+4,4);assert(models==10&&systemBlobs50[24].raw==88+n*20&&n%3==0);const unsigned*directory=(const unsigned*)(p+8);for(int i=0;i<10;i++){assert(directory[i*2]+directory[i*2+1]<=n&&directory[i*2+1]%3==0);}
 const float*v=(const float*)(p+88);for(unsigned i=0;i<n;i++){for(int k=0;k<5;k++)assert(isfinite(v[i*5+k]));assert(v[i*5+3]>=0&&v[i*5+3]<=w&&v[i*5+4]>=0&&v[i*5+4]<=h);}free(p);
 printf("PASS50 23 original companion actors (%u actual ACT frames), maximum one-actor decode %u bytes; ten complete original trap meshes (%u vertices), cutout atlas and CRC-checked disc sections.\n",frames,maximum,n);
}
