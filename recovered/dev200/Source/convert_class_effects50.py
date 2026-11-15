"""MIT. Source-key STR playback and premultiplied mixed-blend class art.

Keeps all accepted Test49 clips and packed bytes unchanged. New clips sample
original animation at 15 Hz, retaining layer end guards and normal/additive/copy
composition. RGB may exceed alpha, which preserves additive light on any ground.
"""
from pathlib import Path
import hashlib,json,math,re,struct,zlib
import numpy as np
from PIL import Image,ImageDraw
import ro_sprite_bake as ro
from asset_index50 import paths,key50
r=Path(__file__).resolve().parent;base=r.parent.parent/'test49'
def parse_str(b):
    assert b[:4]==b'STRM';version,fps,end,count=struct.unpack_from('<4I',b,4);assert version==148 and fps==60 and 0<count<=64 and 0<end<1200
    pos=36;out=[]
    for _ in range(count):
        n=struct.unpack_from('<I',b,pos)[0];pos+=4;assert n<=64
        names=[b[pos+i*128:pos+(i+1)*128].split(b'\0')[0].decode('cp949').lower() for i in range(n)];pos+=128*n
        n=struct.unpack_from('<I',b,pos)[0];pos+=4;assert n<=2000
        keys=[list(struct.unpack_from('<ii2f8f8ffiff4f3i',b,pos+i*124)) for i in range(n)];pos+=124*n
        assert all(k[1] in [0,1] and all(math.isfinite(v) for v in k) for k in keys)
        out.append((names,sorted(keys,key=lambda k:k[0])))
    assert pos==len(b);return fps,end,out
def sample50(keys,t,count):
    from_id=to_id=-1;last=last_source=0
    for i,k in enumerate(keys):
        if k[0]<=t:
            if k[1]==0:from_id=i
            else:to_id=i
        last=max(last,k[0])
        if k[1]==0:last_source=max(last_source,k[0])
    if from_id<0 or (to_id<0 and last<t):return None
    a=list(keys[from_id]);delta=t-a[0];b=keys[to_id] if to_id>=0 else None
    if to_id!=from_id+1 or b is None or b[0]!=a[0]:
        return None if b is not None and last_source<=a[0] else a
    for i in [*range(2,20),*range(23,28)]:a[i]+=b[i]*delta
    mode=b[21]
    if mode==1:a[20]+=b[20]*delta
    elif mode==2:a[20]=min(a[20]+b[22]*delta,count-1)
    elif mode==3:a[20]=math.fmod(a[20]+b[22]*delta,count)
    elif mode==4:a[20]=math.fmod(a[20]-b[22]*delta,count)
    else:a[20]=0
    return a
def points50(a):
    angle=a[23]*math.tau/1024;c,s=math.cos(angle),math.sin(angle)
    return [(a[2]+a[12+i]*c-a[16+i]*s,a[3]+a[12+i]*s+a[16+i]*c) for i in range(4)]
def sparse50(frames,meta,seq,anchor=192):
    unique=[];lookup={};sequence=[]
    for frame in frames:
        raw=frame.tobytes()
        if raw not in lookup:lookup[raw]=len(unique);unique.append(np.array(frame,dtype=np.uint32))
        sequence.append(lookup[raw])
    pixels=bytearray();directory=[]
    for a in unique:
        ys,xs=np.where(np.any(a,axis=2))
        if not len(xs):directory.append((0,0,0,0,len(pixels)));continue
        x,y,xx,yy=int(xs.min()),int(ys.min()),int(xs.max()+1),int(ys.max()+1);v=a[y:yy,x:xx]
        rgba=((v[:,:,3]*15+127)//255<<12)|((v[:,:,0]>>4)<<8)|((v[:,:,1]>>4)<<4)|(v[:,:,2]>>4)
        directory.append((x,y,xx-x,yy-y,len(pixels)));pixels+=rgba.astype('<u2').tobytes()
    assert len(unique)<=1024 and len(seq)<=8192
    raw=struct.pack('<8I',frames[0].width,frames[0].height,len(unique),len(meta),len(seq),frames[0].width//2,anchor,len(pixels)|0xc0000000)
    raw+=b''.join(struct.pack('<3I',*m) for m in meta)+struct.pack('<%dI'%len(seq),*[sequence[i] for i in seq])+b''.join(struct.pack('<5I',*d) for d in directory)+pixels
    return raw
def texture50(path):
    image=Image.open(path).convert('RGBA');a=np.array(image);a[(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245)]=0;return Image.fromarray(a)
def composite50(canvas,dest_alpha,image,a,pts):
    col=np.clip(a[24:28],0,255)/255;blend=tuple(a[28:30]);assert blend in [(5,7),(5,6),(2,1),(2,2),(0,0)],blend
    # Original renderer draws the four corners as a strip, with full texture UV.
    tex=np.array([[0,0],[image.width,0],[image.width,image.height],[0,image.height]],float)
    for ids in [(0,1,3),(1,2,3)]:
        p=np.array([pts[i] for i in ids]);uv=tex[list(ids)];basis=np.column_stack((p[1]-p[0],p[2]-p[0]))
        if abs(np.linalg.det(basis))<1e-7:continue
        mat=np.column_stack((uv[1]-uv[0],uv[2]-uv[0]))@np.linalg.inv(basis);off=uv[0]-mat@p[0]
        warped=np.stack([np.array(channel.convert('F').transform((128,256),Image.Transform.AFFINE,(*mat[0],off[0],*mat[1],off[1]),Image.Resampling.BILINEAR),dtype=np.float32) for channel in image.split()],axis=2)/255
        mask_image=Image.new('L',(128,256));ImageDraw.Draw(mask_image).polygon([tuple(v) for v in p],fill=255);mask=np.array(mask_image)>0
        source=warped*col;valid=mask&(source[:,:,3]>0)&np.any(source[:,:,:3]>0,axis=2)
        # Shared diagonal belongs to only the first triangle.
        if ids==(1,2,3):
            v=p[2]-p[0];cross=(np.indices(mask.shape)[1]-p[0,0])*v[1]-(np.indices(mask.shape)[0]-p[0,1])*v[0];valid&=np.abs(cross)>.01
        if blend==(0,0):canvas[valid]=[0,0,0,1];dest_alpha[valid]=0
        elif blend==(2,2):
            canvas[valid,:3]+=source[valid,:3];dest_alpha[valid]+=source[valid,3]
        elif blend==(2,1):canvas[valid,:3]=source[valid,:3];canvas[valid,3]=1;dest_alpha[valid]=source[valid,3]
        else:
            alpha=source[:,:,3:4];src=source[:,:,:3]*alpha
            if blend==(5,7):
                da=dest_alpha[valid,None].copy();canvas[valid,:3]=src[valid]+canvas[valid,:3]*da;canvas[valid,3]=1-(1-canvas[valid,3])*da[:,0];dest_alpha[valid]=alpha[valid,0]**2+da[:,0]**2
            else:
                canvas[valid,:3]=src[valid]+canvas[valid,:3]*(1-alpha[valid]);canvas[valid,3]=alpha[valid,0]+canvas[valid,3]*(1-alpha[valid,0]);dest_alpha[valid]=alpha[valid,0]**2+dest_alpha[valid]*(1-alpha[valid,0])
        np.clip(canvas,0,1,out=canvas);np.clip(dest_alpha,0,1,out=dest_alpha)
def main():
    header=(base/'Source/art_assets45.h').read_text();part=header.split('static const Art39Blob art39Blobs')[1].split('};')[0]
    records=[dict(offset=int(a),packed=int(b),raw=int(c),scale=float(d)) for a,b,c,d in re.findall(r'\{(\d+),(\d+),(\d+),([\d.e+-]+)f\}',part)];assert len(records)==51
    payload=bytearray((base/'Effects/effects.bin').read_bytes());prefix=bytes(payload);report=[];pre=r.parent/'ArtPreviews50';pre.mkdir(exist_ok=True)
    def emit(name,frames,meta,sequence,scale,source):
        raw=sparse50(frames,meta,sequence);cp=zlib.compress(raw,9);record=dict(name=name,clip=len(records),offset=len(payload),packed=len(cp),raw=len(raw),scale=scale,frames=len(frames),sources=source)
        records.append(record);report.append(record);payload.extend(cp)
        sheet=Image.new('RGB',(128*8,256),(32,45,32))
        for i in range(8):
            a=np.array(frames[round(i*(len(frames)-1)/7)],dtype=float)/255;bg=np.array([32,45,32])/255;rgb=np.clip(a[:,:,:3]+bg*(1-a[:,:,3:4]),0,1);sheet.paste(Image.fromarray((rgb*255).astype('uint8')),(128*i,0))
        sheet.save(pre/(str(record['clip'])+'-'+name+'.png'));print(record['clip'],name,'raw',len(raw),'packed',len(cp),'scale',round(scale,4),flush=True)
    requested={key50(line.split('\t')[0]) for line in (r.parent.parent/'asset-request50/Second-Classes/Resources.tsv').read_text(encoding='utf-8-sig').splitlines() if line.split('\t')[0].endswith('.str')}
    requested.add(key50('data/texture/effect/shockwave.str'))
    requested-={key50('data/texture/effect/holyhit.str'),key50('data/texture/effect/safetywall.str')}
    str_paths=[(key,paths[key]) for key in sorted(requested)];assert len(str_paths)==39
    for key,path in str_paths:
        fps,end,layers=parse_str(path.read_bytes());times=list(range(0,end,4));poses=[[(names,sample50(keys,t,len(names))) for names,keys in layers if names] for t in times]
        pts=[p for pose in poses for names,a in pose if a and a[27]>0 for p in points50(a)];assert pts,key
        scale=min(.5,60/max(1,max(abs(x-320) for x,y in pts)),184/max(1,320-min(y for x,y in pts)),56/max(1,max(y for x,y in pts)-320))
        textures={};sources={key:hashlib.sha256(path.read_bytes()).hexdigest()}
        for names,_ in layers:
            for name in names:
                texkey=key50('data/texture/effect/'+name);p=paths[texkey];textures[name]=texture50(p);sources[texkey]=hashlib.sha256(p.read_bytes()).hexdigest()
        frames=[]
        for pose in poses:
            canvas=np.zeros((256,128,4),np.float32);dest_alpha=np.ones((256,128),np.float32)
            for names,a in pose:
                if a is None or a[27]<=0 or not(0<=int(a[20])<len(names)):continue
                points=[((x-320)*scale+64,(y-320)*scale+192) for x,y in points50(a)];composite50(canvas,dest_alpha,textures[names[int(a[20])]],a,points)
            frames.append(Image.fromarray((canvas*255+.5).astype('uint8')))
        emit(Path(key.replace('\\','/')).stem,frames,[(0,len(frames),67)]*40,list(range(len(frames))),scale,sources)
    # Complete original ACT effect frames, including RGBA SPR variants.
    text=(r/'convert_classic49.py').read_text();ns=dict(ro=ro,np=np,Image=Image);exec(text[text.index('def sprites('):text.index('ro.originY=192')],ns)
    sprpaths=sorted((k,p) for k,p in paths.items() if 'Test50' in str(p) and '\\이팩트\\' in k and k.endswith('.spr') and not k.endswith('\\매.spr'))
    for key,path in sprpaths:
        actkey=key[:-4]+'.act';assert actkey in paths;images,ni=ns['sprites'](path.read_bytes());acts,delays=ns['actions'](paths[actkey].read_bytes());frames=[];meta=[];sequence=[];ro.originY=192
        for group in range(5):
            for direction in range(8):
                ai=min(direction,len(acts)-1);start=len(sequence)
                for layers in acts[ai]:
                    frame=Image.new('RGBA',(128,256))
                    for x,y,index,mirror,col,xs,ys,angle,typ in layers:
                        if index<0:continue
                        ro.drawlayer(frame,images,(x*.5,y*.5,index+(ni if typ else 0),mirror,col,xs*.5,ys*.5,angle,0))
                    a=np.array(frame,dtype=np.uint16);a[:,:,:3]=a[:,:,:3]*a[:,:,3:4]//255;sequence.append(len(frames));frames.append(Image.fromarray(a.astype('uint8')))
                meta.append((start,len(sequence)-start,max(20,round(delays[ai]))))
        emit(Path(key.replace('\\','/')).stem,frames,meta,sequence,.5,{key:hashlib.sha256(path.read_bytes()).hexdigest(),actkey:hashlib.sha256(paths[actkey].read_bytes()).hexdigest()})
    from class_proc_bake50 import extra_clips50
    extra_clips50(emit,texture50,ns["sprites"],ns["actions"],ro)
    assert payload[:len(prefix)]==prefix
    out='/* Original effects; accepted Test49 prefix unchanged; new premultiplied RGBA4444. */\n#define ART39_COUNT %d\ntypedef struct {unsigned offset,packed,raw;float scale;} Art39Blob;\nstatic const Art39Blob art39Blobs[ART39_COUNT]={\n'%len(records)
    out+=','.join('{%d,%d,%d,%.9gf}'%(v['offset'],v['packed'],v['raw'],v['scale']) for v in records).replace(',1f}',',1.0f}')+'};\n#ifdef MYRO_HOST\nstatic const unsigned char art39Packed[]={'+','.join(map(str,payload))+'};\n#endif\n#define ART_FILE_BYTES45 %d\n'%len(payload)
    out+='static const unsigned art45Crc[ART39_COUNT]={'+','.join(str(zlib.crc32(payload[v['offset']:v['offset']+v['packed']]))+'u' for v in records)+'};\n'
    (r/'art_assets45.h').write_text(out);(r.parent/'Effects/effects.bin').write_bytes(payload);(r/'class_effects50.json').write_text(json.dumps(report,indent=2)+'\n')
    (r/'class_effect_ids50.h').write_text('/* Generated original effect clip names. */\n'+''.join('#define FX50_'+{'버서크':'FURY','연환':'CHAINCOMBO','데몬스트레이션':'DEMONSTRATION','블러드러스트':'BLOODLUST','캐슬링':'CASTLING'}.get(v['name'],re.sub('[^A-Z0-9_]','_',v['name'].upper()))+' '+str(v['clip'])+'\n' for v in report))
    print('PASS50',len(report),'new original effects; old51clips byte-identical; pack',len(payload),flush=True)
if __name__=='__main__':main()
