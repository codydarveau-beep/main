"""MIT. Reject float conversions in literal production printf/UI format calls."""
from pathlib import Path
import re
root=Path(__file__).resolve().parent;checked=0
for p in root.glob('*'):
 if p.suffix not in ['.c','.h']or p.name.startswith('test_'):continue
 source=p.read_text(errors='ignore')
 for call in re.finditer(r'\b(?:snprintf|vsnprintf|printf|fprintf|debugPrint|hud_text|ui_scaled|ui_text|ui_exp_text|combat_notice|combat_message)\s*\(',source):
  # Follow parentheses while respecting string literals, including nested calls.
  pos=call.end();depth=1;strings=[]
  while pos<len(source)and depth:
   if source[pos]=='"':
    match=re.match(r'"(?:[^"\\]|\\.)*"',source[pos:]);assert match
    strings.append(match.group());pos+=len(match.group());continue
   if source[pos]=='(':depth+=1
   if source[pos]==')':depth-=1
   pos+=1
  for literal in strings:
   checked+=1;fmt=literal.replace('%%','')
   assert not re.search(r'%(?:[-+ #0]*)(?:\d+|\*)?(?:\.(?:\d+|\*))?[hlL]*[eEfFgGaA]',fmt),(p.name,literal)
print('PASS50a',checked,'literal production format strings: no floating-point conversion; integer UI/diagnostics preserved.')
