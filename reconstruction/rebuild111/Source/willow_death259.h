/* Original Willow death ACTs drawn from shared, small source layers.
 * Frame-fenced, species-shared textures bound GPU memory independently of deaths. */
#ifndef MYRO_WILLOW_DEATH259_H
#define MYRO_WILLOW_DEATH259_H
typedef struct{short x,y;float sx,sy;short angle,mirror;unsigned short u,v,w,h;}WillowLayer259;
typedef struct{unsigned short first,count;}WillowPose259;
typedef struct{const unsigned char*packed;unsigned bytes,height,frames,ms;const WillowLayer259*layers;const WillowPose259(*poses)[22];}WillowArt259;
#include "willow_art259.h"
static void*willowTexture259[2];static unsigned willowUsed259[2];
static unsigned willow_death_code259(unsigned kind,int dir,float elapsed){if(kind!=19&&kind!=27)return 1;unsigned species=kind==27;const WillowArt259*a=willowArt259+species;if(dir<0||dir>7)dir=0;unsigned frame=elapsed>0?(unsigned)(elapsed*1000/a->ms):0;if(frame>=a->frames)frame=a->frames-1;return 2+dir*32+frame;}
static void willow_release259(void){for(unsigned i=0;i<2;i++){if(willowTexture259[i])MmFreeContiguousMemory(willowTexture259[i]);willowTexture259[i]=NULL;willowUsed259[i]=0;}}
/* Call only at the GPU frame fence. No allocation in the actor draw loop. */
static void willow_prepare259(unsigned needed,unsigned now){for(unsigned i=0;i<2;i++){if(needed&(1u<<i)){willowUsed259[i]=now;if(!willowTexture259[i]){const WillowArt259*a=willowArt259+i;unsigned size=512*a->height*2;unsigned char*raw=inflateasset("original Willow death layers",a->packed,a->bytes,size);willowTexture259[i]=gpu_alloc(size);memcpy(willowTexture259[i],raw,size);free(raw);}}else if(willowTexture259[i]&&(unsigned)(now-willowUsed259[i])>=3000){MmFreeContiguousMemory(willowTexture259[i]);willowTexture259[i]=NULL;}}}
typedef struct{float x,y,u,v;}WillowVertex259;
static unsigned willow_clip259(WillowVertex259*out,const WillowVertex259*in,unsigned n,float edge,int lower){unsigned count=0;if(!n)return 0;WillowVertex259 a=in[n-1];int ia=lower?a.y>=edge:a.y<=edge;for(unsigned i=0;i<n;i++){WillowVertex259 b=in[i];int ib=lower?b.y>=edge:b.y<=edge;if(ia!=ib){float t=(edge-a.y)/(b.y-a.y);out[count++]=(WillowVertex259){a.x+(b.x-a.x)*t,edge,a.u+(b.u-a.u)*t,a.v+(b.v-a.v)*t};}if(ib)out[count++]=b;a=b;ia=ib;}return count;}
static void willow_draw259(unsigned species,unsigned code,float x,float y,float depth,float scale){if(species>1||!willowTexture259[species])fail("Willow layers were not prepared");const WillowArt259*a=willowArt259+species;unsigned dir=code/32,frame=code%32;if(dir>=8||frame>=a->frames)fail("Willow death pose invalid");const WillowPose259*pose=&a->poses[dir][frame];gpu_depth_state(0);program(0);bindTexture(willowTexture259[species],512,a->height,1024,0x00011d2a);uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);for(unsigned i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);
 for(unsigned i=0;i<pose->count;i++){const WillowLayer259*l=a->layers+pose->first+i;float angle=l->angle*.0174532925199433f,co=cosf(angle),si=sinf(angle),cx=x+l->x*scale,cy=y+(l->y-6)*scale,hw=l->w*l->sx*scale*.5f,hh=l->h*l->sy*scale*.5f;WillowVertex259 points[8],temp[8],clipped[8];for(unsigned j=0;j<4;j++){int right=j==1||j==2,bottom=j>=2;float dx=right?hw:-hw,dy=bottom?hh:-hh;points[j]=(WillowVertex259){cx+co*dx-si*dy,cy+si*dx+co*dy,l->u+((right^l->mirror)?l->w:0),l->v+(bottom?l->h:0)};}unsigned n=willow_clip259(temp,points,4,spriteClipLow54,1);n=willow_clip259(clipped,temp,n,spriteClipHigh54,0);if(n<3)continue;p=pb_push1(p,NV097_SET_BEGIN_END,7);for(unsigned j=0;j<n;j++)p=vertex(p,clipped[j].x,clipped[j].y,depth,clipped[j].u,clipped[j].v);p=pb_push1(p,NV097_SET_BEGIN_END,0);
 }pb_end(p);
}
#endif
