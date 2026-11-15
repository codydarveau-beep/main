/* MIT. Fixed-memory, exact-length/CRC-checked world-section decompression. */
#ifndef MYRO_WORLD_STREAM171_H
#define MYRO_WORLD_STREAM171_H
#define WORLD_STREAM_IN171 32768u
#define WORLD_STREAM_OUT171 65536u
typedef int(*WorldRead171)(void*,unsigned,unsigned char*,unsigned);
typedef int(*WorldSink171)(void*,unsigned,unsigned char*,unsigned);
static int world_stream171(const WorldBlob*b,WorldRead171 read,void*readContext,WorldSink171 sink,void*sinkContext){if(!b||!read||!sink||!b->packed||!b->raw||b->offset>WORLD_FILE_BYTES||b->packed>WORLD_FILE_BYTES-b->offset)return 0;unsigned char*memory=malloc(WORLD_STREAM_IN171+WORLD_STREAM_OUT171);if(!memory)return 0;unsigned char*input=memory,*output=memory+WORLD_STREAM_IN171;unsigned fetched=0,written=0,crc=crc32(0,NULL,0);z_stream z={0};z.zalloc=asset_zalloc;z.zfree=asset_zfree;int result=inflateInit(&z),ok=result==Z_OK;if(!ok){free(memory);return 0;}
 unsigned pending=0;
 while(ok){if(!z.avail_in&&fetched<b->packed){unsigned n=b->packed-fetched;if(n>WORLD_STREAM_IN171)n=WORLD_STREAM_IN171;if(!read(readContext,b->offset+fetched,input,n)){ok=0;break;}crc=crc32(crc,input,n);fetched+=n;z.next_in=input;z.avail_in=n;}z.next_out=output+pending;z.avail_out=WORLD_STREAM_OUT171-pending;unsigned before=z.avail_in,room=z.avail_out;result=inflate(&z,Z_NO_FLUSH);unsigned produced=room-z.avail_out;pending+=produced;if(pending>b->raw-written){ok=0;break;}if(pending==WORLD_STREAM_OUT171||result==Z_STREAM_END){if(pending&&!sink(sinkContext,written,output,pending)){ok=0;break;}written+=pending;pending=0;}if(result==Z_STREAM_END)break;if(result!=Z_OK||(!produced&&before==z.avail_in)){ok=0;break;}}

 ok=ok&&result==Z_STREAM_END&&written==b->raw&&fetched==b->packed&&!z.avail_in&&crc==b->crc;inflateEnd(&z);free(memory);return ok;}
#endif
