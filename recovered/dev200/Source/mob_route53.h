/* MIT. One shared bounded flow field around the player; never A* per monster.
 *64node expansions/tick, fixed16.5KiB workspace, ordinary movement unchanged.
 *Only blocked pursuers consult it; every chosen segment rechecks collision. */
#define MOB_FLOW_SIDE53 65
#define MOB_FLOW_NODES53 4225
static struct {Combat*owner;unsigned map;int cx,cy,ox,oy;unsigned head,tail;uint16_t distance[MOB_FLOW_NODES53],queue[MOB_FLOW_NODES53];float refreshed,demandUntil;} mobFlow53;
static void mob_flow_tick53(Combat*g){if(mobFlow53.owner==g&&mobFlow53.demandUntil<=g->time)return;
 int cx=(int)floorf(g->x/8),cy=(int)floorf(g->y/8);
 if(g->time<mobFlow53.refreshed||mobFlow53.owner!=g||mobFlow53.map!=g->mapId||abs(cx-mobFlow53.cx)>2||abs(cy-mobFlow53.cy)>2||g->time-mobFlow53.refreshed>3){mobFlow53.owner=g;mobFlow53.map=g->mapId;mobFlow53.cx=cx;mobFlow53.cy=cy;mobFlow53.ox=cx-32;mobFlow53.oy=cy-32;mobFlow53.head=0;mobFlow53.tail=1;mobFlow53.queue[0]=32*65+32;memset(mobFlow53.distance,255,sizeof(mobFlow53.distance));mobFlow53.distance[32*65+32]=0;mobFlow53.refreshed=g->time;}
 for(unsigned work=0;work<64&&mobFlow53.head<mobFlow53.tail;work++){unsigned node=mobFlow53.queue[mobFlow53.head++];int x=node%65,y=node/65;float wx=(mobFlow53.ox+x)*8+4,wy=(mobFlow53.oy+y)*8+4;
  for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){if(!dx&&!dy)continue;int xx=x+dx,yy=y+dy;if(xx<0||yy<0||xx>=65||yy>=65)continue;unsigned next=yy*65+xx;if(mobFlow53.distance[next]!=65535)continue;float nx=(mobFlow53.ox+xx)*8+4,ny=(mobFlow53.oy+yy)*8+4;if(!player_route_clear53(g,nx,ny,wx,wy))continue;mobFlow53.distance[next]=mobFlow53.distance[node]+1;mobFlow53.queue[mobFlow53.tail++]=next;}
 }
}
static int mob_flow_step53(Combat*g,CombatMob*m,float step,float*nx,float*ny){
 mobFlow53.demandUntil=g->time+1;if(g->time<mobFlow53.refreshed||mobFlow53.owner!=g||mobFlow53.map!=g->mapId)return 0;int x=(int)floorf(m->x/8)-mobFlow53.ox,y=(int)floorf(m->y/8)-mobFlow53.oy;if(x<1||y<1||x>=64||y>=64)return 0;unsigned best=mobFlow53.distance[y*65+x];float wx=0,wy=0;
 for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){unsigned d=mobFlow53.distance[(y+dy)*65+x+dx];if(d>=best)continue;float tx=(mobFlow53.ox+x+dx)*8+4,ty=(mobFlow53.oy+y+dy)*8+4;if(!player_route_clear53(g,m->x,m->y,tx,ty))continue;best=d;wx=tx;wy=ty;}
 if(!wx&&!wy)return 0;float dx=wx-m->x,dy=wy-m->y,dist=sqrtf(dx*dx+dy*dy);if(dist<.001f)return 0;if(step>dist)step=dist;*nx=m->x+dx*step/dist;*ny=m->y+dy*step/dist;return 1;
}
