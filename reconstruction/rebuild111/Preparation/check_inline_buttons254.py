from pathlib import Path
import json,hashlib,subprocess,os,re
R=Path(__file__).resolve().parent.parent;V=R/'Validation';s=(R/'Source/npc_dialogue_draw55.h').read_text();a=s.index('static void npc_glyph_native55(');b=s.index('{',a);depth=1;i=b+1
while depth:depth+=(s[i]=='{')-(s[i]=='}');i+=1
function=s[a:i]
x=(R.parent/'decompiler203/native-flat203.bin').read_bytes();reference=x[0x12c8b7-65536:0x12c8e4-65536];assert bytes.fromhex('6a086888020000')in reference
code='''#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#define NV097_SET_COMBINER_FACTOR0 0xa60
#define NV097_SET_COMBINER_SPECULAR_FOG_CW0 0x288
#define SKIN_BUTTONS_Y64 1904
#define SKIN_DIALOGUE_Y64 1824
typedef struct{int x,y;unsigned lineHeight,color;}NpcGlyphNative55;
static unsigned combiner,factor,iconPhase,draws;
static uint32_t command[8];
static uint32_t*pb_begin(void){return command;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){if(reg==0x288)combiner=value;if(reg==0xa60)factor=value;return p;}
static void pb_end(uint32_t*p){(void)p;}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){(void)x;(void)y;(void)w;(void)h;(void)u;(void)v;(void)uw;(void)vh;assert(combiner==(iconPhase?8u:0x08010000u));if(iconPhase)assert(factor==0xffffffff);draws++;}
'''+function+'''
int main(void){NpcGlyphNative55 c={20,20,16,UINT_MAX};npc_glyph_native55(&c,'A',0,0,0);iconPhase=1;npc_glyph_native55(&c,256,10,0,0);iconPhase=0;npc_glyph_native55(&c,'B',20,0,0x203060);iconPhase=1;npc_glyph_native55(&c,257,30,0,0x203060);assert(draws==4);c.speakerWidth264=16;iconPhase=0;npc_glyph_native55(&c,'K',0,0,0);assert(draws==6&&factor==0xff203b6d);npc_glyph_native55(&c,'c',20,0,0);assert(draws==7&&factor==0xff000000);puts("PASS actual shared NPC glyph GPU commands match released unmodulated icon mode and restore subsequent text tint; GPU pixel execution remains target-only.");}
''';contextType=re.search(r'typedef struct\{int x,y,lineHeight;[^}]+\}NpcGlyphNative55;',s)[0];code=code.replace('typedef struct{int x,y;unsigned lineHeight,color;}NpcGlyphNative55;',contextType);(V/'actual_inline_buttons254.c').write_text(code);env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with(V/'inline-buttons254.log').open('w')as out:
 subprocess.run(['cc','-O0','-g','-fsanitize=address,undefined',str(V/'actual_inline_buttons254.c'),'-o',str(V/'inline-buttons254_asan')],stdout=out,stderr=subprocess.STDOUT,check=True);subprocess.run([str(V/'inline-buttons254_asan')],env=env,stdout=out,stderr=subprocess.STDOUT,check=True)
(V/'Inline-Buttons-Checks254.json').write_text(json.dumps(dict(passed=True,recoveredReferenceVA='0x12c8b7',referenceSHA256=hashlib.sha256(reference).hexdigest(),source='released1.10.0 executable',actualGPUCommandsRecorded=True,scope='Original native instruction branch sets final combiner8 for icons; restored production callback emits same mode and restores black/colored text tint after icons. Actual shader/raster remains Xbox validation.'),indent=2)+'\n');print('PASS restored inline button combiner, shared callback command recording and native reference.')
