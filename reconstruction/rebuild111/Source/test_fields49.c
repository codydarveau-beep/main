/* MIT. Source water-cell counts/consumption and one-active-Sage-field policy. */
#define main old_field_classes49_main
#include "test_classes48.c"
#undef main
static int allwater49(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;(void)nx;(void)ny;return 1;}
int main(void){Combat g;prepare48(&g,10);g.time=10;int yellow=class_item48(715),blue=ITEM_BLUE_GEM;int y=inventory_count(&g,yellow),b=inventory_count(&g,blue);
 class_execute48(&g,101,5,-1,g.x,g.y);assert(inventory_count(&g,yellow)==y-1);float until=g.classAreas48[0].until;assert(until>g.time);
 g.time+=10;assert(class_field_reuse49(&g,102));class_execute48(&g,102,5,-1,g.x,g.y);assert(g.classAreas48[0].id==102&&g.classAreas48[0].until==until&&inventory_count(&g,yellow)==y-1);for(int i=1;i<3;i++)assert(!g.classAreas48[i].until);
 g.inWater=NULL;int count[5]={1,9,9,25,25};for(int rank=1;rank<=5;rank++)assert(water_cells49(&g,rank,0)==count[rank-1]);assert(water_cells49(&g,5,1)==25);assert(water_cells49(&g,5,0)==0);assert(!class_field_at48(&g,102,g.x,g.y));
 g.inWater=allwater49;assert(water_cells49(&g,5,0)==25);g.inWater=NULL;
 class_execute48(&g,103,5,-1,g.x,g.y);assert(g.classAreas48[0].until==until&&inventory_count(&g,yellow)==y-1);assert(!g.classAreas48[0].waterUsed49[0]&&!g.classAreas48[0].waterUsed49[1]);
 class_execute48(&g,104,5,-1,g.x,g.y);assert(g.classAreas48[0].id==104&&inventory_count(&g,yellow)==y-2&&inventory_count(&g,blue)==b-1);assert(!class_field_reuse49(&g,101));class_execute48(&g,101,5,-1,g.x,g.y);assert(inventory_count(&g,yellow)==y-3);
 prepare48(&g,9);g.inWater=allwater49;for(int rank=1;rank<=5;rank++)assert(water_cells49(&g,rank,0)==count[rank-1]);g.inWater=NULL;assert(!water_cells49(&g,5,0));
 assert(skill_sound_id49(23)==52&&skill_sound_id49(48)==53&&skill_sound_id49(116)==54&&skill_sound_id49(88)==55&&skill_sound_id49(78)==56&&skill_sound_id49(75)==57);
 puts("PASS49 Water Ball1/9/9/25/25 actual cells, Deluge consumption/field holes, native water, Sage replacement/retained timer/free elemental swaps, LP reagents/reset and original sound IDs.");}
