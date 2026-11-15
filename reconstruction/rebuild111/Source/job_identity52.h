/* Stable native IDs. New jobs remain gated until mechanics/art are integrated. */
#ifndef MYRO_JOB_IDENTITY52_H
#define MYRO_JOB_IDENTITY52_H
#include <stdint.h>
#include "expanded_ids60.h"
typedef uint64_t ClassMask52;
enum {J52_LORD_KNIGHT=21,J52_PALADIN,J52_PROFESSOR,J52_HIGH_PRIEST,J52_CHAMPION,J52_ASSASSIN_CROSS,J52_STALKER,J52_SNIPER,J52_CLOWN,J52_GYPSY,J52_WHITESMITH,J52_CREATOR,
 J52_HIGH_NOVICE,J52_HIGH_SWORDSMAN,J52_HIGH_MAGE,J52_HIGH_ACOLYTE,J52_HIGH_THIEF,J52_HIGH_ARCHER,J52_HIGH_MERCHANT,J52_SUPER_NOVICE,J60_NINJA,J60_GUNSLINGER,J60_TAEKWON,J60_STAR_GLADIATOR,J60_SOUL_LINKER,J52_COUNT};
static int job_valid52(unsigned job){return job<J52_COUNT;}
static ClassMask52 job_bit52(unsigned job){return job<64?(UINT64_C(1)<<job):UINT64_C(0);}
static int job_transcendent52(unsigned job){return job==8||(job>=21&&job<J52_SUPER_NOVICE);}
static int job_high_first52(unsigned job){return job>=J52_HIGH_NOVICE&&job<J52_SUPER_NOVICE;}
static unsigned job_parent52(unsigned job){
 static const unsigned char parent[]={7,11,10,17,18,12,13,14,15,16,19,20,0,1,2,3,4,5,6};
 if(job==J52_SUPER_NOVICE)return 0;return job>=21&&job<J52_SUPER_NOVICE?parent[job-21]:job;
}
static int job_mask_has52(ClassMask52 mask,unsigned job){return job_valid52(job)&&(mask&job_bit52(job))!=0;}
static int job_mask_inherits52(ClassMask52 mask,unsigned job){return job_mask_has52(mask,job)||job_mask_has52(mask,job_parent52(job));}
static unsigned job_source52(unsigned job){
 static const unsigned short source[J52_COUNT]={0,1,2,4,6,3,5,7,4010,9,16,14,12,17,11,19,20,8,15,10,18,4008,4015,4017,4009,4016,4013,4018,4012,4020,4021,4011,4019,4001,4002,4003,4005,4007,4004,4006,23,25,24,4046,4047,4049};
 return job_valid52(job)?source[job]:~0u;
}
#endif
