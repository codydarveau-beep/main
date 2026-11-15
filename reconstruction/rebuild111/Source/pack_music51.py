"""Extend streamed full-length music using the accepted mono 22.05 kHz decoder format."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import csv,hashlib,json,re,subprocess,zlib
from clearance51 import map_names51
ROOT=Path(__file__).resolve().parent.parent;SRC=ROOT/'Source';BASE=ROOT.parent/'test50c';LIB=ROOT.parent/'asset-library/Test51-world-maps'

def main():
 source=(BASE/'Source/music_data.h').read_text();oldnames=re.findall(r'"([^"]+)"',re.search(r'musicNames\[\]=\{(.*?)\}',source)[1]);assign={r['map']:r['virtual_path'].replace('\\','/').lower()for r in csv.DictReader((ROOT.parent/'asset-library/Test51-map-inventory/metadata/Music-Assignments.csv').open(encoding='utf-8-sig'))}
 names=map_names51();index=json.loads((LIB/'Asset-Index.json').read_text());tracks=list(oldnames)
 for n in names[18:]:
  path=assign.get(n,'');name=path.removeprefix('bgm/')
  if name and name not in tracks:assert path in index,path;tracks.append(name)
 out=ROOT/'MusicAssets51';out.mkdir(exist_ok=True)
 def encode(name):
  target=out/name
  if target.exists():return target.read_bytes()
  original=Path(index['bgm/'+name]['path'])
  subprocess.run(['ffmpeg','-v','error','-nostdin','-y','-threads','1','-i',str(original),'-vn','-map_metadata','-1','-ac','1','-ar','22050','-codec:a','libmp3lame','-b:a','48k','-write_xing','0','-id3v2_version','0',str(target)],check=True)
  raw=target.read_bytes();assert 0<len(raw)<=2*1024*1024,(name,len(raw));return raw
 oldpack=(BASE/'Music/music.bin').read_bytes();records=json.loads((BASE/'Source/music_pack50.json').read_text())['tracks'];newrecords=[];temp=ROOT/'Music/music.pending'
 with temp.open('wb')as stream:
  stream.write(oldpack);newrecords.extend(records)
  with ThreadPoolExecutor(max_workers=4)as pool:
   for i,(name,raw)in enumerate(zip(tracks[10:],pool.map(encode,tracks[10:])),10):
    newrecords.append(dict(track=i,offset=stream.tell(),bytes=len(raw),crc=zlib.crc32(raw),sha256=hashlib.sha256(raw).hexdigest()));stream.write(raw);print(i,name,len(raw),flush=True)
  size=stream.tell()
 temp.replace(ROOT/'Music/music.bin')
 h='/* Full-length music. Only current and incoming encoded tracks are resident. */\n#ifndef MYRO_MUSIC_PACK50_H\n#define MYRO_MUSIC_PACK50_H\n#define MUSIC_FILE_BYTES50 %du\ntypedef struct {unsigned offset,bytes,crc;} MusicBlob50;\nstatic const MusicBlob50 musicBlobs50[%d]={\n'%(size,len(tracks))
 h+=''.join('{%du,%du,0x%08xu},\n'%(r['offset'],r['bytes'],r['crc'])for r in newrecords)+'};\n#endif\n';(SRC/'music_pack50.h').write_text(h)
 oldmaps=list(map(int,re.search(r'musicMapTracks\[\]=\{(.*?)\}',source)[1].split(',')));mapping=oldmaps+[tracks.index(assign[n].removeprefix('bgm/'))if assign.get(n)else -1 for n in names[18:]]
 h='#define MUSIC_TRACKS %d\n#define MUSIC_MAP_COUNT49 %d\n#ifndef MYRO_MUSIC_DISC50\n#define MYRO_MUSIC_DISC50 1\n#endif\n#include "music_pack50.h"\nstatic const unsigned char*musicData[MUSIC_TRACKS];\nstatic unsigned musicSizes[MUSIC_TRACKS];\n'%(len(tracks),len(names))
 h+='static const char*musicNames[]={'+','.join(json.dumps(n)for n in tracks)+'};\nstatic const int musicMapTracks[]={'+','.join(map(str,mapping))+'};\nstatic int music_map_track49(unsigned map){return map<MUSIC_MAP_COUNT49?musicMapTracks[map]:-1;}\nstatic void music_blob_init(void){for(int i=0;i<MUSIC_TRACKS;i++)musicSizes[i]=musicBlobs50[i].bytes;}\n#include "music_disc50.h"\n';(SRC/'music_data.h').write_text(h)
 (ROOT/'MUSIC-PACK51.json').write_text(json.dumps(dict(tracks=tracks,records=newrecords,maps=dict(zip(names,mapping)),bytes=size,preserved_prefix_bytes=len(oldpack)),indent=2));print('PASS',len(tracks),'tracks',len(names),'maps',size,'bytes')
if __name__=='__main__':main()
