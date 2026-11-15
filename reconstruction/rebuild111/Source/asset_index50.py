# MIT. Canonical read-only index of verified local collector assets.
from pathlib import Path
import re
from asset_index49 import paths as previous
def key50(s):return re.sub(r'\\+',r'\\',s.replace('/','\\')).lower()
paths={key50(k):p for k,p in previous.items()}
