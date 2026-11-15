/* MIT. Spell ray: interior obstacles matter, walker's step heights do not. */
static int cast_ray(const unsigned char*grid,unsigned w,unsigned h,float x,float y,float nx,float ny){
 if(!grid||!w||!h||!isfinite(x)||!isfinite(y)||!isfinite(nx)||!isfinite(ny)||x<0||y<0||nx<0||ny<0||x>=w*8.f||nx>=w*8.f||y>=h*8.f||ny>=h*8.f)return 0;
 int sx=(int)(x/8),sy=(int)(y/8),ex=(int)(nx/8),ey=(int)(ny/8);
 float dx=nx-x,dy=ny-y;int n=(int)(sqrtf(dx*dx+dy*dy)/4)+1;
 for(int i=1;i<n;i++){int cx=(int)((x+dx*i/n)/8),cy=(int)((y+dy*i/n)/8);if((cx==sx&&cy==sy)||(cx==ex&&cy==ey))continue;if(!grid[cy*w+cx])return 0;}return 1;
}
