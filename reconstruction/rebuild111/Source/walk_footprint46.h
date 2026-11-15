/* MIT. Continuous controller movement with a small ground footprint.
 * RO's blocked GAT cells are authoritative; decorative mesh bounds are not.
 * 3 world units clearance keeps feet away from blocked-cell interiors while
 * retaining passages one 8-unit GAT cell wide. Check actual circle/rectangle
 * distance so diagonal corners are rounded rather than arbitrarily squared.
 */
#ifndef MYRO_WALK_FOOTPRINT46_H
#define MYRO_WALK_FOOTPRINT46_H
#include "prop_clearance46.h"
static int walk_footprint46(const unsigned char*mask,unsigned width,unsigned height,float x,float y){
 const float radius=3.f;if(!mask||!isfinite(x)||!isfinite(y)||x<8+radius||y<8+radius||x>=(width-1)*8.f-radius||y>=(height-1)*8.f-radius)return 0;
 int minx=(int)((x-radius)/8),maxx=(int)((x+radius)/8),miny=(int)((y-radius)/8),maxy=(int)((y+radius)/8);
 for(int cy=miny;cy<=maxy;cy++)for(int cx=minx;cx<=maxx;cx++)if(!mask[cy*width+cx]){float left=cx*8.f,top=cy*8.f;float dx=x<left?left-x:x>left+8?x-left-8:0,dy=y<top?top-y:y>top+8?y-top-8:0;if(dx*dx+dy*dy<radius*radius-.0001f)return 0;}
 return prop_clearance46(width,x,y);
}
#endif
