/* MIT. Source animation chain, exact damage cadence and standing/death depth. */
#define main prior_class48_tests
#include "test_classes48.c"
#undef main
#include "projection.h"
typedef struct {unsigned actions;unsigned*meta;} PoseSprite50c;
#define SparseSprite PoseSprite50c
#include "attack_sequence50c.h"
#undef SparseSprite
int main(void){
 static Combat g;prepare48(&g,12);g.attackAt=-100;g.lastCast=g.time=0;g.fxSkill=131;
 unsigned meta[24*3]={0};for(int d=0;d<8;d++)meta[(16+d)*3+1]=8;
 PoseSprite50c s={24,meta};float elapsed,duration;
 for(int d=0;d<8;d++){
  g.time=.225f;assert(sonic_pose50c(&g,&s,d,&elapsed,&duration)&&fabsf(elapsed-.225f)<.0001f&&duration==.45f);
  for(int action=0;action<7;action++){g.time=.45f+action*.24f+.12f;assert(sonic_pose50c(&g,&s,d,&elapsed,&duration)&&fabsf(elapsed-.12f)<.0001f&&fabsf(duration-.24f)<.0001f);}
  g.time=2.131f;assert(!sonic_pose50c(&g,&s,d,&elapsed,&duration));
 }
 g.time=.6f;g.moving=1;assert(!sonic_pose50c(&g,&s,0,&elapsed,&duration));g.moving=0;g.hp=0;assert(!sonic_pose50c(&g,&s,0,&elapsed,&duration));g.hp=g.maxhp;g.attackAt=.55f;assert(!sonic_pose50c(&g,&s,0,&elapsed,&duration));
 // Real skill entry keeps eight damage events, resources and source cadence.
 prepare48(&g,12);CombatMob*m=&g.mobs[MOB_COUNT-1];int hp=m->hp,sp=g.sp;float castAt=g.time;assert(skill_cast(&g,131,m->x,m->y)&&g.sp==sp-34);
 assert(g.bursts49[0].hits==8&&fabsf(g.bursts49[0].gap-.2f)<.00001f);int total=g.bursts49[0].damage;
 for(int i=1;i<8;i++){for(int k=0;k<19;k++)combat_tick(&g,.01f,0,0);assert(g.bursts49[0].done==i);combat_tick(&g,.01f,0,0);assert(g.bursts49[0].done==i+1);}
 assert(m->hp==hp-total&&!g.bursts49[0].active);
 int hitSounds=0;for(unsigned q=g.soundRead;q!=g.soundWrite;q++)if(g.soundEvents[q%32]==0){assert(fabsf(g.soundDue[q%32]-(castAt+.02f+.2f*hitSounds))<.0001f);hitSounds++;}assert(hitSounds==8);

 for(int yaw=0;yaw<16;yaw++)for(int pitch=0;pitch<8;pitch++){
  float matrix[16],corners[2];world_camera(matrix,1500,1500,0,yaw*.4f,.52f+pitch*.08f,1.2f);float slope=sprite_depth_slope50(matrix),foot=WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS;
  sprite_depth_corners50c(foot,40,400,245,slope,0,corners);assert(corners[0]==sprite_upright_cached50(foot,40,245,slope)&&corners[1]==sprite_upright_cached50(foot,400,245,slope));
  sprite_depth_corners50c(foot,40,400,245,slope,1,corners);assert(corners[0]==foot&&corners[1]==foot);
 }
 puts("PASS eight Sonic Blow actions and 200 ms damage boundaries, movement/KO/new-attack interruption, exact total/SP, unchanged standing depth and planar source fading copies. Target Willow appearance still needs play testing.");
}
