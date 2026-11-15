/* Reconstructed missing engine from retained sliding-puzzle rules.
 * Complete playable 15-puzzle; not claimed to be original engine source. */
#ifndef MYRO_ARCADE_PUZZLE196_H
#define MYRO_ARCADE_PUZZLE196_H
typedef struct{unsigned char tiles[16];unsigned cursor,blank,moves,won;}ArcadePuzzle196;
static int puzzle_solved196(const ArcadePuzzle196*p){for(unsigned i=0;i<15;i++)if(p->tiles[i]!=i+1)return 0;return !p->tiles[15];}
static void puzzle_swap196(ArcadePuzzle196*p,unsigned cell){p->tiles[p->blank]=p->tiles[cell];p->tiles[cell]=0;p->blank=cell;}
static unsigned puzzle_rng196(unsigned*rng){*rng=*rng*1664525u+1013904223u;return*rng;}
static void puzzle_reset196(ArcadePuzzle196*p,unsigned*seed){memset(p,0,sizeof(*p));for(unsigned i=0;i<15;i++)p->tiles[i]=(unsigned char)(i+1);p->blank=15;unsigned previous=16;
 for(unsigned step=0;step<256;step++){unsigned choices[4],n=0,b=p->blank;
  if(b>=4&&b-4!=previous)choices[n++]=b-4;if(b<12&&b+4!=previous)choices[n++]=b+4;if(b%4&&b-1!=previous)choices[n++]=b-1;if(b%4<3&&b+1!=previous)choices[n++]=b+1;
  unsigned to=choices[puzzle_rng196(seed)%n];previous=b;puzzle_swap196(p,to);
 }
 if(puzzle_solved196(p))puzzle_swap196(p,p->blank%4?p->blank-1:p->blank+1);
 p->cursor=p->blank;
}
static int puzzle_input196(ArcadePuzzle196*p,unsigned pressed){if(p->won)return 0;unsigned c=p->cursor;
 if(pressed&1024){if(c>=4)c-=4;}else if(pressed&2048){if(c<12)c+=4;}else if(pressed&4096){if(c%4)c--;}else if(pressed&8192){if(c%4<3)c++;}p->cursor=c;
 if(!(pressed&2)||c==p->blank)return 0;unsigned b=p->blank;int adjacent=(c/4==b/4&&(c+1==b||b+1==c))||(c+4==b||b+4==c);if(!adjacent)return 0;
 puzzle_swap196(p,c);if(p->moves<~0u-1)p->moves++;p->won=(unsigned)puzzle_solved196(p);return 1;
}
static unsigned puzzle_best196(const ArcadePuzzle196*p){return p->won?10000u/(p->moves+1u):0u;}
#endif
