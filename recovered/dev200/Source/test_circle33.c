/* MIT. Render and physics agree without grid snap, including camera rotation. */
#include <assert.h>
#include "combat.h"
#include "projection.h"
static unsigned gw=400,gh=400;static int count;static int px[96],py[96];static unsigned last;
static float height_at(float x,float y){return 0;}
static void pb_fill(int x,int y,int w,int h,unsigned c){assert(count<96&&w==1&&h==1);px[count]=x;py[count++]=y;last=c;}
#include "skills_ui.h"
int main(void){Combat g;combat_init(&g,1502.3f,1501.7f,NULL,NULL);g.fxAt=-100;for(int i=0;i<16;i++){float m[16];world_camera(m,g.x,g.y,0,i*.4f,.78f,1.2f);count=0;skill_overlay(&g,m,1,48,g.x,g.y);assert(count==48);int ox[48],oy[48];memcpy(ox,px,sizeof(ox));memcpy(oy,py,sizeof(oy));g.safety[0]=(SafetyWall){g.x,g.y,50,0,11};count=0;skill_safety_overlay(&g,m);assert(count==48&&last==0xff76e6a5&&!memcmp(px,ox,sizeof(ox))&&!memcmp(py,oy,sizeof(oy)));g.safety[0].expires=0;float ax=g.x+.1f,ay=g.y-.1f;skill_ground_snap(48,&ax,&ay);assert(ax==g.x+.1f&&ay==g.y-.1f);}puts("PASS continuous circle: preview/deployed exact pixel agreement at16 camera rotations; input retained without snapping");}
