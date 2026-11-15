/* SPDX-License-Identifier: MIT
 * Original Xbox E: data partition. Only this project's two files are written.
 */
#ifndef MYRO_SAVE_XBOX_H
#define MYRO_SAVE_XBOX_H
#include <nxdk/mount.h>
#include "save_store.h"
#include "npc_save_bridge55.h"
static unsigned saveCharacter56,saveRecord56;
static char savePathBuffers56[2][100];static const char*savePaths[2]={savePathBuffers56[0],savePathBuffers56[1]};
static void save_select56(unsigned character,unsigned record){saveCharacter56=character;saveRecord56=record;for(unsigned i=0;i<2;i++)snprintf(savePathBuffers56[i],100,"E:\\MyROStory200\\Save54_1_0\\c%02u-r%02u-%c.dat",character+1,record,'a'+i);}
static DWORD saveDiskError;
static int save_directory(const char*path){
 if(CreateDirectory(path,NULL))return 1;
 DWORD err=GetLastError(),a=GetFileAttributes(path);
 if(a!=INVALID_FILE_ATTRIBUTES&&(a&FILE_ATTRIBUTE_DIRECTORY))return 1;
 saveDiskError=err;return 0;
}
static int save_disk_init(void){
 if(!nxIsDriveMounted('E')&&!nxMountDrive('E',"\\Device\\Harddisk0\\Partition1\\")){saveDiskError=GetLastError();return 0;}
 save_select56(0,0);return save_directory("E:\\MyROStory200")&&save_directory("E:\\MyROStory200\\Save54_1_0");
}
static int save_disk_read_path(const char*path,unsigned char*out,DWORD wanted){
 HANDLE f=CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(f==INVALID_HANDLE_VALUE){DWORD err=GetLastError();if(err==ERROR_FILE_NOT_FOUND)return SLOT_MISSING;saveDiskError=err;return SLOT_IO;}
 DWORD high=0;SetLastError(ERROR_SUCCESS);DWORD size=GetFileSize(f,&high);DWORD err=GetLastError();
 if(size==INVALID_FILE_SIZE&&err!=ERROR_SUCCESS){saveDiskError=err;CloseHandle(f);return SLOT_IO;}
 if(high||size!=wanted){CloseHandle(f);return SLOT_BAD_SIZE;}
 DWORD got=0;BOOL ok=ReadFile(f,out,wanted,&got,NULL);err=GetLastError();BOOL closed=CloseHandle(f);
 if(!ok||!closed){saveDiskError=ok?GetLastError():err;return SLOT_IO;}
 return got==wanted?SLOT_RAW:SLOT_BAD_SIZE;
}
static NpcVariables55 npcVariables55;
static NpcState55 npcQuests55;
static NpcSaveBridge55 npcSaveBridge55;
static int save_npc_read_blob55(void*context,int slot,unsigned char**out,uint32_t*bytes){
 (void)context;if(slot<0||slot>1)return SLOT_IO;HANDLE file=CreateFile(savePaths[slot],GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(file==INVALID_HANDLE_VALUE){DWORD error=GetLastError();if(error==ERROR_FILE_NOT_FOUND)return SLOT_MISSING;saveDiskError=error;return SLOT_IO;}
 DWORD high=0;SetLastError(0);DWORD size=GetFileSize(file,&high),error=GetLastError();if(size==INVALID_FILE_SIZE&&error){saveDiskError=error;CloseHandle(file);return SLOT_IO;}
 if(high||size<NPC_BUNDLE_HEADER55||size>NPC_BUNDLE_LIMIT55){CloseHandle(file);return SLOT_BAD_SIZE;}
 unsigned char*data=malloc(size);if(!data){CloseHandle(file);saveDiskError=ERROR_NOT_ENOUGH_MEMORY;return SLOT_IO;}DWORD done=0;
 while(done<size){DWORD n=size-done;if(n>65536)n=65536;DWORD got=0;if(!ReadFile(file,data+done,n,&got,NULL)||!got||got>n){saveDiskError=GetLastError();CloseHandle(file);free(data);return SLOT_IO;}done+=got;}
 if(!CloseHandle(file)){saveDiskError=GetLastError();free(data);return SLOT_IO;}*out=data;*bytes=size;return SLOT_RAW;
}
static int save_npc_write_blob55(void*context,int slot,const unsigned char*data,uint32_t bytes){
 (void)context;if(slot<0||slot>1||!data||bytes<NPC_BUNDLE_HEADER55||bytes>NPC_BUNDLE_LIMIT55)return 0;HANDLE file=CreateFile(savePaths[slot],GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH,NULL);if(file==INVALID_HANDLE_VALUE){saveDiskError=GetLastError();return 0;}
 DWORD done=0,error=0;BOOL ok=TRUE;while(done<bytes){DWORD n=bytes-done;if(n>65536)n=65536;DWORD wrote=0;if(!WriteFile(file,data+done,n,&wrote,NULL)||wrote!=n){error=GetLastError();if(!error)error=ERROR_WRITE_FAULT;ok=FALSE;break;}done+=wrote;}
 if(ok){IO_STATUS_BLOCK io;NTSTATUS status=NtFlushBuffersFile(file,&io);if(status==STATUS_PENDING){status=NtWaitForSingleObject(file,FALSE,NULL);if(status>=0)status=io.Status;}if(status<0){ok=FALSE;error=RtlNtStatusToDosError(status);}}
 BOOL closed=CloseHandle(file);if(!ok||!closed){saveDiskError=ok?GetLastError():error;return 0;}return 1;
}
static void save_npc_setup55(SaveStore*store){npcSaveBridge55.variables=&npcVariables55;npcSaveBridge55.quests=&npcQuests55;npcSaveBridge55.read=save_npc_read_blob55;npcSaveBridge55.write=save_npc_write_blob55;store->ctx=&npcSaveBridge55;store->read=npc_save_read55;store->write=npc_save_write55;store->extensionLoaded=npc_save_loaded55;store->extensionClean=npc_save_clean55;store->extensionDirty=npc_save_dirty55;store->extensionCanSave=npc_save_can_save55;}
static void save_disk_feedback(SaveStore*s,int failed){
 if(failed&&saveDiskError){char text[100];memcpy(text,s->status,sizeof(text));text[99]=0;
  snprintf(s->status,sizeof(s->status),"%.35s [HDD error %lu]",text,(unsigned long)saveDiskError);
  if(s->operationResult58<0)snprintf(s->errorDetail58,sizeof(s->errorDetail58),"%s",s->status);
 }
}
#endif
