#ifndef MYRO_NPC_AUDIO64_H
#define MYRO_NPC_AUDIO64_H
#include "npc_sound_names64.h"
#define NPC_AUDIO_QUEUE64 32u
#define NPC_AUDIO_LOOPS64 8u
typedef struct{unsigned active,map,owner,clip,delay;uint64_t next;}NpcAudioLoop64;
typedef struct{unsigned map,count,clips[NPC_AUDIO_QUEUE64];NpcAudioLoop64 loops[NPC_AUDIO_LOOPS64];}NpcAudio64;
static int npc_audio_index64(const char*name){char key[160];unsigned n=0;for(;*name;name++){unsigned char c=(unsigned char)*name;if(c=='/'||c=='\\'){if(n&&key[n-1]=='\\')continue;c='\\';}if(c>='A'&&c<='Z')c+=32;if(n+1>=sizeof(key))return-1;key[n++]=(char)c;}key[n]=0;for(unsigned i=0;i<NPC_SOUND_COUNT64;i++)if(!strcmp(key,npcSoundNames64[i].name))return(int)i;return-1;}
static int npc_audio_queue64(NpcAudio64*a,unsigned clip){if(clip>=NPC_SOUND_COUNT64||a->count>=NPC_AUDIO_QUEUE64)return 0;a->clips[a->count++]=clip;return 1;}
static int npc_audio_pop64(NpcAudio64*a,unsigned*clip){if(!a->count)return 0;*clip=a->clips[0];a->count--;memmove(a->clips,a->clips+1,a->count*sizeof(*a->clips));return 1;}
static void npc_audio_tick64(NpcAudio64*a,unsigned map,uint64_t ms){if(a->map!=map){memset(a,0,sizeof(*a));a->map=map;}for(unsigned i=0;i<NPC_AUDIO_LOOPS64;i++){NpcAudioLoop64*l=a->loops+i;if(l->active&&ms>=l->next&&npc_audio_queue64(a,l->clip))l->next=ms+npcSoundNames64[l->clip].duration+l->delay;}}
static int npc_audio_request64(NpcAudio64*a,unsigned map,unsigned owner,unsigned clip,unsigned type,unsigned delay,uint64_t ms){if(clip>=NPC_SOUND_COUNT64||type>2)return 0;npc_audio_tick64(a,map,ms);int slot=-1;for(unsigned i=0;i<NPC_AUDIO_LOOPS64;i++){NpcAudioLoop64*l=a->loops+i;if(l->active&&l->owner==owner&&l->clip==clip){slot=(int)i;break;}if(!l->active&&slot<0)slot=(int)i;}if(type==2){for(unsigned i=0;i<NPC_AUDIO_LOOPS64;i++)if(a->loops[i].active&&a->loops[i].owner==owner&&a->loops[i].clip==clip)a->loops[i].active=0;return 1;}if(type==1&&slot<0)return 0;if(!npc_audio_queue64(a,clip))return 0;if(type==1)a->loops[slot]=(NpcAudioLoop64){1,map,owner,clip,delay,ms+npcSoundNames64[clip].duration+delay};return 1;}
#endif
