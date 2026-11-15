/* SPDX-License-Identifier: MIT. Shared light RO-style utility panels. */
static void hud_panel(int x,int y,int w,int h){
 pb_fill(x,y,w,h,0xffeaf0f5);
 pb_fill(x,y,w,1,0xff8999b2);pb_fill(x,y+h-1,w,1,0xff8999b2);
 pb_fill(x,y,1,h,0xff8999b2);pb_fill(x+w-1,y,1,h,0xff8999b2);
 if(w>2&&h>3)pb_fill(x+1,y+1,w-2,2,0xff8fd1ff);
}
