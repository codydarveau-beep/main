/* MIT. Original class cues decoded on demand; do not preload unused skills. */
static short*classSoundMemory50[CLASS_SOUND_COUNT50];static unsigned classSoundJob50=~0u,classSoundCopy50=~0u,classSoundBytes50;
static unsigned classSoundAge180[CLASS_SOUND_COUNT50],classSoundClock180;static float classSoundTime180,classSoundUsed180[CLASS_SOUND_COUNT50],classSoundTrimAt180;
static int class_sound_active180(unsigned id){int active=0;EnterCriticalSection(&soundLock);for(unsigned i=0;i<6;i++)if(soundVoices[i].active&&soundVoices[i].id==id)active=1;LeaveCriticalSection(&soundLock);return active;}
static void class_sound_retire180(unsigned index,int force){unsigned id=index+60;if(!classSoundMemory50[index])return;short*old=NULL;EnterCriticalSection(&soundLock);int active=0;for(unsigned i=0;i<6;i++)if(soundVoices[i].active&&soundVoices[i].id==id){active=1;if(force)soundVoices[i].active=0;}if(force||!active){old=classSoundMemory50[index];classSoundMemory50[index]=NULL;soundData[id]=NULL;soundLengths[id]=0;classSoundBytes50-=classSounds50[index].frames*2;}LeaveCriticalSection(&soundLock);free(old);}
static void class_sound_map180(void){for(unsigned i=0;i<CLASS_SOUND_COUNT50;i++)class_sound_retire180(i,1);classSoundTrimAt180=0;}
/* Keep an already playing class cue/song alive through map travel. */
static void class_sound_map_release173(void){for(unsigned i=0;i<CLASS_SOUND_COUNT50;i++)class_sound_retire180(i,0);classSoundTrimAt180=0;}
static void class_sound_prepare50(const Combat*g){
 if(!soundDevice)return;classSoundTime180=g->time;
 if(g->jobId!=classSoundJob50||g->persistent50.copySkill!=classSoundCopy50){class_sound_map180();classSoundJob50=g->jobId;classSoundCopy50=g->persistent50.copySkill;}
 if(g->time<classSoundTrimAt180)return;classSoundTrimAt180=g->time+1;
 for(unsigned i=0;i<CLASS_SOUND_COUNT50;i++)if(classSoundMemory50[i]&&g->time-classSoundUsed180[i]>10)class_sound_retire180(i,0);
}
static void class_sound_play180(unsigned id){
 if(!soundDevice||id<60||id>=SOUND_TOTAL50)return;unsigned index=id-60;classSoundAge180[index]=++classSoundClock180;classSoundUsed180[index]=classSoundTime180;if(classSoundMemory50[index])return;
 const ClassSound50*s=classSounds50+index;unsigned bytes=s->frames*2;if(!bytes||bytes>4u*1024u*1024u||systemBlobs50[s->blob].raw!=bytes)return;
 unsigned budget=bytes>1048576?bytes:1048576;
 while(classSoundBytes50+bytes>budget){int victim=-1;for(unsigned i=0;i<CLASS_SOUND_COUNT50;i++)if(classSoundMemory50[i]&&!class_sound_active180(i+60)&&(victim<0||classSoundAge180[i]<classSoundAge180[victim]))victim=(int)i;if(victim<0)break;class_sound_retire180((unsigned)victim,0);}
 /* Active voices may finish together; never exceed the previous worst class footprint. */
 if(classSoundBytes50+bytes>4u*1024u*1024u)return;
#ifndef MYRO_SOUND_HOST
 MM_STATISTICS memory={0};memory.Length=sizeof(memory);MmQueryStatistics(&memory);if((uint64_t)memory.AvailablePages*4096u<(uint64_t)bytes+systemBlobs50[s->blob].packed+1048576u)return;
#endif
 short*incoming=(short*)system_expand50(s->blob);if(!incoming)return;
 EnterCriticalSection(&soundLock);classSoundMemory50[index]=incoming;soundData[id]=incoming;soundLengths[id]=s->frames;classSoundBytes50+=bytes;LeaveCriticalSection(&soundLock);
}
static void class_sound_song50(const Combat*g){
 static int song;static float next;if(!soundDevice)return;
 const ClassSoundSkill50*data=NULL;for(unsigned i=0;i<sizeof(classSoundSkills50)/sizeof(*classSoundSkills50);i++)if(classSoundSkills50[i].skill==183)data=&classSoundSkills50[i];if(!data)return;unsigned id=data->ids[0];
 if(g->class50.song!=183){if(song){EnterCriticalSection(&soundLock);for(int v=0;v<6;v++)if(soundVoices[v].id==id)soundVoices[v].active=0;LeaveCriticalSection(&soundLock);}song=0;return;}
 /* A lazy cue has no published length until decoded. Use its source length
    for scheduling, including when low memory prevents the optional decode. */
 float duration=classSounds50[id-60].frames/48000.f;
 if(!song){song=183;next=g->time+duration;}else if(g->time>=next){sound_play(id);next=g->time+duration;}
}
