# Retained 194 recovery packet: reconciliation checkpoint

The supplied packet is preserved verbatim as `recovery-packet-original.txt`, with its hash recorded in `reconciliation.json`. Six complete header excerpts are extracted under `Source/` without edits. This directory is an unintegrated recovery artifact; it does not replace the earlier `recovered/dev200` source tree.

No further development archive is assumed available. Reconstruction proceeds from the packet, earlier source, and exact released bytes. No gameplay code was modified, no native compilation or historical host suite was run, and no Xbox/Xemu playtest occurred. Both additional release review passes remain pending.

## What is now recovered

- Complete excerpts: `career_access194.h`, `career_warp194.h`, `campaign_access194.h`, `native_admission194.h`, `regional194.h`, and `regional_world194.h`.
- The original source bank is 16,778,501 bytes; released `scripts.bin` is 17,353,591 bytes and matches the packet's SHA-256. It remains unmodified.
- The released executable contains a unique validated program lookup table at file offset 5,138,212. All 3,948 selected program containers pass header, bounds, CRC, opcode, string, entry and owner checks. All program owner IDs match the earlier registry; 31 program offsets or lengths differ. A scan alone encounters duplicate owner candidates, so active programs are selected using the actual deployed lookup table, never by guessing from scan order.
- Recovered metadata: all 10,181 released NPC records, the 495 released map names, 85 function rows matching the executable, and 1,506 timer labels reconciled with deployed program labels. The released NPC record numeric fields match the older source; the packet's later relocations have not been applied.
- The two career record numbers are **one-based record IDs**, not zero-based array indices: 7351 / program 3829 and 7588 / program 3886. Applying a relocation to array index 7351 or 7588 would move the next NPC.
- `RecoveredMetadata/npc_registry_data55.h` is a reconstructed data header, not an integrated runtime replacement. The old runtime uses `NPC_RELEASE_JOBS_ONLY55`; its deployed preprocessor value is not established by these tables and is deliberately not invented in the reconstructed header.

The metadata recovery does not recover the full released C implementation. The six retained headers are not represented as independently verified implementations.

## Gaps and reconstruction gates

| Component | Present | Work still required |
| --- | --- | --- |
| Pilgrimage receipt and career warp | Complete excerpts; earlier state/world API shapes match | Root-program dispatcher wiring; actual native-quest and failed-persistence checks |
| Campaign admission | Complete excerpt | Full `campaign_access_data194.h`; 497-map policy review |
| Native NPC chronology | Complete excerpt and deployed registry/script metadata | Full `npc_access_data194.h`, transitive abstract interpreter, original departure redirect, render/open/touch/event adapters |
| Fee-safe travel | Contracts and original service IDs | Reconstruct preflight implementation; preserve original option ordinals and SELECT state before native fees |
| Nine regional dispatches | Complete core/world excerpts and UI/journal contracts | Missing guild foundation, complete UI/journal/tracker adapters, world interaction integration |
| Guild and arcades | Released runtime assets; earlier source lacks `guild194.h` | Reconstruct editable source while preserving existing released functionality |
| Later private maps | Names, IDs and minimum cursors | Implementations of private maps 495 and 496; neither is in the 495-map released catalog |

Direct missing includes are `campaign_access_data194.h`, `npc_access_data194.h`, `story_departure193.h`, and `guild194.h`. Additional required callbacks and adapters are absent from the earlier tree, including `campaign_sandbox193` and the three 194 admission registrations. Presence of an earlier career guard is not recovery of these later transport boundaries.

`map-policy-evidence.json` records only explicitly retained policy facts. It contains 497 map identities, with 11 exact numeric minimum-cursor assignments and 486 unknown minima. Region membership is unresolved. Null means unknown; it never means unrestricted. Qualitative early-class access is recorded separately without assigning an invented cursor. No permissive placeholder policy or dependency header is generated. The nine known regional minimums, eight reserved ledger positions and Expedition-completion prerequisite are recorded separately.

The packet's prior 2,175-member / 12,248-byte dependency-table totals are historical comparison targets, not regenerated results. The original analysis counts and host-suite claims have not been rerun. A native build is not appropriate until the missing policy, departure/guild foundations and adapters are reconciled.

## Required behavior to preserve during reconstruction

- Native scripts retain job requirements, costs, rewards and quest state. Career adapters use the root NPC program, not a shared helper's current program.
- Admission must precede fees, SP/material spending, RNG, loading and portal-use decrement. A denied original selection preserves VM SELECT, PC, ordinals, Cancel, `@menu`, inventory, money, savepoint and state revision.
- Chronology must not replace `npc_scene_available64()`. Initialization remains active; blocking open happens before pending talk, movement/cast interruption or VM start.
- Preserve the three 17-bit regional masks and reject invalid 51-bit records. Native quests remain necessary. Completed physical notices retain free return access.
- The final paragraph-wrapping change is an unverified fragment. The full guild UI is not retained; no previous rendering/controller result certifies that last edit.
- Public target remains 1.11.0, with only released 1.10.0 accepted as its updater baseline. Historical `2.0.0 DEV` names do not change that target or prove full-campaign activation. Exclude online party/WoE and the eight reserved/unavailable/party-instance dispatch groups.
- Original Xbox 64 MB remains primary; bounded caches and actual hardware acceptance remain required. Historical host results are not Xbox playtests. Normal completion checks and two additional review passes must precede any release package.

## Art evidence

The packet records an outstanding reference collector. A focused search of the initially inventoried asset library, attachments and campaign preparation found no named requested character references and no ordinary female Wizard body SPR/ACT pair. This is a filename-based finding, not proof that differently named image content is absent; no new asset request is made at this checkpoint.

## Reproduction

Run `reconcile.py`, then `recover_registry.py`, then `policy_evidence.py` in the new recovery workspace. They read preserved original source and the verified recovered 1.10.0 ISO, and write only recovery artifacts. The scripts and reconstructed tables are checkpointed with the original packet. The extracted executable and script bank remain local; their exact released hashes and reconstruction provenance are recorded in the committed reports.
