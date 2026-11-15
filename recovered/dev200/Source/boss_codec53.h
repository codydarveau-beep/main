/* MIT. Reserved save area:20-byte header,175-byte bitmap,10 bits per dead boss.
 * Maximum1945bytes for1400simultaneous deadlines; alive spawns have no entry. */
#define SAVE_BOSSES53 6000
#define BOSS_CODEC_BYTES53 1945
static void boss_encode53(unsigned char*p,const BossState53*s){
 memset(p,0,BOSS_CODEC_BYTES53);uint64_t base=UINT64_MAX;unsigned count=0;
 for(unsigned i=0;i<BOSS_COUNT53;i++)if(s->until[i]){if(s->until[i]<base)base=s->until[i];count++;}
 save_put(p,0x53334244u);save_put(p+4,0x3b001400u);save_put(p+8,count);if(!count)return;
 save_put(p+12,(uint32_t)base);save_put(p+16,(uint32_t)(base>>32));unsigned bit=0;
 for(unsigned i=0;i<BOSS_COUNT53;i++)if(s->until[i]){p[20+i/8]|=1u<<(i%8);uint64_t delta=s->until[i]-base;if(delta>600)delta=600;for(unsigned b=0;b<10;b++,bit++)if(delta&(1u<<b))p[195+bit/8]|=1u<<(bit%8);}
}
static int boss_decode53(BossState53*s,const unsigned char*p){
 memset(s,0,sizeof(*s));if(!save_u32(p))return 1;
 if(save_u32(p)!=0x53334244u||save_u32(p+4)!=0x3b001400u)return 0;
 unsigned expected=save_u32(p+8),count=0,bit=0;if(expected>BOSS_COUNT53)return 0;
 uint64_t base=(uint64_t)save_u32(p+12)|((uint64_t)save_u32(p+16)<<32);if(base>UINT64_MAX-600)return 0;
 for(unsigned i=0;i<BOSS_COUNT53;i++)if(p[20+i/8]&(1u<<(i%8))){unsigned d=0;for(unsigned b=0;b<10;b++,bit++)if(p[195+bit/8]&(1u<<(bit%8)))d|=1u<<b;if(d>600)return 0;s->until[i]=base+d;count++;}
 return count==expected;
}
