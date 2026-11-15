/* SPDX-License-Identifier: MIT. Worker-owned decoder; soundLock guards controls. */
#include "music_data.h"
#include "music_stream.h"
static MusicStream musicStream;
static int musicCurrent=-1,musicRequested=-1,musicVolume=50,musicMuted,musicFade;
static unsigned musicChanges;
static int music_output(void){
 if(musicCurrent!=musicRequested){
  if(musicFade>0)musicFade--;
  else{musicCurrent=musicRequested;musicChanges++;if(musicCurrent>=0)music_stream_start(&musicStream,musicData[musicCurrent],musicSizes[musicCurrent]);
#ifdef MYRO_MUSIC_DISC50
   music_cache_keep50(musicCurrent);
#endif
  }
 }else if(musicFade<2048)musicFade++;
 if(musicCurrent<0||musicStream.error)return 0;
 int sample=music_stream_sample(&musicStream);
 if(musicMuted)return 0;return (sample*musicVolume/200)*musicFade/2048;
}
