/* MIT. Personal companion controls use the existing window skin and atlas. */
static void ui_companion50(const Combat*g,int choice){
 if(g->utilityMenu==501){ui_panel(100,92,440,160,"Falcon",1,-1);for(int i=0;i<2;i++){int y=127+i*26;ui_cell(110,y-1,420,25,i==choice);ui_text(120,y,i?"Dismiss Falcon":"Hire Falcon - 2500 Zeny");}ui_hint64(112,210,.8f,"A: choose  B: close   %s",g->persistent50.falcon?"Falcon hired":"No Falcon hired");return;}
 const ClassPersistent50*p=&g->persistent50;int family=homun_family50(g);ui_panel(100,70,440,338,"Homunculus",1,-1);
 if(family<0){ui_text(112,99,"Use Call Homunculus with an Embryo first.");ui_scaled(112,126,.8f,"Feed, evolution and its skill tree appear here.");return;}
 ui_text(112,94,"%s  Lv%u | HP %u/%u | SP %u/%u",homunData50[p->homunType-6001].name,p->homunLevel,p->homunHP,homun_maxhp50(p),p->homunSP,homun_maxsp50(p));ui_scaled(112,114,.85f,"Hunger %u | Intimacy %u/1000 | Skill points %u",p->homunHunger,p->homunIntimacy/100,p->homunPoints);
 const char*commands[]={"Feed","Follow / attack selected target","Evolve (Stone of Sage; 910 intimacy)","Strike nearby Marine Sphere (5s countdown)"};
 for(int i=0;i<4;i++){int yy=141+i*21;ui_cell(110,yy-1,420,21,choice==i);char line[100];if(!i)snprintf(line,sizeof(line),"Feed: %s",itemDefs[item_source50(homunData50[p->homunType-6001].food)].name);else if(i==1)snprintf(line,sizeof(line),"%s",g->class50.homunHold?"Attack selected target":"Follow only");else snprintf(line,sizeof(line),"%s",commands[i]);ui_fit47(120,yy,404,.85f,line);}
 for(int i=0;i<4;i++){int skill=family*4+i,yy=231+i*25;const unsigned*t=homun_tree50(g,skill);ui_cell(110,yy-1,420,25,choice==i+4);skin_icon(homunSkillIcons50[skill],114,yy,21,21);ui_fit47(143,yy,274,.9f,homunSkill50[skill].name);ui_scaled(435,yy,.85f,"%u/%u",p->homunSkills[skill],t?t[2]:3);}
 ui_hint64(112,344,.8f,"A: use / action   X: learn skill   B: close");ui_fit47(112,374,415,.8f,g->log);
}
