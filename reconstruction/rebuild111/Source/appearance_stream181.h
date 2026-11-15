/* MIT. On-demand original palettes/portraits; no resident full catalogue. */
#ifndef MYRO_APPEARANCE_STREAM181_H
#define MYRO_APPEARANCE_STREAM181_H
#include "appearance_data58.h"
static void appearance_blob181(const AppearanceBlob181*d,void*out,unsigned bytes){
 if(!d||!d->packed||d->raw!=bytes||bytes>2048)fail("Appearance section bounds invalid");ActorBlob b={0,0,d->offset,d->packed,d->raw,d->crc};unsigned char*packed=actor_blob_packed58(&b,~0u);z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=packed;z.avail_in=d->packed;z.next_out=out;z.avail_out=bytes;if(inflateInit(&z)!=Z_OK){free(packed);fail("Appearance inflater failed");}int result=inflate(&z,Z_FINISH);unsigned count=z.total_out,pending=z.avail_in;inflateEnd(&z);free(packed);if(result!=Z_STREAM_END||count!=bytes||pending)fail("Appearance decode failed");
}
typedef struct{unsigned key,ready;uint16_t palette[256];}ClothCache181;
static ClothCache181 clothCaches181[3];
static const uint16_t*appearance_cloth181(unsigned actor,unsigned sex,unsigned colour,unsigned slot){if(actor>=49||sex>1||!colour||colour>=5||slot>=3)return NULL;const AppearanceBlob181*d=&clothBlobs181[actor][sex][colour];if(!d->packed)return NULL;unsigned key=(actor*2+sex)*5+colour;ClothCache181*c=clothCaches181+slot;if(!c->ready||c->key!=key){appearance_blob181(d,c->palette,512);c->ready=1;c->key=key;}return c->palette;}
#endif
