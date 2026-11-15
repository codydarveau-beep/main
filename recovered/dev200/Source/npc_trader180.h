/* MIT. Source sellitem stock is collected by original OnInit, not invented. */
#ifndef MYRO_NPC_TRADER180_H
#define MYRO_NPC_TRADER180_H
static int npc_trader_open180(NpcGame55*g,CoreNpcUI53*u,unsigned record){
 if(record>=NPC_RECORD_COUNT55||npcRecords55[record].kind!=2||!npcRecords55[record].program||(npcRecords55[record].flags&2)||!(g->scene.flags[record]&N55_NPC_INIT_DONE))return 0;
 unsigned owner=npcProgramFiles55[npcRecords55[record].program-1].owner;unsigned rows=0;for(unsigned i=0;i<g->shops.count;i++)if(g->shops.rows[i].owner==owner)rows++;if(!rows)return 0;
 unsigned(*stock)[2]=malloc(rows*sizeof(*stock));if(!stock)return 0;unsigned at=0;for(unsigned i=0;i<g->shops.count;i++){const NpcShopRow55*p=g->shops.rows+i;if(p->owner==owner){stock[at][0]=p->item;stock[at++][1]=p->price;}}
 core_trader_clear180();coreTraderStock180=stock;coreTraderRows180=rows;const NpcRecord55*n=npcRecords55+record;coreTrader180=(CoreNpc53){.map=n->map,.x=(unsigned)npc_scene_x64(&g->scene,record),.y=(unsigned)npc_scene_y64(&g->scene,record),.kind=2,.start=sizeof(coreStock53)/sizeof(*coreStock53),.count=rows,.name=npc_scene_name55(&g->scene,record)};core_npc_open53(u,g->player.game,CORE_NPC_COUNT53);return 1;
}
#endif
