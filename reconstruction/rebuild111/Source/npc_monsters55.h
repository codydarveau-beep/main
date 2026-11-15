/* MIT. Script-created solo encounters; native combat owns active-map simulation. */
#ifndef MYRO_NPC_MONSTERS55_H
#define MYRO_NPC_MONSTERS55_H
#define NPC_MONSTERS_LIMIT55 1024u
typedef struct{uint32_t map,kind,serial,npc,entry;int slot,hp,alive;float x,y;unsigned season64;uint64_t respawn64;char name[64];}NpcMonster55;
typedef struct{NpcMonster55*rows;unsigned count,capacity,map;uint32_t serial;}NpcMonsters55;
static int npc_monster_kind55(uint32_t source){for(unsigned i=0;i<MOB_SPEC_COUNT;i++)if((uint32_t)mobSpecs[i].id==source)return(int)i;return-1;}
static void npc_monster_recycle55(NpcMonsters55*s,Combat*g){unsigned kept=0;for(unsigned i=0;i<s->count;i++){NpcMonster55*r=s->rows+i;int current=r->map==g->mapId&&r->slot>=0&&g->mobs[r->slot].npcSpawn55==i+1;if(!r->alive&&!(r->season64&&r->map==g->mapId)&&(!current||!g->mobs[r->slot].enabled||g->time>g->mobs[r->slot].deadAt+2))continue;if(kept!=i){s->rows[kept]=*r;if(current)g->mobs[r->slot].npcSpawn55=kept+1;}kept++;}s->count=kept;}
static int npc_monster_reserve55(NpcMonsters55*s,unsigned extra){if(extra>NPC_MONSTERS_LIMIT55-s->count)return 0;unsigned need=s->count+extra;if(need<=s->capacity)return 1;unsigned capacity=s->capacity?s->capacity:32;while(capacity<need)capacity*=2;if(capacity>NPC_MONSTERS_LIMIT55)capacity=NPC_MONSTERS_LIMIT55;void*p=realloc(s->rows,capacity*sizeof(*s->rows));if(!p)return 0;s->rows=p;s->capacity=capacity;return 1;}
static int npc_monster_slot55(const Combat*g){for(unsigned i=0;i<MOB_COUNT-1;i++)if(!g->mobs[i].enabled)return(int)i;return-1;}
static int npc_monster_place55(Combat*g,float*x,float*y){
 if(*x>=8&&*y>=8&&*x<mapWidth43[g->mapId]-8&&*y<mapHeight43[g->mapId]-8&&(!g->canMove||g->canMove(g->world,*x,*y,*x,*y)))return 1;
 float cx=*x,cy=*y;for(unsigned attempt=0;attempt<512;attempt++){float px,py;if(cx>0&&cy>0){int r=1+(int)(attempt/32);px=cx+((int)(combat_random(g)%(2*r+1))-r)*8;py=cy+((int)(combat_random(g)%(2*r+1))-r)*8;}else{px=(1+combat_random(g)%(mapWidth43[g->mapId]/8-2))*8+4;py=(1+combat_random(g)%(mapHeight43[g->mapId]/8-2))*8+4;}if(px>=8&&py>=8&&px<mapWidth43[g->mapId]-8&&py<mapHeight43[g->mapId]-8&&(!g->canMove||g->canMove(g->world,px,py,px,py))){*x=px;*y=py;return 1;}}return 0;
}
static int npc_monster_attach55(NpcMonsters55*s,unsigned index,Combat*g){NpcMonster55*r=s->rows+index;if(!r->alive||r->map!=g->mapId)return 1;int slot=npc_monster_slot55(g);if(slot<0)return 0;float x=r->x,y=r->y;if(!npc_monster_place55(g,&x,&y))return 0;
 CombatMob*m=g->mobs+slot;memset(m,0,sizeof(*m));m->npcSpawn55=index+1;m->enabled=1;m->spawnDef=-2;m->kind=r->kind;m->hp=r->hp>mobSpecs[r->kind].hp?mobSpecs[r->kind].hp:r->hp;r->hp=m->hp;m->faceY=1;m->x=m->homeX=x;m->y=m->homeY=y;m->attackAt=m->hurtAt=m->deadAt=-100;m->wanderAt=g->time+1;m->life=r->serial;r->slot=slot;r->x=x;r->y=y;g->peaceful=0;g->creatureAssetsChanged52=1;return 1;
}
static int npc_monsters_map55(NpcMonsters55*s,Combat*g){if(s->map==g->mapId){for(unsigned i=0;i<s->count;i++){NpcMonster55*r=s->rows+i;if(r->alive&&r->map==s->map&&r->slot>=0){CombatMob*m=g->mobs+r->slot;if(m->npcSpawn55==i+1){r->hp=m->hp;r->x=m->x;r->y=m->y;}}}return 1;}s->map=g->mapId;for(unsigned i=0;i<s->count;i++)s->rows[i].slot=-1;for(unsigned i=0;i<s->count;i++)if(!npc_monster_attach55(s,i,g))return 0;return 1;}
static void npc_monsters_clear55(NpcMonsters55*s){free(s->rows);memset(s,0,sizeof(*s));s->map=UINT32_MAX;}
#endif
