"""Recover original arcade native assembly with explicit relocation boundaries.
No runtime instruction emulator is introduced into the Xbox game.
"""
from pathlib import Path
import json,re,struct,subprocess,os
R=Path(__file__).resolve().parent.parent;d=json.loads((R/'Preparation/Arcade-Control-Flow197.json').read_text());x=(R.parent/'packet194/released-default.xbe').read_bytes();out=['/* Recovered original 1.10.0 arcade logic. Generated; edit relocation generator. */','.intel_syntax noprefix','.text']
state='_arcade197_state';constant='.Larcade_constants197'
def symbol(v):
 if 0xd478f0<=v<0xd47ffc:return state+(' + %d'%(v-0xd478f0)if v!=0xd478f0 else'')
 if 0x749e00<=v<0x74b000:return constant+(' + %d'%(v-0x749e00)if v!=0x749e00 else'')
 if v in [0x1c00f4,0x1c1e98]:return '.Ltable%x'%v
 return None
for name in ['input','tick']:
 out+=['.globl _arcade197_'+name,'_arcade197_'+name+':','push ebp','push ebx','push esi','push edi','mov eax, esp','and esp, -16','sub esp, 0x1800','mov dword ptr [esp + 0x17f0], eax']
 if name=='input':out+=['mov ecx, dword ptr [eax + 20]','mov dword ptr [esp + 0x50], ecx']
 else:out+=['mov ecx, dword ptr [eax + 20]','mov dword ptr [esp + 0x254], ecx','xorps xmm0, xmm0','movaps xmmword ptr [esp + 0xb0], xmm0','mov ecx, dword ptr [eax + 24]','mov dword ptr [esp + 0xb0], ecx']
 out+=['jmp .L%x'%d[name]['start']]
 out+=['.Larcade_'+name+'_done:','mov esp, dword ptr [esp + 0x17f0]','pop edi','pop esi','pop ebx','pop ebp','ret']
out+=['.globl _arcade197_reset','_arcade197_reset:','mov ecx, dword ptr [esp + 4]','mov edx, dword ptr [esp + 8]','jmp .Lcc5a0']
seen=set();tables={}
for name,r in d.items():
 stops={v:'.Larcade_'+name+'_done'for v in r['stops']};tables.update(r['tables']);instructions=r['instructions']
 for i in instructions:
  at=i['address'];assert at not in seen;seen.add(at);mn=i['mnemonic'];operand=i['operands'];out.append('.L%x:'%at)
  if mn.startswith('j')or mn=='call':
   if re.fullmatch(r'0x[0-9a-f]+',operand):target=int(operand,16);operand=stops.get(target,'.L%x'%target)
   else:
    for text in re.findall(r'0x[0-9a-f]+',operand):
     sym=symbol(int(text,16))
     if sym:operand=operand.replace(text,sym)
  else:
   for text in re.findall(r'0x[0-9a-f]+',operand):
    sym=symbol(int(text,16))
    if sym:
     pos=operand.index(text);inmemory=operand[:pos].count('[')>operand[:pos].count(']');operand=operand.replace(text,sym if inmemory else'offset '+sym)
  if mn=='push'and operand.startswith('offset '):out.extend(['.byte 0x68','.long '+operand[7:]])
  else:out.append(mn+' '+operand)
  successor=at+len(bytes.fromhex(i['bytes']))
  if successor in stops and not(mn=='jmp'or mn.startswith('ret')):out.append('jmp '+stops[successor])
# Every direct call/branch target must be in the extracted graph or wrappers.
for r in d.values():
 for call in r['calls']:assert call in seen,hex(call)
out+=['.p2align 4',constant+':']
p=x[0x749e00-0x10000:0x74b000-0x10000]
for i in range(0,len(p),16):out.append('.byte '+','.join(str(v)for v in p[i:i+16]))
for key,targets in tables.items():out+=['.p2align 2','.Ltable%x:'%int(key,16),'.long '+','.join('.L%x'%v for v in targets)]
out+=['.bss','.p2align 4','.space 16','.globl '+state,state+':','.space 1804','.space 16']
assembly='\n'.join(out)+'\n'
# COFF SafeSEH declaration, as used by nxdk's own assembly routines. No handlers.
coff='.def @feat.00; .scl 3; .type 0; .endef\n.globl @feat.00\n.set @feat.00, 1\n'
(R/'Source/arcade_recovered197.s').write_text(coff+assembly)
(R/'Validation/arcade_recovered197-host.s').write_text(assembly)
# A small ELF build runs the SAME source in the host CPU reference harness.
root=Path('/workspace/myro/toolchain/xbox-toolchain/usr/lib/llvm-18/bin');env=os.environ.copy();env['LD_LIBRARY_PATH']='/workspace/myro/toolchain/xbox-toolchain/usr/lib/x86_64-linux-gnu'
subprocess.run([str(root/'clang'),'-target','i386-unknown-linux-gnu','-c',str(R/'Validation/arcade_recovered197-host.s'),'-o',str(R/'Validation/arcade_recovered197.o')],env=env,check=True)
subprocess.run([str(root/'ld.lld'),'-m','elf_i386','-Ttext=0x10000000','--entry=_arcade197_reset',str(R/'Validation/arcade_recovered197.o'),'-o',str(R/'Validation/arcade_recovered197.elf')],env=env,check=True)
print('Recovered complete original input, reset and six-game update logic as relocatable native assembly; no runtime emulator.')

# Regenerate host entry points from the linked image, not assumed offsets.
symbols=subprocess.check_output([str(root/'llvm-nm'),str(R/'Validation/arcade_recovered197.elf')],env=env,text=True)
lines=['#define ARCADE_HOST_ELF197 '+json.dumps(str(R/'Validation/arcade_recovered197.elf'))]
for name in ['input','tick','reset','state']:
 match=re.search(r'^([0-9a-f]+) [A-Za-z] _arcade197_'+name+r'$',symbols,re.M);assert match,name
 lines.append('#define HOST_ARCADE197_'+name.upper()+' 0x'+match[1]+'u')
(R/'Validation/arcade_host_symbols197.h').write_text('\n'.join(lines)+'\n')
