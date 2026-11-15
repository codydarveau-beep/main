/* MIT. Actual wheel contact projection, source-idle freeze and stylist transactions. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "developer.h"
#include "projection.h"
#include "cart_pose40.h"
#include "shop.h"
#include "merchant_services.h"
#include "save_format.h"
static float ground(float x,float y){return x*.01f-y*.02f;}
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,6);g.mapId=2;g.cartOwned=1;CartPose40 p;unsigned cases=0;for(int style=0;style<5;style++)for(int dir=0;dir<8;dir++)for(int rot=0;rot<32;rot++)for(int ti=0;ti<3;ti++)for(int iz=0;iz<3;iz++){float zoom=iz==0?.85f:iz==1?1.2f:1.8f,m[16];g.cartStyle=style;g.faceX=cosf(dir*.78539816f);g.faceY=sinf(dir*.78539816f);g.moving=0;g.time=12345;world_camera(m,g.x,g.y,ground(g.x,g.y),rot*.19634954f,.52f+ti*.305f,zoom);assert(cart_pose40(&g,m,zoom,dir,ground,&p));assert(p.style==style&&p.dir==dir&&p.elapsed==0);assert(fabsf(hypotf(p.x-g.x,p.y-g.y)-13)<.001);float sx,sy;world_project(m,p.x,p.y,ground(p.x,p.y),&sx,&sy);float rect[4];sprite_screen_rect(p.sx,p.sy,zoom/3,64,90,128,rect);assert(fabsf(rect[0]+cartContact40[style][dir][0]*zoom/3-sx)<.001);assert(fabsf(rect[1]+cartContact40[style][dir][1]*zoom/3-sy)<.001);assert(fabsf(p.depth-(m[8]*p.x+m[9]*p.y+m[10]*ground(p.x,p.y)+m[11]-WORLD_SPRITE_BIAS))<1);g.moving=1;assert(cart_pose40(&g,m,zoom,dir,ground,&p)&&p.elapsed==g.time);cases++;}
MerchantUI u;int hp=g.hp,sp=g.sp,zeny=g.zeny;merchant_styles_open(&u,&g);for(int i=0;i<5;i++){u.item=i;int previous=g.cartStyle;int changed=merchant_input(&u,&g,2,1);assert(g.cartStyle==i&&changed==(i!=previous));assert(g.sp==sp&&g.zeny==zeny&&g.hp==hp);}u.item=0;assert(!merchant_input(&u,&g,2,0)&&g.cartStyle==4);merchant_styles_open(&u,&g);g.cartOwned=0;assert(!merchant_input(&u,&g,2,1));g.cartOwned=1;g.jobId=1;assert(!merchant_input(&u,&g,2,1));g.jobId=6;assert(!merchant_input(&u,&g,4,1)&&u.mode==MS_CLOSED);
puts("PASS40 all five free stylist transactions/guards and11520 real projected wheel-contact/depth/idle/walk poses; source mechanics and carrying costs untouched");printf("Cart geometry cases:%u\n",cases);}
