from pathlib import Path
import ast,contextlib,hashlib,json,mmap,os,shutil,struct,subprocess,zipfile
R=Path(__file__).resolve().parent.parent;D=R.parent/'release1111';V=R/'Validation';S=D/'Source';P=D/'MyRO-1.11.1';P.mkdir(exist_ok=True)
def sha(p):
 h=hashlib.sha256()
 with p.open('rb')as f:
  for b in iter(lambda:f.read(1048576),b''):h.update(b)
 return h.hexdigest()
def files(b):
 assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA';sector,size=struct.unpack_from('<II',b,65556);out={};seen=set()
 def visit(at):
  assert at not in seen and 0<=at<=size-14;seen.add(at);p=sector*2048+at;l,r,start,n,attr,k=struct.unpack_from('<HHIIBB',b,p);assert not attr&16;name=b[p+14:p+14+k].decode();assert start*2048+n<=len(b);out[name]=(start*2048,n)
  if l:visit(l*4)
  if r:visit(r*4)
 visit(0);return out
if __name__=='__main__':
 base=R.parent/'released-1.10.0.iso';expected='b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e';assert sha(base)==expected
 n=json.loads((V/'Normal-Complete-Checks244.json').read_text());assert n['passed']
 for name in ['Restoration-Review-Pass1-271.json','Restoration-Review-Pass2-272.json']:
  r=json.loads((V/name).read_text());assert r['passed']and r['sourceDigest']==n['sourceDigest']
 x=(D/'XboxFiles/default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];c=struct.unpack_from('<I',x,0x118)[0]-b;assert x[c+12:c+92].decode('utf-16le').split('\0')[0]=='MyRO v1.11.1';reserve=struct.unpack_from('<I',x,0x130)[0];assert reserve==0x28000
 u={line.split('\t')[0].rsplit(':',1)[-1]:int(line.split('\t')[1])for line in(S/'main.su').read_text().splitlines()}
 ref=json.loads((V/'Native-Checks194.json').read_text());chains=[]
 for row in ref['knownChains']:
  frames={k:u[k]if k in u else value for k,value in row['frames'].items()};total=sum(frames.values());assert total+32768<=reserve;chains.append(dict(frames=frames,bytes=total))
 (V/'Release-Native-Checks275.json').write_text(json.dumps(dict(passed=True,title='MyRO v1.11.1',stackReserve=reserve,knownChains=chains,sourceLabels='Release-Source-Labels274.json',scope='Separate release-labelled native compile and known conservative stack guards; no Xbox/Xemu execution or full RAM claim'),indent=2)+'\n')
 for p in(R/'XboxFiles').iterdir():
  if p.name!='default.xbe':
   q=D/'XboxFiles'/p.name
   if not q.exists():q.symlink_to(p.resolve())
 assert len(list((D/'XboxFiles').iterdir()))==20
 target=D/'MyRO-1.11.1.iso'
 subprocess.run(['/workspace/myro/toolchain/xbox-nxdk/tools/extract-xiso/build/extract-xiso','-q','-c',str(D/'XboxFiles'),str(target)],check=True)
 ops=[];meta={};payload=P/'payload.001.bin'
 with contextlib.ExitStack()as st:
  bf=st.enter_context(base.open('rb'));old=st.enter_context(mmap.mmap(bf.fileno(),0,access=mmap.ACCESS_READ));tf=st.enter_context(target.open('rb'));new=st.enter_context(mmap.mmap(tf.fileno(),0,access=mmap.ACCESS_READ));out=st.enter_context(payload.open('wb'));of=files(old);nf=files(new);assert set(nf)==set(of)|{'guildviews.bin'}
  def data(at,length):
   if length:
    pos=out.tell()
    for i in range(at,at+length,1048576):out.write(new[i:min(i+1048576,at+length)])
    ops.append(dict(source='payload',part=0,offset=pos,length=length))
  last=0
  for name,(at,length)in sorted(nf.items(),key=lambda item:item[1][0]):
   data(last,at-last);digest=hashlib.sha256(memoryview(new)[at:at+length]).hexdigest();assert digest==sha(D/'XboxFiles'/name),name;meta[name]=dict(bytes=length,sha256=digest)
   if name in of and length==of[name][1]and digest==hashlib.sha256(memoryview(old)[of[name][0]:of[name][0]+length]).hexdigest():ops.append(dict(source='baseline',offset=of[name][0],length=length))
   else:data(at,length)
   last=at+length
  data(last,len(new)-last)
 m=dict(format=2,toVersion='1.11.1',targetBytes=target.stat().st_size,targetSHA256=sha(target),payload=[dict(name=payload.name,bytes=payload.stat().st_size,sha256=sha(payload),url=None)],baselines=[dict(version='1.10.0',bytes=base.stat().st_size,sha256=expected,operations=ops)],files=meta)
 assert sum(o['length']for o in ops)==m['targetBytes'];(P/'update.json').write_text(json.dumps(m,indent=2)+'\n')
 with zipfile.ZipFile(R.parent/'remote-originals/downloads/MyRO-1.10.0-Update.zip')as z:
  script=z.read('MyRO-1.10.0/Update-MyRO1.10.0.ps1').decode('utf-8-sig').replace('1.10.0','1.11.1').replace('1.9.3','1.10.0').replace('guild, companion and diagnostics checkpoint','GUI and preservation restoration')
  (P/'Update-MyRO1.11.1.ps1').write_text(script,encoding='utf-8-sig')
  for name in ['GPL-3.0.txt','MIT.txt','DejaVu-Font.txt','roBrowser-GPL-3.0.txt']:(P/name).write_bytes(z.read('MyRO-1.10.0/'+name))
 (P/'Apply-Update.cmd').write_bytes(b'@echo off\r\npowershell.exe -NoProfile -STA -ExecutionPolicy Bypass -File "%~dp0Update-MyRO1.11.1.ps1" %*\r\necho.\r\npause\r\n')
 notes=(R/'Preparation/Release-Notes1.11.1.txt').read_text();notes='\n'.join(line for line in notes.splitlines()if not line.startswith('DRAFT:'))+'\n';notes=notes.replace('Detailed normal checks, the two additional reviews and patch reconstruction\nresults belong in the accompanying report once complete.','Normal checks and both additional reviews passed. See the accompanying report\nfor patch validation and detailed evidence.');(P/'START-HERE.txt').write_text(notes.replace('Normal host/native integration checks and both subsequent review passes are\nrequired before this package is delivered. Detailed evidence accompanies it.','Normal host/native integration checks and both subsequent review passes\npassed. Detailed evidence accompanies this package.'))
 for name in ['Restoration-Normal-Checks270.json','Normal-Complete-Checks244.json','Restoration-Review-Pass1-271.json','Restoration-Review-Pass2-272.json','Release-Native-Checks275.json','Release-Source-Labels274.json']:
  q=P/'Verification'/name;q.parent.mkdir(exist_ok=True);shutil.copy2(V/name,q)
 for name in ['REGRESSION-LEDGER252.md','Restoration-Closure270.md']:
  shutil.copy2(R/'Preparation'/name,P/'Verification'/name)
 (D/'target-manifest275.json').write_text(json.dumps(m,indent=2)+'\n');target.unlink()
 print('PASS candidate payload and full target inventory generated; target ISO removed to leave room for actual updater reconstruction.')
