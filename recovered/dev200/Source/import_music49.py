"""MIT. Extend original five music slots with collected18-map source assignments.
Full-length original MP3s, same existing mono48kbps/22050Hz conversion; no aliases.
"""
from pathlib import Path
import re,json,subprocess,hashlib
from asset_index49 import paths
r=Path(__file__).resolve().parent;base=r.parent.parent/'test48/Source';table=paths['data\\mp3nametable.txt'].read_text(encoding='cp949');maps=re.search(r'mapNames\[\]=\{(.*?)\};',(r/'world_data.h').read_text()).group(1);maps=re.findall(r'"([^"]+)"',maps);tracks=['04','05','08','12','26'];assign=[]
old_assign=[3,3,2,4,3,1,0]
for map_index,name in enumerate(maps):
 if map_index<7:
  assign.append(old_assign[map_index]);continue
 m=re.search(r'^'+name+r'\.rsw#bgm\\+([0-9]+)\.mp3#',table,re.M);assert m,name
 tr=m[1]
 if tr not in tracks:tracks.append(tr)
 assign.append(tracks.index(tr))
parts=[(base/'music_assets.c').read_text()];report=[];out=r.parent/'MusicAssets';out.mkdir(exist_ok=True)
for i,tr in enumerate(tracks[5:],5):
 src=r.parent.parent/'asset-library/Payon43-return/bgm'/(tr+'.mp3');assert src.exists(),src;target=out/(tr+'.mp3')
 subprocess.run(['ffmpeg','-v','error','-y','-i',str(src),'-vn','-map_metadata','-1','-ac','1','-ar','22050','-codec:a','libmp3lame','-b:a','48k','-write_xing','0','-id3v2_version','0',str(target)],check=True)
 b=target.read_bytes();parts.append('const unsigned music%d_size=%d;\nconst unsigned char music%d[]={\n'%(i,len(b),i))
 parts.append(''.join(','.join(map(str,b[at:at+32]))+',\n' for at in range(0,len(b),32)))
 parts.append('};\n');report.append(dict(track=tr+'.mp3',bytes=len(b),sourceSha256=hashlib.sha256(src.read_bytes()).hexdigest(),encodedSha256=hashlib.sha256(b).hexdigest()))
(r/'music_assets.c').write_text(''.join(parts));n=len(tracks);h='/* MIT. Source mp3nametable18-map assignments; original slots0..4 retained. */\n#define MUSIC_TRACKS %d\n#define MUSIC_MAP_COUNT49 %d\n'%(n,len(maps))
for i in range(n):h+='extern const unsigned char music%d[];extern const unsigned music%d_size;\n'%(i,i)
h+='static const unsigned char*musicData[]={'+','.join('music'+str(i)for i in range(n))+'};\nstatic unsigned musicSizes[MUSIC_TRACKS];\nstatic const char*musicNames[]={'+','.join(json.dumps(t+'.mp3')for t in tracks)+'};\nstatic const unsigned musicMapTracks[]={'+','.join(map(str,assign))+'};\nstatic int music_map_track49(unsigned map){return map<MUSIC_MAP_COUNT49?(int)musicMapTracks[map]:-1;}\nstatic void music_blob_init(void){\n'
for i in range(n):h+='musicSizes[%d]=music%d_size;\n'%(i,i)
h+='}\n';(r/'music_data.h').write_text(h);(r/'music49.json').write_text(json.dumps(dict(maps={name:tracks[track]+'.mp3' for name,track in zip(maps,assign)},added=report),indent=2)+'\n');print('PASS18 source map assignments',json.dumps({name:tracks[track]for name,track in zip(maps,assign)}),'added',sum(x['bytes']for x in report),'encoded bytes')
