/* MIT. Real disc body frames, original creature fade alpha and four-pose ghost lifetime. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include "combat.h"
#define MYRO_HOST 1
#define MYRO_DISC_ENEMIES44 1
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned sz,unsigned raw){(void)n;unsigned char*q=malloc(raw);assert(q);uLongf len=raw;assert(uncompress(q,&len,p,sz)==Z_OK&&len==raw);return q;}
#include "sprites.h"
#include "sprite_tint.h"
#include "projection.h"
#include "player_contact.h"
typedef struct {int slot,kind;unsigned frame;float x,y,depth;} DrawActor;
static unsigned allocated45,draws45;
static void*gpu_alloc(unsigned n){assert(n==32768);allocated45++;return calloc(1,n);}
static void MmFreeContiguousMemory(void*p){assert(p&&allocated45);allocated45--;free(p);}
static float height_at(float x,float y){(void)x;(void)y;return 0;}
static void gpu_sprite(void*t,SparseSprite*s,float x,float y,float z,float scale){assert(t&&s->alpha4444&&s->h==128&&scale>0&&isfinite(x)&&isfinite(y)&&isfinite(z));unsigned count=0;uint16_t*p=t;for(unsigned i=0;i<128*128;i++)if(p[i]>>12){assert((p[i]>>12)<=9);count++;}assert(count>0);draws45++;}
#include "quicken_trail45.h"
int main(void){sprite_set_equipment(7,32);assert(spriteJob==7&&spriteGear==3&&sprites[0].actions==64);for(int d=0;d<8;d++)assert(sprites[0].meta[(2*8+d)*3+1]==9);Combat g;combat_init(&g,1500,1500,NULL,NULL);g.jobId=7;g.quickenLeft=30;float matrix[16];world_camera(matrix,g.x,g.y,0,0,.8f,1.2f);for(int i=0;i<8;i++){g.time=1+i*.06f;DrawActor a={.frame=sprite_frame(&sprites[0],2,0,i*.05f,.45f,0)};quicken_record45(&g,&a,0);quicken_draw45(&g,matrix,1.2f);}assert(allocated45==4&&draws45>8);g.quickenLeft=0;quicken_record45(&g,&(DrawActor){0},0);assert(!allocated45);free(sprites[0].raw);sprites[0].raw=NULL;
unsigned partial=0;for(int k=19;k<=38;k++){if(k!=19&&k!=21&&k!=27&&k!=38)continue;sprite_load_enemy44(k);SparseSprite*s=&sprites[k+1];assert(s->alpha4444&&s->bytesPerPixel==2);for(unsigned i=0;i<s->pixelBytes;i+=2){unsigned a=*(const uint16_t*)(s->pixels+i)>>12;if(a&&a<15)partial++;}sprite_tint4444_45(s->pixels,s->pixelBytes/2,1,1,1);}assert(partial>1000);sprite_release_enemies();printf("PASS45 originalKnight72twohandattackframes,4boundedfadingposebuffers/free,allthreecreatures4bitalphafades(%u partial pixels)andstatuscomposition.\n",partial);}
