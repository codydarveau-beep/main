"""MIT. Bounded original companion SPR/ACT and trap RSM pack; no source edits."""
from pathlib import Path
import hashlib,json,math,re,struct,zlib
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
from asset_index50 import paths,key50
from convert_class_effects50 import sparse50,texture50
from convert_scenery import model,uv_tiles
r=Path(__file__).resolve().parent;out=r.parent/'Systems';out.mkdir(exist_ok=True);pre=r.parent/'SystemPreviews50';pre.mkdir(exist_ok=True)
text=(r/'convert_classic49.py').read_text();ns=dict(ro=ro,np=np,Image=Image);exec(text[text.index('def sprites('):text.index('ro.originY=192')],ns)
names=['lif','amistr','filir','vanilmirth','lif2','amistr2','filir2','vanilmirth2','lif_h','amistr_h','filir_h','vanilmirth_h','lif_h2','amistr_h2','filir_h2','vanilmirth_h2']
stems=[key50('data/sprite/homun/'+name) for name in names]+[key50('data/sprite/몬스터/매')]+[key50('data/sprite/'+folder+'/'+name) for folder,name in [('npc','mandragora'),('npc','hydra'),('npc','flora'),('몬스터','parasite'),('몬스터','geographer'),('몬스터','marine_sphere')]]
payload=bytearray();blobs=[];sources={};contacts=[]
def read(key):
    key=key50(key);b=paths[key].read_bytes();sources[key]=hashlib.sha256(b).hexdigest();return b
def emit(name,raw):
    cp=zlib.compress(raw,9);blobs.append(dict(name=name,offset=len(payload),packed=len(cp),raw=len(raw),crc=zlib.crc32(cp)));payload.extend(cp);print(name,len(raw),len(cp),flush=True)
for index,stem in enumerate(stems):
    images,ni=ns['sprites'](read(stem+'.spr'));actions,delays=ns['actions'](read(stem+'.act'));frames=[];sequence=[];meta=[];contact=[];ro.originY=192
    for group in range(5):
        for direction in range(8):
            ai=group*8+direction
            if ai>=len(actions):ai=direction%len(actions)
            start=len(sequence)
            for pose,layers in enumerate(actions[ai]):
                canvas=Image.new('RGBA',(128,256))
                for x,y,idx,mirror,col,xs,ys,angle,typ in layers:
                    if idx<0:continue
                    ro.drawlayer(canvas,images,(x*.5,y*.5,idx+(ni if typ else 0),mirror,col,xs*.5,ys*.5,angle,0))
                if group==0 and pose==0:
                    a=np.array(canvas);ys,xs=np.where(a[:,:,3]>127);assert len(xs);bottom=ys.max();low=ys>=bottom-6;footx=(xs[low].min()+xs[low].max())/2;contact.append([float(64-footx),float(192-bottom-1)])
                sequence.append(len(frames));frames.append(canvas)
            assert len(sequence)>start;meta.append((start,len(sequence)-start,max(20,round(delays[ai]))))
    raw=sparse50(frames,meta,sequence);emit(stem.split('\\')[-1],raw);contacts.append(contact)
    sheet=Image.new('RGBA',(128*8,256),(32,45,32,255))
    for d in range(8):sheet.alpha_composite(frames[meta[d][0]],(128*d,0))
    sheet.convert('RGB').save(pre/(str(index)+'-'+stem.split('\\')[-1]+'.png'))
# All ten original model variants, one small shared cutout atlas and vertex buffer.
trapnames=['트랩01','트랩02','트랩03','트랩03_2','트랩03_3','트랩03_4','트랩03_5','트랩03_6','트랩04','트랩05']
models=[model(read('data/model/외부소품/'+name+'.rsm')) for name in trapnames];texnames=sorted({key50(t) for m in models for t,_,_ in m});assert len(texnames)<=16
w=1024;slot=132;h=1
while h<math.ceil(len(texnames)/4)*slot:h*=2
atlas=Image.new('RGBA',(w,h))
for i,name in enumerate(texnames):
    image=texture50(paths[key50('data/texture/'+name)]).resize((128,128),Image.Resampling.LANCZOS);read('data/texture/'+name);atlas.paste(image,(i%4*slot+2,i//4*slot+2))
a=np.array(atlas,dtype=np.uint16);pixels=((a[:,:,3]>127).astype(np.uint16)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3);emit('trap-atlas',struct.pack('<II',w,h)+pixels.astype('<u2').tobytes())
vertices=[];directory=[]
for mesh in models:
    first=len(vertices)
    for texture,points,uv in mesh:
        ti=texnames.index(key50(texture))
        for poly in uv_tiles(points,uv):
            for j in range(1,len(poly)-1):
                for v in [poly[0],poly[j],poly[j+1]]:vertices.append([*v[:3],ti%4*slot+2+v[3]*128,ti//4*slot+2+v[4]*128])
    directory.append([first,len(vertices)-first])
assert len(vertices)<16000 and all(n%3==0 for _,n in directory)
raw=struct.pack('<II',len(models),len(vertices))+np.array(directory,dtype='<u4').tobytes()+np.array(vertices,dtype='<f4').tobytes();emit('trap-models',raw)
header='/* Original companion/terrain art, streamed with bounded current-class residency. */\n#ifndef MYRO_SYSTEM_DATA50_H\n#define MYRO_SYSTEM_DATA50_H\n#define SYSTEM_FILE_BYTES50 %d\n#define SYSTEM_BLOBS50 %d\ntypedef struct{unsigned offset,packed,raw,crc;} SystemBlob50;\nstatic const SystemBlob50 systemBlobs50[SYSTEM_BLOBS50]={\n'%(len(payload),len(blobs))
header+=','.join('{%d,%d,%d,%du}'%(v['offset'],v['packed'],v['raw'],v['crc']) for v in blobs)+'};\nstatic const float companionContact50[23][8][2]='+json.dumps(contacts,separators=(',',':')).replace('[','{').replace(']','}')+';\n#endif\n'
(out/'systems.bin').write_bytes(payload);(r/'system_data50.h').write_text(header);(r/'systems50.json').write_text(json.dumps(dict(blobs=blobs,sources=sources,contacts=contacts,trapNames=trapnames,trapDirectory=directory,vertices=len(vertices),atlas=[w,h],sha256=hashlib.sha256(payload).hexdigest()),indent=2)+'\n');print('PASS50 23 source actors and10 original traps; pack',len(payload),'bytes',flush=True)
