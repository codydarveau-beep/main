/* MIT. Personal Sniper buffs and source single/line attacks. */
static void class_sniper_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_SN_SIGHT||id==SK52_SN_WINDWALK){class_buff50(g,id,rank);stat_refresh(g);return;}
 CombatMob*m=&g->mobs[target];if(id==SK52_SN_FALCONASSAULT){int power=2*(stat_value(g,4)/10+stat_value(g,3)/2+3*class_rank50(g,166)+40);skill_hit(g,target,power*5*(150+70*rank)/100,0);return;}
 float dx=m->x-g->x,dy=m->y-g->y,length=sqrtf(dx*dx+dy*dy);if(length<.01f)return;dx/=length;dy/=length;float reach=class_range50(g,id,rank);
 for(int i=0;i<MOB_COUNT;i++){CombatMob*t=&g->mobs[i];if(!t->enabled||t->hp<=0)continue;float x=t->x-g->x,y=t->y-g->y,along=x*dx+y*dy,across=fabsf(x*dy-y*dx);if(along<0||along>reach+4||across>12||!class_reachable50(g,g->x,g->y,t->x,t->y))continue;int critical=class_chance50(g,combat_target_crit(g,t)+200,1000);int damage=class_weapon_power50(g,t,critical)*(200+50*rank)/100;damage=damage*class_attack_rate48(g,t,class_weapon_element50(g))/100;if(!critical)damage=combat_reduce48(damage,combat_enemy_defense(t),mobStunVit[t->kind]);skill_hit(g,i,damage,0);}
}
