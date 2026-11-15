/* Source: Hercules v2021.12.01 db/abra_db.txt (21b27966cfc2e7df0bf8151cd717a1105d047ba9).
 * Deliberately bounded to audited existing single-player effects. Source weights
 * are renormalized over eligible entries; no special outcome commands yet. */
static const struct {unsigned char id,max,need;unsigned short weight;} hocusPool48[]={
 {2,10,1,5000}, /* Bash */
 {8,10,1,5000}, /* Magnum Break */
 {28,10,1,5000}, /* Endure */
 {36,1,1,5000}, /* Sight */
 {22,10,1,5000}, /* Napalm Beat */
 {23,10,2,5000}, /* Soul Strike */
 {9,10,1,5000}, /* Cold Bolt */
 {29,10,2,5000}, /* Frost Diver */
 {24,10,2,5000}, /* Fire Ball */
 {31,10,4,5000}, /* Fire Wall */
 {3,10,1,5000}, /* Fire Bolt */
 {21,10,1,5000}, /* Lightning Bolt */
 {30,10,2,5000}, /* Thunder Storm */
 {40,1,1,5000}, /* Ruwach */
 {10,10,1,5000}, /* Heal */
 {6,10,2,5000}, /* Increase AGI */
 {41,10,4,5000}, /* Decrease AGI */
 {43,10,1,5000}, /* Signum Crucis */
 {33,10,1,5000}, /* Angelus */
 {5,10,2,5000}, /* Blessing */
 {50,1,1,5000}, /* Cure */
 {38,10,2,5000}, /* Hiding */
 {13,10,1,5000}, /* Envenom */
 {14,1,1,5000}, /* Detoxify */
};
static void class_hocus_roll48(Combat*g,int rank){
 unsigned total=0;for(unsigned i=0;i<sizeof(hocusPool48)/sizeof(*hocusPool48);i++)if(rank>=hocusPool48[i].need)total+=hocusPool48[i].weight;
 if(!total)return;
 unsigned roll=combat_random(g)%total;
 for(unsigned i=0;i<sizeof(hocusPool48)/sizeof(*hocusPool48);i++)if(rank>=hocusPool48[i].need){if(roll<hocusPool48[i].weight){g->hocusID48=hocusPool48[i].id;g->hocusRank48=rank<hocusPool48[i].max?rank:hocusPool48[i].max;g->castDelay=0;combat_notice(g,POP_SKILLS,"Hocus-pocus: %s Lv%d. A: use, B: discard.",skillDefs[g->hocusID48].name,g->hocusRank48);return;}roll-=hocusPool48[i].weight;}
}
