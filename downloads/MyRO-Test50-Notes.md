# Test50 — solo second classes

Adds Assassin, Rogue, Hunter, Bard, Dancer, Priest, Monk, Blacksmith and Alchemist alongside the four existing second classes. First Classes, Second Classes and Transcendent remain separate in Developer testing; the second-class selector scrolls in pages. Pure Party, PvP, WoE and unfinished Transcendent content remain deferred.

## Playing this build

Use START > Testing > Developer testing tools > Class presets to change class. Each preset grants its implemented solo skills and a suitable starter weapon/reagents. The Skills window now shows the current class and inherited skills, plus First Aid; the old Test Kit page is removed. Existing saved shortcuts are retained.

X selects inward toward nearer enemies; Y selects outward. The existing nearest-target control remains available. Monster name labels have no spell-callout exclamation marks.

Select Equipment, choose a slot and press A to open the compatible inventory picker; A equips and closes, B cancels. Assassin's shield destination becomes Off hand: equip a one-handed dagger, sword or axe in the main hand first, then choose another compatible weapon for Off hand. Equipping the same item in both hands requires two copies. Katar attacks use the original Katar poses.

Hunter's Falconry entry opens hire/dismiss controls; class presets include a hired Falcon. Alchemist's Bioethics entry opens the personal Homunculus controls. Call Homunculus consumes an Embryo only when creating a new one. Use A for its actions/skills and X to learn its selected skill; feeding, rest, revival, growth and evolution are persistent. A companion normally attacks your selected target. Follow only disables that automatic attack. Marine Sphere's five-second countdown can be triggered from the same personal controls.

Use a furnace/hammer from Inventory to open Smithing. Pharmacy opens its own recipe list. Each attempt checks its exact materials, tool, guide, SP and available carrying capacity before consuming anything. Required guide books are kept. A failed production roll still consumes the attempt's resources. Tools, materials and supported gear are in the ordinary item shop.

## Fixes and changes

- Monsters can roam and pursue beyond their original spawn region; their home location no longer creates an exploitable combat boundary. Terrain collision and line-of-sight rules remain active.
- Ground spell sounds play at their scheduled impact even when no monster is underneath. Source class sounds are separate from collision sounds; timed multi-hit attacks retain their distinct intervals.
- Natural HP/SP recovery, sitting recovery and the corresponding class passives now use the pre-renewal rules. HP normally requires standing still; SP can recover while walking. Weight, poison, hiding, Fury/Asura, performances and other recovery gates apply. Monk's sitting Spiritual Cadence has its own timer.
- Status attributes stand out on the left; resulting values are bolder and align in columns. The highlight aligns with the selected attribute. New personal buff icons/timers are included.
- Upright actor depth follows the character's height so raised wall geometry does not incorrectly cover its upper body when the feet are in front. Foreground scenery still occludes characters behind it.
- The source-walkable interior of Payon's south gateway is open again; its solid posts remain blocked.
- Ice Wall's grounded bases and spikes face upward. Safety Wall renders its back and front around the character.
- Original second-class sprites, icons, effects, traps, companions and sounds are loaded in bounded caches. Switching class/map releases abandoned allocations after the GPU finishes using them.
- Music streams its encoded track from disc rather than retaining all ten MP3s in RAM. Izlude's encoded track uses 778,971 bytes instead of 9,676,327 for the old all-track allocation, an approximately 8.5 MiB reduction before allocator overhead. The HUD displays **free** RAM. Audio recovery/transition changes are included; actual xemu playback still needs player verification.

## Saves and update

Apply the update to the exact Test49 or Test49a ISO using Apply-Update.cmd. Extract every update part into one folder first. The updater verifies all inputs and retains the previous ISO. Load the resulting MyRO-Current.iso in xemu and reset the Xbox.

Test50 uses E:\MyROOffline\Save50. On first load, it can read and import a valid previous Save48 character without writing to the old save folder. Later Test50 saves stay in Save50. Character persistence now includes expanded skills/items and the personal Homunculus. Practice targets and temporary map effects are session state.

## Limits of this build

This is the solo second-class implementation pass, with these specific remaining limits:

- Guild, Party, PvP, WoE, ensembles requiring two players, other-player-only support and Soul Link prerequisites are deferred. Beast Strafe and Berserk Pitcher remain gated by their unavailable Soul Link requirement.
- Smithing supports the neutral weapon, metal and Pharmacy recipe set. Forged weapon element/star customization and separate named weapon instances are not implemented yet.
- Greed has no separate ground-loot pickup queue because this build already collects supported drops automatically. It does not invent extra drops.
- Plagiarism records an eligible spell actually received and keeps its chosen rank/shortcuts in the save. The current incoming special-spell practice path supplies Fire Bolt; the full original monster spell AI pool is not yet present.
- Homunculus normal attacks are automatic; its active skills are selected manually. Advanced original/scripted companion AI is not included.
- Original art and source timing are used where implemented. STR clips are sampled at 15 Hz and fitted to bounded screen-facing sprite slots; procedural depth, some secondary particles and advanced class-specific visual details still need comparison in play. This is not a claim that every effect matches every original-client camera angle exactly.

Validation uses the actual native headers/readers/render submission functions, host AddressSanitizer/UndefinedBehaviorSanitizer checks, original save fixtures, source animation comparisons, the real nxdk unsupported-math guard and a native Xbox build. These checks do not replace xemu or physical Xbox testing. Exact results accompany the matching source in validation50.json.
