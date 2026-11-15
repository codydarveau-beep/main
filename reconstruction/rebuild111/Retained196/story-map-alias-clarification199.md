# Designer-confirmed campaign environment references

Maps 495 and 496 are scene-specific aliases of existing maps, not new environments:

- 495 `story_thana194`: source map 343.
- 496 `story_moc194`: source map 118 `moc_fild22`.

Reuse source terrain, height/collision, scenery and associated graphics. No authored static changes are recorded. Preserve surviving actors, evidence and encounters. Do not import source NPC scripts, native encounter prerequisites, multiplayer or ritual entry mechanics.

Recovered transport:

- 280 at (1004,100) -> 495 at (1092,932). Appears at cursor 28; requires objective bit 2 while cursor is 28.
- Paired 495 -> 280 return; trigger not retained.
- Existing camp on map 7 -> 496 appears at cursor 32 and opens at 33.
- Paired 496 -> 7 return; exact breach arrival and return coordinates not retained.
- Original map 118 remains separately restricted until cursor 35.

Where coordinates are missing, reconstruct reachable entrances using surviving placements and actual source collision. Label these as reconstructed rather than recovered. See Preparation/Story-Aliases-Recovery199.json for the explicit distinction.

Preserve scene architecture: load environment; stage actors and encounters; run scripted movement/dialogue/combat with appropriate player-control locks; release scene resources; return to ordinary exploration.

This supersedes the earlier missing-layout question. Restore environment references; do not design replacement interiors.
