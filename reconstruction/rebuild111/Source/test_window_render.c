/* SPDX-License-Identifier: MIT. Render actual UI draw calls through a host recorder. */
#define MYRO_HOST 1
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
#include "window_ui.h"
#include "hud_batch.h"
#include "skin_colors.h"
extern const unsigned char fontWidths[96];
static void*skinTexture,*currentTexture;static HudBatch batch;
#define hudBatch batch
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
static void*gpu_alloc(unsigned n){return malloc(n);}
static unsigned char*inflateasset(const char*n,const unsigned char*s,unsigned sz,unsigned raw){(void)n;unsigned char*p=malloc(raw);uLongf len=raw;if(uncompress(p,&len,s,sz)||len!=raw)fail("inflate");return p;}
static void hud_setup(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){(void)w;(void)h;(void)pitch;(void)format;(void)blend;currentTexture=t;}
static void pb_fill(int x,int y,int w,int h,unsigned c){unsigned i=0;for(;i<sizeof(skinColors)/sizeof(skinColors[0]);i++)if(skinColors[i]==c)break;if(i==sizeof(skinColors)/sizeof(skinColors[0]))fail("missing palette");if(!hud_batch_add(&batch,x,y,w,h,i%64*8,256+i/64*8,0,0))fail("batch overflow");printf("F %d %d %d %d %u\n",x,y,w,h,c);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){if(!hud_batch_add(&batch,x,y,w,h,u,v,uw,vh))fail("batch overflow");printf("Q %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",x,y,w,h,u,v,uw,vh);}
#include "hud_theme.h"
static void hud_text(int x,int y,const char*f,...){char line[160];va_list a;va_start(a,f);vsnprintf(line,sizeof(line),f,a);va_end(a);for(unsigned i=0;line[i]&&x<622;i++){unsigned c=(unsigned char)line[i];if(c<32||c>127)c='?';unsigned k=c-32;if(c!=' ')hud_quad(x,y,16,16,(k%16)*16,(k/16)*16,16,16);x+=fontWidths[k]+1;}}
static void hud_bar(int x,int y,int w,int n,int max,unsigned c){pb_fill(x,y,w,8,0xff101711);if(max>0&&n>0)pb_fill(x+1,y+1,(w-2)*n/max,6,c);}
#include "window_draw.h"
static int musicVolume=50,soundVolume=60,musicMuted,soundMuted;
/* Platform adapters only: no host audio thread, lock, GPU or texture upload. */
#include "sound_mix.h"
static SoundVoice soundVoices[6];static int soundLock,menuSoundEnabled58=1,menuSoundActive58;
static void EnterCriticalSection(int*lock){(void)lock;}
static void LeaveCriticalSection(int*lock){(void)lock;}
#include "pause_draw.h"
#include "world_data.h"
static unsigned gw=312,gh=392;
static void world_merchant(float*x,float*y){*x=1200;*y=1200;}
static void world_instructor(float*x,float*y){*x=1120;*y=1200;}
static void world_stylist(float*x,float*y){*x=1160;*y=1248;}
#include "minimap_data200.h"
static void*minimapTexture200;static unsigned minimapLoaded200=~0u;
#include "minimap_draw.h"
int main(int argc,char**argv){float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;Combat g;combat_init(&g,1500,1500,NULL,NULL);g.level=10;g.statPoints=48;g.hp=135;g.maxhp=150;g.zeny=123456;WindowUI u={.open=15,.active=1,.focus=8,.inside=1,.tipTime=4};u.choice[3]=6;if(argc>1){int w=atoi(argv[1]);u.focus=5+w;u.choice[w]=argc>2?atoi(argv[2]):0;}if(argc>3){g.jobId=atoi(argv[3]);u.skillPage=argc>4?atoi(argv[4]):0;g.skillPoints=8;g.ranks[0]=g.jobId==1?5:0;}if(getenv("MYRO_RANK10")){memset(g.ranks,10,sizeof(g.ranks));g.ranks[32]=g.ranks[36]=1;}const char*dest=getenv("MYRO_TEST_DEST");if(dest)u.assignBank=atoi(dest);const char*placing=getenv("MYRO_PLACE");if(placing){u.placing=1;u.carried=23;u.dropSlot=atoi(placing);}u.hintStat=u.hintSkill=1;skin_init();char wrapped[8][96];int lines=ui_wrap("Sitting: faster HP/SP recovery. L3 to stand; movement is locked.",wrapped,210,.9f);assert(lines>=2);int letters=0;for(int row=0;row<lines;row++)for(int c=0;wrapped[row][c];c++)if(wrapped[row][c]!=' ')letters++;int expected=0;const char*sentence="Sitting: faster HP/SP recovery. L3 to stand; movement is locked.";for(;*sentence;sentence++)if(*sentence!=' ')expected++;assert(letters==expected);for(int k=0;k<lines;k++)assert(ui_text_width(wrapped[k],.9f)<=210);uint8_t grid[312*392];memset(grid,1,sizeof(grid));minimap_raster(skinTexture,512,288,144,grid,gw,gh);FILE*f=fopen("/tmp/myro13-skin.raw","wb");fwrite(skinTexture,1,skin_image_raw,f);fclose(f);if(getenv("MYRO_BUFFS")){g.jobId=5;g.stats[4]=20;g.ranks[11]=10;g.concentrateRank=10;g.concentrateLeft=240;g.buffs[0]=90;g.buffs[1]=120;g.buffLevels[0]=10;g.buffLevels[1]=12;g.poisonLeft=30;}ui_minimap(&g,2);ui_player_status(&g);ui_draw(&g,&u,1);ui_quick_slots(&g,&u);ui_level_hints(&u);ui_buffs(&g);if(getenv("MYRO_NOTICE"))ui_popup(-1,407,getenv("MYRO_NOTICE"),390,.9f);if(argc>5&&argc<7)ui_job_menu(&g,1,1);if(argc>6){PauseUI pause={.tab=atoi(argv[6]),.row=0};ui_pause(&pause,0,1,1,1,"Save ready.");}fprintf(stderr,"PASS actual UI draws: %u quads (%u/%u vertices); bounded shared atlas, all colours covered\n",batch.count,batch.count*4,HUD_BATCH_QUADS*4);free(skinTexture);}
