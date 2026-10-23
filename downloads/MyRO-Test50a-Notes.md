# Test50a — autosave, frame cost and class kits

Update from the exact Test50 ISO. Extract the update ZIP, run Apply-Update.cmd,
select the Test50 MyRO-Current.iso, then load the resulting MyRO-Current.iso in
xemu and reset the Xbox. Save50 remains compatible; no character reset is needed.

The repeatable freeze around the first 30-second autosave had a concrete native
stack overflow: Test50 reserved 64 KiB, while main plus the nested save/scan frames
alone exceeded that. Test50a moves the persistent SaveStore out of main's stack
and reserves 128 KiB. The native build now checks compiler-reported save nesting
against the actual executable reserve, including 32 KiB additional margin. The
stack reserve increases by 64 KiB; SaveStore uses fixed static storage. These
allocations have a fixed size.

Saved/Unsaved HUD checks no longer calculate a disk checksum over all 8,192 bytes
every frame. Actual disk writes still calculate and verify their checksum; the
Save50 format is unchanged. Actor depth correction now derives its slope once
per frame from the camera matrix, removing per-actor trigonometric calls while
retaining the wall-occlusion correction.

Developer > Class presets now replaces carried test items with a fresh kit for
the selected class, including a suitable weapon, basic armour and relevant
reagents/ammunition. Reapplying a preset replenishes that kit. Items from prior
class kits do not accumulate. Storage and cart contents remain intact. All 20
selectable class kits are below 50% carry weight, allowing recovery and casting;
Wizard receives a Rod and gemstones, rather than other classes' weapons/traps.
If a saved character is already overloaded, reselect its current class in
Class presets to receive the lighter kit. Ordinary class changes outside the
developer presets still preserve items.

Validation includes the native Xbox build/stack-budget guard, Save50 disk
round trips and failure handling, repeated developer class switches, Wizard
casting/SP recovery, sanitizer regressions, HUD bounds and the actual nxdk
unsupported-math guard. GPU counts/dimensions and printed numbers remain integer
compatible. No emulator/hardware FPS or runtime freeze test has been performed
here; the next play test must confirm those symptoms are resolved.

For testing: remain in Payon Cave 5 past several 30-second autosaves, then switch
to Wizard through Developer Class presets and check casting/recovery. Please
report the idle FPS and any freeze. Existing Test50 content and limitations are
described in TEST50-NOTES.md in the source archive; this is a focused hotfix.
