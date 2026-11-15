/* Original indexed hair sprites and exact body-material palette replacement. */
#ifndef MYRO_APPEARANCE_RENDER58_H
#define MYRO_APPEARANCE_RENDER58_H
#include "appearance_data58.h"
#include "appearance_stream181.h"
typedef struct{unsigned char*raw;unsigned key,actions,frames,pixelBytes;unsigned*meta;int*directory;unsigned short*palettes;unsigned char*pixels;}HairCache58;
static HairCache58 hairCaches58[3];
static void appearance_hair_release58(void){for(unsigned i=0;i<3;i++){free(hairCaches58[i].raw);memset(clothCaches181+i,0,sizeof(clothCaches181[i]));memset(hairCaches58+i,0,sizeof(*hairCaches58));}}
static HairCache58*appearance_hair58(const SparseSprite*s,unsigned slot){
 if(slot>=3||!s->appearancePoses58)return NULL;unsigned key=(s->sex58?42:0)+s->appearance58.hair;if(key>=84)fail("Hair style outside catalog");HairCache58*c=hairCaches58+slot;if(c->raw&&c->key==key)return c;
 free(c->raw);memset(c,0,sizeof(*c));const ActorBlob*b=hairBlobs58+key;unsigned char*packed=actor_blob_packed58(b,ACTOR_VARIANTS+key);c->raw=inflateasset("original hair",packed,b->packed,b->raw);free(packed);c->key=key;
 unsigned*header=(unsigned*)c->raw;c->actions=header[0];c->frames=header[1];c->pixelBytes=header[2];unsigned bytes=12+c->actions*8+c->frames*28+9*512;
 if(c->actions>256||!c->actions||c->frames>4096||bytes>b->raw||c->pixelBytes!=b->raw-bytes)fail("Hair layout invalid");c->meta=header+3;c->directory=(int*)(c->meta+c->actions*2);c->palettes=(unsigned short*)(c->directory+c->frames*7);c->pixels=(unsigned char*)(c->palettes+9*256);
 for(unsigned i=0;i<c->actions;i++){unsigned*a=c->meta+i*2;if(!a[1]||a[0]>c->frames||a[1]>c->frames-a[0])fail("Hair action invalid");}
 for(unsigned i=0;i<c->frames;i++){int*d=c->directory+i*7;if(d[2]<0||d[3]<0||d[4]<0||d[5]<0||d[2]+d[4]>128||d[3]+d[5]>256||d[6]<0||(unsigned)d[6]>c->pixelBytes||(unsigned)(d[4]*d[5])>c->pixelBytes-d[6])fail("Hair frame bounds invalid");}return c;
}
static void appearance_bounds58(SparseSprite*s,unsigned frame,unsigned slot,unsigned out[4]){unsigned*d=s->directory+frame*5;out[0]=d[0];out[1]=d[1];out[2]=d[0]+d[2];out[3]=d[1]+d[3];HairCache58*c=appearance_hair58(s,slot);if(!c)return;short*pose=(short*)(s->appearancePoses58+frame*12);unsigned action=(unsigned short)pose[2],source=(unsigned short)pose[3];if(action>=c->actions)action%=8;unsigned*a=c->meta+action*2;if(source>=a[1])source=a[1]-1;int*h=c->directory+(a[0]+source)*7;int l=h[2]+pose[0]-h[0],t=h[3]+pose[1]-h[1]+(unsigned short)pose[4]-160,r=l+h[4],b=t+h[5];if(l<0)l=0;if(t<0)t=0;if(r>128)r=128;if(b>(int)s->h)b=s->h;if(l<r&&t<b){if((unsigned)l<out[0])out[0]=l;if((unsigned)t<out[1])out[1]=t;if((unsigned)r>out[2])out[2]=r;if((unsigned)b>out[3])out[3]=b;}}
static void appearance_sprite58(SparseSprite*s,const Combat*g){if(!appearance_equal58(s->appearance58,g->appearance58)||s->sex58!=g->sex55){s->appearance58=g->appearance58;s->sex58=g->sex55;spriteEpoch++;}}
static void appearance_compose58(SparseSprite*s,unsigned frame,unsigned slot,unsigned char*dest,unsigned bounds[4]){
 unsigned*d=s->directory+frame*5;bounds[0]=d[0];bounds[1]=d[1];bounds[2]=d[0]+d[2];bounds[3]=d[1]+d[3];if(!s->appearancePoses58)return;
 unsigned cloth=s->appearance58.cloth;if(s->actor58>=49||cloth>clothMax58[s->actor58])cloth=0;const short*bodyPose=(const short*)(s->appearancePoses58+frame*12);const uint16_t*clothPalette=appearance_cloth181(s->actor58,(unsigned short)bodyPose[5],cloth,slot);
 if(clothPalette)for(unsigned y=0;y<d[3];y++)for(unsigned x=0;x<d[2];x++){unsigned index=s->material58[d[4]/2+y*d[2]+x];if(index)((unsigned short*)dest)[(d[1]+y)*128+d[0]+x]=clothPalette[index];}
 HairCache58*c=appearance_hair58(s,slot);if(!c)return;short*pose=(short*)(s->appearancePoses58+frame*12);unsigned action=(unsigned short)pose[2],sourceFrame=(unsigned short)pose[3],origin=(unsigned short)pose[4];if(action>=c->actions)action%=8;unsigned*a=c->meta+action*2;if(sourceFrame>=a[1])sourceFrame=a[1]-1;int*h=c->directory+(a[0]+sourceFrame)*7;
 int left=h[2]+pose[0]-h[0],top=h[3]+pose[1]-h[1]+(int)origin-160;unsigned colour=s->appearance58.colour;if(colour>=9)colour=0;unsigned short*palette=c->palettes+colour*256;
 for(int y=0;y<h[5];y++)for(int x=0;x<h[4];x++){unsigned index=c->pixels[h[6]+y*h[4]+x];int dx=left+x,dy=top+y;if(index&&dx>=0&&dx<128&&dy>=0&&dy<(int)s->h)((unsigned short*)dest)[dy*128+dx]=palette[index];}
 int l=left<0?0:left,t=top<0?0:top,r=left+h[4]>128?128:left+h[4],b=top+h[5]>(int)s->h?(int)s->h:top+h[5];if(l<r&&t<b){if((unsigned)l<bounds[0])bounds[0]=l;if((unsigned)t<bounds[1])bounds[1]=t;if((unsigned)r>bounds[2])bounds[2]=r;if((unsigned)b>bounds[3])bounds[3]=b;}
}
#endif
