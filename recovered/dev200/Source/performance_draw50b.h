/* MIT. Integer timing readout; audio overlaps main-thread spans. */
#include "frame_profile50b.h"
static void ui_performance50b(const FrameProfile50b*p){
 if(!p->ready){ui_scaled(112,263,.85f,"Frame timing: play for one second first.");return;}
 const unsigned*v=p->tenths,*d=p->drawTenths;unsigned update=v[FRAME_UPDATE50B]+v[FRAME_PREPARE50B],draw=v[FRAME_DRAW50B],hud=v[FRAME_HUD50B],wait=v[FRAME_WAIT50B],audio=v[FRAME_STAGES50B];
 ui_scaled(112,258,.8f,"Frame milliseconds; audio overlaps other work");
 ui_scaled(112,274,.8f,"Update %u.%u  Scene %u.%u  HUD %u.%u",update/10,update%10,draw/10,draw%10,hud/10,hud%10);
 ui_scaled(112,290,.8f,"GPU/display wait %u.%u  Audio %u.%u",wait/10,wait%10,audio/10,audio%10);
 ui_scaled(112,306,.8f,"Upload %u.%u  Ground %u.%u  Scenery %u.%u",d[0]/10,d[0]%10,d[1]/10,d[1]%10,d[2]/10,d[2]%10);
 ui_scaled(112,322,.8f,"Actors %u.%u  World FX %u.%u",d[4]/10,d[4]%10,d[3]/10,d[3]%10);
 ui_scaled(112,338,.8f,"Effects %u.%u  Markers %u.%u",d[5]/10,d[5]%10,d[6]/10,d[6]%10);
}

static void ui_performance53(const FrameProfile50b*p){
 if(!p->ready){ui_scaled(159,126,.8f,"Play for one second first.");return;}
 unsigned values[12]={p->tenths[0]+p->tenths[1],p->tenths[2],p->tenths[3],p->tenths[4],p->tenths[5],p->drawTenths[0],p->drawTenths[1],p->drawTenths[2],p->drawTenths[4],p->drawTenths[3],p->drawTenths[5],p->drawTenths[6]};
 static const char*names[12]={"Update","Scene total","HUD","GPU/display wait","Audio (parallel)","Sprite upload","Ground","Scenery","Actors","World effects","Effects","Markers"};
 for(unsigned i=0;i<12;i++){ui_scaled(159,112+i*17,.75f,"%s",names[i]);ui_scaled(420,112+i*17,.75f,"%u.%u ms",values[i]/10,values[i]%10);}
}
