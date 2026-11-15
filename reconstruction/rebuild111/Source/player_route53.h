/* MIT. Bounded, incremental A* for the single player's combat approaches.
 * Uses the existing footprint/slope and Ice Wall rules. No monster AI changes.
 * 96 expansions/frame, fixed workspace, no runtime allocations or save data. */
#define PLAYER_ROUTE_SIDE53 65
#define PLAYER_ROUTE_NODES53 (PLAYER_ROUTE_SIDE53*PLAYER_ROUTE_SIDE53)
typedef struct {Combat*owner;int ox,oy,gx,gy;unsigned count;int active;uint16_t score[PLAYER_ROUTE_NODES53],heap[PLAYER_ROUTE_NODES53],position[PLAYER_ROUTE_NODES53];int16_t parent[PLAYER_ROUTE_NODES53];} PlayerRouteWork53;
static PlayerRouteWork53 routeWork53;
static int player_route_clear53(Combat*g,float x,float y,float nx,float ny){
 if(g->canMove&&!g->canMove(g->world,x,y,nx,ny))return 0;
 int steps=(int)(combat_dist(x,y,nx,ny)/4)+1;for(int i=1;i<=steps;i++)if(class_ice_block48(g,x+(nx-x)*i/steps,y+(ny-y)*i/steps)&&!class_ice_block48(g,x,y))return 0;return 1;
}
static int player_route_h53(const PlayerRoute53*r,unsigned node){int dx=abs((int)(node%65)-routeWork53.gx),dy=abs((int)(node/65)-routeWork53.gy);int h=10*(dx>dy?dx:dy)+4*(dx<dy?dx:dy)-(int)ceilf(r->range/8)*14;return h>0?h:0;}
static int player_route_less53(const PlayerRoute53*r,unsigned a,unsigned b){int fa=routeWork53.score[a]+player_route_h53(r,a),fb=routeWork53.score[b]+player_route_h53(r,b);return fa<fb||(fa==fb&&routeWork53.score[a]>routeWork53.score[b]);}
static void player_route_up53(const PlayerRoute53*r,unsigned at){unsigned node=routeWork53.heap[at];while(at){unsigned p=(at-1)/2;if(!player_route_less53(r,node,routeWork53.heap[p]))break;routeWork53.heap[at]=routeWork53.heap[p];routeWork53.position[routeWork53.heap[at]]=at+1;at=p;}routeWork53.heap[at]=node;routeWork53.position[node]=at+1;}
static unsigned player_route_pop53(const PlayerRoute53*r){unsigned node=routeWork53.heap[0],last=routeWork53.heap[--routeWork53.count],at=0;routeWork53.position[node]=65535;if(!routeWork53.count)return node;while(at*2+1<routeWork53.count){unsigned c=at*2+1;if(c+1<routeWork53.count&&player_route_less53(r,routeWork53.heap[c+1],routeWork53.heap[c]))c++;if(!player_route_less53(r,routeWork53.heap[c],last))break;routeWork53.heap[at]=routeWork53.heap[c];routeWork53.position[routeWork53.heap[at]]=at+1;at=c;}routeWork53.heap[at]=last;routeWork53.position[last]=at+1;return node;}
static void player_route_add53(const PlayerRoute53*r,unsigned node,unsigned score,int parent){if(score>=routeWork53.score[node]||routeWork53.position[node]==65535)return;routeWork53.score[node]=score;routeWork53.parent[node]=parent;unsigned pos=routeWork53.position[node];if(!pos){pos=++routeWork53.count;routeWork53.heap[pos-1]=node;}player_route_up53(r,pos-1);}
static int player_route_goal53(Combat*g,float x,float y,float range){PlayerRoute53*r=&g->route53;if(combat_dist(x,y,r->goalX,r->goalY)>range)return 0;return !r->mode||!g->canAim?player_route_clear53(g,x,y,r->goalX,r->goalY):g->canAim(g->world,x,y,r->goalX,r->goalY);}
static void player_route_fail53(Combat*g){if(g->route53.target>=0&&g->route53.target<MOB_COUNT)g->mobs[g->route53.target].routeSkipUntil53=g->time+3;g->route53.state=3;g->route53.retryAt=g->time+.75f;routeWork53.active=0;}
static void player_route_begin53(Combat*g){PlayerRoute53*r=&g->route53;routeWork53.owner=g;routeWork53.ox=(int)floorf(g->x/8)-32;routeWork53.oy=(int)floorf(g->y/8)-32;routeWork53.gx=(int)floorf(r->goalX/8)-routeWork53.ox;routeWork53.gy=(int)floorf(r->goalY/8)-routeWork53.oy;routeWork53.count=0;routeWork53.active=1;memset(routeWork53.score,255,sizeof(routeWork53.score));memset(routeWork53.position,0,sizeof(routeWork53.position));memset(routeWork53.parent,255,sizeof(routeWork53.parent));r->state=1;r->count=r->at=0;
 for(int y=31;y<=33;y++)for(int x=31;x<=33;x++){float wx=(routeWork53.ox+x)*8+4,wy=(routeWork53.oy+y)*8+4;if(player_route_clear53(g,g->x,g->y,wx,wy))player_route_add53(r,y*65+x,(unsigned)(combat_dist(g->x,g->y,wx,wy)*1.25f),-1);}
}
static void player_route_search53(Combat*g){PlayerRoute53*r=&g->route53;for(unsigned expanded=0;expanded<96&&routeWork53.count;expanded++){
 unsigned node=player_route_pop53(r);int x=node%65,y=node/65;float wx=(routeWork53.ox+x)*8+4,wy=(routeWork53.oy+y)*8+4;
 if(player_route_goal53(g,wx,wy,fmaxf(.5f,r->range-.25f))){unsigned n=0;int parent=node;while(parent>=0&&n<PLAYER_ROUTE_POINTS53){r->points[n][0]=routeWork53.ox+parent%65;r->points[n++][1]=routeWork53.oy+parent/65;parent=routeWork53.parent[parent];}if(parent>=0){player_route_fail53(g);return;}for(unsigned a=0;a<n/2;a++){int16_t tx=r->points[a][0],ty=r->points[a][1];r->points[a][0]=r->points[n-1-a][0];r->points[a][1]=r->points[n-1-a][1];r->points[n-1-a][0]=tx;r->points[n-1-a][1]=ty;}r->count=n;r->at=0;r->state=2;routeWork53.active=0;return;}
 for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){if(!dx&&!dy)continue;int nx=x+dx,ny=y+dy;if(nx<0||ny<0||nx>=65||ny>=65)continue;unsigned next=ny*65+nx;if(routeWork53.position[next]==65535)continue;unsigned score=routeWork53.score[node]+(dx&&dy?14:10);if(score>=routeWork53.score[next])continue;if(player_route_clear53(g,wx,wy,(routeWork53.ox+nx)*8+4,(routeWork53.oy+ny)*8+4))player_route_add53(r,next,score,node);}
 }if(!routeWork53.count&&r->state==1)player_route_fail53(g);}
/* Returns 1 when moving, 2 while a bounded search is progressing, 0 when blocked. */
static int player_route_position58(Combat*g,int target,unsigned life,float goalX,float goalY,float range,unsigned mode,float dt){PlayerRoute53*r=&g->route53;float movedGoal=(goalX-r->goalX)*(goalX-r->goalX)+(goalY-r->goalY)*(goalY-r->goalY);
 if(!r->state||r->target!=target||r->life!=life||r->map!=g->mapId||r->mode!=mode||fabsf(r->range-range)>.01f||movedGoal>=64){memset(r,0,sizeof(*r));r->target=target;r->life=life;r->map=g->mapId;r->mode=mode;r->range=range;r->goalX=goalX;r->goalY=goalY;}
 if(r->state==3&&g->time<r->retryAt)return 0;
 float wx=goalX,wy=goalY;
 if(r->state==1){if(routeWork53.owner!=g||!routeWork53.active){r->state=0;}else{player_route_search53(g);if(r->state==1)return 2;if(r->state==3)return 0;}}
 if(r->state!=2){if(player_route_clear53(g,g->x,g->y,wx,wy))r->state=0;else{player_route_begin53(g);player_route_search53(g);if(r->state==1)return 2;if(r->state==3)return 0;}}
 if(r->state==2){while(r->at<r->count&&combat_dist(g->x,g->y,r->points[r->at][0]*8+4,r->points[r->at][1]*8+4)<.3f)r->at++;if(r->at>=r->count){r->state=0;return 2;}unsigned at=r->at;for(unsigned look=at+1;look<r->count&&look<=r->at+8;look++){if(!player_route_clear53(g,g->x,g->y,r->points[look][0]*8+4,r->points[look][1]*8+4))break;at=look;}r->at=at;wx=r->points[at][0]*8+4;wy=r->points[at][1]*8+4;}
 float dx=wx-g->x,dy=wy-g->y,d=sqrtf(dx*dx+dy*dy),step=combat_walk_speed(g)*dt;if(r->state!=2&&d>range)step=fminf(step,d-fmaxf(0,range-.1f));if(step>d)step=d;if(d<.001f)return 0;float nx=g->x+dx/d*step,ny=g->y+dy/d*step;if(!player_route_clear53(g,g->x,g->y,nx,ny)){r->state=0;return 2;}combat_face(&g->faceX,&g->faceY,dx,dy);int moved=combat_move(g,&g->x,&g->y,nx,ny);if(!moved)r->state=0;return moved;
}

static int player_route_step53(Combat*g,int target,float range,unsigned mode,float dt){if(target<0||target>=MOB_COUNT)return 0;CombatMob*m=g->mobs+target;return player_route_position58(g,target,m->life,m->x,m->y,range,mode,dt);}
