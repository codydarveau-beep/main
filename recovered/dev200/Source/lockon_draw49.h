#include "effect_cache171.h"
/* GPL-3.0-or-later. Original target image and source phase/attachment rules.
 * Texture cache uses fixed integer128x128 dimensions, bounded20 colour states.
 */
#include "lockon_asset49.h"
#include "lockon_geometry49.h"
static void*lockonTextures49[20];
static void lockon_draw49(const Combat*g,const float*m){
#if LOCKON49_AVAILABLE
 int target=lockon_target49(g);if(target<0)return;const CombatMob*t=&g->mobs[target];float age=g->spellCastTotal-g->spellCastLeft;unsigned level=lockon_pulse49(age);void**slot=&lockonTextures49[level-1];if(effect_cache_prepare171(slot,65536)){unsigned char*raw=inflateasset("Original cast target",lockonPacked49,sizeof(lockonPacked49),65536);for(unsigned i=0;i<65536;i+=4){raw[i]=raw[i]*level/20;raw[i+1]=raw[i+1]*level/20;}memcpy(*slot,raw,65536);free(raw);}
 spell_world_begin41();bindTexture(*slot,128u,128u,512u,0x0001122au);float radius=lockon_width49(age)/2,angle=g->time*4.36332313f,z=height_at(t->x,t->y)+.2f;SpellPoint41 q[4];static const float corners[4][2]={{-1,-1},{1,-1},{1,1},{-1,1}};/* Source canvas keeps the original then overlays its45deg-rotated copy.
  * Two textured quads give the same alpha composition without redrawing art. */
 for(int pass=0;pass<2;pass++){float a=angle+pass*.78539816f,c=cosf(a),sn=sinf(a);for(int i=0;i<4;i++){float x=corners[i][0]*radius,y=corners[i][1]*radius;q[i]=(SpellPoint41){t->x+c*x-sn*y,t->y+sn*x+c*y,z};}float uv[8]={0,0,128,0,128,128,0,128};field_quad48(m,q,uv);}
#else
 (void)g;(void)m;
#endif
}
