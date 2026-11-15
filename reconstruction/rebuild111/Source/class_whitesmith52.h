/* MIT. Source solo Whitesmith buffs and cart-weight damage. */
static void class_whitesmith_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_WS_MELTDOWN||id==SK52_WS_CARTBOOST||id==SK52_WS_OVERTHRUSTMAX){class_buff50(g,id,rank);if(id==SK52_WS_OVERTHRUSTMAX)g->class50.until[233-127]=0;return;}
 if(id==SK52_WS_CARTTERMINATION){CombatMob*m=&g->mobs[target];int divisor=10*(16-rank),ratio=(int)(inventory_cart_weight(g)/divisor);skill_hit(g,target,class_physical50(g,m,ratio,0,-1),0);if(m->hp>0)class_stun50(g,m,5*rank,5);return;}
}
