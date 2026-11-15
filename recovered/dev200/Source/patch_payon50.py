"""MIT. Restore the source-walkable interior of Payon's south gateway.

The solid-section bake cut the raised gate lintel at body height and sealed
five of its six walkable interior columns. Keep its source-blocked posts,
terrain heights, scenery, portal and all other collision bytes unchanged.
"""
from pathlib import Path
import hashlib,json,re,struct,zlib
r=Path(__file__).resolve().parent
p=r.parent/'Packed/world.bin'
h=r/'world_data.h'
s=h.read_text();a=s.index('static const WorldBlob worldBlobs');b=s.index('static const WorldBlob minimapBlobs45',a)
rows=[list(map(int,v)) for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',s[a:b])]
old=p.read_bytes();offset,size,raw,crc=rows[11*7+1]
part=old[offset:offset+size];assert zlib.crc32(part)==crc
data=zlib.decompress(part);assert len(data)==raw
w,ht=struct.unpack_from('<II',data);assert (w,ht)==(300,360)
n=struct.unpack_from('<I',data,8+w*ht)[0];pos=12+w*ht+n*12
count=struct.unpack_from('<I',data,pos)[0]
cells=[struct.unpack_from('<IHH',data,pos+4+i*8) for i in range(count)]
opening={42*w+x for x in range(119,125)}
assert all(data[8+k] for k in opening)
keep=[v for v in cells if v[0] not in opening]
if len(keep)==len(cells):
    print('Payon south gateway source opening already restored.')
else:
    patched=data[:pos]+struct.pack('<I',len(keep))+b''.join(struct.pack('<IHH',*v) for v in keep)
    compressed=zlib.compress(patched,9);rows[11*7+1]=[len(old),len(compressed),len(patched),zlib.crc32(compressed)]
    new=old+compressed;p.write_bytes(new)
    block='static const WorldBlob worldBlobs[18][7]={\n'+',\n'.join('{'+','.join('{'+','.join(map(str,v))+'}' for v in rows[k*7:k*7+7])+'}' for k in range(18))+'};\n'
    s=s[:a]+block+s[b:];s=re.sub(r'WORLD_FILE_BYTES \d+','WORLD_FILE_BYTES '+str(len(new)),s);h.write_text(s)
    (r/'payon_gateway50.json').write_text(json.dumps(dict(map='payon',removed_false_solid_cells=[list(v) for v in cells if v[0] in opening],walkable_opening=[[x,42] for x in range(119,125)],source_walk_and_posts_unchanged=True,previous_sha256=hashlib.sha256(old).hexdigest(),sha256=hashlib.sha256(new).hexdigest()),indent=2)+'\n')
    print('Restored six source-walkable gateway columns; removed',len(cells)-len(keep),'false lintel collisions.')
