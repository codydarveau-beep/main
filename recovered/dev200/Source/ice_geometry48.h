/* GPL-3.0-or-later. RO-compatible QuadHorn geometry/parameters.
 * Reference: roBrowserLegacy2dc0d153, EffectTable EF_ICEWALL74 / QuadHorn.js/.vs.
 * Test50 fixes the source-to-native vertical axis: base remains at ground, tip rises.
 * This original implementation uses the same three horns, height/size ranges and UVs.
 */
static unsigned ice_hash48(unsigned seed){seed^=seed>>16;seed*=0x7feb352du;seed^=seed>>15;seed*=0x846ca68bu;return seed^(seed>>16);}
static float ice_unit48(unsigned seed){return (ice_hash48(seed)&65535)/65535.f;}
static void ice_face48(float x,float y,float z,unsigned seed,int horn,int face,float age,SpellPoint41 q[3],float uv[6]){
 static const float lo[3]={2.8f,2.3f,2.5f};static const float uvAll[4][6]={{0,0,1,0,1,1},{0,0,1,1,0,1},{1,0,1,1,0,1},{1,0,0,1,0,0}};
 static const float corners[4][2]={{-1,1},{1,1},{1,-1},{-1,-1}};
 unsigned hseed=seed+horn*997;float height=lo[horn]+ice_unit48(hseed)*.5f;if(age<height*.05f)height=age/.05f;if(height<0)height=0;float size=(.3f+ice_unit48(hseed+1)*.2f)*8,angle=ice_unit48(hseed+2)*6.2831853f,c=cosf(angle),s=sinf(angle),ox=(ice_unit48(hseed+3)*.5f-.25f)*8,oy=(ice_unit48(hseed+4)*.5f-.25f)*8;
 q[0]=(SpellPoint41){x+ox,y+oy,z+(2*height-.1f)*8};for(int v=1;v<3;v++){int k=(face+v-1)&3;float a=corners[k][0]*size,b=corners[k][1]*size;q[v]=(SpellPoint41){x+ox+c*a-s*b,y+oy+s*a+c*b,z-.8f};}for(int v=0;v<6;v++)uv[v]=uvAll[face][v]*128;
}
