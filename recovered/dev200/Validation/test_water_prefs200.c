#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "combat.h"
#include "pause_ui.h"
#include "autosave50b.h"
#include "controller_nav61.h"
#include "sound_mix.h"
static int musicMuted,soundMuted,musicVolume=50,soundVolume=100,soundLock;
static unsigned menuSoundEnabled58=1,menuSoundActive58;
static SoundVoice soundVoices[6];
static void EnterCriticalSection(int*p){(void)p;}static void LeaveCriticalSection(int*p){(void)p;}
#include "water_mode190.h"
#include "quest_journal65.h"
#include "pause_settings61.h"
#include "prefs_format61.h"
static Combat game;static Autosave50b autosave={.choice=1};
static int input(PauseUI*u,unsigned p){if(!u->editing61)u->value61=pause_value61(&game,&autosave,u->tab,u->row);int action=pause_input(u,p);if(action==PA_OPTION_PREVIEW61||action==PA_OPTION_CANCEL61)pause_set61(&game,&autosave,u->tab,u->row,u->value61);return action;}
typedef int HANDLE;typedef uint32_t DWORD;
#define INVALID_HANDLE_VALUE (-1)
#define GENERIC_READ 1
#define GENERIC_WRITE 2
#define FILE_SHARE_READ 0
#define OPEN_EXISTING 0
#define CREATE_ALWAYS 1
#define FILE_ATTRIBUTE_NORMAL 0
#define FILE_FLAG_WRITE_THROUGH 0
static struct{unsigned char data[256];unsigned size,exists;}files61[2];static unsigned brokenWrite61;
static HANDLE CreateFile(const char*path,unsigned access,unsigned share,void*security,unsigned create,unsigned flags,void*unused){(void)access;(void)share;(void)security;(void)flags;(void)unused;unsigned slot=strstr(path,"preferences-b")?1:0;if(!create&&!files61[slot].exists)return INVALID_HANDLE_VALUE;if(create){files61[slot].exists=1;files61[slot].size=0;}return slot;}
static DWORD GetFileSize(HANDLE h,DWORD*high){*high=0;return files61[h].size;}
static int ReadFile(HANDLE h,void*out,DWORD bytes,DWORD*read,void*unused){(void)unused;if(bytes>files61[h].size)return 0;memcpy(out,files61[h].data,bytes);*read=bytes;return 1;}
static int WriteFile(HANDLE h,const void*in,DWORD bytes,DWORD*wrote,void*unused){(void)unused;if(brokenWrite61||bytes>sizeof(files61[h].data))return 0;memcpy(files61[h].data,in,bytes);files61[h].size=bytes;*wrote=bytes;return 1;}
static int CloseHandle(HANDLE h){(void)h;return 1;}
#include "frontend_prefs56.h"
int main(void){
 assert(!waterOriginal190&&!waterAnimation200);assert(pause_count(P53_VIDEO)==9&&pause_count(P53_TESTING)==5);
 PauseUI u={.tab=P53_TESTING,.row=3,.inside=1,.allowTesting58=1};
 input(&u,2);input(&u,8192);assert(waterOriginal190);assert(input(&u,4)==PA_OPTION_CANCEL61&&!waterOriginal190);
 input(&u,2);input(&u,8192);assert(input(&u,2)==PA_PREFS_SAVE58&&waterOriginal190);
 u.row=4;input(&u,2);for(unsigned i=0;i<12;i++)input(&u,8192);assert(waterAnimation200==8);input(&u,4);assert(!waterAnimation200);
 for(unsigned setting=0;setting<9;setting++){
  input(&u,2);for(unsigned i=0;i<12;i++)input(&u,4096);assert(!waterAnimation200);for(unsigned i=0;i<setting;i++)input(&u,8192);
  assert(input(&u,2)==PA_PREFS_SAVE58&&waterAnimation200==setting);assert(prefs_save56());
  waterAnimation200=99;waterOriginal190=0;prefsNewest56=-1;prefsSequence56=0;prefs_load56();assert(waterAnimation200==setting&&waterOriginal190);
 }
 uint32_t r[PREFS_WORDS61];assert(prefs_read56((unsigned)prefsNewest56,r)&&r[1]==11);
 for(unsigned i=9;i<16;i++){r[5]=64|(i<<7);r[32]=crc32(0,(unsigned char*)r,128);assert(!prefs_valid61(r,132));}
 r[1]=10;r[5]=64;r[2]=99;r[32]=crc32(0,(unsigned char*)r,128);assert(prefs_valid61(r,132));
 memset(files61,0,sizeof(files61));memcpy(files61[0].data,r,132);files61[0].size=132;files61[0].exists=1;prefsNewest56=-1;prefsSequence56=0;prefs_load56();assert(waterOriginal190&&!waterAnimation200);
 r[5]|=128;r[32]=crc32(0,(unsigned char*)r,128);assert(!prefs_valid61(r,132));
 u=(PauseUI){.tab=P53_TESTING,.allowTesting58=0,.inside=1};input(&u,2);assert(u.tab!=P53_TESTING);
 brokenWrite61=1;unsigned accepted=prefsSequence56;assert(!prefs_save56()&&prefsSequence56==accepted);
 puts("PASS Testing water toggle/frame slider preview/cancel/commit, 9 settings global preference roundtrip, old preferences default FULL, invalid settings rejected, developer-only access and failed-write preservation.");
}
