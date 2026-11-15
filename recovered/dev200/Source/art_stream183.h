/* MIT. Original effect frames streamed independently, keeping whole animations
 * on disk. Metadata <=256KiB, raw crops <=512KiB, packed crops <=256KiB. */
#include "art_stream_data183.h"
#define ART_RAW_BYTES183 (512u*1024u)
#define ART_PACKED_BYTES183 (256u*1024u)
#define ART_FRAME_SLOTS183 64u
#define ART_PACKED_SLOTS183 256u
typedef struct{unsigned offset,bytes,crc,used,touched;unsigned char*data;}ArtFrameCache183;
static ArtFrameCache183 artRaw183[ART_FRAME_SLOTS183],artPacked183[ART_PACKED_SLOTS183];
static unsigned artRawBytes183,artPackedBytes183,artStreamClock183,artStreamTime183,artStreamReads183,artStreamDecodes183;
static FILE*artStreamFile183;
static void art_stream_read183(unsigned at,unsigned n,unsigned char*out){
 if(!n||at>ART_FILE_BYTES45||n>ART_FILE_BYTES45-at)fail("Effect stream bounds invalid");
 if(!artStreamFile183){
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_EFFECT_PATH");if(!path)path="../Effects/effects.bin";
#else
 const char*path="D:\\effects.bin";
#endif
 artStreamFile183=fopen(path,"rb");if(!artStreamFile183||fseek(artStreamFile183,0,SEEK_END)||ftell(artStreamFile183)!=ART_FILE_BYTES45)fail("Effect stream file missing or incorrect");}
 if(fseek(artStreamFile183,at,SEEK_SET)||fread(out,1,n,artStreamFile183)!=n)fail("Effect frame read failed");artStreamReads183++;
}
static unsigned char*art_stream_inflate183(const unsigned char*cp,unsigned packed,unsigned raw){
 unsigned char*out=malloc(raw?raw:1);if(!out)fail("Effect frame allocation failed");z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=(unsigned char*)cp;z.avail_in=packed;z.next_out=out;z.avail_out=raw?raw:1;int ok=inflateInit(&z)==Z_OK;if(ok){ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==raw&&!z.avail_in;inflateEnd(&z);}if(!ok){free(out);fail("Effect frame inflation invalid");}artStreamDecodes183++;return out;
}
static void art_stream_load183(unsigned clip){
 const ArtStream183*b=artStreams183+clip;if(b->raw>262144||b->raw<32||!b->packed||b->packed>b->raw+1024)fail("Effect metadata bounds invalid");unsigned char*cp=malloc(b->packed);if(!cp)fail("Effect metadata read allocation failed");art_stream_read183(b->offset,b->packed,cp);if(crc32(0,cp,b->packed)!=b->crc)fail("Effect metadata checksum invalid");unsigned char*raw=art_stream_inflate183(cp,b->packed,b->raw);free(cp);
 SparseSprite*s=art39Sprites+clip;memset(s,0,sizeof(*s));memcpy(s,raw,32);s->bytesPerPixel=2;s->alpha4444=(s->pixelBytes>>30)&1;s->pixelBytes&=0x3fffffffu;
 if(s->w!=128||(s->h!=128&&s->h!=256)||!s->actions||s->actions>256||!s->frames||s->frames>8192||s->sequenceCount>65536||s->anchorX>s->w||s->anchorY>s->h||32+s->actions*12+s->sequenceCount*4+s->frames*36!=b->raw)fail("Effect metadata layout invalid");
 s->raw=raw;s->meta=(unsigned*)(raw+32);s->sequence=s->meta+s->actions*3;s->directory=s->sequence+s->sequenceCount;s->blocks51=s->directory+s->frames*5;
 for(unsigned i=0;i<s->actions;i++){const unsigned*a=s->meta+i*3;if(a[0]>s->sequenceCount||!a[1]||a[1]>s->sequenceCount-a[0]||!a[2])fail("Effect action invalid");}
 for(unsigned i=0;i<s->sequenceCount;i++)if(s->sequence[i]>=s->frames)fail("Effect frame sequence invalid");
 for(unsigned i=0;i<s->frames;i++){const unsigned*d=s->directory+i*5,*f=s->blocks51+i*4;if(d[0]>s->w||d[1]>s->h||d[2]>s->w-d[0]||d[3]>s->h-d[1]||f[2]!=d[2]*d[3]*2||d[4]>s->pixelBytes||f[2]>s->pixelBytes-d[4]||f[2]>65536||!f[1]||f[1]>f[2]+1024||f[0]>ART_FILE_BYTES45||f[1]>ART_FILE_BYTES45-f[0])fail("Effect crop metadata invalid");}
}
static void art_frame_retire183(ArtFrameCache183*c,unsigned*bytes){*bytes-=c->bytes;free(c->data);memset(c,0,sizeof(*c));}
static int art_frame_slot183(ArtFrameCache183*bank,unsigned count,unsigned*bytes,unsigned size,unsigned limit){int slot=-1;while(slot<0||*bytes+size>limit){int victim=-1;for(unsigned i=0;i<count;i++)if(!bank[i].data){if(slot<0)slot=(int)i;}else if(victim<0||bank[i].used<bank[victim].used)victim=(int)i;if(slot>=0&&*bytes+size<=limit)break;if(victim<0)fail("Effect crop cache accounting invalid");art_frame_retire183(bank+victim,bytes);slot=victim;}return slot;}
static unsigned char*art_stream_crop183(unsigned clip,unsigned frame){
 SparseSprite*s=art39Sprites+clip;const unsigned*f=s->blocks51+frame*4;unsigned tick=++artStreamClock183;
 for(unsigned i=0;i<ART_FRAME_SLOTS183;i++)if(artRaw183[i].data&&artRaw183[i].offset==f[0]&&artRaw183[i].crc==f[3]){artRaw183[i].used=tick;artRaw183[i].touched=artStreamTime183;return artRaw183[i].data;}
 unsigned char*packed=NULL;for(unsigned i=0;i<ART_PACKED_SLOTS183;i++)if(artPacked183[i].data&&artPacked183[i].offset==f[0]&&artPacked183[i].crc==f[3]){artPacked183[i].used=tick;artPacked183[i].touched=artStreamTime183;packed=artPacked183[i].data;break;}
 if(!packed){int slot=art_frame_slot183(artPacked183,ART_PACKED_SLOTS183,&artPackedBytes183,f[1],ART_PACKED_BYTES183);packed=malloc(f[1]);if(!packed)fail("Packed effect allocation failed");art_stream_read183(f[0],f[1],packed);if(crc32(0,packed,f[1])!=f[3])fail("Effect crop checksum invalid");artPacked183[slot]=(ArtFrameCache183){f[0],f[1],f[3],tick,artStreamTime183,packed};artPackedBytes183+=f[1];}
 int slot=art_frame_slot183(artRaw183,ART_FRAME_SLOTS183,&artRawBytes183,f[2],ART_RAW_BYTES183);unsigned char*raw=art_stream_inflate183(packed,f[1],f[2]);artRaw183[slot]=(ArtFrameCache183){f[0],f[2],f[3],tick,artStreamTime183,raw};artRawBytes183+=f[2];return raw;
}
static void art_stream_frame183(unsigned now){artStreamTime183=now;for(unsigned i=0;i<ART_PACKED_SLOTS183;i++){if(i<ART_FRAME_SLOTS183&&artRaw183[i].data&&(unsigned)(now-artRaw183[i].touched)>=15000)art_frame_retire183(artRaw183+i,&artRawBytes183);if(artPacked183[i].data&&(unsigned)(now-artPacked183[i].touched)>=15000)art_frame_retire183(artPacked183+i,&artPackedBytes183);}}
static void art_stream_clear183(void){for(unsigned i=0;i<ART_PACKED_SLOTS183;i++){if(i<ART_FRAME_SLOTS183&&artRaw183[i].data)art_frame_retire183(artRaw183+i,&artRawBytes183);if(artPacked183[i].data)art_frame_retire183(artPacked183+i,&artPackedBytes183);}if(artStreamFile183){fclose(artStreamFile183);artStreamFile183=NULL;}artStreamClock183=0;}
