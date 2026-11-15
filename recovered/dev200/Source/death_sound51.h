/* Decode only requested new creature cues; publish and retire under audio lock. */
#include "death_sound_data51.h"
#include "npc_sound_data64.h"
#include "npc_effect_audio172.h"
typedef struct {unsigned id,bytes,age;short*p;unsigned touched183;} DeathSoundCache51;
static DeathSoundCache51 deathCache51[12];static unsigned deathBytes51,deathAge51,deathTime183,deathTrim183;
static void death_sound_prepare51(unsigned id){
 if(id<SOUND_TOTAL50||id>=SOUND_COUNT||!soundDevice)return;for(unsigned i=0;i<12;i++)if(deathCache51[i].id==id&&deathCache51[i].p){deathCache51[i].age=++deathAge51;deathCache51[i].touched183=deathTime183;return;}
 const unsigned*d=id>=SOUND_NPC_FIRST64?npcSounds64[id-SOUND_NPC_FIRST64]:deathSounds51[id-SOUND_TOTAL50];if(!d[2])return;if(d[2]>(id>=SOUND_NPC_FIRST64?2097152u:1048576u))fail("Streamed audio size invalid");
 int slot=-1;
 while(slot<0||deathBytes51+d[2]>2097152){unsigned age=~0u;int victim=-1;for(unsigned i=0;i<12;i++){if(!deathCache51[i].p){if(slot<0)slot=i;}else if(deathCache51[i].age<age){age=deathCache51[i].age;victim=i;}}
  if(slot>=0&&deathBytes51+d[2]<=2097152)break;if(victim<0)fail("Creature audio cache invalid");DeathSoundCache51*c=&deathCache51[victim];
  EnterCriticalSection(&soundLock);for(unsigned v=0;v<6;v++)if(soundVoices[v].id==c->id)soundVoices[v].active=0;soundData[c->id]=NULL;soundLengths[c->id]=0;LeaveCriticalSection(&soundLock);
  deathBytes51-=c->bytes;free(c->p);memset(c,0,sizeof(*c));slot=victim;
 }
 unsigned char*cp=(d[0]&0x80000000u)?npc_effect_audio_read172(d[0]&0x7fffffffu,d[1]):enemy_read51(d[0],d[1]);if(!cp)return;if(crc32(0,cp,d[1])!=d[3]){if(d[0]&0x80000000u){free(cp);return;}fail("Creature audio checksum failed");}short*p=(short*)inflateasset("creature audio",cp,d[1],d[2]);free(cp);
 EnterCriticalSection(&soundLock);soundData[id]=p;soundLengths[id]=d[2]/2;LeaveCriticalSection(&soundLock);deathCache51[slot]=(DeathSoundCache51){id,d[2],++deathAge51,p,deathTime183};deathBytes51+=d[2];
}

/* A previous map's creature/NPC voices do not need to retain decoded PCM. */
static void death_sound_clear180(void){for(unsigned i=0;i<12;i++){DeathSoundCache51*c=deathCache51+i;if(!c->p)continue;EnterCriticalSection(&soundLock);for(unsigned v=0;v<6;v++)if(soundVoices[v].id==c->id)soundVoices[v].active=0;soundData[c->id]=NULL;soundLengths[c->id]=0;LeaveCriticalSection(&soundLock);free(c->p);memset(c,0,sizeof(*c));}deathBytes51=0;}

/* Expire only idle cues; a currently playing voice retains ownership. */
static void death_sound_frame183(unsigned now){deathTime183=now;if((unsigned)(now-deathTrim183)<1000)return;deathTrim183=now;for(unsigned i=0;i<12;i++){DeathSoundCache51*c=deathCache51+i;if(!c->p||(unsigned)(now-c->touched183)<15000)continue;int active=0;EnterCriticalSection(&soundLock);for(unsigned v=0;v<6;v++)if(soundVoices[v].active&&soundVoices[v].id==c->id)active=1;short*old=NULL;if(!active){old=c->p;soundData[c->id]=NULL;soundLengths[c->id]=0;deathBytes51-=c->bytes;memset(c,0,sizeof(*c));}LeaveCriticalSection(&soundLock);free(old);}}
