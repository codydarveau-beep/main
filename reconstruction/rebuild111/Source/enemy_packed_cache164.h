/* Bounded compressed-frame reuse avoids repeated disc seeks for large poses.
 * Raw crop budget remains2MiB; extra compressed storage grows only as used. */
#define ENEMY_PACKED_BYTES164 (1024u*1024u)
#define ENEMY_PACKED_SLOTS164 128u
typedef struct{unsigned offset,bytes,crc,used,touched183;unsigned char*data;}EnemyPacked164;
static EnemyPacked164 enemyPacked164[ENEMY_PACKED_SLOTS164];
static unsigned enemyCacheTime183;
static unsigned enemyPackedBytes164,enemyPackedClock164,enemyPackedHits164,enemyDiskReads164;
static void enemy_packed_clear164(void){for(unsigned i=0;i<ENEMY_PACKED_SLOTS164;i++){free(enemyPacked164[i].data);memset(enemyPacked164+i,0,sizeof(*enemyPacked164));}enemyPackedBytes164=enemyPackedClock164=enemyPackedHits164=0;}
static unsigned char*enemy_frame_packed164(unsigned offset,unsigned bytes,unsigned crc,unsigned raw,int*borrowed){
 *borrowed=0;
#ifdef MYRO_NO_PACKED_CACHE164
 raw=0;
#endif
 if(raw<=16384||bytes>ENEMY_PACKED_BYTES164/4){enemyDiskReads164++;return enemy_read51(offset,bytes);}unsigned tick=++enemyPackedClock164;
 for(unsigned i=0;i<ENEMY_PACKED_SLOTS164;i++){EnemyPacked164*c=enemyPacked164+i;if(c->data&&c->offset==offset&&c->bytes==bytes&&c->crc==crc){c->used=tick;c->touched183=enemyCacheTime183;enemyPackedHits164++;*borrowed=1;return c->data;}}

#ifndef MYRO_HOST
 MM_STATISTICS memory164={0};memory164.Length=sizeof(memory164);MmQueryStatistics(&memory164);if((uint64_t)memory164.AvailablePages*4096<4u*1024*1024+bytes){enemy_packed_clear164();enemyDiskReads164++;return enemy_read51(offset,bytes);}
#endif
 int slot=-1;while(slot<0||enemyPackedBytes164+bytes>ENEMY_PACKED_BYTES164){unsigned oldest=~0u;int victim=-1;for(unsigned i=0;i<ENEMY_PACKED_SLOTS164;i++){EnemyPacked164*c=enemyPacked164+i;if(!c->data){if(slot<0)slot=(int)i;}else if(c->used<oldest){oldest=c->used;victim=(int)i;}}if(slot>=0&&enemyPackedBytes164+bytes<=ENEMY_PACKED_BYTES164)break;if(victim<0)fail("Packed creature cache capacity invalid");EnemyPacked164*c=enemyPacked164+victim;enemyPackedBytes164-=c->bytes;free(c->data);memset(c,0,sizeof(*c));slot=victim;}
 enemyDiskReads164++;unsigned char*data=enemy_read51(offset,bytes);enemyPacked164[slot]=(EnemyPacked164){offset,bytes,crc,tick,enemyCacheTime183,data};enemyPackedBytes164+=bytes;*borrowed=1;return data;
}
