"""GPL-3.0-or-later. Read source skill/effect definitions as data, never execute them.
Produce exact classic dependencies for the remaining nine second-class trees.
"""
from pathlib import Path
import re,json,struct,hashlib
from asset_index49 import paths
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48/roBrowserLegacy/src';j=json.loads((r/'class_skill_audit50.json').read_text())['classes'];skills={q['key']:q for v in j.values()for q in v};skills.update(json.loads((r/'class_skill_audit50.json').read_text())['companionSkills']);se=(ref/'DB/Skills/SkillEffect.js').read_text();et=(ref/'DB/Effects/EffectTable.js').read_text();ec=(ref/'DB/Effects/EffectConst.js').read_text();su=(ref/'DB/Skills/SkillUnit.js').read_text();uc=(ref/'DB/Skills/SkillUnitConst.js').read_text()
# Respect the user's multiplayer deferral. Do not exclude self-buffs merely for PartyOnly.
deferred={'PR_SUFFRAGIUM':'other-player cast-time support','PR_BENEDICTIO':'requires two assisting Acolyte players','PR_REDEMPTIO':'party resurrection','MO_KITRANSLATION':'transfer spheres to another player','RG_GANGSTER':'requires nearby Rogues','RG_FLAGGRAFFITI':'guild flag','RG_CLEANER':'guild flag cleanup','BS_ADRENALINE2':'Soul Link prerequisite not present','AM_TWILIGHT1':'Spirit of Alchemist prerequisite','AM_TWILIGHT2':'Spirit of Alchemist/party prerequisites','AM_TWILIGHT3':'Spirit of Alchemist/party prerequisites'}
for key in ['BA_WHISTLE','BA_ASSASSINCROSS','BA_POEMBRAGI','BA_APPLEIDUN','DC_HUMMING','DC_FORTUNEKISS','DC_SERVICEFORYOU']:deferred[key]='other-player song without Soul Link'
for k in skills:
 if k.startswith('BD_')and k not in ['BD_ADAPTATION','BD_ENCORE']:deferred[k]='two-player ensemble'
# Map resource strings encoded as legacy CP949 byte escapes in source JavaScript.
def js_string(s):
 s=s[1:-1];s=re.sub(r'\\x([\da-fA-F]{2})',lambda m:chr(int(m[1],16)),s);s=s.replace('\\\\','\\').replace("\\'","'").replace('\\"','"')
 if any(128<=ord(c)<=255 for c in s):s=s.encode('latin1').decode('cp949')
 return s

def masked(s,hide_strings=True):
 out=list(s);i=0
 while i<len(s):
  if s[i]in "\"'`":
   q=s[i];a=i;i+=1
   while i<len(s):
    if s[i]=='\\':i+=2;continue
    if s[i]==q:i+=1;break
    i+=1
   if hide_strings:out[a:i]=' '*(i-a)
  elif s.startswith('//',i):
   a=i;i=s.find('\n',i)
   if i<0:i=len(s)
   out[a:i]=' '*(i-a)
  elif s.startswith('/*',i):
   a=i;i=s.find('*/',i+2);i=len(s)if i<0 else i+2;out[a:i]=' '*(i-a)
  else:i+=1
 return ''.join(out)

mask_cache={}
def balanced(s,start):
 if s not in mask_cache:mask_cache[s]=masked(s)
 clean=mask_cache[s];stack=[];pair={']':'[','}':'{',')':'('}
 for i in range(start,len(s)):
  c=clean[i]
  if c in '[{(':stack.append(c)
  elif c in ']})':
   assert stack and stack.pop()==pair[c]
   if not stack:return s[start:i+1]
 raise ValueError('Truncated expression')

const={k:int(v) for k,v in re.findall(r'\b(EF_\w+):\s*(-?\d+)',ec)}
unit_ids={k:int(v,0)for k,v in re.findall(r'\b(UNT_\w+):\s*(0x[\da-fA-F]+|\d+)',uc)}
unit_fx={}
for key,value in re.findall(r'SkillUnit\[SU\.(UNT_\w+)\]\s*=\s*([^;]+);',su):
 m=re.search(r'EC\.(EF_\w+)',value);unit_fx[key]=str(const[m[1]])if m else js_string(value.strip())
blocks={}
for m in re.finditer(r'(?m)^\s*(\d+|[a-zA-Z_][\w]*|\x27[^\x27]+\x27):\s*\[',et):
 key=m[1].strip("'");start=et.index('[',m.start());blocks[key]=balanced(et,start)
selected=set();trace={};unresolved=[]
for key,q in skills.items():
 if key in deferred:continue
 m=re.search(r'SkillEffect\[SK\.'+key+r'\]\s*=\s*',se);effect_keys=[]
 if m:
  p=m.end();expr=balanced(se,p)if se[p]=='{'else se[p:se.index(';',p)]
  for v in re.findall(r'\b\w*[Ee]ffectId\w*\s*:\s*(\d+|\[[^\]]*\]|\x27[^\x27]*\x27|"[^"]*")',expr):
   for token in re.findall(r'\d+|\x27[^\x27]*\x27|"[^"]*"',v):effect_keys.append(js_string(token)if token[0]in"\"'"else token)
  if key=='MO_EXTREMITYFIST':effect_keys+=['328','quake']
 # Source unit IDs can be numeric; use the client table for their ground effects.
 um=re.search(r'\bUnit:\s*\{\s*Id:\s*(0x[\da-fA-F]+|\d+)',q['source'])
 if um:
  id=int(um[1],0);name=next((n for n,v in unit_ids.items()if v==id),None)
  if name in unit_fx:effect_keys.append(unit_fx[name])
 trace[key]=sorted(set(effect_keys));selected.update(effect_keys)
requests={}
def add(key,category):
 key=key.replace('/','\\').replace('\\\\','\\').lower()
 if '..'in key.split('\\')or not key.startswith('data\\'):raise ValueError(key)
 requests[key]=category

def resource(prefix,value,ext):
 value=value.replace('/','\\')
 if value.startswith('data\\'):p=value
 elif value.startswith(prefix[5:]):p='data\\'+value
 else:p=prefix+value
 if not Path(p).suffix:p+=ext
 return p

for key in sorted(selected):
 b=blocks.get(key)
 if not b:
  if key not in ['0','-1','quake']:unresolved.append(key)
  continue
 # Each object literal is interpreted independently; functions remain inert text.
 clean=masked(b);stack=[];objects=[]
 for i,c in enumerate(clean):
  if c=='{':stack.append(i)
  elif c=='}':a=stack.pop();objects.append(b[a+1:i])
 for obj in objects:
  obj=masked(obj,False);clean=masked(obj);chunks=[];depth=0;start=0
  for i,c in enumerate(clean):
   if c in '[{(':depth+=1
   elif c in ']})':depth-=1
   elif c==','and depth==0:chunks.append(obj[start:i]);start=i+1
  chunks.append(obj[start:]);props={}
  for chunk in chunks:
   m=re.match(r'\s*(\w+)\s*:\s*(\x27(?:\\.|[^\x27])*\x27|"(?:\\.|[^"])*")\s*$',chunk,re.S)
   if m:props[m[1]]=js_string(m[2])
  typ=props.get('type','')
  if 'wav'in props and props['wav']and not props['wav'].startswith('_'):add(resource('data\\wav\\',props['wav'],'.wav'),'skill-sound')
  for p in ['textureName','textureFile']:
   if p in props:add(resource('data\\texture\\effect\\',props[p],'.tga'),'effect-texture')
  if 'absoluteSpriteName'in props:
   for ext in ['.spr','.act']:add(resource('data\\sprite\\이팩트\\',props['absoluteSpriteName'],ext),'effect-sprite')
  if 'spriteName'in props:
   for ext in ['.spr','.act']:add(resource('data\\sprite\\이팩트\\',props['spriteName'],ext),'effect-sprite')
  if 'file'in props:
   value=props['file']
   if typ=='STR':add(resource('data\\texture\\effect\\',value,'.str'),'skill-str')
   elif typ=='SPR':
    for ext in ['.spr','.act']:add(resource('data\\sprite\\이팩트\\',value,ext),'effect-sprite')
   elif typ=='RSM':add(resource('data\\model\\',value,'.rsm'),'effect-model')
   elif typ in ['3D','2D']:add(resource('data\\texture\\',value,'.tga'),'effect-texture')
# Icons for exact source skills, including passive/quest skills. No third/transcendent groups.
for key in skills:
 if key not in deferred:add('data\\texture\\유저인터페이스\\item\\'+key.lower()+'.bmp','skill-icon')
# Source SpiritSphere renderer uses this original shared texture.
add('data\\texture\\effect\\thunder_center.bmp','monk-sphere-texture')
# Chase known STR texture closure locally; the collector handles still-missing STRs.
for key in list(requests):
 p=paths.get(key)
 if p is None or not key.endswith('.str'):continue
 b=p.read_bytes()
 try:
  assert b[:4]==b'STRM';version,fps,end,layers=struct.unpack_from('<4I',b,4);assert version==148;pos=36
  for _ in range(layers):
   n=struct.unpack_from('<I',b,pos)[0];pos+=4
   for _ in range(n):
    name=b[pos:pos+128].split(b'\0')[0].decode('cp949');pos+=128;add(resource('data\\texture\\effect\\',name,'.bmp'),'str-texture')
   frames=struct.unpack_from('<I',b,pos)[0];pos+=4+frames*124
 except Exception as e:unresolved.append('localSTR:'+key+':'+str(e))
out=r.parent.parent/'asset-request50/Second-Classes';out.mkdir(parents=True,exist_ok=True)
(out/'Resources.tsv').write_text('\n'.join(key+'\t'+cat for key,cat in sorted(requests.items()))+'\n',encoding='utf-8-sig')
(r/'class_asset_audit50.json').write_text(json.dumps(dict(source='roBrowserLegacy2dc0d153 + supplied pre-renewal skill_db',classes=list(j),distinctSourceSkills=len(skills),deferred=deferred,effectTrace=trace,effects=sorted(selected),resources=len(requests),alreadyPresent=sum(k in paths for k in requests),missingResources=[k for k in sorted(requests)if k not in paths],unresolvedEffectKeys=unresolved),indent=2,ensure_ascii=False)+'\n')
print('Source classes',len(j),'distinct skills',len(skills),'resources',len(requests),'already present',sum(k in paths for k in requests),'missing',sum(k not in paths for k in requests),'unresolved effect keys',unresolved)
