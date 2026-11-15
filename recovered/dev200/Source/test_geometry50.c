/* MIT. Regression for inverted horns and Safety Wall actor enclosure. */
#define CLASS_ART49_ENTRY old_class_geometry50_main
#include "test_class_art48.c"
#undef CLASS_ART49_ENTRY
int main(void){
 for(unsigned seed=0;seed<40;seed++)for(int horn=0;horn<3;horn++)for(int face=0;face<4;face++){SpellPoint41 q[3];float uv[6];ice_face48(500,500,12,seed,horn,face,1,q,uv);assert(q[0].z>q[1].z+30&&q[1].z==q[2].z&&fabsf(q[1].z-11.2f)<.001f);}
 Combat g;combat_init(&g,1500,1500,NULL,NULL);g.time=10;g.safety[0]=(SafetyWall){g.x,g.y,100,0,11,1};float m[16];
 for(int yaw=0;yaw<64;yaw++){world_camera(m,g.x,g.y,0,yaw*6.2831853f/64,.8f,1.2f);unsigned halves[2];for(int front=0;front<2;front++){vertices48=quads48=0;safety_draw50(&g,m,front);assert(vertices48%4==0&&quads48==vertices48/4+2);halves[front]=vertices48/4;assert(halves[front]>0&&halves[front]<60);}assert(halves[0]+halves[1]==60);for(int face=0;face<20;face++){int front=safety_front50(m,g.time,face);assert(front==0||front==1);}}
 g.safety[0].hits=0;vertices48=0;safety_draw50(&g,m,0);safety_draw50(&g,m,1);assert(!vertices48);
 for(int i=0;i<9;i++)for(int n=0;n<16;n++)for(int t=0;t<2;t++)if(fieldTextures48[i][n][t])free(fieldTextures48[i][n][t]);
 puts("PASS50 Ice Wall tips above grounded bases across480 horn faces; Safety Wall front/back encloses actors with each of60 faces exactly once for64 camera angles, preserves expiration/hit rules.");}
