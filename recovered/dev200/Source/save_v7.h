/* Frozen Test14 Save07. Import only; never overwrites source files. */
#ifndef MYRO_SAVE_V7_H
#define MYRO_SAVE_V7_H
#define V7_BYTES 208
typedef struct {
 uint32_t sequence,rng;
 float x,y,faceX,faceY;
 int hp,sp,level,joblevel,exp,jexp,kills,jellopy,clover,apples;
 int extraItems[5];unsigned equipment;
 unsigned char hotbar[8];unsigned hotSlot,mapId;int zeny;unsigned char stats[6];int statPoints;unsigned jobId;unsigned char ranks[4];int skillPoints;
} V7Character;
static void v7_capture(V7Character*s,const Combat*g,uint32_t seq){
 memset(s,0,sizeof(*s));s->sequence=seq;s->rng=g->rng;
 s->x=g->x;s->y=g->y;s->faceX=g->faceX;s->faceY=g->faceY;
 s->hp=g->hp;s->sp=g->sp;s->level=g->level;s->joblevel=g->joblevel;s->exp=g->exp;s->jexp=g->jexp;
 s->kills=g->kills;s->jellopy=g->jellopy;s->clover=g->clover;s->apples=g->apples;
 memcpy(s->extraItems,g->extraItems,sizeof(s->extraItems));s->equipment=g->equipment;memcpy(s->hotbar,g->hotbar,8);s->hotSlot=g->hotSlot;s->mapId=g->mapId;s->zeny=g->zeny;memcpy(s->stats,g->stats,6);s->statPoints=g->statPoints;s->jobId=g->jobId;memcpy(s->ranks,g->ranks,4);s->skillPoints=g->skillPoints;
}
static int v7_valid(const V7Character*s){
 if(s->level<1||s->level>20||s->joblevel<1||s->joblevel>20||s->jobId>2)return 0;
 for(int i=0;i<6;i++)if(s->stats[i]<1||s->stats[i]>30)return 0;
 if(s->statPoints<0||s->statPoints>stat_budget(s->level)||s->statPoints+stat_spent(s->stats)!=stat_budget(s->level))return 0;
 if(s->jobId>2)return 0;int spent=0;for(int i=0;i<4;i++){if(s->ranks[i]>10||(s->ranks[i]&&s->jobId!=(unsigned)(i<2?1:2)))return 0;spent+=s->ranks[i];}
 if(s->ranks[1]&&s->ranks[0]<5)return 0;
 if(s->skillPoints<0||s->skillPoints>TEST_JOB_CAP||spent+s->skillPoints!=(s->jobId?s->joblevel-1:0))return 0;
 if(s->zeny<0||s->zeny>1000000000)return 0;
 if(!s->sequence||s->level<1||s->level>TEST_LEVEL_CAP||s->joblevel<1||s->joblevel>(s->jobId?TEST_JOB_CAP:10))return 0;
 if(s->hp<0||s->hp>60+(s->level-1)*10+(s->stats[2]-1)*5+jobHP[s->jobId][s->level-1]-jobHP[0][s->level-1]||s->sp<0||s->sp>10+(s->level-1)*2+(s->stats[3]-1)*2+jobSP[s->jobId][s->level-1]-jobSP[0][s->level-1])return 0;
 if(s->exp<0||s->jexp<0)return 0;
 if(s->level==TEST_LEVEL_CAP?s->exp!=0:s->exp>=baseCurve[s->level-1])return 0;
 if(s->joblevel==(s->jobId?TEST_JOB_CAP:10)?s->jexp!=0:s->jexp>=(s->jobId?firstJobCurve[s->joblevel-1]:jobCurve[s->joblevel-1]))return 0;
 if(s->kills<0||s->kills>1000000000||s->jellopy<0||s->jellopy>1000000000||s->clover<0||s->clover>1000000000||s->apples<0||s->apples>1000000000)return 0;
 if(!isfinite(s->x)||!isfinite(s->y)||s->x<8||s->y<8||s->x>=3192||s->y>=3192)return 0;
 if(!isfinite(s->faceX)||!isfinite(s->faceY))return 0;
 if(s->equipment&~15u||s->hotSlot>=8||s->mapId>=7)return 0;
 for(int i=0;i<8;i++)if(!(s->hotbar[i]<10||s->hotbar[i]==255)||(s->hotbar[i]==8&&!s->ranks[1])||(s->hotbar[i]==9&&!s->ranks[3]))return 0;
 for(int i=0;i<5;i++)if(s->extraItems[i]<0||s->extraItems[i]>ITEM_STACK_MAX)return 0;
 for(int i=1;i<5;i++)if((s->equipment&(1u<<(i-1)))&&s->extraItems[i]<1)return 0;
 float len=s->faceX*s->faceX+s->faceY*s->faceY;
 return len>.9f&&len<1.1f;
}
static void v7_encode(unsigned char*p,const V7Character*s){
 memset(p,0,V7_BYTES);memcpy(p,"MYROSV07",8);save_put(p+8,7);save_put(p+12,V7_BYTES);save_put(p+16,s->sequence);save_put(p+20,SAVE_MAP);
 save_put_float(p+24,s->x);save_put_float(p+28,s->y);save_put_float(p+32,s->faceX);save_put_float(p+36,s->faceY);
 save_put(p+40,s->hp);save_put(p+44,s->sp);save_put(p+48,s->level);save_put(p+52,s->joblevel);save_put(p+56,s->exp);save_put(p+60,s->jexp);
 save_put(p+64,s->kills);save_put(p+68,s->jellopy);save_put(p+72,s->clover);save_put(p+76,s->apples);save_put(p+80,s->rng);
 for(int i=0;i<5;i++)save_put(p+84+i*4,s->extraItems[i]);
 save_put(p+104,s->equipment);save_put(p+108,1);
 memcpy(p+112,s->hotbar,8);save_put(p+120,s->hotSlot);save_put(p+124,s->mapId);save_put(p+128,s->zeny);
 memcpy(p+132,s->stats,6);save_put(p+140,s->statPoints);save_put(p+144,s->jobId);save_put(p+148,s->skillPoints);memcpy(p+152,s->ranks,4);save_put(p+156,1);save_put(p+204,save_crc(p,204));
}
/* 1 valid, 0 corrupt/invalid, -1 unrecognized format: preserve without writes. */
static int v7_decode(V7Character*s,const unsigned char*p){
 if(memcmp(p,"MYROSV07",8)||save_u32(p+8)!=7||save_u32(p+12)!=V7_BYTES||save_u32(p+20)!=SAVE_MAP)return -1;
 if(save_crc(p,204)!=save_u32(p+204)||save_u32(p+156)!=1||save_u32(p+108)!=1)return 0;
 if(p[138]||p[139])return 0;
 for(int at=160;at<204;at+=4)if(save_u32(p+at))return 0;
 V7Character t;memset(&t,0,sizeof(t));t.sequence=save_u32(p+16);t.rng=save_u32(p+80);
 t.x=save_float(p+24);t.y=save_float(p+28);t.faceX=save_float(p+32);t.faceY=save_float(p+36);
 t.hp=(int)save_u32(p+40);t.sp=(int)save_u32(p+44);t.level=(int)save_u32(p+48);t.joblevel=(int)save_u32(p+52);
 t.exp=(int)save_u32(p+56);t.jexp=(int)save_u32(p+60);t.kills=(int)save_u32(p+64);t.jellopy=(int)save_u32(p+68);t.clover=(int)save_u32(p+72);t.apples=(int)save_u32(p+76);
 for(int i=0;i<5;i++)t.extraItems[i]=(int)save_u32(p+84+i*4);t.equipment=save_u32(p+104);
 memcpy(t.hotbar,p+112,8);t.hotSlot=save_u32(p+120);t.mapId=save_u32(p+124);t.zeny=(int)save_u32(p+128);memcpy(t.stats,p+132,6);t.statPoints=(int)save_u32(p+140);t.jobId=save_u32(p+144);t.skillPoints=(int)save_u32(p+148);memcpy(t.ranks,p+152,4);
 if(!v7_valid(&t))return 0;*s=t;return 1;
}
static void v7_restore(Combat*g,const V7Character*s,float campX,float campY,CombatCanMove canMove,void*world){
 combat_init(g,campX,campY,canMove,world);
 g->x=s->x;g->y=s->y;g->faceX=s->faceX;g->faceY=s->faceY;
 g->hp=s->hp;g->sp=s->sp;g->level=s->level;g->joblevel=s->joblevel;
 memcpy(g->stats,s->stats,6);g->statPoints=s->statPoints;g->jobId=s->jobId;g->skillPoints=s->skillPoints;memcpy(g->ranks,s->ranks,4);
 g->maxhp=60+(s->level-1)*10+(s->stats[2]-1)*5+jobHP[s->jobId][s->level-1]-jobHP[0][s->level-1];g->maxsp=10+(s->level-1)*2+(s->stats[3]-1)*2+jobSP[s->jobId][s->level-1]-jobSP[0][s->level-1];g->exp=s->exp;g->jexp=s->jexp;
 g->kills=s->kills;g->jellopy=s->jellopy;g->clover=s->clover;g->apples=s->apples;g->rng=s->rng;
 /* Session timers and enemies start fresh; KO is preserved, with A available. */
 g->deadAt=-2;g->lastDamage=0;
 memcpy(g->extraItems,s->extraItems,sizeof(s->extraItems));g->equipment=s->equipment;memcpy(g->hotbar,s->hotbar,8);g->hotSlot=s->hotSlot;g->mapId=s->mapId;g->zeny=s->zeny;
}

#endif
