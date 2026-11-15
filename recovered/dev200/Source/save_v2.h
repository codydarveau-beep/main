/* SPDX-License-Identifier: MIT
 * Versioned little-endian save format. Never serialize Combat pointers/timers.
 */
#ifndef MYRO_SAVE_V2_H
#define MYRO_SAVE_V2_H
#include "combat.h"
#define V2_BYTES 144
#define V2_MAP 0x08f17d50u /* this prototype's prt_fild08 geometry */
typedef struct {
 uint32_t sequence,rng;
 float x,y,faceX,faceY;
 int hp,sp,level,joblevel,exp,jexp,kills,jellopy,clover,apples;
 int extraItems[5];unsigned equipment;
} V2Character;
static uint32_t v2_u32(const unsigned char*p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void v2_put(unsigned char*p,uint32_t n){p[0]=n;p[1]=n>>8;p[2]=n>>16;p[3]=n>>24;}
static float v2_float(const unsigned char*p){uint32_t u=v2_u32(p);float f;memcpy(&f,&u,4);return f;}
static void v2_put_float(unsigned char*p,float f){uint32_t u;memcpy(&u,&f,4);v2_put(p,u);}
static uint32_t v2_crc(const unsigned char*p,unsigned n){
 uint32_t c=~0u;for(unsigned i=0;i<n;i++){c^=p[i];for(int k=0;k<8;k++)c=(c>>1)^(0xedb88320u&-(c&1u));}return ~c;
}
static void v2_capture(V2Character*s,const Combat*g,uint32_t seq){
 memset(s,0,sizeof(*s));s->sequence=seq;s->rng=g->rng;
 s->x=g->x;s->y=g->y;s->faceX=g->faceX;s->faceY=g->faceY;
 s->hp=g->hp;s->sp=g->sp;s->level=g->level;s->joblevel=g->joblevel;s->exp=g->exp;s->jexp=g->jexp;
 s->kills=g->kills;s->jellopy=g->jellopy;s->clover=g->clover;s->apples=g->apples;
 memcpy(s->extraItems,g->extraItems,sizeof(s->extraItems));s->equipment=g->equipment;
}
static int v2_valid(const V2Character*s){
 if(!s->sequence||s->level<1||s->level>10||s->joblevel<1||s->joblevel>10)return 0;
 if(s->hp<0||s->hp>60+(s->level-1)*10||s->sp<0||s->sp>10+(s->level-1)*2)return 0;
 if(s->exp<0||s->jexp<0)return 0;
 if(s->level==10?s->exp!=0:s->exp>=baseCurve[s->level-1])return 0;
 if(s->joblevel==10?s->jexp!=0:s->jexp>=jobCurve[s->joblevel-1])return 0;
 if(s->kills<0||s->kills>1000000000||s->jellopy<0||s->jellopy>1000000000||s->clover<0||s->clover>1000000000||s->apples<0||s->apples>1000000000)return 0;
 if(!isfinite(s->x)||!isfinite(s->y)||s->x<8||s->y<8||s->x>=3192||s->y>=3192)return 0;
 if(!isfinite(s->faceX)||!isfinite(s->faceY))return 0;
 if(s->equipment&~15u)return 0;
 for(int i=0;i<5;i++)if(s->extraItems[i]<0||s->extraItems[i]>ITEM_STACK_MAX)return 0;
 for(int i=1;i<5;i++)if((s->equipment&(1u<<(i-1)))&&s->extraItems[i]<1)return 0;
 float len=s->faceX*s->faceX+s->faceY*s->faceY;
 return len>.9f&&len<1.1f;
}
static void v2_encode(unsigned char*p,const V2Character*s){
 memset(p,0,V2_BYTES);memcpy(p,"MYROSV02",8);v2_put(p+8,2);v2_put(p+12,V2_BYTES);v2_put(p+16,s->sequence);v2_put(p+20,V2_MAP);
 v2_put_float(p+24,s->x);v2_put_float(p+28,s->y);v2_put_float(p+32,s->faceX);v2_put_float(p+36,s->faceY);
 v2_put(p+40,s->hp);v2_put(p+44,s->sp);v2_put(p+48,s->level);v2_put(p+52,s->joblevel);v2_put(p+56,s->exp);v2_put(p+60,s->jexp);
 v2_put(p+64,s->kills);v2_put(p+68,s->jellopy);v2_put(p+72,s->clover);v2_put(p+76,s->apples);v2_put(p+80,s->rng);
 for(int i=0;i<5;i++)v2_put(p+84+i*4,s->extraItems[i]);
 v2_put(p+104,s->equipment);v2_put(p+108,1);
 v2_put(p+140,v2_crc(p,140));
}
/* 1 valid, 0 corrupt/invalid, -1 unrecognized format: preserve without writes. */
static int v2_decode(V2Character*s,const unsigned char*p){
 if(memcmp(p,"MYROSV02",8)||v2_u32(p+8)!=2||v2_u32(p+12)!=V2_BYTES||v2_u32(p+20)!=V2_MAP)return -1;
 if(v2_crc(p,140)!=v2_u32(p+140)||v2_u32(p+108)!=1)return 0;
 for(int at=112;at<140;at+=4)if(v2_u32(p+at))return 0;
 V2Character t;memset(&t,0,sizeof(t));t.sequence=v2_u32(p+16);t.rng=v2_u32(p+80);
 t.x=v2_float(p+24);t.y=v2_float(p+28);t.faceX=v2_float(p+32);t.faceY=v2_float(p+36);
 t.hp=(int)v2_u32(p+40);t.sp=(int)v2_u32(p+44);t.level=(int)v2_u32(p+48);t.joblevel=(int)v2_u32(p+52);
 t.exp=(int)v2_u32(p+56);t.jexp=(int)v2_u32(p+60);t.kills=(int)v2_u32(p+64);t.jellopy=(int)v2_u32(p+68);t.clover=(int)v2_u32(p+72);t.apples=(int)v2_u32(p+76);
 for(int i=0;i<5;i++)t.extraItems[i]=(int)v2_u32(p+84+i*4);t.equipment=v2_u32(p+104);
 if(!v2_valid(&t))return 0;*s=t;return 1;
}
static void v2_restore(Combat*g,const V2Character*s,float campX,float campY,CombatCanMove canMove,void*world){
 combat_init(g,campX,campY,canMove,world);
 g->x=s->x;g->y=s->y;g->faceX=s->faceX;g->faceY=s->faceY;
 g->hp=s->hp;g->sp=s->sp;g->level=s->level;g->joblevel=s->joblevel;
 g->maxhp=60+(s->level-1)*10;g->maxsp=10+(s->level-1)*2;g->exp=s->exp;g->jexp=s->jexp;
 g->kills=s->kills;g->jellopy=s->jellopy;g->clover=s->clover;g->apples=s->apples;g->rng=s->rng;
 /* Session timers and enemies start fresh; KO is preserved, with A available. */
 g->deadAt=-2;g->lastDamage=0;
 memcpy(g->extraItems,s->extraItems,sizeof(s->extraItems));g->equipment=s->equipment;
}
#endif
