#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "guild_arcade194.h"
static void valid(const Arcade194*p){unsigned seen=0,inversions=0;for(unsigned i=0;i<16;i++){assert(p->tiles[i]<16);assert(!(seen&(1u<<p->tiles[i])));seen|=1u<<p->tiles[i];if(p->tiles[i])for(unsigned j=i+1;j<16;j++)if(p->tiles[j]&&p->tiles[i]>p->tiles[j])inversions++;}assert(seen==65535&&!p->tiles[p->blank]&&((inversions+4-p->blank/4)&1)==1);}
int main(void){Arcade194 a,b;arcade_start_seed196(&a,4,1);arcade_start_seed196(&b,4,1);assert(!memcmp(&a,&b,sizeof a));arcade_input194(&a,16);assert(a.paused);b=a;arcade_tick194(&a,500);arcade_input194(&a,2|8192);assert(!memcmp(&a,&b,sizeof a));arcade_input194(&a,16);assert(!a.paused);
for(unsigned seed=1;seed<=10000;seed++){arcade_start_seed196(&a,4,seed);valid(&a);assert(!a.won&&!a.over&&!a.score);for(unsigned i=0;i<16;i++){a.cursor=i;b=a;arcade_input194(&a,2);valid(&a);if(a.blank==b.blank)assert(!memcmp(&a,&b,sizeof a));}}
arcade_start_seed196(&a,4,7);for(unsigned i=0;i<15;i++)a.tiles[i]=(unsigned char)(i+1);a.tiles[14]=0;a.tiles[15]=15;a.blank=14;a.cursor=15;a.score=0;arcade_input194(&a,2);assert(a.won&&a.over&&a.score==1);valid(&a);puts("PASS recovered original sliding-puzzle native logic: solvable resets, legal/illegal slides, pause and completion scoring. HOST CPU replay only.");}
