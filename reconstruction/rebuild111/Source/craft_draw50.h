/* MIT. Shared recipe browser, six visible results and exact selected materials. */
static void ui_craft50(const Combat*g,int choice){
 int n=class_craft_rows50(g),first=choice/6*6;ui_panel(100,70,440,338,g->utilityMenu==239?"Pharmacy":"Smithing",1,-1);
 for(int k=first;k<n&&k<first+6;k++){const Recipe50*r=class_recipe50(g,k);int yy=96+(k-first)*23;ui_cell(108,yy-1,424,23,k==choice);skin_icon(itemIcons[r->product],113,yy,20,20);ui_fit47(140,yy,318,.9f,itemDefs[r->product].name);ui_scaled(465,yy,.8f,"x%d",inventory_count(g,r->product));}
 const Recipe50*r=class_recipe50(g,choice);if(r){ui_scaled(112,240,.8f,"Ingredients (guide books are kept):");for(int i=0;i<r->count;i++){int item=r->materials[i][0],amount=r->materials[i][1],x=112+(i%2)*208,y=258+(i/2)*19;char line[100];snprintf(line,sizeof(line),amount?"%s %d/%d":"%s %d (guide)",itemDefs[item].name,inventory_count(g,item),amount);ui_fit47(x,y,202,.8f,line);}}
 ui_hint64(112,323,.8f,"A: attempt once   B: close   %d/%d",n?choice+1:0,n);ui_scaled(112,342,.75f,g->utilityMenu==239?"Each attempt uses 5 SP and a Medicine Bowl.":"Each attempt uses the selected hammer or furnace.");ui_fit47(112,374,415,.8f,g->log);
}
