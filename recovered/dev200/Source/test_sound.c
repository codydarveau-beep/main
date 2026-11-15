#include <assert.h>
#include <stdio.h>
#include "sound_mix.h"
int main(void){const short a[]={30000,-30000,7},b[]={10000,-10000};const short*data[]={a,b};unsigned sizes[]={3,2};SoundVoice v[3]={{0,0,1},{1,0,1},{99,0,1}};short out[12];sound_mix(out,6,v,3,data,sizes,2);assert(out[0]==32767&&out[1]==32767&&out[2]==-32768&&out[3]==-32768&&out[4]==7&&out[5]==7);for(int i=6;i<12;i++)assert(!out[i]);for(int i=0;i<3;i++)assert(!v[i].active);sound_mix(out,6,v,3,data,sizes,2);for(int i=0;i<12;i++)assert(!out[i]);puts("PASS stereo PCM, saturation, clip completion, silent idle and invalid voice guard");}
