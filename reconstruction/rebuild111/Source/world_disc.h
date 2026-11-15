/* MIT. Read one compressed section, validate it, then release it after expansion. */
#ifndef MYRO_WORLD_DISC_H
#define MYRO_WORLD_DISC_H
static unsigned worldDiscReads,worldDiscBytes,worldDiscPeak;
static unsigned char*world_packed_blob45(const WorldBlob*b,unsigned map,unsigned section){
 if(!b->packed||b->offset>WORLD_FILE_BYTES||b->packed>WORLD_FILE_BYTES-b->offset)fail("World section bounds invalid");
 unsigned char*p=malloc(b->packed);if(!p)fail("Insufficient memory for disc read");unsigned done=0;char message[180];
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_WORLD_PATH");if(!path)path="Xbox-Combat-Test-18/Packed/world.bin";
 FILE*f=fopen(path,"rb");if(!f){free(p);fail("Cannot open world.bin (host)");}fseek(f,0,SEEK_END);long size=ftell(f);
 if(size!=WORLD_FILE_BYTES||fseek(f,b->offset,SEEK_SET)){fclose(f);free(p);fail("world.bin size/seek mismatch");}
 while(done<b->packed){unsigned n=b->packed-done;if(n>32768)n=32768;unsigned got=fread(p+done,1,n,f);if(!got){fclose(f);free(p);fail("world.bin host read failed");}done+=got;}fclose(f);
#else
 const char*path="D:\\world.bin";HANDLE f=CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(f==INVALID_HANDLE_VALUE){unsigned err=GetLastError();free(p);snprintf(message,sizeof(message),"Cannot open D: world.bin: error %u. Mount the complete Test18 ISO.",err);fail(message);}
 DWORD high=0,size=GetFileSize(f,&high);SetLastError(0);DWORD at=SetFilePointer(f,b->offset,NULL,FILE_BEGIN);
 if(high||size!=WORLD_FILE_BYTES||at!=b->offset){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"world.bin size/seek failed: map%u part%u offset%u error%u",map,section,b->offset,err);fail(message);}
 while(done<b->packed){DWORD n=b->packed-done,got=0;if(n>32768)n=32768;BOOL ok=ReadFile(f,p+done,n,&got,NULL);if(!ok||!got||got>n){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"world.bin read failed: map%u part%u offset%u request%lu got%lu error%u",map,section,b->offset+done,(unsigned long)n,(unsigned long)got,err);fail(message);}done+=got;}CloseHandle(f);
#endif
 if(crc32(0,p,b->packed)!=b->crc){free(p);snprintf(message,sizeof(message),"world.bin checksum failed: map%u part%u",map,section);fail(message);}
 worldDiscReads++;worldDiscBytes+=b->packed;if(b->packed>worldDiscPeak)worldDiscPeak=b->packed;return p;
}
static unsigned char*world_packed(unsigned map,unsigned section){if(map>=WORLD_MAP_COUNT||section>=7)fail("World section index invalid");return world_packed_blob45(&worldBlobs[map][section],map,section);}
static unsigned char*world_expand(unsigned map,unsigned section,const char*name){const WorldBlob*b=&worldBlobs[map][section];unsigned char*packed=world_packed(map,section);unsigned char*out=inflateasset(name,packed,b->packed,b->raw);free(packed);return out;}
#endif
