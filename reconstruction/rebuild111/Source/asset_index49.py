# MIT. Read-only index of local collector payloads and extracted client trees.
from pathlib import Path
import csv
lib=Path(__file__).resolve().parent.parent.parent/'asset-library';paths={}
for root in lib.iterdir():
 if not root.is_dir():continue
 for p in (root/'data').rglob('*'):
  if p.is_file():paths[str(p.relative_to(root)).replace('/','\\').lower()]=p
 table=root/'Assets.csv'
 if table.exists():
  for row in csv.DictReader(table.open(encoding='utf-8-sig')):
   p=root/row.get('payload','');key=row.get('virtual_path','').replace('\\\\','\\').lower()
   if p.is_file()and key.startswith('data\\'):paths[key]=p
