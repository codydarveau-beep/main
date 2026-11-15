#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "top_buttons200.h"
#include "compass_layout62.h"
#include "font_metrics65.h"
int main(void){const char*labels[]={"Quests","Equips","Status","Items","Skills"};for(unsigned map=0;map<3;map++)for(int right=220;right<=390;right+=5){TopButtons200 b=top_buttons200(right,map);for(int i=0;i<5;i++){assert(b.x[i]>=b.left&&b.x[i]+b.w<=b.right);assert(b.w>30&&b.h>20);int width=0;for(const char*p=labels[i];*p;p++)width+=ui_native_advance65(*p,9.f/11.f);assert(width<=b.w-4);for(int j=i+1;j<5;j++)assert(b.y[i]!=b.y[j]||b.x[i]+b.w+4<=b.x[j]);}for(int row=0;row<5;row++){int first=-1,last=-1;for(int i=0;i<5;i++)if(b.y[i]==b.y[row]){if(first<0)first=i;last=i;}assert(abs((b.x[first]+b.x[last]+b.w)-(b.left+b.right))<=1);}basicInfoRight200=right;for(unsigned size=1;size<=2;size++){int cx,cy,r;compass_layout62(map,size,&cx,&cy,&r);assert(cy-r-32>=b.bottom+2);}}for(unsigned mode=0;mode<3;mode++){for(int br=220;br<390;br+=10){basicInfoRight200=br;diagnosticsVisible200=1;int x,y,cx,cy,r;diagnostics_layout200(mode,&x,&y);assert(x+210<=(mode==0?626:mode==2?470:518)-6);assert(y>=top_buttons200(br,mode).bottom+6);compass_layout62(mode,2,&cx,&cy,&r);assert(cy-r-32>=y+49);}}puts("PASS enlarged42x26 top buttons with10px native labels; all minimap sizes/live Basic Info widths, centered rows/nonoverlap and compass2px clearance.");}
