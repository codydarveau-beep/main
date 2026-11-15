/* Original complete animations: metadata per active species, a 2 MiB crop LRU.
 * Cache entries are cached CPU RAM. No CPU reads from GPU allocations. */
#ifndef ENEMY_FILE_BYTES
#include "enemy_disc_data44.h"
#endif
#include "enemy_stream_data51.h"
#include "guardian_baked162.h"
#include "legacy_enemy_streams171.h"
static FILE*enemyStreamFile51;
static unsigned char*enemy_read51(unsigned offset,unsigned size){
 if(!size||offset>ENEMY_FILE_BYTES||size>ENEMY_FILE_BYTES-offset)fail("Creature stream bounds invalid");
 if(!enemyStreamFile51){
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_ENEMY_PATH");if(!path)path="../Enemies/enemies.bin";
#else
 const char*path="D:\\enemies.bin";
#endif
 enemyStreamFile51=fopen(path,"rb");if(!enemyStreamFile51)fail("Cannot open creature stream");if(fseek(enemyStreamFile51,0,SEEK_END)||ftell(enemyStreamFile51)!=ENEMY_FILE_BYTES)fail("Creature pack size mismatch");}
 unsigned char*p=malloc(size);if(!p)fail("Creature read allocation failed");
 if(fseek(enemyStreamFile51,offset,SEEK_SET)||fread(p,1,size,enemyStreamFile51)!=size)fail("Creature stream read failed");return p;
}

#include "enemy_packed_cache164.h"
#define ENEMY_CROP_SLOTS164 128u
typedef struct {SparseSprite*source;unsigned frame,used,bytes,touched183;unsigned char*p;} CropCache51;
static CropCache51 cropCache51[ENEMY_CROP_SLOTS164];static unsigned cropClock51,cropBytes51;
static void enemy_cache_clear51(void){for(unsigned i=0;i<ENEMY_CROP_SLOTS164;i++){free(cropCache51[i].p);memset(&cropCache51[i],0,sizeof(CropCache51));}cropBytes51=0;enemy_packed_clear164();if(enemyStreamFile51){fclose(enemyStreamFile51);enemyStreamFile51=NULL;}}
static void enemy_cache_frame183(unsigned now){enemyCacheTime183=now;for(unsigned i=0;i<ENEMY_CROP_SLOTS164;i++){CropCache51*c=cropCache51+i;if(c->p&&(unsigned)(now-c->touched183)>=15000){cropBytes51-=c->bytes;free(c->p);memset(c,0,sizeof(*c));}}for(unsigned i=0;i<ENEMY_PACKED_SLOTS164;i++){EnemyPacked164*c=enemyPacked164+i;if(c->data&&(unsigned)(now-c->touched183)>=15000){enemyPackedBytes164-=c->bytes;free(c->data);memset(c,0,sizeof(*c));}}}
static void sprite_stream_load51(unsigned k){
 unsigned art171=mob_art_kind55(k);const EnemyStream51*b=art171<50?&legacyEnemyStreams171[art171]:&enemyStreams51[art171-50];SparseSprite*s=&sprites[k+1];if(b->guardian&&guardianSprites162)b=&guardianBaked162[b->guardian-7];
 if(b->guardian){
  unsigned bytes=40*12+40*4+5*20;unsigned*p=calloc(1,bytes);if(!p)fail("Guardian metadata allocation failed");s->raw=(unsigned char*)p;s->meta=p;s->sequence=p+120;s->directory=s->sequence+40;s->w=128;s->h=256;s->anchorX=64;s->anchorY=210;s->frames=5;s->actions=40;s->sequenceCount=40;s->bytesPerPixel=2;s->guardian51=b->guardian;
  for(unsigned a=0;a<40;a++){s->meta[a*3]=a;s->meta[a*3+1]=1;s->meta[a*3+2]=100;s->sequence[a]=a/8;}
  for(unsigned a=0;a<5;a++){s->directory[a*5]=4;s->directory[a*5+1]=4;s->directory[a*5+2]=120;s->directory[a*5+3]=206;}return;
 }
 if(b->raw>262144||b->raw<32)fail("Creature metadata size invalid");unsigned char*p=enemy_read51(b->offset,b->packed);if(crc32(0,p,b->packed)!=b->crc)fail("Creature metadata checksum failed");
 unsigned char*raw=inflateasset("creature metadata",p,b->packed,b->raw);free(p);memcpy(s,raw,32);s->raw=raw;s->bytesPerPixel=2;s->alpha4444=(s->pixelBytes>>30)&1;s->pixelBytes&=0x3fffffff;s->stream51=b;
 /* Correct the immutable pack coordinate origin, preserving original hovering offsets. */
 if(s->anchorY<ENEMY_ANCHOR_BIAS51)fail("Creature anchor bias invalid");s->anchorY-=ENEMY_ANCHOR_BIAS51;
 if(s->w<128||s->w>1024||s->h<128||s->h>1024||s->actions!=40||!s->frames||s->frames>8192||s->sequenceCount>32768||s->anchorX>s->w||s->anchorY>s->h)fail("Creature stream header invalid");
 unsigned bytes=32+s->actions*12+s->sequenceCount*4+s->frames*36;if(bytes!=b->raw)fail("Creature stream layout invalid");
 s->meta=(unsigned*)(raw+32);s->sequence=s->meta+s->actions*3;s->directory=s->sequence+s->sequenceCount;s->blocks51=s->directory+s->frames*5;
 for(unsigned i=0;i<s->actions;i++){unsigned*a=s->meta+i*3;if(a[0]>s->sequenceCount||!a[1]||a[1]>s->sequenceCount-a[0]||a[2]<20)fail("Creature action invalid");}
 for(unsigned i=0;i<s->sequenceCount;i++)if(s->sequence[i]>=s->frames)fail("Creature sequence invalid");
 for(unsigned i=0;i<s->frames;i++){unsigned*d=s->directory+i*5,*f=s->blocks51+i*4;if(d[0]>s->w||d[1]>s->h||!d[2]||!d[3]||d[2]>s->w-d[0]||d[3]>s->h-d[1]||f[2]!=d[2]*d[3]*2||f[2]>2097152||f[0]>b->framesBytes||f[1]>b->framesBytes-f[0])fail("Creature crop invalid");}
}
static unsigned char*sprite_crop51(SparseSprite*s,unsigned frame){
 unsigned tick=++cropClock51;for(unsigned i=0;i<ENEMY_CROP_SLOTS164;i++)if(cropCache51[i].source==s&&cropCache51[i].frame==frame){cropCache51[i].used=tick;cropCache51[i].touched183=enemyCacheTime183;return cropCache51[i].p;}
 unsigned*f=s->blocks51+frame*4;int slot=-1;unsigned budget171=2097152;
#ifndef MYRO_HOST
 MM_STATISTICS memory171={0};memory171.Length=sizeof(memory171);MmQueryStatistics(&memory171);if((uint64_t)memory171.AvailablePages*4096<6u*1024u*1024u){budget171=f[2]>524288?f[2]:524288;enemy_packed_clear164();}
#endif

 while(slot<0||cropBytes51+f[2]>budget171){
  unsigned oldest=~0u;int victim=-1;for(unsigned i=0;i<ENEMY_CROP_SLOTS164;i++){if(!cropCache51[i].p){if(slot<0)slot=i;continue;}if(cropCache51[i].used<oldest){oldest=cropCache51[i].used;victim=i;}}
  if(slot>=0&&cropBytes51+f[2]<=budget171)break;if(victim<0)fail("Creature cache capacity invalid");cropBytes51-=cropCache51[victim].bytes;free(cropCache51[victim].p);memset(&cropCache51[victim],0,sizeof(CropCache51));slot=victim;
 }
 int borrowed164=0;unsigned char*cp=enemy_frame_packed164(s->stream51->framesOffset+f[0],f[1],f[3],f[2],&borrowed164);if(crc32(0,cp,f[1])!=f[3])fail("Creature frame checksum failed");unsigned char*p=inflateasset("creature frame",cp,f[1],f[2]);if(!borrowed164)free(cp);cropCache51[slot]=(CropCache51){s,frame,tick,f[2],enemyCacheTime183,p};cropBytes51+=f[2];return p;
}
