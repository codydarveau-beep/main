#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "appearance_state58.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned bytes){(void)n;unsigned char*out=malloc(bytes);assert(out);uLongf got=bytes;assert(uncompress(out,&got,p,packed)==Z_OK&&got==bytes);return out;}
#include "../Validation/actual_sprite195.inc"
#include "campaign_actor_data200.h"
#include "campaign_companions200.h"
#include "npc_effect_stream172.h"
#include "npc_portrait171.h"
#include "campaign_portrait200.h"
#include "../Validation/portrait_crc195.h"
static int badRead,corrupt;
static int read195(void*ctx,unsigned at,unsigned char*out,unsigned bytes){FILE*f=ctx;if(badRead)return 0;if(fseek(f,at,SEEK_SET)||fread(out,1,bytes,f)!=bytes)return 0;if(corrupt&&bytes)out[bytes/2]^=1;return 1;}
static FILE*open195(const char*dir,const char*name){char path[1024];assert(snprintf(path,sizeof(path),"%s/%s",dir,name)<(int)sizeof(path));FILE*f=fopen(path,"rb");assert(f);return f;}
int main(int argc,char**argv){assert(argc==2);unsigned char*out=malloc(NPC_PORTRAIT_RAW171);assert(out);FILE*f=open195(argv[1],"campaign.bin");
 for(unsigned i=0;i<CAMPAIGN_FRAME_COUNT200;i++){unsigned n=campaignFrames200[i].packed;unsigned char*p=malloc(n);assert(p&&read195(f,campaignFrames200[i].offset,p,n));assert(crc32(0,p,n)==campaignFrames200[i].crc);SparseSprite sprite={0};sprite_load(&sprite,"released campaign pose",p,n,campaignFrames200[i].raw);assert(sprite.w*sprite.h*sprite.bytesPerPixel<=65536);free(sprite.raw);free(p);}
 fclose(f);
 for(unsigned i=0;i<19;i++)assert(campaignCompanions200[i].sceneActor<CAMPAIGN_ACTOR_COUNT200);
 for(unsigned i=0;i<sizeof(campaignActions200)/sizeof(*campaignActions200);i++){assert(campaignActions200[i].count&&campaignActions200[i].first+campaignActions200[i].count<=CAMPAIGN_FRAME_COUNT200);}
 f=open195(argv[1],"npcfx.bin");for(unsigned i=0;i<sizeof(npcFxFrames172)/sizeof(*npcFxFrames172);i++)assert(npc_fx_frame172(i,read195,f,out,65536));
 badRead=1;assert(!npc_fx_frame172(0,read195,f,out,65536));badRead=0;corrupt=1;assert(!npc_fx_frame172(0,read195,f,out,65536));corrupt=0;fclose(f);
 f=open195(argv[1],"portraits.bin");for(unsigned i=0;i<sizeof(npcPortraits171)/sizeof(*npcPortraits171);i++){assert(npc_portrait_index171(npcPortraits171[i].name)==(int)i);assert(npc_portrait_decode171(i,read195,f,out,NPC_PORTRAIT_RAW171));assert(crc32(0,out,NPC_PORTRAIT_RAW171)==portraitRawCRC195[i]);}
 corrupt=1;assert(!npc_portrait_decode171(0,read195,f,out,NPC_PORTRAIT_RAW171));corrupt=0;fclose(f);
 f=open195(argv[1],"storyportraits.bin");for(unsigned i=0;i<sizeof(campaignPortraits200)/sizeof(*campaignPortraits200);i++){assert(campaign_portrait_index200(campaignPortraits200[i].name,campaignPortraits200[i].expression)==(int)i);assert(campaign_portrait_decode200(i,read195,f,out,CAMPAIGN_PORTRAIT_RAW200));}
 badRead=1;assert(!campaign_portrait_decode200(0,read195,f,out,CAMPAIGN_PORTRAIT_RAW200));badRead=0;corrupt=1;assert(!campaign_portrait_decode200(0,read195,f,out,CAMPAIGN_PORTRAIT_RAW200));fclose(f);free(out);
 puts("PASS released actor poses, all roster art mappings, effect frames, NPC portraits, speaker expressions and failed-read/corruption guards through production readers. HOST ONLY.");return 0;}
