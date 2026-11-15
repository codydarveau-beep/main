/* Exact original base-actor/job to promoted-actor mapping. */
#ifndef MYRO_COMPANION_ART200_H
#define MYRO_COMPANION_ART200_H
static unsigned party_actor_source200(unsigned base,unsigned job){
 static const unsigned char variants[][3]={{1,11,28},{2,17,29},{11,13,30},{7,21,31},{1,22,32},{8,8,33},{12,23,34},{2,24,35},{13,25,36},{10,26,37},{11,27,38},{4,28,39},{14,29,40},{15,30,41},{16,31,42},{5,32,43},{9,40,44}};
 for(unsigned i=0;i<sizeof(variants)/sizeof(variants[0]);i++)if(variants[i][0]==base&&variants[i][1]==job)return variants[i][2];
 return base;
}
#endif
