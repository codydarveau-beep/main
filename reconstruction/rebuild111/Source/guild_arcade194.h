/* MIT. Reconstructed bounded cabinet simulation. Scores use released guild slots.
 * No character RNG, inventory, experience or native quest operation is used. */
#ifndef MYRO_GUILD_ARCADE194_H
#define MYRO_GUILD_ARCADE194_H
#define ARCADE_W194 24
#define ARCADE_H194 16
#define ARCADE_CELLS194 (ARCADE_W194*ARCADE_H194)
typedef struct{
 unsigned kind,over,score,elapsed,accumulator,ticks,rng,dir,nextDir,length;
 int x,y,ballX,ballY,vx,vy,paddle,foodX,foodY,piece,rotation,ghostX[2],ghostY[2];
 unsigned power;
 unsigned short snake[ARCADE_CELLS194];
 unsigned char cells[ARCADE_CELLS194];
}GuildArcade194;
static unsigned arcade_random194(GuildArcade194*a){a->rng=a->rng*1664525u+1013904223u;return a->rng;}
static int arcade_inside194(int x,int y){return x>=0&&x<ARCADE_W194&&y>=0&&y<ARCADE_H194;}
static int arcade_free194(const GuildArcade194*a,int x,int y){return arcade_inside194(x,y)&&a->cells[y*ARCADE_W194+x]!=1;}
static void arcade_food194(GuildArcade194*a){
 unsigned start=arcade_random194(a)%ARCADE_CELLS194;
 for(unsigned k=0;k<ARCADE_CELLS194;k++){unsigned p=(start+k)%ARCADE_CELLS194;int occupied=0;
  for(unsigned i=0;i<a->length;i++)if(a->snake[i]==p){occupied=1;break;}
  if(!occupied){a->foodX=p%ARCADE_W194;a->foodY=p/ARCADE_W194;return;}
 }a->over=1;
}
static void arcade_piece_cell194(const GuildArcade194*a,unsigned index,int*x,int*y){
 static const signed char shapes[7][4][2]={{{-1,0},{0,0},{1,0},{2,0}},{{0,0},{1,0},{0,1},{1,1}},{{-1,0},{0,0},{1,0},{0,1}},{{-1,1},{0,1},{0,0},{1,0}},{{-1,0},{0,0},{0,1},{1,1}},{{-1,0},{-1,1},{0,1},{1,1}},{{1,0},{-1,1},{0,1},{1,1}}};
 int xx=shapes[a->piece%7][index%4][0],yy=shapes[a->piece%7][index%4][1];
 if(a->piece%7!=1)for(unsigned i=0;i<a->rotation%4;i++){int t=xx;xx=-yy;yy=t;}
 *x=a->x+xx;*y=a->y+yy;
}
static int arcade_piece_valid194(const GuildArcade194*a){
 for(unsigned i=0;i<4;i++){int x,y;arcade_piece_cell194(a,i,&x,&y);if(!arcade_inside194(x,y)||a->cells[y*ARCADE_W194+x])return 0;}return 1;
}
static void arcade_new_piece194(GuildArcade194*a){a->piece=(int)(arcade_random194(a)%7);a->rotation=0;a->x=12;a->y=1;if(!arcade_piece_valid194(a))a->over=1;}
static void arcade_start194(GuildArcade194*a,unsigned kind){
 memset(a,0,sizeof(*a));a->kind=kind<6?kind:0;a->rng=0x194cafeu+kind;a->paddle=12;a->ballX=12;a->ballY=10;a->vx=1;a->vy=-1;a->x=12;a->y=15;
 if(kind==1)for(unsigned y=1;y<4;y++)for(unsigned x=2;x<23;x+=3)a->cells[y*24+x]=1;
 if(kind==2){a->length=3;a->snake[0]=8*24+12;a->snake[1]=8*24+11;a->snake[2]=8*24+10;arcade_food194(a);}
 if(kind==3)for(unsigned y=1;y<5;y++)for(unsigned x=1;x<23;x++)a->cells[y*24+x]=1;
 if(kind==4)arcade_new_piece194(a);
 if(kind==5){
  for(int y=0;y<16;y++)for(int x=0;x<24;x++)a->cells[y*24+x]=(!x||!y||x==23||y==15||(x%4==0&&y%2==0))?1:2;
  a->x=a->y=1;a->cells[25]=0;a->ghostX[0]=22;a->ghostY[0]=14;a->ghostX[1]=22;a->ghostY[1]=1;
  a->cells[1*24+22]=a->cells[14*24+1]=a->cells[14*24+22]=3;
 }
}
static void arcade_input194(GuildArcade194*a,unsigned pressed){
 if(a->over)return;
 if(a->kind==2||a->kind==5){if(pressed&8192)a->nextDir=0;if(pressed&2048)a->nextDir=1;if(pressed&4096)a->nextDir=2;if(pressed&1024)a->nextDir=3;}
 else if(a->kind==4){
  if(pressed&(4096|8192)){int old=a->x;a->x+=(pressed&8192)?1:-1;if(!arcade_piece_valid194(a))a->x=old;}
  if(pressed&2){unsigned old=a->rotation;a->rotation=(a->rotation+1)%4;if(!arcade_piece_valid194(a))a->rotation=old;}
  if(pressed&2048){a->y++;if(!arcade_piece_valid194(a))a->y--;}
 }else{
  if(pressed&4096)a->paddle--;if(pressed&8192)a->paddle++;
  if(a->paddle<2)a->paddle=2;if(a->paddle>21)a->paddle=21;
  if(a->kind==1&&(pressed&2))for(int y=14;y>=0;y--)if(a->cells[y*24+a->paddle]){a->cells[y*24+a->paddle]=0;a->score+=10;break;}
 }
}
static void arcade_step194(GuildArcade194*a){
 static const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};a->ticks++;
 if(a->kind==0||a->kind==3){
  int x=a->ballX+a->vx,y=a->ballY+a->vy;
  if(x<0||x>=24){a->vx=-a->vx;x=a->ballX+a->vx;}if(y<0){a->vy=1;y=a->ballY+1;}
  if(y>=14){if(abs(x-a->paddle)<=2){a->vy=-1;y=13;a->score++;}else{a->over=1;return;}}
  if(a->kind==3&&a->cells[y*24+x]){a->cells[y*24+x]=0;a->score+=5;a->vy=-a->vy;}
  a->ballX=x;a->ballY=y;
 }else if(a->kind==1){
  if(a->ticks%4==0){for(int x=0;x<24;x++)if(a->cells[14*24+x]){a->over=1;return;}
   memmove(a->cells+24,a->cells,15*24);memset(a->cells,0,24);a->cells[arcade_random194(a)%24]=1;}
 }else if(a->kind==2){
  unsigned direction=a->nextDir;if((direction+2)%4==a->dir)direction=a->dir;a->dir=direction;
  int x=a->snake[0]%24+dx[direction],y=a->snake[0]/24+dy[direction];if(!arcade_inside194(x,y)){a->over=1;return;}
  unsigned cell=(unsigned)(y*24+x);int grow=x==a->foodX&&y==a->foodY;
  for(unsigned i=0;i<a->length-(grow?0u:1u);i++)if(a->snake[i]==cell){a->over=1;return;}
  if(grow){a->score+=10;if(a->length==ARCADE_CELLS194){a->over=1;return;}a->length++;}
  memmove(a->snake+1,a->snake,(a->length-1)*sizeof(*a->snake));a->snake[0]=(unsigned short)cell;if(grow)arcade_food194(a);
 }else if(a->kind==4){
  a->y++;if(!arcade_piece_valid194(a)){
   a->y--;for(unsigned i=0;i<4;i++){int x,y;arcade_piece_cell194(a,i,&x,&y);if(!arcade_inside194(x,y)){a->over=1;return;}a->cells[y*24+x]=1;}
   for(int y=15;y>=0;y--){int full=1;for(int x=0;x<24;x++)if(!a->cells[y*24+x])full=0;
    if(full){memmove(a->cells+24,a->cells,(size_t)y*24);memset(a->cells,0,24);a->score+=100;y++;}}
   a->score++;arcade_new_piece194(a);
  }
 }else if(a->kind==5){
  unsigned direction=a->nextDir;int x=a->x+dx[direction],y=a->y+dy[direction];
  if(arcade_free194(a,x,y)){a->dir=direction;a->x=x;a->y=y;}
  else if(arcade_free194(a,a->x+dx[a->dir],a->y+dy[a->dir])){a->x+=dx[a->dir];a->y+=dy[a->dir];}
  unsigned cell=(unsigned)(a->y*24+a->x);if(a->cells[cell]>=2){a->score++;if(a->cells[cell]==3)a->power=30;a->cells[cell]=0;}
  if(a->power)a->power--;
  for(unsigned i=0;i<2;i++){
   if(a->x==a->ghostX[i]&&a->y==a->ghostY[i]){if(!a->power){a->over=1;return;}a->score+=20;a->ghostX[i]=22;a->ghostY[i]=14;}
   if(a->ticks%2==0){int best=10000,nx=a->ghostX[i],ny=a->ghostY[i];unsigned start=arcade_random194(a)%4;
    for(unsigned k=0;k<4;k++){unsigned d=(start+k)%4;int xx=a->ghostX[i]+dx[d],yy=a->ghostY[i]+dy[d];if(!arcade_free194(a,xx,yy))continue;int cost=abs(xx-a->x)+abs(yy-a->y);if(a->power)cost=-cost;if(cost<best){best=cost;nx=xx;ny=yy;}}
    a->ghostX[i]=nx;a->ghostY[i]=ny;
   }
   if(a->x==a->ghostX[i]&&a->y==a->ghostY[i]&&!a->power){a->over=1;return;}
  }
 }
}
static void arcade_tick194(GuildArcade194*a,unsigned milliseconds){
 if(a->over)return;if(milliseconds>1000)milliseconds=1000;
 if(a->elapsed<3600000)a->elapsed+=milliseconds;a->accumulator+=milliseconds;
 unsigned steps=0;while(a->accumulator>=120&&steps++<4&&!a->over){a->accumulator-=120;arcade_step194(a);}
 if(a->accumulator>480)a->accumulator=480;
}
#endif
