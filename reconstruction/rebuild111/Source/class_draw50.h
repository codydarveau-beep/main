/* GPL-3.0-or-later. Source SpiritSphere orbit and original directional projectiles.
 * Source cell size8; rotation tick/64 degrees, five equally spaced positions.
 */
static void class_persistent_draw50(const Combat*g,const float*m,float zoom){
 /* Source repeating ground effects use their combat-owned lifetimes. */
 for(int k=0;k<CLASS_AREAS50;k++){const ClassArea50*a=&g->areas50[k];if(a->until<=g->time||a->map!=g->mapId)continue;float age=g->time-a->created;
  if(a->id==SK60_NJ_KAENSIN){for(int dy=-2;dy<=2;dy++)for(int dx=-2;dx<=2;dx++)if((dx||dy)&&g->class50.ninjaCells60[k][(dy+2)*5+dx+2]<(a->rank+1)/2+4)art39_world(FX62_FIRE_FORMATION,age,m,a->x+dx*8,a->y+dy*8,zoom,1);}
  else if(a->id==SK60_GS_GROUNDDRIFT){int c=a->power==4?FX62_MINE_WIND:a->power==7?FX62_MINE_DARK:a->power==5?FX62_MINE_POISON:a->power==1?FX62_MINE_ICE:FX62_MINE_FIRE;art39_world(c,age,m,a->x,a->y,zoom,1);}
 }
 if(combat_casting(g)&&g->spellCastId==SK60_GS_TRACKING)art39_world(FX62_TRACK_CAST,g->spellCastTotal-g->spellCastLeft,m,g->x,g->y,zoom,1);
 if(combat_casting(g)&&g->spellCastId==SK60_GS_INCREASING){float age=g->spellCastTotal-g->spellCastLeft;art39_world(FX62_INCREASING_BOTTOM,age,m,g->x,g->y,zoom,1);art39_world(FX62_INCREASING_CAST,age,m,g->x,g->y,zoom,1);}
 for(unsigned i=0;i<MOB_COUNT;i++){const CombatMob*q=g->mobs+i;int card=q->class50.tarotVisual52;float age=g->time-q->class50.tarotVisualAt52;if(q->enabled&&card>=1&&card<=14&&age>=0&&age<3)art39_world(FX52_TAROT_BASE+card-1,age,m,q->class50.tarotVisualSelf52?g->x:q->x,q->class50.tarotVisualSelf52?g->y:q->y,zoom,0);}

 for(int i=g->class50.spheres;i>0;i--){float a=(i%5)*1.25663706f-g->time*.2727077f;
  art39_world_z45(FX50_SPIRIT_SPHERE,g->time,m,g->x+8*cosf(a),g->y+8*sinf(a),zoom*.1875f,1,16);
 }
}
static int class_event_draw50(const Art39Event*e,const Combat*g,const float*m,float zoom,float age){
 if(e->skill==SK60_NJ_SYURIKEN||e->skill==SK60_NJ_KUNAI||e->skill==SK60_NJ_HUUMA||e->skill==SK60_NJ_ZENYNAGE||e->skill==SK60_GS_FLING){classic_flight49(e->clip,e,g,m,zoom,age,.2f,0);return 1;}
 if(e->skill==SK60_NJ_KAENSIN||e->skill==SK60_GS_GROUNDDRIFT)return 1;
 if(e->skill==SK60_TK_COUNTER){art39_world(FX62_COUNTER_BOTTOM,age,m,g->x,g->y,zoom,0);art39_world(FX62_COUNTER,age,m,g->x,g->y,zoom,0);return 1;}
 if(e->skill==206){int count=e->bolts>0?e->bolts:1;for(int n=0;n<count;n++)classic_flight49(FX50_FINGER_SPHERE,e,g,m,zoom*.6f,age-n*.2f,.15f,0);return 1;}
 if(e->skill==173||e->skill==180){if(age>=.15f)return 1;float t=age/.15f,x=e->startX+(e->x-e->startX)*t,y=e->startY+(e->y-e->startY)*t,sx,sy,z=height_at(x,y)+12;world_project(m,x,y,z,&sx,&sy);float dx=e->x-e->startX,dy=e->y-e->startY,a=atan2f(-(m[0]*dx+m[1]*dy),m[1]*dx-m[0]*dy);int dir=((int)floorf(a/.7853981634f+.5f)+16)%8;art39_one(FX50_ARROW_PROJECTILE,age,sx,sy,m[8]*x+m[9]*y+m[10]*z+m[11]-WORLD_SPRITE_BIAS*2,zoom/(3*.5f),1,0,dir);return 1;}
 return 0;
}
