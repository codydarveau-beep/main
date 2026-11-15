/* GPL-3.0-or-later. Original pre-renewal Ninja actions and field ownership. */
static int ninja_field60(unsigned id){return id==SK60_NJ_KAENSIN||id==SK60_NJ_SUITON||id==SK60_NJ_TATAMIGAESHI;}
static int ninja_field_slot60(const Combat*g,unsigned id){for(int i=0;i<CLASS_AREAS50;i++)if(g->areas50[i].id==(int)id&&g->areas50[i].map==g->mapId&&g->areas50[i].until>g->time)return i;return class_area_slot50(g);}
static int ninja_ready60(Combat*g,unsigned id,int rank,int target,float x,float y){
 if((id==SK60_NJ_BUNSINJYUTSU||id==SK60_NJ_ISSEN)&&(!class_active50(g,SK60_NJ_NEN)||(id==SK60_NJ_ISSEN&&g->hp<2))){combat_notice(g,POP_SKILLS,"Requires Soul first; resources kept.");return 0;}
 if(ninja_field60(id)&&ninja_field_slot60(g,id)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire; resources kept.");return 0;}
 if(id==SK60_NJ_SHADOWJUMP&&g->canMove&&!g->canMove(g->world,x,y,x,y))return 0;
 const ClassSkill50*d=class_skill_data50(id);if(d->target==2&&(target<0||target>=MOB_COUNT||!g->mobs[target].enabled||g->mobs[target].hp<=0))return 0;
 int hits=d->hits[rank-1];if(hits<0)hits=-hits;if(hits>1){int need=1,free=0;for(int i=0;i<SKILL_BURSTS49;i++)free+=!g->bursts49[i].active;
  if(id==SK60_NJ_HUUMA||id==SK60_NJ_BAKUENRYU){float tx=target>=0?g->mobs[target].x:x,ty=target>=0?g->mobs[target].y:y;need=0;for(int i=0;i<MOB_COUNT;i++)need+=class_in_area50(g,&g->mobs[i],tx,ty,d->splash[rank-1]*8+4);}
  if(free<need){combat_notice(g,POP_SKILLS,"Wait for active skill hits; resources kept.");return 0;}
 }return 1;
}
static int ninja_step60(Combat*g,float x,float y){if(class_ice_block48(g,x,y)||(g->canMove&&!g->canMove(g->world,x,y,x,y)))return 0;g->x=x;g->y=y;g->moving=0;g->route53.state=0;return 1;}
static void ninja_near_target60(Combat*g,const CombatMob*m){for(int n=0;n<8;n++){float x=m->x+(int[]){-8,0,8,-8,8,-8,0,8}[n],y=m->y+(int[]){-8,-8,-8,0,0,8,8,8}[n];if(ninja_step60(g,x,y))return;}}
static void ninja_magic60(Combat*g,int target,unsigned id,int rank,int element,int ratio,int hits){CombatMob*m=&g->mobs[target];if(id==SK60_NJ_HYOUSYOURAKU&&m->frozenLeft>0)return;int damage=combat_magic_power48(g)*ratio/100;if(damage<1)damage=1;damage=class_multi_element48(g,m,element,damage,hits);if(damage<=0&&class_attack_rate48(g,m,element)>0)damage=hits;skill_magic_hit_ex48(g,target,damage,0,hits);
 if(id==SK60_NJ_HYOUSYOURAKU)skill_freeze164(g,m,10+10*rank,(int)(class_duration50(id,rank,1)*1000));
}
static void ninja_execute60(Combat*g,unsigned id,int rank,int target,float x,float y){
 const ClassSkill50*d=class_skill_data50(id);
 if(id==SK60_NJ_NEN||id==SK60_NJ_UTSUSEMI||id==SK60_NJ_BUNSINJYUTSU){class_buff50(g,id,rank);if(id!=SK60_NJ_NEN)g->class50.next[id-127]=(rank+1)/2;if(id==SK60_NJ_BUNSINJYUTSU)g->class50.until[SK60_NJ_NEN-127]=0;return;}
 if(id==SK60_NJ_SHADOWJUMP){ninja_step60(g,x,y);g->hideLeft=0;return;}
 if(ninja_field60(id)){int slot=ninja_field_slot60(g,id);ClassArea50*a=&g->areas50[slot];*a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=id==SK60_NJ_SUITON?x:g->x,.y=id==SK60_NJ_SUITON?y:g->y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time};memset(g->class50.ninjaCells60[slot],0,25);if(id==SK60_NJ_TATAMIGAESHI)class_buff50(g,id,rank);return;}
 if(id==SK60_NJ_HYOUSYOURAKU||id==SK60_NJ_RAIGEKISAI){for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],g->x,g->y,d->splash[rank-1]*8+4))ninja_magic60(g,i,id,rank,id==SK60_NJ_HYOUSYOURAKU?1:4,id==SK60_NJ_HYOUSYOURAKU?100+50*rank:160+40*rank,1);return;}
 if(target<0||target>=MOB_COUNT)return;CombatMob*m=&g->mobs[target];int hits=d->hits[rank-1];if(hits<0)hits=-hits;if(hits<1)hits=1;
 if(id==SK60_NJ_KOUENKA||id==SK60_NJ_HYOUSENSOU||id==SK60_NJ_HUUJIN){ninja_magic60(g,target,id,rank,id==SK60_NJ_KOUENKA?3:id==SK60_NJ_HYOUSENSOU?1:4,id==SK60_NJ_KOUENKA?90:100,hits);return;}
 if(id==SK60_NJ_BAKUENRYU||id==SK60_NJ_HUUMA){float tx=m->x,ty=m->y;int count=0;for(int i=0;i<MOB_COUNT;i++)count+=class_in_area50(g,&g->mobs[i],tx,ty,d->splash[rank-1]*8+4);if(!count)return;
  for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],tx,ty,d->splash[rank-1]*8+4)){if(id==SK60_NJ_BAKUENRYU)ninja_magic60(g,i,id,rank,3,100+50*(rank-1),hits);else skill_hit_ex(g,i,class_physical50(g,&g->mobs[i],150+150*rank,0,-1)/count,0,hits);}return;}
 if(id==SK60_NJ_KAMAITACHI){float dx=m->x-g->x,dy=m->y-g->y,dist=sqrtf(dx*dx+dy*dy);if(dist<.01f)return;dx/=dist;dy/=dist;float length=class_range50(g,id,rank);for(int i=0;i<MOB_COUNT;i++){CombatMob*t=&g->mobs[i];float px=t->x-g->x,py=t->y-g->y,along=px*dx+py*dy,across=fabsf(px*dy-py*dx);if(along>=0&&along<=length&&across<=12&&class_in_area50(g,t,g->x,g->y,length))ninja_magic60(g,i,id,rank,4,100+100*rank,1);}return;}
 if(id==SK60_NJ_ZENYNAGE){unsigned cost=expanded_requirement60(id)->zeny[rank-1];int damage=cost+combat_random(g)%(cost?cost:1);if(combat_status_boss(m))damage/=3;skill_hit(g,target,damage,0);return;}
 if(id==SK60_NJ_ISSEN){int damage=(40*stat_value(g,0)+rank*(g->hp/10+35))*class_attack_rate48(g,m,class_weapon_element50(g))/100;skill_hit(g,target,damage,0);g->hp=1;g->class50.until[SK60_NJ_NEN-127]=0;g->hideLeft=0;return;}
 if(id==SK60_NJ_KIRIKAGE){ninja_near_target60(g,m);g->hideLeft=0;int critical=class_chance50(g,combat_target_crit(g,m)+250+50*rank,1000),power=class_weapon_power50(g,m,critical)*rank;if(critical)power=power*(140+g->itemBonuses52.scalar[B52_bCritAtkRate])/100;power=item_physical_bonus52(g,m,power*class_attack_rate48(g,m,class_weapon_element50(g))/100,id);skill_hit(g,target,item_normal_def52(g,m,power,critical),0);return;}
 int extra=id==SK60_NJ_SYURIKEN?g->lastAmmoAttack60+4*rank:id==SK60_NJ_KUNAI?g->lastAmmoAttack60:0;
 int damage=class_physical_add60(g,m,id==SK60_NJ_KASUMIKIRI?100+10*rank:100,0,-1,extra);
 if(id==SK60_NJ_SYURIKEN)damage+=(3*class_rank50(g,SK60_NJ_TOBIDOUGU))*class_attack_rate48(g,m,class_weapon_element50(g))/100;
 if(id==SK60_NJ_KUNAI)damage+=60*class_attack_rate48(g,m,class_weapon_element50(g))/100;
 skill_hit_ex(g,target,damage*(id==SK60_NJ_KUNAI?3:1),0,hits);
 if(id==SK60_NJ_KASUMIKIRI){g->hideLeft=class_duration50(id,rank,0);g->hideRank=rank;g->hideDrain=0;g->autoAttack=0;g->target=-1;}
}
static int ninja_received60(Combat*g,int mob,int damage,int ranged){
 if(damage<=0)return damage;if(ranged&&class_active50(g,SK60_NJ_TATAMIGAESHI))return 0;
 int cicada=class_active50(g,SK60_NJ_UTSUSEMI),mirror=class_active50(g,SK60_NJ_BUNSINJYUTSU);if(!cicada&&!mirror)return damage;
 if(cicada){if(--g->class50.next[SK60_NJ_UTSUSEMI-127]<=0)g->class50.until[SK60_NJ_UTSUSEMI-127]=0;
  if(mob>=0&&mob<MOB_COUNT){CombatMob*m=&g->mobs[mob];float dx=g->x-m->x,dy=g->y-m->y,dist=sqrtf(dx*dx+dy*dy);if(dist>.01f)for(int i=0;i<7;i++)if(!combat_move(g,&g->x,&g->y,g->x+dx/dist*8,g->y+dy/dist*8))break;}
 }
 if(mirror&&--g->class50.next[SK60_NJ_BUNSINJYUTSU-127]<=0)g->class50.until[SK60_NJ_BUNSINJYUTSU-127]=0;
 combat_guard_number53(g);return 0;
}
static void ninja_tick60(Combat*g){
 for(int k=0;k<CLASS_AREAS50;k++){ClassArea50*a=&g->areas50[k];if(!ninja_field60(a->id))continue;if(a->map!=g->mapId){a->until=0;continue;}if(a->until<=g->time||a->next>g->time)continue;
  int old=g->fxSkill;g->fxSkill=a->id;for(unsigned pulse=0;pulse<8&&a->next<=g->time&&a->next<a->until;pulse++){a->next+=a->id==SK60_NJ_KAENSIN?.02f:a->id==SK60_NJ_TATAMIGAESHI?2.f:.1f;
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];int dx=(int)floorf(m->x/8)-(int)floorf(a->x/8),dy=(int)floorf(m->y/8)-(int)floorf(a->y/8);
   int radius=a->id==SK60_NJ_SUITON?(a->rank-1)/3+1:a->id==SK60_NJ_TATAMIGAESHI?(a->rank+2)/2:2;if(abs(dx)>radius||abs(dy)>radius||!class_in_area50(g,m,a->x,a->y,radius*8+4))continue;
   if(a->id==SK60_NJ_SUITON){if(!combat_status_boss(m)){m->class50.suitonUntil60=g->time+.2f;m->class50.suitonRank60=a->rank;}continue;}
   if(a->id==SK60_NJ_TATAMIGAESHI){if((dx&&dy)||(!dx&&!dy))continue;skill_hit(g,i,class_physical50(g,m,100+10*a->rank,0,-1),0);if(m->hp>0)combat_knockback(g,i,m->x-a->x,m->y-a->y,24);continue;}
   if(!dx&&!dy)continue;int cell=(dy+2)*5+dx+2;if(g->class50.ninjaCells60[k][cell]>=(a->rank+1)/2+4)continue;g->class50.ninjaCells60[k][cell]++;ninja_magic60(g,i,a->id,a->rank,3,50,1);
  }}g->fxSkill=old;
 }
}
