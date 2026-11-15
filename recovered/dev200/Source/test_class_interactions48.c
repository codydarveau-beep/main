/* MIT. Cross-system second-class regressions, not duplicate formula fixtures. */
#define main classes48_other_main
#include "test_classes48.c"
#undef main
int main(void){Combat g;
 for(unsigned i=0;i<sizeof(classPrereqs48)/sizeof(*classPrereqs48);i++){const uint16_t*p=classPrereqs48[i];prepare48(&g,p[0]);int id=p[1],parent=skill_rank_index(p[2]);if(!job_owns_skill48(g.jobId,p[0],id)){assert(!skill_learn(&g,id));continue;}g.ranks[skill_rank_index(id)]=0;g.ranks[parent]=p[3]-1;g.skillPoints=100;assert(!skill_learn(&g,id));g.ranks[parent]=p[3];if(!skill_learn(&g,id)){fprintf(stderr,"edge %u job%d id%d parent%d: %s\n",i,p[0],id,p[2],g.log);abort();}}
 prepare48(&g,3);assert(!class_missing_prereq48(3,10,g.ranks));
 prepare48(&g,10);CombatMob*m=&g.mobs[MOB_COUNT-1];int native=class_element_rate48(m,3);g.classAreas48[0]=(ClassArea48){.id=101,.rank=5,.x=g.x,.y=g.y,.until=100,.map=g.mapId};assert(class_attack_rate48(&g,m,3)==native+20);g.x+=40;assert(class_attack_rate48(&g,m,3)==native);g.x-=40;
 g.classAreas48[0]=(ClassArea48){.id=89,.rank=5,.x=g.x+16,.y=g.y,.until=100,.map=g.mapId,.axis=1,.hp={100,100,100,100,100}};assert(!class_ice_line48(&g,g.x,g.y,g.x+40,g.y));assert(class_ice_line48(&g,g.x,g.y-40,g.x+40,g.y-40));g.classAreas48[0].hp[2]=0;assert(class_ice_line48(&g,g.x,g.y,g.x+40,g.y));
 prepare48(&g,10);m=&g.mobs[MOB_COUNT-1];g.sp=g.maxsp-100;m->castUntil48=g.time+.1f;m->castRank48=3;m->castSkill48=3;m->castSP48=16;class_buff48(&g,92,5);int hp=g.hp,sp=g.sp;for(int tick=0;tick<3;tick++)combat_tick(&g,.04f,0,0);assert(g.hp==hp&&g.sp==sp+16&&!m->castUntil48);
 prepare48(&g,10);m=&g.mobs[MOB_COUNT-1];g.sp=g.maxsp-100;g.hp/=2;m->castUntil48=g.time+10;m->castRank48=3;m->castSkill48=3;m->castSP48=16;sp=g.sp;assert(cast48(&g,93));assert(!m->castUntil48&&g.sp==sp-skill_cost(&g,93)+16&&m->hp<1000000);
 prepare48(&g,11);DeveloperUI u;dev_open(&u,&g);u.row=7;dev_input(&u,&g,2);assert(g.mounted48);SavedCharacter s;save_capture(&s,&g,1);assert(save_valid(&s));dev_input(&u,&g,2);assert(!g.mounted48);
 prepare48(&g,10);int book=item_source50(1550);assert(itemDefs[book].id==1550&&inventory_count(&g,book)>0);inventory_action(&g,book);assert(inventory_wtype46(&g)==11);int attack=combat_physical(&g),motion=stat_amotion48(&g);g.ranks[90-3]=0;assert(combat_physical(&g)==attack-30&&stat_amotion48(&g)>motion);
 prepare48(&g,10);class_buff48(&g,95,10);g.autoSpell48=3;int spent=g.sp;for(int i=0;i<100&&g.sp==spent;i++)class_autospell48(&g,MOB_COUNT-1);assert(g.sp<spent&&g.fxSkill==3&&g.fxRank48==3&&g.mobs[MOB_COUNT-1].hp<1000000);
 puts("PASS48 all supported source prerequisite edges and deferred Spirit gates, shared Heal class isolation, source elemental field bonus, Ice Wall line blocking/gaps, real incoming Magic Rod/Spell Breaker, mount save/toggle and equipped Book Study.");}
