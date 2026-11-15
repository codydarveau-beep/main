/* MIT. Exercise actual equipment, damage and persistence with both hands. */
#define main preceding_class_tests50
#include "test_classes48.c"
#undef main
int main(void){Combat g,h;prepare48(&g,12);inventory_remove46(&g,0);inventory_remove46(&g,3);int knife=ITEM_KNIFE,sword=item_source50(1101),axe=item_source50(1301),katar=item_source50(1250);assert(sword>=0&&axe>=0&&katar>=0);
 *inventory_stack(&g,knife)=1;assert(inventory_equip_slot50(&g,knife,0));assert(!inventory_equip_slot50(&g,knife,3));*inventory_stack(&g,knife)=2;assert(inventory_equip_slot50(&g,knife,3));assert(class_offhand50(&g)==knife&&class_dual_gear50(&g)==201&&inventory_defense(&g)>=0);
 SavedCharacter a,b;unsigned char raw[SAVE_BYTES];save_capture(&a,&g,4);assert(save_valid(&a));save_encode(raw,&a);assert(save_decode(&b,raw));save_restore(&h,&b,1500,1500,clear48,NULL);assert(inventory_slot46(&h,0)==knife&&class_offhand50(&h)==knife);
 a.extraItems[knife-3]=1;assert(!save_valid(&a));inventory_remove46(&g,3);assert(inventory_slot46(&g,0)==knife&&(g.equipment&itemDefs[knife].equipBit));assert(inventory_equip_slot50(&g,knife,3));inventory_remove46(&g,0);assert(class_offhand50(&g)<0&&inventory_slot46(&g,0)<0);
 int ids[3]={knife,sword,axe};unsigned gears[3][3]={{201,204,205},{204,202,206},{205,206,203}};
 for(int i=0;i<3;i++)for(int j=0;j<3;j++){*inventory_stack(&g,ids[i])=2;*inventory_stack(&g,ids[j])=2;assert(inventory_equip_slot50(&g,ids[i],0));assert(inventory_equip_slot50(&g,ids[j],3));assert(class_dual_gear50(&g)==gears[i][j]);save_capture(&a,&g,4);assert(save_valid(&a));inventory_reconcile46(&g);assert(class_offhand50(&g)==ids[j]);}
 *inventory_stack(&g,katar)=1;assert(inventory_equip_slot50(&g,katar,0)&&class_offhand50(&g)<0);assert(!inventory_equip_slot50(&g,knife,3));*inventory_stack(&g,knife)=2;assert(inventory_equip_slot50(&g,knife,0)&&inventory_equip_slot50(&g,knife,3));
 CombatMob*m=&g.mobs[MOB_COUNT-1];g.ranks[128-3]=0;g.rng=123;int low=class_offhand_damage50(&g,m);g.ranks[128-3]=5;g.rng=123;assert(class_offhand_damage50(&g,m)>low);int hp=m->hp;class_after_attack50(&g,MOB_COUNT-1);assert(m->hp<hp);
 *inventory_stack(&g,knife)=1;inventory_reconcile46(&g);assert(class_offhand50(&g)<0&&inventory_slot46(&g,0)==knife);g.jobId=13;assert(!inventory_fits50(&g,knife,3));
 puts("PASS50 dual-wield copy counts, nine original hand combinations, source left mastery damage, real off-hand hit, shield/two-hand transitions, class gates and Save50 corruption rejection.");}
