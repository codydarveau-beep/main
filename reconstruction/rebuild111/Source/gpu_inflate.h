/* SPDX-License-Identifier: MIT. Chunked upload avoids a second full atlas. */
static void*gpu_atlas(const unsigned char*src,unsigned packed,unsigned raw,unsigned maxW,unsigned maxH,unsigned*w,unsigned*h){
 if(raw<8)fail("Truncated atlas");unsigned char header[8];z_stream z={0};z.zalloc=asset_zalloc;z.zfree=asset_zfree;z.next_in=(Bytef*)src;z.avail_in=packed;z.next_out=header;z.avail_out=8;
 if(inflateInit(&z)!=Z_OK)fail("Atlas inflater init failed");int result=inflate(&z,Z_NO_FLUSH);
 if(z.total_out!=8||result!=Z_OK)fail("Atlas header decode failed");memcpy(w,header,4);memcpy(h,header+4,4);
 if(!*w||!*h||*w>maxW||*h>maxH||raw!=8+(*w)*(*h)*2)fail("Atlas dimensions invalid");
 unsigned bytes=raw-8,done=0;unsigned char*gpu=gpu_alloc(bytes),*chunk=malloc(65536);if(!chunk)fail("Atlas chunk allocation failed");
 while(result!=Z_STREAM_END){
  unsigned room=bytes-done;if(room>65536)room=65536;if(!room)room=1;
  z.next_out=chunk;z.avail_out=room;result=inflate(&z,Z_NO_FLUSH);unsigned produced=room-z.avail_out;
  if(produced>bytes-done)fail("Atlas expands beyond expected size");if(produced)memcpy(gpu+done,chunk,produced);done+=produced;
  if(result!=Z_OK&&result!=Z_STREAM_END)fail("Atlas body decode failed");
  if(!produced&&result!=Z_STREAM_END)fail("Atlas decode made no progress");
 }
 if(done!=bytes||z.total_out!=raw||z.avail_in)fail("Atlas length mismatch");inflateEnd(&z);free(chunk);return gpu;
}
