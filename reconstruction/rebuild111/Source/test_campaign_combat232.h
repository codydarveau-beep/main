/* Functional encounter acceptance with a qualified host character with explicit HP/SP topups.
 * Real authored enemies/HP, player combat/AI/defenses, companion AI, rewards and
 * native monster-death callback execute. This is not a balance or target test. */
#include "npc_game55.h"
static NpcGame55 deathContext232;
static unsigned encounterKills232,encounterTicks232;
/* Scripted controller steering after long knockback. Uses the real collision
 * predicate; no teleport, enemy weakening or production navigation changes. */
static void combat_steer232(const CombatMob*enemy,float*mx,float*my){
 Combat*g=&player200;*mx=*my=0;if(combat_dist(g->x,g->y,enemy->x,enemy->y)<=176)return;
 unsigned n=gw*gh,start=(unsigned)(g->y/8)*gw+(unsigned)(g->x/8),*queue=malloc(n*sizeof(*queue)),*parent=malloc(n*sizeof(*parent));assert(queue&&parent&&start<n);for(unsigned i=0;i<n;i++)parent[i]=~0u;parent[start]=start;queue[0]=start;unsigned head=0,tail=1,goal=~0u;
 while(head<tail){unsigned node=queue[head++];float x=node==start?g->x:(node%gw)*8+4,y=node==start?g->y:(node/gw)*8+4;if(combat_dist(x,y,enemy->x,enemy->y)<=128){goal=node;break;}int dx[]={-1,1,0,0},dy[]={0,0,-1,1};for(unsigned i=0;i<4;i++){int xx=(int)(node%gw)+dx[i],yy=(int)(node/gw)+dy[i];if(xx<1||yy<1||xx>=(int)gw-1||yy>=(int)gh-1)continue;unsigned next=(unsigned)yy*gw+(unsigned)xx;if(parent[next]!=~0u||!world_can_move(NULL,x,y,xx*8+4,yy*8+4))continue;parent[next]=node;queue[tail++]=next;}}
 if(goal!=~0u&&goal!=start){while(parent[goal]!=start)goal=parent[goal];float dx=(goal%gw)*8+4-g->x,dy=(goal/gw)*8+4-g->y,d=sqrtf(dx*dx+dy*dy);if(d>0){*mx=dx/d;*my=dy/d;}}
 free(queue);free(parent);
}
static void sequence_combat232(CombatMob*enemy){
 Combat*g=&player200;assert(enemy->enabled&&enemy->hp>0);unsigned target=(unsigned)(enemy-g->mobs),life=enemy->life,kills=g->kills;int peaceful=g->peaceful;g->peaceful=0;g->debugImmortal=0;
 /* Explicit combat calibration. Ordinary growth traversal is separately tested
  * without these fixture stats in Campaign-Companions-Checks226.json. */
 g->level=150;unsigned char stats[6]={99,50,50,99,99,1};memcpy(g->stats,stats,6);g->statPoints=stat_budget(g->level)-stat_spent(g->stats);assert(g->statPoints>=0);stat_refresh(g);g->hp=g->maxhp;g->sp=g->maxsp;
 deathContext232.player.game=g;deathContext232.monsters=monsters200;combat_npc_context55=&deathContext232;combat_npc_kill55=npc_game_mob_killed55;combat_companion_field194=party_wizard_hit194;
 for(unsigned tick=0;enemy->hp>0&&tick<120000;tick++){
  assert(enemy->life==life);g->hp=g->maxhp;g->sp=g->maxsp;g->target=(int)target;g->autoAttack=1;g->floorPickup58=-1;campaign_party_bind200(g);campaign_follow_tick200(&campaignParty200,g,.05f,0);float mx,my;combat_steer232(enemy,&mx,&my);combat_tick(g,.05f,mx,my);g->hp=g->maxhp;g->sp=g->maxsp;campaign_battle_tick200(g,.05f,0);encounterTicks232++;
 }
 if(enemy->hp>0)fprintf(stderr,"Encounter combat did not finish: cursor %u kind %u hp %d player %.0f %.0f enemy %.0f %.0f\n",campaignEncounter198.cursor,enemy->kind,enemy->hp,g->x,g->y,enemy->x,enemy->y);
 assert(enemy->hp<=0&&enemy->life==life&&g->kills>=kills+1);assert(enemy->npcSpawn55&&enemy->npcSpawn55<=monsters200.count&&!monsters200.rows[enemy->npcSpawn55-1].alive);g->autoAttack=0;g->target=-1;g->peaceful=peaceful;deathContext232.monsters.rows=NULL;deathContext232.monsters.count=deathContext232.monsters.capacity=0;encounterKills232++;
}
