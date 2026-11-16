from pathlib import Path
import json,re,subprocess,os
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source'
def fn(s,name):
 at=s.index('static ',s.rfind('\n',0,s.index(name+'('))+1);brace=s.index('{',at);depth=1;i=brace+1
 while depth:
  depth+=(s[i]=='{')-(s[i]=='}');i+=1
 return s[at:i]+'\n'
s=(S/'hud.h').read_text();names=['hud_frame_begin253','hud_batch_begin_texture53','hud_batch_end','hud_quad'];actual=''.join(fn(s,n)for n in names);constants=sorted(set(re.findall(r'NV097_\w+',actual)))
pre='''#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "hud_batch.h"
typedef uintptr_t DWORD;
static float skin[HUD_BATCH_QUADS*HUD_QUAD_FLOATS],damage[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];
static float*hudSkinVertices54b=skin,*hudDamageVertices54b=damage;
static unsigned hudSkinUsed253,hudDamageUsed253;
static HudBatch hudBatch;
static void*skinTexture=(void*)1,*hudBatchTexture53;
static unsigned hudBatchWidth53,hudBatchHeight53,hudBatchPitch53,hudBatchFormat53;
static void fail(const char*s){(void)s;_Exit(77);}
static uint32_t commands[16];
static uint32_t*pb_begin(void){return commands;}
static void pb_end(uint32_t*p){(void)p;}
static uint32_t*pb_push1(uint32_t*p,unsigned k,unsigned v){(void)k;(void)v;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){(void)x;(void)y;(void)z;(void)u;(void)v;return p;}
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned p,unsigned f,int b){(void)t;(void)w;(void)h;(void)p;(void)f;(void)b;}
'''+''.join('#define '+n+' 0\n'for n in constants)
body='''
static void start(void*t){hud_batch_begin_texture53(t,512,2048,2048,0);}
int main(void){for(unsigned prefix=1;prefix<1000;prefix*=7){hud_frame_begin253();start(skinTexture);for(unsigned i=0;i<prefix;i++)hud_quad(i+1,2,3,4,5,6,7,8);hud_batch_end();float*saved=malloc(prefix*HUD_QUAD_FLOATS*sizeof(float));memcpy(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float));start(skinTexture);assert(hudBatch.vertices==skin+prefix*HUD_QUAD_FLOATS);for(unsigned i=0;i<30;i++)hud_quad(100,20,3,4,5,6,7,8);hud_batch_end();assert(!memcmp(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float)));start((void*)2);assert(hudBatch.vertices==damage);hud_quad(2,2,2,2,0,0,1,1);hud_batch_end();start(skinTexture);assert(hudBatch.vertices==skin+(prefix+30)*HUD_QUAD_FLOATS);hud_quad(9,9,9,9,0,0,1,1);hud_batch_end();assert(!memcmp(saved,skin,prefix*HUD_QUAD_FLOATS*sizeof(float)));free(saved);}hud_frame_begin253();hudSkinUsed253=HUD_BATCH_QUADS-1;start(skinTexture);hud_quad(1,1,1,1,1,1,1,1);hud_batch_end();assert(hudSkinUsed253==HUD_BATCH_QUADS);pid_t p=fork();assert(p>=0);if(!p){start(skinTexture);hud_quad(1,1,1,1,1,1,1,1);_Exit(0);}int status;assert(waitpid(p,&status,0)==p&&WIFEXITED(status)&&WEXITSTATUS(status)==77);hud_frame_begin253();assert(!hudSkinUsed253&&!hudDamageUsed253);puts("PASS actual shared HUD arenas: modal/adjacent windows preserve submitted vertex prefixes, separate skin/damage cursors, frame reset and capacity denial. GPU boundary modeled.");}
'''
(V/'actual_hud_arena253.c').write_text(pre+actual+body)
env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with(V/'shared-ui253.log').open('w')as out:
 subprocess.run(['cc','-O0','-g','-fsanitize=address,undefined','-I'+str(S),str(V/'actual_hud_arena253.c'),'-o',str(V/'hud-arena253_asan')],stdout=out,stderr=subprocess.STDOUT,check=True);subprocess.run([str(V/'hud-arena253_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
helper=fn((S/'window_draw.h').read_text(),'ui_skill_maximum253');(V/'actual_skill_maximum253.c').write_text('#include <assert.h>\n#include "combat.h"\n'+helper+'''\nstatic Combat g;int main(void){int index=skill_rank_index(338);assert(index>=0&&learnMax[index]==9);for(unsigned i=0;i<=9;i++){g.ranks[index]=i;assert(ui_skill_maximum253(&g,338)==9);}assert(ui_skill_maximum253(&g,0)==1);g.jobId=13;g.persistent50.copySkill=3;g.persistent50.copyRank=4;assert(ui_skill_maximum253(&g,3)==4);}\n''')
with(V/'skill-maximum253.log').open('w')as out:
 subprocess.run(['cc','-O0','-g','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-fsanitize=address,undefined','-I'+str(S),str(V/'actual_skill_maximum253.c'),'-lm','-lz','-o',str(V/'skill-maximum253_asan')],stdout=out,stderr=subprocess.STDOUT,check=True);subprocess.run([str(V/'skill-maximum253_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Shared-UI-Checks253.json').write_text(json.dumps(dict(passed=True,scope='Exact production HUD arena lifecycle and skill-cap helper under sanitizers. Existing submitted vertices survive modal/adjacent batches; overflow rejected; Basic Skill remains /9 across all learned ranks; copied skill and nonlearnable bounds preserved.',XboxVisualAcceptance=False,additionalRestorationReviewsCompleted=0),indent=2)+'\n');print('PASS shared HUD vertex ownership and stable skill maximum; host boundaries only.')
