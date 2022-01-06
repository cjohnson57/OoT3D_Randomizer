#include "logic.hpp"

#include <3ds.h>
#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "settings.hpp"
#include "dungeon.hpp"
#include "setting_descriptions.hpp"

using namespace Settings;

namespace Logic {

  bool noVariable    = false;

  //Child item logic
  bool KokiriSword   = false;
  bool ZeldasLetter  = false;
  bool WeirdEgg      = false;
  bool HasBottle     = false;
  bool Bombchus      = false;
  bool Bombchus5     = false;
  bool Bombchus10    = false;
  bool Bombchus20    = false;
  bool MagicBean     = false;
  bool MagicBeanPack = false;
  bool RutosLetter   = false;
  bool Boomerang     = false;
  bool DinsFire      = false;
  bool FaroresWind   = false;
  bool NayrusLove    = false;
  bool LensOfTruth   = false;
  bool ShardOfAgony  = false;
  bool SkullMask     = false;
  bool MaskOfTruth   = false;

  //Adult logic
  bool Hammer        = false;
  bool IronBoots     = false;
  bool HoverBoots    = false;
  bool MirrorShield  = false;
  bool GoronTunic    = false;
  bool ZoraTunic     = false;
  bool Epona         = false;
  bool BigPoe        = false;
  bool GerudoToken   = false;
  bool FireArrows    = false;
  bool IceArrows     = false;
  bool LightArrows   = false;

  //Trade Quest
  bool PocketEgg     = false;
  bool Cojiro        = false;
  bool OddMushroom   = false;
  bool OddPoultice   = false;
  bool PoachersSaw   = false;
  bool BrokenSword   = false;
  bool Prescription  = false;
  bool EyeballFrog   = false;
  bool Eyedrops      = false;
  bool ClaimCheck    = false;

  //Trade Quest Events
  bool WakeUpAdultTalon   = false;
  bool CojiroAccess       = false;
  bool OddMushroomAccess  = false;
  bool OddPoulticeAccess  = false;
  bool PoachersSawAccess  = false;
  bool BrokenSwordAccess  = false;
  bool PrescriptionAccess = false;
  bool EyeballFrogAccess  = false;
  bool EyedropsAccess     = false;
  bool DisableTradeRevert = false;

  //Songs
  bool ZeldasLullaby    = false;
  bool SariasSong       = false;
  bool SunsSong         = false;
  bool SongOfStorms     = false;
  bool EponasSong       = false;
  bool SongOfTime       = false;
  bool MinuetOfForest   = false;
  bool BoleroOfFire     = false;
  bool SerenadeOfWater  = false;
  bool RequiemOfSpirit  = false;
  bool NocturneOfShadow = false;
  bool PreludeOfLight   = false;

  //Stones and Meddallions
  bool ForestMedallion = false;
  bool FireMedallion   = false;
  bool WaterMedallion  = false;
  bool SpiritMedallion = false;
  bool ShadowMedallion = false;
  bool LightMedallion  = false;
  bool KokiriEmerald   = false;
  bool GoronRuby       = false;
  bool ZoraSapphire    = false;

  //Dungeon Clears
  bool DekuTreeClear       = false;
  bool DodongosCavernClear = false;
  bool JabuJabusBellyClear = false;
  bool ForestTempleClear   = false;
  bool FireTempleClear     = false;
  bool WaterTempleClear    = false;
  bool SpiritTempleClear   = false;
  bool ShadowTempleClear   = false;

  //Trial Clears
  bool ForestTrialClear = false;
  bool FireTrialClear   = false;
  bool WaterTrialClear  = false;
  bool SpiritTrialClear = false;
  bool ShadowTrialClear = false;
  bool LightTrialClear  = false;

  //Progressive Items
  u8 ProgressiveBulletBag = 0;
  u8 ProgressiveBombBag   = 0;
  u8 ProgressiveMagic     = 0;
  u8 ProgressiveScale     = 0;
  u8 ProgressiveHookshot  = 0;
  u8 ProgressiveBow       = 0;
  u8 ProgressiveWallet    = 0;
  u8 ProgressiveStrength  = 0;
  u8 ProgressiveOcarina   = 0;

  //Logical keysanity
  bool IsKeysanity = false;

  //Keys
  u8 ForestTempleKeys          = 0;
  u8 FireTempleKeys            = 0;
  u8 WaterTempleKeys           = 0;
  u8 SpiritTempleKeys          = 0;
  u8 ShadowTempleKeys          = 0;
  u8 GanonsCastleKeys          = 0;
  u8 GerudoFortressKeys        = 0;
  u8 GerudoTrainingGroundsKeys = 0;
  u8 BottomOfTheWellKeys       = 0;

  //Boss Keys
  bool BossKeyForestTemple = false;
  bool BossKeyFireTemple   = false;
  bool BossKeyWaterTemple  = false;
  bool BossKeySpiritTemple = false;
  bool BossKeyShadowTemple = false;
  bool BossKeyGanonsCastle = false;

  //Gold Skulltula Count
  u8 GoldSkulltulaTokens = 0;

  //Drops and Bottle Contents Access
  bool DekuNutDrop      = false;
  bool NutPot           = false;
  bool NutCrate         = false;
  bool DekuBabaNuts     = false;
  bool DekuStickDrop    = false;
  bool StickPot         = false;
  bool DekuBabaSticks   = false;
  bool BugsAccess       = false;
  bool BugShrub         = false;
  bool WanderingBugs    = false;
  bool BugRock          = false;
  bool BlueFireAccess   = false;
  bool FishAccess       = false;
  bool FishGroup        = false;
  bool LoneFish         = false;
  bool FairyAccess      = false;
  bool GossipStoneFairy = false;
  bool BeanPlantFairy   = false;
  bool ButterflyFairy   = false;
  bool FairyPot         = false;
  bool FreeFairies      = false;
  bool FairyPond        = false;
  bool BombchuDrop      = false;
  bool AmmoCanDrop      = false;

  bool BuyBombchus5     = false;
  bool BuyBombchus10    = false;
  bool BuyBombchus20    = false;
  bool BuySeed          = false;
  bool BuyArrow         = false;
  bool BuyBomb          = false;
  bool BuyGPotion       = false;
  bool BuyBPotion       = false;
  bool MagicRefill      = false;

  /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
  /* These are used to simplify reading the logic, but need to be updated
  /  every time a base value is updated.                       */

  bool Slingshot        = false;
  bool Ocarina          = false;
  bool OcarinaOfTime    = false;
  bool BombBag          = false;
  bool MagicMeter       = false;
  bool Hookshot         = false;
  bool Longshot         = false;
  bool Bow              = false;
  bool GoronBracelet    = false;
  bool SilverGauntlets  = false;
  bool GoldenGauntlets  = false;
  bool SilverScale      = false;
  bool GoldScale        = false;
  bool AdultsWallet     = false;

  bool ScarecrowSong    = false;
  bool Scarecrow        = false;
  bool DistantScarecrow = false;

  bool Bombs            = false;
  bool DekuShield       = false;
  bool HylianShield     = false;
  bool Nuts             = false;
  bool Sticks           = false;
  bool Bugs             = false;
  bool BlueFire         = false;
  bool Fish             = false;
  bool Fairy            = false;
  bool BottleWithBigPoe = false;

  bool FoundBombchus    = false;
  bool CanPlayBowling   = false;
  bool HasBombchus      = false;
  bool HasExplosives    = false;
  bool IsChild          = false;
  bool IsAdult          = false;
  bool CanBlastOrSmash  = false;
  bool CanChildAttack   = false;
  bool CanChildDamage   = false;
  bool CanCutShrubs     = false;
  bool CanDive          = false;
  bool CanLeaveForest   = false;
  bool CanPlantBugs     = false;
  bool CanRideEpona     = false;
  bool CanStunDeku      = false;
  bool CanSummonGossipFairy = false;
  bool CanSummonGossipFairyWithoutSuns = false;
  bool CanTakeDamage       = false;
  //bool CanPlantBean        = false;
  bool CanOpenBombGrotto   = false;
  bool CanOpenStormGrotto  = false;
  bool BigPoeKill          = false;
  bool HookshotOrBoomerang = false;
  bool CanGetNightTimeGS   = false;

  bool GuaranteeTradePath     = false;
  bool GuaranteeHint          = false;
  bool HasFireSource          = false;
  bool HasFireSourceWithTorch = false;

  bool CanFinishGerudoFortress = false;

  bool HasShield        = false;
  bool CanShield        = false;
  bool CanJumpslash     = false;
  bool CanUseProjectile = false;

  //Bridge and LACS Requirements
  u8 MedallionCount          = 0;
  u8 StoneCount              = 0;
  u8 DungeonCount            = 0;
  bool HasAllStones          = false;
  bool HasAllMedallions      = false;
  bool CanBuildRainbowBridge = false;
  bool CanTriggerLACS        = false;

  //Other
  bool AtDay         = false;
  bool AtNight       = false;
  u8 Age             = 0;

  //Events
  bool ShowedMidoSwordAndShield  = false;
  bool CarpenterRescue           = false;
  bool GF_GateOpen               = false;
  bool DampesWindmillAccess      = false;
  bool DrainWell                 = false;
  bool GoronCityChildFire        = false;
  bool GCWoodsWarpOpen           = false;
  bool StopGCRollingGoronAsAdult = false;
  bool ChildWaterTemple          = false;
  bool RaiseWaterLevel           = false;
  bool KakarikoVillageGateOpen   = false;
  bool KingZoraThawed            = false;
  bool ForestTempleJoAndBeth     = false;
  bool ForestTempleAmyAndMeg     = false;
  bool LinksCow                  = false;
  bool AtDampeTime               = false;
  bool DeliverLetter             = false;
  bool TimeTravel                = false;

  /* --- END OF HELPERS AND LOCATION ACCESS --- */

  //Placement Tracking
  u8 AddedProgressiveBulletBags = 0;
  u8 AddedProgressiveBombBags   = 0;
  u8 AddedProgressiveMagics     = 0;
  u8 AddedProgressiveScales     = 0;
  u8 AddedProgressiveHookshots  = 0;
  u8 AddedProgressiveBows       = 0;
  u8 AddedProgressiveWallets    = 0;
  u8 AddedProgressiveStrengths  = 0;
  u8 AddedProgressiveOcarinas   = 0;
  u8 TokensInPool               = 0;

  //Event checking past
  bool DrainWellPast            = false;
  bool DampesWindmillAccessPast = false;
  bool DekuTreeClearPast        = false;
  bool GoronRubyPast            = false;
  bool ZoraSapphirePast         = false;
  bool ForestTrialClearPast     = false;
  bool FireTrialClearPast       = false;
  bool WaterTrialClearPast      = false;
  bool SpiritTrialClearPast     = false;
  bool ShadowTrialClearPast     = false;
  bool LightTrialClearPast      = false;
  bool BuyDekuShieldPast        = false;
  bool TimeTravelPast           = false;

  bool CanPlay(bool song) {
    return Ocarina && song;
  }

  static bool IsMagicItem(ItemKey item) {
    return item == DINS_FIRE    ||
           item == FARORES_WIND ||
           item == NAYRUS_LOVE  ||
           item == LENS_OF_TRUTH;
  }

  static bool IsAdultItem(ItemKey item) {
    return item == BOW              ||
           item == MEGATON_HAMMER   ||
           item == IRON_BOOTS       ||
           item == HOVER_BOOTS      ||
           item == HOOKSHOT         ||
           item == LONGSHOT         ||
           item == SILVER_GAUNTLETS ||
           item == GOLDEN_GAUNTLETS ||
           item == GORON_TUNIC      ||
           item == ZORA_TUNIC       ||
           item == SCARECROW        ||
           item == DISTANT_SCARECROW;
  }

  static bool IsChildItem(ItemKey item) {
    return item == SLINGSHOT    ||
           item == BOOMERANG    ||
           item == KOKIRI_SWORD ||
           item == STICKS       ||
           item == DEKU_SHIELD;
  }

  static bool IsMagicArrow(ItemKey item) {
    return item == FIRE_ARROWS ||
           item == ICE_ARROWS  ||
           item == LIGHT_ARROWS;
  }

  bool HasItem(ItemKey itemName) {
    return (itemName == DINS_FIRE         && DinsFire)        ||
           (itemName == FARORES_WIND      && FaroresWind)     ||
           (itemName == NAYRUS_LOVE       && NayrusLove)      ||
           (itemName == LENS_OF_TRUTH     && LensOfTruth)     ||
           (itemName == BOW               && Bow)             ||
           (itemName == MEGATON_HAMMER    && Hammer)          ||
           (itemName == IRON_BOOTS        && IronBoots)       ||
           (itemName == HOVER_BOOTS       && HoverBoots)      ||
           (itemName == HOOKSHOT          && Hookshot)        ||
           (itemName == LONGSHOT          && Longshot)        ||
           (itemName == SILVER_GAUNTLETS  && SilverGauntlets) ||
           (itemName == GOLDEN_GAUNTLETS  && GoldenGauntlets) ||
           (itemName == GORON_TUNIC       && GoronTunic)      ||
           (itemName == ZORA_TUNIC        && ZoraTunic)       ||
           (itemName == SCARECROW         && Scarecrow)       ||
           (itemName == DISTANT_SCARECROW && DistantScarecrow)||
           (itemName == SLINGSHOT         && Slingshot)       ||
           (itemName == BOOMERANG         && Boomerang)       ||
           (itemName == KOKIRI_SWORD      && KokiriSword)     ||
           (itemName == STICKS            && Sticks)          ||
           (itemName == DEKU_SHIELD       && DekuShield)      ||
           (itemName == FIRE_ARROWS       && FireArrows)      ||
           (itemName == ICE_ARROWS        && IceArrows)       ||
           (itemName == LIGHT_ARROWS      && LightArrows);

  }

  //Can the passed in item be used?
  bool CanUse(ItemKey itemName) {
    return (IsMagicItem(itemName)  && HasItem(itemName) && MagicMeter) ||
           (IsAdultItem(itemName)  && HasItem(itemName) && IsAdult)    ||
           (IsMagicArrow(itemName) && HasItem(itemName) && MagicMeter  && IsAdult && Bow) ||
           (IsChildItem(itemName)  && HasItem(itemName) && IsChild);
  }

  bool HasProjectile(HasProjectileAge age) {
    return HasExplosives ||
           (age == HasProjectileAge::Child  && (Slingshot || Boomerang)) ||
           (age == HasProjectileAge::Adult  && (Hookshot  || Bow      )) ||
           (age == HasProjectileAge::Both   && (Slingshot || Boomerang)  && (Hookshot || Bow)) ||
           (age == HasProjectileAge::Either && (Slingshot || Boomerang   ||  Hookshot || Bow));
  }

  u8 GetDifficultyValueFromString(Option& glitchOption) {
    for (size_t i = 0; i < GlitchDifficulties.size(); i++) {
      if (glitchOption.GetSelectedOptionText() == GlitchDifficulties[i]) {
        return i + 1;
      }
    }
    return 0;
  }

  bool CanDoGlitch(GlitchType glitch, GlitchDifficulty difficulty) {
    u8 setDifficulty;
    switch (glitch) {
    //Infinite Sword Glitch
    case GlitchType::ISG:
      setDifficulty = GetDifficultyValueFromString(GlitchISG);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return HasShield && (IsAdult || (IsChild && (KokiriSword || Sticks)));
    //Bomb Hover
    case GlitchType::BombHover:
      setDifficulty = GetDifficultyValueFromString(GlitchHover);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) && (HasBombchus || (Bombs && setDifficulty >= static_cast<u8>(GlitchDifficulty::ADVANCED)));
    //Megaflip
    case GlitchType::Megaflip:
      setDifficulty = GetDifficultyValueFromString(GlitchMegaflip);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return HasShield && Bombs;
    //Hookshot Clip
    case GlitchType::HookshotClip:
      setDifficulty = GetDifficultyValueFromString(GlitchHookshotClip);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return IsAdult && Hookshot;
    //Hookshot Jump: Bonk
    case GlitchType::HookshotJump_Bonk:
      setDifficulty = GetDifficultyValueFromString(GlitchHookshotJump_Bonk);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return IsAdult && Hookshot;
    //Hookshot Jump: Boots
    case GlitchType::HookshotJump_Boots:
      setDifficulty = GetDifficultyValueFromString(GlitchHookshotJump_Boots);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return IsAdult && Hookshot && (IronBoots || HoverBoots);
    //Ledge Clip
    case GlitchType::LedgeClip:
      setDifficulty = GetDifficultyValueFromString(GlitchLedgeClip);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return IsAdult;
    //Triple Slash Clip
    case GlitchType::TripleSlashClip:
      setDifficulty = GetDifficultyValueFromString(GlitchTripleSlashClip);
      if (setDifficulty < static_cast<u8>(difficulty)) {
        return false;
      }
      return IsAdult || (IsChild && KokiriSword);
    }
    //Shouldn't be reached
    return false;
  }

  //Updates all logic helpers. Should be called whenever a non-helper is changed
  void UpdateHelpers() {
    Slingshot       = (ProgressiveBulletBag >= 1) && (BuySeed || AmmoCanDrop);
    Ocarina         = ProgressiveOcarina   >= 1;
    OcarinaOfTime   = ProgressiveOcarina   >= 2;
    MagicMeter      = (ProgressiveMagic     >= 1) && (AmmoCanDrop || (HasBottle && (BuyGPotion || BuyBPotion)));
    BombBag         = (ProgressiveBombBag   >= 1) && (BuyBomb || AmmoCanDrop);
    Hookshot        = ProgressiveHookshot  >= 1;
    Longshot        = ProgressiveHookshot  >= 2;
    Bow             = (ProgressiveBow       >= 1) && (BuyArrow || AmmoCanDrop);
    GoronBracelet   = ProgressiveStrength  >= 1;
    SilverGauntlets = ProgressiveStrength  >= 2;
    GoldenGauntlets = ProgressiveStrength  >= 3;
    SilverScale     = ProgressiveScale     >= 1;
    GoldScale       = ProgressiveScale     >= 2;
    AdultsWallet    = ProgressiveWallet    >= 1;

    Scarecrow        = Hookshot && CanPlay(ScarecrowSong);
    DistantScarecrow = Longshot && CanPlay(ScarecrowSong);

    //Drop Access
    DekuStickDrop = StickPot || DekuBabaSticks;
    DekuNutDrop   = (NutPot  || NutCrate         || DekuBabaNuts) && AmmoCanDrop;
    BugsAccess    = BugShrub || WanderingBugs    || BugRock;
    FishAccess    = LoneFish || FishGroup;
    FairyAccess   = FairyPot || GossipStoneFairy || BeanPlantFairy || ButterflyFairy || FreeFairies || FairyPond;


    //refills
    Bombs        = BombBag;
    Nuts         = DekuNutDrop || Nuts;
    Sticks       = DekuStickDrop || Sticks;
    Bugs         = HasBottle && BugsAccess;
    BlueFire     = HasBottle && BlueFireAccess;
    Fish         = HasBottle && FishAccess;
    Fairy        = HasBottle && FairyAccess;

    FoundBombchus   = (BombchuDrop || Bombchus || Bombchus5 || Bombchus10 || Bombchus20);
    CanPlayBowling  = (BombchusInLogic && FoundBombchus) || (!BombchusInLogic && BombBag);
    HasBombchus     = (BuyBombchus5 || BuyBombchus10 || BuyBombchus20 || (AmmoDrops.Is(AMMODROPS_BOMBCHU) && FoundBombchus));
    
    HasExplosives =  Bombs || (BombchusInLogic && HasBombchus);

    //Unshuffled adult trade quest
    Eyedrops     = Eyedrops     || (!ShuffleAdultTradeQuest && ClaimCheck);
    EyeballFrog  = EyeballFrog  || (!ShuffleAdultTradeQuest && Eyedrops);
    Prescription = Prescription || (!ShuffleAdultTradeQuest && EyeballFrog);
    BrokenSword  = BrokenSword  || (!ShuffleAdultTradeQuest && Prescription);
    PoachersSaw  = PoachersSaw  || (!ShuffleAdultTradeQuest && BrokenSword);
    OddPoultice  = OddPoultice  || (!ShuffleAdultTradeQuest && PoachersSaw);
    OddMushroom  = OddMushroom  || (!ShuffleAdultTradeQuest && OddPoultice);
    Cojiro       = Cojiro       || (!ShuffleAdultTradeQuest && OddMushroom);
    PocketEgg    = PocketEgg    || (!ShuffleAdultTradeQuest && Cojiro);

    // IsChild = Age == AGE_CHILD;
    // IsAdult = Age == AGE_ADULT;

    //IsGlitched = false;

    CanBlastOrSmash = HasExplosives || CanUse(MEGATON_HAMMER);
    CanChildAttack  = IsChild && (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse(DINS_FIRE));
    CanChildDamage  = IsChild && (Slingshot ||              Sticks || KokiriSword || HasExplosives || CanUse(DINS_FIRE));
    CanStunDeku     = IsAdult || (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse(DINS_FIRE) || Nuts || DekuShield);
    CanCutShrubs    = IsAdult /*|| Sticks*/ || KokiriSword || Boomerang || HasExplosives;
    CanDive         = ProgressiveScale >= 1;
    CanLeaveForest  = OpenForest.IsNot(OPENFOREST_CLOSED) || IsAdult || DekuTreeClear;
    CanPlantBugs    = IsChild && Bugs;
    CanRideEpona    = IsAdult && Epona && CanPlay(EponasSong);
    CanSummonGossipFairy            = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime || SunsSong);
    CanSummonGossipFairyWithoutSuns = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime);
    CanTakeDamage       = DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) || DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OCTUPLE) || DamageMultiplier.IsNot(DAMAGEMULTIPLIER_SEXDECUPLE) || Fairy || CanUse(NAYRUS_LOVE);
    //CanPlantBean        = IsChild && (MagicBean || MagicBeanPack);
    CanOpenBombGrotto   = CanBlastOrSmash       && (ShardOfAgony || LogicGrottosWithoutAgony);
    CanOpenStormGrotto  = CanPlay(SongOfStorms) && (ShardOfAgony || LogicGrottosWithoutAgony);
    HookshotOrBoomerang = CanUse(HOOKSHOT) || CanUse(BOOMERANG);
    CanGetNightTimeGS = (CanPlay(SunsSong) || !NightGSExpectSuns);

    GuaranteeTradePath     = ShuffleInteriorEntrances || ShuffleOverworldEntrances || LogicBiggoronBolero || CanBlastOrSmash || StopGCRollingGoronAsAdult;
  //GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints != "Agony");
    HasFireSource          = CanUse(DINS_FIRE) || CanUse(FIRE_ARROWS);
    HasFireSourceWithTorch = HasFireSource || (IsChild && Sticks);

    //Gerudo Fortress
    CanFinishGerudoFortress = (GerudoFortress.Is(GERUDOFORTRESS_NORMAL)    && GerudoFortressKeys >= 4 && (IsAdult || KokiriSword) && ((IsAdult && (Bow || Hookshot || HoverBoots)) || GerudoToken || LogicGerudoKitchen)) || //Default GF and 4 keys found
                              (GerudoFortress.Is(GERUDOFORTRESS_NORMAL)    && GerudoFortressKeys >= 1 && GerudoKeys.Is(GERUDOKEYS_PACK) && (IsAdult || KokiriSword) && ((IsAdult && (Bow || Hookshot || HoverBoots)) || GerudoToken || LogicGerudoKitchen)) || //Default GF and 1 key pack found
                              (GerudoFortress.Is(GERUDOFORTRESS_FAST)      && GerudoFortressKeys >= 1 && (IsAdult || KokiriSword)) || //Fast GF and 1 key found
                              (GerudoFortress.IsNot(GERUDOFORTRESS_NORMAL) && GerudoFortress.IsNot(GERUDOFORTRESS_FAST)); //Open GF

    HasShield        = (IsAdult && HylianShield) ||                   (IsChild && DekuShield); //Mirror shield can't reflect attacks
    CanShield        = (IsAdult && (HylianShield || MirrorShield)) || (IsChild && DekuShield);
    CanJumpslash     = IsAdult || Sticks || KokiriSword;
    CanUseProjectile = HasExplosives || (IsAdult && (Bow || Hookshot)) || (IsChild && (Slingshot || Boomerang));

    //Bridge and LACS Requirements
    MedallionCount        = (ForestMedallion ? 1:0) + (FireMedallion ? 1:0) + (WaterMedallion ? 1:0) + (SpiritMedallion ? 1:0) + (ShadowMedallion ? 1:0) + (LightMedallion ? 1:0);
    StoneCount            = (KokiriEmerald ? 1:0) + (GoronRuby ? 1:0) + (ZoraSapphire ? 1:0);
    DungeonCount          = (DekuTreeClear ? 1:0) + (DodongosCavernClear ? 1:0) + (JabuJabusBellyClear ? 1:0) + (ForestTempleClear ? 1:0) + (FireTempleClear ? 1:0) + (WaterTempleClear ? 1:0) + (SpiritTempleClear ? 1:0) + (ShadowTempleClear ? 1:0);
    HasAllStones          = StoneCount == 3;
    HasAllMedallions      = MedallionCount == 6;

    CanBuildRainbowBridge = Bridge.Is(RAINBOWBRIDGE_OPEN)                                                                         ||
                           (Bridge.Is(RAINBOWBRIDGE_VANILLA)    && ShadowMedallion && SpiritMedallion && LightArrows)             ||
                           (Bridge.Is(RAINBOWBRIDGE_STONES)     && StoneCount >= BridgeStoneCount.Value<u8>())                    ||
                           (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS) && MedallionCount >= BridgeMedallionCount.Value<u8>())            ||
                           (Bridge.Is(RAINBOWBRIDGE_REWARDS)    && StoneCount + MedallionCount >= BridgeRewardCount.Value<u8>())  ||
                           (Bridge.Is(RAINBOWBRIDGE_DUNGEONS)   && DungeonCount >= BridgeDungeonCount.Value<u8>())                ||
                           (Bridge.Is(RAINBOWBRIDGE_TOKENS)     && GoldSkulltulaTokens >= BridgeTokenCount.Value<u8>());

    CanTriggerLACS = (LACSCondition == LACSCONDITION_VANILLA    && ShadowMedallion && SpiritMedallion)                          ||
                     (LACSCondition == LACSCONDITION_STONES     && StoneCount >= LACSStoneCount.Value<u8>())                    ||
                     (LACSCondition == LACSCONDITION_MEDALLIONS && MedallionCount >= LACSMedallionCount.Value<u8>())            ||
                     (LACSCondition == LACSCONDITION_REWARDS    && StoneCount + MedallionCount >= LACSRewardCount.Value<u8>())  ||
                     (LACSCondition == LACSCONDITION_DUNGEONS   && DungeonCount >= LACSDungeonCount.Value<u8>())                ||
                     (LACSCondition == LACSCONDITION_TOKENS     && GoldSkulltulaTokens >= LACSTokenCount.Value<u8>());

  }

  bool SmallKeys(u8 dungeonKeyCount, u8 requiredAmount) {
    return (dungeonKeyCount >= requiredAmount);
  }

  bool SmallKeys_ShadowTemple(u8 dungeonKeyCount, u8 requiredAmountGlitchless, u8 requiredAmountGlitched) {
    if (Settings::Logic.Is(LOGIC_GLITCHED) && GetDifficultyValueFromString(GlitchHookshotClip) >= static_cast<u8>(GlitchDifficulty::NOVICE)) {
      return (dungeonKeyCount >= requiredAmountGlitched);
    } else {
      return (dungeonKeyCount >= requiredAmountGlitchless);
    }
  }

  bool EventsUpdated() {

      if (DekuTreeClearPast        != DekuTreeClear        ||
          GoronRubyPast            != GoronRuby            ||
          ZoraSapphirePast         != ZoraSapphire         ||
          ForestTrialClearPast     != ForestTrialClear     ||
          FireTrialClearPast       != FireTrialClear       ||
          WaterTrialClearPast      != WaterTrialClear      ||
          ShadowTrialClearPast     != ShadowTrialClear     ||
          SpiritTrialClearPast     != SpiritTrialClear     ||
          LightTrialClearPast      != LightTrialClear      ||
          DrainWellPast            != DrainWell            ||
          DampesWindmillAccessPast != DampesWindmillAccess ||
          TimeTravelPast           != TimeTravel) {
            DekuTreeClearPast        = DekuTreeClear;
            GoronRubyPast            = GoronRuby;
            ZoraSapphirePast         = ZoraSapphire;
            ForestTrialClearPast     = ForestTrialClear;
            FireTrialClearPast       = FireTrialClear;
            WaterTrialClearPast      = WaterTrialClear;
            ShadowTrialClearPast     = ShadowTrialClear;
            SpiritTrialClearPast     = SpiritTrialClear;
            LightTrialClearPast      = LightTrialClear;
            DrainWellPast            = DrainWell;
            DampesWindmillAccessPast = DampesWindmillAccess;
            return true;
          }
     return false;
   }

   //Reset All Logic to false
   void LogicReset() {
     //Settings-dependent variables
     IsKeysanity = Keysanity.Is(KEYSANITY_ANYWHERE) || Keysanity.Is(KEYSANITY_OVERWORLD) || Keysanity.Is(KEYSANITY_ANY_DUNGEON);
     AmmoCanDrop = AmmoDrops.IsNot(AMMODROPS_NONE);

     //Child item logic
     KokiriSword   = false;
     ZeldasLetter  = false;
     WeirdEgg      = false;
     HasBottle     = false;
     Bombchus      = false;
     Bombchus5     = false;
     Bombchus10    = false;
     Bombchus20    = false;
     MagicBean     = false;
     MagicBeanPack = false;
     RutosLetter   = false;
     Boomerang     = false;
     DinsFire      = false;
     FaroresWind   = false;
     NayrusLove    = false;
     LensOfTruth   = false;
     ShardOfAgony  = false;
     SkullMask     = false;
     MaskOfTruth   = false;

     //Adult logic
     Hammer        = false;
     IronBoots     = false;
     HoverBoots    = false;
     MirrorShield  = false;
     GoronTunic    = false;
     ZoraTunic     = false;
     Epona         = false;
     BigPoe        = false;
     GerudoToken   = false;
     FireArrows    = false;
     IceArrows     = false;
     LightArrows   = false;

     //Trade Quest
     PocketEgg     = false;
     Cojiro        = false;
     OddMushroom   = false;
     OddPoultice   = false;
     PoachersSaw   = false;
     BrokenSword   = false;
     Prescription  = false;
     EyeballFrog   = false;
     Eyedrops      = false;
     ClaimCheck    = false;

     //Trade Quest Events
     WakeUpAdultTalon   = false;
     CojiroAccess       = false;
     OddMushroomAccess  = false;
     OddPoulticeAccess  = false;
     PoachersSawAccess  = false;
     BrokenSwordAccess  = false;
     PrescriptionAccess = false;
     EyeballFrogAccess  = false;
     EyedropsAccess     = false;
     DisableTradeRevert = false;

     //Songs
     ZeldasLullaby    = false;
     SariasSong       = false;
     SunsSong         = false;
     SongOfStorms     = false;
     EponasSong       = false;
     SongOfTime       = false;
     MinuetOfForest   = false;
     BoleroOfFire     = false;
     SerenadeOfWater  = false;
     RequiemOfSpirit  = false;
     NocturneOfShadow = false;
     PreludeOfLight   = false;

     //Stones and Meddallions
     ForestMedallion = false;
     FireMedallion   = false;
     WaterMedallion  = false;
     SpiritMedallion = false;
     ShadowMedallion = false;
     LightMedallion  = false;
     KokiriEmerald   = false;
     GoronRuby       = false;
     ZoraSapphire    = false;

     //Dungeon Clears
     DekuTreeClear       = false;
     DodongosCavernClear = false;
     JabuJabusBellyClear = false;
     ForestTempleClear   = false;
     FireTempleClear     = false;
     WaterTempleClear    = false;
     SpiritTempleClear   = false;
     ShadowTempleClear   = false;

     //Trial Clears
     ForestTrialClear = false;
     FireTrialClear   = false;
     WaterTrialClear  = false;
     SpiritTrialClear = false;
     ShadowTrialClear = false;
     LightTrialClear  = false;

     //Progressive Items
     ProgressiveBulletBag = 0;
     ProgressiveBombBag   = 0;
     ProgressiveMagic     = 0;
     ProgressiveScale     = 0;
     ProgressiveHookshot  = 0;
     ProgressiveBow       = 0;
     ProgressiveWallet    = 0;
     ProgressiveStrength  = 0;
     ProgressiveOcarina   = 0;

     //Keys
     ForestTempleKeys          = 0;
     //If not keysanity, start with 1 logical key to account for automatically unlocking the basement door in vanilla FiT
     FireTempleKeys            = IsKeysanity || Dungeon::FireTemple.IsMQ() ? 0 : 1;
     WaterTempleKeys           = 0;
     SpiritTempleKeys          = 0;
     ShadowTempleKeys          = 0;
     GanonsCastleKeys          = 0;
     GerudoFortressKeys        = 0;
     GerudoTrainingGroundsKeys = 0;
     BottomOfTheWellKeys       = 0;

     //Boss Keys
     BossKeyForestTemple = 0;
     BossKeyFireTemple   = 0;
     BossKeyWaterTemple  = 0;
     BossKeySpiritTemple = 0;
     BossKeyShadowTemple = 0;
     BossKeyGanonsCastle = 0;

     //Gold Skulltula Count
     GoldSkulltulaTokens = 0;



     //Drops and Bottle Contents Access
     DekuNutDrop      = false;
     NutPot           = false;
     NutCrate         = false;
     DekuBabaNuts     = false;
     DekuStickDrop    = false;
     StickPot         = false;
     DekuBabaSticks   = false;
     BugsAccess       = false;
     BugShrub         = false;
     WanderingBugs    = false;
     BugRock          = false;
     BlueFireAccess   = false;
     FishAccess       = false;
     FishGroup        = false;
     LoneFish         = false;
     FairyAccess      = false;
     GossipStoneFairy = false;
     BeanPlantFairy   = false;
     ButterflyFairy   = false;
     FairyPot         = false;
     FreeFairies      = false;
     FairyPond        = false;
     BombchuDrop      = false;

     BuyBombchus5     = false;
     BuyBombchus10    = false;
     BuyBombchus20    = false;
     BuySeed          = false;
     BuyArrow         = false;
     BuyBomb          = false;
     BuyGPotion       = false;
     BuyBPotion       = false;
     MagicRefill      = false;

     /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
     /* These are used to simplify reading the logic, but need to be updated
     /  every time a base value is updated.                       */

     Slingshot        = false;
     Ocarina          = false;
     OcarinaOfTime    = false;
     BombBag          = false;
     MagicMeter       = false;
     Hookshot         = false;
     Longshot         = false;
     Bow              = false;
     GoronBracelet    = false;
     SilverGauntlets  = false;
     GoldenGauntlets  = false;
     SilverScale      = false;
     GoldScale        = false;
     AdultsWallet     = false;

     ScarecrowSong    = false;
     Scarecrow        = false;
     DistantScarecrow = false;

     Bombs            = false;
     DekuShield       = false;
     HylianShield     = false;
     Nuts             = false;
     Sticks           = false;
     Bugs             = false;
     BlueFire         = false;
     Fish             = false;
     Fairy            = false;
     BottleWithBigPoe = false;

     FoundBombchus    = false;
     CanPlayBowling   = false;
     HasBombchus      = false;
     HasExplosives    = false;
     IsChild          = false;
     IsAdult          = false;
   //IsGlitched       = false;
     CanBlastOrSmash  = false;
     CanChildAttack   = false;
     CanChildDamage   = false;
     CanCutShrubs     = false;
     CanDive          = false;
     CanLeaveForest   = false;
     CanPlantBugs     = false;
     CanRideEpona     = false;
     CanStunDeku      = false;
     CanSummonGossipFairy = false;
     CanSummonGossipFairyWithoutSuns = false;
     //CanPlantBean        = false;
     CanOpenBombGrotto   = false;
     CanOpenStormGrotto  = false;
     BigPoeKill          = false;
     HookshotOrBoomerang = false;

     GuaranteeTradePath     = false;
     GuaranteeHint          = false;
     HasFireSource          = false;
     HasFireSourceWithTorch = false;

     CanFinishGerudoFortress = false;

     HasShield        = false;
     CanShield        = false;
     CanJumpslash     = false;
     CanUseProjectile = false;

     //Bridge Requirements
     HasAllStones          = false;
     HasAllMedallions      = false;
     CanBuildRainbowBridge = false;
     CanTriggerLACS        = false;

     //Other
     AtDay         = false;
     AtNight       = false;
     Age           = Settings::ResolvedStartingAge;

     //Events
     ShowedMidoSwordAndShield  = false;
     CarpenterRescue           = false;
     GF_GateOpen               = false;
     DampesWindmillAccess      = false;
     DrainWell                 = false;
     GoronCityChildFire        = false;
     GCWoodsWarpOpen           = false;
     StopGCRollingGoronAsAdult = false;
     ChildWaterTemple          = false;
     KakarikoVillageGateOpen   = false;
     KingZoraThawed            = false;
     ForestTempleJoAndBeth     = false;
     ForestTempleAmyAndMeg     = false;
     LinksCow                  = false;
     AtDampeTime               = false;
     DeliverLetter             = false;
     TimeTravel                = false;

     DrainWellPast            = false;
     DampesWindmillAccessPast = false;
     DekuTreeClearPast        = false;
     GoronRubyPast            = false;
     ZoraSapphirePast         = false;
     ForestTrialClearPast     = false;
     FireTrialClearPast       = false;
     WaterTrialClearPast      = false;
     SpiritTrialClearPast     = false;
     ShadowTrialClearPast     = false;
     LightTrialClearPast      = false;
     BuyDekuShieldPast        = false;
     TimeTravelPast           = false;
   }
}
