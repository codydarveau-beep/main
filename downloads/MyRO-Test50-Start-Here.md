# MyRO Test50

[Download the Test50 update](MyRO-Xbox-Test50-Update.zip) (20.5 MiB). Extract it, run `Apply-Update.cmd`, and select the exact Test49 or Test49a `MyRO-Current.iso`. The updater keeps the previous ISO. Load the new `MyRO-Current.iso` in xemu and reset the Xbox.

[Changes, controls and remaining limits](MyRO-Test50-Notes.md). This build adds the remaining nine ordinary second classes for solo testing, recovery fixes, roaming enemies, ground-impact audio, status alignment, the Payon gateway fix, companion/trap rendering and memory work. Party/PvP/WoE and Transcendent completion remain deferred. Read the notes for the specific forging, companion-AI and effect limits.

[Matching native source and licences](MyRO-Xbox-Test50-Source.zip) (21.8 MiB). Each ZIP is under the 32 MiB transfer limit. The source is optional for playing. Source rebuild instructions, frozen save fixtures and exact validation results are included.

Validation: native Xbox build, 55 ASan/UBSan suites, 1,629 HUD cases, the real nxdk unsupported-math guard, source animation comparisons, memory-cache checks and actual PowerShell update/rollback/failure tests. xemu/physical Xbox playback remains to be checked in play.

Test50 writes Save50, with read-only import of a valid previous Save48 character. [SHA256/update manifest](MyRO-Test50-Manifest.json).
