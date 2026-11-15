/* Native lane motion plus original script-owned checkpoints and rewards. */
static int npc_game_racer_command164(NpcGame55*g,NpcRuntime55*r,NpcMachine55*m,const char*name,const NpcValue55*args,unsigned count,NpcValue55*out){
 if(!strcmp(name,"getmapxy")){int64_t type;if(count<4||!npc_vm_integer55(m,args[3],&type))return N55_ERROR;if(type!=1)return-1;if(count>5||!m->api.write)return N55_ERROR;unsigned npc=r->npc-1;if(count==5){NpcValue55 value;if(!npc_vm_value55(m,args[4],&value)||value.kind!=N55_STRING_KIND)return N55_ERROR;int found=npc_record_name55(value.text);if(found<0){*out=npc_vm_number55(-1);return N55_READY;}npc=(unsigned)found;}if(npc>=NPC_RECORD_COUNT55||npcRecords55[npc].map>=MYRO_MAP_COUNT43)return N55_ERROR;NpcValue55 values[3]={npc_vm_string55(mapNames[npcRecords55[npc].map]),npc_vm_number55((int)(npc_scene_x64(&g->scene,npc)/8)),npc_vm_number55((int)(npc_scene_y64(&g->scene,npc)/8))};for(unsigned i=0;i<3;i++)if(args[i].kind!=N55_REFERENCE_KIND||!m->api.write(m->api.context,args+i,values+i))return N55_ERROR;*out=npc_vm_number55(0);return N55_READY;}
 if(strcmp(name,"sc_start"))return-1;int slot=(int)(r-g->vm);unsigned actor=g->raceActor164[slot];if(!actor)return-1;*out=npc_vm_number55(0);if(actor>MOB_COUNT)return N55_ERROR;Combat*game=g->player.game;CombatMob*mob=game->mobs+actor-1;if(!mob->enabled||!combat_racer_kind164(mob->kind)||mob->life!=g->raceLife164[slot]||npcRecords55[r->npc-1].map!=game->mapId)return N55_READY;
 int64_t status,ms,value;if(count!=3||!npc_vm_integer55(m,args[0],&status)||!npc_vm_integer55(m,args[1],&ms)||!npc_vm_integer55(m,args[2],&value)||ms<0||ms>600000)return N55_ERROR;
 if(status==278){if(value<1||value>10000)return N55_ERROR;mob->raceSpeed164=8000.f/value;mob->raceSpeedUntil164=game->time+ms/1000.f;}
 else if(status==2)mob->stun=ms/1000.f;else if(status==3)mob->class50.sleepUntil=game->time+ms/1000.f;else return N55_ERROR;return N55_READY;
}
static void npc_game_racer_step164(void*context,Combat*game,CombatMob*mob,float dt){
 NpcGame55*g=context;if(game->mapId>=MYRO_MAP_COUNT43)return;float speed=mob->raceSpeedUntil164>game->time?mob->raceSpeed164:mobSpecs[mob->kind].speed;mob->faceX=-1;mob->faceY=0;mob->moving=combat_mob_move52(game,mob,mob->x-speed*dt,mob->homeY);
 unsigned start=npcMapSpans55[game->mapId].start,count=npcMapSpans55[game->mapId].count,touched=0;
 for(unsigned j=0;j<count;j++){unsigned npc=npcMapRecords55[start+j];const NpcRecord55*n=npcRecords55+npc;if(!n->program||(n->flags&2)||(g->scene.flags[npc]&(N55_NPC_DISABLED|N55_NPC_HIDDEN))||fabsf(mob->x-npc_scene_x64(&g->scene,npc))>n->rx+4||fabsf(mob->y-npc_scene_y64(&g->scene,npc))>n->ry+4)continue;
  const NpcProgram55*program=npc_program_cached55(&g->programs,NULL,n->program);unsigned entry;if(!program||!npc_vm_entry55(program,program->labels,program->labelCount,"OnTouchNPC",&entry))continue;touched=npc+1;if(mob->raceTouch164!=touched){unsigned actor=(unsigned)(mob-game->mobs)+1;if(!npc_game_schedule55(g,npc,entry,0,N55_EVENT_RACER164|(actor<<16)))combat_message(game,"Race checkpoint queue is full.");}break;
 }
 mob->raceTouch164=touched;
}
