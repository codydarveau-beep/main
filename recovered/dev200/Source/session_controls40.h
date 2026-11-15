/* MIT. Session-only gestures and delayed practice hit; no save format changes. */
#ifndef MYRO_SESSION_CONTROLS40_H
#define MYRO_SESSION_CONTROLS40_H
typedef struct{float elapsed;int armed,fired;} StartShortcut;
static int start_shortcut_tick(StartShortcut*s,int down,float dt,int entered,int paused){if(entered){s->elapsed=0;s->armed=paused;s->fired=0;}if(!down||!paused){memset(s,0,sizeof(*s));return 0;}if(s->armed&&!s->fired){s->elapsed+=dt;if(s->elapsed>=.6f){s->fired=1;return 1;}}return 0;}
typedef struct{float left;unsigned map;int active;} RangedTest;
static void ranged_test_arm(RangedTest*t,const Combat*g){t->left=1;t->map=g->mapId;t->active=1;}
static int ranged_test_tick(RangedTest*t,Combat*g,float dt,int playing){if(!t->active)return 0;if(g->hp<=0||g->mapId!=t->map){t->active=0;return 0;}if(!playing)return 0;t->left-=dt;if(t->left>0)return 0;t->active=0;combat_ranged_hit(g,20);return 1;}
/* Menus own navigation; only START suspends the simulation. */
static void session_world_tick43(Combat*g,float dt,int paused,int ownsInput,float dx,float dy){if(!paused)combat_tick(g,dt,ownsInput?0:dx,ownsInput?0:dy);}
#endif
