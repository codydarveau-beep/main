/* MIT. Reproductions of the Test49 review: travel, pursuit and empty impacts. */
#define main original_world_review50
#include "test_world43.c"
#undef main
#include "projection.h"
#include "window_ui.h"
int main(void){
 assert(world_activate(11));unsigned steps=0;
 for(int col=119;col<=124;col++)for(int dir=-1;dir<=1;dir+=2){float x=col*8+4,y=(dir<0?46.5f:30.5f)*8;for(int i=0;i<128;i++){assert(world_can_move(NULL,x,y,x,y+dir));y+=dir;steps++;}}
 /* Posts and the stream bank remain blocked. */
 assert(!allowed(118.5f*8,41.5f*8)&&!allowed(125.5f*8,41.5f*8));world_release();
 Combat g;combat_init(&g,1500,1500,NULL,NULL);memset(g.mobs,0,sizeof(g.mobs));int kind=0;while(kind<MOB_SPEC_COUNT&&(!(mobSpecs[kind].flags&2)||!(mobSpecs[kind].flags&1)))kind++;assert(kind<MOB_SPEC_COUNT);
 CombatMob*m=&g.mobs[0];m->enabled=1;m->kind=kind;m->hp=mobSpecs[kind].hp;m->homeX=200;m->homeY=200;m->x=g.x-80;m->y=g.y;m->aggro=1;m->cooldown=100;m->faceX=1;
 float original=m->x;for(int i=0;i<100;i++)combat_tick(&g,.01f,0,0);assert(m->aggro&&m->x>original+8);
 /* A distant spawn is not an idle movement destination either. */
 m->aggro=0;m->x=1500;m->y=1500;g.x=2200;g.y=2200;m->wanderAt=g.time+10;m->wanderUntil=g.time+1;m->wanderX=1;m->wanderY=0;original=m->x;combat_tick(&g,.05f,0,0);assert(m->x>original&&!m->returningHome45);
 memset(g.mobs,0,sizeof(g.mobs));memset(g.fields,0,sizeof(g.fields));g.soundRead=g.soundWrite=0;CombatField*f=&g.fields[0];f->secondId=75;f->remaining=f->expected=3;f->rank=5;f->power=200;f->nextAt=g.time;f->createdAt45=g.time;unsigned sound=0;
 for(int i=0;i<3;i++){combat_fields_tick(&g);assert(combat_next_sound(&g,&sound)&&sound==skill_sound_id49(75));assert(!combat_next_sound(&g,&sound));g.time+=1;}
 assert(!f->remaining&&!g.damageNext);
 g.jobId=9;WindowUI u={0};ui_open(&u,UI_SKILLS,1);assert(u.skillPage==1);u.choice[UI_SKILLS]=2;ui_input(&u,&g,16384);assert(u.skillPage==1&&u.choice[UI_SKILLS]==2);
 unsigned planes=0;
 for(int yaw=0;yaw<32;yaw++)for(int t=0;t<8;t++){float tilt=.52f+t*.08f,zoom=.85f+t*.1f,mat[16];world_camera(mat,1500,1600,20,yaw*.2f,tilt,zoom);float px,py,footY;world_project(mat,1500,1600,20,&px,&footY);
  for(int h=0;h<=64;h+=4){world_project(mat,1500,1600,20+h,&px,&py);float actual=mat[8]*1500+mat[9]*1600+mat[10]*(20+h)+mat[11]-WORLD_SPRITE_BIAS;float computed=sprite_upright_depth50(WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS,py,footY,zoom,tilt);assert(fabsf(actual-computed)<3);planes++;}
 }
 printf("PASS50 Payon gateway %u unit steps in six columns/both directions with blocked posts; pursuit/idle roam far from spawn; three empty meteor impact sounds; class-only skill page; %u upright actor depth projections.\n",steps,planes);
}
