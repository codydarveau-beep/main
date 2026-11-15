/* MIT. Actual companion/trap cache publication, draw ranges and fenced retirement. */
#define main source_system_decoder50_main
#include "test_system_art50.c"
#undef main
#include "scenery_format.h"
#include "projection.h"
#include "developer.h"
#include "sprite_tint.h"
#include <nv_regs.h>
typedef uintptr_t DWORD;
#define MERCHANT_SPRITE (MOB_SPEC_COUNT+1)
static SparseSprite merchantSprite;
typedef struct{int slot,kind;unsigned frame;float x,y,depth,groundY;}DrawActor;
static void*entityTextures[SPRITE_SLOT_COUNT];static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static unsigned busy50,allocs50,frees50,draws50;static uint32_t commands50[129];
static void*gpu_alloc(unsigned n){allocs50++;return calloc(1,n);}
static int pb_busy(void){if(busy50){busy50--;return 1;}return 0;}
static void MmFreeContiguousMemory(void*p){assert(p&&!busy50);frees50++;free(p);}
static void gpu_depth_state(int n){assert(n==1);}
static void program(int n){assert(n==1);}
static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned format){assert(p&&w==1024&&h==512&&pitch==2048&&format==0x0001102a);}
static uint32_t*pb_begin(void){commands50[128]=0xdeadbeef;return commands50;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){assert(p+2<=commands50+128);if(reg==NV097_DRAW_ARRAYS){unsigned n=(value>>24)+1,at=value&0xffffff;assert(n&&n<=252&&n%3==0&&at+n<=729);draws50++;}*p++=reg;*p++=value;return p;}
static void pb_push(uint32_t*p,unsigned reg,unsigned n){assert(p+n+1<commands50+128);*p=reg;}
static void pb_end(uint32_t*p){assert(p>=commands50&&p<=commands50+128&&commands50[128]==0xdeadbeef);}
static float height_at(float x,float y){(void)x;(void)y;return 0;}
static int facing(float fx,float fy,float co,float si){return((int)floorf(atan2f(-(co*fx+si*fy),si*fx-co*fy)/.7853981634f+.5f)+8)%8;}
#include "gpu_sprite_upload45.h"
#include "companion_render50.h"
static void empty_cache50(Combat*g){g->jobId=0;g->persistent50.homunResting=1;g->persistent50.falcon=0;memset(g->summons50,0,sizeof(g->summons50));memset(g->traps50,0,sizeof(g->traps50));busy50=2;companion_prepare50(g);assert(!busy50&&!trapAtlas50&&!trapMesh50);for(int i=0;i<4;i++)assert(!companionSprites50[i].raw&&companionLoaded50[i]==-1);for(int i=RENDER_MOBS+2;i<SPRITE_SLOT_COUNT;i++)assert(!entityTextures[i]);}
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16];world_camera(m,g.x,g.y,0,0,.785f,1.2f);
 for(int type=6001;type<=6016;type++){g.jobId=20;g.persistent50.homunType=type;g.persistent50.homunResting=0;g.persistent50.homunHP=1;g.class50.homunX=g.x+10;g.class50.homunY=g.y;companion_prepare50(&g);assert(companionLoaded50[0]==type-6001);sprite_upload(&companionSprites50[0],0,RENDER_MOBS+10);DrawActor a[14];int n=0;companion_actors50(&g,m,1,0,1.2f,a,&n);assert(n==1&&actor_shape50(a[0].kind)==&companionSprites50[0]&&isfinite(a[0].groundY));unsigned old=allocs50;companion_prepare50(&g);assert(allocs50==old);empty_cache50(&g);}
 dev_class_preset(&g,14);g.time=1;for(int i=0;i<10;i++)g.traps50[i]=(ClassTrap50){.id=154+i,.rank=5,.until=100,.map=g.mapId,.x=g.x,.y=g.y};companion_prepare50(&g);assert(companionLoaded50[1]==16&&trapAtlas50&&trapMesh50&&trapVertices50==729);trap_draw50(&g,m);assert(draws50>=10);sprite_upload(&companionSprites50[1],0,RENDER_MOBS+11);empty_cache50(&g);
 for(int kind=0;kind<6;kind++){g.summons50[0]=(ClassSummon50){.kind=kind,.hp=100,.until=100,.map=g.mapId,.x=g.x,.y=g.y};companion_prepare50(&g);int cache=kind==5?3:2;assert(companionLoaded50[cache]==17+kind);sprite_upload(&companionSprites50[cache],0,RENDER_MOBS+2);empty_cache50(&g);}
 assert(allocs50==frees50);puts("PASS50 sixteen original Homunculus/Falcon/six summons, actual lazy GPU uploads, stable same-class reuse, ten cutout trap draw ranges,128DWORD guards and fenced complete retirement.");}
