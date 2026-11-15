/* MIT. Copy only a supported damaging skill after surviving its incoming hit. */
static int class_copyable50(unsigned id){return id>=2&&id<SKILL_COUNT&&!skill_passive(id)&&id!=5&&id!=6&&!(id>=85&&id<=88)&&id!=171&&id!=253;}
static void class_copy_received50(Combat*g,unsigned id,int rank,int damage){
 if(class_active50(g,SK52_ST_PRESERVE)||job_parent52(g->jobId)!=13||damage<=0||damage>=g->hp||!class_rank50(g,152)||!class_copyable50(id))return;
 int k=skill_rank_index(id);if(k<0||g->ranks[k])return;if(rank>class_rank50(g,152))rank=class_rank50(g,152);if(rank>learnMax[k])rank=learnMax[k];if(rank<1)return;
 unsigned old=g->persistent50.copySkill;if(old&&old!=id){int previous=skill_rank_index(old);if(previous<0||!g->ranks[previous]){for(int i=0;i<12;i++)if(g->hotbar[i]==old)g->hotbar[i]=BIND_EMPTY50;if(g->quickKind==1&&g->quickId==old){g->quickKind=2;g->quickId=0;}if(g->rbBinding==old)g->rbBinding=BIND_EMPTY50;}}
 g->persistent50.copySkill=id;g->persistent50.copyRank=rank;combat_notice(g,POP_SKILLS,"Copied %s rank %d.",skillDefs[id].name,rank);
}
