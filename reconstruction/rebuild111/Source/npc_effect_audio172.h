/* MIT. Extra NPC effect cues share the existing2MiB streamed voice cache. */
#include "npc_effect_data172.h"
static unsigned char*npc_effect_audio_read172(unsigned at,unsigned bytes){
 if(at>NPC_FX_BYTES172||bytes>NPC_FX_BYTES172-at||bytes>2097152)return NULL;unsigned char*out=malloc(bytes);if(!out)return NULL;
#ifdef MYRO_SOUND_HOST
 const char*path=getenv("MYRO_NPCFX_PATH");if(!path)path="/workspace/myro/test69/Presentation/npcfx.bin";FILE*f=fopen(path,"rb");int ok=f&&!fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;if(f)fclose(f);
#else
 HANDLE f=CreateFile("D:\\npcfx.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);int ok=f!=INVALID_HANDLE_VALUE;DWORD high=0,done=0;if(ok){ok=GetFileSize(f,&high)==NPC_FX_BYTES172&&!high&&SetFilePointer(f,at,NULL,FILE_BEGIN)==at;while(ok&&done<bytes){DWORD n=bytes-done,got=0;if(n>32768)n=32768;ok=ReadFile(f,out+done,n,&got,NULL)&&got&&got<=n;done+=got;}CloseHandle(f);}
#endif
 if(!ok){free(out);return NULL;}return out;
}
