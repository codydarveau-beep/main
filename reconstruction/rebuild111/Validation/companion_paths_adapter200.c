#include "companion_paths200.h"
unsigned promote200(unsigned i,unsigned j,unsigned l,unsigned c){return party_growth_promotion200(i,j,l,c);}
void stats200(unsigned i,unsigned j,unsigned l,unsigned*out){unsigned char s[6];if(!party_growth_stats200(i,j,l,s,out+6,out+7))abort();for(unsigned k=0;k<6;k++)out[k]=s[k];}
