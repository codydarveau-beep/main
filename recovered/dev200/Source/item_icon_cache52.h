/* MIT. Stream icons into protected empty texels of the existing HUD atlas.
 * No extra GPU texture, no per-frame allocation, no overwriting live UV slots. */
#include "item_icon_pack52.h"
#include "item_icon_slots52.h"
typedef struct {int code;unsigned frame;} ItemIconEntry52;
static ItemIconEntry52 itemIconEntries52[ITEM_ICON_SLOTS52];static unsigned itemIconFrame52;
static FILE*itemIconFile52;
static void item_icon_begin52(void){if(!++itemIconFrame52){itemIconFrame52=1;memset(itemIconEntries52,0,sizeof(itemIconEntries52));}}
static int item_icon_open52(void){if(itemIconFile52)return 1;
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_ITEM_ICONS52");if(!path)path="../Items/icons.bin";
#else
 const char*path="D:\\itemicons.bin";
#endif
 itemIconFile52=fopen(path,"rb");if(!itemIconFile52)return 0;unsigned char header[32];if(fseek(itemIconFile52,0,SEEK_END)||ftell(itemIconFile52)!=ITEM_ICON_FILE_BYTES52||fseek(itemIconFile52,0,SEEK_SET)||fread(header,1,32,itemIconFile52)!=32||memcmp(header,"MYROIC52",8)){fclose(itemIconFile52);itemIconFile52=NULL;return 0;}return 1;}
static unsigned item_icon_u32_52(const unsigned char*p){return(unsigned)p[0]|(unsigned)p[1]<<8|(unsigned)p[2]<<16|(unsigned)p[3]<<24;}
static const unsigned short*item_icon_rect52(int code){int ordinal=(code-ITEM_ICON_BASE52)/2,dim=(code-ITEM_ICON_BASE52)&1;if(code<ITEM_ICON_BASE52||ordinal<255||ordinal>=ITEM_COUNT)return NULL;if(!itemIconFrame52)item_icon_begin52();unsigned oldest=0;
 for(unsigned i=0;i<ITEM_ICON_SLOTS52;i++){ItemIconEntry52*p=itemIconEntries52+i;if(p->code==code){p->frame=itemIconFrame52;return itemIconSlots52[i];}if(p->frame<itemIconEntries52[oldest].frame)oldest=i;}
 if(itemIconEntries52[oldest].frame==itemIconFrame52||!item_icon_open52())return NULL;unsigned char entry[8];if(fseek(itemIconFile52,64+ordinal*8,SEEK_SET)||fread(entry,1,8,itemIconFile52)!=8)return NULL;unsigned offset=item_icon_u32_52(entry),size=item_icon_u32_52(entry+4);if(!size)return NULL;if(size>2048||offset<64+ITEM_COUNT*8||offset>ITEM_ICON_FILE_BYTES52||size>ITEM_ICON_FILE_BYTES52-offset)return NULL;
 unsigned char packed[2048],raw[1600];if(fseek(itemIconFile52,offset,SEEK_SET)||fread(packed,1,size,itemIconFile52)!=size)return NULL;
 z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=packed;z.avail_in=size;z.next_out=raw;z.avail_out=sizeof(raw);if(inflateInit(&z)!=Z_OK)return NULL;int result=inflate(&z,Z_FINISH);unsigned bytes=z.total_out;inflateEnd(&z);if(result!=Z_STREAM_END||bytes!=sizeof(raw))return NULL;
#ifndef MYRO_HOST
 while(pb_busy()){}
#endif
 const unsigned short*r=itemIconSlots52[oldest];unsigned char*texture=skinTexture;for(int y=-1;y<=20;y++)memset(texture+((r[1]+y)*512+r[0]-1)*4,0,22*4);
 if(dim)for(unsigned i=3;i<sizeof(raw);i+=4)raw[i]=(raw[i]+1)/2;
 for(unsigned y=0;y<20;y++)memcpy(texture+((r[1]+y)*512+r[0])*4,raw+y*80,80);__sync_synchronize();itemIconEntries52[oldest]=(ItemIconEntry52){code,itemIconFrame52};return r;}
