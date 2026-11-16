#include <assert.h>
#include "combat.h"
static unsigned ui_skill_maximum253(const Combat*g,unsigned id){int rank=skill_rank_index(id);return g->jobId==13&&g->persistent50.copySkill==id?g->persistent50.copyRank:rank>=0?learnMax[rank]:1;}

static Combat g;int main(void){int index=skill_rank_index(338);assert(index>=0&&learnMax[index]==9);for(unsigned i=0;i<=9;i++){g.ranks[index]=i;assert(ui_skill_maximum253(&g,338)==9);}assert(ui_skill_maximum253(&g,0)==1);g.jobId=13;g.persistent50.copySkill=3;g.persistent50.copyRank=4;assert(ui_skill_maximum253(&g,3)==4);}
