/* Source no-save exam rooms resume at the character's outside save point. */
static const unsigned jobNoSave55[]={65,101,426,427,428,429,430,431,434,435,482,484,485,486,487,488};
static int job_no_save55(unsigned map){for(unsigned i=0;i<sizeof(jobNoSave55)/sizeof(*jobNoSave55);i++)if(jobNoSave55[i]==map)return 1;return 0;}
static WorldPosition job_save_position55(const Combat*g){WorldPosition p={g->mapId,g->x,g->y};if(job_no_save55(p.map)){p=g->home;if(!combat_position_valid(p)||job_no_save55(p.map))p=(WorldPosition){2,1244,1476};}return p;}
