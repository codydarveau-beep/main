"""Host-only native arcade replay linkage; never linked into the Xbox game."""
from pathlib import Path
R=Path(__file__).resolve().parent.parent
U=R.parent/'emulation-libs/unicorn'
def flags():
 return [str(R/'Validation/arcade_host197.c'),'-I'+str(U/'include'),'-L'+str(U/'lib'),'-Wl,-rpath,'+str(U/'lib'),'-l:libunicorn.so.2']
