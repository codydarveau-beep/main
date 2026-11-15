/* MIT. Screen-space six-pixel cast indicator, anchored to the visible player top. */
#ifndef MYRO_CAST_INDICATOR_H
#define MYRO_CAST_INDICATOR_H

#include "cast_layout43.h"
typedef struct {int x,y,fill,width;} CastIndicator;
static int cast_indicator(const Combat*g,float headX,float headTop,CastIndicator*b){if(!combat_casting(g)||g->spellCastTotal<=0||!isfinite(headX)||!isfinite(headTop))return 0;float p=1-g->spellCastLeft/g->spellCastTotal;if(p<0)p=0;if(p>1)p=1;int margin,used,step,n;cast_layout41(g->spellCastTotal,&margin,&used,&step,&n);b->width=used+2;b->x=(int)floorf(headX-b->width*.5f+.5f);b->y=(int)floorf(headTop-10+.5f);b->fill=(int)ceilf(used*p);if(b->x<2)b->x=2;if(b->x>638-b->width)b->x=638-b->width;if(b->y<2)b->y=2;if(b->y>472)b->y=472;return 1;}
#endif
