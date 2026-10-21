MYRO TEST45 - MAPS, COMBAT FEEDBACK AND EFFECTS

Extract the complete ZIP. Run Apply-Update.cmd and select your working Test44
MyRO-Current.iso. This is an exact Test44 -> Test45 update. The updater preserves
the original ISO and verifies the new MyRO-Current.iso. Mount the new image.
Complete current source is included. No rollback bundle is needed.

White decreases / Black increases the highlighted active skill's cast level.
Learning ranks and prerequisite checks are unchanged. Walking defaults to 100%;
the walking slider remains. Diagnostics is now an independent Toggles setting;
R3 closes windows. Your Save44 namespace is retained. Hold B during startup to
recover a saved location to South Field camp if necessary.

All 18 maps now share the corrected camera projection handedness. World geometry,
controller movement, sprite facing and original minimap images use one orientation.
This fixes the mirrored caves globally rather than applying cave-only patches.
Raised source walk surfaces support Sograt bridges and Payon stairs. Izlude's
accepted collision data and movement behavior are preserved.

Personal buffs and their remaining timers survive zoning. Random Teleport works
on the appended maps. Cast movement has a brief 0.2-second guard. Threatening
monsters take targeting priority, with lower HP first; other targets use distance.
Enemy direction hysteresis and return-home logic address rapid direction flicker.

See TEST-CHECKLIST.txt for every changed effect and relevant gameplay test.
Original effects and prototype geometry are explicitly distinguished there.
See VALIDATION.txt for build evidence and MEMORY-RESIDENCY.txt for resource scope.

REBUILD
Use Source/build45.sh with the existing Checkpoint-15 nxdk toolchain. Supply your
new Test45 ISO as its second argument to stage the four matching packed assets,
or run Source/stage_base_assets45.py on that ISO first. Packed content stays on
disc; it is not duplicated inside this source bundle. Conversion tools reference
collected original assets and are for development, not needed for a native rebuild.
