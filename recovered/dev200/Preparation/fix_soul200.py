from pathlib import Path
S=Path('/workspace/myro/dev200/Source')
def edit(n,a,b):
 p=S/n;s=p.read_text();assert a in s,(n,a);p.write_text(s.replace(a,b))
edit('combat.h','int fxSkill,fxRank48;','int fxSkill,fxRank48;int fxTarget200;unsigned fxLife200;float fxFromX200,fxFromY200;')
edit('skills.h','g->fxSkill=id;g->fxRank48=rank;','g->fxSkill=id;g->fxRank48=rank;g->fxTarget200=target;g->fxLife200=target>=0&&target<MOB_COUNT?g->mobs[target].life:0;g->fxFromX200=g->x;g->fxFromY200=g->y;')
edit('skills.h','if(p->skill!=75&&p->skill<127)skill_sound49(g,p->skill);','if(p->skill!=75&&p->skill<127&&(p->skill!=23||p->done==1))skill_sound49(g,p->skill);')
edit('art_visual39.h','if(g->fxSkill==23)e->bolts=','if(g->fxSkill==23){e->target45=g->fxTarget200;e->life45=g->fxLife200;e->startX=g->fxFromX200;e->startY=g->fxFromY200;}if(g->fxSkill==23)e->bolts=')
edit('art_draw39.h','#include "projection.h"','#include "projection.h"\n/* Per-draw brightness for premultiplied additive artwork; no new textures. */\nstatic unsigned art39Gain200=255;')
a='p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,clip>=51?1:(clip<10||clip>=15)?1:0x302);'
b='if(art39Gain200<255&&clip>=15&&clip<51){p=pb_push1(p,NV097_SET_BLEND_COLOR,(art39Gain200<<24)|0xffffffu);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,NV097_SET_BLEND_FUNC_SFACTOR_V_CONSTANT_ALPHA);}else p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,clip>=51?1:(clip<10||clip>=15)?1:0x302);'
edit('art_draw39.h',a,b)
edit('classic_draw49.h','retreat=24*(1+hit*.2f)*sine;','retreat=fminf(24*(1+hit*.2f),length*.15f)*sine;')
edit('classic_draw49.h','for(unsigned duplicate=0;duplicate<5;duplicate++){','unsigned beforeGain200=art39Gain200;for(unsigned duplicate=0;duplicate<5;duplicate++){')
edit('classic_draw49.h','art39_world_z45(43,elapsed,m,x,y,zoom*(1+4*p),1,24+32*(1+hit*.1f)*sine);','art39Gain200=(unsigned)(beforeGain200*powf(.65f,(float)duplicate));art39_world_z45(43,elapsed,m,x,y,zoom*(1+4*p),1,24+32*(1+hit*.1f)*sine);')
edit('classic_draw49.h','\n }\n}\nstatic int classic_event49','\n }art39Gain200=beforeGain200;\n}\nstatic int classic_event49')
edit('classic_draw49.h','if(e->skill==23||e->skill==78){int count=','if(e->skill==23||e->skill==78){unsigned beforeGain200=art39Gain200;if(e->skill==23)art39Gain200=128;int count=')
edit('classic_draw49.h','}return 1;}\n if(e->skill==74)','}art39Gain200=beforeGain200;return 1;}\n if(e->skill==74)')
edit('sound_mix.h','/* Sum before gain:','/* Original Soul Strike recording is much hotter than the base cue bank. */\nstatic int sound_clip_gain200(unsigned id,int sample){return id==52?sample*30/100:sample;}\n/* Sum before gain:')
edit('sound_mix.h','mix+=sound_voice_sample64(v,data[v->id],lengths[v->id]);','mix+=sound_clip_gain200(v->id,sound_voice_sample64(v,data[v->id],lengths[v->id]));')
edit('sound_mix.h','int sample=sound_voice_sample64(v,data[v->id],lengths[v->id]);','int sample=sound_clip_gain200(v->id,sound_voice_sample64(v,data[v->id],lengths[v->id]));')
p=S/'main.c';s=p.read_text();s=s.replace('#include "water_actor54.h"','#include "water_actor54.h"\n#include "campaign_scene200.h"');p.write_text(s)
