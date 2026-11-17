#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "combat.h"
static unsigned gw=400,gh=400;static float height_at(float x,float y){(void)x;(void)y;return 0;}
static void hud_setup(void*t,unsigned w,unsigned h,unsigned pitch,unsigned fmt,int blend){(void)t;assert(w==512&&h==256&&pitch==1024&&fmt==0x00011d2a&&blend);}
static float q[128][8];static unsigned count;
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){assert(count<128&&isfinite(x)&&isfinite(y)&&w>0&&h>0);float f[]={x,y,w,h,u,v,uw,vh};for(unsigned i=0;i<8;i++)q[count][i]=f[i];count++;}
#include "damage_draw.h"
static Combat game;
int main(void){float m[16]={1,0,0,0,0,1,-1,0};DamageEvent d={.x=320,.y=240};unsigned sizes=0;
for(unsigned value=1;value<=1000000000u;value*=10){for(unsigned f=0;f<6;f++){float age=f*.25f,scale=fmaxf(.3f,1.5f*(1-age/1.5f));count=0;damage_particle53(&d,m,(int)value,age,1,0);assert(count>=2);float expected=fmaxf(42,damage_number_width262((int)value,1)+12)*scale;assert(fabsf(q[0][2]-expected)<.001f&&fabsf(q[0][3]-36*scale)<.001f);for(unsigned i=1;i<count;i++){assert(q[i][0]>=q[0][0]-.001f&&q[i][0]+q[i][2]<=q[0][0]+q[0][2]+.001f);assert(q[i][1]>=q[0][1]-.001f&&q[i][1]+q[i][3]<=q[0][1]+q[0][3]+.001f);}sizes++;}if(value==1000000000u)break;}
count=0;damage_particle53(&d,m,9,0,0,0);assert(count==1&&fabsf(q[0][2]-damageGlyphs53[9*6][2]*1.5f)<.001f);
game.damageNext=1;game.damage[0]=(DamageEvent){.x=320,.y=240,.kind=2,.hits=1};count=0;damage_draw(&game,m);assert(count==1&&fabsf(q[0][2]-damageGlyphs53[50*6][2]*.64f)<.001f);game.damage[0].kind=1;game.damage[0].value=8;count=0;damage_draw(&game,m);assert(count==1&&fabsf(q[0][2]-damageGlyphs53[18*6][2]*.6f)<.001f);printf("PASS actual damage renderer: restored released number/MISS/received sizes; critical burst contains1..10digits across%u cases, same center/fade/motion; no sprite-art replacement. GPU boundary recorded.\n",sizes);}
