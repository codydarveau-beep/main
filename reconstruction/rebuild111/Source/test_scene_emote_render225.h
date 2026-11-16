/* Host boundaries: GPU allocation/push/raster recorded; real clip decoder,
 * production draw traversal, camera projection and world height execute. */
#include "npc_effect_stream172.h"
static unsigned emoteReads225;
static int npc_fx_read172(void*context,unsigned at,unsigned char*out,unsigned bytes){(void)context;FILE*f=fopen(getenv("MYRO_NPCFX_PATH"),"rb");assert(f);assert(!fseek(f,0,SEEK_END)&&ftell(f)==NPC_FX_BYTES172);int ok=!fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;fclose(f);emoteReads225++;return ok;}
static unsigned art39DrawCount,artCacheTime183,artGpuUsed183[24],art39Uploads[24],art39Sources[24];
static void*art39Textures[24];
#define ART39_DRAW_LIMIT 24
#define PAGE_READWRITE 1
#define PAGE_WRITECOMBINE 2
#define NV097_SET_BLEND_FUNC_SFACTOR 1
#define NV097_SET_BLEND_FUNC_DFACTOR 2
typedef struct{unsigned Length,AvailablePages;}MM_STATISTICS;
static unsigned emoteRaster225,emoteFrames225,emoteEvents225,emoteMask225;
static uint32_t emoteCommands225[8];
static void MmQueryStatistics(MM_STATISTICS*m){m->AvailablePages=2048;}
static void*MmAllocateContiguousMemoryEx(unsigned n,unsigned a,unsigned b,unsigned c,unsigned d){(void)a;(void)b;(void)c;(void)d;assert(n==65536);return gpu_alloc(n);}
static uint32_t*pb_begin(void){return emoteCommands225;}
static uint32_t*pb_push1(uint32_t*p,unsigned m,unsigned v){assert(m==1||m==2);assert(v==1||v==0x302||v==0x303);return p;}
static void pb_end(uint32_t*p){assert(p==emoteCommands225);}
static void gpu_sprite(void*t,SparseSprite*s,float x,float y,float z,float scale){assert(t&&s->w==128&&s->h==256&&s->bytesPerPixel==2&&s->alpha4444&&isfinite(x)&&isfinite(y)&&isfinite(z)&&scale>0);emoteRaster225++;}
#include "../Validation/actual_npc_fx_one225.inc"
#include "campaign_emote_draw225.h"
static void emote_render_release225(void){for(unsigned i=0;i<24;i++)if(art39Textures[i]){MmFreeContiguousMemory(art39Textures[i]);art39Textures[i]=NULL;art39Uploads[i]=art39Sources[i]=~0u;}}
