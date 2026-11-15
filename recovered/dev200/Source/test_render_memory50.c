/* MIT. Actual opacity/target caches: exact pixels after fenced reclamation. */
#define CLASS_ART49_ENTRY old_class_memory50_main
#include "test_class_art48.c"
#undef CLASS_ART49_ENTRY
static void*iceTexture48;
static unsigned gpuBusy50,freed50;
static int pb_busy(void){if(gpuBusy50){gpuBusy50--;return 1;}return 0;}
static void MmFreeContiguousMemory(void*p){assert(p&&!gpuBusy50);freed50++;free(p);}
#include "render_cache50.h"
static unsigned populate50(Combat*g,const float*m){
 unsigned crc=0;
 for(int index=0;index<FIELD_TEXTURE_COUNT50;index++)for(int level=1;level<=15;level++)for(int threshold=0;threshold<2;threshold++){
  field_bind48(index,level,threshold);unsigned bytes=fieldTexDefs48[index].side*fieldTexDefs48[index].side*4;
  crc=crc32(crc,fieldTextures48[index][level][threshold],bytes);
 }
 for(int phase=0;phase<20;phase++){
  float age=phase*.02f+.005f;g->time=100+age;g->spellCastLeft=2-age;lockon_draw49(g,m);
 }
 for(int i=0;i<20;i++){assert(lockonTextures49[i]);crc=crc32(crc,lockonTextures49[i],65536);}
 iceTexture48=gpu_alloc(65536);memset(iceTexture48,77,65536);return crc;
}
int main(void){
 Combat g;combat_init(&g,1500,1500,NULL,NULL);g.time=100;g.spellCastTarget=0;g.spellCastLife=7;g.spellCastTotal=2;g.mobs[0].enabled=1;g.mobs[0].hp=100;g.mobs[0].life=7;g.mobs[0].x=g.x+24;g.mobs[0].y=g.y;
 float m[16];world_camera(m,g.x,g.y,0,0,.785f,1.2f);
 unsigned checksum=populate50(&g,m),bytes=spell_texture_bytes50();assert(bytes==30*(9*16384+2*65536)+20*65536+65536);
 for(int round=0;round<4;round++){
  gpuBusy50=2;unsigned before=freed50;spell_texture_release50();assert(!gpuBusy50&&!spell_texture_bytes50()&&freed50==before+351);
  spell_texture_release50();assert(freed50==before+351);assert(populate50(&g,m)==checksum&&spell_texture_bytes50()==bytes);
 }
 visualCacheRelease50=spell_texture_release50;art39_prepare45(9,0);assert(!spell_texture_bytes50());
 field_bind48(7,15,0);assert(spell_texture_bytes50()==65536);unsigned before=freed50;art39_prepare45(9,0);assert(freed50==before&&spell_texture_bytes50()==65536);
 gpuBusy50=1;art39_prepare45(11,0);assert(!spell_texture_bytes50()&&freed50==before+1);
 for(unsigned i=0;i<ART39_COUNT;i++)free(art39Sprites[i].raw);
 visualCacheRelease50=NULL;
 printf("PASS50 all330 opacity variants+20 original target states+Ice Wall: %u bytes reclaimed after GPU fence, four exact-pixel rebuilds, idempotent release, class changes reclaim and same-class reuse preserves caches.\n",bytes);
}
