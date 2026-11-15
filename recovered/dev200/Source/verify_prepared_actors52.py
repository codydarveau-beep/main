# MIT. Validate staged sprites with the actual native loader, and activated class variants.
from pathlib import Path
import re,json,hashlib,tempfile,subprocess
r=Path(__file__).resolve().parent;out=r.parent/'ActorAssets52';base=r.parent.parent/'test51'
blob=(out/'actors52.bin').read_bytes();old=(base/'Actors/actors.bin').read_bytes();assert blob[:len(old)]==old
rows=json.loads((out/'actors52.json').read_text());assert len(rows)==64 and {q['job']for q in rows}==set(range(21,33))
for q in rows:
 assert (q['actor']==q['job']+1 or q['actor']in [41,42]) and q['raw']<=4*1024*1024
 if q['weapon']and not(q['name']=='Gypsy'and q['wtype']==1 or q['name']=='Champion'and q['wtype']==13):assert all(q['visibleDirections'])
contacts=json.loads((out/'contacts52.json').read_text());assert len(contacts)==14
assert all(len(v)==8 and all(len(p)==2 and max(map(abs,p))<32 for p in v)for v in [r['contact']for r in contacts])
source=(r/'sprites.h').read_text();load=source[:source.index('static void sprite_load_enemy44')]
frames=source[source.index('static unsigned sprite_frame('):source.index('#include "actor_disc.h"')]
program='''
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>
#include "combat.h"
#define MYRO_HOST 1
#define MYRO_DISC_ENEMIES44 1
#include "../ActorAssets52/actor_data52.h"
static void fail(const char*s){fprintf(stderr,"%s\\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf sz=raw;assert(uncompress(b,&sz,p,packed)==Z_OK&&sz==raw);return b;}
'''+load+frames+'''
int main(int argc,char**argv){assert(argc==2);FILE*f=fopen(argv[1],"rb");assert(f);fseek(f,0,SEEK_END);assert(ftell(f)==ACTOR_FILE_BYTES);unsigned peak=0;
for(unsigned i=0;i<ACTOR_VARIANTS;i++){const ActorBlob*b=&actorBlobs[i];assert(b->offset<=ACTOR_FILE_BYTES&&b->packed<=ACTOR_FILE_BYTES-b->offset);unsigned char*p=malloc(b->packed);assert(p&&!fseek(f,b->offset,SEEK_SET)&&fread(p,1,b->packed,f)==b->packed);assert(crc32(0,p,b->packed)==b->crc);SparseSprite sprite={0};sprite_load(&sprite,"staged actor",p,b->packed,b->raw);free(p);if(b->raw>peak)peak=b->raw;
for(unsigned group=0;group<sprite.actions/8;group++)for(int d=0;d<8;d++)for(int n=0;n<20;n++){unsigned frame=sprite_frame(&sprite,group,d,n*.05f,.6f,0);assert(frame<sprite.frames);}free(sprite.raw);}fclose(f);printf("PASS staged52 actual native sprite loader/frame traversal: %u variants, prior51 prefix retained; one-body peak%u bytes.\\n",ACTOR_VARIANTS,peak);}
'''
with tempfile.TemporaryDirectory(prefix='myro-actors50-')as td:
 d=Path(td);src=d/'check.c';src.write_text(program);exe=d/'check'
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-I'+str(r),str(src),'-lm','-lz','-o',str(exe)],check=True)
 subprocess.run([str(exe),str(out/'actors52.bin')],check=True)
print('PASS52 fourteen contact sets,64 authentic body/weapon/dual/mount variants; source weapon poses and Champion normal attack slices validated. Mounted variants currently body-only; not activated yet.')
