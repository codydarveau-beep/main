#include "interior_rooms181.h"
#include "world_gate_state64.h"
#include "world_availability44.h"
#include "map_markers64.h"
static unsigned minimap_marker_color64(unsigned rgb){unsigned best=0xff65dffa;unsigned distance=~0u;for(unsigned i=0;i<sizeof(skinColors)/sizeof(*skinColors);i++){unsigned c=skinColors[i];if((c>>24)!=255)continue;int r=(int)((c>>16)&255)-(int)((rgb>>16)&255),g=(int)((c>>8)&255)-(int)((rgb>>8)&255),b=(int)(c&255)-(int)(rgb&255);unsigned d=r*r+g*g+b*b;if(d<distance){distance=d;best=c;}}return best;}
/* One shared-atlas quad at either size; no extra minimap texture. */
static float miniScale61=1;static int miniX61=522,miniY61=38;
static void minimap_marker(float x,float y,unsigned color,int size){if(!rooms_point181(&interiorRooms181,x,y))return;int px,py;minimap_point(x,y,gw,gh,&px,&py);int w=(int)ceilf(size*miniScale61);pb_fill(miniX61+(int)(px*miniScale61)-w/2,miniY61+(int)(py*miniScale61)-w/2,w,w,color);}
static void ui_minimap(const Combat*g,unsigned id){if(id>=WORLD_MAP_COUNT||minimapSize60==DISPLAY_OFF60)return;miniScale61=minimapSize60==DISPLAY_LARGE60?1.5f:1;int width=(int)(MINI_W*miniScale61),height=(int)(MINI_H*miniScale61);miniX61=622-width-4;miniY61=38;ui_panel(miniX61-4,18,width+8,height+24,"",0,-1);ui_fit47(miniX61+1,19,width-2,1,mapLabels[id]);if(hudBatch.active)fail("Minimap must precede shared HUD batch");
 if(minimapTexture200&&minimapLoaded200==id){hud_setup(minimapTexture200,256,128,512,0x0001102a,1);hud_quad(miniX61,miniY61,width,height,0,0,MINIMAP_W200,MINIMAP_H200);}
 hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);
 for(unsigned i=0;i<sizeof(worldGates)/sizeof(*worldGates);i++)if(worldGates[i].source==id&&world_gate_enabled64(i))minimap_marker(worldGates[i].x,worldGates[i].y,(world_destination_ready44(worldGates[i].destination)&&(!combatTravelAdmission194||!combatTravelAdmission194((Combat*)g,worldGates[i].destination)))?0xff65dffa:0xffff4848,3);
 for(unsigned i=0;i<32;i++)if(mapMarkers64[i].active&&mapMarkers64[i].map==id)minimap_marker(mapMarkers64[i].x,mapMarkers64[i].y,minimap_marker_color64(mapMarkers64[i].color),4);
 CampaignRegions194 regional194;if(campaign_regions_load194(questPins65,&regional194))for(unsigned i=0;i<REGIONAL_COUNT194;i++){const RegionalJourney194*p=regionalJourneys194+i;unsigned bit=regional_bit194(i);if(p->map==id&&(regional194.unlocked&bit)&&!(regional194.completed&bit)&&quest_tracked65(REGIONAL_QUEST194+p->region-1)){minimap_marker(p->noteX,p->noteY,0xff000000,6);minimap_marker(p->noteX,p->noteY,0xffffdf56,3);}}
 if(id==2){float x,y;world_merchant(&x,&y);minimap_marker(x,y,0xffffdf56,3);world_instructor(&x,&y);minimap_marker(x,y,0xffffdf56,3);world_stylist(&x,&y);minimap_marker(x,y,0xffffdf56,3);}minimap_marker(g->x,g->y,0xffff4848,4);
}
#include "compass_layout62.h"
static void compass_line62(int x,int y,int nx,int ny,unsigned color,int width){int dx=abs(nx-x),dy=-abs(ny-y),sx=x<nx?1:-1,sy=y<ny?1:-1,error=dx+dy;for(;;){pb_fill(x-width/2,y-width/2,width,width,color);if(x==nx&&y==ny)break;int e=2*error;if(e>=dy){error+=dy;x+=sx;}if(e<=dx){error+=dx;y+=sy;}}}
/* Draw only the annulus; its centre and the surrounding world stay transparent. */
static void compass_ring62(int cx,int cy,int radius,int thickness,unsigned color){int inner=radius-thickness;for(int y=-radius;y<=radius;y++){int outer=(int)sqrtf((float)(radius*radius-y*y));int hole=abs(y)<=inner?(int)ceilf(sqrtf((float)(inner*inner-y*y))):0;if(hole>0){pb_fill(cx-outer,cy+y,outer-hole+1,1,color);pb_fill(cx+hole,cy+y,outer-hole+1,1,color);}else pb_fill(cx-outer,cy+y,outer*2+1,1,color);}}
/* Floral points replace the crossed spears; open centre preserves world visibility. */
static void compass_blossom200(int x,int y,int north){int w=north?16:12,h=north?16:12;hud_quad(x-w/2,y-h/2,w,h,COMPASS_ART_X200+(north?0:16),COMPASS_ART_Y200,w,h);}
static void ui_compass61(float yaw){
 if(compassSize60==DISPLAY_OFF60)return;
 int cx,cy,r;compass_layout62(minimapSize60,compassSize60,&cx,&cy,&r);float co=cosf(yaw),si=sinf(yaw);
 compass_ring62(cx+2,cy+3,r+2,5,0x70000000);
 compass_ring62(cx,cy,r+1,5,0xff241d1b);
 compass_ring62(cx,cy,r,3,0xffbd8c3e);
 compass_ring62(cx,cy,r-1,1,0xfff4d47a);
 /* Restrained alternating over/under gold stitches suggest a Nordic braid. */
 for(unsigned k=0;k<24;k++){float a=k*.2617993878f,rad=r-(k&1?0:1);int x=cx+(int)roundf(sinf(a)*rad),y=cy+(int)roundf(cosf(a)*rad);pb_fill(x,y,1,1,k&1?0xff78532e:0xffffe6a2);}
 hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);
 for(int i=0;i<4;i++){
  float dx=i==0?si:i==1?co:i==2?-si:-co,dy=i==0?-co:i==1?si:i==2?co:-si;
  /* A leaf at the foot of each blossom ties it into the gold ring. */
  int lx=cx+(int)roundf(dx*(r-3)),ly=cy+(int)roundf(dy*(r-3));
  hud_quad(lx-3,ly-2,7,5,COMPASS_ART_X200+32,COMPASS_ART_Y200,7,5);
  int fx=cx+(int)roundf(dx*(r+3)),fy=cy+(int)roundf(dy*(r+3));compass_blossom200(fx,fy,i==0);
  int x=cx+(int)roundf(dx*(r+(i?20:23))),y=cy+(int)roundf(dy*(r+(i?20:23)));
  hud_quad(x-8,y-8,16,16,COMPASS_LETTERS_X200+i*16,SKIN_COMPASS_Y62,16,16);
 }
}
