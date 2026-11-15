/* MIT. Three bounded flame barriers; gameplay uses source-derived fire traits. */
#include "mob_flame_traits.h"
static int combat_barrier_slot(const Combat*g){for(int i=0;i<COMBAT_BARRIERS;i++)if(g->barriers[i].expires<=g->time)return i;return -1;}
static void combat_knockback(Combat*g,int i,float dx,float dy,float distance){
 CombatMob*m=&g->mobs[i];if(m->hp<=0||combat_racer_kind164(m->kind)||mobKnockImmune[m->kind])return;float d=sqrtf(dx*dx+dy*dy);if(d<.001f){dx=g->faceX;dy=g->faceY;d=sqrtf(dx*dx+dy*dy);}if(d<.001f)return;dx/=d;dy/=d;
 for(float step=0;step<distance;step+=2){float n=distance-step;if(n>2)n=2;float nx=m->x+dx*n,ny=m->y+dy*n;if(g->canMove&&!g->canMove(g->world,m->x,m->y,nx,ny))break;m->x=nx;m->y=ny;}
}
static void combat_barriers_tick(Combat*g){
 if(g->hp<=0){memset(g->barriers,0,sizeof(g->barriers));g->angelusLeft=0;return;}
 for(int w=0;w<COMBAT_BARRIERS;w++){CombatBarrier*f=&g->barriers[w];if(f->expires<=g->time||g->time+.0001f<f->nextAt)continue;f->nextAt=g->time+.15f;int hit=0,left=0;
  for(int c=0;c<3;c++){float x=f->x+(c-1)*f->axisX*8,y=f->y+(c-1)*f->axisY*8;if(f->hits[c]<=0)continue;
   for(int i=0;i<MOB_COUNT&&f->hits[c]>0;i++){CombatMob*m=&g->mobs[i];if(!m->enabled||m->hp<=0||class_field_at48(g,104,m->x,m->y)||fabsf(m->x-x)>5||fabsf(m->y-y)>5||(g->canAim&&!g->canAim(g->world,x,y,m->x,m->y)))continue;
    int noPush=m->frozenLeft<=0&&mobFlameNoPush[m->kind];int damage=f->power*class_attack_rate48(g,m,3)/100;if(damage<=0)continue;if(mobSpecs[m->kind].flags&16)damage=1;damage=combat_magic_def48(m,damage,1);skill_hit(g,i,damage,0);f->total[i]+=damage;combat_combo(g,&f->totalEvent[i],m->x,m->y,f->total[i]);f->hits[c]--;hit=1;if(!noPush)combat_knockback(g,i,f->awayX,f->awayY,16);
   }left+=f->hits[c];
  }if(hit)combat_sound(g,0);if(!left)f->expires=g->time;
 }
}
static void combat_barrier_start(Combat*g,float x,float y,int rank){
 int slot=combat_barrier_slot(g);if(slot<0)return;CombatBarrier*f=&g->barriers[slot];memset(f,0,sizeof(*f));f->x=x;f->y=y;
 float dx=x-g->x,dy=y-g->y,d=sqrtf(dx*dx+dy*dy);if(d<.01f){dx=g->faceX;dy=g->faceY;d=sqrtf(dx*dx+dy*dy);}if(d<.01f){dx=0;dy=1;d=1;}f->awayX=dx/d;f->awayY=dy/d;
 /* Three cells perpendicular to the cast direction. Diagonal walls use the same bounded shape. */
 if(fabsf(dx)>=fabsf(dy)){f->axisX=0;f->axisY=1;}else{f->axisX=1;f->axisY=0;}
 f->expires=g->time+4+rank;f->nextAt=g->time;f->power=combat_magic_power48(g)/2;
 for(int c=0;c<3;c++){float xx=x+(c-1)*f->axisX*8,yy=y+(c-1)*f->axisY*8;f->hits[c]=(!g->canMove||g->canMove(g->world,xx,yy,xx,yy))?4+rank:0;}combat_barriers_tick(g);
}
