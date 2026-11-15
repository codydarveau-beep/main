/* Original released six-game native logic, recovered as relocatable assembly.
 * The Xbox executes native code, never an instruction emulator. */
#ifndef MYRO_GUILD_ARCADE194_H
#define MYRO_GUILD_ARCADE194_H
#include <stddef.h>
#define AR194_W 23
#define AR194_H 17
#define AR194_CELLS (AR194_W*AR194_H)
#define ARCADE_CELLS194 AR194_CELLS
enum{AR194_PONG,AR194_PATROL,AR194_SNAKE,AR194_BREAKER,AR194_PUZZLE,AR194_MAZE};
typedef struct{float x,y,vx,vy;unsigned on;}ArcadeShot194;
typedef struct{
 union{unsigned game,kind;};unsigned rng,score,lives,level,over,won,paused,submitted;
 float time,clock,accumulator,fire,x,y,vx,vy,paddle,opponent;
 unsigned char board[AR194_CELLS];unsigned short snake[AR194_CELLS],length,food;
 unsigned dir,nextDir,turnLock;unsigned char tiles[16],cursor,blank;
 unsigned short ghosts[4];unsigned ghostDirs[4],dots,launched;float powerUntil;
 ArcadeShot194 shots[24];
}Arcade194;
typedef Arcade194 GuildArcade194;
typedef char ArcadeWireBudget197[sizeof(Arcade194)==1804&&offsetof(Arcade194,shots)==1324&&offsetof(Arcade194,tiles)==1268?1:-1];
static const char*arcade_names194[]={"Poring Pong","Peco Patrol","Herb Trail","Pupa Breaker","Kafra's Lost Parcels","Moonlight Munch"};
#ifdef MYRO_HOST
/* Host-only adapter executes the identical assembled source in an isolated CPU
 * harness; explicitly linked by validation runners, never part of the game. */
extern void arcade_host197(unsigned operation,void*state,unsigned argument,float dt);
static void arcade_start_seed196(Arcade194*a,unsigned game,unsigned seed){memset(a,0,sizeof(*a));a->game=game;arcade_host197(0,a,seed,0);}
static void arcade_input194(Arcade194*a,unsigned pressed){arcade_host197(1,a,pressed,0);}
static void arcade_tick_held197(Arcade194*a,unsigned held,float dt){arcade_host197(2,a,held,dt);}
#else
extern Arcade194 arcade197_state;
extern void arcade197_reset(unsigned game,unsigned seed);
extern void arcade197_input(unsigned pressed);
extern void arcade197_tick(unsigned held,float dt);
static void arcade_start_seed196(Arcade194*a,unsigned game,unsigned seed){arcade197_reset(game,seed);memcpy(a,&arcade197_state,sizeof(*a));}
static void arcade_input194(Arcade194*a,unsigned pressed){memcpy(&arcade197_state,a,sizeof(*a));arcade197_input(pressed);memcpy(a,&arcade197_state,sizeof(*a));}
static void arcade_tick_held197(Arcade194*a,unsigned held,float dt){memcpy(&arcade197_state,a,sizeof(*a));arcade197_tick(held,dt);memcpy(a,&arcade197_state,sizeof(*a));}
#endif
static void arcade_start194(Arcade194*a,unsigned kind){arcade_start_seed196(a,kind,0x194cafeu+kind);}
static void arcade_tick194(Arcade194*a,unsigned milliseconds){arcade_tick_held197(a,0,milliseconds/1000.f);}
#endif
