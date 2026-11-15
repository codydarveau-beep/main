# Chapter1 integration status

The current development XBE connects three world scenes. It is not the complete2.0 campaign and is not hardware-tested.

## Current milestone — Chapter 1 world integration and follow prototype, 2026-11-06

User asked to continue the next phase while away, then supplied the Campaign Actors archive. All 14 SPR/ACT files passed manifest byte/SHA checks and were imported into asset-library/campaign-actors200. There is no outstanding collector for this milestone.

Implemented in dev200 (not a public release):

- Four genuine source body/head actors, 288 individually compressed poses, 414,080-byte disc file. Fixed the staging bake's too-high canvas origin; all genuine frames now pass complete head/foot/crop-margin checks in the actual runtime sparse reader. Only current visible poses are held in memory; no entire animation bank or full Combat copy per companion.
- Reviewed reference renders using actual packed South Field ground/scenery and projection.h camera/depth equations. The first candidate was hidden by the church at reverse yaw. Moved the whole encounter to centre1460,2804 and verified all eight45-degree camera angles, native walkability/standing heights, driver route and NPC clearance. These are host renders, not Xbox screenshots. Opening activation is enabled in development and tied to the reviewed actor-pack SHA.
- Three connected world conversations at the camp: rescue, Hald's permanent-career warning/normal-job proof and role review, then explicit companion recruitment. Driver is replaced by Hald at the next scene; parcel disappears after its scene. Actors remain available through the follow-up conversations, instead of disappearing after scene1.1. Current executable dialogue pack is1,401bytes; the36-scene prose pack is still separate preparation.
- Normal career proof reads actual native job identity and normalizes all46 IDs to their advancement families. A campaign-only guard rejects native NPC changes to another committed family before applying job mutation; legitimate promotion/rebirth remains supported. Developer presets retain their separate test path. The ordinary NPC quest code still supplies authentic job requirements. Hald's warning precedes his exam instructions; a declined role leaves it uncommitted.
- Super Novice exception: at Hald's waiting panel, Novice can explicitly review/accept Super Novice intent, then separately confirm a permanent story role. This sets a story exemption only; no class, level, skill rank, item or Zeny grant. The authentic Super Novice quest remains required later. Cancellation/high-Novice/non-Novice denial and controller flow passed tests.
- Roan/Yuufa recruitment is an explicit accept/decline branch. One atomic character record commits both recruit bits and the join proof. Decline/reopen and save/reopen during the welcome cannot duplicate or silently recruit them. Native story progression still requires driver/parcel/job proof; skip never grants physical objectives.
- Added19 authored roster identities, a compact read-only Companions roster, and a three-slot follow prototype. Currently Roan/Yuufa follow only after the accepted Chapter1 join scene. Their existing source idle/walk poses use the same bounded cache; unused scene slots are freed. Follow pauses/death, checks movement collision, catches up after blocked progress, and uses tested clear nearby positions across map changes. No follower attacks, healing, enemy targeting, progression, equipment or behaviour settings have been claimed.
- Tests: source pose reader all288 real frames; two-followers source walk selection/cache release; real combat/source NPC kill observer coexistence and native NPC career guard; scene/controller allthree roles, Super Novice intent and recruitment acceptance/cancellation/reopen; bounded follow and actual packed South Field collision/height traversal (160 steps), safe Prontera re-placement and complete world GPU cleanup. ASAN/UBSAN passes. Latest native Xbox XBE build passes and staged campaign.bin/chapter1.bin match the prepared files. No Xbox/Xemu campaign playthrough has happened here.

Next work: companion combat/skill/target-lifetime and assist adapter, persistent active-party/settings UI, final named companion appearance/career progression, and Chapter2 native quest anchors/scenes. Before any2.0 public package, complete the approved three-stage comedic developer conversion warnings and audited sandbox handling, plus hardware/controller acceptance. Full12-chapter campaign is not complete. No2.0ZIP/ISO has been published.1.9.1 remains the delivered testing build; do not re-release it or request the returned collector again.

## Next acceptance pass

1. Create a fresh normal character in Training Grounds and follow the tracker to Nera, on the eastern side of the South Field crossroads.
2. Check the original NPC/map setup remains intact; rotate through all eight camera angles and approach the camp from either side.
3. Try taking the parcel early, then fight the two Porings. Save after one kill, reload and verify only the remaining encounter enemy is required.
4. Speak with the driver, stay close while he reaches Nera, and recover the parcel. Pausing/death/walking away must not fabricate success.
5. Return to the camp. Hald explains permanent careers before examination instructions. Complete a native first-job quest, return, review and confirm a role. Check promotion/rebirth within that family and reject changing family through native NPCs.
6. Separately test a fresh Novice choosing Super Novice intent: Y review, B reconsider, Y/A accept intent, role review/cancel/confirm. Character remains Novice and normal Super Novice requirements remain in effect.
7. At the camp's final conversation decline recruitment; save/reload and reopen. Accept later, save during the welcome and reload. Both companions join once after that conversation finishes.
8. Check the Companions window, follow around the road, pause/unpause, die/recover and travel to Prontera. No blocked-cell placement, invisible actor interaction, duplicated recruit or retained offscreen pose texture.
9. Measure actual original-Xbox RAM/frame timings with and without the two followers. Host reference renders and compilation do not establish hardware performance.

The next chapter and companion combat/skill/settings systems are still development work. Keep the incomplete campaign out of a final2.0 release package.
