"""Export preserved native callback reference views; not buildable game source."""
from pathlib import Path
import subprocess,os
R=Path(__file__).resolve().parent.parent;D=R.parent/'decompiler203';V=R/'Validation/Native-Decompile203';V.mkdir(exist_ok=True)
SCRIPT207='import ghidra.app.script.GhidraScript;\nimport ghidra.app.decompiler.DecompInterface;\nimport java.nio.file.*;\npublic class Document207 extends GhidraScript {\n public void run() throws Exception {\n  long[] addresses={0x117850};\n  for(long a:addresses){disassemble(toAddr(a));if(getFunctionAt(toAddr(a))==null)createFunction(toAddr(a),null);}\n  var d=new DecompInterface();d.openProgram(currentProgram);\n  for(long a:addresses){var f=getFunctionAt(toAddr(a));var r=d.decompileFunction(f,60,monitor);if(r.decompileCompleted()){Files.writeString(Path.of(getScriptArgs()[0],"callback-"+Long.toHexString(a)+".c"),r.getDecompiledFunction().getC());println("Exported callback "+Long.toHexString(a));}else println("Failed callback "+Long.toHexString(a));}d.dispose();\n }\n}\n'
(D/'Document207.java').write_text(SCRIPT207)
env=os.environ.copy();env['JAVA_HOME']=str(D/'jdk-25.0.5+8')
with (V/'document207.log').open('w')as log:subprocess.run([str(D/'ghidra_12.2_PUBLIC/support/analyzeHeadless'),str(D),'document207','-import',str(D/'native-flat203.bin'),'-loader','BinaryLoader','-processor','x86:LE:32:default','-cspec','windows','-loader-baseAddr','10000','-scriptPath',str(D),'-noanalysis','-postScript','Document207.java',str(V),'-deleteProject'],env=env,stdout=log,stderr=subprocess.STDOUT,check=True)
