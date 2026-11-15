/* MIT. Actual original texture uploads, alpha, source pulse and two-layer draw. */
#define CLASS_ART49_ENTRY old_original_class_art49_main
#include "test_class_art48.c"
#undef CLASS_ART49_ENTRY
int main(void){assert(LOCKON49_AVAILABLE);Combat g;combat_init(&g,1500,1500,NULL,NULL);g.time=100;g.spellCastTarget=0;g.spellCastLife=7;g.spellCastTotal=2;g.mobs[0].enabled=1;g.mobs[0].hp=100;g.mobs[0].life=7;g.mobs[0].x=g.x+24;g.mobs[0].y=g.y;float m[16];world_camera(m,g.x,g.y,0,0,.785f,1.2f);
 unsigned char*original=inflateasset("original lock-on",lockonPacked49,sizeof(lockonPacked49),65536);unsigned partial=0;for(int i=0;i<65536;i+=4)partial+=original[i+3]>0&&original[i+3]<255;assert(partial>0);
 for(int phase=0;phase<20;phase++){float age=phase*.02f+.005f;g.time=100+age;g.spellCastLeft=2-age;unsigned level=lockon_pulse49(g.spellCastTotal-g.spellCastLeft);vertices48=quads48=0;lockon_draw49(&g,m);assert(vertices48==8&&quads48==2);unsigned char*actual=lockonTextures49[level-1];assert(actual);for(unsigned p=0;p<65536;p+=4){assert(actual[p]==original[p]*level/20);assert(actual[p+1]==original[p+1]*level/20);assert(actual[p+2]==original[p+2]&&actual[p+3]==original[p+3]);}}
 for(int i=0;i<20;i++)assert(lockonTextures49[i]);g.mobs[0].x+=8;vertices48=0;lockon_draw49(&g,m);assert(vertices48==8);g.mobs[0].life++;vertices48=0;lockon_draw49(&g,m);assert(!vertices48);g.mobs[0].life=7;g.spellCastLeft=0;lockon_draw49(&g,m);assert(!vertices48);
 for(int i=0;i<20;i++)free(lockonTextures49[i]);free(original);
 puts("PASS49 original128x128 cast graphic:20 actual integer-size GPU uploads, exact source RGB pulse/all alpha pixels retained, original+45deg copy, two finite quads,1.25MiB cache, moving-target/life/completion guards.");}
