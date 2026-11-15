"""Copy source and text evidence only; never publish private native binaries/assets."""
from pathlib import Path
import shutil,hashlib,json
r=Path(__file__).resolve().parent.parent;dest=r.parent/'checkpoint/reconstruction/rebuild111';files=[]
for folder in ['Source','Preparation','Validation','Recovered195','Retained196','Guild/Directional197']:
 for p in sorted((r/folder).rglob('*')):
  if not p.is_file() or p.is_symlink() or '__pycache__' in p.parts or 'tmp' in p.relative_to(r).parts:continue
  if folder=='Source' and p.suffix in ['.obj','.o','.exe','.su','.d','.pyc']:continue
  if folder=='Validation' and p.suffix not in ['.log','.json','.h','.inc','.c']:continue
  if folder=='Preparation' and p.suffix not in ['.py','.json','.md']:continue
  if folder=='Guild/Directional197' and p.suffix not in ['.png','.bin','.json','.md']:continue
  if folder=='Retained196' and p.suffix not in ['.json','.h','.c','.txt','.md']:continue
  if folder=='Recovered195' and p.suffix not in ['.json','.h']:continue
  if p.stat().st_size>90_000_000:raise ValueError(p)
  files.append(p)
files.extend([r/'STATUS.md',r/'RELEASE-GATES.md',r/'WORK-REMAINING.md'])
manifest=[]
for p in files:
 rel=p.relative_to(r);target=dest/rel;target.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,target);data=p.read_bytes();manifest.append(dict(path=str(rel),bytes=len(data),sha256=hashlib.sha256(data).hexdigest()))
(dest/'source-manifest194.json').write_text(json.dumps(dict(status='Partial-source reconstruction, private native compilation passed; not release ready',files=manifest),indent=2)+'\n')
print(len(manifest),'source/report artifacts copied; binaries/assets excluded')
