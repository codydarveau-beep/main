#include "companion_progress200.h"
int companion_decode200(const unsigned char*in,unsigned bytes,unsigned char*out){return party_progress_decode200(in,bytes,out);}
int companion_put200(unsigned char*out,unsigned id,const unsigned*v){PartyGrowth200 m={v[0],v[1],v[2],v[3],v[4],v[5],v[6]};return party_progress_put200(out,id,&m);}
