/* MIT. Gameplay and GPU-filter palette regressions. */
#include <assert.h>
#include <zlib.h>
#include "save_store.h"
#include "developer.h"
#include "pause_ui.h"
#include "skin_layout.h"
#include "skin_colors.h"
#include "hud_palette.h"
extern const unsigned char skin_image[];extern const unsigned int skin_image_raw,skin_image_size;
static int fence(void*c,float x,float y,float nx,float ny){(void)c;(void)x;(void)y;return nx>=1480&&nx<3200&&ny>8&&ny<3192;}
static void ready(Combat*g){g->sp=g->maxsp;g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));}
int main(void){Combat g;combat_init(&g,1500,1500,fence,NULL);dev_class_preset(&g,4);memset(g.mobs,0,sizeof(g.mobs));g.faceX=1;g.faceY=0;float x=g.x;int sp=g.sp;assert(skill_cast(&g,47,0,0));assert(g.x==1480&&g.faceX==1&&g.sp==sp-7);ready(&g);sp=g.sp;assert(!skill_cast(&g,47,0,0)&&g.sp==sp);
 dev_class_preset(&g,1);assert(g.ranks[40]&&g.ranks[41]&&g.ranks[42]);memset(g.mobs,0,sizeof(g.mobs));g.hp=g.maxhp/4-1;int damage=combat_physical(&g);ready(&g);assert(skill_cast(&g,46,0,0)&&combat_berserk_active(&g)&&combat_physical(&g)==damage*132/100);g.hp=g.maxhp;assert(!combat_berserk_active(&g));ready(&g);assert(skill_cast(&g,46,0,0)&&!g.autoBerserk);
 // Walking recovery requires its passive; stationary natural regen remains.
 g.hp=g.maxhp-10;g.lastDamage=-100;g.time=10;g.ranks[40]=0;for(int i=0;i<100;i++)combat_tick(&g,.05f,0,1);assert(g.hp==g.maxhp-10);g.ranks[40]=1;for(int i=0;i<100;i++)combat_tick(&g,.05f,0,1);assert(g.hp>g.maxhp-10);
 // Quest unlocks cost no ordinary points, including at zero points.
 g.ranks[40]=0;int points=g.skillPoints;assert(skill_learn(&g,44)&&g.skillPoints==points);SavedCharacter s;save_capture(&s,&g,1);assert(save_valid(&s));unsigned char raw[SAVE_BYTES];save_encode(raw,&s);assert(save_decode(&s,raw)==1);
 // Fatal Blow: no more guaranteed stun at Bash1; Bash10 can proc with passive.
 g.canMove=NULL;g.x=g.y=1500;g.ranks[0]=1;g.debugFreeze=1;CombatMob*m=&g.mobs[0];memset(m,0,sizeof(*m));m->enabled=m->training=1;m->kind=5;m->hp=1000000;m->x=1508;m->y=1500;g.target=0;ready(&g);assert(skill_cast(&g,2,0,0)&&!m->stun);g.ranks[0]=10;int procs=0;for(int i=0;i<300;i++){ready(&g);m->stun=0;assert(skill_cast(&g,2,0,0));procs+=m->stun>0;}assert(procs>0&&procs<100);m->testTraits=3;ready(&g);m->stun=0;assert(skill_cast(&g,2,0,0)&&!m->stun);
 uint32_t*p=malloc(skin_image_raw);uLongf n=skin_image_raw;assert(uncompress((void*)p,&n,skin_image,skin_image_size)==Z_OK);for(unsigned i=0;i<sizeof(skinColors)/sizeof(*skinColors);i++){float u,v;hud_solid_uv(i,&u,&v);int xx=(int)floorf(u-.5f),yy=(int)floorf(v-.5f);for(int y=yy;y<=yy+1;y++)for(int x=xx;x<=xx+1;x++)assert(p[y*512+x]==skinColors[i]);}free(p);
 PauseUI ui={.tab=0,.row=2};assert(pause_count(0)==4&&pause_input(&ui,2)==PA_HELP);ui.tab=2;ui.row=1;assert(pause_input(&ui,2)==PA_TRAVEL);pause_input(&ui,512);assert(ui.tab==0);
 puts("PASS opaque filtered palette/red;3-category menu; Back Sliding collision/SP/facing; Auto Berserk threshold/toggle; moving recovery eligibility; free quest unlocks/current save; Fatal Blow rank/chance/boss guards");}
