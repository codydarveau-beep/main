/* MIT. Actual actor pixels -> shared gpu_sprite quad -> projected world contact. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <zlib.h>
#include "projection.h"
#include "player_contact.h"
#include "actor_data.h"
static unsigned u32(const unsigned char*p){return p[0]|p[1]<<8|p[2]<<16|(unsigned)p[3]<<24;}
int main(int argc,char**argv){assert(argc==2);FILE*f=fopen(argv[1],"rb");assert(f);unsigned char*b=malloc(ACTOR_FILE_BYTES);assert(fread(b,1,ACTOR_FILE_BYTES,f)==ACTOR_FILE_BYTES);assert(fgetc(f)==EOF);fclose(f);unsigned checks=0;
 for(unsigned variant=0;variant<ACTOR_VARIANTS;variant++){const ActorBlob*a=&actorBlobs[variant];assert(crc32(0,b+a->offset,a->packed)==a->crc);unsigned char*raw=malloc(a->raw);uLongf n=a->raw;assert(uncompress(raw,&n,b+a->offset,a->packed)==Z_OK&&n==a->raw);unsigned frames=u32(raw+8),actions=u32(raw+12),seq=u32(raw+16),ax=u32(raw+20),ay=u32(raw+24),h=u32(raw+4),directory=32+actions*12+seq*4,pixels=directory+frames*20;
 for(unsigned dir=0;dir<8;dir++){unsigned first=u32(raw+32+dir*12),frame=u32(raw+32+actions*12+first*4);const unsigned char*d=raw+directory+frame*20;unsigned x=u32(d),y=u32(d+4),w=u32(d+8),hh=u32(d+12),off=u32(d+16);int lo=10000,hi=-1;for(unsigned yy=hh>14?hh-14:0;yy<hh;yy++)for(unsigned xx=0;xx<w;xx++){const unsigned char*p=raw+pixels+off+(yy*w+xx)*2;if(p[1]&128){if((int)(x+xx)<lo)lo=x+xx;if((int)(x+xx)>hi)hi=x+xx;}}assert(hi>=lo);float fx=(lo+hi)*.5f;int left=0,right=0;for(unsigned yy=hh>14?hh-14:0;yy<hh;yy++)for(unsigned xx=0;xx<w;xx++){const unsigned char*p=raw+pixels+off+(yy*w+xx)*2;if(p[1]&128){if(x+xx<=fx&&(int)(y+yy+1)>left)left=y+yy+1;if(x+xx>=fx&&(int)(y+yy+1)>right)right=y+yy+1;}}float fy=(left+right)*.5f;
 for(int rot=0;rot<32;rot++)for(int tilt=0;tilt<3;tilt++)for(int iz=0;iz<3;iz++)for(int slope=0;slope<3;slope++){float zoom=iz==0?.85f:iz==1?1.2f:1.8f,z=slope==0?0:slope==1?15:-23,m[16],px,py;world_camera(m,1234.5f,1567.25f,z,rot*.19634954f,.52f+tilt*.305f,zoom);world_project(m,1234.5f,1567.25f,z,&px,&py);float rect[4],scale=zoom/3;sprite_screen_rect(px+playerContact[a->job][dir][0]*scale,py+playerContact[a->job][dir][1]*scale,scale,ax,ay,h,rect);assert(fabsf(rect[0]+fx*scale-px)<.002f&&fabsf(rect[1]+fy*scale-py)<.002f);assert(fabsf(px-320)<.002&&fabsf(py-245)<.002);checks++;}
 }free(raw);}free(b);printf("PASS %u real pixel/quad/world-contact checks across14 actors,8 directions,32 rotations,3 tilts,3 zooms,3 heights\n",checks);
}
