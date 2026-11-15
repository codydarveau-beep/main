/* MIT. Actual new texture uploads and geometry submission, finite/bounded GPU data. */
#define main previous_art48_main
#include "test_art_render45.c"
#undef main
#include "ice_geometry48.h"
#define NV097_SET_BEGIN_END 3
static uint32_t fieldCommands48[256];static unsigned vertices48,quads48,bytes48;
static uint32_t*field_begin48(void){return fieldCommands48;}
static uint32_t*field_push48(uint32_t*p,unsigned reg,unsigned value){assert(reg==NV097_SET_BLEND_FUNC_DFACTOR||reg==NV097_SET_BEGIN_END);assert(value==0||value==1||value==8||value==0x303);*p++=value;return p;}
static void field_end48(uint32_t*p){assert(p>=fieldCommands48&&p<fieldCommands48+256);quads48++;}
static uint32_t*field_vertex48(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&isfinite(u)&&isfinite(v));assert(u>=0&&u<=128&&v>=0&&v<=128);vertices48++;return p+5;}
static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned fmt){assert(p&&(w==64||w==128)&&h==w&&pitch==w*4&&fmt==0x0001122au);}
static void spell_world_begin41(void){}
#define pb_begin field_begin48
#define pb_push1 field_push48
#define pb_end field_end48
#define vertex field_vertex48
#include "field_draw48.h"
#undef pb_begin
#undef pb_push1
#undef pb_end
#undef vertex
#ifndef CLASS_ART49_ENTRY
#define CLASS_ART49_ENTRY main
#endif
int CLASS_ART49_ENTRY(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);g.time=10;g.mapId=0;float m[16];world_camera(m,g.x,g.y,0,0,.785f,1.2f);Art39State s={0};
 for(int id=101;id<=104;id++){g.classAreas48[0]=(ClassArea48){.id=id,.rank=5,.x=g.x,.y=g.y,.until=100,.map=0};vertices48=quads48=0;field_draw48(&g,&s,m);assert(vertices48>0&&vertices48<=4000&&quads48<=1000);}
 memset(g.classAreas48,0,sizeof(g.classAreas48));for(int id=119;id<=124;id++)if(id==119||id==121||id==124){s.events[0]=(Art39Event){.skill=id,.at=9,.x=g.x,.y=g.y};vertices48=quads48=0;field_draw48(&g,&s,m);assert(vertices48>0&&vertices48<=816);}
 for(int h=0;h<3;h++)for(int f=0;f<4;f++)for(int t=0;t<100;t++){SpellPoint41 q[3];float uv[6];ice_face48(500,500,12,123,h,f,t*.01f,q,uv);for(int j=0;j<3;j++){assert(isfinite(q[j].x)&&fabsf(q[j].x-500)<8&&fabsf(q[j].y-500)<8&&q[j].z>=11&&q[j].z<=66);assert(uv[2*j]>=0&&uv[2*j]<=128&&uv[2*j+1]>=0&&uv[2*j+1]<=128);}}
 for(int i=0;i<FIELD_TEXTURE_COUNT50;i++)for(int n=0;n<16;n++)for(int t=0;t<2;t++)if(fieldTextures48[i][n][t]){bytes48+=fieldTexDefs48[i].side*fieldTexDefs48[i].side*4;free(fieldTextures48[i][n][t]);}assert(bytes48<1024*1024);
 puts("PASS48 original class texture uploads, field/cross/shield geometry, finite vertices/UVs, bounded push buffers, Ice Wall horns and lazy texture residency.");}
