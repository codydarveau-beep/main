MYRO TEST47 - TEST46 REVIEW FIXES

Extract the whole ZIP. Run Apply-Update.cmd and select your Test46
MyRO-Current.iso. The updater preserves that original and verifies Test47.
This update requires Test46, not Test45 or Test45a.

Save46 and its character format are unchanged: this update should keep your
Test46 character/location. A fresh Novice is NOT an intended Test47 reset.

FIXES
- All18 maps use their full Test45a terrain again, byte for byte. Black-triangle
  deletion is reverted. Faint void lines are left alone, as requested.
- Restored the original white font, damage digits and critical graphic. New
  equipment art now avoids every runtime font/damage/minimap/palette region.
  LVL UP/Hold, damage and Miss should no longer contain inventory graphics.
- First Aid uses a clean white medical cross on blue instead of the tiny hand.
- Larger readable class/base/job labels, another space before JOB EXP.
- Inventory displays only owned stacks, with the actual matching item IDs for
  tooltips, equip/use and hotbar binding. Empty positions show no zero-stock
  catalog items. Selected item names fit their field and use bold text.
- Equipment slots always show their headers, then the item or (empty).
  Character preview is30% smaller and centered. Wider, cleaner equipment panel.
- Cleaner Status columns: ATK/MATK/DEF/HIT/FLEE/CRIT/ASPD/range/walk pace.
  Decimal values no longer depend on unsupported floating-point text formatting.
  MDEF is marked --: separate player magic defence is not implemented yet.
- Quicken body tint reduced further (half the previous tint strength). Trails
  are untouched. Successful-cast circle and Horong animation are unchanged.
- Broader body-height prop clearance, including larger opaque structures/stalls.
  Source bridge/stair surfaces and portal routes retain priority. Please retest
  Izlude's counter and the other reported objects; this is not an all-props claim.

NEW ENEMY DISPLAY / CONTROLS
R3: immediately select the closest visible enemy.
X: step farther out. Y: step nearer in. They stop at either end rather than wrap.
A: approach/attack the selected enemy. B: cancel, as before.
Selection reaches farther across the visible area. Equal-distance targets favour
attackers, then lower HP. Hidden/dead/off-screen candidates are excluded.

Selected monster name appears below it in a small translucent black callout.
It is the name only: no added !! or spell punctuation.
Current HP plus a space and / is on the first line above the HP bar; maximum HP
is on the next. Both lines use white text with a dark drop shadow and fit the bar.

Original UI/equipment work and remaining spell-effect gaps continue from Test46.
No new assets needed. Full source and validation notes included.
