/* MIT. Original RSW wave/UV/animation parameters, native world scale16 per tile.
 * Reference: roBrowser Water.js/Ground.js (GPL3); source equations independently
 * expressed here. Gameplay water queries deliberately retain the mean level. */
#ifndef MYRO_WATER_WAVE190_H
#define MYRO_WATER_WAVE190_H
#include <math.h>
#include "water_data190.h"
#include "water_mode190.h"
/* Reduced modes hold selected source frames across the original cycle length. */
static unsigned water_frame190(unsigned map,float seconds){const WaterMap190*w=waterSettings190+map;unsigned count=waterFrameCounts200[waterAnimation200<WATER_ANIMATION_COUNT200?waterAnimation200:0];if(count==1)return 0;float phase=fmodf(seconds*60.f/(float)w->animation,32.f);if(phase<0)phase+=32;unsigned step=(unsigned)floorf(phase*count/32.f);if(step>=count)step=count-1;return step*32u/count;}
static float water_sample_time200(unsigned map,float seconds){if(!waterAnimation200||waterAnimation200>=WATER_ANIMATION_COUNT200)return seconds;if(waterAnimation200==8)return 0;float rate=60.f/waterSettings190[map].animation,clock=seconds*rate,cycle=floorf(clock/32.f);return(cycle*32.f+water_frame190(map,seconds))/rate;}
static float water_corner190(unsigned map,int x,int y,float seconds,float level){const WaterMap190*w=waterSettings190+map;seconds=water_sample_time200(map,seconds);float phase=fmodf(seconds*60.f*w->speed,360.f)-180.f+w->pitch*((float)x+(float)y+.5f);return level-w->height*sinf(phase*.01745329251994329577f);}
static float water_surface190(unsigned map,float x,float y,float seconds,float level){int ix=(int)floorf(x/16.f),iy=(int)floorf(y/16.f);float u=x/16.f-ix,v=y/16.f-iy,a=water_corner190(map,ix,iy,seconds,level),b=water_corner190(map,ix+1,iy,seconds,level),c=water_corner190(map,ix,iy+1,seconds,level),d=water_corner190(map,ix+1,iy+1,seconds,level);return u>=v?a+(b-a)*u+(d-b)*v:a+(d-c)*u+(c-a)*v;}
#endif
