/* MIT. Original NPC animation crops: no eager decoded clip or texture allocation. */
#ifndef MYRO_NPC_EFFECT_STREAM172_H
#define MYRO_NPC_EFFECT_STREAM172_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "npc_effect_data172.h"
typedef int(*NpcFxRead172)(void*,unsigned,unsigned char*,unsigned);
static int npc_fx_frame172(unsigned id,NpcFxRead172 read,void*context,unsigned char*out,unsigned bytes){
 if(id>=sizeof(npcFxFrames172)/sizeof(*npcFxFrames172)||!read||!out||bytes!=65536)return 0;const NpcFxFrame172*f=npcFxFrames172+id;
 if(f->x>128||f->y>256||f->w>128-f->x||f->h>256-f->y||f->raw!=f->w*f->h*2||f->raw>65536||f->offset>NPC_FX_BYTES172||f->packed>NPC_FX_BYTES172-f->offset||f->packed>66000||!f->packed)return 0;
 unsigned char*packed=malloc(f->packed),*raw=malloc(f->raw?f->raw:1);if(!packed||!raw){free(packed);free(raw);return 0;}int ok=read(context,f->offset,packed,f->packed)&&crc32(0,packed,f->packed)==f->crc;
 if(ok){z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=packed;z.avail_in=f->packed;z.next_out=raw;z.avail_out=f->raw?f->raw:1;if(inflateInit(&z)!=Z_OK)ok=0;else{ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==f->raw&&!z.avail_in;inflateEnd(&z);}}
 if(ok){memset(out,0,bytes);for(unsigned y=0;y<f->h;y++)memcpy(out+((f->y+y)*128+f->x)*2,raw+y*f->w*2,f->w*2);}free(packed);free(raw);return ok;
}
#endif
