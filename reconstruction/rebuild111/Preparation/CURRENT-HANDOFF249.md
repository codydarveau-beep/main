# Current handoff — packaging paused at designer request

The designer requested an immediate GitHub commit and removal of old reproducible files after unstable chat behavior. Do not resume packaging in this turn.

## Completed

- Complete twelve-chapter/36-scene runtime enabled; all nineteen original companion kits, independent growth/promotions/settings/vitals, guild construction, six original arcade engines, eight-direction cabinets, nine dispatches, native quests/costs/rewards and campaign-aware access preserved.
- Corrected normal release-wide checks passed on the current unchanged Source: `Normal-Complete-Checks244.json`, `Full-Candidate-Checks240.json`, `Companion-Release-Checks224.json`.
- Both additional reviews completed AFTER corrected normal checks: `Additional-Review-Pass1-245.json`, `Additional-Review-Pass2-247.json`.
- A genuine upload-order bug found during review was fixed BEFORE repeating all normal checks and confirming both final reviews. Campaign poses are now prepared after the GPU fence and before generic actor upload. All 9,352 real poses pass the actual production uploader/pixel/cache/cleanup probe (`Campaign-Upload-Checks246.json`).
- Actual character/session reset probe passes; no cross-character transient actor/effect/access/companion state survives rebinding.
- Obsolete test-character preservation/migration is deliberately not required. Keep current-format durability and interrupted-write recovery.

## Remaining

No final ISO or ZIP has been built. Package and validate the established format-2 ZIP accepting ONLY exact released 1.10.0. Native executable remains the private RECOVERY build. Do not claim Xbox/Xemu playtesting or complete 64 MB residency; those remain unverified on target.

Existing PowerShell `/workspace/myro/pwsh/bin/pwsh` 7.4.6 works. Extract-xiso follows symbolic links via stat, so stage large original data packs with symlinks; hardlinking lower-layer assets can consume overlay space. Keep only one newly generated full ISO at a time. Original baseline ISO is in the recovery root and MUST be preserved. Delivery-Plan244.md and the released 1.10.0 ZIP/updater provide the delivery reference.

Potential final packaging presentation task: private pause label is `MyRO 1.11.0 DEV` and certificate title is `MyRO v1.11.0 RECOVERY`. Preserve the checked private Source/artifact. If producing a release-labelled artifact, use a separate staging/build directory, record only the label/title changes, and validate its native stack/artifact metadata. No such release transformation has been performed.

## Preserved

Active source: `/workspace/work/recovery/rebuild111`. Git source checkpoint: `/workspace/work/recovery/checkpoint`, branch `recovery/ragnarok-1.11.0-inventory`. Original `/workspace/myro`, all released data/source archives and immutable developer archives remain untouched. The designer received the direct developer backup217 download; do not delete/replace that published branch/archive.

Storage cleanup removed an abandoned incomplete/unindexed Git transfer (~802 MiB), a redundant reinstallable PowerShell download, and ~493 MiB of reproducible host executables after final checks. Detailed manifests are Disk-Cleanup243.json and Post-Review-Cleanup248.json. Further cleanup for this request is recorded in Commit-Cleanup249.json. Do not remove recovered inputs, current Xbox binaries, reports, registered Git objects or developer archives to save space.


## 1.11.0 delivery completion251

Normal corrected-source checks and both subsequent additional reviews passed. The separate release-labelled native build changes only the pause version text and certificate title; reviewed private Source and native artifacts remain intact. Release-native known stack guards pass. The established format-2 ZIP accepts only exact released1.10.0. The actual shipped PowerShell updater rebuilt and verified the ISO/all20files and passed idempotence, wrong/same-size altered baseline, missing/corrupt payload, conflicting output, partial invalid-range/full target-hash failure cleanup, rollback/receipt and original-input preservation. See Patch-Validation251.json and Release-Native-Checks250.json.

Final ZIP: /workspace/work/recovery/release111/MyRO-1.11.0-Update.zip. Target ISO was removed after packaging to keep disk use bounded; validation rebuilt it independently and removed the generated test image after verification. All original source/assets/baseline/developer archives remain preserved. No Xbox/Xemu playtest or complete64MB runtime residency claim. Natural playthrough/balance, target performance/controller/CRT/FATX testing remain. Delivery branch: ragnarok-1.11.0-download; direct raw link will be verified before the user receives it. Packaging pause249 was superseded by the designer’s instruction to finish the build.


## Active preservation restoration252

Designer reports extensive1.9.x UI/control/render regressions in delivered1.11.0. REGRESSION-LEDGER252.md records38 groups, historical decisions/encountered bugs, current evidence versus suspicion, latest overrides and Xbox-only checks. Earlier release tests were too narrow to establish whole1.9.x preservation. RESTORATION-CURRENT252.md is now the active entry point. Original title recovered losslessly from exact released executable; Hanson initial native-admission denial reproduced and targeted opening admission/17native graduation destination redirects restored. Actual full native VM graduation passes with explicit course/carrying/OnInit fixtures and no early job. Native scripts/costs/rewards remain unchanged. Willow/guardian/memory/shared-rendering audits and remaining UI repairs are not complete. Additional restoration reviews0/2, unstarted; normal restoration checks precede them. No corrective ZIP published.
