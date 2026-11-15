"""Private native artifact guards; no execution or hardware memory claim."""
from pathlib import Path
import struct,json,hashlib,subprocess,os,re,tempfile
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
u={}
for line in (S/'main.su').read_text().splitlines():
 loc,size,kind=line.split('\t');assert kind=='static',line;u[loc.rsplit(':',1)[-1]]=int(size)
pe=(S/'main.exe').read_bytes();p=struct.unpack_from('<I',pe,60)[0];assert pe[p:p+4]==b'PE\0\0'
reserve=struct.unpack_from('<I',pe,p+24+72)[0];xbe=(R/'XboxFiles/default.xbe').read_bytes();assert xbe[:4]==b'XBEH';assert struct.unpack_from('<I',xbe,0x130)[0]==reserve==0x28000
base=struct.unpack_from('<I',xbe,0x104)[0];cert=struct.unpack_from('<I',xbe,0x118)[0]-base;title=xbe[cert+12:cert+92].decode('utf-16le').split('\0')[0];assert title=='MyRO v1.11.0 RECOVERY',title
# Missing emitted functions have been inlined into callers, not silently ignored.
chains=[['main','save_commit','save_scan','save_decode','save_valid'],['main','mp3dec_decode_frame'],['main','npc_player_command55','npc_runtime_call55','world_script_warp55'],['main','guild_world_visit194','world_script_warp55'],['main','regional_world_visit194','world_script_warp55'],['main','world_test_warp'],['main','frontend_run56','frontend_fade56']]
checks=[]
for chain in chains:
 frames={n:u[n] for n in chain};total=sum(frames.values());assert total+32768<=reserve,(frames,total,reserve);checks.append(dict(frames=frames,bytes=total,margin=32768))
# Assembly wrappers reserve 6144 bytes plus alignment/saved registers; the
# 512-byte nested-helper allowance exceeds recovered reset/math frames.
arcadeFrames=dict(main=u['main'],assemblyWrapper=6144+32,nestedHelpers=512)
arcadeTotal=sum(arcadeFrames.values());assert arcadeTotal+32768<=reserve
checks.append(dict(frames=arcadeFrames,bytes=arcadeTotal,margin=32768,assemblyExplicit=True))
nxdk=Path('/workspace/myro/toolchain/xbox-nxdk');objdump=nxdk.parent/'xbox-toolchain/usr/lib/llvm-18/bin/llvm-objdump';env=os.environ.copy();env['LD_LIBRARY_PATH']=str(nxdk.parent/'xbox-toolchain/usr/lib/x86_64-linux-gnu');symbols=subprocess.check_output([str(objdump),'-t',str(S/'main.obj')],env=env,text=True);assert '_lroundf' not in symbols
# Exercise exact bounded conversion with real asserting SDK math stub.
function=re.search(r'static int ui_round47a\(float value\)\{[^\n]+', (S/'ui_context.h').read_text()).group(0)
with tempfile.TemporaryDirectory(dir=V/'tmp') as td:
 d=Path(td);(d/'probe.c').write_text('#include <assert.h>\n'+function+'\nint main(void){assert(ui_round47a(0)==0);assert(ui_round47a(.49f)==0);assert(ui_round47a(.5f)==1);assert(ui_round47a(-.5f)==-1);assert(ui_round47a(1625.4f)==1625);return 0;}\n')
 subprocess.run(['cc','-O1',str(d/'probe.c'),str(nxdk/'lib/pdclib/platform/xbox/functions/math/lround.c'),'-lm','-o',str(d/'probe')],check=True);subprocess.run([str(d/'probe')],check=True)
report=dict(nativeCompiled=True,title=title,xbeBytes=len(xbe),xbeSHA256=hashlib.sha256(xbe).hexdigest(),stackReserve=reserve,knownChains=checks,unsupportedLroundReference=False,boundedRoundingPassed=True,legacySDKHarness='Repaired: 42 SDK cases and 1806 sanitizer HUD cases pass; see SDK-Checks194.json and HUD-Checks194.json',warnings=['Ignored trigraph in inherited NPC text','Linker .edata merge warning'],scope='Private native compile/link and conservative known stack nesting plus 32KiB margin; not exhaustive stack analysis, hardware RAM measurement or Xbox/Xemu playtest',additionalReviewPassesCompleted=0,originalXboxPlaytested=False,xemuPlaytested=False)
(V/'Native-Checks194.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
