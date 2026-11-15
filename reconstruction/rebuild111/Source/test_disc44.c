/* MIT. Actual disc sprite reader and cache lifetime, no embedded monster blobs. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>
#include <setjmp.h>
#include "combat.h"
#define MYRO_HOST 1
#define MYRO_DISC_ENEMIES44 1
static jmp_buf trap;static int expectedFailure;
static void fail(const char*s){if(expectedFailure)longjmp(trap,1);fprintf(stderr,"%s\n",s);exit(2);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned sz,unsigned raw){(void)n;unsigned char*d=malloc(raw);assert(d);uLongf len=raw;assert(uncompress(d,&len,p,sz)==Z_OK&&len==raw);return d;}
#include "sprites.h"
static unsigned resident44(void){unsigned n=0;for(unsigned k=0;k<MOB_SPEC_COUNT;k++)n+=sprites[k+1].raw!=NULL;return n;}
int main(void){if(getenv("MYRO_DISC_PROBE44")){unsigned char*p=enemy_packed44(0);free(p);puts("PASS44 disc probe");return 0;}sprite_load_all();assert(actorDiscReads==1&&sprites[0].raw&&!resident44());
 for(unsigned i=0;i<ACTOR_VARIANTS;i++){spriteDualGear50=actorBlobs[i].gear>=201?actorBlobs[i].gear:0;unsigned eq=actorBlobs[i].gear==113?(1u<<21):actorBlobs[i].gear==114?(1u<<22):actorBlobs[i].gear==115?(1u<<23):actorBlobs[i].gear==116?(1u<<24):actorBlobs[i].gear==102?64:actorBlobs[i].gear==104?128:actorBlobs[i].gear==105?256:actorBlobs[i].gear==106?512:actorBlobs[i].gear==107?1024:actorBlobs[i].gear==108?2048:actorBlobs[i].gear==109?4096:actorBlobs[i].gear==111?8192:actorBlobs[i].gear==3?32:actorBlobs[i].gear==2?16:actorBlobs[i].gear==1?1:0;sprite_set_equipment(actorBlobs[i].job,eq);assert(spriteJob==actorBlobs[i].job&&spriteGear==actorBlobs[i].gear);unsigned n=actorDiscReads;sprite_set_equipment(spriteJob,eq);assert(n==actorDiscReads);}
 for(unsigned map=0;map<18;map++){sprite_release_enemies();assert(!resident44());sprite_load_map(map);unsigned want=0;for(unsigned k=0;k<MOB_SPEC_COUNT;k++){int needed=0;for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)needed|=spawnDefs[j].map==map&&spawnDefs[j].kind==k;assert((sprites[k+1].raw!=NULL)==needed);want+=needed;}assert(resident44()==want);for(int kind=0;kind<MOB_SPEC_COUNT;kind++){sprite_test_target(map,kind);assert(resident44()<=want+1&&sprites[kind+1].raw);}}
 sprite_release_enemies();assert(!resident44());free(sprites[0].raw);expectedFailure=1;if(!setjmp(trap)){free(enemy_packed44(ENEMY_DISC_COUNT));assert(0);}expectedFailure=0;
 printf("PASS44 disc-only player variants100, species50, maps18; same-class reuse, previous cache eviction, one optional test species; reads %u/%u; invalid index rejected.\n",actorDiscReads,enemyDiscReads44);
}
