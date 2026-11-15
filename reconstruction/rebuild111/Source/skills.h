/* SPDX-License-Identifier: MIT. Small skill test kit; simplified RO-like rules. */
#ifndef MYRO_SKILLS_H
#define MYRO_SKILLS_H
#include "expanded_ids60.h"
#include "expanded_ids60.h"
enum { SKILL_ATTACK,SKILL_FIRST_AID,SKILL_BASH,SKILL_FIRE_BOLT,SKILL_HEAVENS_DRIVE,SKILL_BLESSING,SKILL_INCREASE_AGI,SKILL_KYRIE,SKILL_MAGNUM,SKILL_COLD_BOLT,SKILL_HEAL,SKILL_DIVINE,SKILL_DOUBLE,SKILL_ENVENOM,SKILL_DETOX,SKILL_OWL,SKILL_VULTURE,SKILL_STRAFE,SKILL_DISCOUNT,SKILL_OVERCHARGE,SKILL_MAMMONITE,SKILL_LIGHTNING,SKILL_NAPALM,SKILL_SOUL,SKILL_FIREBALL,SKILL_SP_RECOVERY,SKILL_HP_RECOVERY,SKILL_PROVOKE,SKILL_ENDURE,SKILL_FROST_DIVER,SKILL_THUNDERSTORM,SKILL_FIREWALL,SKILL_ARROW_SHOWER,SKILL_ANGELUS,SKILL_DODGE,SKILL_SWORD_MASTERY,SKILL_SIGHT,SKILL_STEAL,SKILL_HIDING,SKILL_CONCENTRATION,SKILL_RUWACH,SKILL_DECREASE_AGI,SKILL_DEMON_BANE,SKILL_SIGNUM,SKILL_MOVING_RECOVERY,SKILL_FATAL_BLOW,SKILL_AUTO_BERSERK,SKILL_BACK_SLIDE,SKILL_SAFETY_WALL,SKILL_STONE_CURSE,SKILL_CURE,SKILL_HOLY_LIGHT,SKILL_TELEPORT,SKILL_PNEUMA,SKILL_WARP_PORTAL,SKILL_AQUA_BENEDICTA,SKILL_FIND_STONE,SKILL_STONE_FLING,SKILL_SAND_ATTACK,SKILL_CHARGE_ARROW,SKILL_ARROW_CRAFT,SKILL_WEIGHT,SKILL_APPRAISAL,SKILL_CART,SKILL_CART_REVOLUTION,SKILL_CHANGE_CART,SKILL_UPROAR,SKILL_ENERGY_COAT,SKILL_TWOHAND,SK43_KN_TWOHANDQUICKEN,SK43_KN_AUTOCOUNTER,SK43_KN_BOWLINGBASH,SK43_KN_CHARGEATK,SK43_WZ_FIREPILLAR,SK43_WZ_SIGHTRASHER,SK43_WZ_METEOR,SK43_WZ_JUPITEL,SK43_WZ_VERMILION,SK43_WZ_WATERBALL,SK43_WZ_FROSTNOVA,SK43_WZ_STORMGUST,SK43_WZ_EARTHSPIKE,SK43_WZ_QUAGMIRE,SK43_WZ_ESTIMATION,SK43_WZ_SIGHTBLASTER,SK43_HW_SOULDRAIN,SK43_HW_MAGICCRASHER,SK43_HW_MAGICPOWER,SK43_HW_NAPALMVULCAN,SK48_WZ_ICEWALL,SK48_SA_ADVANCEDBOOK,SK48_SA_CASTCANCEL,SK48_SA_MAGICROD,SK48_SA_SPELLBREAKER,SK48_SA_FREECAST,SK48_SA_AUTOSPELL,SK48_SA_FLAMELAUNCHER,SK48_SA_FROSTWEAPON,SK48_SA_LIGHTNINGLOADER,SK48_SA_SEISMICWEAPON,SK48_SA_DRAGONOLOGY,SK48_SA_VOLCANO,SK48_SA_DELUGE,SK48_SA_VIOLENTGALE,SK48_SA_LANDPROTECTOR,SK48_SA_DISPELL,SK48_SA_ABRACADABRA,SK48_SA_CREATECON,SK48_SA_ELEMENTWATER,SK48_SA_ELEMENTGROUND,SK48_SA_ELEMENTFIRE,SK48_SA_ELEMENTWIND,SK48_KN_RIDING,SK48_KN_CAVALIERMASTERY,SK48_KN_SPEARMASTERY,SK48_CR_TRUST,SK48_CR_AUTOGUARD,SK48_CR_SHIELDCHARGE,SK48_CR_SHIELDBOOMERANG,SK48_CR_REFLECTSHIELD,SK48_CR_HOLYCROSS,SK48_CR_GRANDCROSS,SK48_CR_DEVOTION,SK48_CR_PROVIDENCE,SK48_CR_DEFENDER,SK48_CR_SPEARQUICKEN,SK48_CR_SHRINK,SK50_AS_RIGHT,SK50_AS_LEFT,SK50_AS_KATAR,SK50_AS_CLOAKING,SK50_AS_SONICBLOW,SK50_AS_GRIMTOOTH,SK50_AS_ENCHANTPOISON,SK50_AS_POISONREACT,SK50_AS_VENOMDUST,SK50_AS_SPLASHER,SK50_AS_SONICACCEL,SK50_AS_VENOMKNIFE,SK50_HT_REMOVETRAP,SK50_RG_SNATCHER,SK50_RG_STEALCOIN,SK50_RG_BACKSTAP,SK50_RG_TUNNELDRIVE,SK50_RG_RAID,SK50_RG_STRIPWEAPON,SK50_RG_STRIPSHIELD,SK50_RG_STRIPARMOR,SK50_RG_STRIPHELM,SK50_RG_INTIMIDATE,SK50_RG_GRAFFITI,SK50_RG_COMPULSION,SK50_RG_PLAGIARISM,SK50_RG_CLOSECONFINE,SK50_HT_SKIDTRAP,SK50_HT_LANDMINE,SK50_HT_ANKLESNARE,SK50_HT_SHOCKWAVE,SK50_HT_SANDMAN,SK50_HT_FLASHER,SK50_HT_FREEZINGTRAP,SK50_HT_BLASTMINE,SK50_HT_CLAYMORETRAP,SK50_HT_TALKIEBOX,SK50_HT_BEASTBANE,SK50_HT_FALCON,SK50_HT_STEELCROW,SK50_HT_BLITZBEAT,SK50_HT_DETECTING,SK50_HT_SPRINGTRAP,SK50_HT_PHANTASMIC,SK50_HT_POWER,SK50_BA_MUSICALLESSON,SK50_BA_MUSICALSTRIKE,SK50_BA_DISSONANCE,SK50_BA_FROSTJOKER,SK50_BD_ADAPTATION,SK50_BD_ENCORE,SK50_BA_PANGVOICE,SK50_DC_DANCINGLESSON,SK50_DC_THROWARROW,SK50_DC_UGLYDANCE,SK50_DC_SCREAM,SK50_DC_DONTFORGETME,SK50_DC_WINKCHARM,SK50_ALL_RESURRECTION,SK50_PR_MACEMASTERY,SK50_PR_IMPOSITIO,SK50_PR_ASPERSIO,SK50_PR_SANCTUARY,SK50_PR_SLOWPOISON,SK50_PR_STRECOVERY,SK50_PR_MAGNIFICAT,SK50_PR_GLORIA,SK50_PR_LEXDIVINA,SK50_PR_TURNUNDEAD,SK50_PR_LEXAETERNA,SK50_PR_MAGNUS,SK50_MO_IRONHAND,SK50_MO_SPIRITSRECOVERY,SK50_MO_CALLSPIRITS,SK50_MO_ABSORBSPIRITS,SK50_MO_TRIPLEATTACK,SK50_MO_BODYRELOCATION,SK50_MO_DODGE,SK50_MO_INVESTIGATE,SK50_MO_FINGEROFFENSIVE,SK50_MO_STEELBODY,SK50_MO_BLADESTOP,SK50_MO_EXPLOSIONSPIRITS,SK50_MO_EXTREMITYFIST,SK50_MO_CHAINCOMBO,SK50_MO_COMBOFINISH,SK50_MO_BALKYOUNG,SK50_BS_IRON,SK50_BS_STEEL,SK50_BS_ENCHANTEDSTONE,SK50_BS_ORIDEOCON,SK50_BS_DAGGER,SK50_BS_SWORD,SK50_BS_TWOHANDSWORD,SK50_BS_AXE,SK50_BS_MACE,SK50_BS_KNUCKLE,SK50_BS_SPEAR,SK50_BS_HILTBINDING,SK50_BS_FINDINGORE,SK50_BS_WEAPONRESEARCH,SK50_BS_REPAIRWEAPON,SK50_BS_SKINTEMPER,SK50_BS_HAMMERFALL,SK50_BS_ADRENALINE,SK50_BS_WEAPONPERFECT,SK50_BS_OVERTHRUST,SK50_BS_MAXIMIZE,SK50_BS_UNFAIRLYTRICK,SK50_BS_GREED,SK50_AM_AXEMASTERY,SK50_AM_LEARNINGPOTION,SK50_AM_PHARMACY,SK50_AM_DEMONSTRATION,SK50_AM_ACIDTERROR,SK50_AM_POTIONPITCHER,SK50_AM_CANNIBALIZE,SK50_AM_SPHEREMINE,SK50_AM_CP_WEAPON,SK50_AM_CP_SHIELD,SK50_AM_CP_ARMOR,SK50_AM_CP_HELM,SK50_AM_BIOETHICS,SK50_AM_CALLHOMUN,SK50_AM_REST,SK50_AM_RESURRECTHOMUN,SK50_AM_BERSERKPITCHER,SKILL_SUPER_PRAYER53=337,SKILL_BASIC54B=338,SKILL_PLAY_DEAD55=339,SKILL_COUNT=445 };
typedef char BindingCapacity50[(SKILL_COUNT<=SKILL_CAP50&&SKILL_CAP50<BIND_ITEM_BASE50&&BIND_ITEM_BASE50+ITEM_COUNT<BIND_EMPTY50)?1:-1];
typedef struct {const char*name;const char*shortName;const char*help;int sp;float cooldown,range,radius;} SkillDef;
static const SkillDef skillDefs[SKILL_COUNT]={
 {"Basic Attack","Attack","Approach and repeatedly punch the selected enemy.",0,0,14,0},
 {"First Aid","Aid","Restore 5 HP. No SP spent at full HP.",3,.8f,0,0},
 {"Bash","Bash","Close physical strike. Fatal Blow adds stun chance to Bash6+.",4,.8f,16,0},
 {"Fire Bolt","Bolt","Fire magic with DEX-scaled casting and rank-based hits/SP.",4,1.2f,160,0},
 {"Heaven's Drive","Earth","Aim on ground, then A to hit a small area.",5,2,140,20},
 {"Blessing","Bless","Raises STR/INT/DEX by the learned skill rank.",4,1,0,0},
 {"Increase AGI","AGI","Costs 15 HP plus SP. Timed AGI/walking buff; learned rank sets bonus.",4,1,0,0},
 {"Kyrie Eleison","Kyrie","Physical barrier: 12-30% maximum HP, 5-10 hits, lasting 120 seconds.",5,2,0,0},
 {"Magnum Break","Magnum","Self-centred fire burst. Learn after Bash rank 5.",8,2,0,40},
 {"Cold Bolt","Cold","Water magic with DEX-scaled casting and rank-based hits/SP.",4,1.2f,160,0},
 {"Heal","Heal","Self-heal. SP cost grows with learned rank; full HP keeps SP.",13,1,0,0},
 {"Divine Protection","Divine","Passive: reduces Undead/Demon damage. Blessing needs rank 5.",0,0,0,0},
 {"Double Attack","Double","Passive: 5% per rank for a double normal Knife hit.",0,0,0,0},
 {"Envenom","Venom","Melee poison strike. Bosses, plants and Poporings resist poison.",12,.8f,16,0},
 {"Detoxify","Detox","Requires Envenom 3. Removes your poison; no effect keeps SP.",10,.8f,0,0},
 {"Owl's Eye","Owl","Passive: +1 DEX per rank, including bow damage.",0,0,0,0},
 {"Vulture's Eye","Vulture","Requires Owl 3. Passive: +1 cell bow range per rank.",0,0,0,0},
 {"Double Strafe","Strafe","Bow required. Two-hit ranged attack; consumes one Arrow.",12,.8f,152,0},
 {"Discount","Discount","Enlarge Weight Limit 3. Passive merchant buy discount.",0,0,0,0},
 {"Overcharge","Overcharge","Requires Discount 3. Passive: improves merchant selling prices.",0,0,0,0},
 {"Mammonite","Mammonite","Melee blow: spends 100 Zeny per rank and 5 SP on success.",5,.8f,16,0},
 {"Lightning Bolt","Lightning","Wind magic; one hit per learned rank, spaced 0.2 seconds apart.",12,1.2f,160,0},
 {"Napalm Beat","Napalm","Ghost splash; damage is divided among enemies near the target.",9,1,160,12},
 {"Soul Strike","Soul","Ghost magic; up to five hits. Requires Napalm Beat 4.",18,1.2f,160,0},
 {"Fire Ball","Fire Ball","Targeted fire splash. Requires Fire Bolt 4; nearby enemies take damage.",25,1.5f,160,24},
 {"SP Recovery","SP Regen","Passive: extra SP every 10 stationary seconds; sitting doubles it.",0,0,0,0},
 {"HP Recovery","HP Regen","Passive: extra HP every 10 stationary seconds; sitting doubles it.",0,0,0,0},
 {"Provoke","Provoke","30s: lower target DEF, raise its ATK and draw aggro. Boss/Undead immune.",4,1,72,0},
 {"Endure","Endure","Avoid physical hit-stagger for seven hits. Duration rises with rank.",10,10,0,0},
 {"Frost Diver","Frost","Cold Bolt 5. Water strike; chance to freeze. Next damaging hit breaks ice.",25,1.5f,72,0},
 {"Thunder Storm","Storm","Lightning Bolt 4. Timed wind strikes every 1.0s in a 5x5-cell area.",29,2.f,72,20},
 {"Fire Wall","Wall","Fire Ball 5. Three-cell flame barrier; contact hits and collision-safe pushback.",40,.65f,72,12},
 {"Arrow Shower","Shower","Double Strafe 5. Bow required; 5x5-cell physical splash and pushback.",15,.8f,72,20},
 {"Angelus","Angelus","Divine Protection 3. Raises VIT defence by 5% per rank for 30 seconds per rank.",23,3.5f,0,0},
 {"Improve Dodge","Dodge","Passive Thief evasion: three FLEE per rank, modeled as +3% dodge chance.",0,0,0,0},
 {"Sword Mastery","Mastery","Passive Swordsman: +4 damage per rank with the equipped Knife.",0,0,0,0},
 {"Sight","Sight","Ten-second reveal aura, three-cell radius. Needed for newly learned Fire Wall.",10,1,0,24},
 {"Steal","Steal","Close attempt to steal supported loot. One success per monster life; failed rolls cost SP.",10,.5f,16,0},
 {"Hiding","Hide","Steal 5. Stay still and evade ordinary monsters. Detectors can see you. B or recast to emerge.",10,.5f,0,0},
 {"Improve Concentration","Concentrate","Vulture 1. Boosts base AGI/DEX by 2+rank percent and reveals nearby hidden enemies once.",25,1,0,24},
 {"Ruwach","Ruwach","Ten-second two-cell reveal aura. Hidden enemies revealed by it take holy magic damage.",10,1,0,16},
 {"Decrease AGI","Slow","Increase AGI 1. Chance to slow a target; bosses resist. No direct damage.",15,1,72,0},
 {"Demon Bane","Bane","Divine Protection 3. Passive normal-attack bonus against Undead and Demons.",0,0,0,0},
 {"Signum Crucis","Signum","Demon Bane 3. Chance to weaken nearby Demon/Undead-element DEF until death.",35,2,0,120},
 {"Moving HP Recovery","Walk Regen","Quest passive: natural HP recovery works at half rate while moving.",0,0,0,0},
 {"Fatal Blow","Fatal Blow","Quest passive: Bash6+ can stun. Chance grows with Bash rank and base level.",0,0,0,0},
 {"Auto Berserk","Berserk","Toggle: below25% HP, raises physical ATK32% and lowers defence55%.",1,.5f,0,0},
 {"Back Sliding","Back Slide","Slide five cells backward without turning. Collision stops the slide.",7,.3f,0,0},
 {"Safety Wall","Safety","Blue Gemstone: one-cell wall blocks rank+1 melee hits; lasts5s/rank.",30,.65f,72,4},
 {"Stone Curse","Stone","Red Gemstone: chance to petrify after5s; damage breaks full stone. Boss/Undead immune.",25,1,16,0},
 {"Cure","Cure","Self-cure Blind, Silence and Confusion. Cannot cast while silenced.",15,1,0,0},
 {"Holy Light","Holy Light","Quest holy magic:125% of current prototype magic power.",15,1,72,0},
 {"Teleport","Teleport","Rank1: random safe spot. Rank2: also return to home. B cancels for free.",10,1,0,0},
 {"Pneuma","Pneuma","Ten-second field blocks ranged physical hits, not melee or magic.",10,.5f,72,12},
 {"Warp Portal","Warp","Choose home or a remembered location. Consumes one Blue Gemstone.",35,1,72,6},
 {"Aqua Benedicta","Aqua","While wading:10 SP and one Empty Bottle produce one Holy Water.",10,.5f,0,0},
 {"Find Stone","Find Stone","Quest: 0.5s base cast,3 SP for one Stone. Damage does not interrupt.",3,.5f,0,0},
 {"Stone Fling","Fling","Consumes one Stone and2 SP. Fixed50 damage; small stun/blind chance.",2,.5f,56,0},
 {"Sand Attack","Sand","Quest:130% Earth physical attack;20% Blind chance.9 SP.",9,.5f,16,0},
 {"Charge Arrow","Charge","Bow + one Arrow:1.5s base cast,150% damage and six-cell knockback. Damage does not interrupt.",15,1.5f,152,0},
 {"Arrow Crafting","Craft","10 SP: choose Jellopy (4 Arrows) or Tree Root (7 Arrows). Cancel is free.",10,.5f,0,0},
 {"Enlarge Weight Limit","Weight","Passive: +200 weight capacity per rank. 50% stops recovery; 90% blocks attacks/skills.",0,0,0,0},
 {"Item Appraisal","Appraise","Identifies one selected piece of unidentified equipment. B cancels freely.",10,.5f,0,0},
 {"Pushcart","Cart","Rent from the Prontera merchant (800 Zeny). This opens owned-cart management; rank reduces slowdown.",0,0,0,0},
 {"Cart Revolution","Cart Rev","Cart required. 12 SP, 150-250% prototype physical splash by cart load, two-cell push.",12,.8f,16,8},
 {"Change Cart","Cart Style","40 SP opens cart style selection; normal skill level requirements apply. Free Cart Stylist can preview all five styles.",40,.5f,0,0},
 {"Crazy Uproar","Uproar","Quest: 8 SP gives +4 STR for 300 seconds; refreshes without stacking.",8,.5f,0,0},
 {"Energy Coat","Coat","Quest: 30 SP, 300 seconds. Physical damage reduced 6-30%; each hit drains SP by current SP band. Fixed five-second prototype cast; movement, B or landed attacks interrupt.",30,.5f,0,0},
 {"Two-Handed Sword Mastery","2H Mastery","Passive: +4 prototype weapon damage per rank with Katana only. Requires Sword Mastery 1.",0,0,0,0},
 {"Twohand Quicken","Quicken","Two-handed attack speed buff.",14,1.0f,0,0},
 {"Counter Attack","Counter","Brief guard counters the next close physical hit.",3,1.0f,0,0},
 {"Bowling Bash","Bowling","Two physical hits around a nearby target; simplified collision.",13,1.0f,24,24},
 {"Charge Attack","Charge","Approach a reachable enemy and strike.",40,1.0f,112,0},
 {"Fire Pillar","Pillar","Persistent fire damage zone; prototype trigger and splash.",75,1.0f,144,20},
 {"Sightrasher","Rasher","Self-centred fire burst; requires Sight.",35,1.0f,0,40},
 {"Meteor Storm","Meteor","Timed fire impacts over a targeted zone; prototype area pattern.",20,1.0f,144,28},
 {"Jupitel Thunder","Jupitel","Wind multi-hit with knockback.",20,1.0f,160,0},
 {"Lord of Vermilion","Vermilion","Repeated wind damage over a ground area.",60,1.0f,144,44},
 {"Water Ball","Waterball","Water multi-hit; requires shallow water.",15,1.0f,160,0},
 {"Frost Nova","Nova","Water burst around caster, with freeze chance.",45,1.0f,0,40},
 {"Storm Gust","Gust","Timed water zone; surviving normal enemies freeze every third hit.",78,1.0f,144,36},
 {"Earth Spike","Spike","Earth multi-hit attack.",12,1.0f,160,0},
 {"Quagmire","Quagmire","Ground zone slows non-boss enemies; prototype stat reduction.",5,1.0f,144,24},
 {"Sense","Estimate","Inspect selected enemy HP, defence and element data.",10,1.0f,160,0},
 {"Sight Blaster","Blaster","One-shot close-range fire defence; prototype trigger.",40,1.0f,0,0},
 {"Soul Drain","SoulDrain","Passive max SP increase; restores SP from magic kills.",0,1.0f,0,0},
 {"Stave Crasher","Crasher","Single magic-powered physical strike.",8,1.0f,160,0},
 {"Mystical Amplification","Amplify","Boosts the next damaging spell; simplified MATK multiplier.",14,1.0f,0,0},
 {"Napalm Vulcan","Vulcan","Ghost splash multi-hit; prototype area distribution.",10,1.0f,160,20},
 {"Ice Wall","Ice Wall","Five-cell Ice Wall blocks movement and sight. Cells lose HP over time.",20,0,72,20},
 {"Study","Study","Passive: books gain 3 ATK and 0.5% attack speed per rank.",0,0,0,0},
 {"Cast Cancel","Cast Cancel","Cancel your current spell; rank reduces the lost casting SP.",2,0,0,0},
 {"Magic Rod","Magic Rod","Briefly catch targeted magic and recover part of its SP cost.",2,0,0,0},
 {"Spell Breaker","Spell Breake","Interrupt a casting enemy. Higher ranks recover SP; bosses resist.",10,0,72,0},
 {"Free Cast","Free Cast","Passive: move and attack while casting, with speed penalties.",0,0,0,0},
 {"Hindsight","Hindsight","Choose a learned spell to trigger on ordinary attacks; procs cost SP.",35,0,0,0},
 {"Endow Blaze","Endow Blaze","Fire endow: consumes Red Blood. Low ranks may damage your weapon.",40,0,72,0},
 {"Endow Tsunami","Endow Tsunam","Water endow: consumes Crystal Blue. Low ranks may damage your weapon.",40,0,72,0},
 {"Endow Tornado","Endow Tornad","Wind endow: consumes Wind of Verdure. Low ranks may damage your weapon.",40,0,72,0},
 {"Endow Quake","Endow Quake","Earth endow: consumes Green Live. Low ranks may damage your weapon.",40,0,72,0},
 {"Dragonology","Dragonology","Passive: raises INT. Dragon-specific bonuses await dragon enemies.",0,0,0,0},
 {"Volcano","Volcano","Fire-enhancing ground field. Consumes a Yellow Gemstone.",48,0,16,28},
 {"Deluge","Deluge","Water-enhancing ground field; supplies Water Ball water. Yellow Gemstone.",48,0,16,28},
 {"Whirlwind","Whirlwind","Wind-enhancing ground field. Consumes a Yellow Gemstone.",48,0,16,28},
 {"Magnetic Earth","Magnetic Ear","Ground magic suppression. Consumes Yellow and Blue Gemstones.",66,0,16,44},
 {"Dispell","Dispell","Chance to remove supported enemy buffs and ailments. Yellow Gemstone.",1,0,72,0},
 {"Hocus-pocus","Hocus-pocus","Two Yellow Gemstones: roll an existing single-player spell. A use; B discard.",50,0,0,0},
 {"Create Elemental Converter","Create Eleme","Create a converter from 3 matching materials and 1 Blank Scroll.",30,0,0,0},
 {"Elemental Change Water","Elemental Ch","Spend a Water Converter to change a non-boss target to Water.",30,0,72,0},
 {"Elemental Change Earth","Elemental Ch","Spend an Earth Converter to change a non-boss target to Earth.",30,0,72,0},
 {"Elemental Change Fire","Elemental Ch","Spend a Fire Converter to change a non-boss target to Fire.",30,0,72,0},
 {"Elemental Change Wind","Elemental Ch","Spend a Wind Converter to change a non-boss target to Wind.",30,0,72,0},
 {"Peco Peco Riding","Peco Peco Ri","Passive: permits a Peco mount. Toggle in Developer Player build.",0,0,0,0},
 {"Cavalier Mastery","Cavalier Mas","Passive: removes the mounted attack speed penalty as rank increases.",0,0,0,0},
 {"Spear Mastery","Spear Master","Passive: spear attack bonus, increased while riding.",0,0,0,0},
 {"Faith","Faith","Passive: +200 maximum HP per rank and holy resistance.",0,0,0,0},
 {"Guard","Guard","Shield required. Toggle chance to block physical attacks.",12,0,0,0},
 {"Smite","Smite","Shield strike with knockback and a chance to stun.",10,0,24,0},
 {"Shield Boomerang","Shield Boome","Throw the equipped shield at a distant enemy. Shield weight adds damage.",12,0,24,0},
 {"Shield Reflect","Shield Refle","Shield required. Return part of melee damage to the attacker.",35,0,0,0},
 {"Holy Cross","Holy Cross","Two-hit Holy weapon strike; may blind the target.",11,0,0,0},
 {"Grand Cross","Grand Cross","Three Holy cross pulses. Consumes HP and also harms the caster.",37,0,40,24},
 {"Sacrifice","Sacrifice","CR_DEVOTION: Sacrifice. Source pre-renewal rank and costs.",25,0,56,0},
 {"Resistant Souls","Resistant So","CR_PROVIDENCE: Resistant Souls. Source pre-renewal rank and costs.",30,0,72,0},
 {"Defending Aura","Defending Au","Shield required. Reduce ranged physical damage; movement slows.",30,0,0,0},
 {"Spear Quicken","Spear Quicke","Two-handed spear required. Temporarily increase attack speed.",24,0,0,0},
 {"Shrink","Shrink","Toggle knockback on successful Guard blocks.",15,0,0,0},
 {"Righthand Mastery","Righthand Ma","Righthand Mastery.",0,0,0,0},
 {"Lefthand Mastery","Lefthand Mas","Lefthand Mastery.",0,0,0,0},
 {"Katar Mastery","Katar Master","Katar Mastery.",0,0,0,0},
 {"Cloaking","Cloaking","Cloaking.",15,0,0,0},
 {"Sonic Blow","Sonic Blow","Sonic Blow.",16,0,8,0},
 {"Grimtooth","Grimtooth","Grimtooth.",3,0,24,0},
 {"Enchant Poison","Enchant Pois","Enchant Poison.",20,0,8,0},
 {"Poison React","Poison React","Poison React.",25,0,0,0},
 {"Venom Dust","Venom Dust","Venom Dust.",20,0,16,4},
 {"Venom Splasher","Venom Splash","Venom Splasher.",12,0,8,0},
 {"Sonic Acceleration","Sonic Accele","Sonic Acceleration.",0,0,0,0},
 {"Throw Venom Knife","Throw Venom ","Throw Venom Knife.",15,0,72,0},
 {"Remove Trap","Remove Trap","Remove Trap.",5,0,16,0},
 {"Gank","Gank","Gank.",0,0,0,0},
 {"Mug","Mug","Mug.",15,0,8,0},
 {"Back Stab","Back Stab","Back Stab.",16,0,0,0},
 {"Stalk","Stalk","Stalk.",0,0,0,0},
 {"Sightless Mind","Sightless Mi","Sightless Mind.",20,0,0,0},
 {"Divest Weapon","Divest Weapo","Divest Weapon.",17,0,8,0},
 {"Divest Shield","Divest Shiel","Divest Shield.",12,0,8,0},
 {"Divest Armor","Divest Armor","Divest Armor.",17,0,8,0},
 {"Divest Helm","Divest Helm","Divest Helm.",12,0,8,0},
 {"Snatch","Snatch","Snatch.",13,0,8,0},
 {"Scribble","Scribble","Scribble.",15,0,8,4},
 {"Haggle","Haggle","Haggle.",0,0,0,0},
 {"Intimidate","Intimidate","Intimidate.",0,0,0,0},
 {"Close Confine","Close Confin","Close Confine.",25,0,8,0},
 {"Skid Trap","Skid Trap","Skid Trap.",10,0,24,4},
 {"Land Mine","Land Mine","Land Mine.",10,0,24,12},
 {"Ankle Snare","Ankle Snare","Ankle Snare.",12,0,24,4},
 {"Shockwave Trap","Shockwave Tr","Shockwave Trap.",45,0,24,12},
 {"Sandman","Sandman","Sandman.",12,0,24,20},
 {"Flasher","Flasher","Flasher.",12,0,24,12},
 {"Freezing Trap","Freezing Tra","Freezing Trap.",10,0,24,12},
 {"Blast Mine","Blast Mine","Blast Mine.",10,0,24,12},
 {"Claymore Trap","Claymore Tra","Claymore Trap.",15,0,24,20},
 {"Talkie Box","Talkie Box","Talkie Box.",1,0,24,4},
 {"Beast Bane","Beast Bane","Beast Bane.",0,0,0,0},
 {"Falconry Mastery","Falconry Mas","Falconry Mastery.",0,0,0,0},
 {"Steel Crow","Steel Crow","Steel Crow.",0,0,0,0},
 {"Blitz Beat","Blitz Beat","Blitz Beat.",10,0,40,0},
 {"Detect","Detect","Detect.",8,0,24,28},
 {"Spring Trap","Spring Trap","Spring Trap.",10,0,32,0},
 {"Phantasmic Arrow","Phantasmic A","Phantasmic Arrow.",10,0,0,0},
 {"Beast Strafing","Beast Strafi","Beast Strafing.",12,0,0,0},
 {"Music Lessons","Music Lesson","Music Lessons.",0,0,0,0},
 {"Melody Strike","Melody Strik","Melody Strike.",1,0,72,0},
 {"Unchained Serenade","Unchained Se","Unchained Serenade.",18,0,0,0},
 {"Unbarring Octave","Unbarring Oc","Unbarring Octave.",12,0,0,0},
 {"Amp","Amp","Amp.",1,0,0,0},
 {"Encore","Encore","Encore.",1,0,0,0},
 {"Pang Voice","Pang Voice","Pang Voice.",20,0,72,0},
 {"Dance Lessons","Dance Lesson","Dance Lessons.",0,0,0,0},
 {"Slinging Arrow","Slinging Arr","Slinging Arrow.",1,0,72,0},
 {"Hip Shaker","Hip Shaker","Hip Shaker.",23,0,0,0},
 {"Dazzler","Dazzler","Dazzler.",12,0,0,0},
 {"Slow Grace","Slow Grace","Slow Grace.",28,0,0,0},
 {"Wink of Charm","Wink of Char","Wink of Charm.",40,0,72,0},
 {"Resurrection","Resurrection","Resurrection.",60,0,72,0},
 {"Mace Mastery","Mace Mastery","Mace Mastery.",0,0,0,0},
 {"Impositio Manus","Impositio Ma","Impositio Manus.",13,0,72,0},
 {"Aspersio","Aspersio","Aspersio.",14,0,72,0},
 {"Sanctuary","Sanctuary","Sanctuary.",15,0,72,4},
 {"Slow Poison","Slow Poison","Slow Poison.",6,0,72,0},
 {"Status Recovery","Status Recov","Status Recovery.",5,0,72,0},
 {"Magnificat","Magnificat","Magnificat.",40,0,0,0},
 {"Gloria","Gloria","Gloria.",20,0,0,0},
 {"Lex Divina","Lex Divina","Lex Divina.",20,0,40,0},
 {"Turn Undead","Turn Undead","Turn Undead.",20,0,40,0},
 {"Lex Aeterna","Lex Aeterna","Lex Aeterna.",10,0,72,0},
 {"Magnus Exorcismus","Magnus Exorc","Magnus Exorcismus.",40,0,72,4},
 {"Iron Fists","Iron Fists","Iron Fists.",0,0,0,0},
 {"Spiritual Cadence","Spiritual Ca","Spiritual Cadence.",0,0,0,0},
 {"Summon Spirit Sphere","Summon Spiri","Summon Spirit Sphere.",8,0,0,0},
 {"Absorb Spirit Sphere","Absorb Spiri","Absorb Spirit Sphere.",5,0,72,0},
 {"Raging Trifecta Blow","Raging Trife","Raging Trifecta Blow.",0,0,0,0},
 {"Snap","Snap","Snap.",14,0,144,4},
 {"Dodge","Dodge","Dodge.",0,0,0,0},
 {"Occult Impaction","Occult Impac","Occult Impaction.",10,0,16,0},
 {"Throw Spirit Sphere","Throw Spirit","Throw Spirit Sphere.",10,0,72,0},
 {"Mental Strength","Mental Stren","Mental Strength.",200,0,0,0},
 {"Root","Root","Root.",10,0,0,0},
 {"Fury","Fury","Fury.",15,0,0,0},
 {"Asura Strike","Asura Strike","Asura Strike.",1,0,0,0},
 {"Raging Quadruple Blow","Raging Quadr","Raging Quadruple Blow.",11,0,0,0},
 {"Raging Thrust","Raging Thrus","Raging Thrust.",11,0,0,0},
 {"Ki Explosion","Ki Explosion","Ki Explosion.",20,0,0,0},
 {"Iron Tempering","Iron Temperi","Iron Tempering.",0,0,0,0},
 {"Steel Tempering","Steel Temper","Steel Tempering.",0,0,0,0},
 {"Enchanted Stone Craft","Enchanted St","Enchanted Stone Craft.",0,0,0,0},
 {"Oridecon Research","Oridecon Res","Oridecon Research.",0,0,0,0},
 {"Smith Dagger","Smith Dagger","Smith Dagger.",0,0,0,0},
 {"Smith Sword","Smith Sword","Smith Sword.",0,0,0,0},
 {"Smith Two-handed Sword","Smith Two-ha","Smith Two-handed Sword.",0,0,0,0},
 {"Smith Axe","Smith Axe","Smith Axe.",0,0,0,0},
 {"Smith Mace","Smith Mace","Smith Mace.",0,0,0,0},
 {"Smith Knucklebrace","Smith Knuckl","Smith Knucklebrace.",0,0,0,0},
 {"Smith Spear","Smith Spear","Smith Spear.",0,0,0,0},
 {"Hilt Binding","Hilt Binding","Hilt Binding.",0,0,0,0},
 {"Ore Discovery","Ore Discover","Ore Discovery.",0,0,0,0},
 {"Weaponry Research","Weaponry Res","Weaponry Research.",0,0,0,0},
 {"Weapon Repair","Weapon Repai","Weapon Repair.",30,0,16,0},
 {"Skin Tempering","Skin Temperi","Skin Tempering.",0,0,0,0},
 {"Hammer Fall","Hammer Fall","Hammer Fall.",10,0,8,20},
 {"Adrenaline Rush","Adrenaline R","Adrenaline Rush.",20,0,0,0},
 {"Weapon Perfection","Weapon Perfe","Weapon Perfection.",18,0,0,0},
 {"Power-Thrust","Power-Thrust","Power-Thrust.",18,0,0,0},
 {"Maximize Power","Maximize Pow","Maximize Power.",10,0,0,0},
 {"Unfair Trick","Unfair Trick","Unfair Trick.",0,0,0,0},
 {"Greed","Greed","Greed.",10,0,0,0},
 {"Axe Mastery","Axe Mastery","Axe Mastery.",0,0,0,0},
 {"Potion Research","Potion Resea","Potion Research.",0,0,0,0},
 {"Prepare Potion","Prepare Poti","Prepare Potion.",5,0,0,0},
 {"Bomb","Bomb","Bomb.",10,0,72,4},
 {"Acid Terror","Acid Terror","Acid Terror.",15,0,72,0},
 {"Aid Potion","Aid Potion","Aid Potion.",1,0,72,0},
 {"Summon Flora","Summon Flora","Summon Flora.",20,0,32,4},
 {"Summon Marine Sphere","Summon Marin","Summon Marine Sphere.",10,0,8,4},
 {"Alchemical Weapon","Alchemical W","Alchemical Weapon.",30,0,8,0},
 {"Synthesized Shield","Synthesized ","Synthesized Shield.",25,0,8,0},
 {"Synthetic Armor","Synthetic Ar","Synthetic Armor.",25,0,8,0},
 {"Biochemical Helm","Biochemical ","Biochemical Helm.",25,0,8,0},
 {"Bioethics","Bioethics","Bioethics.",0,0,0,0},
 {"Call Homunculus","Call Homuncu","Call Homunculus.",10,0,0,0},
 {"Vaporize","Vaporize","Vaporize.",50,0,0,0},
 {"Homunculus Resurrection","Homunculus R","Homunculus Resurrection.",74,0,72,0},
 {"Aid Berserk Potion","Aid Berserk ","Aid Berserk Potion.",10,0,72,0},
 {"Aura Blade","Aura Blade","Adds fixed damage after enemy defence while using a sword.",18,0,0,0},
 {"Parrying","Parrying","Parries physical blows while a two-handed sword is equipped.",50,0,0,0},
 {"Concentration","Concentration","Raises attack and accuracy, lowers defence, and grants Endure.",14,0,0,0},
 {"Relax","Relax","Sit to recover HP faster; ends when you stand.",15,0,0,0},
 {"Frenzy","Frenzy","Triples maximum HP and boosts combat power; blocks skills and items.",200,0,0,0},
 {"Spiral Pierce","Spiral Pierce","Five spear strikes based on weapon weight; briefly pins the target.",18,0,40,0},
 {"Traumatic Blow","Traumatic Blow","A physical strike with a chance to cause bleeding.",23,0,32,0},
 {"Vital Strike","Vital Strike","A spear strike that can injure an enemy joint.",12,0,32,0},
 {"Gloria Domini","Gloria Domini","Fixed holy damage that also drains the target SP.",30,0,72,0},
 {"Martyr's Reckoning","Martyr's Reckon","The next five normal attacks spend HP to deal HP-based damage.",100,0,0,0},
 {"Battle Chant","Battle Chant","Remain still to maintain Gospel and affect nearby enemies.",80,0,0,0},
 {"Shield Chain","Shield Chain","Launches five strikes using shield weight and refinement.",28,0,40,0},
 {"Ganbantein","Ganbantein","Attempts to remove nearby ground effects; consumes two gemstones.",40,0,128,8},
 {"Gravitation Field","Gravitation Fie","Remain still to maintain a damaging field that slows enemies.",20,0,144,0},
 {"Indulge","Indulge","Converts a portion of HP into SP.",1,0,0,0},
 {"Soul Exhale","Soul Exhale","Recovers SP once from each monster.",5,0,72,0},
 {"Soul Siphon","Soul Siphon","Attempts to burn enemy SP; failure can burn your own SP.",80,0,72,0},
 {"Mind Breaker","Mind Breaker","Lowers enemy magic defence while increasing its magic attack.",12,0,72,0},
 {"Foresight","Foresight","Halves the cast time of your next five spells.",1,0,0,0},
 {"Blinding Mist","Blinding Mist","Places fog that blinds enemies and protects against ranged attacks.",25,0,72,0},
 {"Fiber Lock","Fiber Lock","Roots an enemy in a web; fire breaks it and gains extra damage.",50,0,56,0},
 {"Double Casting","Double Casting","Chance to repeat Fire, Cold and Lightning Bolt casts.",40,0,0,0},
 {"Assumptio","Assumptio","Halves incoming monster damage; cannot coexist with Kyrie.",20,0,72,8},
 {"Basilica","Basilica","Remain still inside a protected area that excludes ordinary monsters.",80,0,32,0},
 {"Meditatio","Meditatio","Improves maximum SP, SP recovery and Heal.",0,0,0,0},
 {"Mana Recharge","Mana Recharge","Reduces the SP cost of skills.",0,0,0,0},
 {"Raging Palm Strike","Raging Palm Str","A close-range blow with a delayed impact and knockback.",2,0,0,0},
 {"Glacier Fist","Glacier Fist","Follow a combo finisher with a strike that roots the enemy.",4,0,0,0},
 {"Chain Crush Combo","Chain Crush Com","Continues a combo with multiple rhythmic strikes.",4,0,0,0},
 {"Zen","Zen","Summons five Spirit Spheres.",20,0,0,0},
 {"Advanced Katar Mastery","Advanced Katar ","Improves damage while using a Katar.",0,0,0,0},
 {"Enchant Deadly Poison","Enchant Deadly ","Consumes a Poison Bottle to empower weapon attacks.",60,0,0,0},
 {"Soul Destroyer","Soul Destroyer","A ranged attack combining physical damage and intelligence.",20,0,56,0},
 {"Meteor Assault","Meteor Assault","Strikes nearby enemies and may inflict ailments.",10,0,0,16},
 {"Create Deadly Poison","Create Deadly P","Creates a Poison Bottle from its required ingredients.",50,0,0,0},
 {"Stealth","Stealth","Move while hidden, spending SP periodically; cancel to act.",10,0,0,0},
 {"Counter Instinct","Counter Instinc","Reflects up to three incoming sword attacks.",10,0,0,0},
 {"Preserve","Preserve","Protects the currently copied skill from replacement.",30,0,0,0},
 {"Divest All","Divest All","Attempts to disable an enemy weapon, armour, shield and helm.",22,0,8,0},
 {"Falcon Eyes","Falcon Eyes","Raises all six stats, accuracy, critical chance and damage.",20,0,0,0},
 {"Falcon Assault","Falcon Assault","A powerful single Falcon strike.",30,0,40,0},
 {"Focused Arrow Strike","Focused Arrow S","A precise arrow that pierces enemies along a line.",18,0,72,8},
 {"Wind Walker","Wind Walker","Raises movement speed and evasion.",46,0,0,0},
 {"Vulcan Arrow","Vulcan Arrow","Nine rapid strikes using an instrument or whip.",12,0,72,0},
 {"Sheltering Bliss","Sheltering Blis","Original Transcendent skill. Solo mechanics integration in progress.",30,0,0,24},
 {"Marionette Control","Marionette Cont","Original Transcendent skill. Solo mechanics integration in progress.",100,0,8,0},
 {"Longing for Freedom","Longing for Fre","Original Transcendent skill. Solo mechanics integration in progress.",15,0,0,0},
 {"Wand of Hermode","Wand of Hermode","Original Transcendent skill. Solo mechanics integration in progress.",20,0,0,8},
 {"Tarot Card of Fate","Tarot Card of F","Attempts to draw a Tarot card with a random effect on the target.",40,0,72,0},
 {"Shattering Strike","Shattering Stri","Normal attacks may damage enemy weapon or armour.",50,0,0,0},
 {"Cart Boost","Cart Boost","Briefly increases movement speed while using a cart.",20,0,0,0},
 {"Upgrade Weapon","Upgrade Weapon","Select a weapon to refine using ore; failure destroys it.",5,0,0,0},
 {"Cart Termination","Cart Terminatio","A cart strike whose power depends on cart weight; may stun.",15,0,0,0},
 {"Maximum Power Thrust","Maximum Power T","Spend Zeny to greatly increase weapon damage.",15,0,0,0},
 {"Aid Condensed Potion","Aid Condensed P","Throw a condensed potion to heal within a small area.",30,0,24,24},
 {"Full Protection","Full Protection","Protects equipped weapon, armour, shield and helm.",40,0,8,0},
 {"Acid Demonstration","Acid Demonstrat","Repeated acid damage based on intelligence and enemy vitality.",30,0,72,0},
 {"Plant Cultivation","Plant Cultivati","Attempts to cultivate a mushroom or plant on clear ground.",10,0,8,0},
 {"Pierce","Pierce","A spear thrust with more hits against larger enemies.",7,0,0,0},
 {"Spear Stab","Spear Stab","Stabs and pushes enemies along a line.",9,0,0,0},
 {"Spear Boomerang","Spear Boomerang","Throws a spear at a distant enemy.",10,0,24,0},
 {"Brandish Spear","Brandish Spear","Sweeps a mounted spear across a widening area.",12,0,0,0},
#include "gear_skill_defs52.inc"
 [338]={"Basic Skill","Basic Skill","Novice fundamentals. Learn rank 9 before changing to a first job.",0,0,0,0},
 [337]={"Angel Prayer","Prayer","Super Novice: recite four prayer lines at exactly10%,20%,...90% base EXP to gain Fury (+50 critical).",0,0,0,0},
 [339]={"Play Dead","Play Dead","Pretend to be dead until used again. Enemies ignore you; movement, other skills and natural HP/SP recovery stop. Novice classes only.",5,0,0,0},
#include "expanded_skill_defs60.inc"
};
/* A stable catalog: internal IDs/rank slots never move when trees expand. */
static const uint16_t learnIds[LEARN_COUNT]={2,8,3,9,10,11,5,6,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,4,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,7,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,302,303,304,305,306,307,308,309,310,311,312,313,314,315,338,1,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,317,385,386,387,388,389,390,391,392,393,394,395,396,398,318,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,416,433,434,435,436,437,438,439,440,441,442,443};
static const unsigned char learnJobs[LEARN_COUNT]={1,1,2,2,3,3,3,3,4,4,4,5,5,5,6,6,6,2,2,2,2,2,1,1,1,2,2,2,5,3,4,1,2,4,4,5,3,3,3,3,1,1,1,4,2,2,3,3,3,3,3,3,4,4,4,5,5,6,6,6,6,6,6,2,1,7,7,7,7,9,9,9,9,9,9,9,9,9,9,9,9,8,8,8,8,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,17,21,21,21,21,21,21,21,21,22,22,22,22,8,8,23,23,23,23,23,23,23,23,24,24,24,24,25,25,25,25,26,26,26,26,26,27,27,27,27,28,28,28,28,29,29,31,31,31,31,31,32,32,32,32,7,7,7,7,0,0,0,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,45,45,45,45,45,45,45,45,45,45,45};
static const unsigned char learnMax[LEARN_COUNT]={10,10,10,10,10,10,10,10,10,10,1,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,1,10,10,10,1,10,10,10,1,1,1,1,10,10,1,1,2,1,4,1,1,1,1,1,1,10,1,10,1,1,1,1,10,10,5,10,1,10,10,10,10,10,5,10,10,5,5,1,1,10,1,10,5,5,10,10,5,5,5,10,10,5,5,5,5,5,5,5,5,5,5,10,1,1,1,1,1,1,5,10,10,10,5,5,10,10,10,5,5,5,10,1,5,5,10,10,10,5,10,10,10,10,1,1,1,10,10,10,5,5,5,5,5,5,5,1,5,10,1,5,5,5,5,5,5,5,5,5,1,10,1,10,5,4,5,1,1,10,5,5,5,1,1,1,10,5,5,5,10,1,4,10,5,5,10,4,1,5,5,10,10,1,10,10,5,5,1,10,1,10,5,5,5,5,5,5,5,5,1,5,5,5,5,3,3,3,3,3,3,3,1,1,10,1,5,5,5,5,5,5,1,1,10,10,10,5,5,5,5,5,5,5,5,5,1,1,1,5,1,10,5,10,5,1,1,5,5,10,5,5,10,5,1,5,5,1,5,5,1,1,1,5,5,5,10,5,5,5,10,1,5,5,10,10,1,5,5,1,5,10,5,5,10,10,5,10,1,10,10,5,10,5,10,2,10,10,5,10,9,1,1,10,10,5,5,10,5,10,5,5,5,10,10,10,10,5,10,10,5,10,5,5,5,10,5,1,1,1,1,1,1,1,1,10,10,10,10,5,5,10,10,10,10,10,10,10,10,1,7,1,7,1,7,1,7,1,7,10,10,7,5,1,3,3,3,3,4,4,4,3,3,3,3,5,5,5,10,10,7,7,3,7,7,7,7,10,7,3,3};
static const uint16_t learnNeeds[LEARN_COUNT]={0,2,0,0,0,0,11,10,0,0,13,0,15,0,61,18,0,0,0,22,3,0,0,0,27,9,21,24,17,11,0,0,0,0,37,16,0,6,11,42,0,0,0,0,23,0,10,0,40,54,52,0,0,0,0,0,0,0,0,61,0,0,0,0,35,68,68,69,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,81,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const unsigned char learnNeedsRank[LEARN_COUNT]={0,5,0,0,0,0,5,3,0,0,3,0,3,0,3,3,0,0,0,4,4,0,0,0,5,5,4,5,5,3,0,0,0,0,5,1,0,1,3,3,0,0,0,0,5,0,2,0,1,4,2,0,0,0,0,0,0,0,0,5,0,0,0,0,1,1,1,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int skill_passive(unsigned id){if(id==338)return 1;if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&d->passive;}return id==90||id==94||id==100||id==112||id==113||id==114||id==115||id==85||id==61||id==68||id==11||id==12||id==15||id==16||id==18||id==19||id==25||id==26||id==34||id==35||id==42||id==44||id==45;}
static int skill_rank_index(unsigned id){for(int i=0;i<LEARN_COUNT;i++)if(learnIds[i]==id)return i;return -1;}
static int skill_rank(const Combat*g,unsigned id){if(id==337)return g->jobId==J52_SUPER_NOVICE?1:0;if(job_parent52(g->jobId)==13&&g->persistent50.copySkill==id&&g->persistent50.copyRank){int k=skill_rank_index(id),use=k>=0?g->useRanks45[k]:0;return use>0&&use<(int)g->persistent50.copyRank?use:g->persistent50.copyRank;}if(g->hocusID48==(int)id&&g->hocusRank48)return g->hocusRank48;int k=skill_rank_index(id),learned=k>=0&&g->ranks[k]?g->ranks[k]:id==0?1:0;if(id<SKILL_COUNT&&g->itemBonuses52.grant[id]>learned)learned=g->itemBonuses52.grant[id];if(!learned)return 0;int chosen=k>=0&&!skill_passive(id)?g->useRanks45[k]:0;return chosen>0&&chosen<learned?chosen:learned;}
static int skill_choose_rank45(Combat*g,unsigned id,int delta){int k=skill_rank_index(id);int maximum=job_parent52(g->jobId)==13&&g->persistent50.copySkill==id?g->persistent50.copyRank:k>=0?g->ranks[k]:0;if(id<SKILL_COUNT&&g->itemBonuses52.grant[id]>maximum)maximum=g->itemBonuses52.grant[id];if(k<0||!maximum||skill_passive(id))return 0;int rank=skill_rank(g,id)+delta;if(rank<1)rank=1;if(rank>maximum)rank=maximum;g->useRanks45[k]=rank==maximum?0:rank;return rank;}
static unsigned class_count(const Combat*g){unsigned n=0+(g->jobId==J52_SUPER_NOVICE)+(job_parent52(g->jobId)==13&&g->persistent50.copySkill?1:0);for(int k=0;k<LEARN_COUNT;k++)if(job_owns_skill48(g->jobId,learnJobs[k],learnIds[k]))n++;for(unsigned id=1;id<SKILL_COUNT;id++)if(g->itemBonuses52.grant[id]){int k=skill_rank_index(id);if((k<0||!job_owns_skill48(g->jobId,learnJobs[k],id))&&g->persistent50.copySkill!=id)n++;}return n;}
static int class_inherited49(const Combat*g,int owner){if(g->jobId>=12&&g->jobId<=20)return owner==classParent50[g->jobId-12];return (g->jobId==7||job_parent52(g->jobId)==11)?owner==1:(g->jobId==8)?owner==2||owner==9:(g->jobId==9||job_parent52(g->jobId)==10)?owner==2:0;}
static unsigned class_skill(const Combat*g,int choice){for(int pass=0;pass<2;pass++)for(int k=0;k<LEARN_COUNT;k++)if(job_owns_skill48(g->jobId,learnJobs[k],learnIds[k])&&class_inherited49(g,learnJobs[k])==pass&&choice--==0)return learnIds[k];if(job_parent52(g->jobId)==13&&g->persistent50.copySkill){if(!choice)return g->persistent50.copySkill;choice--;}for(unsigned id=1;id<SKILL_COUNT;id++)if(g->itemBonuses52.grant[id]){int k=skill_rank_index(id);if((k<0||!job_owns_skill48(g->jobId,learnJobs[k],id))&&g->persistent50.copySkill!=id&&choice--==0)return id;}if(g->jobId==J52_SUPER_NOVICE){if(!choice)return 337;choice--;}return 0;}

#include "class_copy50.h"
static int skill_quest(unsigned id){if(id==339)return 1;if(id==1)return 1;if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&d->quest;}return id==107||id==108||id==109||id==110||id==111||id==126||id>=44&&id<=47||id==51||id>=56&&id<=60||id>=64&&id<=67;}
#include "class_prereqs48.h"
#include "expanded_prereqs60.h"
static const uint16_t*trans_missing_prereq52(unsigned job,unsigned id,const unsigned char*r){for(unsigned i=0;i<sizeof(expandedPrereqs60)/sizeof(*expandedPrereqs60);i++){const uint16_t*p=expandedPrereqs60[i];if((p[0]==job||p[0]==J60_TAEKWON&&(job==J60_STAR_GLADIATOR||job==J60_SOUL_LINKER))&&p[1]==id){int k=skill_rank_index(p[2]);if(k<0||r[k]<p[3])return p;}}if(job==J52_SUPER_NOVICE){static uint16_t missing[4];for(unsigned i=0;i<sizeof(superNeeds53)/sizeof(*superNeeds53);i++){const uint16_t*p=superNeeds53[i];int k=skill_rank_index(p[1]);if(p[0]==id&&(k<0||r[k]<p[2])){missing[0]=job;missing[1]=id;missing[2]=p[1];missing[3]=p[2];return missing;}}}for(unsigned n=0;n<sizeof(transPrereqs52)/sizeof(*transPrereqs52);n++){const uint16_t*p=transPrereqs52[n];if(p[0]!=job||p[1]!=id)continue;int k=skill_rank_index(p[2]);if(k<0||r[k]<p[3])return p;}return NULL;}
static int skill_prereqs_for48(const unsigned char*r,unsigned job){if(job_parent52(job)!=17&&r[44]&&r[18]<7)return 0;for(int k=0;k<LEARN_COUNT;k++)if(r[k]&&trans_missing_prereq52(job,learnIds[k],r))return 0;else if(r[k]&&learnNeeds[k]&&!class_has_tree48(job_parent52(job),learnIds[k])){int need=skill_rank_index(learnNeeds[k]);if(need<0||r[need]<learnNeedsRank[k])return 0;}return 1;}
static int skill_prereqs(const unsigned char*r){return skill_prereqs_for48(r,999);}
static int skill_learn(Combat*g,unsigned id){
 if(skill_quest(id)){combat_notice(g,POP_SKILLS,"Quest skill: learn it through its quest or developer presets.");return 0;}
 int k=skill_rank_index(id);if(k<0||!job_owns_skill48(g->jobId,learnJobs[k],learnIds[k])){combat_notice(g,POP_SKILLS,"Choose the matching job at the instructor.");return 0;}
 if((!skill_quest(id)&&g->skillPoints<=0)||g->ranks[k]>=learnMax[k]){combat_notice(g,POP_SKILLS,"Need a skill point, or this skill is already at maximum.");return 0;}
 const uint16_t*missing52=trans_missing_prereq52(g->jobId,id,g->ranks);if(missing52){combat_notice(g,POP_SKILLS,"%s requires %s %u.",skillDefs[id].name,skillDefs[missing52[2]].name,missing52[3]);return 0;}
 int missing48=class_missing_prereq48(job_parent52(g->jobId),id,g->ranks);if(missing48){const uint16_t*p=classPrereqs48[missing48-1];combat_notice(g,POP_SKILLS,"%s requires %s %u.",skillDefs[id].name,skillDefs[p[2]].name,p[3]);return 0;}
 if(id==31&&!g->ranks[27]&&!g->ranks[32]){combat_notice(g,POP_SKILLS,"New Fire Wall builds require Sight 1.");return 0;}
 if(id==48&&job_parent52(g->jobId)!=17&&g->ranks[18]<7){combat_notice(g,POP_SKILLS,"Safety Wall requires Napalm Beat7 and Soul Strike5.");return 0;}
 if(learnNeeds[k]&&!class_has_tree48(job_parent52(g->jobId),id)){int need=skill_rank_index(learnNeeds[k]);if(g->ranks[need]<learnNeedsRank[k]){combat_notice(g,POP_SKILLS,"%s requires %s %u.",skillDefs[id].name,skillDefs[learnNeeds[k]].name,learnNeedsRank[k]);return 0;}}
 g->ranks[k]++;if(!skill_quest(id))g->skillPoints--;stat_refresh(g);combat_notice(g,POP_SKILLS,"Learned %s rank %u.",skillDefs[id].name,g->ranks[k]);return 1;
}
#include "skill_costs.h"
#include "classic_costs164.h"
static const unsigned short secondCosts43[20][10]={{14,18,22,26,30,34,38,42,46,50},{3,3,3,3,3,3,3,3,3,3},{13,14,15,16,17,18,19,20,21,22},{40,40,40,40,40,40,40,40,40,40},{75,75,75,75,75,75,75,75,75,75},{35,37,39,41,43,45,47,49,51,53},{20,24,30,34,40,44,50,54,60,64},{20,23,26,29,32,35,38,41,44,47},{60,64,68,72,76,80,84,88,92,96},{15,20,20,25,25,25,25,25,25,25},{45,43,41,39,37,35,33,31,29,27},{78,78,78,78,78,78,78,78,78,78},{12,14,16,18,20,22,24,26,28,30},{5,10,15,20,25,30,35,40,45,50},{10,10,10,10,10,10,10,10,10,10},{40,40,40,40,40,40,40,40,40,40},{0,0,0,0,0,0,0,0,0,0},{8,8,8,8,8,8,8,8,8,8},{14,18,22,26,30,34,38,42,46,50},{10,25,40,55,70,85,100,115,130,145}};
static const unsigned short classCosts48[38][10]={{20, 20, 20, 20, 20, 20, 20, 20, 20, 20}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {35, 35, 35, 35, 35, 35, 35, 35, 35, 35}, {40, 40, 40, 40, 40, 40, 40, 40, 40, 40}, {40, 40, 40, 40, 40, 40, 40, 40, 40, 40}, {40, 40, 40, 40, 40, 40, 40, 40, 40, 40}, {40, 40, 40, 40, 40, 40, 40, 40, 40, 40}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {48, 46, 44, 42, 40, 38, 36, 34, 32, 30}, {48, 46, 44, 42, 40, 38, 36, 34, 32, 30}, {48, 46, 44, 42, 40, 38, 36, 34, 32, 30}, {66, 62, 58, 54, 50, 46, 42, 38, 34, 30}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {50, 50, 50, 50, 50, 50, 50, 50, 50, 50}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {12, 14, 16, 18, 20, 22, 24, 26, 28, 30}, {10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, {12, 12, 12, 12, 12, 12, 12, 12, 12, 12}, {35, 40, 45, 50, 55, 60, 65, 70, 75, 80}, {11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, {37, 44, 51, 58, 65, 72, 79, 86, 93, 100}, {25, 25, 25, 25, 25, 25, 25, 25, 25, 25}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, {24, 28, 32, 36, 40, 44, 48, 52, 56, 60}, {15, 15, 15, 15, 15, 15, 15, 15, 15, 15}};
static int skill_cost_raw52(const Combat*g,unsigned id){if(id<127&&classicCostPresent164[id]){int rank=skill_rank(g,id);if(rank<1)rank=1;if(rank>10)rank=10;return classicCosts164[id][rank-1];}if(id==339)return 5;if(id==177&&g->class50.lastSong){const ClassSkill50*d=class_skill_data50(g->class50.lastSong);return 1+d->sp[g->class50.lastSongRank-1]/2;}if(id>=SKILL_COUNT)return 0;if(id==SK60_SL_SMA||id==SK60_SL_STIN||id==SK60_SL_STUN){const ClassSkill50*d=class_skill_data50(id);int rank=skill_rank(g,id);if(rank<1)rank=1;int cost=d->sp[rank-1],kaina=class_rank50(g,SK60_SL_KAINA),rate=g->level>=90?7:g->level>=80?5:g->level>=70?3:0;return cost-cost*rate*kaina/100;}if(id==7&&job_parent52(g->jobId)==17){int rank=skill_rank(g,id);return class_skill_data50(id)->sp[rank>0?rank-1:0];}if(id>=127){const ClassSkill50*d=class_skill_data50(id);int rank=skill_rank(g,id);if(rank<1)rank=1;if(rank>10)rank=10;return d?d->sp[rank-1]:0;}if(id>=89){int rank=skill_rank(g,id);if(rank<1)rank=1;return classCosts48[id-89][rank-1];}if(id>=69){int rank=skill_rank(g,id);if(rank<1)rank=1;if(rank>10)rank=10;return secondCosts43[id-69][rank-1];}if(id>=56)return skillDefs[id].sp;int rank=skill_rank(g,id);if(rank<1)rank=1;if(rank>10)rank=10;if(id==50||id==51)return 15;if(id==52)return 11-rank;if(id==53||id==55)return 10;if(id==54)return 38-3*rank;if(id==48)return rank<=3?30:rank<=6?35:40;if(id==49)return 26-rank;if(id==44||id==45)return 0;if(id==46)return 1;if(id==47)return 7;if(id==41)return 13+2*rank;if(id==43)return 35;if(id==42)return 0;if(id==39)return 20+5*rank;if(id==36||id==37||id==38||id==40)return 10;if(id==31)return 40;if(id==32)return 15;if(id==33)return 20+3*rank;if(id==34||id==35)return 0;if(id==29)return 26-rank;if(id==30)return 24+5*rank;if(id>=21)return addedSkillCosts[id-21][rank-1];if((id==3&&(g->ranks[2]||g->persistent50.copySkill==3))||(id==9&&(g->ranks[3]||g->persistent50.copySkill==9)))return addedSkillCosts[0][rank-1];int cost=id==10?10+3*rank:skillDefs[id].sp;if(id==5&&g->ranks[6])cost=24+4*rank;if(id==6&&g->ranks[7])cost=15+3*rank;return cost;}
static int skill_cost(const Combat*g,unsigned id){int raw=skill_cost_raw52(g,id),discount=4*class_rank50(g,SK52_HP_MANARECHARGE);int rate=100-discount+g->itemBonuses52.scalar[B52_bUseSPrate];return rate>0?raw*rate/100:0;}
static int binding_item(unsigned id){return id>=BIND_ITEM_BASE50&&id<BIND_ITEM_BASE50+ITEM_COUNT?(int)id-BIND_ITEM_BASE50:-1;}
static int binding_valid(unsigned id){int i=binding_item(id);return id==BIND_EMPTY50||(id<SKILL_COUNT&&!skill_passive(id))||(i>=0&&(itemDefs[i].healMin||itemDefs[i].spMin||itemDefs[i].equipBit));}
static const char*binding_name(unsigned id){int i=binding_item(id);return i>=0?itemDefs[i].name:id<SKILL_COUNT?skillDefs[id].name:"Empty";}
static int skill_id_valid(unsigned id){return id<SKILL_COUNT||id==BIND_EMPTY50;}
static int skill_ground(unsigned id){if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&(d->target&4);}return id==89||id==101||id==102||id==103||id==104||id==73||id==75||id==77||id==80||id==82||id==4||id==30||id==31||id==32||id==48||id==53||id==54;}
static int skill_point(const Combat*g,float x,float y){
 return isfinite(x)&&isfinite(y)&&x>=8&&x<3192&&y>=8&&y<3192&&combat_dist(g->x,g->y,x,y)<=140&&(!g->canMove||g->canMove(g->world,g->x,g->y,x,y));
}
static float skill_ground_range(const Combat*g,unsigned id){return id==32?combat_attack_range(g):id<SKILL_COUNT?skillDefs[id].range:0;}
static float skill_ground_radius49(const Combat*g,unsigned id){if(id==104){int rank=skill_rank(g,id);if(rank<1)rank=1;return 20+8*((rank+1)/2);}return id<SKILL_COUNT?skillDefs[id].radius:0;}
static void skill_ground_snap(unsigned id,float*x,float*y){if(id==89){*x=floorf(*x/8.f)*8.f+4;*y=floorf(*y/8.f)*8.f+4;}}
static const char*skill_ground_reason(const Combat*g,unsigned id,float x,float y){
 skill_ground_snap(id,&x,&y);
 if(id>=SKILL_COUNT||!isfinite(x)||!isfinite(y)||x<8||y<8||x>=3192||y>=3192)return "Outside map";
 if(combat_dist(g->x,g->y,x,y)>skill_ground_range(g,id)+.05f)return "Out of range";
 if(!class_ice_line_mode200(g,g->x,g->y,x,y,id==89)||(g->canAim&&!g->canAim(g->world,g->x,g->y,x,y)))return "Line of sight blocked";if((id==31||id==48||id==53||id==54)&&g->canMove&&!g->canMove(g->world,x,y,x,y))return "Wall needs clear ground";if(id==48){int slot=combat_safety_slot(g,x,y);if(slot==-2)return "A Safety Wall is already here";if(slot<0)return "Three Safety Walls active";if(combat_pneuma_at(g,x,y)>=0)return "Pneuma occupies this ground";}if(id==53){if(combat_pneuma_slot(g,x,y)<0)return "Pneuma overlap or three fields active";if(combat_safety_at(g,x,y)>=0)return "Safety Wall occupies this ground";}if(id==54&&combat_portal_slot(g)<0)return "Three portals active";return NULL;
}
static int skill_ground_point(const Combat*g,unsigned id,float x,float y){return !skill_ground_reason(g,id,x,y);}
static int skill_assign(Combat*g,unsigned slot,unsigned skill){
 if(skill_passive(skill)){combat_notice(g,POP_SKILLS,"Passive skill: learn with X; it works without a hotbar slot.");return 0;}if(slot>=12||!skill_id_valid(skill))return 0;if(skill!=BIND_EMPTY50&&(!skill_rank(g,skill)||(g->hocusID48==(int)skill&&skill_rank_index(skill)>=0&&!g->ranks[skill_rank_index(skill)]))){combat_notice(g,POP_SKILLS,"Learn that skill first (X on the Class skills page).");return 0;}g->hotbar[slot]=skill;combat_notice(g,POP_SKILLS,"Assigned %s to bar %u slot %u.",skill==BIND_EMPTY50?"empty slot":skillDefs[skill].name,slot/6+1,slot%6+1);return 1;
}
static unsigned hot_binding(const Combat*g){if(g->hocusID48)return g->hocusID48;return g->hotAttack?0:g->hotbar[g->hotSlot];}
static unsigned hot_column(const Combat*g){return g->hotAttack?0:g->hotSlot%6+1;}
static void skill_slot(Combat*g,int column,int row){
 unsigned bar=(g->hotSlot/6+(row?1:0))%2,col=(hot_column(g)+column+7)%7;g->hotAttack=col==0;g->hotSlot=bar*6+(col?col-1:0);
}
#include "skill_status164.h"
static void skill_hit_now49(Combat*g,int i,int damage,int stun,int hits){
 CombatMob*m=&g->mobs[i];if(m->hp<=0)return;g->itemDamageSkill52=g->fxSkill;if((g->fxSkill==3||g->fxSkill==24||g->fxSkill==31||g->fxSkill==75||g->fxSkill==77)&&m->class50.webStacks52>0){damage*=2;m->class50.webRoot52=0;if(!--m->class50.webStacks52)m->class50.webUntil52=0;}damage=(mobSpecs[m->kind].flags&16)&&g->fxSkill!=SK52_PA_PRESSURE&&g->fxSkill!=SK52_HW_GRAVITATION?1:damage;if(damage<1)damage=1;combat_enemy_number180(g,m,damage,hits,0);if(hits>1)combat_hit_sound(g,hits);else if(g->fxSkill>=127&&g->fxSkill!=202)combat_hit_sound(g,1);combat_enemy_damage(g,m,damage);stargladiator_hit60(g);if(g->fxSkill>0)item_proc_event52(g,1,i,damage,(unsigned)g->fxSkill);m->hurtAt=g->time;m->aggro=!m->training&&(mobSpecs[m->kind].flags&2)!=0;
 if(stun)m->stun=1.2f;
 if(m->hp<=0){if(g->jobId==8&&g->ranks[81]&&g->fxSkill!=86&&!m->training){g->sp+=3*g->ranks[81];if(g->sp>g->maxsp)g->sp=g->maxsp;}m->hp=0;m->deadAt=g->time;m->respawnAt=0;m->provokeLeft=0;m->provokeRank=0;m->aggro=0;m->stun=0;combat_reward(g,m);if(g->target==i)g->target=-1;}
}
static int skill_burst_slot49(const Combat*g){for(int i=0;i<SKILL_BURSTS49;i++)if(!g->bursts49[i].active)return i;return -1;}
static void skill_stagger49(Combat*g,CombatMob*m){if(m->hp>0&&!combat_status_boss(m)){float until=g->time+mobDamageMotion49[m->kind]/1000.f;if(until>m->hitLockUntil49)m->hitLockUntil49=until;}}
static void skill_burst_tick49(Combat*g){for(int i=0;i<SKILL_BURSTS49;i++){SkillBurst49*p=&g->bursts49[i];if(!p->active)continue;if(g->hp<=0||g->mapId!=p->map||g->jobId!=p->job||p->target<0||p->target>=MOB_COUNT){p->active=0;continue;}CombatMob*m=&g->mobs[p->target];if(!m->enabled||m->hp<=0||m->life!=p->life){p->active=0;continue;}if(g->time+.00001f<p->next)continue;int damage=p->damage/p->hits+(p->done<p->damage%p->hits);int old=g->fxSkill,oldDeal=g->class50.homunDealing;g->class50.homunDealing=p->companion50;g->fxSkill=p->skill;g->itemProcSkip52=p->done>0;skill_hit_now49(g,p->target,damage,p->stun,1);g->itemProcSkip52=0;g->fxSkill=old;g->class50.homunDealing=oldDeal;p->applied+=damage;p->done++;skill_stagger49(g,m);if(p->skill!=75&&p->skill<127)skill_sound49(g,p->skill);combat_combo(g,&p->combo,m->x,m->y,p->applied);combat_enemy_tag180(g,m,&g->damage[(p->combo-1)%DAMAGE_EVENTS]);if(p->done>=p->hits||m->hp<=0)p->active=0;else p->next+=p->skill==78&&p->done==1?.15f:p->gap;}}
static void skill_hit_ex(Combat*g,int i,int damage,int stun,int hits){if(i<0||i>=MOB_COUNT||combat_racer_kind164(g->mobs[i].kind)||g->mobs[i].hp<=0||damage<=0)return;if(hits<=1||mobSpecs[g->mobs[i].kind].flags&16){damage=combat_hit_bonus50(g,&g->mobs[i],damage);skill_hit_now49(g,i,damage,stun,1);skill_stagger49(g,&g->mobs[i]);return;}if(hits>25)hits=25;if(hits>damage)hits=damage;int slot=skill_burst_slot49(g);if(slot<0){damage=combat_hit_bonus50(g,&g->mobs[i],damage);skill_hit_now49(g,i,damage,stun,hits);skill_stagger49(g,&g->mobs[i]);return;}CombatMob*m=&g->mobs[i];damage=combat_hit_bonus50(g,m,damage);g->bursts49[slot]=(SkillBurst49){.active=1,.companion50=g->class50.homunDealing,.target=i,.hits=hits,.damage=damage,.stun=stun,.skill=g->fxSkill,.rank=g->fxRank48,.life=m->life,.map=g->mapId,.job=g->jobId,.next=g->time,.gap=g->fxSkill==78?.125f:.2f};skill_burst_tick49(g);}
static int skill_burst_ready49(Combat*g,unsigned id,int rank,float x,float y){int hits=id==3||id==4||id==9||id==21||id==81?rank:id==23?(rank+1)/2:id==88?rank:id==17||id==71||id==120?2:id==78?25:1;if(hits<=1)return 1;int need=1,free=0;for(int i=0;i<SKILL_BURSTS49;i++)free+=!g->bursts49[i].active;if(id==4||id==71||id==88){need=0;for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].enabled&&g->mobs[i].hp>0&&combat_dist(x,y,g->mobs[i].x,g->mobs[i].y)<=(id==71?24:id==88?12:20))need++;}if(free>=need)return 1;combat_notice(g,POP_SKILLS,"Wait for the active skill hits; resources kept.");return 0;}
static void skill_hit(Combat*g,int i,int damage,int stun){skill_hit_ex(g,i,damage,stun,1);}
static void skill_magic_hit_ex48(Combat*g,int i,int damage,int stun,int hits){if(damage<=0)return;skill_hit_ex(g,i,combat_magic_def52(g,&g->mobs[i],damage,hits),stun,hits);}
static void skill_magic_hit48(Combat*g,int i,int damage,int stun){skill_magic_hit_ex48(g,i,damage,stun,1);}
#include "class_menu48.h"
static int inventory_action_rows52(const Combat*g);
static int inventory_action_commit52(Combat*g,int choice);
static int class_companion_menu50(Combat*g,int choice);
static int class_craft_rows50(const Combat*g);
static int class_craft_commit50(Combat*g,int choice);
#include "acolyte_skills.h"
/* Failed casts do not consume resources or start cooldowns. Ground casts may
 * deliberately hit empty terrain, as long as the location is valid. */
#include "cast_timing.h"
/* Pre-renewal DEX scaling: base * max(0,150-total DEX)/150.
 * Equipment/status cast modifiers and renewal fixed/variable splits are deferred. */
static float skill_cast_seconds(const Combat*g,unsigned id,int rank){if(id==SKG52_TK_RUN&&class_active50(g,id))return 0;if(id==210&&(g->class50.rootUntil>g->time||class_combo_action52(g,210)))return 0;const CastTiming*t=cast_timing(id);if(!t)return 0;if(rank<1)rank=1;if(rank>10)rank=10;int dex=stat_value(g,4);if(dex<0)dex=0;if(dex>150)dex=150;float seconds=id==87?t->cast[rank-1]/1000.f:t->cast[rank-1]*(150-dex)/150000.f;if(g->superSuffragUntil53>g->time)seconds*=.85f;seconds*=fmaxf(0,100+g->itemBonuses52.scalar[B52_bCastrate])*.01f;return g->class50.memorizeCasts52>0?seconds*.5f:seconds;}
static int skill_cast_targeted(unsigned id){if(id==SKG52_GM_SANDMAN)return 1;if(id==SK52_PF_SOULCHANGE||id==SK52_PF_SPIDERWEB||id==185||id==191||id==211||id==212)return 1;if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&(d->target&2);}return id==93||id==105||id==108||id==109||id==110||id==111||id==117||id==118||id==120||id==71||id==72||id==76||id==78||id==81||id==83||id==86||id==88||id==3||id==9||id==21||id==22||id==23||id==24||id==29||id==49||id==51||id==41||id==59;}
static int skill_target_clear(const Combat*g,unsigned id,float x,float y){CombatCanMove test=cast_timing(id)&&g->canAim?g->canAim:g->canMove;return class_ice_line_mode200(g,g->x,g->y,x,y,id==89)&&(!test||test(g->world,g->x,g->y,x,y));}
/* Validate twice: before showing a cast, and immediately before committing it.
 * Completion never selects a replacement monster or ground location. */
#include "second_jobs43.h"
#include "class_skills48.h"
#include "class_skills50.h"
#include "skill_approach53.h"
static int skill_heal_amount200(const Combat*g,int rank){int heal=(g->level+stat_value(g,3))/8*(4+8*rank);heal+=heal*(g->itemBonuses52.scalar[B52_bHealPower2]+2*class_rank50(g,SK52_HP_MEDITATIO)+g->itemBonuses52.scalar[B52_bHealPower]+item_bonus_match52(g,B52_bSkillHeal,(int)item_script_source52(10),-1))/100;return heal<1?1:heal;}
static int skill_apply(Combat*g,unsigned id,float groundX,float groundY,int release){
 if(id&&job_noskill55(g->mapId)&&!(id==339&&g->trickDead55)){combat_message(g,"Skills are not allowed in this exam room.");return 0;}if((id==52&&job_noteleport55(g->mapId))||(id==54&&job_nowarp55(g->mapId))){combat_message(g,"Teleportation is not allowed in this exam room.");return 0;}

 if(id==339){if(g->hp<=0||!skill_rank(g,339)||(g->jobId!=0&&g->jobId!=J52_HIGH_NOVICE))return 0;if(g->trickDead55){g->trickDead55=0;combat_message(g,"Play Dead ended.");return 1;}if(combat_casting(g)||g->sp<5||g->silenceLeft>0||inventory_overweight(g,90))return 0;g->sp-=5;g->trickDead55=1;g->deadAt=g->time;g->autoAttack=g->approachSkill53=g->route53.state=g->sitting=g->moving=0;g->target=-1;combat_message(g,"Playing dead. Use Play Dead again to stand.");return 1;}
 if(g->trickDead55){combat_message(g,"End Play Dead before using another skill.");return 0;}

 if(id==1&&!skill_rank(g,1)){combat_notice(g,POP_SKILLS,"First Aid must be learned from its quest.");return 0;}
 if(id==91)return class_cast_cancel48(g);
 if(g->class50.expandedStunUntil60>g->time){combat_notice(g,POP_SKILLS,"Stunned; wait before using a skill.");return 0;}
 if(combat_casting(g)){combat_notice(g,POP_SKILLS,"Casting; B or movement cancels.");return 0;}
 if(g->hp<=0){combat_notice(g,POP_SKILLS,"Knocked out. A returns to camp after a moment.");return 0;}
 if(id==SK52_ST_CHASEWALK&&class_active50(g,id)){g->class50.until[id-127]=0;return 1;}
 if(class_active50(g,SK52_ST_CHASEWALK)){combat_notice(g,POP_SKILLS,"End Chase Walk before casting.");return 0;}
 if(id==38&&g->hideLeft>0){g->hideLeft=g->hideDrain=0;combat_notice(g,POP_SKILLS,"Hiding ended.");return 1;}
 if(g->hideLeft>0&&id!=132&&id!=144&&id!=130&&id!=SK60_NJ_SHADOWJUMP&&id!=SK60_NJ_KIRIKAGE){combat_notice(g,POP_SKILLS,"B or Hiding: emerge before using other skills.");return 0;}
 if(g->sitting){combat_notice(g,POP_SKILLS,"Press L3 to stand before casting.");return 0;}
 if(id!=63&&inventory_overweight(g,90)){combat_notice(g,POP_SKILLS,"Weight at 90%%: store or sell items before attacking/casting.");return 0;}
 if(class_active50(g,207)&&id!=0){combat_notice(g,POP_SKILLS,"Steel Body prevents casting while active.");return 0;}
 if(g->class50.song&&id!=176&&id!=173&&id!=180){combat_notice(g,POP_SKILLS,"Use Amp before another skill while performing.");return 0;}
 if(g->class50.rootUntil>g->time&&!((id==206&&g->class50.rootRank>=3)||(id==209&&g->class50.rootRank>=4)||(id==210&&g->class50.rootRank>=5))){combat_notice(g,POP_SKILLS,"Root holds you; this action cannot be used.");return 0;}
 if(id==SK52_HP_BASILICA&&class_active50(g,id)){int active=class_active50(g,id);g->class50.until[id-127]=0;g->castDelay=class_skill_data50(id)->delay[active-1]*.001f;g->autoAttack=0;return 1;}
 if(class_active50(g,SK52_HP_BASILICA)){combat_notice(g,POP_SKILLS,"Cancel Basilica before attacking or casting.");return 0;}
 if(id==SK52_PA_GOSPEL&&class_active50(g,id)){g->class50.until[id-127]=0;return 1;}
 if(class_active50(g,SK52_PA_GOSPEL)){combat_notice(g,POP_SKILLS,"Cancel Gospel before attacking or casting.");return 0;}
 if(class_active50(g,SK52_HW_GRAVITATION)){combat_notice(g,POP_SKILLS,"Wait for Gravitational Field to finish.");return 0;}
 if(id!=0&&class_active50(g,SK52_LK_BERSERK)){combat_notice(g,POP_SKILLS,"Berserk prevents casting.");return 0;}
 if(id==337){if(g->jobId!=J52_SUPER_NOVICE)return 0;int next=g->level<TEST_LEVEL_CAP?progression_base_curve43(g->jobId)[g->level-1]:progression_base_curve43(g->jobId)[g->level-2];int permille=next?(int)((int64_t)g->exp*1000/next):0;if(!permille||permille%100){g->superPrayer53=0;combat_notice(g,POP_SKILLS,"Prayer requires exactly10%%,20%%,...90%% base EXP.");return 0;}static const char*lines[]={"Dear angel, can you hear my voice?","I am your Super Novice~","Help me out~ Please~ T_T"};if(g->superPrayer53<3){combat_notice(g,POP_SKILLS,"%s",lines[g->superPrayer53++]);return 1;}g->superPrayer53=0;g->class50.until[209-127]=g->time+180;g->class50.level[209-127]=17;g->lastCast=g->fxAt=g->time;g->fxX=g->x;g->fxY=g->y;g->fxSkill=209;g->fxRank48=5;combat_notice(g,POP_SKILLS,"Your angel grants Fury: +50 critical for180seconds.");return 1;}
 if(id==0){combat_attack(g);return 1;}
 if(g->silenceLeft>0){combat_notice(g,POP_SKILLS,"Silenced: cannot cast until it expires.");return 0;}
 if(id>=SKILL_COUNT||skill_passive(id)){combat_notice(g,POP_SKILLS,"Empty hotbar slot. Select opens the Skills window.");return 0;}
 int rank=skill_rank(g,id);if(!rank){combat_notice(g,POP_SKILLS,"Learn that job skill first.");return 0;}
 const SkillDef*s=&skillDefs[id];int rolled=g->hocusID48==(int)id&&g->hocusRank48;int cost=rolled?0:skill_cost(g,id);
 if(g->hitStun>0&&!release){combat_notice(g,POP_SKILLS,"Hit-staggered; SP kept.");return 0;}
 if((g->castDelay>0&&!class_combo_action52(g,id))||g->skillCD[id-1]>0){combat_notice(g,POP_SKILLS,"%s is cooling down.",s->name);return 0;}
 if(g->sp<cost){combat_notice(g,POP_SKILLS,"Not enough SP for %s (%d needed).",s->name,cost);return 0;}
 if((id==17||id==32||id==59)&&!(g->equipment&16)){combat_notice(g,POP_SKILLS,"Equip a Bow first; SP kept.");return 0;}
 if(id==64&&(!g->cartOwned||(g->equipment&16))){combat_notice(g,POP_SKILLS,"Cart Revolution needs a rented cart and melee loadout; SP kept.");return 0;}
 if(id==20&&(g->equipment&16)){combat_notice(g,POP_SKILLS,"Mammonite requires a melee weapon or bare hands.");return 0;}
 if(id==20&&g->zeny<(job_parent52(g->jobId)==19&&class_rank50(g,235)?90:100)*rank){combat_notice(g,POP_SKILLS,"Mammonite needs %d Zeny; SP kept.",(job_parent52(g->jobId)==19&&class_rank50(g,235)?90:100)*rank);return 0;}
 float range=id>=127?class_range50(g,id,rank):id>=89?class_range48(g,id,rank):(id==17||id==59)?combat_attack_range(g):s->range;float x=g->x,y=g->y;int target=g->target;int friendlyHeal200=0;int friendlyRevive200=id==185&&combat_friendly_target200;int friendlyBuff200=id>=5&&id<=7&&combat_friendly_target200;int friendlyCast200=friendlyRevive200||friendlyBuff200;
 if(friendlyRevive200){if(!combat_friendly_revive_ready200||!combat_friendly_revive_ready200(g,&x,&y))return 0;target=-1;}
 if(friendlyBuff200){if(!combat_friendly_buff_ready200||!combat_friendly_buff_ready200(g,&x,&y))return 0;target=-1;}
 if(id==14&&g->poisonLeft<=0){combat_notice(g,POP_SKILLS,"You are not poisoned; SP kept.");return 0;}
 if((id==1||(id==10&&!combat_friendly_target200))&&g->hp==g->maxhp){combat_notice(g,POP_SKILLS,"HP already full; SP kept.");return 0;}
 if(skill_ground(id)){
  skill_ground_snap(id,&groundX,&groundY);
  if(!skill_ground_point(g,id,groundX,groundY)){combat_notice(g,POP_SKILLS,"Ground blocked or out of range; SP kept.");return 0;}x=groundX;y=groundY;
 }else if(!friendlyCast200&&(skill_cast_targeted(id)||(id==201&&!g->class50.spheres)||id==2||id==3||id==9||id==13||id==17||id==20||id==21||id==22||id==23||id==24||id==27||id==29||id==37||id==41||id==49||id==51||id==57||id==58||id==59||id==64)){
  if(!combat_valid_target(g,target)&&!release){
   float nearest=(!g->itemCasting52?192.f:range)+.001f;target=-1;for(int i=0;i<MOB_COUNT;i++)if(combat_valid_target(g,i)){float d=combat_dist(g->x,g->y,g->mobs[i].x,g->mobs[i].y);if(d<nearest&&(!g->itemCasting52||skill_target_clear(g,id,g->mobs[i].x,g->mobs[i].y))){nearest=d;target=i;}}
  }
  if(!combat_valid_target(g,target)){combat_notice(g,POP_SKILLS,"No enemy within 24 cells; resources kept.");return 0;}
  float distance53=combat_dist(g->x,g->y,g->mobs[target].x,g->mobs[target].y);
  if(!release&&!g->itemCasting52&&distance53>192.f){target=-1;float nearest=192.001f;for(int i=0;i<MOB_COUNT;i++)if(combat_valid_target(g,i)){float d=combat_dist(g->x,g->y,g->mobs[i].x,g->mobs[i].y);if(d<nearest){nearest=d;target=i;}}if(target<0){combat_notice(g,POP_SKILLS,"No enemy within 24 cells; resources kept.");return 0;}distance53=combat_dist(g->x,g->y,g->mobs[target].x,g->mobs[target].y);}
  if(distance53>range||!skill_target_clear(g,id,g->mobs[target].x,g->mobs[target].y)){
   if(!release&&!g->itemCasting52&&distance53<=192.f)return skill_approach_queue53(g,id,rank,target);
   combat_notice(g,POP_SKILLS,"Target moved out of reach; resources kept.");return 0;
  }
  x=g->mobs[target].x;y=g->mobs[target].y;g->target=target;combat_face(&g->faceX,&g->faceY,x-g->x,y-g->y);
 }
 if(id==27){CombatMob*m=&g->mobs[target];if((mobSpecs[m->kind].flags&(4|16))||mobProtectedRace[m->kind]==1||(!m->training&&!(mobSpecs[m->kind].flags&2))){combat_notice(g,POP_SKILLS,"That target resists Provoke; SP kept.");return 0;}}
 if((id==30||id==73||id==75||id==77||id==80||id==82)&&combat_field_slot(g)<0){combat_notice(g,POP_SKILLS,"Three storms already active; SP kept.");return 0;}
 if(id==31&&combat_barrier_slot(g)<0){combat_notice(g,POP_SKILLS,"Three Fire Walls already active; SP kept.");return 0;}
 if(id==37){CombatMob*m=&g->mobs[target];if(m->training||m->stolen||mobUtility[m->kind].blocked||m->frozenLeft>0||!mobUtility[m->kind].count){combat_notice(g,POP_SKILLS,m->stolen?"Already stolen from this monster; SP kept.":"That target has no stealable supported loot right now; SP kept.");return 0;}}
 if(id==41&&combat_status_boss(&g->mobs[target])){combat_notice(g,POP_SKILLS,"That target resists Decrease AGI; SP kept.");return 0;}
 if(id==47&&g->canMove&&!g->canMove(g->world,g->x,g->y,g->x-2*g->faceX,g->y-2*g->faceY)){combat_notice(g,POP_SKILLS,"No room to slide backward; SP kept.");return 0;}
 if(id==48){if(combat_safety_slot(g,x,y)<0){combat_notice(g,POP_SKILLS,"Wall already here, or three walls active; resources kept.");return 0;}if(!g->itemBonuses52.scalar[B52_bNoGemStone]&&!inventory_count(g,ITEM_BLUE_GEM)){combat_notice(g,POP_SKILLS,"Safety Wall needs one Blue Gemstone; SP kept.");return 0;}}
 if(id==49){CombatMob*m=&g->mobs[target];if(combat_status_boss(m)||(m->training&&m->testTraits?m->testTraits==2:mobProtectedRace[m->kind]==1)){m->stoneNotice=4;m->stoneNoticeUntil=g->time+2.5f;combat_notice(g,POP_SKILLS,"That target resists Stone Curse; resources kept.");return 0;}if(!g->itemBonuses52.scalar[B52_bNoGemStone]&&!inventory_count(g,ITEM_RED_GEM)){combat_notice(g,POP_SKILLS,"Stone Curse needs one Red Gemstone; SP kept.");return 0;}}
 if(id==50&&g->blindLeft<=0&&g->silenceLeft<=0&&g->confusionLeft<=0){combat_notice(g,POP_SKILLS,"No ailment Cure can remove; SP kept.");return 0;}
 if(id==55&&(!g->inWater||!g->inWater(g->world,g->x,g->y,g->x,g->y))){combat_notice(g,POP_SKILLS,"Stand in shallow water to make Holy Water; resources kept.");return 0;}
 if(id==55&&(!inventory_count(g,ITEM_EMPTY_BOTTLE)||inventory_count(g,ITEM_HOLY_WATER)>=ITEM_STACK_MAX||inventory_weight(g)-itemWeights[ITEM_EMPTY_BOTTLE]+itemWeights[ITEM_HOLY_WATER]>inventory_weight_max(g))){combat_notice(g,POP_SKILLS,"Need an Empty Bottle and room for Holy Water; resources kept.");return 0;}
 if(id==52||id==54){if(id==54&&!g->itemBonuses52.scalar[B52_bNoGemStone]&&!inventory_count(g,ITEM_BLUE_GEM)){combat_notice(g,POP_SKILLS,"Warp Portal needs a Blue Gemstone; resources kept.");return 0;}g->utilityItemRank52=g->itemCasting52?rank:0;g->utilityMenu=id;g->utilityX=x;g->utilityY=y;g->autoAttack=0;combat_notice(g,POP_SKILLS,"Choose destination. B cancels without cost.");return 1;}
 if(id==62||id==63||id==65){if((id==63||id==65)&&(job_first50(g->jobId)!=6&&g->jobId!=J52_SUPER_NOVICE))return 0;if(id==63&&!g->cartOwned){combat_notice(g,POP_SKILLS,"Rent a cart from the Prontera merchant first.");return 0;}if(id==65&&!g->cartOwned){combat_notice(g,POP_SKILLS,"Rent a cart first; SP kept.");return 0;}g->utilityItemRank52=g->itemCasting52?rank:0;g->utilityMenu=id;g->autoAttack=0;combat_notice(g,POP_SKILLS,"%s: choose an action. B closes without confirming.",s->name);return 1;}
 if(id==107){g->utilityMenu=107;g->autoAttack=0;return 1;}
 if(id==60){g->utilityMenu=60;g->autoAttack=0;return 1;}
 if(id==56&&!inventory_can_add(g,ITEM_STONE,1)){combat_notice(g,POP_SKILLS,"Stone stack full; SP kept.");return 0;}
 if(id==57&&!inventory_count(g,ITEM_STONE)){combat_notice(g,POP_SKILLS,"Find a Stone first; SP kept.");return 0;}
 if((id==17||id==32||id==59)&&!inventory_count(g,ITEM_ARROW)){combat_notice(g,POP_SKILLS,"Out of Arrows; SP kept.");return 0;}
 if(friendlyRevive200){if(!class_resources50(g,id,rank,0))return 0;}else if(id>=127){int ready=class_ready50(g,id,x,y,target);if(ready!=1)return ready==2;}
 if(id>=89&&id<127&&!class_ready48(g,id,x,y,target))return 0;
 if(id>=69&&id<89&&!second_ready43(g,id)){return 0;}
 if(!skill_burst_ready49(g,id,rank,x,y))return 0;
 const CastTiming*timing=cast_timing(id);float castSeconds=skill_cast_seconds(g,id,rank);
 if(!rolled&&timing&&g->hp<=timing->hp[rank-1]){combat_notice(g,POP_SKILLS,"Not enough HP for %s; casting resources kept.",s->name);return 0;}
 if(!release&&timing&&castSeconds>.0001f){
  if(g->class50.memorizeCasts52>0&&!--g->class50.memorizeCasts52)g->class50.until[SK52_PF_MEMORIZE-127]=0;
  g->superSuffragUntil53=0;g->moveLock45=.2f;g->spellCastId=id;g->spellCastLeft=g->spellCastTotal=castSeconds;g->spellCastX=x;g->spellCastY=y;g->spellCastFriendly200=friendlyCast200?combat_friendly_target200:0;g->spellCastFriendlyLife200=friendlyCast200?combat_friendly_life200:0;g->spellCastTarget=friendlyCast200?-1:skill_cast_targeted(id)?target:-1;g->spellCastLife=g->spellCastTarget>=0?g->mobs[target].life:0;g->spellCastRank=rank;g->spellCastJob=g->jobId;g->spellCastInterruptible=timing->interruptible;g->spellCastMap=g->mapId;g->coatCastLeft=id==67?castSeconds:0;if(skill_cast_aura49(id))combat_sound_at(g,58,0);if(id==SK52_CH_SOULCOLLECT)combat_sound_at(g,74,0);
  return 1;
 }
 if(friendlyRevive200){if(!combat_friendly_revive200||combat_friendly_revive200(g,rank,&x,&y)<=0)return 0;}
 if(friendlyBuff200){if(!combat_friendly_buff200||!combat_friendly_buff200(g,id,rank,&x,&y))return 0;}
 if(id==10&&combat_friendly_target200){if(!combat_friendly_heal200)return 0;friendlyHeal200=combat_friendly_heal200(g,rank,&x,&y);if(friendlyHeal200<=0)return 0;target=-1;}
 if(id==17||id==32||id==59)--*inventory_stack(g,ITEM_ARROW);
 if(id==20)g->zeny-=(job_parent52(g->jobId)==19&&class_rank50(g,235)?90:100)*rank;
 g->moveLock45=.2f;if(timing&&!rolled)g->hp-=timing->hp[rank-1];g->sp-=cost;if(id!=130)g->class50.until[130-127]=0;g->castDelay=(timing?timing->delay[rank-1]/1000.f:.35f)*fmaxf(0,100+g->itemBonuses52.scalar[B52_bDelayrate])*.01f;g->skillCD[id-1]=timing?timing->cooldown[rank-1]/1000.f:s->cooldown;g->lastCast=g->fxAt=g->attackAt=g->time;g->fxX=x;g->fxY=y;g->fxSkill=id;g->fxRank48=rank;g->fxTarget200=target;g->fxLife200=target>=0&&target<MOB_COUNT?g->mobs[target].life:0;g->fxFromX200=g->x;g->fxFromY200=g->y;
 if(friendlyBuff200){combat_notice(g,POP_SKILLS,"%s: companion supported (-%d SP).",s->name,cost);}
 else if(friendlyRevive200){class_resources50(g,id,rank,1);class_sound_emit50(g,id);combat_notice(g,POP_SKILLS,"Companion revived (-%d SP).",cost);}
 else if(id>=127){class_execute50(g,id,rank,target,x,y);if(!(id>=154&&id<=163)&&id!=136&&id!=240&&id!=SK52_CH_PALMSTRIKE)class_sound_emit50(g,id);}
 else if(id>=89){class_execute48(g,id,rank,target,x,y);}
 else if(id>=69){second_execute43(g,id,rank,target,x,y);}
 else if(id==67){g->energyCoatLeft=300;combat_notice(g,POP_SKILLS,"Energy Coat: physical protection for 300 seconds.");}
 else if(id==66){g->uproarLeft=300;combat_notice(g,POP_SKILLS,"Crazy Uproar: +4 STR for 300 seconds.");}
 else if(id==64){int count=0,rate=150+(int)(100*inventory_cart_weight(g)/CART_WEIGHT_MAX);for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!m->enabled||m->hp<=0||fabsf(m->x-x)>8||fabsf(m->y-y)>8||(g->canAim&&!g->canAim(g->world,x,y,m->x,m->y)))continue;int damage=combat_physical(g)*rate/100;damage=damage*(100-combat_enemy_defense(m))/100;skill_hit(g,i,damage,0);combat_knockback(g,i,m->x-g->x,m->y-g->y,16);count++;}skill_sound49(g,g->fxSkill);combat_notice(g,POP_DAMAGE,"Cart Revolution: %d targets, %d%% prototype ATK.",count,rate);}
 else if(id==56){inventory_add(g,ITEM_STONE,1);combat_notice(g,POP_SKILLS,"Found one Stone (%d carried).",inventory_count(g,ITEM_STONE));}
 else if(id==57){--*inventory_stack(g,ITEM_STONE);CombatMob*m=&g->mobs[target];skill_hit(g,target,mobSpecs[m->kind].flags&16?1:50,0);if(!combat_status_boss(m)){if(combat_random(g)%100<3)m->stun=5;else if(combat_random(g)%100<3)m->mobBlind=8;}skill_sound49(g,g->fxSkill);combat_notice(g,POP_SKILLS,"Stone Fling. Stones left:%d",inventory_count(g,ITEM_STONE));}
 else if(id==58||id==59){CombatMob*m=&g->mobs[target];int rate=id==58?130:150,damage=combat_physical(g)*rate/100;if(id==58)damage=damage*mobSandRate[m->kind]/100;damage=damage*(100-combat_enemy_defense(m))/100;if(damage<1)damage=1;skill_hit(g,target,damage,0);if(id==58&&!combat_status_boss(m)&&combat_random(g)%100<20)m->mobBlind=10;if(id==59)combat_knockback(g,target,m->x-g->x,m->y-g->y,48);skill_sound49(g,g->fxSkill);combat_notice(g,POP_DAMAGE,"%s: %d damage.",s->name,damage);}
 else if(id==50){g->blindLeft=g->silenceLeft=g->confusionLeft=0;combat_notice(g,POP_SKILLS,"Cure: ailments removed.");}
 else if(id==51){int power=(combat_magic_power48(g))*125/100;skill_magic_hit48(g,target,power,0);skill_sound49(g,g->fxSkill);combat_notice(g,POP_DAMAGE,"Holy Light: %d holy damage.",power);}
 else if(id==53){int slot=combat_pneuma_slot(g,x,y);g->pneuma[slot]=(PneumaField){x,y,g->time+10};combat_notice(g,POP_SKILLS,"Pneuma: ranged physical protection for10 seconds.");}
 else if(id==55){--*inventory_stack(g,ITEM_EMPTY_BOTTLE);inventory_add(g,ITEM_HOLY_WATER,1);g->castDelay=.5f;combat_notice(g,POP_SKILLS,"Aqua Benedicta: created one Holy Water.");}
 else if(id==48){int slot=combat_safety_slot(g,x,y);g->safety[slot]=(SafetyWall){combat_safety_center(x),combat_safety_center(y),g->time+5*rank,0,rank+1,g->time};if(!g->itemBonuses52.scalar[B52_bNoGemStone])--*inventory_stack(g,ITEM_BLUE_GEM);skill_sound49(g,48);combat_notice(g,POP_SKILLS,"Safety Wall: %d melee hits, %ds. Stay inside the wall.",rank+1,5*rank);}
 else if(id==49){CombatMob*m=&g->mobs[target];int applied=0;if(m->stoneWait>0||m->stoneLeft>0){m->stoneWait=m->stoneLeft=m->stoneTick=0;m->stoneNotice=2;m->stoneNoticeUntil=g->time+2.5f;applied=1;combat_notice(g,POP_SKILLS,"Stone Curse removed existing petrification.");}else{int chance=(20+4*rank)*100*(100-mobFreezeMdef[m->kind])/100-mobStatusLuk[m->kind]*10;if(mobSourceLevel[m->kind]>g->level)chance-=(mobSourceLevel[m->kind]-g->level)*10;if(chance<0)chance=0;if(chance>10000)chance=10000;applied=combat_random(g)%10000<(unsigned)chance;if(applied){m->stoneWait=5;m->stoneLeft=m->stoneTick=0;m->stoneNotice=0;combat_notice(g,POP_SKILLS,"Stone Curse: petrification begins in5s.");}else{m->stoneNotice=1;m->stoneNoticeUntil=g->time+2.5f;combat_notice(g,POP_SKILLS,rank>5?"Stone Curse resisted; SP spent, gem kept.":"Stone Curse resisted; SP and gem spent.");}}if(applied||rank<=5)if(!g->itemBonuses52.scalar[B52_bNoGemStone])--*inventory_stack(g,ITEM_RED_GEM);}
 else if(id==46){g->autoBerserk=!g->autoBerserk;combat_notice(g,POP_SKILLS,"Auto Berserk %s. Activates below25%% HP.",g->autoBerserk?"enabled":"disabled");}
 else if(id==47){int steps=0;for(int j=0;j<20;j++){if(!combat_move(g,&g->x,&g->y,g->x-2*g->faceX,g->y-2*g->faceY))break;steps++;}combat_notice(g,POP_SKILLS,"Back Sliding: moved %d.%d cells.",steps/4,(steps%4)*10/4);}
 else if(id==41){CombatMob*m=&g->mobs[target];int chance=(40+2*rank+(g->level+stat_value(g,3))/5)*(100-mobFreezeMdef[m->kind])/100-mobStatusLuk[m->kind]/10;if(chance<0)chance=0;if(chance>100)chance=100;if(combat_random(g)%100<(unsigned)chance){m->slowLeft=30+10*rank;m->slowRank=rank;combat_notice(g,POP_SKILLS,"Decrease AGI: slowed for %d seconds.",30+10*rank);}else combat_notice(g,POP_SKILLS,"Decrease AGI resisted. SP spent.");}
 else if(id==43){int count=0;for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!combat_valid_target(g,i)||!combat_signum_target(m)||combat_dist(g->x,g->y,m->x,m->y)>120||(g->canAim&&!g->canAim(g->world,g->x,g->y,m->x,m->y)))continue;int chance=23+4*rank+g->level-mobSourceLevel[m->kind];if(chance<0)chance=0;if(chance>100)chance=100;if(combat_random(g)%100<(unsigned)chance){if(m->crucisRank<rank)m->crucisRank=rank;count++;}}g->castDelay=2;combat_notice(g,POP_SKILLS,"Signum Crucis: %d targets weakened.",count);}
 else if(id==36){g->sightLeft=10;g->revealTick=0;combat_reveal(g,24,0);combat_notice(g,POP_SKILLS,"Sight: reveal aura active for 10 seconds.");}
 else if(id==37){combat_steal(g,target,rank);}
 else if(id==38){g->hideLeft=30.f*rank;g->hideRank=rank;g->hideDrain=0;g->autoAttack=0;g->target=-1;combat_notice(g,POP_SKILLS,"Hiding. B or Hiding to emerge; detectors can see you.");}
 else if(id==39){g->concentrateLeft=40+20*rank;g->concentrateRank=rank;combat_reveal(g,24,0);combat_notice(g,POP_SKILLS,"Concentration: +%d%% base AGI/DEX for %d seconds.",2+rank,40+20*rank);}
 else if(id==40){g->ruwachLeft=10;g->revealTick=0;combat_reveal(g,16,1);combat_notice(g,POP_SKILLS,"Ruwach: holy reveal aura active for 10 seconds.");}
 else if(id==31){combat_barrier_start(g,x,y,rank);combat_notice(g,POP_SKILLS,"Fire Wall: three cells, %d contact hits per cell.",4+rank);}
 else if(id==32){int count=0;for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!m->enabled||m->hp<=0||fabsf(m->x-x)>20||fabsf(m->y-y)>20||(g->canAim&&!g->canAim(g->world,x,y,m->x,m->y)))continue;int damage=combat_physical(g)*(75+5*rank)/100;damage=damage*(100-combat_enemy_defense(m))/100;if(damage<1)damage=1;skill_hit(g,i,damage,0);combat_knockback(g,i,m->x-g->x,m->y-g->y,16);count++;}if(count)skill_sound49(g,g->fxSkill);combat_notice(g,POP_DAMAGE,"Arrow Shower: %d targets.",count);}
 else if(id==33){g->angelusLeft=30.f*rank;g->angelusRank=rank;g->castDelay=3.5f;combat_notice(g,POP_SKILLS,"Angelus: +%d%% VIT defence for %d seconds.",5*rank,30*rank);}
 else if(id==29){
  CombatMob*m=&g->mobs[target];int power=combat_magic_power48(g);int damage=power*(100+10*rank)/100;damage=damage*(m->frozenLeft>0?25:mobWaterRate[m->kind])/100;
  if(damage>0){skill_magic_hit48(g,target,damage,0);skill_sound49(g,g->fxSkill);}
  if(damage>0&&skill_freeze164(g,m,35+3*rank,3000*rank)){int tenths=(int)(m->frozenLeft*10+.5f);combat_notice(g,POP_SKILLS,"Frost Diver: frozen for %d.%ds.",tenths/10,tenths%10);}
  else combat_notice(g,POP_DAMAGE,"Frost Diver: %d damage; no freeze.",damage);
 }else if(id==30){
  combat_field_start(g,x,y,rank,(combat_magic_power48(g))*80/100);
  combat_notice(g,POP_SKILLS,"Thunder Storm: %d timed strikes, one second apart.",rank);
 }else if(id>=21){
  if(id==27){CombatMob*m=&g->mobs[target];m->provokeLeft=30;m->provokeRank=rank;m->aggro=!m->training;combat_notice(g,POP_SKILLS,"Provoke: DEF reduced, ATK increased for 30 seconds.");}
  else if(id==28){g->endureLeft=7+3*rank;g->endureHits=7;g->hitStun=0;combat_notice(g,POP_SKILLS,"Endure: %d seconds / seven physical hits.",(int)g->endureLeft);}
  else {int power=combat_magic_power48(g);int hits=id==21?rank:id==23?(rank+1)/2:1;int damage=power*hits;if(id==21){CombatMob*m=&g->mobs[target];damage=class_multi_element48(g,m,4,power,hits);}if(id==22)damage=power*(70+10*rank)/100;if(id==24)damage=power*(70+10*rank)/100;
   if(id==22||id==24){int count=0;for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].hp>0&&combat_dist(x,y,g->mobs[i].x,g->mobs[i].y)<=s->radius&&(!g->canMove||g->canMove(g->world,x,y,g->mobs[i].x,g->mobs[i].y)))count++;if(id==22&&count)damage/=count;for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].hp>0&&combat_dist(x,y,g->mobs[i].x,g->mobs[i].y)<=s->radius&&(!g->canMove||g->canMove(g->world,x,y,g->mobs[i].x,g->mobs[i].y)))skill_magic_hit48(g,i,id==24&&g->mobs[i].stoneLeft>0?damage*150/100:damage,0);skill_sound49(g,g->fxSkill);}
   else {skill_magic_hit_ex48(g,target,damage,0,hits);if(hits==1)skill_sound49(g,g->fxSkill);}combat_notice(g,POP_DAMAGE,"%s: %d hit%s (-%d SP).",s->name,hits,hits==1?"":"s",cost);
  }
 }
 else if(id==1){int heal=g->maxhp-g->hp;if(heal>5)heal=5;g->hp+=heal;combat_recovery_number53(g,heal,0);combat_notice(g,POP_SKILLS,"First Aid: +%d HP (-3 SP).",heal);}
 else if(id==2||id==3||id==9||id==13||id==17||id==20){int damage=id==2?(10+2*(g->level-1)+inventory_attack(g)+(stat_value(g,0)-1)*2)*2:combat_magic_power48(g);if(id==17)damage=combat_physical(g)*(180+20*rank)/100;else if(id==20)damage=combat_physical(g)*(100+50*rank)/100;else if(id==13)damage=10+inventory_attack(g)+(stat_value(g,0)-1)*2+15*rank;else if(id!=3&&id!=9)damage=damage*(100+(rank-1)*12)/100;if(id==2)damage=class_physical50(g,&g->mobs[target],100+30*rank,0,-1);if(id==20)damage=class_physical50(g,&g->mobs[target],100+50*rank,0,-1);if(id==2&&combat_berserk_active(g))damage=damage*132/100;int hitCount=id==17?2:(id==3||id==9)?rank:1;if((id==3||id==9)&&rank>1)damage=damage*rank;if(id==3||id==9)damage=class_multi_element48(g,&g->mobs[target],id==3?3:1,damage/rank,rank);if(id==3||id==9)skill_magic_hit_ex48(g,target,damage,0,hitCount);else skill_hit_ex(g,target,damage,0,hitCount);if(id==2&&rank>5&&g->ranks[41]&&g->mobs[target].hp>0&&!combat_status_boss(&g->mobs[target])){CombatMob*m=&g->mobs[target];int chance=500*(rank-5)*g->level/50;chance=chance*(100-mobStunVit[m->kind])/100-10*mobStatusLuk[m->kind];if(chance>0&&combat_random(g)%10000<(unsigned)chance)m->stun=5.f*(100-mobStunVit[m->kind])/100;}if(id==13&&g->mobs[target].hp>0)class_poison50(g,&g->mobs[target],10+4*rank,10+5*rank);combat_notice(g,POP_DAMAGE,"%s: %d damage (-%d SP).",s->name,damage,cost);}
 else if(id==4||id==8){
  if(id==8){x=g->x;y=g->y;g->fxX=x;g->fxY=y;}
  int hits=0,damage=id==4?combat_magic_power48(g):(10+2*(g->level-1)+inventory_attack(g)+(stat_value(g,0)-1)*2)*(100+20*rank)/100;for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(m->hp>0&&combat_dist(x,y,m->x,m->y)<=s->radius&&(!g->canMove||g->canMove(g->world,x,y,m->x,m->y))){if(id==4)skill_magic_hit_ex48(g,i,class_multi_element48(g,m,2,damage,rank),0,rank);else{skill_hit(g,i,class_physical50(g,m,100+20*rank,0,3),0);combat_knockback(g,i,m->x-g->x,m->y-g->y,16);}hits++;}}
  combat_notice(g,POP_DAMAGE,"%s: hit %d enemies (-%d SP).",s->name,hits,s->sp);
 }
 else if(id==10){int heal=friendlyHeal200?friendlyHeal200:skill_heal_amount200(g,rank);if(friendlyHeal200){combat_number(g,x,y,heal,1,0);DamageEvent*d=g->damage+(g->damageNext-1)%DAMAGE_EVENTS;d->kind=4;d->style=3;}else{if(heal>g->maxhp-g->hp)heal=g->maxhp-g->hp;g->hp+=heal;combat_recovery_number53(g,heal,0);}combat_notice(g,POP_SKILLS,"Heal: +%d HP (-%d SP).",heal,cost);}
 else if(id==14){g->poisonLeft=g->poisonTick=0;combat_notice(g,POP_SKILLS,"Poison removed (-10 SP).");}
 else {if(id==7)g->class50.until[SK52_HP_ASSUMPTIO-127]=0;int b=(int)id-5;g->buffs[b]=b==2?60:120;if(b<2){int learned=rolled?rank:g->ranks[b==0?6:7];g->buffLevels[b]=learned?(b==0?learned:2+learned):0;if(learned)g->buffs[b]=40+20*learned;}if(b==2){g->shieldHP=g->maxhp*(10+2*rank)/100;g->shieldHits=5+rank/2;g->buffs[2]=120;}combat_notice(g,POP_SKILLS,"%s active for %d seconds.",s->name,(int)g->buffs[b]);}
 item_proc_event52(g,3,target,0,id);
 class_double_bolt52(g,id,rank,target);
 if(rolled)g->hocusID48=g->hocusRank48=0;
 return 1;
}
static int skill_cast(Combat*g,unsigned id,float x,float y){if(g->mapId==489||g->mapId==490){combat_message(g,"Skills are disabled in the race arena.");return 0;}if(!g->itemCasting52)g->approachSkill53=0;return skill_apply(g,id,x,y,0);}
static void skill_cast_tick(Combat*g,float dt){
 if(g->spellCastLeft<=0)return;
 if(g->hp<=0||g->jobId!=g->spellCastJob||g->mapId!=g->spellCastMap||g->sitting||g->hideLeft>0||g->silenceLeft>0||inventory_overweight(g,90)||skill_rank(g,g->spellCastId)!=g->spellCastRank){combat_interrupt_cast(g);return;}
 int target=g->spellCastTarget;
 if(target>=0&&(!combat_valid_target(g,target)||g->mobs[target].life!=g->spellCastLife)){combat_interrupt_cast(g);return;}
 g->spellCastLeft-=dt;g->coatCastLeft=g->spellCastId==67?fmaxf(0,g->spellCastLeft):0;
 if(g->spellCastLeft>.0001f)return;
 unsigned id=g->spellCastId,friendly=g->spellCastFriendly200,life=g->spellCastFriendlyLife200;float x=g->spellCastX,y=g->spellCastY;g->spellCastLeft=g->coatCastLeft=0;g->spellCastId=g->spellCastFriendly200=g->spellCastFriendlyLife200=0;
 if(target>=0)g->target=target;
 combat_friendly_target200=friendly;combat_friendly_life200=life;int applied=skill_apply(g,id,x,y,1);combat_friendly_target200=combat_friendly_life200=0;if(!applied)return;
}
#include "item_proc52.h"
#endif
