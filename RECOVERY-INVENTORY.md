# Ragnarok Offline recovery inventory

The original environment was not accessed or modified. All inspection used the new environment and read-only access to the published repository. Original workspace files were preserved. No gameplay implementation, compilation, emulator playtest or Xbox playtest was performed.

## Verified recovery

- Repository source pinned to `9aeac8c16ddccbe3b4a8a2f359a30402b897ada4` on `myro-test45-download`.
- All 12 other pre-existing repository branches were checked; none adds files beyond the pinned tree. GitHub Releases is empty.
- All 377 remote files verified against Git blob identities. All 147 published ZIPs passed CRC checks; available SHA-256 sidecars matched. Remote ZIP member inventories and 135 recovery/build instruction documents were recorded.
- Released 1.10.0 ISO reconstructed through the published 1.9.0 -> 1.9.3 -> 1.10.0 patch chain, without changing the original 1.9.0 ISO. Full target SHA-256: `b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e`; size 1,889,075,200 bytes. All 19 contained files independently match the 1.10.0 release manifest. No build upload is needed.
- The released executable, campaign packs, guild interior, portraits and all other packed runtime assets are therefore recovered byte-for-byte. This does not recover editable C source or original authoring inputs from those packs.
- Three standalone source archives (Test50/50a/50b), earlier update ZIPs containing source, an earlier local campaign development tree (`dev200`), historical release trees, toolchain, story design and preparation files survive.
- Local initial inventory: 133,418 files, 73,110,124,643 logical bytes, 392 archives (388 ZIPs). These figures include duplicates and build outputs; they are not unique recovered content totals.
- Asset library: 63 groups, 37,948 files, 5,188,415,715 logical bytes, plus original attached archives. Presence does not establish coverage of every future campaign requirement.

## Editable-source gap

The 1.9.2, 1.9.3 and 1.10.0 update ZIPs contain binary patch payloads rather than native source. The newest standalone published source is Test50b. The local `dev200` source is an earlier campaign snapshot; it must not be represented as released 1.10.0 source. Its historical source manifest has 918 entries: none missing, 22 changed. Newly recorded hashes preserve the actual recovered files.

No source archive for the released 1.10.0 checkpoint, or actual later implementations of career-safe transport, NPC chronology checks, fee-safe travel restrictions and nine regional dispatch quests, was located in the enumerated files. Earlier career/quest code and ordinary uses of the word dispatch do not establish recovery of those later changes.

Needed next: the newest available native Source/development archive from the missing period, if retained, and the actual code excerpts for those unpublished changes from the previous conversation. Released build archives alone do not replace that source. No broad asset recollection or baseline ISO upload is currently needed.

## Release authority and work gates

1.10.0 remains the sole baseline for the next 1.11.0 ZIP patch. Historical internal 2.0 naming in preserved files is provenance, not a changed release target. Published 1.10.0 already includes six arcade cabinets and guild/companion foundations; retain and verify them against source recovery before deciding what needs implementation. Four chapters are playable in the published checkpoint. Later scope remains pending.

Original Xbox with 64 MB RAM is primary; Xemu remains supported. Preserve native job quests, costs and rewards; exclude online party/WoE content. Public updates remain spoiler-free. Checkpoint recovered source to GitHub before substantial new development. Normal completion checks and both additional review passes remain pending; no 1.11.0 package was produced.

## Completed backups

The earlier campaign source checkpoint is GitHub commit `c391aa13431fe7ae58d6771067e245e3c39c190b`. All 1,189 provenance-listed checkpoint files match their recorded hashes. A separate local source/recovery backup contains 60,531 files; SHA-256 `75b1b4cb48cd7888a364f62dc2c2ad7e19c4e43e927db0938d4fcc5f9f1c93ee`. This is a source/text backup, not a duplicate of all original raw assets. Original raw asset files and attachments remain preserved in place; the full released runtime is also retained in the verified recovered ISO. All 388 original local ZIPs passed CRC inspection. The initial complete filesystem inventory, ZIP member inventories and recovery receipts are preserved alongside this report.

Recovery files in the new workspace are under `/workspace/work/recovery/`; the source backup is `source-and-recovery-backup.zip` and the exact released baseline is `released-1.10.0.iso`. These recovery outputs are not a 1.11.0 release package.
