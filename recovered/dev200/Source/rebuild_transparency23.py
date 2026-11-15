"""MIT. Rebuild cutout atlases only; verify unchanged model UVs.
Usage: python rebuild_transparency23.py expansion-collection.zip
"""
from pathlib import Path
import sys,re,zlib,struct,json
sys.path.insert(0,str(Path(__file__).resolve().parent));import convert_scenery
r=Path(__file__).resolve().parent.parent;src=r/'Source';s=(src/'world_data.h').read_text();blobs=[(int(x[0]),int(x[1]),int(x[2]),int(x[3],16)) for x in re.findall(r'\{(\d+),(\d+),(\d+),0x([0-9a-f]+)u\}',s.split('worldBlobs')[1].split('mapLabels')[0])];assert len(blobs)==49
old=(r/'Packed/world.bin').read_bytes();new=bytearray();newblobs=[];report=[]
for m,name in enumerate(['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09']):
 out=r/'TransparencyAssets'/name;out.mkdir(parents=True,exist_ok=True);(out/'Source').mkdir(exist_ok=True)
 convert_scenery.convert([sys.argv[1]],out,[name],128)
 raw=(out/'SceneryAssets/atlas.bin').read_bytes()
 for j in range(7):
  off,n,rawlen,crc=blobs[m*7+j];packed=old[off:off+n];assert zlib.crc32(packed)==crc
  if j==4:
   before=zlib.decompress(packed);assert len(raw)==len(before);assert raw[:8]==before[:8]
   # Packing/layout must be identical: mesh and instance generation unchanged.
   # Match original mesh exactly before reusing its UVs with the new atlas.
   om=(out/'SceneryAssets/mesh.bin').read_bytes();o,nm,rm,cm=blobs[m*7+5];assert om==zlib.decompress(old[o:o+nm]),name+' mesh differs'
   packed=zlib.compress(raw,9);report.append(dict(map=name,changed_bytes=sum(a!=b for a,b in zip(raw,before)),old_packed=n,new_packed=len(packed)))
  newblobs.append((len(new),len(packed),rawlen,zlib.crc32(packed)));new+=packed
it=iter(newblobs);a=s.index('static const WorldBlob worldBlobs');b=s.index('static const char*mapLabels');s=s[:a]+re.sub(r'\{\d+,\d+,\d+,0x[0-9a-f]+u\}',lambda m:'{'+','.join(map(str,next(it)))+'}',s[a:b])+s[b:];s=re.sub(r'#define WORLD_FILE_BYTES \d+','#define WORLD_FILE_BYTES '+str(len(new)),s);(src/'world_data.h').write_text(s);(r/'Packed/world.bin').write_bytes(new);(r/'TRANSPARENCY-CONVERSION-REPORT.json').write_text(json.dumps(report,indent=2));print(report)
