/* Original independent job-level learning paths; three fixed caches, no heap. */
#ifndef MYRO_COMPANION_SKILLS201_H
#define MYRO_COMPANION_SKILLS201_H
#include "companion_skills_data201.h"
#include "companion_progress200.h"
typedef struct{unsigned id,job,level,valid;unsigned char ranks[401];}PartySkillCache201;
static PartySkillCache201 partySkillCache201[3];
static unsigned partySkillNext201;
static unsigned party_path_job_cap201(unsigned job){return job==41||job==42||job==8?70:job==33||!job?10:job==40?99:job>20&&job<=32?70:50;}
static unsigned party_skill_path_rank201(unsigned id,unsigned job,unsigned level,unsigned skill){
 if(id>=19)return 0;
 if(skill==338)return 9;
 if((id==4&&skill==51)||((id==12||id==13)&&skill==1))return 1;
 if(!job)job=partyInitialJobs200[id];
 if(!level||level>party_path_job_cap201(job))return 0;
 unsigned index=401;for(unsigned k=0;k<401;k++)if(partySkillIDs201[k]==skill){index=k;break;}
 if(index==401)return 0;
 for(unsigned i=0;i<3;i++){const PartySkillCache201*c=partySkillCache201+i;if(c->valid&&c->id==id&&c->job==job&&c->level==level)return c->ranks[index];}
 const PartySkillPath201*path=NULL;for(unsigned k=0;k<36;k++)if(partySkillPaths201[k].id==id&&partySkillPaths201[k].job==job){path=partySkillPaths201+k;break;}
 if(!path)return 0;
 PartySkillCache201*c=partySkillCache201+partySkillNext201++%3;memset(c,0,sizeof(*c));c->id=id;c->job=job;c->level=level;c->valid=1;
 unsigned count=level+path->start-1;if(count>path->count)count=path->count;
 for(unsigned k=0;k<count;k++){unsigned n=path->queue[k];if(n<401&&c->ranks[n]<partySkillCaps201[n])c->ranks[n]++;}
 return c->ranks[index];
}
#endif
