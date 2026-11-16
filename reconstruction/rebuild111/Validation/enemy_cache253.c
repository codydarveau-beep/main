#define MYRO_HOST
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf len=raw;assert(uncompress(b,&len,p,packed)==Z_OK&&len==raw);return b;}
#include "sprites.h"
int main(void){sprite_stream_load51(448);sprite_stream_load51(449);unsigned requests=0,large=0;for(unsigned round=0;round<12;round++)for(unsigned bank=0;bank<2;bank++){SparseSprite*s=sprites+449+bank;for(unsigned dir=0;dir<4;dir++){unsigned*a=s->meta+(16+dir)*3;for(unsigned phase=0;phase<8;phase++){unsigned frame=s->sequence[a[0]+phase*a[1]/8];unsigned char*p=sprite_crop51(s,frame);assert(p);requests++;large+=s->blocks51[frame*4+2]>16384;assert(cropBytes51<=2097152&&enemyPackedBytes164<=ENEMY_PACKED_BYTES164);}}}printf("Requests%u large%u frame disc reads%u packed hits%u rawbytes%u packedbytes%u\n",requests,large,enemyDiskReads164,enemyPackedHits164,cropBytes51,enemyPackedBytes164);
#ifdef MYRO_NO_PACKED_CACHE164
assert(enemyDiskReads164>=requests/2&&!enemyPackedHits164);
#else
assert(enemyDiskReads164<requests/2);assert(enemyPackedHits164>0);
#endif
enemy_cache_frame183(14000);SparseSprite*active=sprites+449;unsigned activeFrame=active->sequence[active->meta[16*3]];unsigned char*activePixels=sprite_crop51(active,activeFrame);unsigned activeCRC=crc32(0,activePixels,active->blocks51[activeFrame*4+2]);enemy_cache_frame183(15000);assert(cropBytes51==active->blocks51[activeFrame*4+2]);assert(crc32(0,sprite_crop51(active,activeFrame),cropBytes51)==activeCRC);enemy_cache_frame183(30000);assert(!cropBytes51&&!enemyPackedBytes164);sprite_release_enemies();assert(!cropBytes51&&!enemyPackedBytes164&&!enemyStreamFile51);for(unsigned i=0;i<ENEMY_CROP_SLOTS164;i++)assert(!cropCache51[i].p);puts("PASS approved Guardian poses retain CRC/decompression with bounded raw/packed LRUs, repeated disc seeks avoided and map cleanup complete.");}
