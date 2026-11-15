/* Versioned global settings records; old40-byte records remain readable. */
#ifndef MYRO_PREFS_FORMAT61_H
#define MYRO_PREFS_FORMAT61_H
#include <zlib.h>
#define PREFS_WORDS61 33u
#define PREFS_BYTES61 (PREFS_WORDS61*4u)
static int prefs_valid61(const uint32_t*r,unsigned bytes){if((bytes!=40&&bytes!=88&&bytes!=96&&bytes!=108&&bytes!=PREFS_BYTES61)||r[0]!=0x3650464d||!r[2]||r[3]>100||r[4]>100||r[5]>=(r[1]>=11?2048u:r[1]>=10?128u:r[1]>=7?64u:r[1]>=6?32u:16u)||r[6]>=MONSTER_VIEW_COUNT53||r[7]>1)return 0;if(r[1]<1||r[1]>11||(r[1]<=2&&bytes!=40)||(r[1]==3&&bytes!=88)||(r[1]==4&&bytes!=96)||(r[1]>=5&&r[1]<=7&&bytes!=108)||(r[1]>=8&&bytes!=PREFS_BYTES61))return 0;if(r[1]>=11&&(r[5]>>7)>=9)return 0;if(r[1]==1){if(r[8])return 0;}else if((r[8]&0xffff0000u)||(r[8]&255)>25||(r[8]>>8)>25)return 0;if(r[1]>=3&&(r[9]>=MONSTER_VIEW_COUNT53||r[10]>2||r[11]>2||r[12]>1||r[13]>1||r[14]>1||r[15]>100||r[16]>1||r[17]>100||r[18]>1||r[19]>=4||r[20]>=128))return 0;if(r[1]>=4&&(r[21]>=MONSTER_VIEW_COUNT53||r[22]>=MONSTER_VIEW_COUNT53))return 0;if(r[1]>=5&&(!r[24]||r[23]>100||r[24]>r[25]||r[25]>r[23]))return 0;if(r[1]>=8)for(unsigned i=26;i<32;i++)if(r[i]>1000)return 0;return r[bytes/4-1]==crc32(0,(const unsigned char*)r,bytes-4);}
#endif
