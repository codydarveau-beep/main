/* MIT. Bounded prototype ground geometry; no resource/collision changes. */
#ifndef MYRO_SPELL_GEOMETRY41_H
#define MYRO_SPELL_GEOMETRY41_H
typedef struct{float x,y,z;} SpellPoint41;
static void spell_line_quad41(float ax,float ay,float bx,float by,float z,float width,SpellPoint41*p){float dx=bx-ax,dy=by-ay,len=sqrtf(dx*dx+dy*dy),nx=0,ny=0;if(len>.0001f){nx=-dy/len*width*.5f;ny=dx/len*width*.5f;}p[0]=(SpellPoint41){ax+nx,ay+ny,z};p[1]=(SpellPoint41){bx+nx,by+ny,z};p[2]=(SpellPoint41){bx-nx,by-ny,z};p[3]=(SpellPoint41){ax-nx,ay-ny,z};}
static void spell_cone_face41(float x,float y,float z,int face,SpellPoint41*p){static const float corners[4][2]={{-.9f,-.9f},{.9f,-.9f},{.9f,.9f},{-.9f,.9f}};int j=(face+1)%4;p[0]=(SpellPoint41){x+corners[face][0],y+corners[face][1],z};p[1]=(SpellPoint41){x+corners[j][0],y+corners[j][1],z};p[2]=p[3]=(SpellPoint41){x,y,z+2};}
/* EF_LOCKON is class independent: timed cast aimed at another entity.
 * The caller requires a live cast/target. It is distinct from caster aura,
 * whose separate hideCastAura flags do not suppress this target marker. */
static int spell_circle_skill41(int id){return id>0;}

static float spell_circle_radius43(float elapsed,float diameter){float t=elapsed/.6f;if(t<0)t=0;if(t>1)t=1;if(diameter<16)diameter=16;if(diameter>56)diameter=56;return fmaxf(36,diameter*.85f)*.9f+(56-fmaxf(36,diameter*.85f)*.9f)*(1-t);}
static void spell_storm_point41(int bolt,int pulse,float*x,float*y){float a=bolt*2.399963f+pulse*.61f,r=6+(bolt%3)*5;*x=cosf(a)*r;*y=sinf(a)*r;}
#endif
