/* MIT. Atomic original recipes; reusable guide books require possession only. */
static int class_recipe_enabled50(const Combat*g,const Recipe50*r){
 if(g->utilityMenu==239)return job_parent52(g->jobId)==20&&r->skill==239&&class_rank50(g,239)>=r->rank;
 if(g->utilityMenu!=600||job_parent52(g->jobId)!=19||r->skill==239||class_rank50(g,r->skill)<r->rank)return 0;
 return g->class50.craftTool==612?r->level==21:r->level==g->class50.craftTool-612;
}
static const Recipe50*class_recipe50(const Combat*g,int choice){for(unsigned i=0;i<sizeof(recipes50)/sizeof(*recipes50);i++)if(class_recipe_enabled50(g,&recipes50[i])&&choice--==0)return &recipes50[i];return NULL;}
static int class_craft_rows50(const Combat*g){int n=0;while(class_recipe50(g,n))n++;return n;}
static int class_craft_rate50(Combat*g,const Recipe50*r){
 int rank=class_rank50(g,r->skill),id=itemDefs[r->product].id;
 int chance=20*g->joblevel+10*stat_value(g,4)+10*stat_value(g,5);
 if(r->skill==239){if(g->persistent50.homunType&&!g->persistent50.homunResting&&g->persistent50.homunHP)chance+=100*g->persistent50.homunSkills[14];chance+=50*class_rank50(g,238)+300*rank+10*(stat_value(g,3)/2);
  if(id==501||id==503||id==504)chance+=2000+10*(1+combat_random(g)%100);
  else if(id==970)chance+=1000+10*(1+combat_random(g)%100);
  else if(id>=7135&&id<=7138)chance+=10*(1+combat_random(g)%100);
  else if(id==546)chance-=10*(1+combat_random(g)%50);
  else if(id==547||id==7139)chance-=10*(1+combat_random(g)%100);
 }else if(r->level==21){chance+=(id==998?4000:id==999?3000:1000)+500*rank;if(id==1000)chance=100000;
 }else{int lv=itemDefs[r->product].weaponLv;chance+=5000+500*rank+100*class_rank50(g,227)+(lv>=3?100*class_rank50(g,217):0)-(lv>1?1000*lv:0);
  static const int anvils[]={986,987,988,989},bonus[]={0,300,500,1000};for(int i=3;i>=0;i--)if(inventory_count(g,item_source50(anvils[i]))){chance+=bonus[i];break;}
 }
 return chance<1?1:chance;
}
static int class_craft_commit50(Combat*g,int choice){
 const Recipe50*r=class_recipe50(g,choice);if(!r)return 0;
 int pharmacy=r->skill==239,tool=item_source50(g->class50.craftTool),bowl=item_source50(7134);
 if(g->castDelay>0||g->sp<(pharmacy?5:0)||(!pharmacy&&(tool<0||!inventory_count(g,tool)))||(pharmacy&&!inventory_count(g,bowl))){combat_message(g,"Need the production tool and SP; resources kept.");return 0;}
 int64_t weight=inventory_weight(g);for(int i=0;i<r->count;i++){int item=r->materials[i][0],amount=r->materials[i][1];if(inventory_count(g,item)<(amount?amount:1)){combat_message(g,"Need %d %s; resources kept.",amount?amount:1,itemDefs[item].name);return 0;}weight-=(int64_t)itemWeights[item]*amount;}
 weight-=itemWeights[pharmacy?bowl:tool];weight+=itemWeights[r->product];
 if(inventory_count(g,r->product)>=ITEM_STACK_MAX||weight>inventory_weight_max(g)){combat_message(g,"Make room for the result; resources kept.");return 0;}
 int chance=class_craft_rate50(g,r);for(int i=0;i<r->count;i++)*inventory_stack(g,r->materials[i][0])-=r->materials[i][1];
 --*inventory_stack(g,pharmacy?bowl:tool);g->sp-=pharmacy?5:0;g->castDelay=.35f;g->lastCast=g->fxAt=g->time;g->fxSkill=pharmacy?239:600;
 int success=class_chance50(g,chance,10000);if(success)++*inventory_stack(g,r->product);
 combat_notice(g,POP_ITEMS,success?"Created %s.":"Failed to create %s; materials consumed.",itemDefs[r->product].name);return 1;
}
