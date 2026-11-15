# SPDX-License-Identifier: MIT. Compact full-length mono music from supplied RO assets.
from pathlib import Path
import zipfile,csv,io,hashlib,re,json,subprocess,sys
root=Path(__file__).resolve().parent.parent;out=root/'MusicAssets';out.mkdir(exist_ok=True)
z=zipfile.ZipFile(sys.argv[1]);rows={r['virtual_path'].lower():r for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig')))}
def read(k):
 r=rows[k];b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];return b
mapping=read('data\\mp3nametable.txt').decode('cp949',errors='replace');maps=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09'];tracks=['04','05','08','12','26'];maptracks=[];report={'encoding':'Full-length MP3, 48 kbps mono / 22050 Hz; bounded frame decoder','tracks':[],'maps':{}}
for m in maps:
 match=re.search(r'^'+m+r'\.rsw#bgm\\+([0-9]+)\.mp3#',mapping,re.M);assert match
 maptracks.append(tracks.index(match[1]));report['maps'][m]=match[1]+'.mp3'
blobs=[]
for tr in tracks:
 original=out/(tr+'-source.mp3');target=out/(tr+'.mp3');original.write_bytes(read('bgm\\'+tr+'.mp3'))
 subprocess.run(['ffmpeg','-v','error','-y','-i',str(original),'-vn','-map_metadata','-1','-ac','1','-ar','22050','-codec:a','libmp3lame','-b:a','48k','-write_xing','0','-id3v2_version','0',str(target)],check=True)
 b=target.read_bytes();blobs.append(b);report['tracks'].append({'source':tr+'.mp3','source_sha256':hashlib.sha256(original.read_bytes()).hexdigest(),'encoded_bytes':len(b),'encoded_sha256':hashlib.sha256(b).hexdigest()})
with (root/'Source/music_assets.c').open('w') as f:
 f.write('/* User-supplied full music tracks; original ownership retained. */\n')
 for i,b in enumerate(blobs):
  f.write(f'const unsigned music{i}_size={len(b)};\nconst unsigned char music{i}[]={{\n')
  for at in range(0,len(b),32):f.write(','.join(map(str,b[at:at+32]))+',\n')
  f.write('};\n')
with (root/'Source/music_data.h').open('w') as f:
 f.write('/* SPDX-License-Identifier: MIT. Source music table mappings. */\n#define MUSIC_TRACKS 5\n')
 for i in range(5):f.write(f'extern const unsigned char music{i}[];extern const unsigned music{i}_size;\n')
 f.write('static const unsigned char*musicData[]={'+','.join('music'+str(i) for i in range(5))+'};\nstatic unsigned musicSizes[5];\nstatic const char*musicNames[]={'+','.join(json.dumps(t+'.mp3') for t in tracks)+'};\nstatic const unsigned musicMapTracks[]={'+','.join(map(str,maptracks))+'};\nstatic void music_blob_init(void){\n')
 for i in range(5):f.write(f'musicSizes[{i}]=music{i}_size;\n')
 f.write('}\n')
report['encoded_total_bytes']=sum(map(len,blobs));(root/'MUSIC-CONVERSION-REPORT.json').write_text(json.dumps(report,indent=2));print(report['encoded_total_bytes'],'music bytes')
