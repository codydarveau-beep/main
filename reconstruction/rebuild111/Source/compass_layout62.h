#include "top_buttons200.h"
#ifndef MYRO_COMPASS_LAYOUT62_H
#define MYRO_COMPASS_LAYOUT62_H
/* Leave12px between compass extent and minimap; clear the top window buttons. */
static void compass_layout62(unsigned mapSize,unsigned compassSize,int*cx,int*cy,int*r){*r=compassSize==2?20:12;int left=mapSize==0?626:mapSize==2?470:518;*cx=left-12-(*r+32);*cy=*r+90;TopButtons200 top200=top_buttons200(basicInfoRight200,mapSize);int lowest200=top200.bottom+2+*r+32;if(diagnosticsVisible200){int dx,dy;diagnostics_layout200(mapSize,&dx,&dy);int clear200=dy+43+6+*r+32;if(clear200>lowest200)lowest200=clear200;}if(*cy<lowest200)*cy=lowest200;}
#endif
