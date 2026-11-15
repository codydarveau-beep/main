/* SPDX-License-Identifier: MIT
 * Versioned little-endian save format. Never serialize Combat pointers/timers.
 */
#ifndef MYRO_SAVE_V3_H
#define MYRO_SAVE_V3_H
#include "combat.h"
#define V3_BYTES 144
#define V3_MAP 0x08f17d50u /* this prototype's prt_fild08 geometry */
typedef struct {
 uint32_t sequence,rng;
 float x,y,faceX,faceY;
 int hp,sp,level,joblevel,exp,jexp,kills,jellopy,clover,apples;
 int extraItems[5];unsigned equipment;
 unsigned char hotbar[8];unsigned hotSlot;
} V3Character;
static uint32_t v3_u32(const unsigned char*p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void v3_put(unsigned char*p,uint32_t n){p[0]=n;p[1]=n>>8;p[2]=n>>16;p[3]=n>>24;}
static float v3_float(const unsigned char*p){uint32_t u=v3_u32(p);float f;memcpy(&f,&u,4);return f;}
static void v3_put_float(unsigned char*p,float f){uint32_t u;memcpy(&u,&f,4);v3_put(p,u);}
static uint32_t v3_crc(const unsigned char*p,unsigned n){
 uint32_t c=~0u;for(unsigned i=0;i<n;i++){c^=p[i];for(int k=0;k<8;k++)c=(c>>1)^(0xedb88320u&-(c&1u));}return ~c;
}
static void v3_capture(V3Character*s,const Combat*g,uint32_t seq){
 memset(s,0,sizeof(*s));s->sequence=seq;s->rng=g->rng;
 s->x=g->x;s->y=g->y;s->faceX=g->faceX;s->faceY=g->faceY;
 s->hp=g->hp;s->sp=g->sp;s->level=g->level;s->joblevel=g->joblevel;s->exp=g->exp;s->jexp=g->jexp;
 s->kills=g->kills;s->jellopy=g->jellopy;s->clover=g->clover;s->apples=g->apples;
 memcpy(s->extraItems,g->extraItems,sizeof(s->extraItems));s->equipment=g->equipment;memcpy(s->hotbar,g->hotbar,8);s->hotSlot=g->hotSlot;
}
static int v3_valid(const V3Character*s){
 if(!s->sequence||s->level<1||s->level>10||s->joblevel<1||s->joblevel>10)return 0;
 if(s->hp<0||s->hp>60+(s->level-1)*10||s->sp<0||s->sp>10+(s->level-1)*2)return 0;
 if(s->exp<0||s->jexp<0)return 0;
 if(s->level==10?s->exp!=0:s->exp>=baseCurve[s->level-1])return 0;
 if(s->joblevel==10?s->jexp!=0:s->jexp>=jobCurve[s->joblevel-1])return 0;
 if(s->kills<0||s->kills>1000000000||s->jellopy<0||s->jellopy>1000000000||s->clover<0||s->clover>1000000000||s->apples<0||s->apples>1000000000)return 0;
 if(!isfinite(s->x)||!isfinite(s->y)||s->x<8||s->y<8||s->x>=3192||s->y>=3192)return 0;
 if(!isfinite(s->faceX)||!isfinite(s->faceY))return 0;
 if(s->equipment&~15u||s->hotSlot>=8)return 0;
 for(int i=0;i<8;i++)if(!skill_id_valid(s->hotbar[i]))return 0;
 for(int i=0;i<5;i++)if(s->extraItems[i]<0||s->extraItems[i]>ITEM_STACK_MAX)return 0;
 for(int i=1;i<5;i++)if((s->equipment&(1u<<(i-1)))&&s->extraItems[i]<1)return 0;
 float len=s->faceX*s->faceX+s->faceY*s->faceY;
 return len>.9f&&len<1.1f;
}
static void v3_encode(unsigned char*p,const V3Character*s){
 memset(p,0,V3_BYTES);memcpy(p,"MYROSV03",8);v3_put(p+8,3);v3_put(p+12,V3_BYTES);v3_put(p+16,s->sequence);v3_put(p+20,V3_MAP);
 v3_put_float(p+24,s->x);v3_put_float(p+28,s->y);v3_put_float(p+32,s->faceX);v3_put_float(p+36,s->faceY);
 v3_put(p+40,s->hp);v3_put(p+44,s->sp);v3_put(p+48,s->level);v3_put(p+52,s->joblevel);v3_put(p+56,s->exp);v3_put(p+60,s->jexp);
 v3_put(p+64,s->kills);v3_put(p+68,s->jellopy);v3_put(p+72,s->clover);v3_put(p+76,s->apples);v3_put(p+80,s->rng);
 for(int i=0;i<5;i++)v3_put(p+84+i*4,s->extraItems[i]);
 v3_put(p+104,s->equipment);v3_put(p+108,1);
 memcpy(p+112,s->hotbar,8);v3_put(p+120,s->hotSlot);
 v3_put(p+140,v3_crc(p,140));
}
/* 1 valid, 0 corrupt/invalid, -1 unrecognized format: preserve without writes. */
static int v3_decode(V3Character*s,const unsigned char*p){
 if(memcmp(p,"MYROSV03",8)||v3_u32(p+8)!=3||v3_u32(p+12)!=V3_BYTES||v3_u32(p+20)!=V3_MAP)return -1;
 if(v3_crc(p,140)!=v3_u32(p+140)||v3_u32(p+108)!=1)return 0;
 for(int at=124;at<140;at+=4)if(v3_u32(p+at))return 0;
 V3Character t;memset(&t,0,sizeof(t));t.sequence=v3_u32(p+16);t.rng=v3_u32(p+80);
 t.x=v3_float(p+24);t.y=v3_float(p+28);t.faceX=v3_float(p+32);t.faceY=v3_float(p+36);
 t.hp=(int)v3_u32(p+40);t.sp=(int)v3_u32(p+44);t.level=(int)v3_u32(p+48);t.joblevel=(int)v3_u32(p+52);
 t.exp=(int)v3_u32(p+56);t.jexp=(int)v3_u32(p+60);t.kills=(int)v3_u32(p+64);t.jellopy=(int)v3_u32(p+68);t.clover=(int)v3_u32(p+72);t.apples=(int)v3_u32(p+76);
 for(int i=0;i<5;i++)t.extraItems[i]=(int)v3_u32(p+84+i*4);t.equipment=v3_u32(p+104);
 memcpy(t.hotbar,p+112,8);t.hotSlot=v3_u32(p+120);
 if(!v3_valid(&t))return 0;*s=t;return 1;
}
static void v3_restore(Combat*g,const V3Character*s,float campX,float campY,CombatCanMove canMove,void*world){
 combat_init(g,campX,campY,canMove,world);
 g->x=s->x;g->y=s->y;g->faceX=s->faceX;g->faceY=s->faceY;
 g->hp=s->hp;g->sp=s->sp;g->level=s->level;g->joblevel=s->joblevel;
 g->maxhp=60+(s->level-1)*10;g->maxsp=10+(s->level-1)*2;g->exp=s->exp;g->jexp=s->jexp;
 g->kills=s->kills;g->jellopy=s->jellopy;g->clover=s->clover;g->apples=s->apples;g->rng=s->rng;
 /* Session timers and enemies start fresh; KO is preserved, with A available. */
 g->deadAt=-2;g->lastDamage=0;
 memcpy(g->extraItems,s->extraItems,sizeof(s->extraItems));g->equipment=s->equipment;memcpy(g->hotbar,s->hotbar,8);g->hotSlot=s->hotSlot;
}
#endif
