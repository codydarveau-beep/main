static unsigned ui_skill_maximum253(const Combat*g,unsigned id){int rank=skill_rank_index(id);return g->jobId==13&&g->persistent50.copySkill==id?g->persistent50.copyRank:rank>=0?learnMax[rank]:1;}
