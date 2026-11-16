"""Preserve the exact released registry and append empty campaign map spans."""
from pathlib import Path
import re,json,hashlib
R=Path(__file__).resolve().parent.parent

def extend():
 p=R/'Source/npc_registry_data55.h';s=p.read_text();m=re.search(r'(npcMapSpans55\[\]=\{)(.*?)(\};)',s,re.S);assert m
 rows=[tuple(map(int,r))for r in re.findall(r'\{(\d+)u?,(\d+)u?\}',m[2])];assert len(rows)in[495,497]
 original=(R.parent/'packet194/RecoveredMetadata/npc_registry_data55.h').read_text();om=re.search(r'npcMapSpans55\[\]=\{(.*?)\};',original,re.S);baseline=[tuple(map(int,r))for r in re.findall(r'\{(\d+)u?,(\d+)u?\}',om[1])];assert len(baseline)==495
 prior=rows[:495];prefixSHA256=hashlib.sha256(json.dumps(prior).encode()).hexdigest();existingRelocationDifferences=sum(a!=b for a,b in zip(prior,baseline))
 end=sum(baseline[-1]);expected=[(end,0),(end,0)]
 if len(rows)==495:
  body=m[2].rstrip().rstrip(',')+','+','.join('{%du,%du}'%r for r in expected)
  s=s[:m.start(2)]+body+s[m.end(2):];p.write_text(s)
 else:assert rows[495:]==expected
 updated=re.search(r'npcMapSpans55\[\]=\{(.*?)\};',p.read_text(),re.S);assert [tuple(map(int,r))for r in re.findall(r'\{(\d+)u?,(\d+)u?\}',updated[1])]==prior+expected
 (R/'Validation/Alias-NPC-Registry242.json').write_text(json.dumps(dict(passed=True,existingSpansPreserved=495,existingSpanSHA256=prefixSHA256,preexistingRelocationSpanDifferences=existingRelocationDifferences,aliasSpans=[dict(map=495,start=end,count=0),dict(map=496,start=end,count=0)],scope='Append two empty spans only. No records/programs/spawn scripts are copied from source environment maps; existing career-safe relocation registry prefix stays exact.',sourceSHA256=hashlib.sha256(p.read_bytes()).hexdigest()),indent=2)+'\n')
if __name__=='__main__':extend();print('Preserved current NPC registry and appended empty campaign alias map spans.')
