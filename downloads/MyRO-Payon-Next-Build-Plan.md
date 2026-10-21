# Test43: Payon expedition and base level99 — awaiting requested source assets

User authorizes Payon, its overland connecting route and Payon Dungeon with all
source-defined enemies BEFORE second jobs. Also explicitly requests base cap99.
Base is frozen Test42; no new gameplay release built during this request turn.
Do not modify/rebuild42. This supersedes previous43/next-batch plans.

Required input / prepared deliverable
/workspace/myro/asset-request43/Payon-Expansion/Collect-Payon-Assets.cmd
Read-only Windows collector prompts for client data.grf root and Hercules root
containing npc/pre-re/{warps,mobs} and db/pre-re/mob_db.conf. Uses real source warp
graph, shortest connected overland route from existing7 maps to Payon, then
Archer Village/pay_arche and pay_dun00..04. No guessed portal coordinates.
Only selected map GAT/GND/RSW + recursively referenced terrain/model textures and
RSM; selected spawn lines and monster DB blocks/SPR/ACT; referenced monster sounds;
selected music if indexed; exact exp_group_db.conf/job_db.conf for level99.
Optional three Merchant BMP icons included if found. Do not recollect broad
asset trees, server configs/accounts or unrelated NPC scripts. GRF precedence
and loose overrides follow existing Reader. Payload ≤24MiB per volume, each ZIP
verified<32MiB,512MiB total raw cap. Send ALL matching Desktop volumes.
Assets.csv per-part hashes, common Report.json maps/routes/monsterIDs/missing/errors
and Route.txt. Complete=false/exit2 for missing required data. Source/license and
fixture tests included. No client writes, install/admin/network/autoupload.
Fixture tests pass real PowerShell wrapper + C#; live Windows archive/GUI unrun.
Reference source job_db full HP/SP arrays already exist; full EXP table missing.

Pending fixes (NOT YET IMPLEMENTED; combine with map expansion after assets)
- Cart final13 world units (corrects previously accepted15).
- Outgoing hit sound fixed20ms; user tested attacks, Double Attack and bolts.
  Remove sound slider; retain multi-hit spacing/non-hit sound behavior.
- Replace its Player row with successful-cast minimum DIAMETER slider, numbered
  world units, proposed16..56 step2/default32. Diameter, not radius. Await user's
  preferred size after release. No final value claimed as authentic.
- Successful white/red circle: keep.6s shrink, slightly slower rotation (proposed
 20% slower), hold final size1.5s (was1s), total2.1s. Adjust preview/event lifetime.
- Select must NOT freeze simulation. Only START explicitly pauses. Continue AI,
  damage/DoTs/regen/cast/effect/sound timers under Select and other non-Start
  menus. Route UI input separately; no unintended movement/skill activations
  from navigation. Preserve active auto-attack when merely opening Select;
  assignment cancellation remains deliberate. Handle player KO/cast finish while
  editing windows. Existing map/camera/controls preserved. Test actual tick path,
  not just paused flag:42 excludes ui.active/menuInput/shop/job from combat_tick.
- Cast blue ticks: screenshot shows wide unticked end zones after prior fix.
  Need equal complete end segments and uniform1px separators spanning full width.
  Keep real cast timing; no invisible margins. Consider near48px dynamically
  sized bar with integer cells rather than forcing46px and big leftover ends.
  Verify whole bar from first fill through completion for all durations/ranks.
- Blue AIMING ring must be continuous raised triangular cross-section: join
  inner bases, outer bases AND apex ridge around whole circumference. Remove
  individual pyramid geometry and simple connecting flat band; a single annular
  peaked strip gives the shape user described (pyramid traced around a circle).
  Retain shimmer; interior +5 percentage points opacity, slightly toward cyan.
  Proposed existing fill alpha12/20/28 ->25/33/41 out of255, color101/234/250.
  Preserve square numerical hit area; prototype geometry clearly identified.
- Thunder Storm currently functional but user dislikes visual fidelity. Keep
  this recorded as unfinished original-effect work, do not call it authentic or
  silently revert the giant LoV-like composite. Don't block exploration on it.
- All other42 checklist items accepted, including practice AI/FireWall, menu
  order/highlights, cart/save fix, glow/callout, target markers and hotbars.
  Do not ask user to repeat exhaustive accepted spell testing.

Expansion scope / implementation constraints
- Append new map IDs; preserve existing0..6. Derive gates/spawns from returned
  source metadata, include normal and boss_monster species, not a handpicked
  substitute selection. Include all five classic Payon Dungeon floors. Interiors
  outside connecting route are not implied by Payon town. Existing NPC art can
  support useful town services; do not collect all NPC families speculatively.
- All source enemy TYPES/spawns collected; advanced original monster/MVP skill
  AI is a separate roadmap item. Include source boss species, distinguish basic
  prototype combat from authentic special mechanics. Audit population counts,
  spawn capacity, monster traits/element/status tables and actual sprite IDs.
- Preserve one-map residency; budget terrain/scenery atlases, geometry and
  monster frames for64MiB shared RAM. Evict stale enemy caches on travel; don't
  let exploring more maps accumulate all decoded sprite families.32 visible
  actors can remain a render budget; don't silently drop source populations.
- Append new compressed map resources to original world.bin when practical.
  Preserve old seven map blobs verbatim. Updater must reuse baseline world
  PREFIX plus actor data; old package helper assumes whole world.bin unchanged
  and must be adapted. New source build must stage matching new resources from
  updated ISO or reproducible received collections; avoid duplicating whole
  worlds/source payload unnecessarily. User receives complete source and exact
  incremental update against42, GitHub, no rollback bundle.
- Expand all WORLD_MAP_COUNT users, pending gates, test travel, portal/memo/save
  map bounds and minimaps. Don't simply change array counts without data.

Base level99 / progression
- Obtain full pre-re FirstClasses Base EXP group (98 transitions), confirm HP/SP
  arrays through index98 for all seven current jobs, safe stat/EXP/HP arithmetic.
- Audit literal20 caps in level controls, class presets, stat refresh, source
  arrays, save validation, level-up hints and skill formulas. Keep Novice job10
  and first-job job50 separate from base99. User did not request second jobs yet.
- Current prototype: stat_budget=12+4*(level-1), stat cap30, custom maxHP baseline
  plus job table deltas. Decide explicitly which progression formulas are source
  backed vs prototype; don't claim full authentic RO balance by changing cap.
  Review stat limits/budget consistency alongside99. No rushed invented growth.
- Old disposable test saves need no migration. If preset/curve schema changes,
  use fresh namespace and retain previous files. Preserve popup preferences in
  new schema; user's workflow accepts fresh characters.
- Verify reaching99 naturally/testtool, no table OOB, correct cap EXP discard,
  save/load at low20/mid/high99 and first-job tier separation.

Next playtest/release checklist
Connected route traversal both directions; Payon/Archer Village/five dungeon
floors; source populations and representative new enemy families; zoning/cache
RAM behavior across repeated outdoor/town/dungeon transitions; level99 growth,
new circle slider/shape/ticks; live Select vs paused START. Native build and
host checks first. No emulator/hardware/FPS/RAM claims without actual testing.

Updated roadmap
Requested Payon expedition + first-job stabilization/base99 -> remaining first-job
mechanics/effects/useful services -> second jobs -> broader equipment/loot/
consumables -> cards/refinement/crafting -> remaining maps/enemies/MVP behavior
-> offline progression/balance/real-hardware polish. AI companions last; no WoE.
