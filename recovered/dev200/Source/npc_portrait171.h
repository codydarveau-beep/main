/* MIT. Optional original cutin art: catalog-only lookup and bounded disc decode. */
#ifndef MYRO_NPC_PORTRAIT171_H
#define MYRO_NPC_PORTRAIT171_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zlib.h>
#include "npc_portrait_data171.h"
static int npc_portrait_index171(const char*input){char name[128];size_t n=input?strlen(input):0;if(!n||n>=sizeof(name))return-1;for(size_t i=0;i<=n;i++){unsigned c=(unsigned char)input[i];name[i]=(char)(c>='A'&&c<='Z'?c+32:c);}if(n>4&&!strcmp(name+n-4,".bmp"))name[n-=4]=0;
 /* Original hair scripts use both padded and unpadded numeric filenames. */
 if(!strncmp(name,"hair_m_",7)||!strncmp(name,"hair_f_",7)){char*end;unsigned long style=strtoul(name+7,&end,10);if(*end==0&&end!=name+7&&style>=1&&style<=27){char sex=name[5];snprintf(name,sizeof(name),"hair_%c_%02lu",sex,style);}}
 unsigned a=0,b=sizeof(npcPortraits171)/sizeof(*npcPortraits171);while(a<b){unsigned mid=a+(b-a)/2;int c=strcmp(name,npcPortraits171[mid].name);if(c==0)return(int)mid;if(c<0)b=mid;else a=mid+1;}return-1;}
typedef int(*NpcPortraitRead171)(void*,unsigned,unsigned char*,unsigned);
static int npc_portrait_decode171(unsigned index,NpcPortraitRead171 read,void*ctx,unsigned char*out,unsigned bytes){if(index>=sizeof(npcPortraits171)/sizeof(*npcPortraits171)||!read||!out||bytes!=NPC_PORTRAIT_RAW171)return 0;unsigned at=npcPortraits171[index].offset,n=npcPortraits171[index].packed;if(!n||n>NPC_PORTRAIT_RAW171||at>NPC_PORTRAIT_FILE_BYTES171||n>NPC_PORTRAIT_FILE_BYTES171-at)return 0;unsigned char*cp=malloc(n);if(!cp)return 0;int ok=read(ctx,at,cp,n)&&crc32(0,cp,n)==npcPortraits171[index].crc;if(ok){z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=cp;z.avail_in=n;z.next_out=out;z.avail_out=bytes;if(inflateInit(&z)!=Z_OK)ok=0;else{int result=inflate(&z,Z_FINISH);ok=result==Z_STREAM_END&&z.total_out==bytes&&!z.avail_in;inflateEnd(&z);}}free(cp);return ok;}
static int npc_portrait_rect171(unsigned index,unsigned position,float out[4]){if(index>=sizeof(npcPortraits171)/sizeof(*npcPortraits171)||position>4)return 0;float w=npcPortraits171[index].width,h=npcPortraits171[index].height;out[0]=position==0?0:position==2?640-w:(640-w)*.5f;out[1]=position>=3?(480-h)*.5f:480-h;out[2]=w;out[3]=h;return 1;}
#endif
