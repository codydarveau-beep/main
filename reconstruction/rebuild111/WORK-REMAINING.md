# Completing 1.11.0

The agreed scope is unchanged: twelve chapters/36 scenes, nineteen independently growing companions, guild construction and upgrades, six original arcade games, nine regional dispatches, campaign-aware access, and preserved native job quests/costs/rewards. Original Xbox with 64 MB is primary; Xemu remains supported. Online party/WoE is excluded. Only exact released 1.10.0 is an accepted patch baseline.

## Current implementation and verification

| Area | Missing or broken functionality | Completed functionality and host evidence | Requires target testing |
|---|---|---|---|
| Campaign | No known remaining missing authored runtime feature. | All 36 scenes are enabled following later-runtime integration. Ordinary world interactions, stage/art readiness, dialogue, expressions/emotes, control locks, evidence, encounters and cleanup are exercised. Opening escort and existing gameplay camera are preserved; no imaginary lost cinematic tracks were added. Complete sequence tests cover all roles/replies. Real authored enemy combat is separately exercised with an explicitly qualified/replenished host player; this is not balance acceptance. | Unassisted playthrough, controller/presentation, natural progression and combat balance. |
| Companions | All nineteen original kits and authored career paths are restored. | Own EXP/levels and preset growth, story-gated promotions, per-character HP/SP/settings, three-person formation and no swap healing are checked. Live recruitment/chapter rewards, actual combat EXP, all promotion transactions and full current-format save bundles pass their module checks. | Sustained three-companion combat, formation feel, readability, performance and memory. |
| Guild and arcade | No known missing original construction/game engine. | Original rooms, furniture, collision, upgrade costs, invitations and all six native game engines/screens are restored; original-code differential checks pass. Eight-direction cabinet artwork preserves the established design. | Room navigation/appearance, controller timing, cabinet playability and frame rate. |
| Regional/native content | No known missing core among nine retained dispatches. | Dispatch materials, prerequisites and one-time rewards are checked. Native quest bytecode is preserved. Actual NPC/VM finalization covers classical and expanded first jobs, deferred Super Novice progression, original rewards and reachable denial/repeat cases. Earlier quest milestones are declared fixtures, not full journeys. | Full original quest journeys and regional playthrough acceptance. |
| Travel and chronology | No known unresolved required scene-map reference. | Both campaign aliases reuse confirmed original geometry without native scripts/spawns. Empty alias NPC registry spans now prevent stale NPC state and out-of-range reads. Denied travel preserves funds/items/quests. Current stage connectivity and optional native ferry admission/fare/path are checked. Missing historical coordinates remain explicitly reconstructed and collision checked. | Streaming/controller transitions and complete journey acceptance. |
| Content | Released input mismatch is resolved. | All eighteen data packs match released 1.10.0; production readers cover catalogs, expressions, promoted bodies and scene props. | GPU color/alpha, visual placement and streaming. |
| Saves | No known missing current-format core. Obsolete test characters are deliberately expendable. | Actual alternating store roundtrips campaign, companions, guild/scores, dispatches and native variables. Interrupted/lying writes preserve prior current-format state. Unsupported test slots remain replaceable by design. | FATX storage/restart and power-loss recovery for current characters. |
| Platform | No known compile failure. | Native compilation and known stack guards pass. All-map resource inventory passes, with bounded caches; inventory excludes some runtime allocations and is not a full 64 MB residency measurement. | Original 64 MB residency, stack high-water, audio/frame timing, CRT and controller. Xemu execution remains pending if a suitable environment becomes available. |
| Delivery | Final ZIP is not yet built. | Established ZIP/PowerShell format and released manifests survive. Corrected frozen-source normal release-wide checks and both additional reviews have passed. | Installation/run acceptance after developer packaging validation. |

## Required remaining sequence

1. Completed: normal integrated candidate checks and the full original companion-kit refresh on the corrected frozen source.
2. Completed: both additional review passes, confirmed after corrected normal integration.
3. Prepare and validate the established ZIP: exact 1.10.0 admission, reconstruction/hash, rejection, interrupted failure, existing-output protection and rollback. Keep the executable a development build until these checks and packaging validation are complete.
4. Deliver a direct download link and concise Xbox testing instructions. No host/native compilation evidence is described as an Xbox or Xemu playtest.

No additional assets or designer decisions are currently needed. Earlier recovery questions are answered in the retained clarification records. Historical checkpoints document earlier restrictions; their twelve-scene ceiling and disabled private readiness guard do not describe the current activated candidate.

Current detailed evidence lives in Validation, especially Full-Candidate-Checks240.json (normal runner result), Campaign-Runtime-Checks239.json, Campaign-Companions-Checks226.json, Companion-Promotions-Checks227.json, Campaign-Combat-Checks232.json, Campaign-Save-Bundle-Checks229.json, Native-First-Jobs-Checks231.json, Native-Expanded-Jobs-Checks233.json, Native-Supernovice-Checks235.json and Alias-NPC-Checks242.json. Read each report's declared fixture/target limitations.

Packaging is paused at the designer’s request for an immediate GitHub commit and cleanup. See Preparation/CURRENT-HANDOFF249.md.

Current completion251: corrected normal checks, both additional reviews, release-labelled native build and actual shipped patch/updater validation passed. The ZIP is ready for delivery. Target Xbox/Xemu playtesting and full64MB residency remain unclaimed. Prior packaging-pause/pending statements above are historical.
