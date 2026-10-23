# MyRO Test50b

[Download the Test50b update](MyRO-Xbox-Test50b-Update.zip) (2.6 MiB). Extract it, run `Apply-Update.cmd`, and select your exact **Test50a** `MyRO-Current.iso`. Load the resulting `MyRO-Current.iso` in xemu and reset the Xbox. Save50 remains compatible.

START > Game now includes an autosave slider: **OFF / 1 / 3 / 5 / 10 / 15 / 30 minutes**. The default is 1 minute. The choice is remembered in small global preference files, independently of character saves. Off disables all automatic character saves, including checkpoints; manual Save remains available. Enabled intervals retain ordinary travel/service checkpoints in addition to the periodic timer.

Equipment navigation follows the drawn two-column layout. Up/down stay in the same column; left/right switch columns on the same row. The compatible-equipment popup remains a vertical list.

The FPS regression from Test49a is still under investigation. Test50b composes audio and sprite pixels in cached CPU buffers before writing to DMA/GPU memory, preserving the original samples and pixels. These improvements do not establish the regression's cause or verify restored FPS. After a few seconds of normal play, **START > Game** shows the last unpaused frame timings for Update, Scene, HUD, GPU/display wait and Audio. If FPS remains low, report those readings along with the FPS. Audio overlaps the main-thread phases.

[Changes and remaining limits](MyRO-Test50b-Notes.md). Validation includes 63 sanitizer suites collectively, 1,642 actual HUD cases, 768 sprite pixel comparisons, 1,152 exact PCM blocks, native Xbox build/stack/math guards, persistent autosave preference tests, clean source rebuild and actual PowerShell update/failure checks. No emulator/hardware FPS measurement has been performed here.

[Optional source and licence files](MyRO-Xbox-Test50b-Source.zip) (21.9 MiB). Only the update ZIP is needed to play. Both ZIPs are under 32 MiB. [Release hashes](MyRO-Test50b-Manifest.json).
