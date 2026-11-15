/* MIT. Per-stick radial input thresholds, integer percent steps2. */
#ifndef MYRO_CONTROLLER_TOLERANCE58_H
#define MYRO_CONTROLLER_TOLERANCE58_H
#include <stdint.h>
static unsigned stickSteps58[2]={10,10};
static unsigned stick_step58(unsigned value,int delta){int n=(int)value+delta;return n<0?0:n>25?25:(unsigned)n;}
static int stick_accept58(int x,int y,unsigned steps){int64_t xx=x,yy=y;int64_t threshold=(int64_t)(steps>25?25:steps)*2*32768/100;return xx*xx+yy*yy>threshold*threshold;}
#endif
