MYRO TEST44 - LOADING RECOVERY / MEMORY RESIDENCY / IZLUDE FIXES

Extract the whole ZIP. Run Apply-Update.cmd and choose the working Test43
MyRO-Current.iso. The updater verifies the exact baseline, preserves it and
creates/verifies the new MyRO-Current.iso. Mount the new ISO and reset xemu.
This update requires Test43, not Test42 or Test34. Full current source included.

STARTUP RECOVERY
Test44 starts fresh disposable characters in E:\MyROOffline\Save44.
Your old Save43 files are left untouched and are not imported. Select your
Knight/High Wizard preset again via hold START > Testing > Developer tools.
If a future saved location causes trouble, hold B while the game starts through
the initial loading screens. It loads your character at South Field camp before
attempting the saved map. Skills, items and stats are retained. Initial disc
loading still occurs normally; keep B held until the game appears.

FIXES
- All18 minimap titles use the full map table. Test43's stale seven-name table
  could read out of bounds upon entering appended maps, leaving the last
  loading screen visible. The southern route's maps are present in the ISO.
- Destination metadata is checked before enabling blue/interactable gates.
  Source warps from the new region to unbuilt destinations are red/inaccessible.
  Map loading now labels enemy/minimap preparation separately from scenery.
- Minimap raster and markers are mirrored horizontally together; camera
  controls are unchanged.
- HP/SP bars move to fit the displayed numbers, including Knight8488/8488.
  JOB EXP gains the requested leading space.
-50 omitted raised Izlude collision cells now use source GAT corner heights.
  Four southern bridge-approach columns pass movement checks both ways.
  The old average-height threshold missed partial raised ramp corners.
- Original Enlarge Weight Limit, Push Cart and Change Cart icons installed
  from your returned collector files.

MEMORY / DISC LOADING
Only the selected player variant is decoded. Switching class/equipped artwork
reads its packed section from actors.bin, releases the old decoded player,
then releases the temporary packed input. This includes the existing special
Swordsman two-handed artwork, previously embedded despite only one decoded body.
Only one map's terrain, collision and scenery are resident. Zoning releases the
previous map and its enemy cache before loading the next map from world.bin.
Enemy packed artwork now resides in enemies.bin instead of the XBE. Only current
map species are read/decoded, plus at most one optional developer target species.
The fixed GPU frame pools, common effects/UI/audio and game metadata remain
shared resources. This is not a full current-skill-only effects cache.

The native XBE image allocation falls from9,388,308 to7,364,884 bytes: a static
2,023,424-byte reduction (about1.93MiB). This is a build measurement, not a measured
runtime free-RAM gain. Xbox CPU/GPU share64MB; GPU uploads do not move allocations
into a separate VRAM pool. Please compare free RAM after class/map switching.

No xemu or hardware execution was performed here. No runtime FPS/RAM claim.
Test43's map/class gameplay and prototype limitations otherwise remain.
See TEST-CHECKLIST.txt and VALIDATION.txt for focused tests and evidence.
