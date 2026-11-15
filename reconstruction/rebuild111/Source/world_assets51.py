"""Read-only, bounded cache over the verified Test51 asset index."""
from collections import OrderedDict
from collections.abc import Mapping
from pathlib import Path
import json

class WorldAssets51(Mapping):
 def __init__(self,index,cache_bytes=32*1024*1024):
  self.index=json.loads(Path(index).read_text()); self.limit=cache_bytes
  self.cache=OrderedDict(); self.resident=0; self.read_bytes=0
 @staticmethod
 def key(key):return key.replace(chr(92),'/').lower()
 def __len__(self):return len(self.index)
 def __iter__(self):return iter(self.index)
 def __contains__(self,key):return self.key(key) in self.index
 def __getitem__(self,key):
  key=self.key(key)
  if key in self.cache:
   value=self.cache.pop(key);self.cache[key]=value;return value
  row=self.index[key];value=Path(row['path']).read_bytes()
  if len(value)!=row['bytes']:raise ValueError('Verified asset size changed: '+key)
  self.read_bytes+=len(value)
  if len(value)<=self.limit:
   while self.cache and self.resident+len(value)>self.limit:
    _,old=self.cache.popitem(last=False);self.resident-=len(old)
   self.cache[key]=value;self.resident+=len(value)
  return value
