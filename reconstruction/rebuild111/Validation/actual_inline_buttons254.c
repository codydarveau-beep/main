#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#define NV097_SET_COMBINER_FACTOR0 0xa60
#define NV097_SET_COMBINER_SPECULAR_FOG_CW0 0x288
#define SKIN_BUTTONS_Y64 1904
#define SKIN_DIALOGUE_Y64 1824
typedef struct{int x,y,lineHeight;uint32_t color;unsigned speakerWidth264;}NpcGlyphNative55;
static unsigned combiner,factor,iconPhase,draws;
static uint32_t command[8];
static uint32_t*pb_begin(void){return command;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){if(reg==0x288)combiner=value;if(reg==0xa60)factor=value;return p;}
static void pb_end(uint32_t*p){(void)p;}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){(void)x;(void)y;(void)w;(void)h;(void)u;(void)v;(void)uw;(void)vh;assert(combiner==(iconPhase?8u:0x08010000u));if(iconPhase)assert(factor==0xffffffff);draws++;}
static void npc_glyph_native55(void*context,unsigned ch,unsigned x,unsigned y,uint32_t rgb){NpcGlyphNative55*c=context;if(ch>=256&&ch<270){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_COMBINER_FACTOR0,0xffffffff);p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW0,8);pb_end(p);hud_quad(c->x+(int)x,c->y+(int)y*c->lineHeight+1,12,12,(ch-256)*16+.5f,SKIN_BUTTONS_Y64+.5f,15,15);c->color=UINT32_MAX;return;}if(ch<32||ch>127)ch='?';if(ch==' ')return;int speaker264=y==0&&x<c->speakerWidth264;if(speaker264)rgb=0x203b6d;if(c->color!=rgb){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_COMBINER_FACTOR0,0xff000000u|rgb);p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW0,0x08010000u);pb_end(p);c->color=rgb;}unsigned k=ch-32;hud_quad((float)(c->x+(int)x-1),(float)(c->y+(int)y*c->lineHeight),16,16,(k%32)*16,SKIN_DIALOGUE_Y64+(k/32)*16,16,16);if(speaker264)hud_quad((float)(c->x+(int)x+1-1),(float)(c->y+(int)y*c->lineHeight),16,16,(k%32)*16,SKIN_DIALOGUE_Y64+(k/32)*16,16,16);}
int main(void){NpcGlyphNative55 c={20,20,16,UINT_MAX};npc_glyph_native55(&c,'A',0,0,0);iconPhase=1;npc_glyph_native55(&c,256,10,0,0);iconPhase=0;npc_glyph_native55(&c,'B',20,0,0x203060);iconPhase=1;npc_glyph_native55(&c,257,30,0,0x203060);assert(draws==4);c.speakerWidth264=16;iconPhase=0;npc_glyph_native55(&c,'K',0,0,0);assert(draws==6&&factor==0xff203b6d);npc_glyph_native55(&c,'c',20,0,0);assert(draws==7&&factor==0xff000000);puts("PASS actual shared NPC glyph GPU commands match released unmodulated icon mode and restore subsequent text tint; GPU pixel execution remains target-only.");}
