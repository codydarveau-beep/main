/* New eight-view cabinet sprites: fixed world facing, streamed current pose. */
#ifndef MYRO_GUILD_VIEW197_H
#define MYRO_GUILD_VIEW197_H
#include "guild_views_data197.h"
typedef int(*GuildViewRead197)(void*,unsigned,unsigned char*,unsigned);
static unsigned guild_view_direction197(float camera,float front){if(!isfinite(camera)||!isfinite(front))return 0;float turn=fmodf(camera-front,6.28318530718f);if(turn<0)turn+=6.28318530718f;return(unsigned)floorf(turn/.785398163397f+.5f)&7u;}
static int guild_view_decode197(unsigned game,unsigned view,GuildViewRead197 read,void*ctx,unsigned char*out,unsigned bytes){if(game>=6||view>=8||!read||!out||bytes!=GUILD_VIEW_RAW197)return 0;unsigned i=game*8+view,at=guildViews197[i].offset,n=guildViews197[i].packed;if(!n||n>GUILD_VIEW_RAW197+128||at>GUILD_VIEWS_BYTES197||n>GUILD_VIEWS_BYTES197-at)return 0;unsigned char*packed=malloc(n);if(!packed)return 0;int ok=read(ctx,at,packed,n)&&crc32(0,packed,n)==guildViews197[i].crc;if(ok){z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=packed;z.avail_in=n;z.next_out=out;z.avail_out=bytes;if(inflateInit(&z)!=Z_OK)ok=0;else{ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==bytes&&!z.avail_in;inflateEnd(&z);}if(ok)ok=crc32(0,out,bytes)==guildViews197[i].rawCRC;}free(packed);return ok;}
#endif
