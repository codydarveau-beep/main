/* Radial deadzone plus menu hysteresis; feed held bits through normal repeat. */
#ifndef MYRO_CONTROLLER_NAV61_H
#define MYRO_CONTROLLER_NAV61_H
static unsigned menu_stick61(int x,int y,unsigned steps,unsigned previous){if(!stick_accept58(x,y,steps))return 0;int ax=x<0?-x:x,ay=y<0?-y:y,threshold=previous?9830:14745;if(ax<threshold&&ay<threshold)return 0;if(ax>ay)return x<0?4096:8192;return y<0?1024:2048;}
#endif
