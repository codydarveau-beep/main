"""Restore the deployed guild-only alias to its original map assets."""
from pathlib import Path
import re,struct,json,hashlib
R=Path(__file__).resolve().parent.parent;S=R/'Source';p=S/'world_data.h';s=p.read_text();a=s.index('static const WorldBlob worldBlobs[WORLD_MAP_COUNT][7]=');b=s.index(';',a);old=s[a:b];v=[tuple(map(int,r))for r in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',old)];rows=[sum((list(t)for t in v[i:i+7]),[])for i in range(0,len(v),7)];assert len(rows)in[494,495]
x=(R.parent/'packet194/released-default.xbe').read_bytes();needle=struct.pack('<56I',*rows[0],*rows[1]);at=x.find(needle);assert at>=0 and x.find(needle,at+1)<0;released=[list(struct.unpack_from('<28I',x,at+i*112))for i in range(495)];assert rows[:494]==released[:494] and released[494]==released[451]
new='static const WorldBlob worldBlobs[WORLD_MAP_COUNT][7]={\n'+''.join('{'+','.join('{'+','.join(map(str,r[j:j+4]))+'}'for j in range(0,28,4))+'},\n'for r in released)+'}';p.write_text(s[:a]+new+s[b:])
(R/'Preparation/Guild-Map-Recovery197.json').write_text(json.dumps(dict(releasedTableFileOffset=at,originalMapCount=494,guildMap=494,sourceGeometryAlias=451,sourceMapName='z_agit',onlineContent=False,sourceGeometryOnly=True,allOriginalRowsPreserved=True,aliasRowMatchesReleased=True,tableSHA256=hashlib.sha256(struct.pack('<%dI'%(495*28),*[w for r in released for w in r])).hexdigest()),indent=2)+'\n')
# Exact retained door/room rules, without pretending missing prop generator is supplied.
s=(R/'Retained196/guild_layout194.partial.h').read_text();(S/'guild_layout194.h').write_text('/* Retained doors and room predicates; source geometry alias independently recovered. */\n#ifndef MYRO_GUILD_LAYOUT194_H\n#define MYRO_GUILD_LAYOUT194_H\n#define GUILD_MAP194 494u\n'+s+'\n#endif\n')
