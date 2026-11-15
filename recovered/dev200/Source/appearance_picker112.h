/* Controller state and fixed interior layout; all choices fit inside the main window. */
#ifndef MYRO_APPEARANCE_PICKER112_H
#define MYRO_APPEARANCE_PICKER112_H
#include "appearance_state58.h"
typedef struct{int x,y,w,h;}FrontRect112;
static const FrontRect112 hairPanel112={220,96,202,214},colourPanel112={220,318,202,72},statPanel112={430,96,162,294};
typedef struct{unsigned mode,cursor;Appearance58 before;}AppearancePicker112;
static FrontRect112 appearance_cell112(unsigned mode,unsigned index){if(mode==1)return(FrontRect112){231+(int)(index%7)*26,125+(int)(index/7)*26,24,24};return(FrontRect112){231+(int)index*20,346,18,18};}
static unsigned appearance_move112(unsigned value,unsigned count,unsigned columns,unsigned p){if(value>=count)value=0;unsigned row=value/columns,col=value%columns;if((p&4096)&&col)return value-1;if((p&8192)&&col+1<columns&&value+1<count)return value+1;if((p&1024)&&row)return value-columns;if((p&2048)&&(row+1)*columns<count){unsigned n=value+columns;return n<count?n:count-1;}return value;}
static void appearance_open112(AppearancePicker112*p,Appearance58 a,unsigned mode){p->mode=mode;p->before=a;p->cursor=mode==1?a.hair:a.colour;}
/*1: keep editing,2: confirm,3: revert. Preview never persists until creation. */
static unsigned appearance_input112(AppearancePicker112*p,Appearance58*a,unsigned buttons){if(!p->mode)return 0;if(buttons&4){*a=p->before;p->mode=0;return 3;}if(buttons&2){p->mode=0;return 2;}p->cursor=appearance_move112(p->cursor,p->mode==1?42:9,p->mode==1?7:9,buttons);if(p->mode==1)a->hair=p->cursor;else a->colour=p->cursor;return 1;}
#endif
