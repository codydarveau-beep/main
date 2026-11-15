/* MIT. Top controls occupy the gap between live Basic Info and minimap bounds. */
#ifndef MYRO_TOP_BUTTONS200_H
#define MYRO_TOP_BUTTONS200_H
static int basicInfoRight200=220,basicInfoBottom200=118,diagnosticsVisible200;
typedef struct{int x[5],y[5],w,h,bottom,left,right;}TopButtons200;
static TopButtons200 top_buttons200(int basicRight,unsigned mapSize){TopButtons200 b={0};b.left=basicRight+6;b.right=(mapSize==0?626:mapSize==2?470:518)-6;b.w=42;b.h=26;int top=20,available=b.right-b.left;if(available<42){b.left=b.right-42;available=42;top=118;}int columns=(available+4)/(b.w+4);if(columns>5)columns=5;if(columns<1)columns=1;if(columns==4)columns=3;for(int first=0;first<5;first+=columns){int count=5-first<columns?5-first:columns,width=count*b.w+(count-1)*4,start=b.left+(available-width)/2,row=first/columns;for(int n=0;n<count;n++){b.x[first+n]=start+n*(b.w+4);b.y[first+n]=top+row*(b.h+8);}}b.bottom=b.y[4]+b.h+4;return b;}
static void diagnostics_layout200(unsigned mapSize,int*x,int*y){TopButtons200 b=top_buttons200(basicInfoRight200,mapSize);*x=(mapSize==0?626:mapSize==2?470:518)-216;*y=b.bottom+6;if(*x<basicInfoRight200+6&&*y<basicInfoBottom200+6)*y=basicInfoBottom200+6;}
#endif
