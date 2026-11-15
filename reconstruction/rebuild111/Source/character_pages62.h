/* Three character pages; visual transition is independent of saved characters. */
#ifndef MYRO_CHARACTER_PAGES62_H
#define MYRO_CHARACTER_PAGES62_H
typedef struct{float active[3];unsigned ready;}CharacterPages62;
static void character_pages_tick62(CharacterPages62*p,unsigned page,unsigned ms){if(page>2)page=2;if(!p->ready){for(unsigned i=0;i<3;i++)p->active[i]=i==page?1:0;p->ready=1;return;}float step=ms/160.f;for(unsigned i=0;i<3;i++){float target=i==page?1:0,d=target-p->active[i];if(d>step)d=step;if(d< -step)d=-step;p->active[i]+=d;}}
static void character_page_rect62(unsigned page,float active,float out[4]){if(active<0)active=0;if(active>1)active=1;out[2]=28*(1+.1f*active);out[3]=3*(1+.1f*active);out[0]=278+page*42-out[2]*.5f;out[1]=89-out[3]*.5f;}
#endif
