#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "input_repeat.h"
#include "cast_ray.h"
int main(void){InputRepeat r={0};assert(!input_repeat(&r,8192,12288,1,.05f));int early=0,late=0;for(int i=0;i<60;i++){unsigned b=input_repeat(&r,8192,12288,1,.05f);if(i<20)early+=!!b;else late+=!!b;}assert(early>0&&late>early);assert(!input_repeat(&r,8192,12288,2,.1f));for(int i=0;i<30;i++)assert(!input_repeat(&r,8192,12288,2,.1f));input_repeat(&r,0,12288,2,.1f);input_repeat(&r,8192,12288,2,.1f);int n=0;for(int i=0;i<10;i++)n+=!!input_repeat(&r,8192,12288,2,.1f);assert(n);assert(!input_repeat(&r,12288,12288,2,.1f));for(int i=0;i<30;i++)assert(!input_repeat(&r,2,0,0,.1f));unsigned char grid[100];for(int i=0;i<100;i++)grid[i]=1;assert(cast_ray(grid,10,10,12,12,68,12));grid[1*10+4]=0;assert(!cast_ray(grid,10,10,12,12,68,12));grid[14]=1;grid[18]=0;assert(cast_ray(grid,10,10,12,12,68,12));assert(!cast_ray(grid,10,10,NAN,12,68,12));assert(!cast_ray(grid,10,10,12,12,80,12));puts("PASS hold acceleration, fresh press/context protection, opposed buttons, excluded actions, spell obstacle/end-cell/bounds guards");}
