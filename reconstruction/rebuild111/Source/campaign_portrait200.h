/* MIT. Disc-only expression lookup/decode; caller retains just one BGRA texture. */
#ifndef MYRO_CAMPAIGN_PORTRAIT200_H
#define MYRO_CAMPAIGN_PORTRAIT200_H
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "campaign_portrait_data200.h"
static int campaign_portrait_index200(const char*speaker,unsigned expression){if(!speaker)return-1;int neutral=-1;for(unsigned i=0;i<sizeof(campaignPortraits200)/sizeof(*campaignPortraits200);i++){if(strcmp(speaker,campaignPortraits200[i].name))continue;if(campaignPortraits200[i].expression==expression)return(int)i;if(!campaignPortraits200[i].expression)neutral=(int)i;}return neutral;}
typedef int(*CampaignPortraitRead200)(void*,unsigned,unsigned char*,unsigned);
static int campaign_portrait_decode200(unsigned index,CampaignPortraitRead200 read,void*context,unsigned char*out,unsigned bytes){if(index>=sizeof(campaignPortraits200)/sizeof(*campaignPortraits200)||!read||!out||bytes!=CAMPAIGN_PORTRAIT_RAW200)return 0;unsigned at=campaignPortraits200[index].offset,n=campaignPortraits200[index].packed;if(!n||n>CAMPAIGN_PORTRAIT_RAW200||at>CAMPAIGN_PORTRAIT_FILE_BYTES200||n>CAMPAIGN_PORTRAIT_FILE_BYTES200-at)return 0;unsigned char*cp=malloc(n);if(!cp)return 0;int ok=read(context,at,cp,n)&&crc32(0,cp,n)==campaignPortraits200[index].crc;if(ok){z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=cp;z.avail_in=n;z.next_out=out;z.avail_out=bytes;if(inflateInit(&z)!=Z_OK)ok=0;else{ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==bytes&&!z.avail_in;inflateEnd(&z);}if(ok)ok=crc32(0,out,bytes)==campaignPortraits200[index].rawCRC;}free(cp);return ok;}
#endif
