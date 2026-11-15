/* MIT. Original RO digits/messages and type colours. Fixed texture/bounded batch. */
#include "damage_art53.h"
static void*damageTexture53;
#ifdef DAMAGE_NATIVE53
static void damage_init53(void){unsigned char*p=inflateasset("original combat numbers",damageImage53,damageImageSize53,damageImageRaw53);damageTexture53=gpu_alloc(damageImageRaw53);memcpy(damageTexture53,p,damageImageRaw53);free(p);}
#endif
static void damage_glyph53(unsigned glyph,unsigned fade,float cx,float cy,float scale){const unsigned short*r=damageGlyphs53[glyph*DAMAGE_FADE_LEVELS53+fade];hud_quad(cx-r[2]*scale*.5f,cy-r[3]*scale*.5f,r[2]*scale,r[3]*scale,r[0],r[1],r[2],r[3]);}
static void damage_digits53(int value,float cx,float cy,unsigned style,float scale,unsigned fade){char digits[16];snprintf(digits,sizeof(digits),"%d",value);float width=0;for(unsigned i=0;digits[i];i++)width+=damageGlyphs53[(style*10+digits[i]-'0')*DAMAGE_FADE_LEVELS53][2]+2;width-=2;float x=cx-width*scale*.5f;for(unsigned i=0;digits[i];i++){unsigned glyph=style*10+digits[i]-'0';float w=damageGlyphs53[glyph*DAMAGE_FADE_LEVELS53][2];damage_glyph53(glyph,fade,x+w*scale*.5f,cy,scale);x+=(w+2)*scale;}}
static unsigned damage_fade53(float p){if(p<0)p=0;unsigned fade=(unsigned)(p*DAMAGE_FADE_LEVELS53);return fade>=DAMAGE_FADE_LEVELS53?DAMAGE_FADE_LEVELS53-1:fade;}
static void damage_spread180(const DamageEvent*d,float*x,float*y,float scale){if(!d->spread180||!d->owner180)return;unsigned seed=d->owner180*131+d->life180*7919;seed^=seed>>16;seed*=0x7feb352du;seed^=seed>>15;*x+=((seed&255)/255.f-.5f)*16*scale;*y+=(((seed>>8)&255)/255.f-.5f)*10*scale;}
static void damage_particle53(const DamageEvent*d,const float*m,int value,float age,int critical,unsigned style){float p=age/1.5f;if(p<0||p>1)return;float wx=d->x+32*p,wy=d->y-32*p,z=height_at(d->x,d->y)+16+40*sinf(4.71238898f*p);float x=m[0]*wx+m[1]*wy+m[2]*z+m[3],y=m[4]*wx+m[5]*wy+m[6]*z+m[7];float scale=fmaxf(.3f,1.3f*(1-p));unsigned fade=damage_fade53(p);damage_spread180(d,&x,&y,scale);if(critical){/* Same centre/clock/scale: numbers cannot drift away from their burst. */damage_glyph53(54,fade,x,y,.6f*scale);style=1;}damage_digits53(value,x,y,style,scale,fade);}
static void damage_draw(const Combat*g,const float*m){unsigned shown=0,n=g->damageNext<DAMAGE_EVENTS?g->damageNext:DAMAGE_EVENTS;hud_setup(damageTexture53,512,256,1024,0x00011d2a,1);
 for(unsigned k=0;k<n&&shown<8;k++){const DamageEvent*d=&g->damage[(g->damageNext-1-k)%DAMAGE_EVENTS];float age=g->time-d->at,last=(d->hits-1)*d->hitGap,life=d->kind==7?1.f:d->kind==1?3.f:1.5f;if(age<0||age>last+life||d->x<0||d->y<0||d->x>=gw*8||d->y>=gh*8)continue;float z=height_at(d->x,d->y),x=m[0]*d->x+m[1]*d->y+m[2]*z+m[3],y=m[4]*d->x+m[5]*d->y+m[6]*z+m[7];if(x< -100||x>740||y< -120||y>600)continue;shown++;
  if(d->kind==7){float p=age,yy=y-10-18*p;unsigned fade=damage_fade53(p);damage_glyph53(57,fade,x-15,yy,.3f);damage_digits53(d->value,x,yy,1,.325f,fade);continue;}
  if(d->kind==2||d->kind==3||d->kind==6){float p=age/1.5f,yy=y+m[6]*(28+56*age/.8f);unsigned glyph=d->kind==3?(d->style==2?53:52):d->kind==6?55:(d->style==2?51:50);if(d->kind==6)damage_glyph53(56,damage_fade53(p),x,yy+3,1);damage_glyph53(glyph,damage_fade53(p),x,yy,d->kind==2?.55f:1);continue;}
  if(d->kind==4||d->kind==5){float p=age/1.5f,yy=y+m[6]*((d->kind==5?36:16)+fmaxf(0,p-.4f)*40),scale=fmaxf(.8f,(1-2*p)*1.3f);damage_digits53(d->value,x,yy,d->kind==4?3:4,scale,damage_fade53(p));continue;}
  if(d->kind==1){damage_spread180(d,&x,&y,1.2f);float p=age/3.f;damage_digits53(d->value,x,y+m[6]*(56+p*8),1,fminf(1.2f,.5f+age*8),damage_fade53(p));continue;}
  if(d->hits>1){int part=d->value/d->hits,remainder=d->value%d->hits;for(int hit=0;hit<d->hits;hit++){float hitAge=age-hit*d->hitGap;if(hitAge>=0&&hitAge<=1.5f)damage_particle53(d,m,part+(hit<remainder),hitAge,0,d->style);}
   damage_spread180(d,&x,&y,1.2f);int landed=(int)(age/d->hitGap)+1;if(landed>d->hits)landed=d->hits;damage_digits53(part*landed+(remainder<landed?remainder:landed),x,y+m[6]*56,d->style==2?2:1,1.2f,damage_fade53(fmaxf(0,age-last)/1.5f));
  }else damage_particle53(d,m,d->value,age,d->critical,d->style);
 }
}
