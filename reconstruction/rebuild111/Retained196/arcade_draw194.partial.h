static void arcade_poring194(
 int x,int y,int size,unsigned color
){
 for(int r=0;r<size;r++){
  float v=(r-size*.5f)/(size*.5f);
  int w=(int)(sqrtf(fmaxf(0,1-v*v))*size*.5f);
  if(w)pb_fill(x+size/2-w,y+r,w*2,1,color);
 }

 if(size>=8){
  pb_fill(x+size/3,y+size/2,1,2,0xff000000);
  pb_fill(x+size*2/3,y+size/2,1,2,0xff000000);
  pb_fill(x+size/2,y+size*2/3,2,1,0xff000000);
 }
}

static void arcade_draw194(void){
 const Arcade194*a=&arcade194;

 ui_panel(68,46,504,390,arcade_names194[a->game],1,-1);
 pb_fill(84,105,472,286,0xff101711);

 ui_scaled(
  88,77,1,"Score %u    Lives %u    Round %u",
  a->score,a->lives,a->level);

 int x=100,y=116,w=440,h=264;

 if(a->game==AR194_PONG){
  for(int k=0;k<15;k++)
   pb_fill(x+w/2,y+k*18,2,8,0xff5b7568);

  pb_fill(x+20,y+(int)(a->paddle*h)-27,6,54,0xff6aabef);
  pb_fill(x+w-26,y+(int)(a->opponent*h)-27,6,54,0xff60d27a);

  arcade_poring194(
   x+(int)(a->x*w)-5,y+(int)(a->y*h)-5,10,0xffedbfd1);
 }
 else if(a->game==AR194_PATROL){
  for(unsigned i=0;i<36;i++)if(a->board[i]){
   int ex=x+(int)(
    (.12f+i%9*.09f+sinf(a->time*.8f)*.04f)*w);
   int ey=y+(int)((.12f+i/9*.085f)*h);

   pb_fill(ex-6,ey-4,12,8,0xffffdf56);
   pb_fill(ex-8,ey+2,3,5,0xffbd8c3e);
   pb_fill(ex+5,ey+2,3,5,0xffbd8c3e);
   pb_fill(ex+2,ey-2,2,2,0xff000000);
  }

  arcade_poring194(
   x+(int)(a->x*w)-7,y+(int)(h*.89f),14,0xffedbfd1);

  for(unsigned i=0;i<24;i++)if(a->shots[i].on)
   pb_fill(
    x+(int)(a->shots[i].x*w),
    y+(int)(a->shots[i].y*h),
    2,5,
    a->shots[i].vy<0?0xff65dffa:0xffff4848);
 }
 else if(a->game==AR194_SNAKE||a->game==AR194_MAZE){
  const int cell=15,gx=148,gy=116;

  if(a->game==AR194_SNAKE){
   for(unsigned i=0;i<a->length;i++)
    pb_fill(
     gx+a->snake[i]%23*cell+1,
     gy+a->snake[i]/23*cell+1,
     13,13,i?0xff60d27a:0xffedbfd1);

   pb_fill(
    gx+a->food%23*cell+4,
    gy+a->food/23*cell+4,
    7,7,0xffff4848);
  }else{
   for(unsigned i=0;i<AR194_CELLS;i++){
    int xx=gx+i%23*cell,yy=gy+i/23*cell;

    if(!a->board[i])
     pb_fill(xx,yy,14,14,0xff6aabef);
    else if(a->board[i]<3)
     pb_fill(
      xx+(a->board[i]==2?5:6),
      yy+(a->board[i]==2?5:6),
      a->board[i]==2?5:2,
      a->board[i]==2?5:2,
      0xffffdf56);
   }

   arcade_poring194(
    gx+a->food%23*cell+1,
    gy+a->food/23*cell+1,
    13,0xffedbfd1);

   for(unsigned i=0;i<4;i++)
    arcade_poring194(
     gx+a->ghosts[i]%23*cell+2,
     gy+a->ghosts[i]/23*cell+2,
     11,
     a->powerUntil>a->time?0xff8999b2:
      (unsigned[]){
       0xffff4848,0xff65dffa,0xffffdf56,0xff60d27a
      }[i]);
  }
 }
 else if(a->game==AR194_BREAKER){
  for(unsigned i=0;i<60;i++)if(a->board[i]){
   int xx=x+i%10*44,yy=y+26+i/10*13;
   pb_fill(xx+1,yy,41,11,i/10%2?0xff60d27a:0xffbd8c3e);
  }

  pb_fill(
   x+(int)(a->paddle*w)-44,
   y+(int)(h*.92f),
   88,6,0xff6aabef);

  arcade_poring194(
   x+(int)(a->x*w)-5,y+(int)(a->y*h)-5,10,0xffedbfd1);
 }
 else if(a->game==AR194_PUZZLE){
  for(unsigned i=0;i<16;i++){
   int xx=182+i%4*70,yy=112+i/4*66;

   pb_fill(
    xx,yy,66,62,
    a->tiles[i]?0xffdbe3ed:0xff27392b);

   if(i==a->cursor)
    ui_outline(xx-1,yy-1,68,64,0xffffdf56);

   if(a->tiles[i]){
    arcade_poring194(xx+21,yy+8,24,0xffedbfd1);

    char n[8];
    snprintf(n,sizeof(n),"%u",a->tiles[i]);

    ui_scaled(
     xx+31-ui_text_width(n,1)/2,yy+39,1,"%s",n);
   }
  }
 }

 if(a->paused||a->over){
  pb_fill(176,204,288,84,0xffeaf0f5);
  ui_outline(176,204,288,84,0xff6aabef);

  ui_scaled(
   196,218,1,"%s",
   a->paused?"Resting the Poring...":
   a->won?"A splendid result!":
          "Another biscuit, another try.");

  ui_hint64(
   196,253,.9f,
   a->paused?"Y: resume   B: leave":
             "A: play again   B: leave");
 }

 const char*help=
  a->game==AR194_PONG?
   "UP/DOWN: paddle":
  a->game==AR194_PATROL?
   "LEFT/RIGHT: move   A: fire":
  a->game==AR194_BREAKER?
   "LEFT/RIGHT: paddle   A: launch":
  a->game==AR194_PUZZLE?
   "D-PAD: choose   A: slide":
   "D-PAD: move";

 ui_hint64(
  88,400,.85f,"%s   Y: pause   B: leave",help);
}
