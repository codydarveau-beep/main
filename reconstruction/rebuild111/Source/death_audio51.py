"""Original available death cues, PCM kept on disc until requested."""
from pathlib import Path
import json,io,wave,audioop,hashlib,zlib
from world_assets51 import WorldAssets51
R=Path(__file__).resolve().parent;ROOT=R.parent;a=WorldAssets51(ROOT.parent/'asset-library/Test51-world-maps/Asset-Index.json',1048576);cat=json.loads((ROOT/'CATALOG51.json').read_text());reports={r['prefix']:r for r in json.loads((ROOT/'ENEMY-ART51.json').read_text())};out=ROOT/'CreatureAudio51';out.mkdir(exist_ok=True);rows=[]
for id in cat['ids'][50:]:
 stem=cat['requests'][str(id)];candidates=reports.get(stem,{}).get('death_sounds',[]);chosen=None
 for name in candidates:
  path='data/wav/'+name.replace('\\','/').lower()
  if not path.endswith('.wav'):path+='.wav'
  if path in a:chosen=path;break
 if not chosen:rows.append(None);continue
 key=hashlib.sha256(chosen.encode()).hexdigest()[:16];target=out/(key+'.z')
 if not target.exists():
  try:
   with wave.open(io.BytesIO(a[chosen]),'rb')as w:raw=w.readframes(w.getnframes());width=w.getsampwidth();channels=w.getnchannels();rate=w.getframerate()
   if width==1:raw=audioop.bias(raw,1,-128)
   if channels==2:raw=audioop.tomono(raw,width,.5,.5)
   if width!=2:raw=audioop.lin2lin(raw,width,2)
   raw=audioop.ratecv(raw,2,1,rate,48000,None)[0];raw=audioop.mul(raw,2,.35);assert len(raw)<=1048576
   cp=zlib.compress(raw,6);target.write_bytes(cp);(out/(key+'.json')).write_text(json.dumps(dict(path=chosen,raw=len(raw),packed=len(cp),crc=zlib.crc32(cp))))
  except(wave.Error,EOFError)as e:print('Invalid optional source cue',chosen,str(e));rows.append(None);continue
 rows.append(dict(json.loads((out/(key+'.json')).read_text()),key=key))
(ROOT/'DEATH-AUDIO51.json').write_text(json.dumps(rows,indent=2));print('PASS',sum(r is not None for r in rows),'available source cues /',len(rows))
