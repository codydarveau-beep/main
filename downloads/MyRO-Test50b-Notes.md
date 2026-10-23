# Test50b — equipment navigation and frame timing

Apply this update to the exact Test50a ISO, then load MyRO-Current.iso and reset
xemu. Save50 and the lighter class kits remain compatible. All six disc packs
are reused unchanged. No new asset collection is needed.

Autosave is now a persistent slider on START > Game: OFF,1 min,3 min,5 min,
10 min,15 min or30 min. Left/right changes the setting; the default is1 minute.
Off disables both periodic and checkpoint character saves; manual Save remains
available. When enabled, ordinary travel/service checkpoints still save in
addition to the selected periodic interval. The choice is stored in separate
small global preference files, so changing it never writes character progress.
The preference carries across character loads and future builds. Changes are
written once after releasing the slider or leaving its row.

Equipment slots now follow their drawn two-column layout: up/down move within
the current column; left/right switch columns on the same row. Horizontal
edges stay in their column. Up from the first row or down from the last row
reaches the close header. The compatible-item popup remains a vertical list.

The remaining 20–30 FPS regression is NOT yet conclusively attributed. The
confirmed comparison is Test49a at roughly 60 FPS versus Test50/50a at 20–30,
even across classes/maps. The autosave freeze fix remains in place. The old
per-frame checksum was removed in 50a, but that did not restore the user's FPS.
The new classes alone have not been established as the cause.

This build improves two expensive Xbox memory-access patterns. Audio now mixes
and reads its 4 KiB block in cached CPU memory, then writes the completed block
to write-combining DMA memory once. Sprite uploads likewise compose their pixels
and tint in one cached 64 KiB buffer, then stream a completed upload to GPU
memory. Four-bit-alpha sprites without a tint also skip a redundant pixel loop.
Pixels, timing, audio samples, queue recovery and the Quicken trail are retained.
These are bounded 68 KiB buffers, rather than allocations that grow over time.
These memory patterns also existed before the regression; fixing them does
not establish which change caused the Test49a-to50 FPS loss.

To measure what remains: play normally for at least a few seconds, then press
START and stay on the Game category. The new readout shows the LAST UNPAUSED
average milliseconds per frame for Update, Scene, HUD, GPU/display wait and
Audio. The counters continue to work when ordinary diagnostics are disabled.
The pause menu retains the last play measurements instead of measuring itself.
Audio overlaps the main-thread phases; do not add it to the other numbers.
Please report the FPS and the pause-screen timing values if performance is
still low. This adds no new toggle or gameplay HUD drawing.

Native counters, averaging and printed tenths use integer arithmetic. Existing
save stack guards and nxdk unsupported-math checks remain active. No xemu or
physical Xbox performance measurement has been performed here; restoration to
60 FPS requires the next play test. Test51's equipped-weapon Basic Attack icon
remains queued while this performance problem is investigated.
