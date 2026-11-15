/* Shared native option-edit arrows. */
#ifndef MYRO_OPTION_TRIANGLE200_H
#define MYRO_OPTION_TRIANGLE200_H
static void ui_option_triangle62(int x,int y,int right){for(int i=0;i<5;i++){int half=right?4-i:i;pb_fill(x+i,y-half,1,half*2+1,0xff111111);}}
#endif
