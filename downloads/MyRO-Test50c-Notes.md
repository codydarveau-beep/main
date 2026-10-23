MyRO Test50c

Apply this small update to the exact Test50b MyRO-Current.iso, then load the
resulting ISO and reset xemu. No character reset is required.

Developer travel now works while knocked out. A successful warp restores full
HP/SP at the destination; living characters retain their current HP/SP. Items,
levels, class, learned skills, Zeny and saved settings remain compatible.

Sonic Blow now chains one normal attack followed by seven rapid attack actions,
using the original client action pattern (30 ms per source frame for the last
seven). Eight damage hits retain the reference 200 ms spacing, damage total,
SP requirement and after-cast lock. The original cast sound is retained; eight
existing contact sounds remain tied to the damage hits.

Willow/Elder Willow translucent death fades use their earlier screen-space
depth placement. The standing-character upright depth correction remains in
place. Source pixels and four-bit fade alpha are unchanged. This is a focused
fix to test against the reported large blocks; its appearance still needs an
in-game check. It does not reverse the wall correction or roaming changes.

The FPS investigation remains open. This patch does not claim to restore
60 FPS. Pause > Game timing readings from slow and fast scenes remain useful.

The separate Test51 World Maps collector requests 391 ordinary maps across
14 regions and their direct assets. WoE/guild, Battleground, Event, PvP and
party-only minigames remain excluded. This hotfix does not add those maps.

Validation: native nxdk build and actual stack budget; sanitized real-world
loader/travel checks across all 18 maps including KO travel; Sonic Blow action
chain, 200 ms damage and 20 ms contact-audio offsets; exact standing depth vs
previous projection; integer-only production format guard. No target FPS or
visual verification is claimed. No standalone source archive is prepared.
