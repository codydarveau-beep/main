/* MIT. Expand immediately, relax shrinking; always contain current opaque frame. */
#ifndef MYRO_TARGET_GEOMETRY41_H
#define MYRO_TARGET_GEOMETRY41_H
typedef struct{float x0,y0,x1,y1;} TargetBounds41;
typedef struct{int valid,id;unsigned life;float halfW,halfH;} TargetTrack41;
static int target_bounds41(TargetTrack41*t,int id,unsigned life,const unsigned*d,unsigned anchorX,unsigned anchorY,float sx,float sy,float scale,float dt,TargetBounds41*out){if(!d||!isfinite(sx)||!isfinite(sy)||scale<=0)return 0;if(!d[2]||!d[3])return 0;float x0=sx+(d[0]-(float)anchorX)*scale,y0=sy+(d[1]-(float)anchorY)*scale,w=d[2]*scale*.5f+3,h=d[3]*scale*.5f+3;if(w<7)w=7;if(h<6)h=6;float k=1-expf(-fmaxf(0,dt)*16);if(!t->valid||t->id!=id||t->life!=life){t->halfW=w;t->halfH=h;t->valid=1;t->id=id;t->life=life;}else{t->halfW=w>t->halfW?w:t->halfW+(w-t->halfW)*k;t->halfH=h>t->halfH?h:t->halfH+(h-t->halfH)*k;}float cx=x0+d[2]*scale*.5f,cy=y0+d[3]*scale*.5f;*out=(TargetBounds41){cx-t->halfW,cy-t->halfH,cx+t->halfW,cy+t->halfH};return 1;}
#endif
