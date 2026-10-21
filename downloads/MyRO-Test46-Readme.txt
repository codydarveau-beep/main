MYRO TEST46

Extract the full ZIP. Run Apply-Update.cmd and select your Test45 OR Test45a
MyRO-Current.iso. The updater verifies the input, preserves it and creates the
verified Test46 MyRO-Current.iso. Mount that image and restart the game.

Test46 uses a fresh Save46 test character because the inventory/save layout now
supports 100 items and ten equipment slots. Older test saves remain untouched.
Use START > Developer testing > Class presets to rebuild your test character.
Presets now provide test Zeny for equipment shopping. Base cap remains99.

WHAT CHANGED
- Original-style Basic Info, Status, Equipment, Inventory and Shop layouts.
- Compact skill list and expanded skill grid: RT switches between them.
  White lowers / Black raises the highlighted skill's selected casting level.
- 82 additional source-defined pieces of equipment, original item icons, job/level
  restrictions, weapon types, shields/two-handed exclusions and staff MATK.
  See EQUIPMENT.txt for the supported catalog and explicit limitations.
- Additional held-weapon families for Swordsman/Knight and High Wizard staff art.
- Current-map solid-prop clearance; source stair/bridge heights retained. Portal
  routes take priority over extra decorative collision. Fully black cave terrain
  triangles are removed; background clears black.
- Long target names and exact HP use separate lines rather than spilling out.
- Three developer pages; Apply ailment is under Practice. Old ranged-hit,
  wading-water and art-preview menu actions are removed.
- Quicken body tint reduced about20%, retaining its accepted trails.
- Successful-cast circle: final radius10% smaller, opaque, rotation10% faster,
  lines10% thicker. Accepted aiming ridge and blue cast bar retained.
- Source Horong attack uses its full37-frame sequence and partial fades instead
  of four sampled poses. Please retest the reported fire monster's final frame.
- Generic golden casting glow remains removed, as requested.

No additional assets are needed to test this build. Missing authentic spell
components remain on the roadmap; this build does not claim every skill effect
is complete. See TEST-CHECKLIST.txt, ROADMAP.txt and MEMORY.txt.

Full native source is in Source. To rebuild with the matching nxdk toolchain,
first stage packed assets from the completed Test46 ISO using
Source/stage_base_assets46.py. See Source/build46.sh.
