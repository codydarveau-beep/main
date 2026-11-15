/* MIT. Fixed choices; exact source Hindsight unlock thresholds. */
static const unsigned char classAutoIDs48[]={22,3,9,21,23,24,29};
static const unsigned char classAutoNeeds48[]={1,2,2,2,5,8,10};
static int class_item48(int source);
static int class_auto_choice48(const Combat*g,int row){int rank=skill_rank(g,95);for(int i=0;i<7;i++)if(rank>=classAutoNeeds48[i]&&skill_rank(g,classAutoIDs48[i])&&row--==0)return classAutoIDs48[i];return -1;}
static int class_auto_count48(const Combat*g){int n=0;while(class_auto_choice48(g,n)>=0)n++;return n;}
static int class_craft48(Combat*g,int choice);
static int class_choose_auto48(Combat*g,int choice);
