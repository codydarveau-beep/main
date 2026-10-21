MYRO TEST45a - TERRAIN RENDERING HOTFIX

Extract the full ZIP. Run Apply-Update.cmd and choose your Test45
MyRO-Current.iso. The updater preserves the original and creates/verifies the
corrected MyRO-Current.iso. Mount that corrected image and reset the game.
This requires the exact Test45 image, not Test44. Complete current source included.

FIX
Test45 corrected the camera handedness to remove the mirrored world, but terrain
back-face culling still used the old clockwise front-face convention. This could
hide the ground while scenery remained visible. Terrain now uses the matching
counterclockwise convention. Corrected map orientation is retained.

Your latest correction is included: the makeshift generic casting glow is removed.
Spell-specific effects, blue casting bar and spell callouts remain.

All four content packs are byte-identical to Test45. No scenery, map geometry,
collision, equipment or Quicken changes are bundled into this hotfix. Saves stay
in Save44. Test46's UI/collision/equipment work remains separate and unfinished.

The reported Horong attack/black effect remains a separate animation investigation;
this hotfix does not claim to resolve it. The source ACT contains black layers,
and the full attack sequence needs review before changing its appearance.

CHECK FIRST
- Izlude ground/bridges and Payon Cave5 terrain are visible again.
- Rotate and zoom in both places; confirm ground remains visible.
- Confirm cave orientation stays corrected and scenery still occludes normally.
- Casting has no generic golden glow, while specific skill effects remain.

See VALIDATION.txt and Validation-Logs for actual build/check evidence.
