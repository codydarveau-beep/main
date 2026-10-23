# MyRO Test50a

[Download Test50a](MyRO-Xbox-Test50a-Update.zip) (2.6 MiB). Extract it, run `Apply-Update.cmd` and select your exact **Test50** `MyRO-Current.iso`. Load the resulting `MyRO-Current.iso` in xemu and reset the Xbox. Save50 remains compatible.

Addresses the native stack overflow at the first 30-second autosave, removes repeated save checksums from the HUD, and caches actor depth calculations once per frame. Developer Class presets now **replace carried items with a fresh class kit**, rather than accumulating supplies from previous classes. All 20 selectable kits stay below 50% carry weight. Storage and cart contents remain intact. If Wizard is already overloaded, reselect Wizard in Class presets.

[Changes and testing notes](MyRO-Test50a-Notes.md). Native Xbox build and stack guard, 57 sanitizer suites, 1,629 HUD cases, the real nxdk unsupported-math guard, clean source rebuild and actual PowerShell update/rollback/failure checks passed. Emulator/hardware FPS and the runtime freeze fix still need confirmation in play. Please test past several autosaves in Payon Cave 5 and check idle FPS.

[Matching source and licences](MyRO-Xbox-Test50a-Source.zip) (21.8 MiB). Both ZIPs are below 32 MiB; source is optional for playing. [Release hashes](MyRO-Test50a-Manifest.json).
