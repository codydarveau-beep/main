/* MIT. World-space cursor; follow actual movement, never attempted movement. */
static void ground_cursor_clamp(float*x,float*y,float px,float py,float range,unsigned w,unsigned h){
 float dx=*x-px,dy=*y-py,d=sqrtf(dx*dx+dy*dy);if(d>range&&d>0){*x=px+dx*range/d;*y=py+dy*range/d;}
 if(*x<8)*x=8;if(*y<8)*y=8;if(*x>w*8.f-9)*x=w*8.f-9;if(*y>h*8.f-9)*y=h*8.f-9;
}
static void ground_cursor_follow(float*x,float*y,float oldX,float oldY,float newX,float newY,float range,unsigned w,unsigned h){
 *x+=newX-oldX;*y+=newY-oldY;ground_cursor_clamp(x,y,newX,newY,range,w,h);
}
