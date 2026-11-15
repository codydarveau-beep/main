/* SPDX-License-Identifier: MIT
 * Versioned little-endian save format. Never serialize Combat pointers/timers.
 */
#ifndef MYRO_SAVE_V4_H
#define MYRO_SAVE_V4_H
#include "combat.h"
#define V4_BYTES 144
#define V4_MAP 0x08f17d50u /* fixed world-set identifier; mapId selects a resident field */
typedef struct {
 uint32_t sequence,rng;
 float x,y,faceX,faceY;
 int hp,sp,level,joblevel,exp,jexp,kills,jellopy,clover,apples;
 int extraItems[5];unsigned equipment;
 unsigned char hotbar[8];unsigned hotSlot,mapId;
} V4Character;
static uint32_t v4_u32(const unsigned char*p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void v4_put(unsigned char*p,uint32_t n){p[0]=n;p[1]=n>>8;p[2]=n>>16;p[3]=n>>24;}
static float v4_float(const unsigned char*p){uint32_t u=v4_u32(p);float f;memcpy(&f,&u,4);return f;}
static void v4_put_float(unsigned char*p,float f){uint32_t u;memcpy(&u,&f,4);v4_put(p,u);}
static uint32_t v4_crc(const unsigned char*p,unsigned n){
 uint32_t c=~0u;for(unsigned i=0;i<n;i++){c^=p[i];for(int k=0;k<8;k++)c=(c>>1)^(0xedb88320u&-(c&1u));}return ~c;
}
static void v4_capture(V4Character*s,const Combat*g,uint32_t seq){
 memset(s,0,sizeof(*s));s->sequence=seq;s->rng=g->rng;
 s->x=g->x;s->y=g->y;s->faceX=g->faceX;s->faceY=g->faceY;
 s->hp=g->hp;s->sp=g->sp;s->level=g->level;s->joblevel=g->joblevel;s->exp=g->exp;s->jexp=g->jexp;
 s->kills=g->kills;s->jellopy=g->jellopy;s->clover=g->clover;s->apples=g->apples;
 memcpy(s->extraItems,g->extraItems,sizeof(s->extraItems));s->equipment=g->equipment;memcpy(s->hotbar,g->hotbar,8);s->hotSlot=g->hotSlot;s->mapId=g->mapId;
}
static int v4_valid(const V4Character*s){
 if(!s->sequence||s->level<1||s->level>10||s->joblevel<1||s->joblevel>10)return 0;
 if(s->hp<0||s->hp>60+(s->level-1)*10||s->sp<0||s->sp>10+(s->level-1)*2)return 0;
 if(s->exp<0||s->jexp<0)return 0;
 if(s->level==10?s->exp!=0:s->exp>=baseCurve[s->level-1])return 0;
 if(s->joblevel==10?s->jexp!=0:s->jexp>=jobCurve[s->joblevel-1])return 0;
 if(s->kills<0||s->kills>1000000000||s->jellopy<0||s->jellopy>1000000000||s->clover<0||s->clover>1000000000||s->apples<0||s->apples>1000000000)return 0;
 if(!isfinite(s->x)||!isfinite(s->y)||s->x<8||s->y<8||s->x>=3192||s->y>=3192)return 0;
 if(!isfinite(s->faceX)||!isfinite(s->faceY))return 0;
 if(s->equipment&~15u||s->hotSlot>=8||s->mapId>=2)return 0;
 for(int i=0;i<8;i++)if(!skill_id_valid(s->hotbar[i]))return 0;
 for(int i=0;i<5;i++)if(s->extraItems[i]<0||s->extraItems[i]>ITEM_STACK_MAX)return 0;
 for(int i=1;i<5;i++)if((s->equipment&(1u<<(i-1)))&&s->extraItems[i]<1)return 0;
 float len=s->faceX*s->faceX+s->faceY*s->faceY;
 return len>.9f&&len<1.1f;
}
static void v4_encode(unsigned char*p,const V4Character*s){
 memset(p,0,V4_BYTES);memcpy(p,"MYROSV04",8);v4_put(p+8,4);v4_put(p+12,V4_BYTES);v4_put(p+16,s->sequence);v4_put(p+20,V4_MAP);
 v4_put_float(p+24,s->x);v4_put_float(p+28,s->y);v4_put_float(p+32,s->faceX);v4_put_float(p+36,s->faceY);
 v4_put(p+40,s->hp);v4_put(p+44,s->sp);v4_put(p+48,s->level);v4_put(p+52,s->joblevel);v4_put(p+56,s->exp);v4_put(p+60,s->jexp);
 v4_put(p+64,s->kills);v4_put(p+68,s->jellopy);v4_put(p+72,s->clover);v4_put(p+76,s->apples);v4_put(p+80,s->rng);
 for(int i=0;i<5;i++)v4_put(p+84+i*4,s->extraItems[i]);
 v4_put(p+104,s->equipment);v4_put(p+108,1);
 memcpy(p+112,s->hotbar,8);v4_put(p+120,s->hotSlot);v4_put(p+124,s->mapId);
 v4_put(p+140,v4_crc(p,140));
}
/* 1 valid, 0 corrupt/invalid, -1 unrecognized format: preserve without writes. */
static int v4_decode(V4Character*s,const unsigned char*p){
 if(memcmp(p,"MYROSV04",8)||v4_u32(p+8)!=4||v4_u32(p+12)!=V4_BYTES||v4_u32(p+20)!=V4_MAP)return -1;
 if(v4_crc(p,140)!=v4_u32(p+140)||v4_u32(p+108)!=1)return 0;
 for(int at=128;at<140;at+=4)if(v4_u32(p+at))return 0;
 V4Character t;memset(&t,0,sizeof(t));t.sequence=v4_u32(p+16);t.rng=v4_u32(p+80);
 t.x=v4_float(p+24);t.y=v4_float(p+28);t.faceX=v4_float(p+32);t.faceY=v4_float(p+36);
 t.hp=(int)v4_u32(p+40);t.sp=(int)v4_u32(p+44);t.level=(int)v4_u32(p+48);t.joblevel=(int)v4_u32(p+52);
 t.exp=(int)v4_u32(p+56);t.jexp=(int)v4_u32(p+60);t.kills=(int)v4_u32(p+64);t.jellopy=(int)v4_u32(p+68);t.clover=(int)v4_u32(p+72);t.apples=(int)v4_u32(p+76);
 for(int i=0;i<5;i++)t.extraItems[i]=(int)v4_u32(p+84+i*4);t.equipment=v4_u32(p+104);
 memcpy(t.hotbar,p+112,8);t.hotSlot=v4_u32(p+120);t.mapId=v4_u32(p+124);
 if(!v4_valid(&t))return 0;*s=t;return 1;
}
static void v4_restore(Combat*g,const V4Character*s,float campX,float campY,CombatCanMove canMove,void*world){
 combat_init(g,campX,campY,canMove,world);
 g->x=s->x;g->y=s->y;g->faceX=s->faceX;g->faceY=s->faceY;
 g->hp=s->hp;g->sp=s->sp;g->level=s->level;g->joblevel=s->joblevel;
 g->maxhp=60+(s->level-1)*10;g->maxsp=10+(s->level-1)*2;g->exp=s->exp;g->jexp=s->jexp;
 g->kills=s->kills;g->jellopy=s->jellopy;g->clover=s->clover;g->apples=s->apples;g->rng=s->rng;
 /* Session timers and enemies start fresh; KO is preserved, with A available. */
 g->deadAt=-2;g->lastDamage=0;
 memcpy(g->extraItems,s->extraItems,sizeof(s->extraItems));g->equipment=s->equipment;memcpy(g->hotbar,s->hotbar,8);g->hotSlot=s->hotSlot;g->mapId=s->mapId;
}
#endif
