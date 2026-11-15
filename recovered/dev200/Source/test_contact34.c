/* MIT. Shared field/foot projection: slope, full camera rotation, exact centre. */
#include <assert.h>
#include "combat.h"
#include "projection.h"
static unsigned gw=400,gh=400;static int count;static float xs[96],ys[96];static float slopeX,slopeY;
static float height_at(float x,float y){return slopeX*(x-1500)+slopeY*(y-1500);}
static void pb_fill(int x,int y,int w,int h,unsigned c){if(w==1&&h==1){assert(count<96);xs[count]=x;ys[count++]=y;}}
#include "skills_ui.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);g.fxAt=-100;
 for(int slope=0;slope<3;slope++){slopeX=slope==1?.2f:0;slopeY=slope==2?-.15f:0;
 for(int a=0;a<32;a++){float m[16];world_camera(m,g.x,g.y,height_at(g.x,g.y),a*.19634954f,.78f,1.2f);count=0;skill_small_ring(m,g.x,g.y,6,0);assert(count==64);for(int k=0;k<32;k++){assert(fabsf(xs[k]+xs[k+32]-640)<=1);assert(fabsf(ys[k]+ys[k+32]-490)<=1);}float px=m[0]*g.x+m[1]*g.y+m[3],py=m[4]*g.x+m[5]*g.y+m[6]*height_at(g.x,g.y)+m[7];assert(fabsf(px-320)<.001&&fabsf(py-245)<.001);
 g.safety[0]=(SafetyWall){g.x,g.y,50,0,11};assert(combat_safety_at(&g,g.x,g.y)==0);float baseX[64],baseY[64];memcpy(baseX,xs,sizeof(baseX));memcpy(baseY,ys,sizeof(baseY));count=0;skill_safety_overlay(&g,m);assert(count==64&&!memcmp(xs,baseX,sizeof(baseX))&&!memcmp(ys,baseY,sizeof(baseY)));g.safety[0].expires=0;
 }}puts("PASS circle/feet share exact projected centre, including3 slopes x32 rotations; preview/deployed path agrees");}
