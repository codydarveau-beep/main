/* MIT. Current-map sparse 2-unit solid-base occupancy, no scenery mesh resident. */
#ifndef MYRO_PROP_CLEARANCE46_H
#define MYRO_PROP_CLEARANCE46_H
#include <stdint.h>
typedef struct {uint32_t cell;uint16_t bits,pad;} PropCell46;
static const PropCell46*propCells46;static unsigned propCount46;
static unsigned prop_bits46(unsigned cell){unsigned lo=0,hi=propCount46;while(lo<hi){unsigned m=(lo+hi)/2;if(propCells46[m].cell<cell)lo=m+1;else hi=m;}return lo<propCount46&&propCells46[lo].cell==cell?propCells46[lo].bits:0;}
static int prop_clearance46(unsigned width,float x,float y){const float r=4;int x0=(int)((x-r)/2),x1=(int)((x+r)/2),y0=(int)((y-r)/2),y1=(int)((y+r)/2);for(int yy=y0;yy<=y1;yy++)for(int xx=x0;xx<=x1;xx++){unsigned bits=prop_bits46((yy/4)*width+xx/4);if(bits&(1u<<((yy%4)*4+xx%4))){float l=xx*2.f,t=yy*2.f,dx=x<l?l-x:x>l+2?x-l-2:0,dy=y<t?t-y:y>t+2?y-t-2:0;if(dx*dx+dy*dy<r*r-.0001f)return 0;}}return 1;}
#endif
