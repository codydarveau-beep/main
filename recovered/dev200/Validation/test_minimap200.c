#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <zlib.h>
#include "world_data.h"
static unsigned surfaceMap,allocations;
static int pb_busy(void){return 0;}
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(2);}
static void*gpu_alloc(unsigned n){assert(n==65536);allocations++;void*p=malloc(n);assert(p);return p;}
static unsigned char*inflateasset(const char*s,const unsigned char*cp,unsigned packed,unsigned raw){(void)s;unsigned char*p=malloc(raw);assert(p);unsigned long n=raw;assert(uncompress(p,&n,cp,packed)==Z_OK&&n==raw);return p;}
#include "minimap_upload.h"
int main(void){for(unsigned map=0;map<WORLD_MAP_COUNT;map++){surfaceMap=map;minimap_upload();assert(minimapLoaded200==map);assert(allocations==1);uint32_t crc=0;for(unsigned y=0;y<108;y++){crc=crc32(crc,(unsigned char*)minimapTexture200+y*512,288);for(unsigned x=0;x<144;x++)assert(((uint16_t*)minimapTexture200)[y*256+x]&0x8000);for(unsigned x=144;x<256;x++)assert(!((uint16_t*)minimapTexture200)[y*256+x]);}assert(crc==minimapBlobs200[map].crc);}assert(minimapReads200==494);free(minimapTexture200);puts("PASS all494 native-large map loads: size/decompression/CRC, opaque 144x108 pixels, pitch/padding, exactly one reusable64KiB GPU allocation.");}
