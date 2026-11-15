/* MIT. Hocus rolls stay transient and use the normal cast/aim validation. */
#define main classes48_other_main
#include "test_classes48.c"
#undef main
int main(void){Combat g;unsigned seen=0;
 for(int rank=1;rank<=10;rank++)for(int seed=1;seed<=400;seed++){
  prepare48(&g,10);g.rng=seed;
  class_hocus_roll48(&g,rank);assert(g.hocusID48&&g.hocusRank48<=rank);
  int found=0;for(unsigned i=0;i<sizeof(hocusPool48)/sizeof(*hocusPool48);i++)if(hocusPool48[i].id==g.hocusID48){assert(rank>=hocusPool48[i].need);found=1;seen|=1u<<i;}assert(found);
 }
 assert(seen==((1u<<24)-1));
 prepare48(&g,10);int gem=class_item48(715),gems=inventory_count(&g,gem),sp=g.sp,cost=skill_cost(&g,106);
 assert(cast48(&g,106));assert(g.hocusID48&&inventory_count(&g,gem)==gems-2&&g.sp==sp-cost);
 int id=g.hocusID48;assert(hot_binding(&g)==(unsigned)id);combat_cancel(&g);assert(!g.hocusID48);
 for(unsigned i=0;i<sizeof(hocusPool48)/sizeof(*hocusPool48);i++){
  prepare48(&g,10);id=hocusPool48[i].id;g.hocusID48=id;g.hocusRank48=hocusPool48[i].max;g.sp=0;g.hp/=2;g.blindLeft=1;g.poisonLeft=1;
  unsigned char ranks[LEARN_COUNT];memcpy(ranks,g.ranks,LEARN_COUNT);sp=g.sp;
  if(!cast48(&g,id)){fprintf(stderr,"Hocus outcome %d: %s\n",id,g.log);abort();}
  assert(!g.hocusID48&&g.sp==sp&&!memcmp(ranks,g.ranks,LEARN_COUNT));
 }
 prepare48(&g,10);g.hocusID48=3;g.hocusRank48=10;g.target=-1;memset(g.mobs,0,sizeof(g.mobs));assert(!skill_cast(&g,3,g.x,g.y)&&g.hocusID48==3);
 g.hocusID48=2;g.hocusRank48=10;g.ranks[skill_rank_index(2)]=0;assert(!skill_assign(&g,0,2));g.hocusID48=3;g.hocusRank48=10;
 SavedCharacter saved;save_capture(&saved,&g,1);assert(save_valid(&saved));combat_support_clear(&g);assert(!g.hocusID48&&!g.hocusRank48);
 puts("PASS48 Hocus: 4000 eligible weighted rolls, all 24 outcomes cast at zero extra SP, two gemstones once, failed target retains roll, discard, unchanged learned ranks and save isolation.");
}
