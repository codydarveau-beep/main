MYRO TEST47a - STARTUP HOTFIX + TARGET BUTTON SWAP

Extract the whole ZIP. Run Apply-Update.cmd and select your Test47
MyRO-Current.iso. The file does NOT need to boot for the updater to use it.
The updater preserves that original and creates/verifies Test47a.
This package requires Test47, not Test46.

FIX
Test47's first-frame diagnostics and Status display called lroundf. The supplied
nxdk SDK implements that function as assert(0), so it could stop before the first
gameplay frame, leaving the last 'Loading Minimap' screen visible while music
briefly began. Those UI calls are replaced with bounded arithmetic conversion.
The minimap and map content were not changed for this fix.

TARGETING
X: step inward (nearer).
Y: step outward (farther).
R3: immediately select the closest visible enemy, unchanged.
Menu X/Y actions are unchanged; this swap applies to gameplay enemy selection.

Your existing Save46 character format/namespace is unchanged. No intentional
character reset. All four content packs are byte-identical to Test47. Its restored
terrain, UI/atlas fixes, inventory/equipment work, monster labels without !!,
Quicken tint/trails, cast circle and Horong animation remain as they were.

CHECK
- Normal launch reaches gameplay and music keeps playing.
- Your saved character/location restores.
- Diagnostics shows walk numbers; opening Status also works without freezing.
- X goes nearer, Y farther, R3 nearest.

Full current source and actual SDK-stub regression/build/updater logs included.
No collector needed. Build with Source/build47a.sh and the matching toolchain;
Source/stage_base_assets47a.py stages packed assets from the completed47a ISO.
