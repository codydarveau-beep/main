/* Exact original career skill ratios; distinct from Bash and spell hit counts. */
#ifndef MYRO_COMPANION_MULTIPLIERS203_H
#define MYRO_COMPANION_MULTIPLIERS203_H
static unsigned party_skill_ratio203(unsigned skill,unsigned rank){
 static const unsigned short cases[][3]={{142,300,40},{173,125,25},{180,125,25},{202,100,20},{211,150,50},{378,100,10},{386,160,20},{388,160,20},{390,190,30},{392,190,30}};
 for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);i++)if(cases[i][0]==skill)return cases[i][1]+cases[i][2]*rank;
 return 100;
}
#endif
