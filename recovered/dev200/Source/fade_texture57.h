/* MIT. NV2A linear textures require rows on a 64-byte pitch boundary. */
#ifndef MYRO_FADE_TEXTURE57_H
#define MYRO_FADE_TEXTURE57_H
#include <stdint.h>
#define FADE_WIDTH57 16u
#define FADE_HEIGHT57 256u
#define FADE_PITCH57 64u
#define FADE_BYTES57 (FADE_PITCH57*FADE_HEIGHT57)
static void fade_pixels57(uint32_t*p){for(unsigned y=0;y<FADE_HEIGHT57;y++)for(unsigned x=0;x<FADE_WIDTH57;x++)p[y*FADE_WIDTH57+x]=y<<24;}
#endif
