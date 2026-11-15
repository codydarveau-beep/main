/* MIT. Divide translucent cylinder faces using camera depth at their midpoint.
 * Back faces precede the actors; front faces follow them. Each face draws once.
 */
static int safety_front50(const float*m,float angle,int face){float a=angle+(face+.5f)*6.2831853f/20;return m[8]*sinf(a)+m[9]*cosf(a)<0;}

/* Actor planes do not write depth. Choose the whole wall's side when outside,
 * splitting cylinder faces only while standing inside the wall. */
static int safety_actor_front52(const float*m,float wx,float wy,float px,float py,float angle,int face){
 float dx=px-wx,dy=py-wy;if(dx*dx+dy*dy<=5.6f*5.6f)return safety_front50(m,angle,face);
 return m[8]*(wx-px)+m[9]*(wy-py)<0;
}
