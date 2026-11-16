/* MIT. Visual range affects rendering only, never simulation. Units are map cells. */
#ifndef MYRO_PLAY_OPTIONS52_H
#define MYRO_PLAY_OPTIONS52_H
enum {MONSTER_VIEW_DEFAULT53=0,MONSTER_VIEW_COUNT53=62};
static const unsigned monsterCells52[MONSTER_VIEW_COUNT53]={0,8,12,16,24,32,48,10,14,18,20,22,26,28,30,34,36,38,40,42,44,46,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128};
static const char*monsterViewNames52[MONSTER_VIEW_COUNT53]={"Screen","8 cells","12 cells","16 cells","24 cells","32 cells","48 cells","10 cells","14 cells","18 cells","20 cells","22 cells","26 cells","28 cells","30 cells","34 cells","36 cells","38 cells","40 cells","42 cells","44 cells","46 cells","50 cells","52 cells","54 cells","56 cells","58 cells","60 cells","62 cells","64 cells","66 cells","68 cells","70 cells","72 cells","74 cells","76 cells","78 cells","80 cells","82 cells","84 cells","86 cells","88 cells","90 cells","92 cells","94 cells","96 cells","98 cells","100 cells","102 cells","104 cells","106 cells","108 cells","110 cells","112 cells","114 cells","116 cells","118 cells","120 cells","122 cells","124 cells","126 cells","128 cells"};
static unsigned monster_view_step52(unsigned setting,int direction){unsigned cells=setting<MONSTER_VIEW_COUNT53?monsterCells52[setting]:0;if(cells&&cells<16)cells=16;if(!cells){if(direction>0)return 0;cells=128;}else if(direction>0){if(cells==128)return 0;cells+=2;}else if(cells>16)cells-=2;for(unsigned i=0;i<MONSTER_VIEW_COUNT53;i++)if(monsterCells52[i]==cells)return i;return MONSTER_VIEW_DEFAULT53;}
static int monster_visible52(unsigned setting,float dx,float dy){if(!setting||setting>=MONSTER_VIEW_COUNT53)return 1;unsigned r=monsterCells52[setting]*8;return dx*dx+dy*dy<=(float)(r*r);}
#include "options61.h"
#endif
