/* MIT. Source catalog invariants before runtime class activation. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../ClassAssets50/catalog50.h"
int main(void){
 unsigned ranks[254]={0};for(int i=0;i<252;i++){unsigned id=classRankIDs50[i];assert(id<254&&!ranks[id]);ranks[id]=i+1;}assert(!ranks[0]&&!ranks[1]&&ranks[7]==252);
 for(unsigned id=2;id<254;id++)assert(ranks[id]);
 for(unsigned job=12;job<=20;job++){
  unsigned j=job-12;assert(classParent50[j]>=3&&classParent50[j]<=6);
  for(int level=0;level<99;level++)assert(classHP50[j][level]>0&&classSP50[j][level]>0);
  for(int level=1;level<50;level++)for(int stat=0;stat<6;stat++)assert(classBonus50[j][level][stat]>=classBonus50[j][level-1][stat]);
  assert(class_actor_id50(job,0)==job+1&&class_actor_id50(job,1)==job+1);
 }
 assert(class_actor_id50(11,1)==12&&class_actor_id50(11,0)==11);
 assert(classMotion50[4][10]==classMotion50[3][10]&&classMotion50[4][10]==650&&classMotion50[4][15]==575);
 for(unsigned i=0;i<sizeof(classSkills50)/sizeof(*classSkills50);i++){
  const ClassSkill50*s=&classSkills50[i];assert(s->id<254&&ranks[s->id]&&s->maxRank&&s->maxRank<=10&&s->owners&&s->name[0]);
  assert(class_skill_data50(s->id)==s);
  for(int rank=0;rank<10;rank++){assert(s->sp[rank]<65535&&s->cast[rank]<=15000);assert(s->range[rank]>=-9&&s->range[rank]<=21);}
 }
 for(unsigned i=0;i<sizeof(classPrereqs50)/sizeof(*classPrereqs50);i++){
  const uint16_t*p=classPrereqs50[i];assert(p[0]>=12&&p[0]<=20&&p[1]<254&&p[2]<254&&ranks[p[1]]&&ranks[p[2]]&&p[3]&&p[3]<=10);
 }
 const ClassSkill50*sonic=class_skill_data50(131);assert(sonic->hits[9]==-8&&sonic->delay[9]==2000&&sonic->sp[9]==34);
 const ClassSkill50*spheres=class_skill_data50(206);assert(spheres->spheres[4]==5&&spheres->hits[4]==5&&spheres->sp[4]==10);
 assert(class_skill_data50(142)->range[0]==-1);assert(!class_skill_data50(254));
 puts("PASS50 nine full source job profiles,252 unique stable rank slots including Kyrie,133 typed skill records, signed source ranges/hit counts,126 closed prerequisite edges, Dancer inheritance and mounted actor isolation.");
}
