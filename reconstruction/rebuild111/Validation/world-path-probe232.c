#define main unused_world232
#include "../Source/test_world43.c"
#undef main
static Combat player200;
static void combat_steer232(const CombatMob*enemy,float*mx,float*my){
 Combat*g=&player200;*mx=*my=0;if(combat_dist(g->x,g->y,enemy->x,enemy->y)<=176)return;
 unsigned n=gw*gh,start=(unsigned)(g->y/8)*gw+(unsigned)(g->x/8),*queue=malloc(n*sizeof(*queue)),*parent=malloc(n*sizeof(*parent));assert(queue&&parent&&start<n);for(unsigned i=0;i<n;i++)parent[i]=~0u;parent[start]=start;queue[0]=start;unsigned head=0,tail=1,goal=~0u;
 while(head<tail){unsigned node=queue[head++];float x=node==start?g->x:(node%gw)*8+4,y=node==start?g->y:(node/gw)*8+4;if(combat_dist(x,y,enemy->x,enemy->y)<=128){goal=node;break;}int dx[]={-1,1,0,0},dy[]={0,0,-1,1};for(unsigned i=0;i<4;i++){int xx=(int)(node%gw)+dx[i],yy=(int)(node/gw)+dy[i];if(xx<1||yy<1||xx>=(int)gw-1||yy>=(int)gh-1)continue;unsigned next=(unsigned)yy*gw+(unsigned)xx;if(parent[next]!=~0u||!world_can_move(NULL,x,y,xx*8+4,yy*8+4))continue;parent[next]=node;queue[tail++]=next;}}
 if(goal!=~0u&&goal!=start){while(parent[goal]!=start)goal=parent[goal];float dx=(goal%gw)*8+4-g->x,dy=(goal/gw)*8+4-g->y,d=sqrtf(dx*dx+dy*dy);if(d>0){*mx=dx/d;*my=dy/d;}}
 printf("BFS visited %u of %u goal %u player allowed %d\n",tail,n,goal,allowed(g->x,g->y));free(queue);free(parent);
}

int main(void){assert(world_activate(313));float x=291,y=2145;printf("Map %u grid %ux%u. Player point allowed %d height %.2f; enemy allowed %d height %.2f\n",activeMap,gw,gh,allowed(x,y),height_at(x,y),allowed(650,1849),height_at(650,1849));for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)if(dx||dy)printf("Offset %d %d: center %.0f %.0f allowed %d move %d; exact shift allowed %d move %d\n",dx,dy,292+dx*8.f,2148+dy*8.f,allowed(292+dx*8,2148+dy*8),world_can_move(NULL,x,y,292+dx*8,2148+dy*8),allowed(x+dx*8,y+dy*8),world_can_move(NULL,x,y,x+dx*8,y+dy*8));player200.x=x;player200.y=y;CombatMob enemy={0};enemy.x=650;enemy.y=1849;float mx,my;combat_steer232(&enemy,&mx,&my);printf("BFS axes %.2f %.2f\n",mx,my);world_release();assert(!allocated);return 0;}
