"""MIT. Check compiler-reported autosave stack against actual PE/XBE reserves.
Conservatively sum emitted save frames even when an optimizer inlines a call;
reserve another32KiB for kernel/library calls and non-save work below main.
This is a budget guard, not an exhaustive dynamic stack/high-water measurement.
"""
from pathlib import Path
import struct,json
r=Path(__file__).resolve().parent
usage={}
for line in (r/'main.su').read_text().splitlines():
 location,size,kind=line.split('\t');name=location.rsplit(':',1)[-1]
 assert kind=='static',('unbounded compiler stack usage',line)
 usage[name]=int(size)
pe=(r/'main.exe').read_bytes();peoff=struct.unpack_from('<I',pe,0x3c)[0];assert pe[peoff:peoff+4]==b'PE\0\0'
reserve=struct.unpack_from('<I',pe,peoff+24+72)[0]
xbe=(r.parent/'XboxFiles/default.xbe').read_bytes();assert xbe[:4]==b'XBEH';assert struct.unpack_from('<I',xbe,0x130)[0]==reserve
chains=[['main','save_commit','save_scan','save_decode','save_valid'],['main','save_load','save_scan','save_decode','save_valid'],['main','mp3dec_decode_frame']]
margin=32768;report=[]
for chain in chains:
 frames={n:usage[n]for n in chain};total=sum(frames.values());assert total+margin<=reserve,('Xbox stack budget exceeded',frames,total,margin,reserve)
 report.append(dict(frames=frames,bytes=total,margin=margin))
assert reserve==131072,('Expected128KiB stack reserve',reserve)
result=dict(stackReserve=reserve,chains=report,scope='Conservative known save/load/decode nesting plus32KiB margin; not a hardware high-water measurement')
(r/'stack_budget50a.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS50a actual PE/XBE stack reserve',reserve,'bytes; conservative autosave nesting',report[0]['bytes'],'bytes +',margin,'bytes margin fits.')
