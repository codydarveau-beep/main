/* MIT. Source solo smith buffs, stuns, repair and ore discovery. */
static int class_repair_material50(const Combat*g){const OwnedItem52*p=inventory_broken52(g);if(!p)return -1;const EquipmentRule52*e=equipment_rule52(p->sourceID);if(!e)return -1;int lv=e->weaponLevel;return item_source50(e->weapon==0?999:lv==1?1002:lv==2?998:lv==3?999:984);}
static void class_blacksmith_execute50(Combat*g,unsigned id,int rank,float x,float y){
 if(id==228){const OwnedItem52*p=inventory_broken52(g);int material=class_repair_material50(g);if(!p||material<0||!inventory_count(g,material))return;uint32_t uid=p->uid;--*inventory_stack(g,material);inventory_repair52(g,uid);combat_notice(g,POP_ITEMS,"Weapon repaired.");return;}
 if(id==230){for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],x,y,20))class_stun50(g,&g->mobs[i],20+10*rank,class_duration50(id,rank,1));return;}
 if(id>=231&&id<=233){class_buff50(g,id,rank);if(class_rank50(g,225))g->class50.until[id-127]+=(g->class50.until[id-127]-g->time)/10;return;}
 if(id==234){if(class_active50(g,id))g->class50.until[id-127]=0;else{g->class50.level[id-127]=rank;g->class50.until[id-127]=g->time+86400;g->class50.next[id-127]=g->time+class_duration50(id,rank,0);}return;}
 if(id==236){unsigned picked=0;for(unsigned i=0;i<groundUsed58;i++)if(ground_live58(g,(int)i)&&combat_dist(g->x,g->y,groundItems58[i].x,groundItems58[i].y)<=12){unsigned attempts=0;while(groundItems58[i].count&&attempts++<64&&ground_take58(g,(int)i))picked++;}if(!picked)combat_notice(g,POP_ITEMS,"No nearby ground items could be picked up.");}
}
static void class_ore_drop50(Combat*g){
 if(job_parent52(g->jobId)!=19||!class_rank50(g,226))return;
 /* Source chain chooses one uniformly, then tests that entry's rate. */
 static const unsigned short sources[20]={1002,998,993,1003,992,1010,991,990,999,1011,757,756,997,996,995,994,985,984,969,714};
 static const unsigned short rates[20]={600,380,100,80,100,600,100,100,50,380,70,80,40,40,40,40,20,20,10,5};
 int n=combat_random(g)%20;if(class_chance50(g,rates[n],10000)){int floor58;ground_loot58(g,sources[n],g->x,g->y,&floor58);}
}
