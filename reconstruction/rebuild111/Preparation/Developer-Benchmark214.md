# Developer benchmark / recovery savepoint 214

This is a durable development checkpoint for the full Ragnarok Offline 1.11.0 project. It is **not a release patch, performance/FPS measurement, Xbox/Xemu playtest, completed normal release regression, or either additional review pass**. The accompanying immutable archive and receipt pin the exact source commit and private build. Continue development from this work; do not restart the recovery audit.

## Preserved locations

- Active reconstruction: `/workspace/work/recovery/rebuild111`.
- Source checkpoint worktree: `/workspace/work/recovery/checkpoint`, branch `recovery/ragnarok-1.11.0-inventory` and immutable tag `ragnarok-1.11.0-dev-benchmark214` at `https://github.com/codydarveau-beep/main`.
- Immutable developer backups: `/workspace/work/recovery/benchmarks`. The generated receipt records the exact archive and source commit; it is stored outside the tracked source to avoid a self-referencing commit hash.
- Original workspace `/workspace/myro` remains preserved. Do not replace it or attempt to revive the inaccessible earlier environment.
- Exact released baseline: `/workspace/work/recovery/released-1.10.0.iso`, 1,889,075,200 bytes, SHA-256 `b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e`.
- Original executable reference: `/workspace/work/recovery/packet194/released-default.xbe`. Its archive copy is a reference for the native CPU comparisons, not the new development executable.

The archive carries the source/reports, private native build and stack metadata, original executable reference, baseline manifest, and added runtime assets. The eighteen unchanged released content packs are referenced by their exact released hashes instead of being duplicated. They are recoverable from the preserved released ISO; the user retains released builds. The new eight-direction cabinet art and reconstruction metadata are in the source checkpoint. No additional released-asset request is currently needed.

## Scope and state at this checkpoint

The target remains the complete twelve-chapter campaign and original nineteen-person companion roster, guild upgrades, all six original arcade engines, regional content, campaign-aware access and preserved native job costs/rewards. Original Xbox with 64 MB RAM is primary; Xemu remains supported. Online party/WoE content stays excluded.

Available normal checks pass, including the private native build and conservative stack checks. `Validation/Developer-Benchmark214.json` indexes the exact evidence and source digest. `Validation/Normal-Release-Checks194.json`, `STATUS.md`, `WORK-REMAINING.md` and `RELEASE-GATES.md` retain the detailed limits.

| Area | Current game implementation | Remaining distinction |
|---|---|---|
| Campaign | All dialogue, authored staging, evidence/encounters, aliases, routes, completion rules, original journal directions, minimap markers and document props are restored. Complete bounded host candidate sequences exercise all chapters. | Full roster integration, remaining native emote presentation, full travel/job/save regression and final activation remain. Scene-sequence combat/job outcomes use explicitly identified fixtures. |
| Companion progression | Independent EXP/job EXP, personality paths, story/job promotions, durable character HP/SP/growth/settings, reserve/swap preservation and promoted art are restored. | Full-roster mixed-party and complete campaign acceptance remain. |
| Restored combat candidates | Roan, Yuufa, Takius through both promotions, Edda through promotion, Kaede, Miri, Judia through promotion, Brann through promotion, Iruga through promotion, and Pip have original candidate paths with native comparisons and actual host integration. | The world-selection guard still admits the original initial pair while roster-wide integration continues. Candidate readiness is not target playtesting. |
| Missing combat implementation | Maya's original potion support and the remaining roles Suri, Kest, Oren, Lale, Dagna, Corin, Daro and Haneul need completion. | Preserve each original kit; do not enable generic melee substitutes or invent active abilities merely because they appear in a learned-skill queue. |
| Guild / arcade | Original room/furnishing/collision rules, invitations/upgrades and all six original engines/screens are restored. Cabinet art has eight camera directions. | Release-wide context regression and target controller/visual/performance acceptance remain. |
| Regional / access | Nine retained dispatches, fee-safe travel preflight, chronology checks and scene-only aliases are integrated and host-checked. | Full native career/service and campaign-context dependency reconciliation remain. |
| Saves | Complete native RPV3 companion record, original RPV2 migration, per-character resource/growth transactions and multiple failure paths are restored. | Legacy sandbox migration and complete released-character/save regression remain uncertified. |
| Platform / delivery | Private 1.11.0 RECOVERY executable compiles. Existing caches/budgets and exact 1.10.0 patch baseline are preserved. | 64 MB residency, real frame timing, Xbox/Xemu acceptance, final normal regression, two additional reviews and ZIP packaging validation remain. |

At capture, `CAMPAIGN_RELEASE_SCENES193 = 12` and `CAMPAIGN_OPENING_READY200 = 0`. The former is the retained four-chapter checkpoint ceiling; the latter is a private development guard. Neither reduces the agreed final campaign. Change them only after the complete later runtime and companions are integrated and checked. **Additional review passes: 0/2, neither started. No final 1.11.0 patch is packaged.**

## Recovery decisions that must survive handoff

- Maps 495 (`story_thana194`) and 496 (`story_moc194`) reuse original maps 343 and 118 respectively. They are independent scene identities, not replacement interiors. Preserve original terrain/height/collision/scenery; do not import native NPC scripts, encounters or ritual entry rules. Missing transport coordinates were explicitly reconstructed and collision/path checked, not called recovered.
- The opening escort is preserved. No additional scene-specific movement/camera timelines are missing. The 264 retained views were eight-bearing visibility audits across 33 stages, not cinematic camera tracks. Preserve functional staging, modal control locks, interactions, encounters and cleanup. Do not invent lost choreography.
- Ordinary companions are replaced by scene actors during all modal stages. Expression portraits remain; remaining native emote integration is real presentation work.
- Native helper data and caller behavior are separate. The original initial pair pays raw technique costs; generic caster discounts must not be applied to those callers. The original minimum starting technique rank is retained only where its original caller uses it.
- This project's authored career IDs include Kaede 41, Miri 45, Iruga 12/26 and Pip 40. Use recovered roster/learning records; generic RO numbering caused incorrect early specialist fixtures and was corrected and rerun.
- Native companion basic enemy targeting supports melee/ranged attacks. A prior optional scope question asks whether additional enemy spell/status targeting was actually agreed. No answer is an approval, and the absence of that answer does not prevent the remaining original companion work. Do not manufacture a lost enemy spell engine from an assumption.
- Use the actual original six arcade engines and native room/furnishing data. Their recovered assembly and independent replay evidence are in the checkpoint.
- Keep all story updates spoiler-free. Put hashes, counts and internal paths in reports rather than routine chat. Ask only for necessary missing assets, decisions or access; continue authorized work between updates.

## Resume procedure

1. Read this file, `STATUS.md`, `WORK-REMAINING.md` and `RELEASE-GATES.md`. Verify the immutable backup with its included `verify.py` before restoring it into a **new** directory. The receipt pins the Git source commit and archive checksum.
2. Continue the remaining original companion support/physical/specialist kits. Reference pseudocode is preserved in `Validation/Native-Decompile203`; it is evidence, not completed buildable game code. Native replay scripts execute the immutable original executable using Unicorn 2.1.4; Capstone 5.0.9 is also installed in `/workspace/work/recovery/emulation-libs`. They can be reinstalled into the same relative directory in a new environment. Do not substitute simpler kits.
3. Verify mixed parties, resource persistence/promotions across the complete campaign, native job/access dependencies, remaining presentation and save compatibility. Finish all normal release-wide checks before starting either extra review.
4. Then perform and record both additional review passes. Only afterward build and validate the established ZIP patch accepting **only exact released 1.10.0**, including rejection, reconstruction and rollback. Host or native CPU comparisons must never be called Xbox playtests.

Useful normal commands, from the reconstruction directory:

```bash
python3 Preparation/run_developer_benchmark214.py
python3 Preparation/run_developer_benchmark214.py --refresh
source /workspace/myro/activate-toolchain.sh
make -C Source -j2 ../XboxFiles/default.xbe
python3 Preparation/check_native194.py
python3 Preparation/summarize_normal_checks194.py
```

The default benchmark checks checkpoint evidence and records current source/artifact digests. `--refresh` reruns the available policy/guild integration suites and restored companion integration suites first. It does not execute target hardware or complete the remaining release gates. Its working report may be regenerated; an already created immutable archive is never modified.

Avoid `make all`: it also targets ISO generation. Wait for compilation to finish before validating or snapshotting the binary. If a production source changes during compilation, force a fresh main compilation before recording results. The native compile is not an Xbox/Xemu playtest or a 64 MB proof.

### Safe source checkpointing in the partial checkout

The Git worktree has inherited missing blobs. **Do not use `git add -A`, normal `git commit`, or normal `git write-tree`.** Copy only the authorized reconstructed subtree, retain the inherited tree and use the established safe procedure:

```bash
# From the reconstruction directory:
python3 Preparation/checkpoint_source194.py
# From /workspace/work/recovery/checkpoint:
git add reconstruction/rebuild111
tree=$(git write-tree --missing-ok)
parent=$(git rev-parse HEAD)
commit=$(git -c user.name='Recovery checkpoint' -c user.email='recovery@users.noreply.github.com' commit-tree "$tree" -p "$parent" -m 'Describe the verified source checkpoint')
git update-ref HEAD "$commit" "$parent"
git push origin HEAD:refs/heads/recovery/ragnarok-1.11.0-inventory
```

The copier excludes private native binaries and large released assets from Git. The separate developer backup keeps the private artifacts needed to return to this savepoint. Preserve both copies and the existing released baseline.
