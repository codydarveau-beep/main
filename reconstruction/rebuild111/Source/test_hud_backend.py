"""MIT. Compile the actual native batch-end function against a command recorder.
Checks commands/bounds only; does not simulate NV2A rasterisation.
Requires host GCC, Python3. No SDK or ROM files needed.
"""
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parent
s=(root/'hud.h').read_text();a=s.index('static void hud_batch_end(void)');b=s.index('static void hud_quad(',a);body=s[a:b]
harness=r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hud_batch.h"
#include "skin_layout.h"
typedef uintptr_t DWORD;
#define NV097_SET_VERTEX_DATA_ARRAY_FORMAT 0x100
#define NV097_SET_VERTEX_DATA_ARRAY_OFFSET 0x200
#define NV097_BREAK_VERTEX_BUFFER_CACHE 0x300
#define NV097_SET_BEGIN_END 0x400
#define NV097_SET_BEGIN_END_OP_QUADS 8
#define NV097_DRAW_ARRAYS 0x500
static HudBatch hudBatch;static void*skinTexture=(void*)0x1000;
static uint32_t commands[129];static unsigned length,setups,blocks;
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned pitch,unsigned fmt,int blend){assert(t==skinTexture&&w==512&&h==SKIN_H&&pitch==2048&&fmt==0x0001122a&&blend==1);setups++;}
static uint32_t*pb_begin(void){blocks++;return commands;}
static uint32_t*pb_push1(uint32_t*p,unsigned method,unsigned value){assert(p+2<=commands+128);*p++=method;*p++=value;return p;}
static void pb_end(uint32_t*p){length=p-commands;assert(commands[128]==0xdeadbeef);}
'''
checks=r'''
int main(void){for(unsigned n=0;n<=HUD_BATCH_QUADS;n++){
 memset(commands,0,sizeof(commands));commands[128]=0xdeadbeef;length=setups=blocks=0;hudBatch.count=n;hudBatch.active=1;hudBatch.vertices=(float*)0x10000;
 hud_batch_end();assert(!hudBatch.active);if(!n){assert(!setups&&!blocks);continue;}
 assert(setups==1&&blocks==1&&length<=128);unsigned total=0,started=0,ended=0;
 for(unsigned i=0;i<length;i+=2){unsigned k=commands[i],v=commands[i+1];
  if(k==NV097_SET_BEGIN_END){if(v==8)started++;else{assert(v==0);ended++;}}
  if(k==NV097_DRAW_ARRAYS){unsigned count=(v>>24)+1,start=v&0xffffff;assert(start==total&&count%4==0&&count<=252);total+=count;}
 }
 assert(total==n*4&&started==1&&ended==1);
 }puts("PASS actual native HUD command function: zero/full capacity, one setup/pass, ordered quad chunks, 128-DWORD block bounds and sentinel");}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(harness+body+checks)
 subprocess.run(['gcc','-O2','-I',str(root),str(p/'test.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
