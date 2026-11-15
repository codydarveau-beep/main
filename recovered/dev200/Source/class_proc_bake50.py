"""GPL-3.0-or-later. Original procedural textures and inert EF328 parameters.
The source object literals remain data; no client JavaScript is executed.
"""
from pathlib import Path
import hashlib,json,math,re
import numpy as np
from PIL import Image
from asset_index50 import paths,key50

def source_objects50(effect):
    r=Path(__file__).resolve().parent
    text=(r/'collect_requests50.py').read_text();ns={'re':re}
    exec(text[text.index('def js_string'):text.index('const={')],ns)
    et=(r.parent.parent/'reference48/roBrowserLegacy/src/DB/Effects/EffectTable.js').read_text()
    m=re.search(r'(?m)^\s*'+str(effect)+r':\s*\[',et);assert m
    block=ns['balanced'](et,et.index('[',m.start()));clean=ns['masked'](block,False)
    clean=re.sub(r"'(?:\\.|[^'\\])*'",lambda m:json.dumps(ns['js_string'](m[0])),clean)
    clean=re.sub(r'\b([A-Za-z_][\w]*)\s*:',r'"\1":',clean)
    clean=re.sub(r',\s*([}\]])',r'\1',clean)
    return json.loads(clean)

def extra_clips50(emit,texture50,sprites,actions,ro):
    def original(key):
        key=key50('data/texture/'+key);p=paths[key]
        return texture50(p),{key:hashlib.sha256(p.read_bytes()).hexdigest()}
    # SpiritSphere.js draws two additive blue/white quads from this same bitmap.
    image,source=original('effect/thunder_center.bmp');frame=np.zeros((256,128,4),np.float32)
    for side,color in [(32,(0,0,1)),(19,(.8,.8,1))]:
        a=np.array(image.resize((side,side),Image.Resampling.LANCZOS),dtype=np.float32)/255
        x,y=64-side//2,192-side//2;frame[y:y+side,x:x+side,:3]+=a[:,:,:3]*a[:,:,3:4]*color
    np.clip(frame,0,1,out=frame)
    emit('spirit_sphere',[Image.fromarray((frame*255+.5).astype('uint8'))],[(0,1,100)]*40,[0],.5,source)
    image,source=original('effect/blue_ivy.bmp');image.thumbnail((56,56));a=np.array(image,dtype=np.float32)/255;a[:,:,:3]*=a[:,:,3:4];a[:,:,3]=0
    im=Image.fromarray((a*255+.5).astype('uint8'));frame=Image.new('RGBA',(128,256));frame.paste(im,(64-im.width//2,192-im.height//2))
    emit('finger_sphere',[frame],[(0,1,150)]*40,[0],.5,source)
    # Original six Asura glyphs, staggered duplicates, logarithmic shrinking,
    # grow-back and fade. Mesh rings are rendered in world space separately.
    defs=[d for d in source_objects50(328) if d.get('type')=='3D'];sources={};images={}
    for d in defs:
        if d['file'] not in images:
            images[d['file']],ss=original(d['file']);sources.update(ss)
    scale=.25;frames=[]
    for ms in range(0,2201,67):
        canvas=Image.new('RGBA',(128,256))
        for d in defs:
            for copy in range(d.get('duplicate',1)):
                age=ms-d.get('delayStart',0)-copy*d.get('timeBetweenDupli',0);dur=d['duration']
                if age<0 or age>=dur:continue
                phase=age/dur;alpha=max(0,min(1,d.get('alphaMax',1)+copy*d.get('alphaMaxDelta',0)))
                if d.get('fadeIn') and phase<.25:alpha*=phase*4
                elif d.get('fadeOut') and phase>.75:alpha*=(1-phase)*4
                p=math.log10(1+9*phase) if d.get('sizeSmooth') else phase
                size=(d.get('sizeStart',100)+(d.get('sizeEnd',100)-d.get('sizeStart',100))*p)/100
                image=images[d['file']];w=max(1,round(image.width*size*scale));h=max(1,round(image.height*size*scale));a=np.array(image.resize((w,h),Image.Resampling.LANCZOS),dtype=np.float32)
                a[:,:,:3]*=[d.get('red',1),d.get('green',1),d.get('blue',1)];a[:,:,3]*=alpha
                layer=Image.fromarray(np.clip(a,0,255).astype('uint8'))
                # Source cell positions are mapped through the existing24px/cell art scale.
                x=round(64+d.get('posx',0)*24*scale-w/2);y=round(192-d.get('posz',0)*24*scale-h/2)
                canvas.alpha_composite(layer,(x,y))
        a=np.array(canvas,dtype=np.uint16);a[:,:,:3]=a[:,:,:3]*a[:,:,3:4]//255
        frames.append(Image.fromarray(a.astype('uint8')))
    emit('asura_glyphs',frames,[(0,len(frames),67)]*40,list(range(len(frames))),scale,sources)
    # Original directional arrow ACT, reused by Melody Strike/Slinging Arrow.
    stem=key50('data/sprite/npc/skel_archer_arrow');sp=paths[stem+'.spr'];ac=paths[stem+'.act'];images,ni=sprites(sp.read_bytes());acts,delays=actions(ac.read_bytes());frames=[];meta=[];seq=[];ro.originY=192
    for group in range(5):
        for direction in range(8):
            ai=direction%len(acts);start=len(seq)
            for layers in acts[ai]:
                frame=Image.new('RGBA',(128,256))
                for x,y,index,mirror,col,xs,ys,angle,typ in layers:
                    if index>=0:ro.drawlayer(frame,images,(x*.5,y*.5,index+(ni if typ else 0),mirror,col,xs*.5,ys*.5,angle,0))
                a=np.array(frame,dtype=np.uint16);a[:,:,:3]=a[:,:,:3]*a[:,:,3:4]//255;frames.append(Image.fromarray(a.astype('uint8')));seq.append(len(frames)-1)
            meta.append((start,len(seq)-start,max(20,round(delays[ai]))))
    emit('arrow_projectile',frames,meta,seq,.5,{stem+'.spr':hashlib.sha256(sp.read_bytes()).hexdigest(),stem+'.act':hashlib.sha256(ac.read_bytes()).hexdigest()})
