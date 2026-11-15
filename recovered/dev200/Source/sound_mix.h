/* SPDX-License-Identifier: MIT. Integer-only PCM mixer shared with host tests. */
#ifndef MYRO_SOUND_MIX_H
#define MYRO_SOUND_MIX_H
#include <string.h>
typedef struct {unsigned id,pos;int active;unsigned halfRate64,phase64,tailPos191,tailPhase191,fade191;} SoundVoice;
/* NPC recordings retain24kHz PCM; interpolate at48kHz without a larger cache. */
static int sound_source_sample191(SoundVoice*v,const short*p,unsigned length){int sample=p[v->pos];if(!v->halfRate64){v->pos++;return sample;}if(!v->phase64){v->phase64=1;return sample;}v->phase64=0;int next=v->pos+1<length?p[v->pos+1]:sample;v->pos++;return(sample+next)/2;}
static int sound_voice_sample64(SoundVoice*v,const short*p,unsigned length){int sample=sound_source_sample191(v,p,length);if(v->fade191){SoundVoice tail={.pos=v->tailPos191,.halfRate64=v->halfRate64,.phase64=v->tailPhase191};int old=tail.pos<length?sound_source_sample191(&tail,p,length):0;unsigned left=v->fade191--;v->tailPos191=tail.pos;v->tailPhase191=tail.phase64;sample=(sample*(int)(128-left)+old*(int)left)/128;}return sample;}
/* Bound noisy sustained duplicates without dropping a new cast or click-cutting.
 * maxCopies=0 retains the ordinary six-voice policy (including per-hit cues). */
static int sound_voice_start191(SoundVoice*v,unsigned count,unsigned id,unsigned halfRate,unsigned maxCopies){int slot=-1,oldest=-1;unsigned copies=0;for(unsigned i=0;i<count;i++){if(!v[i].active&&slot<0)slot=(int)i;if(v[i].active&&v[i].id==id){copies++;if(oldest<0||v[i].pos>v[oldest].pos)oldest=(int)i;}}int replace=maxCopies&&copies>=maxCopies;if(replace)slot=oldest;if(slot<0)return 0;SoundVoice old=v[slot];v[slot]=(SoundVoice){.id=id,.active=1,.halfRate64=halfRate};if(replace){v[slot].tailPos191=old.pos;v[slot].tailPhase191=old.phase64;v[slot].fade191=128;}return 1;}
/* Original Soul Strike recording is much hotter than the base cue bank. */
static int sound_clip_gain200(unsigned id,int sample){return id==52?sample*30/100:sample;}
/* Sum before gain: overlapping voices must not clip before the volume control. */
static int sound_sample52(SoundVoice*voices,unsigned count,const short*const*data,const unsigned*lengths,unsigned clips){
 int mix=0;for(unsigned j=0;j<count;j++){SoundVoice*v=&voices[j];if(!v->active)continue;if(v->id>=clips||v->pos>=lengths[v->id]){v->active=0;continue;}mix+=sound_clip_gain200(v->id,sound_voice_sample64(v,data[v->id],lengths[v->id]));}return mix;
}
/* Creature voices have their own gain; hit/player/spell cues keep master gain. */
static int sound_creature61(unsigned id,unsigned dynamicFirst){
#ifdef SOUND_NPC_FIRST64
 if(id>=SOUND_NPC_FIRST64)return 0;
#endif
 return(id>=2&&id<52)||id>=dynamicFirst;}
static int sound_sample_buses61(SoundVoice*voices,unsigned count,const short*const*data,const unsigned*lengths,unsigned clips,unsigned dynamicFirst,unsigned enemyVolume){int mix=0;if(enemyVolume>100)enemyVolume=100;for(unsigned j=0;j<count;j++){SoundVoice*v=voices+j;if(!v->active)continue;if(v->id>=clips||!data[v->id]||v->pos>=lengths[v->id]){v->active=0;continue;}int sample=sound_clip_gain200(v->id,sound_voice_sample64(v,data[v->id],lengths[v->id]));if(sound_creature61(v->id,dynamicFirst))sample=sample*(int)enemyVolume/100;mix+=sample;}return mix;}
/* Independent buses, fixed headroom; no music-driven effects attenuation. */
static short sound_output52(int effects,int effectsVolume,int music){
 int mix=effects*effectsVolume/200+music/2;if(mix>32767)mix=32767;if(mix< -32768)mix=-32768;return (short)mix;
}
static void sound_mix(short*out,unsigned frames,SoundVoice*voices,unsigned count,const short*const*data,const unsigned*lengths,unsigned clips){
 for(unsigned i=0;i<frames;i++){int mix=sound_sample52(voices,count,data,lengths,clips);if(mix>32767)mix=32767;if(mix< -32768)mix=-32768;out[i*2]=out[i*2+1]=(short)mix;}
}
#endif
