/* Source EF_PORTAL2 cylinder dimensions, ticks and ground-ring cadence. */
#ifndef MYRO_PORTAL_GEOMETRY61_H
#define MYRO_PORTAL_GEOMETRY61_H
#define PORTAL_UNIT61 1.6f
static float portal_opacity61(float age,float duration,float maximum){float p=age/duration;if(p<0||p>=1)return 0;if(p<.25f)return maximum*p*4;if(p>.75f)return maximum*(1-p)*4;return maximum;}
static void portal_point61(float x,float y,float ground,float bottom,float top,float height,unsigned side,unsigned count,unsigned upper,float rotation,float out[3]){float a=side*6.283185307f/count+rotation,r=(upper?top:bottom)*PORTAL_UNIT61;out[0]=x+sinf(a)*r;out[1]=y+cosf(a)*r;out[2]=ground+(upper?height*PORTAL_UNIT61:0);}
#endif
