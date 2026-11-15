#define _POSIX_C_SOURCE 200809L
#define MYRO_HOST 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
typedef struct{unsigned mapId;}Combat;
typedef struct{struct{Combat*game;}player;}NpcGame55;
typedef struct{unsigned Length,AvailablePages;}MM_STATISTICS;
static unsigned pages=4096,allocs,frees,activeBytes,nativeReleases,nativePrepares,nativeDraws,draws;
#define PAGE_READWRITE 1
#define PAGE_WRITECOMBINE 2
static int pb_busy(void){return 0;}
static void MmQueryStatistics(MM_STATISTICS*m){m->AvailablePages=pages;}
static void*MmAllocateContiguousMemoryEx(unsigned bytes,unsigned a,unsigned b,unsigned c,unsigned d){(void)a;(void)b;(void)c;(void)d;assert(bytes==262144&&!activeBytes);void*p=malloc(bytes);assert(p);allocs++;activeBytes=bytes;return p;}
static void MmFreeContiguousMemory(void*p){assert(p&&activeBytes==262144);free(p);activeBytes=0;frees++;}
static unsigned char*npcPortraitTexture171;
static void npc_portrait_release171(void){free(npcPortraitTexture171);npcPortraitTexture171=NULL;nativeReleases++;}
static void npc_portrait_prepare171(NpcGame55*g){(void)g;nativePrepares++;}
static void npc_portrait_draw171(const NpcGame55*g){(void)g;nativeDraws++;}
static int modal=1,status=1;static const char*speaker="Roan";static unsigned expression;
typedef struct{int unused;}Scene200;
static struct{Scene200 scene;}campaignUI200;
#define SC200_LINE 1
static int scene_ui_modal200(void){return modal;}
static int scene_ui_tick200(void){return status;}
static const char*scene_text200(Scene200*s,unsigned field){(void)s;assert(!field);return speaker;}
static unsigned scene_expression200(const Scene200*s){(void)s;return expression;}
static void hud_setup_direct(void*texture,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){assert(texture&&w==256&&h==256&&pitch==1024&&format==0x0001122a&&blend);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){assert(x>=0&&y>=0&&x+w<=640&&y+h<=480&&u==0&&v==0&&uw==256&&vh==256);draws++;}
#include "campaign_portrait_draw200.h"
int main(void){assert(!setenv("MYRO_CAMPAIGN_PORTRAIT_PATH","/workspace/myro/dev200/Campaign/portraits.bin",1));Combat game={0};NpcGame55 npc={0};npc.player.game=&game;npcPortraitTexture171=malloc(1048576);assert(npcPortraitTexture171);campaign_portrait_prepare200(&npc);assert(nativeReleases==1&&!nativePrepares&&allocs==1&&activeBytes==262144);unsigned char*texture=campaignPortraitTexture200;static const char*names[]={"Roan","Yuufa","Judia","Maya"};for(unsigned n=0;n<4;n++)for(unsigned e=0;e<6;e++){speaker=names[n];expression=e;campaign_portrait_prepare200(&npc);int index=campaign_portrait_index200(speaker,e);assert(campaignPortraitLoaded200==index&&campaignPortraitTexture200==texture&&allocs==1);assert(crc32(0,texture,262144)==campaignPortraits200[index].rawCRC);campaign_portrait_draw200(&npc);}assert(draws==24&&campaign_portrait_index200("Roan",99)==campaign_portrait_index200("Roan",0)&&campaign_portrait_index200("Nera",0)==-1);speaker="Nera";campaign_portrait_prepare200(&npc);assert(!campaignPortraitTexture200&&!activeBytes);campaign_portrait_draw200(&npc);assert(!nativeDraws&&draws==24);modal=0;campaign_portrait_prepare200(&npc);campaign_portrait_draw200(&npc);assert(nativePrepares==1&&nativeDraws==1);modal=1;speaker="Roan";expression=0;pages=0;campaign_portrait_prepare200(&npc);assert(!campaignPortraitTexture200&&campaignPortraitFailed200==0);campaign_portrait_draw200(&npc);pages=4096;expression=1;campaign_portrait_prepare200(&npc);assert(campaignPortraitTexture200&&activeBytes==262144);game.mapId=11;campaign_portrait_prepare200(&npc);assert(campaignPortraitTexture200&&activeBytes==262144);status=2;campaign_portrait_prepare200(&npc);assert(!campaignPortraitTexture200&&!activeBytes);status=1;unsigned char bad[16]={0};assert(!campaign_portrait_decode200(100,NULL,NULL,bad,sizeof(bad)));
 FILE*in=fopen("/workspace/myro/dev200/Campaign/portraits.bin","rb"),*out=fopen("/tmp/bad-campaign-portrait200.bin","wb");assert(in&&out);unsigned char buffer[4096];size_t n;while((n=fread(buffer,1,sizeof(buffer),in)))assert(fwrite(buffer,1,n,out)==n);fclose(in);fclose(out);out=fopen("/tmp/bad-campaign-portrait200.bin","r+b");assert(out);fputc(0,out);fclose(out);assert(!setenv("MYRO_CAMPAIGN_PORTRAIT_PATH","/tmp/bad-campaign-portrait200.bin",1));expression=0;campaign_portrait_prepare200(&npc);assert(campaignPortraitLoaded200==-1&&campaignPortraitFailed200==0);unsigned before=draws;campaign_portrait_draw200(&npc);assert(draws==before);campaign_portrait_release200();assert(!activeBytes&&allocs==frees);remove("/tmp/bad-campaign-portrait200.bin");puts("PASS all24 expression textures through bounded disc/decode/draw cache: exact BGRA CRCs, one256KiB texture reused across characters/expressions, original NPC cutin released, neutral fallback, unknown speaker/choice/low-memory hide safely, map/close cleanup and corruption rejection without wrong portrait.");}
