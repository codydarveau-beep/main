# Ragnarok Offline recovery inventory

Recovery source: `myro-test45-download` at `9aeac8c16ddccbe3b4a8a2f359a30402b897ada4`.

## Status

Remote metadata inventory only. Archive bytes have not yet been downloaded, checksummed, opened, or reconstructed. The new execution environment is starting. The previous environment has not been accessed or changed. No implementation or playtest has occurred.

The complete recursive Git tree contains 380 entries (not truncated). The downloads directory lists 321 entries, including two directories. Three source ZIPs are listed: Test50, Test50a and Test50b, with SHA256 sidecars. Test51 lists 54 data chunks; Test52 lists two. Archive contents and completeness remain unverified.

## Release authority

Last released version: 1.10.0. Next target: 1.11.0. The 1.10.0 manifest identifies MyRO-1.10.0-Update.zip, 20418973 bytes, SHA256 `66e40cda55adf906bda6142c743a112b3d9d547ba4a53967b18a728ea821c2b3`. Released target ISO: 1889075200 bytes, SHA256 `b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e`. Manifest says four playable chapters, twelve scenes, 495 public maps, later campaign disabled, and no original Xbox playtest.

## Required recovery sequence

1. Inventory and back up the new workspace before mutation.
2. Download and hash all available source archives, release manifests and recovery instructions; inspect nested archives and asset chunks. Preserve originals separately from extracted working copies.
3. Establish source and asset coverage against the released 1.10.0 manifest before requesting missing files. Older source is not evidence of recovered 1.10.0 source. Collector packages are not evidence their requested assets exist.
4. Checkpoint actually recovered source to GitHub before substantial development.
5. Reconstruct unpublished transport, chronology, fee restrictions and nine regional dispatch quests only from recovered code or user-supplied conversation excerpts; identify uncertainty explicitly.

## Development constraints

Primary target: original Xbox with 64 MB RAM; retain Xemu support. Preserve native job quests, costs and rewards. Exclude online party and WoE content. Keep public story updates spoiler-free. Remaining scope includes twelve campaign chapters, companions, guild improvements, six arcade games, regional side quests and campaign-aware map/NPC access.

Use the established ZIP patch format; 1.11.0 must accept only released 1.10.0 as its baseline. Complete normal checks followed by two additional review passes before packaging. Those passes are pending. Host checks must never be described as Xbox playtests.
