/* MIT. Actual preference adapter; character save bytes remain untouched. */
#define CreateFile character_CreateFile50b
#define main preceding_disk50_test
#include "test_save_disk50.c"
#undef main
#undef CreateFile
static HANDLE CreateFile(const char*p,DWORD access,DWORD share,void*security,DWORD how,DWORD flags,void*template){(void)share;(void)security;(void)template;assert(!strcmp(p,"E:\\MyROOffline\\settings-a.dat")||!strcmp(p,"E:\\MyROOffline\\settings-b.dat"));assert(access==GENERIC_WRITE&&how==CREATE_ALWAYS&&(flags&FILE_FLAG_WRITE_THROUGH));if(openWriteFail){lastError=ERROR_ACCESS_DENIED;return NULL;}FILE*f=fopen(mapped(p),"wb");lastError=f?0:ERROR_ACCESS_DENIED;return f;}
#include "autosave_xbox50b.h"
int main(void){char tmp[]="/tmp/myro-prefs50b-XXXXXX";assert(mkdtemp(tmp));strcpy(testRoot,tmp);assert(save_disk_init());static Combat game;combat_init(&game,1500,1500,NULL,NULL);SaveStore characters={.read=save_disk_read,.write=save_disk_write};assert(save_commit(&characters,&game));unsigned char original[SAVE_BYTES];assert(save_disk_read(NULL,0,original)==SLOT_RAW);
 Autosave50b p={.read=autosave_disk_read50b,.write=autosave_disk_write50b};autosave_load50b(&p);assert(p.choice==1);
 for(unsigned choice=0;choice<7;choice++){p.choice=choice;assert(autosave_commit50b(&p));Autosave50b reload={.read=autosave_disk_read50b,.write=autosave_disk_write50b};autosave_load50b(&reload);assert(reload.choice==choice);unsigned char current[SAVE_BYTES];assert(save_disk_read(NULL,0,current)==SLOT_RAW&&!memcmp(original,current,SAVE_BYTES));assert(save_disk_read(NULL,1,current)==SLOT_MISSING);}
 unsigned char protected[24];int newest=p.newest;assert(autosave_disk_read50b(NULL,newest,protected)==1);p.choice=0;
 shortWrite=1;assert(!autosave_commit50b(&p));shortWrite=0;Autosave50b recover={.read=autosave_disk_read50b,.write=autosave_disk_write50b};autosave_load50b(&recover);assert(recover.choice==6);openWriteFail=1;assert(!autosave_commit50b(&p));openWriteFail=0;flushFail=1;assert(!autosave_commit50b(&p));flushFail=0;unsigned char check[24];assert(autosave_disk_read50b(NULL,newest,check)==1&&!memcmp(check,protected,24));unsigned char current[SAVE_BYTES];assert(save_disk_read(NULL,0,current)==SLOT_RAW&&!memcmp(original,current,SAVE_BYTES));
 for(int i=0;i<2;i++)assert(!remove(mapped(autosavePaths50b[i])));assert(!remove(mapped(savePaths[0])));assert(!rmdir(mapped("E:\\MyROOffline\\Save50")));assert(!rmdir(mapped("E:\\MyROOffline")));assert(!rmdir(tmp));
 puts("PASS50b real native preference adapter: default/seven choices/Off persist, character files byte-identical,24-byte read-back, previous-copy preservation on short-write/access/flush failure, isolated settings paths.");}
