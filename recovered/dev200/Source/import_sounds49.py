"""MIT. Retain frozen48 PCM bank, append returned original classic sounds.
Offline FFmpeg resampling to the existing native integer 48kHz mono PCM16 mixer.
"""
from pathlib import Path
import subprocess,struct,re,json,hashlib
from asset_index49 import paths
r=Path(__file__).resolve().parent
names=['ef_soulstrike','ef_glasswall','kyrie_guard','ef_napalmbeat','wizard_waterball_chulung','wizard_meteor','ef_beginspell','매직 크래쉬']
s=(r.parent.parent/'test48/Source/sound_assets.c').read_text();body=s[:s.index('const short*soundData')];ptrs=s.split('const short*soundData[]={')[1].split('};')[0].split(',');lengths=list(map(int,s.split('const unsigned soundLengths[]={')[1].split('};')[0].split(',')));assert len(ptrs)==len(lengths)==52
report=[]
for name in names:
 p=paths['data\\wav\\effect\\'+name+'.wav'];raw=subprocess.check_output(['ffmpeg','-v','error','-i',str(p),'-f','s16le','-ac','1','-ar','48000','-']);assert len(raw)%2==0
 samples=struct.unpack('<%dh'%(len(raw)//2),raw);assert samples and max(samples)>0
 symbol='classic49_'+(name if name.isascii()else'stave_crasher');body+='const short '+symbol+'[]={'+','.join(map(str,samples))+'};\n';ptrs.append(symbol);lengths.append(len(samples));report.append(dict(id=len(ptrs)-1,name=name,samples=len(samples),sourceSha256=hashlib.sha256(p.read_bytes()).hexdigest(),pcmSha256=hashlib.sha256(raw).hexdigest()))
body+='const short*soundData[]={'+','.join(ptrs)+'};\nconst unsigned soundLengths[]={'+','.join(map(str,lengths))+'};\n';(r/'sound_assets.c').write_text(body);(r/'sounds49.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS preserved52 original sound slots; appended8 original clips',sum(lengths[52:])*2,'PCM bytes')
