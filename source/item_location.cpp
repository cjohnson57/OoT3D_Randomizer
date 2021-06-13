#include "item_location.hpp"

#include "dungeon.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "shops.hpp"
#include "debug.hpp"
#include "keys.hpp"

//Location definitions
static std::array<ItemLocation, KEY_ENUM_MAX> locationTable;

void LocationTable_Init() {
    locationTable[NONE]                                  = ItemLocation::Base       (0xFF, 0xFF, "Invalid Location",                     NONE,                                  {},                                                                                                                   SpoilerCollectionCheck::None());
    //Kokiri Forest                                                                 scene  flag  name                                    hint key (hint_list.cpp)               categories                                                                                                            collection check (if needed)
    locationTable[KF_KOKIRI_SWORD_CHEST]                 = ItemLocation::Chest      (0x55, 0x00, "KF Kokiri Sword Chest",                KF_KOKIRI_SWORD_CHEST,                 {Category::cKokiriForest, Category::cForest,});
    locationTable[KF_MIDOS_TOP_LEFT_CHEST]               = ItemLocation::Chest      (0x28, 0x00, "KF Mido Top Left Chest",               KF_MIDOS_TOP_LEFT_CHEST,               {Category::cKokiriForest, Category::cForest,});
    locationTable[KF_MIDOS_TOP_RIGHT_CHEST]              = ItemLocation::Chest      (0x28, 0x01, "KF Mido Top Right Chest",              KF_MIDOS_TOP_RIGHT_CHEST,              {Category::cKokiriForest, Category::cForest,});
    locationTable[KF_MIDOS_BOTTOM_LEFT_CHEST]            = ItemLocation::Chest      (0x28, 0x02, "KF Mido Bottom Left Chest",            KF_MIDOS_BOTTOM_LEFT_CHEST,            {Category::cKokiriForest, Category::cForest,});
    locationTable[KF_MIDOS_BOTTOM_RIGHT_CHEST]           = ItemLocation::Chest      (0x28, 0x03, "KF Mido Bottom Right Chest",           KF_MIDOS_BOTTOM_RIGHT_CHEST,           {Category::cKokiriForest, Category::cForest,});
    locationTable[KF_STORMS_GROTTO_CHEST]                = ItemLocation::Chest      (0x3E, 0x0C, "KF Storms Grotto Chest",               KF_STORMS_GROTTO_CHEST,                {Category::cKokiriForest, Category::cForest, Category::cGrotto});

    //Lost Woods
    locationTable[LW_NEAR_SHORTCUTS_GROTTO_CHEST]        = ItemLocation::Chest      (0x3E, 0x14, "LW Near Shortcuts Grotto Chest",       LW_NEAR_SHORTCUTS_GROTTO_CHEST,        {Category::cLostWoods, Category::cForest, Category::cGrotto});
    locationTable[LW_SKULL_KID]                          = ItemLocation::Base       (0x5B, 0x3E, "LW Skull Kid",                         LW_SKULL_KID,                          {Category::cLostWoods, Category::cForest,},                                                                           SpoilerCollectionCheck::ItemGetInf(30));
    locationTable[LW_OCARINA_MEMORY_GAME]                = ItemLocation::Base       (0x5B, 0x76, "LW Ocarina Memory Game",               LW_OCARINA_MEMORY_GAME,                {Category::cLostWoods, Category::cForest, Category::cMinigame},                                                       SpoilerCollectionCheck::ItemGetInf(31));
    locationTable[LW_TARGET_IN_WOODS]                    = ItemLocation::Base       (0x5B, 0x60, "LW Target in Woods",                   LW_TARGET_IN_WOODS,                    {Category::cLostWoods, Category::cForest,},                                                                           SpoilerCollectionCheck::ItemGetInf(21));
    locationTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT] = ItemLocation::Base       (0x5B, 0x30, "LW Deku Scrub Near Deku Theater Right",LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
    locationTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT]  = ItemLocation::Base       (0x5B, 0x31, "LW Deku Scrub Near Deku Theater Left", LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,  {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
    locationTable[LW_DEKU_SCRUB_NEAR_BRIDGE]             = ItemLocation::Base       (0x5B, 0x77, "LW Deku Scrub Near Bridge",            LW_DEKU_SCRUB_NEAR_BRIDGE,             {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades},                        SpoilerCollectionCheck::InfTable(0x19, 0x0A));
    locationTable[LW_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(0xF5, 0x33, "LW Deku Scrub Grotto Rear",            LW_DEKU_SCRUB_GROTTO_REAR,             {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cGrotto});
    locationTable[LW_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(0xF5, 0x79, "LW Deku Scrub Grotto Front",           LW_DEKU_SCRUB_GROTTO_FRONT,            {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto},     SpoilerCollectionCheck::InfTable(0x19, 0x0B));
    locationTable[DEKU_THEATER_SKULL_MASK]               = ItemLocation::Base       (0x3E, 0x77, "Deku Theater Skull Mask",              DEKU_THEATER_SKULL_MASK,               {Category::cLostWoods, Category::cForest, Category::cGrotto},                                                         SpoilerCollectionCheck::ItemGetInf(22));
    locationTable[DEKU_THEATER_MASK_OF_TRUTH]            = ItemLocation::Base       (0x3E, 0x7A, "Deku Theater Mask of Truth",           DEKU_THEATER_MASK_OF_TRUTH,            {Category::cLostWoods, Category::cForest, Category::cNeedSpiritualStones, Category::cGrotto},                         SpoilerCollectionCheck::ItemGetInf(23));

    //Sacred Forest Meadow
    locationTable[SFM_WOLFOS_GROTTO_CHEST]               = ItemLocation::Chest      (0x3E, 0x11, "SFM Wolfos Grotto Chest",              SFM_WOLFOS_GROTTO_CHEST,               {Category::cSacredForestMeadow, Category::cForest, Category::cGrotto});
    locationTable[SFM_DEKU_SCRUB_GROTTO_REAR]            = ItemLocation::GrottoScrub(0xEE, 0x39, "SFM Deku Scrub Grotto Rear",           SFM_DEKU_SCRUB_GROTTO_REAR,            {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});
    locationTable[SFM_DEKU_SCRUB_GROTTO_FRONT]           = ItemLocation::GrottoScrub(0xEE, 0x3A, "SFM Deku Scrub Grotto Front",          SFM_DEKU_SCRUB_GROTTO_FRONT,           {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});

    //Hyrule Field
    locationTable[HF_SOUTHEAST_GROTTO_CHEST]             = ItemLocation::Chest      (0x3E, 0x02, "HF Southeast Grotto Chest",            HF_SOUTHEAST_GROTTO_CHEST,             {Category::cHyruleField, Category::cGrotto,});
    locationTable[HF_OPEN_GROTTO_CHEST]                  = ItemLocation::Chest      (0x3E, 0x03, "HF Open Grotto Chest",                 HF_OPEN_GROTTO_CHEST,                  {Category::cHyruleField, Category::cGrotto,});
    locationTable[HF_NEAR_MARKET_GROTTO_CHEST]           = ItemLocation::Chest      (0x3E, 0x00, "HF Near Market Grotto Chest",          HF_NEAR_MARKET_GROTTO_CHEST,           {Category::cHyruleField, Category::cGrotto,});
    locationTable[HF_OCARINA_OF_TIME_ITEM]               = ItemLocation::Base       (0x51, 0x0C, "HF Ocarina of Time Item",              HF_OCARINA_OF_TIME_ITEM,               {Category::cHyruleField, Category::cNeedSpiritualStones,},                                                            SpoilerCollectionCheck::EventChkInf(0x43));
    locationTable[HF_TEKTITE_GROTTO_FREESTANDING_POH]    = ItemLocation::Collectable(0x3E, 0x01, "HF Tektite Grotto Freestanding PoH",   HF_TEKTITE_GROTTO_FREESTANDING_POH,    {Category::cHyruleField, Category::cGrotto,});
    locationTable[HF_DEKU_SCRUB_GROTTO]                  = ItemLocation::GrottoScrub(0xE6, 0x3E, "HF Deku Scrub Grotto",                 HF_DEKU_SCRUB_GROTTO,                  {Category::cHyruleField, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto},                      SpoilerCollectionCheck::ItemGetInf(3));

    //Lake Hylia
    locationTable[LH_CHILD_FISHING]                      = ItemLocation::Base       (0x49, 0x3E, "LH Child Fishing",                     LH_CHILD_FISHING,                      {Category::cLakeHylia, Category::cMinigame,},                                                                         SpoilerCollectionCheck::Minigame(0x05, 0x02));
    locationTable[LH_ADULT_FISHING]                      = ItemLocation::Base       (0x49, 0x38, "LH Adult Fishing",                     LH_ADULT_FISHING,                      {Category::cLakeHylia, Category::cMinigame,},                                                                         SpoilerCollectionCheck::Minigame(0x05, 0x03));
    locationTable[LH_LAB_DIVE]                           = ItemLocation::Base       (0x38, 0x3E, "LH Lab Dive",                          LH_LAB_DIVE,                           {Category::cLakeHylia,},                                                                                              SpoilerCollectionCheck::ItemGetInf(24));
    locationTable[LH_UNDERWATER_ITEM]                    = ItemLocation::Base       (0x57, 0x15, "LH Underwater Item",                   LH_UNDERWATER_ITEM,                    {Category::cLakeHylia,},                                                                                              SpoilerCollectionCheck::EventChkInf(0x31));
    locationTable[LH_SUN]                                = ItemLocation::Base       (0x57, 0x58, "LH Sun",                               LH_SUN,                                {Category::cLakeHylia,});
    locationTable[LH_FREESTANDING_POH]                   = ItemLocation::Collectable(0x57, 0x1E, "LH Freestanding PoH",                  LH_FREESTANDING_POH,                   {Category::cLakeHylia,});
    locationTable[LH_DEKU_SCRUB_GROTTO_LEFT]             = ItemLocation::GrottoScrub(0xEF, 0x30, "LH Deku Scrub Grotto Left",            LH_DEKU_SCRUB_GROTTO_LEFT,             {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
    locationTable[LH_DEKU_SCRUB_GROTTO_RIGHT]            = ItemLocation::GrottoScrub(0xEF, 0x37, "LH Deku Scrub Grotto Right",           LH_DEKU_SCRUB_GROTTO_RIGHT,            {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
    locationTable[LH_DEKU_SCRUB_GROTTO_CENTER]           = ItemLocation::GrottoScrub(0xEF, 0x33, "LH Deku Scrub Grotto Center",          LH_DEKU_SCRUB_GROTTO_CENTER,           {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});

    //Gerudo Valley
    locationTable[GV_CHEST]                              = ItemLocation::Chest      (0x5A, 0x00, "GV Chest",                             GV_CHEST,                              {Category::cGerudoValley, Category::cGerudo,});
    locationTable[GV_WATERFALL_FREESTANDING_POH]         = ItemLocation::Collectable(0x5A, 0x01, "GV Waterfall Freestanding PoH",        GV_WATERFALL_FREESTANDING_POH,         {Category::cGerudoValley, Category::cGerudo,});
    locationTable[GV_CRATE_FREESTANDING_POH]             = ItemLocation::Collectable(0x5A, 0x02, "GV Crate Freestanding PoH",            GV_CRATE_FREESTANDING_POH,             {Category::cGerudoValley, Category::cGerudo,});
    locationTable[GV_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(0xF0, 0x39, "GV Deku Scrub Grotto Rear",            GV_DEKU_SCRUB_GROTTO_REAR,             {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});
    locationTable[GV_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(0xF0, 0x3A, "GV Deku Scrub Grotto Front",           GV_DEKU_SCRUB_GROTTO_FRONT,            {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});

    //Gerudo Fortress
    locationTable[GF_CHEST]                              = ItemLocation::Chest      (0x5D, 0x00, "GF Chest",                             GF_CHEST,                              {Category::cGerudoFortress, Category::cGerudo,});
    locationTable[GF_HBA_1000_POINTS]                    = ItemLocation::Base       (0x5D, 0x3E, "GF HBA 1000 Points",                   GF_HBA_1000_POINTS,                    {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame},                                                  SpoilerCollectionCheck::InfTable(0x19, 0x08));
    locationTable[GF_HBA_1500_POINTS]                    = ItemLocation::Base       (0x5D, 0x30, "GF HBA 1500 Points",                   GF_HBA_1500_POINTS,                    {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame},                                                  SpoilerCollectionCheck::ItemGetInf(7));
    locationTable[GF_GERUDO_TOKEN]                       = ItemLocation::Base       (0x0C, 0x3A, "GF Gerudo Token",                      GF_GERUDO_TOKEN,                       {Category::cGerudoFortress, Category::cGerudo,});
    locationTable[GF_NORTH_F1_CARPENTER]                 = ItemLocation::Collectable(0x0C, 0x0C, "GF North F1 Carpenter",                GF_NORTH_F1_CARPENTER,                 {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey},                                         SpoilerCollectionCheck::EventChkInf(0x90));
    locationTable[GF_NORTH_F2_CARPENTER]                 = ItemLocation::Collectable(0x0C, 0x0A, "GF North F2 Carpenter",                GF_NORTH_F2_CARPENTER,                 {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey},                                         SpoilerCollectionCheck::EventChkInf(0x91));
    locationTable[GF_SOUTH_F1_CARPENTER]                 = ItemLocation::Collectable(0x0C, 0x0E, "GF South F1 Carpenter",                GF_SOUTH_F1_CARPENTER,                 {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey},                                         SpoilerCollectionCheck::EventChkInf(0x92));
    locationTable[GF_SOUTH_F2_CARPENTER]                 = ItemLocation::Collectable(0x0C, 0x0F, "GF South F2 Carpenter",                GF_SOUTH_F2_CARPENTER,                 {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey},                                         SpoilerCollectionCheck::EventChkInf(0x93));

    //Haunted Wasteland
    locationTable[WASTELAND_CHEST]                       = ItemLocation::Chest      (0x5E, 0x00, "Wasteland Chest",                      WASTELAND_CHEST,                       {Category::cHauntedWasteland,});

    //Desert Colossus
    locationTable[COLOSSUS_FREESTANDING_POH]             = ItemLocation::Collectable(0x5C, 0x0D, "Colossus Freestanding PoH",            COLOSSUS_FREESTANDING_POH,             {Category::cDesertColossus,});
    locationTable[COLOSSUS_DEKU_SCRUB_GROTTO_REAR]       = ItemLocation::GrottoScrub(0xFD, 0x39, "Colossus Deku Scrub Grotto Rear",      COLOSSUS_DEKU_SCRUB_GROTTO_REAR,       {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});
    locationTable[COLOSSUS_DEKU_SCRUB_GROTTO_FRONT]      = ItemLocation::GrottoScrub(0xFD, 0x3A, "Colossus Deku Scrub Grotto Front",     COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,      {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});

    //Market
    locationTable[MARKET_TREASURE_CHEST_GAME_REWARD]     = ItemLocation::Chest      (0x10, 0x0A, "MK Treasure Chest Game Reward",        MARKET_TREASURE_CHEST_GAME_REWARD,     {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
    locationTable[MARKET_BOMBCHU_BOWLING_FIRST_PRIZE]    = ItemLocation::Base       (0x4B, 0x33, "MK Bombchu Bowling First Prize",       MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,    {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
    locationTable[MARKET_BOMBCHU_BOWLING_SECOND_PRIZE]   = ItemLocation::Base       (0x4B, 0x3E, "MK Bombchu Bowling Second Prize",      MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,   {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
    locationTable[MARKET_BOMBCHU_BOWLING_BOMBCHUS]       = ItemLocation::Base       (0x4B, 0xFF, "MK Bombchu Bowling Bombchus",          NONE,                                  {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
    locationTable[MARKET_LOST_DOG]                       = ItemLocation::Base       (0x35, 0x3E, "MK Lost Dog",                          MARKET_LOST_DOG,                       {Category::cInnerMarket, Category::cMarket,},                                                                         SpoilerCollectionCheck::InfTable(0x19, 0x09));
    locationTable[MARKET_SHOOTING_GALLERY_REWARD]        = ItemLocation::Base       (0x42, 0x60, "MK Shooting Gallery",                  MARKET_SHOOTING_GALLERY_REWARD,        {Category::cInnerMarket, Category::cMarket, Category::cMinigame},                                                     SpoilerCollectionCheck::ItemGetInf(21));
    locationTable[MARKET_10_BIG_POES]                    = ItemLocation::Base       (0x4D, 0x0F, "MK 10 Big Poes",                       MARKET_10_BIG_POES,                    {Category::cInnerMarket, Category::cMarket,});

    //Hyrule Castle
    locationTable[HC_MALON_EGG]                          = ItemLocation::Base       (0x5F, 0x47, "HC Malon Egg",                         HC_MALON_EGG,                          {Category::cHyruleCastle, Category::cMarket,},                                                                        SpoilerCollectionCheck::EventChkInf(0x12));
    locationTable[HC_ZELDAS_LETTER]                      = ItemLocation::Base       (0x4A, 0x0B, "HC Zeldas Letter",                     HC_ZELDAS_LETTER,                      {Category::cHyruleCastle, Category::cMarket,},                                                                        SpoilerCollectionCheck::EventChkInf(0x40));

    //Kakariko
    locationTable[KAK_REDEAD_GROTTO_CHEST]               = ItemLocation::Chest      (0x3E, 0x0A, "Kak Redead Grotto Chest",              KAK_REDEAD_GROTTO_CHEST,               {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
    locationTable[KAK_OPEN_GROTTO_CHEST]                 = ItemLocation::Chest      (0x3E, 0x08, "Kak Open Grotto Chest",                KAK_OPEN_GROTTO_CHEST,                 {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
    locationTable[KAK_10_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (0x50, 0x45, "Kak 10 Gold Skulltula Reward",         KAK_10_GOLD_SKULLTULA_REWARD,          {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse},                                         SpoilerCollectionCheck::EventChkInf(0xDA));
    locationTable[KAK_20_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (0x50, 0x39, "Kak 20 Gold Skulltula Reward",         KAK_20_GOLD_SKULLTULA_REWARD,          {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse},                                         SpoilerCollectionCheck::EventChkInf(0xDB));
    locationTable[KAK_30_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (0x50, 0x46, "Kak 30 Gold Skulltula Reward",         KAK_30_GOLD_SKULLTULA_REWARD,          {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse},                                         SpoilerCollectionCheck::EventChkInf(0xDC));
    locationTable[KAK_40_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (0x50, 0x03, "Kak 40 Gold Skulltula Reward",         KAK_40_GOLD_SKULLTULA_REWARD,          {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse},                                         SpoilerCollectionCheck::EventChkInf(0xDD));
    locationTable[KAK_50_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (0x50, 0x3E, "Kak 50 Gold Skulltula Reward",         KAK_50_GOLD_SKULLTULA_REWARD,          {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse},                                         SpoilerCollectionCheck::EventChkInf(0xDE));
    locationTable[KAK_MAN_ON_ROOF]                       = ItemLocation::Base       (0x52, 0x3E, "Kak Man on Roof",                      KAK_MAN_ON_ROOF,                       {Category::cKakarikoVillage, Category::cKakariko,},                                                                   SpoilerCollectionCheck::ItemGetInf(29));
    locationTable[KAK_SHOOTING_GALLERY_REWARD]           = ItemLocation::Base       (0x42, 0x30, "Kak Shooting Gallery Reward",          KAK_SHOOTING_GALLERY_REWARD,           {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame},                                               SpoilerCollectionCheck::ItemGetInf(6));
    locationTable[KAK_ANJU_AS_ADULT]                     = ItemLocation::Base       (0x52, 0x1D, "Kak Anju as Adult",                    KAK_ANJU_AS_ADULT,                     {Category::cKakarikoVillage, Category::cKakariko,},                                                                   SpoilerCollectionCheck::ItemGetInf(36));
    locationTable[KAK_ANJU_AS_CHILD]                     = ItemLocation::Base       (0x52, 0x0F, "Kak Anju as Child",                    KAK_ANJU_AS_CHILD,                     {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame},                                               SpoilerCollectionCheck::ItemGetInf(4));
    locationTable[KAK_IMPAS_HOUSE_FREESTANDING_POH]      = ItemLocation::Collectable(0x37, 0x01, "Kak Impas House Freestanding PoH",     KAK_IMPAS_HOUSE_FREESTANDING_POH,      {Category::cKakarikoVillage, Category::cKakariko,});
    locationTable[KAK_WINDMILL_FREESTANDING_POH]         = ItemLocation::Collectable(0x48, 0x01, "Kak Windmill Freestanding PoH",        KAK_WINDMILL_FREESTANDING_POH,         {Category::cKakarikoVillage, Category::cKakariko,});

    //Graveyard
    locationTable[GRAVEYARD_SHIELD_GRAVE_CHEST]          = ItemLocation::Chest      (0x40, 0x00, "GY Shield Grave Chest",                GRAVEYARD_SHIELD_GRAVE_CHEST,          {Category::cGraveyard, Category::cKakariko,});
    locationTable[GRAVEYARD_HEART_PIECE_GRAVE_CHEST]     = ItemLocation::Chest      (0x3F, 0x00, "GY Heart Piece Grave Chest",           GRAVEYARD_HEART_PIECE_GRAVE_CHEST,     {Category::cGraveyard, Category::cKakariko,});
    locationTable[GRAVEYARD_COMPOSERS_GRAVE_CHEST]       = ItemLocation::Chest      (0x41, 0x00, "GY Composers Grave Chest",             GRAVEYARD_COMPOSERS_GRAVE_CHEST,       {Category::cGraveyard, Category::cKakariko,});
    locationTable[GRAVEYARD_HOOKSHOT_CHEST]              = ItemLocation::Chest      (0x48, 0x00, "GY Hookshot Chest",                    GRAVEYARD_HOOKSHOT_CHEST,              {Category::cGraveyard, Category::cKakariko,});
    locationTable[GRAVEYARD_DAMPE_RACE_FREESTANDING_POH] = ItemLocation::Collectable(0x48, 0x07, "GY Dampe Race Freestanding PoH",       GRAVEYARD_DAMPE_RACE_FREESTANDING_POH, {Category::cGraveyard, Category::cKakariko, Category::cMinigame});
    locationTable[GRAVEYARD_FREESTANDING_POH]            = ItemLocation::Collectable(0x53, 0x04, "GY Freestanding PoH",                  GRAVEYARD_FREESTANDING_POH,            {Category::cGraveyard, Category::cKakariko,});
    locationTable[GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR]     = ItemLocation::Collectable(0x53, 0x08, "GY Dampe Gravedigging Tour",           GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,     {Category::cGraveyard, Category::cKakariko,},                                                                         SpoilerCollectionCheck::ItemGetInf(20));

    //Death Mountain
    locationTable[DMT_CHEST]                             = ItemLocation::Chest      (0x60, 0x01, "DMT Chest",                            DMT_CHEST,                             {Category::cDeathMountainTrail, Category::cDeathMountain,});
    locationTable[DMT_STORMS_GROTTO_CHEST]               = ItemLocation::Chest      (0x3E, 0x17, "DMT Storms Grotto Chest",              DMT_STORMS_GROTTO_CHEST,               {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cGrotto});
    locationTable[DMT_BIGGORON]                          = ItemLocation::Base       (0x60, 0x57, "DMT Biggoron",                         DMT_BIGGORON,                          {Category::cDeathMountainTrail, Category::cDeathMountain,});
    locationTable[DMT_FREESTANDING_POH]                  = ItemLocation::Collectable(0x60, 0x1E, "DMT Freestanding PoH",                 DMT_FREESTANDING_POH,                  {Category::cDeathMountainTrail, Category::cDeathMountain,});

    //Goron City
    locationTable[GC_MAZE_LEFT_CHEST]                    = ItemLocation::Chest      (0x62, 0x00, "GC Maze Left Chest",                   GC_MAZE_LEFT_CHEST,                    {Category::cGoronCity,});
    locationTable[GC_MAZE_RIGHT_CHEST]                   = ItemLocation::Chest      (0x62, 0x01, "GC Maze Right Chest",                  GC_MAZE_RIGHT_CHEST,                   {Category::cGoronCity,});
    locationTable[GC_MAZE_CENTER_CHEST]                  = ItemLocation::Chest      (0x62, 0x02, "GC Maze Center Chest",                 GC_MAZE_CENTER_CHEST,                  {Category::cGoronCity,});
    locationTable[GC_ROLLING_GORON_AS_CHILD]             = ItemLocation::Base       (0x62, 0x34, "GC Rolling Goron as Child",            GC_ROLLING_GORON_AS_CHILD,             {Category::cGoronCity,},                                                                                              SpoilerCollectionCheck::InfTable(0x11, 0x06));
    locationTable[GC_ROLLING_GORON_AS_ADULT]             = ItemLocation::Base       (0x62, 0x2C, "GC Rolling Goron as Adult",            GC_ROLLING_GORON_AS_ADULT,             {Category::cGoronCity,},                                                                                              SpoilerCollectionCheck::InfTable(0x10, 0x01));
    locationTable[GC_DARUNIAS_JOY]                       = ItemLocation::Base       (0x62, 0x54, "GC Darunias Joy",                      GC_DARUNIAS_JOY,                       {Category::cGoronCity,});
    locationTable[GC_POT_FREESTANDING_POH]               = ItemLocation::Collectable(0x62, 0x1F, "GC Pot Freestanding PoH",              GC_POT_FREESTANDING_POH,               {Category::cGoronCity,});
    locationTable[GC_DEKU_SCRUB_GROTTO_LEFT]             = ItemLocation::GrottoScrub(0xFB, 0x30, "GC Deku Scrub Grotto Left",            GC_DEKU_SCRUB_GROTTO_LEFT,             {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
    locationTable[GC_DEKU_SCRUB_GROTTO_RIGHT]            = ItemLocation::GrottoScrub(0xFB, 0x37, "GC Deku Scrub Grotto Right",           GC_DEKU_SCRUB_GROTTO_RIGHT,            {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
    locationTable[GC_DEKU_SCRUB_GROTTO_CENTER]           = ItemLocation::GrottoScrub(0xFB, 0x33, "GC Deku Scrub Grotto Center",          GC_DEKU_SCRUB_GROTTO_CENTER,           {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});

    //Death Mountain Crater
    locationTable[DMC_UPPER_GROTTO_CHEST]                = ItemLocation::Chest      (0x3E, 0x1A, "DMC Upper Grotto Chest",               DMC_UPPER_GROTTO_CHEST,                {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cGrotto});
    locationTable[DMC_WALL_FREESTANDING_POH]             = ItemLocation::Collectable(0x61, 0x02, "DMC Wall Freestanding PoH",            DMC_WALL_FREESTANDING_POH,             {Category::cDeathMountainCrater, Category::cDeathMountain,});
    locationTable[DMC_VOLCANO_FREESTANDING_POH]          = ItemLocation::Collectable(0x61, 0x08, "DMC Volcano Freestanding PoH",         DMC_VOLCANO_FREESTANDING_POH,          {Category::cDeathMountainCrater, Category::cDeathMountain,});
    locationTable[DMC_DEKU_SCRUB]                        = ItemLocation::Base       (0x61, 0x37, "DMC Deku Scrub",                       DMC_DEKU_SCRUB,                        {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub});
    locationTable[DMC_DEKU_SCRUB_GROTTO_LEFT]            = ItemLocation::GrottoScrub(0xF9, 0x30, "DMC Deku Scrub Grotto Left",           DMC_DEKU_SCRUB_GROTTO_LEFT,            {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
    locationTable[DMC_DEKU_SCRUB_GROTTO_RIGHT]           = ItemLocation::GrottoScrub(0xF9, 0x37, "DMC Deku Scrub Grotto Right",          DMC_DEKU_SCRUB_GROTTO_RIGHT,           {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
    locationTable[DMC_DEKU_SCRUB_GROTTO_CENTER]          = ItemLocation::GrottoScrub(0xF9, 0x33, "DMC Deku Scrub Grotto Center",         DMC_DEKU_SCRUB_GROTTO_CENTER,          {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});

    //Zoras River
    locationTable[ZR_OPEN_GROTTO_CHEST]                  = ItemLocation::Chest      (0x3E, 0x09, "ZR Open Grotto Chest",                 ZR_OPEN_GROTTO_CHEST,                  {Category::cZorasRiver, Category::cGrotto,});
    locationTable[ZR_MAGIC_BEAN_SALESMAN]                = ItemLocation::Base       (0x54, 0x16, "ZR Magic Bean Salesman",               ZR_MAGIC_BEAN_SALESMAN,                {Category::cZorasRiver,},                                                                                             SpoilerCollectionCheck::Collectable(0x54, 0x01));
    locationTable[ZR_FROGS_OCARINA_GAME]                 = ItemLocation::Base       (0x54, 0x76, "ZR Frogs Ocarina Game",                ZR_FROGS_OCARINA_GAME,                 {Category::cZorasRiver,},                                                                                             SpoilerCollectionCheck::EventChkInf(0xD6));
    locationTable[ZR_FROGS_IN_THE_RAIN]                  = ItemLocation::Base       (0x54, 0x3E, "ZR Frogs in the Rain",                 ZR_FROGS_IN_THE_RAIN,                  {Category::cZorasRiver, Category::cMinigame,},                                                                        SpoilerCollectionCheck::EventChkInf(0xD0));
    locationTable[ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH]  = ItemLocation::Collectable(0x54, 0x04, "ZR Near Open Grotto Freestanding PoH", ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,  {Category::cZorasRiver,});
    locationTable[ZR_NEAR_DOMAIN_FREESTANDING_POH]       = ItemLocation::Collectable(0x54, 0x0B, "ZR Near Domain Freestanding PoH",      ZR_NEAR_DOMAIN_FREESTANDING_POH,       {Category::cZorasRiver,});
    locationTable[ZR_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(0xEB, 0x39, "ZR Deku Scrub Grotto Rear",            ZR_DEKU_SCRUB_GROTTO_REAR,             {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});
    locationTable[ZR_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(0xEB, 0x3A, "ZR Deku Scrub Grotto Front",           ZR_DEKU_SCRUB_GROTTO_FRONT,            {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});

    //Zoras Domain
    locationTable[ZD_CHEST]                              = ItemLocation::Chest      (0x58, 0x00, "ZD Chest",                             ZD_CHEST,                              {Category::cZorasDomain,});
    locationTable[ZD_DIVING_MINIGAME]                    = ItemLocation::Base       (0x58, 0x37, "ZD Diving Minigame",                   ZD_DIVING_MINIGAME,                    {Category::cZorasDomain, Category::cMinigame,},                                                                       SpoilerCollectionCheck::EventChkInf(0x38));
    locationTable[ZD_KING_ZORA_THAWED]                   = ItemLocation::Base       (0x58, 0x2D, "ZD King Zora Thawed",                  ZD_KING_ZORA_THAWED,                   {Category::cZorasDomain,},                                                                                            SpoilerCollectionCheck::InfTable(0x13, 0x01));

    //Zoras Fountain
    locationTable[ZF_ICEBERG_FREESTANDING_POH]           = ItemLocation::Collectable(0x59, 0x01, "ZF Iceberg Freestanding PoH",          ZF_ICEBERG_FREESTANDING_POH,           {Category::cZorasFountain,});
    locationTable[ZF_BOTTOM_FREESTANDING_POH]            = ItemLocation::Collectable(0x59, 0x14, "ZF Bottom Freestanding PoH",           ZF_BOTTOM_FREESTANDING_POH,            {Category::cZorasFountain,});

    //Lon Lon Ranch
    locationTable[LLR_TALONS_CHICKENS]                   = ItemLocation::Base       (0x4C, 0x14, "LLR Talons Chickens",                  LLR_TALONS_CHICKENS,                   {Category::cLonLonRanch, Category::cMinigame},                                                                        SpoilerCollectionCheck::ItemGetInf(10));
    locationTable[LLR_FREESTANDING_POH]                  = ItemLocation::Collectable(0x4C, 0x01, "LLR Freestanding PoH",                 LLR_FREESTANDING_POH,                  {Category::cLonLonRanch,});
    locationTable[LLR_DEKU_SCRUB_GROTTO_LEFT]            = ItemLocation::GrottoScrub(0xFC, 0x30, "LLR Deku Scrub Grotto Left",           LLR_DEKU_SCRUB_GROTTO_LEFT,            {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
    locationTable[LLR_DEKU_SCRUB_GROTTO_RIGHT]           = ItemLocation::GrottoScrub(0xFC, 0x37, "LLR Deku Scrub Grotto Right",          LLR_DEKU_SCRUB_GROTTO_RIGHT,           {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
    locationTable[LLR_DEKU_SCRUB_GROTTO_CENTER]          = ItemLocation::GrottoScrub(0xFC, 0x33, "LLR Deku Scrub Grotto Center",         LLR_DEKU_SCRUB_GROTTO_CENTER,          {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});

    /*-------------------
       --- DUNGEONS ---
      -------------------*/

    //Deku Tree Vanilla
    locationTable[DEKU_TREE_MAP_CHEST]                                         = ItemLocation::Chest      (0x00, 0x03, "Deku Tree Map Chest",                                DEKU_TREE_MAP_CHEST,                    {Category::cDekuTree, Category::cVanillaMap,});
    locationTable[DEKU_TREE_COMPASS_CHEST]                                     = ItemLocation::Chest      (0x00, 0x02, "Deku Tree Compass Chest",                            DEKU_TREE_COMPASS_CHEST,                {Category::cDekuTree, Category::cVanillaCompass,});
    locationTable[DEKU_TREE_COMPASS_ROOM_SIDE_CHEST]                           = ItemLocation::Chest      (0x00, 0x06, "Deku Tree Compass Room Side Chest",                  DEKU_TREE_COMPASS_ROOM_SIDE_CHEST,      {Category::cDekuTree,});
    locationTable[DEKU_TREE_BASEMENT_CHEST]                                    = ItemLocation::Chest      (0x00, 0x04, "Deku Tree Basement Chest",                           DEKU_TREE_BASEMENT_CHEST,               {Category::cDekuTree,});
    locationTable[DEKU_TREE_SLINGSHOT_CHEST]                                   = ItemLocation::Chest      (0x00, 0x01, "Deku Tree Slingshot Chest",                          DEKU_TREE_SLINGSHOT_CHEST,              {Category::cDekuTree,});
    locationTable[DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST]                         = ItemLocation::Chest      (0x00, 0x05, "Deku Tree Slingshot Room Side Chest",                DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST,    {Category::cDekuTree,});
    //Deku Tree MQ
    locationTable[DEKU_TREE_MQ_MAP_CHEST]                                      = ItemLocation::Chest      (0x00, 0x03, "Deku Tree MQ Map Chest",                             DEKU_TREE_MQ_MAP_CHEST,                 {Category::cDekuTree, Category::cVanillaMap,});
    locationTable[DEKU_TREE_MQ_COMPASS_CHEST]                                  = ItemLocation::Chest      (0x00, 0x01, "Deku Tree MQ Compass Chest",                         DEKU_TREE_MQ_COMPASS_CHEST,             {Category::cDekuTree, Category::cVanillaCompass,});
    locationTable[DEKU_TREE_MQ_SLINGSHOT_CHEST]                                = ItemLocation::Chest      (0x00, 0x06, "Deku Tree MQ Slingshot Chest",                       DEKU_TREE_MQ_SLINGSHOT_CHEST,           {Category::cDekuTree,});
    locationTable[DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST]                      = ItemLocation::Chest      (0x00, 0x02, "Deku Tree MQ Slingshot Room Back Chest",             DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, {Category::cDekuTree,});
    locationTable[DEKU_TREE_MQ_BASEMENT_CHEST]                                 = ItemLocation::Chest      (0x00, 0x04, "Deku Tree MQ Basement Chest",                        DEKU_TREE_MQ_BASEMENT_CHEST,            {Category::cDekuTree,});
    locationTable[DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST]                      = ItemLocation::Chest      (0x00, 0x05, "Deku Tree MQ Before Spinning Log Chest",             DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, {Category::cDekuTree,});
    locationTable[DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST]                       = ItemLocation::Chest      (0x00, 0x00, "Deku Tree MQ After Spinning Log Chest",              DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST,  {Category::cDekuTree,});
    locationTable[DEKU_TREE_MQ_DEKU_SCRUB]                                     = ItemLocation::Base       (0x00, 0x34, "Deku Tree MQ Deku Scrub",                            DEKU_TREE_MQ_DEKU_SCRUB,                {Category::cDekuTree,});

    //Dodongos Cavern Shared
    locationTable[DODONGOS_CAVERN_BOSS_ROOM_CHEST]                             = ItemLocation::Chest      (0x12, 0x00, "Dodongos Cavern Boss Room Chest",                    DODONGOS_CAVERN_BOSS_ROOM_CHEST,                 {Category::cDodongosCavern,});
    //Dodongos Cavern Vanilla
    locationTable[DODONGOS_CAVERN_MAP_CHEST]                                   = ItemLocation::Chest      (0x01, 0x08, "Dodongos Cavern Map Chest",                          DODONGOS_CAVERN_MAP_CHEST,                          {Category::cDodongosCavern, Category::cVanillaMap,});
    locationTable[DODONGOS_CAVERN_COMPASS_CHEST]                               = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern Compass Chest",                      DODONGOS_CAVERN_COMPASS_CHEST,                      {Category::cDodongosCavern, Category::cVanillaCompass,});
    locationTable[DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST]                  = ItemLocation::Chest      (0x01, 0x06, "Dodongos Cavern Bomb Flower Platform Chest",         DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,         {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_BOMB_BAG_CHEST]                              = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern Bomb Bag Chest",                     DODONGOS_CAVERN_BOMB_BAG_CHEST,                     {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_END_OF_BRIDGE_CHEST]                         = ItemLocation::Chest      (0x01, 0x0A, "Dodongos Cavern End Of Bridge Chest",                DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,                {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT]               = ItemLocation::Base       (0x01, 0x30, "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,      {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS]          = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Side Room Near Dodongos", DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS, {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT]              = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,     {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_LOBBY]                            = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Lobby",                   DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                   {Category::cDodongosCavern, Category::cDekuScrub,});
    //Dodongos Cavern MQ
    locationTable[DODONGOS_CAVERN_MQ_MAP_CHEST]                                = ItemLocation::Chest      (0x01, 0x00, "Dodongos Cavern MQ Map Chest",                       DODONGOS_CAVERN_MQ_MAP_CHEST,                                    {Category::cDodongosCavern, Category::cVanillaMap,});
    locationTable[DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST]                           = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern MQ Bomb Bag Chest",                  DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST,                               {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_MQ_COMPASS_CHEST]                            = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern MQ Compass Chest",                   DODONGOS_CAVERN_MQ_COMPASS_CHEST,                                {Category::cDodongosCavern, Category::cVanillaCompass,});
    locationTable[DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST]                        = ItemLocation::Chest      (0x01, 0x02, "Dodongos Cavern MQ Larvae Room Chest",               DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,                            {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST]                  = ItemLocation::Chest      (0x01, 0x03, "Dodongos Cavern MQ Torch Puzzle Room Chest",         DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,                      {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST]                        = ItemLocation::Chest      (0x01, 0x01, "Dodongos Cavern MQ Under Grave Chest",               DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST,                            {Category::cDodongosCavern,});
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR]                    = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Lobby Rear",              DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,                        {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT]                   = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Lobby Front",             DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,                       {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE]                     = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Staircase",               DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,                         {Category::cDodongosCavern, Category::cDekuScrub,});
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = ItemLocation::Base       (0x01, 0x39, "Dodongos Cavern Deku Scrub Side Room Near Lower Lizalfos",DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS,{Category::cDodongosCavern, Category::cDekuScrub,});

    //Jabu Jabus Belly Vanilla
    locationTable[JABU_JABUS_BELLY_MAP_CHEST]                                  = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly Map Chest",                         JABU_JABUS_BELLY_MAP_CHEST,                     {Category::cJabuJabusBelly, Category::cVanillaMap,});
    locationTable[JABU_JABUS_BELLY_COMPASS_CHEST]                              = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly Compass Chest",                     JABU_JABUS_BELLY_COMPASS_CHEST,                 {Category::cJabuJabusBelly, Category::cVanillaCompass,});
    locationTable[JABU_JABUS_BELLY_BOOMERANG_CHEST]                            = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly Boomerang Chest",                   JABU_JABUS_BELLY_BOOMERANG_CHEST,               {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_DEKU_SCRUB]                                 = ItemLocation::Base       (0x02, 0x30, "Jabu Jabus Belly Deku Scrub",                        JABU_JABUS_BELLY_DEKU_SCRUB,                    {Category::cJabuJabusBelly, Category::cDekuScrub,});
    //Jabu Jabus Belly MQ
    locationTable[JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST]                   = ItemLocation::Chest      (0x02, 0x05, "Jabu Jabus Belly MQ First Room Side Chest",          JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST,        {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_MAP_CHEST]                               = ItemLocation::Chest      (0x02, 0x03, "Jabu Jabus Belly MQ Map Chest",                      JABU_JABUS_BELLY_MQ_MAP_CHEST,                    {Category::cJabuJabusBelly, Category::cVanillaMap,});
    locationTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST]                 = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly MQ Second Room Lower Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,      {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_COMPASS_CHEST]                           = ItemLocation::Chest      (0x02, 0x00, "Jabu Jabus Belly MQ Compass Chest",                  JABU_JABUS_BELLY_MQ_COMPASS_CHEST,                {Category::cJabuJabusBelly, Category::cVanillaCompass,});
    locationTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST]                 = ItemLocation::Chest      (0x02, 0x07, "Jabu Jabus Belly MQ Second Room Upper Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,      {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST]            = ItemLocation::Chest      (0x02, 0x08, "Jabu Jabus Belly MQ Basement Near Switches Chest",   JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST]               = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly MQ Basement Near Vines Chest",      JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST]                         = ItemLocation::Chest      (0x02, 0x0A, "Jabu Jabus Belly MQ Near Boss Chest",                JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,              {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST]            = ItemLocation::Chest      (0x02, 0x09, "Jabu Jabus Belly MQ Falling Like Like Room Chest",   JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST]              = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly MQ Boomerang Room Small Chest",     JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,   {Category::cJabuJabusBelly,});
    locationTable[JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST]                         = ItemLocation::Chest      (0x02, 0x06, "Jabu Jabus Belly MQ Boomerang Chest",                JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,              {Category::cJabuJabusBelly,});
    //COW

    //Forest Temple Vanilla
    locationTable[FOREST_TEMPLE_FIRST_ROOM_CHEST]                              = ItemLocation::Chest      (0x03, 0x03, "Forest Temple First Room Chest",                     FOREST_TEMPLE_FIRST_ROOM_CHEST,              {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_FIRST_STALFOS_CHEST]                           = ItemLocation::Chest      (0x03, 0x00, "Forest Temple First Stalfos Chest",                  FOREST_TEMPLE_FIRST_STALFOS_CHEST,           {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST]                 = ItemLocation::Chest      (0x03, 0x05, "Forest Temple Raised Island Courtyard Chest",        FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST, {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (0x03, 0x01, "Forest Temple Map Chest",                            FOREST_TEMPLE_MAP_CHEST,                     {Category::cForestTemple, Category::cVanillaMap,});
    locationTable[FOREST_TEMPLE_WELL_CHEST]                                    = ItemLocation::Chest      (0x03, 0x09, "Forest Temple Well Chest",                           FOREST_TEMPLE_WELL_CHEST,                    {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST]                    = ItemLocation::Chest      (0x03, 0x07, "Forest Temple Falling Ceiling Room Chest",           FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST,    {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_EYE_SWITCH_CHEST]                              = ItemLocation::Chest      (0x03, 0x04, "Forest Temple Eye Switch Chest",                     FOREST_TEMPLE_EYE_SWITCH_CHEST,              {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple Boss Key Chest",                       FOREST_TEMPLE_BOSS_KEY_CHEST,                {Category::cForestTemple, Category::cVanillaBossKey});
    locationTable[FOREST_TEMPLE_FLOORMASTER_CHEST]                             = ItemLocation::Chest      (0x03, 0x02, "Forest Temple Floormaster Chest",                    FOREST_TEMPLE_FLOORMASTER_CHEST,             {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_BOW_CHEST]                                     = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple Bow Chest",                            FOREST_TEMPLE_BOW_CHEST,                     {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_RED_POE_CHEST]                                 = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple Red Poe Chest",                        FOREST_TEMPLE_RED_POE_CHEST,                 {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_BLUE_POE_CHEST]                                = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple Blue Poe Chest",                       FOREST_TEMPLE_BLUE_POE_CHEST,                {Category::cForestTemple, Category::cVanillaCompass,});
    locationTable[FOREST_TEMPLE_BASEMENT_CHEST]                                = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple Basement Chest",                       FOREST_TEMPLE_BASEMENT_CHEST,                {Category::cForestTemple,});
    //Forest Temple MQ
    locationTable[FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST]                           = ItemLocation::Chest      (0x03, 0x03, "Forest Temple MQ First Room Chest",                    FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST,                     {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_WOLFOS_CHEST]                               = ItemLocation::Chest      (0x03, 0x00, "Forest Temple MQ Wolfos Chest",                        FOREST_TEMPLE_MQ_WOLFOS_CHEST,                         {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_BOW_CHEST]                                  = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple MQ Bow Chest",                           FOREST_TEMPLE_MQ_BOW_CHEST,                            {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST]        = ItemLocation::Chest      (0x03, 0x01, "Forest Temple MQ Raised Island Courtyard Lower Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST,  {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST]        = ItemLocation::Chest      (0x03, 0x05, "Forest Temple MQ Raised Island Courtyard Upper Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST,  {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_WELL_CHEST]                                 = ItemLocation::Chest      (0x03, 0x09, "Forest Temple MQ Well Chest",                          FOREST_TEMPLE_MQ_WELL_CHEST,                           {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple MQ Map Chest",                           FOREST_TEMPLE_MQ_MAP_CHEST,                            {Category::cForestTemple, Category::cVanillaMap,});
    locationTable[FOREST_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple MQ Compass Chest",                       FOREST_TEMPLE_MQ_COMPASS_CHEST,                        {Category::cForestTemple, Category::cVanillaCompass,});
    locationTable[FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST]                 = ItemLocation::Chest      (0x03, 0x06, "Forest Temple MQ Falling Ceiling Room Chest",          FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST,           {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_MQ_BASEMENT_CHEST]                             = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple MQ Basement Chest",                      FOREST_TEMPLE_MQ_BASEMENT_CHEST,                       {Category::cForestTemple,});
    locationTable[FOREST_TEMPLE_MQ_REDEAD_CHEST]                               = ItemLocation::Chest      (0x03, 0x02, "Forest Temple MQ Redead Chest",                        FOREST_TEMPLE_MQ_REDEAD_CHEST,                         {Category::cForestTemple, Category::cVanillaSmallKey});
    locationTable[FOREST_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple MQ Boss Key Chest",                      FOREST_TEMPLE_MQ_BOSS_KEY_CHEST,                       {Category::cForestTemple, Category::cVanillaBossKey});

    //Fire Temple Vanilla
    locationTable[FIRE_TEMPLE_NEAR_BOSS_CHEST]                                 = ItemLocation::Chest      (0x04, 0x01, "Fire Temple Near Boss Chest",                        FIRE_TEMPLE_NEAR_BOSS_CHEST,                     {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_FLARE_DANCER_CHEST]                              = ItemLocation::Chest      (0x04, 0x00, "Fire Temple Flare Dancer Chest",                     FIRE_TEMPLE_FLARE_DANCER_CHEST,                  {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_BOSS_KEY_CHEST]                                  = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple Boss Key Chest",                         FIRE_TEMPLE_BOSS_KEY_CHEST,                      {Category::cFireTemple, Category::cVanillaBossKey});
    locationTable[FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST]                = ItemLocation::Chest      (0x04, 0x02, "Fire Temple Big Lava Room Blocked Door Chest",       FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,    {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST]             = ItemLocation::Chest      (0x04, 0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST]                        = ItemLocation::Chest      (0x04, 0x03, "Fire Temple Boulder Maze Lower Chest",               FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,            {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST]                        = ItemLocation::Chest      (0x04, 0x06, "Fire Temple Boulder Maze Upper Chest",               FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,            {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST]                    = ItemLocation::Chest      (0x04, 0x08, "Fire Temple Boulder Maze Side Room Chest",           FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST,        {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST]                     = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple Boulder Maze Shortcut Chest",            FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,         {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_SCARECROW_CHEST]                                 = ItemLocation::Chest      (0x04, 0x0D, "Fire Temple Scarecrow Chest",                        FIRE_TEMPLE_SCARECROW_CHEST,                     {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_MAP_CHEST]                                       = ItemLocation::Chest      (0x04, 0x0A, "Fire Temple Map Chest",                              FIRE_TEMPLE_MAP_CHEST,                           {Category::cFireTemple, Category::cVanillaMap,});
    locationTable[FIRE_TEMPLE_COMPASS_CHEST]                                   = ItemLocation::Chest      (0x04, 0x07, "Fire Temple Compass Chest",                          FIRE_TEMPLE_COMPASS_CHEST,                       {Category::cFireTemple, Category::cVanillaCompass,});
    locationTable[FIRE_TEMPLE_HIGHEST_GORON_CHEST]                             = ItemLocation::Chest      (0x04, 0x09, "Fire Temple Highest Goron Chest",                    FIRE_TEMPLE_HIGHEST_GORON_CHEST,                 {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_MEGATON_HAMMER_CHEST]                            = ItemLocation::Chest      (0x04, 0x05, "Fire Temple Megaton Hammer Chest",                   FIRE_TEMPLE_MEGATON_HAMMER_CHEST,                {Category::cFireTemple,});
    //Fire Temple MQ
    locationTable[FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST]                              = ItemLocation::Chest      (0x04, 0x07, "Fire Temple MQ Near Boss Chest",                     FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,                  {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST]                         = ItemLocation::Chest      (0x04, 0x00, "Fire Temple MQ Megaton Hammer Chest",                FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST,             {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_MQ_COMPASS_CHEST]                                = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple MQ Compass Chest",                       FIRE_TEMPLE_MQ_COMPASS_CHEST,                    {Category::cFireTemple, Category::cVanillaCompass,});
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST]                    = ItemLocation::Chest      (0x04, 0x03, "Fire Temple MQ Lizalfos Maze Lower Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,        {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST]                    = ItemLocation::Chest      (0x04, 0x06, "Fire Temple MQ Lizalfos Maze Upper Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST,        {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_MQ_CHEST_ON_FIRE]                                = ItemLocation::Chest      (0x04, 0x05, "Fire Temple MQ Chest on Fire",                       FIRE_TEMPLE_MQ_CHEST_ON_FIRE,                    {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST]                          = ItemLocation::Chest      (0x04, 0x02, "Fire Temple MQ Map Room Side Chest",                 FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST,              {Category::cFireTemple,});
    locationTable[FIRE_TEMPLE_MQ_MAP_CHEST]                                    = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple MQ Map Chest",                           FIRE_TEMPLE_MQ_MAP_CHEST,                        {Category::cFireTemple, Category::cVanillaMap,});
    locationTable[FIRE_TEMPLE_MQ_BOSS_KEY_CHEST]                               = ItemLocation::Chest      (0x04, 0x04, "Fire Temple MQ Boss Key Chest",                      FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                   {Category::cFireTemple, Category::cVanillaBossKey});
    locationTable[FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST]             = ItemLocation::Chest      (0x04, 0x01, "Fire Temple MQ Big Lava Room Blocked Door Chest",    FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST]                = ItemLocation::Chest      (0x04, 0x08, "Fire Temple MQ Lizalfos Maze Side Room Chest",       FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST,    {Category::cFireTemple, Category::cVanillaSmallKey});
    locationTable[FIRE_TEMPLE_MQ_FREESTANDING_KEY]                             = ItemLocation::Collectable(0x04, 0x1C, "Fire Temple MQ Freestanding Key",                    FIRE_TEMPLE_MQ_FREESTANDING_KEY,                 {Category::cFireTemple, Category::cVanillaSmallKey});

    //Water Temple Vanilla
    locationTable[WATER_TEMPLE_MAP_CHEST]                                      = ItemLocation::Chest      (0x05, 0x02, "Water Temple Map Chest",                             WATER_TEMPLE_MAP_CHEST,                {Category::cWaterTemple, Category::cVanillaMap,});
    locationTable[WATER_TEMPLE_COMPASS_CHEST]                                  = ItemLocation::Chest      (0x05, 0x09, "Water Temple Compass Chest",                         WATER_TEMPLE_COMPASS_CHEST,            {Category::cWaterTemple, Category::cVanillaCompass,});
    locationTable[WATER_TEMPLE_TORCHES_CHEST]                                  = ItemLocation::Chest      (0x05, 0x01, "Water Temple Torches Chest",                         WATER_TEMPLE_TORCHES_CHEST,            {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_DRAGON_CHEST]                                   = ItemLocation::Chest      (0x05, 0x0A, "Water Temple Dragon Chest",                          WATER_TEMPLE_DRAGON_CHEST,             {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST]                       = ItemLocation::Chest      (0x05, 0x08, "Water Temple Central Bow Target Chest",              WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_CENTRAL_PILLAR_CHEST]                           = ItemLocation::Chest      (0x05, 0x06, "Water Temple Central Pillar Chest",                  WATER_TEMPLE_CENTRAL_PILLAR_CHEST,     {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_CRACKED_WALL_CHEST]                             = ItemLocation::Chest      (0x05, 0x00, "Water Temple Cracked Wall Chest",                    WATER_TEMPLE_CRACKED_WALL_CHEST,       {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_BOSS_KEY_CHEST]                                 = ItemLocation::Chest      (0x05, 0x05, "Water Temple Boss Key Chest",                        WATER_TEMPLE_BOSS_KEY_CHEST,           {Category::cWaterTemple, Category::cVanillaBossKey});
    locationTable[WATER_TEMPLE_LONGSHOT_CHEST]                                 = ItemLocation::Chest      (0x05, 0x07, "Water Temple Longshot Chest",                        WATER_TEMPLE_LONGSHOT_CHEST,           {Category::cWaterTemple,});
    locationTable[WATER_TEMPLE_RIVER_CHEST]                                    = ItemLocation::Chest      (0x05, 0x03, "Water Temple River Chest",                           WATER_TEMPLE_RIVER_CHEST,              {Category::cWaterTemple, Category::cVanillaSmallKey});
    //Water Temple MQ
    locationTable[WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST]                        = ItemLocation::Chest      (0x05, 0x06, "Water Temple MQ Central Pillar Chest",               WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST, {Category::cWaterTemple, Category::cVanillaSmallKey});
    locationTable[WATER_TEMPLE_MQ_BOSS_KEY_CHEST]                              = ItemLocation::Chest      (0x05, 0x05, "Water Temple MQ Boss Key Chest",                     WATER_TEMPLE_MQ_BOSS_KEY_CHEST,       {Category::cWaterTemple, Category::cVanillaBossKey});
    locationTable[WATER_TEMPLE_MQ_LONGSHOT_CHEST]                              = ItemLocation::Chest      (0x05, 0x00, "Water Temple MQ Longshot Chest",                     WATER_TEMPLE_MQ_LONGSHOT_CHEST,       {Category::cWaterTemple,});
    locationTable[WATER_TEMPLE_MQ_COMPASS_CHEST]                               = ItemLocation::Chest      (0x05, 0x01, "Water Temple MQ Compass Chest",                      WATER_TEMPLE_MQ_COMPASS_CHEST,        {Category::cWaterTemple, Category::cVanillaCompass,});
    locationTable[WATER_TEMPLE_MQ_MAP_CHEST]                                   = ItemLocation::Chest      (0x05, 0x02, "Water Temple MQ Map Chest",                          WATER_TEMPLE_MQ_MAP_CHEST,            {Category::cWaterTemple, Category::cVanillaMap,});
    locationTable[WATER_TEMPLE_MQ_FREESTANDING_KEY]                            = ItemLocation::Collectable(0x05, 0x01, "Water Temple MQ Freestanding Key",                   WATER_TEMPLE_MQ_FREESTANDING_KEY,     {Category::cWaterTemple, Category::cVanillaSmallKey});

    //Spirit Temple Shared
    locationTable[SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST]                        = ItemLocation::Chest      (0x5C, 0x0B, "Spirit Temple Silver Gauntlets Chest",               SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST,       {Category::cSpiritTemple, Category::cDesertColossus});
    locationTable[SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST]                           = ItemLocation::Chest      (0x5C, 0x09, "Spirit Temple Mirror Shield Chest",                  SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,          {Category::cSpiritTemple, Category::cDesertColossus});
    //Spirit Temple Vanilla
    locationTable[SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST]                            = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple Child Bridge Chest",                   SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,            {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST]                     = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple Child Early Torches Chest",            SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_COMPASS_CHEST]                                 = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple Compass Chest",                        SPIRIT_TEMPLE_COMPASS_CHEST,                 {Category::cSpiritTemple, Category::cVanillaCompass,});
    locationTable[SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST]                       = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple Early Adult Right Chest",              SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST]                       = ItemLocation::Chest      (0x06, 0x0D, "Spirit Temple First Mirror Left Chest",              SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,       {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST]                      = ItemLocation::Chest      (0x06, 0x0E, "Spirit Temple First Mirror Right Chest",             SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST,      {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple Map Chest",                            SPIRIT_TEMPLE_MAP_CHEST,                     {Category::cSpiritTemple, Category::cVanillaMap,});
    locationTable[SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST]                       = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple Child Climb North Chest",              SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST,       {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST]                        = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple Child Climb East Chest",               SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,        {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST]                          = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple Sun Block Room Chest",                 SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST]                        = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple Statue Room Hand Chest",               SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,        {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST]                   = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple Statue Room Northeast Chest",          SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,   {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST]                         = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple Near Four Armos Chest",                SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,         {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST]                 = ItemLocation::Chest      (0x06, 0x14, "Spirit Temple Hallway Right Invisible Chest",        SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST, {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST]                  = ItemLocation::Chest      (0x06, 0x15, "Spirit Temple Hallway Left Invisible Chest",         SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,  {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (0x06, 0x0A, "Spirit Temple Boss Key Chest",                       SPIRIT_TEMPLE_BOSS_KEY_CHEST,                {Category::cSpiritTemple, Category::cVanillaBossKey});
    locationTable[SPIRIT_TEMPLE_TOPMOST_CHEST]                                 = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple Topmost Chest",                        SPIRIT_TEMPLE_TOPMOST_CHEST,                 {Category::cSpiritTemple,});
    //Spirit Temple MQ
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST]                  = ItemLocation::Chest      (0x06, 0x1A, "Spirit Temple MQ Entrance Front Left Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST,     {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST]                  = ItemLocation::Chest      (0x06, 0x1F, "Spirit Temple MQ Entrance Back Right Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST,     {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST]                 = ItemLocation::Chest      (0x06, 0x1B, "Spirit Temple MQ Entrance Front Right Chest",        SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST]                   = ItemLocation::Chest      (0x06, 0x1E, "Spirit Temple MQ Entrance Back Left Chest",          SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,      {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST]                  = ItemLocation::Chest      (0x06, 0x1D, "Spirit Temple MQ Child Hammer Switch Chest",         SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple MQ Map Chest",                         SPIRIT_TEMPLE_MQ_MAP_CHEST,                     {Category::cSpiritTemple, Category::cVanillaMap,});
    locationTable[SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST]                       = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple MQ Map Room Enemy Chest",              SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST]                    = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple MQ Child Climb North Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST,       {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST]                    = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple MQ Child Climb South Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple MQ Compass Chest",                     SPIRIT_TEMPLE_MQ_COMPASS_CHEST,                 {Category::cSpiritTemple, Category::cVanillaCompass,});
    locationTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST]                  = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple MQ Statue Room Lullaby Chest",         SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,     {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST]                = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple MQ Statue Room Invisible Chest",       SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST,   {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST]                 = ItemLocation::Chest      (0x06, 0x1C, "Spirit Temple MQ Silver Block Hallway Chest",        SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
    locationTable[SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST]                       = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple MQ Sun Block Room Chest",              SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,          {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST]                        = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple MQ Symphony Room Chest",               SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,           {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST]                          = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple MQ Leever Room Chest",                 SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,             {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST]                          = ItemLocation::Chest      (0x06, 0x19, "Spirit Temple MQ Beamos Room Chest",                 SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,             {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST]                         = ItemLocation::Chest      (0x06, 0x18, "Spirit Temple MQ Chest Switch Chest",                SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,            {Category::cSpiritTemple,});
    locationTable[SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple MQ Boss Key Chest",                    SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,                {Category::cSpiritTemple, Category::cVanillaBossKey});
    locationTable[SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST]              = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple MQ Mirror Puzzle Invisible Chest",     SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, {Category::cSpiritTemple, Category::cVanillaSmallKey});

    //Shadow Temple Vanilla
    locationTable[SHADOW_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple Map Chest",                            SHADOW_TEMPLE_MAP_CHEST,                        {Category::cShadowTemple, Category::cVanillaMap,});
    locationTable[SHADOW_TEMPLE_HOVER_BOOTS_CHEST]                             = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple Hover Boots Chest",                    SHADOW_TEMPLE_HOVER_BOOTS_CHEST,                {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_COMPASS_CHEST]                                 = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple Compass Chest",                        SHADOW_TEMPLE_COMPASS_CHEST,                    {Category::cShadowTemple, Category::cVanillaCompass,});
    locationTable[SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST]                      = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple Early Silver Rupee Chest",             SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST,         {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST]                = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple Invisible Blades Visible Chest",       SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,   {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST]              = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple Invisible Blades Invisible Chest",     SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST, {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST]                    = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple Falling Spikes Lower Chest",           SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,       {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST]                    = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple Falling Spikes Upper Chest",           SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,       {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST]                   = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple Falling Spikes Switch Chest",          SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,      {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST]                        = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple Invisible Spikes Chest",               SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_WIND_HINT_CHEST]                               = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple Wind Hint Chest",                      SHADOW_TEMPLE_WIND_HINT_CHEST,                  {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST]                        = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple After Wind Enemy Chest",               SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST]                       = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple After Wind Hidden Chest",              SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST,          {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST]                        = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple Spike Walls Left Chest",               SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple Boss Key Chest",                       SHADOW_TEMPLE_BOSS_KEY_CHEST,                   {Category::cShadowTemple, Category::cVanillaBossKey});
    locationTable[SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST]                   = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple Invisible Floormaster Chest",          SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST,      {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_FREESTANDING_KEY]                              = ItemLocation::Collectable(0x07, 0x01, "Shadow Temple Freestanding Key",                     SHADOW_TEMPLE_FREESTANDING_KEY,                 {Category::cShadowTemple, Category::cVanillaSmallKey});
    //Shadow Temple MQ
    locationTable[SHADOW_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple MQ Compass Chest",                     SHADOW_TEMPLE_MQ_COMPASS_CHEST,                    {Category::cShadowTemple, Category::cVanillaCompass,});
    locationTable[SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST]                          = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple MQ Hover Boots Chest",                 SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST,                {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST]                         = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple MQ Early Gibdos Chest",                SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,               {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple MQ Map Chest",                         SHADOW_TEMPLE_MQ_MAP_CHEST,                        {Category::cShadowTemple, Category::cVanillaMap,});
    locationTable[SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST]                 = ItemLocation::Chest      (0x07, 0x0F, "Shadow Temple MQ Beamos Silver Rupees Chest",        SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,       {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST]                = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple MQ Falling Spikes Switch Chest",       SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST,      {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST]                 = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple MQ Falling Spikes Lower Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,       {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST]                 = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple MQ Falling Spikes Upper Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,       {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST]                     = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple MQ Invisible Spikes Chest",            SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple MQ Boss Key Chest",                    SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,                   {Category::cShadowTemple, Category::cVanillaBossKey});
    locationTable[SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST]                     = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple MQ Spike Walls Left Chest",            SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST]                         = ItemLocation::Chest      (0x07, 0x10, "Shadow Temple MQ Stalfos Room Chest",                SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,               {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST]           = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple MQ Invisible Blades Invisible Chest",  SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST]             = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple MQ Invisible Blades Visible Chest",    SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,   {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST]                          = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple MQ Bomb Flower Chest",                 SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,                {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_WIND_HINT_CHEST]                            = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple MQ Wind Hint Chest",                   SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,                  {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST]                    = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple MQ After Wind Hidden Chest",           SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST,          {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST]                     = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple MQ After Wind Enemy Chest",            SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,           {Category::cShadowTemple,});
    locationTable[SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST]                  = ItemLocation::Chest      (0x07, 0x0E, "Shadow Temple MQ Near Ship Invisible Chest",         SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST,        {Category::cShadowTemple, Category::cVanillaSmallKey});
    locationTable[SHADOW_TEMPLE_MQ_FREESTANDING_KEY]                           = ItemLocation::Collectable(0x07, 0x06, "Shadow Temple MQ Freestanding Key",                  SHADOW_TEMPLE_MQ_FREESTANDING_KEY,                 {Category::cShadowTemple, Category::cVanillaSmallKey});

    //Bottom of the Well Vanilla
    locationTable[BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST]               = ItemLocation::Chest      (0x08, 0x08, "Bottom of the Well Front Left Fake Wall Chest",         BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,   {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
    locationTable[BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST]              = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well Front Center Bombable Chest",        BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,  {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST]             = ItemLocation::Chest      (0x08, 0x05, "Bottom of the Well Right Bottom Fake Wall Chest",       BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
    locationTable[BOTTOM_OF_THE_WELL_COMPASS_CHEST]                            = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well Compass Chest",                      BOTTOM_OF_THE_WELL_COMPASS_CHEST,                {Category::cBottomOfTheWell, Category::cVanillaCompass,});
    locationTable[BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST]                   = ItemLocation::Chest      (0x08, 0x0E, "Bottom of the Well Center Skulltula Chest",             BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,       {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST]                 = ItemLocation::Chest      (0x08, 0x04, "Bottom of the Well Back Left Bombable Chest",           BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,     {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST]                      = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well Lens of Truth Chest",                BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,          {Category::cBottomOfTheWell, Category::cSongDungeonReward});
    locationTable[BOTTOM_OF_THE_WELL_INVISIBLE_CHEST]                          = ItemLocation::Chest      (0x08, 0x14, "Bottom of the Well Invisible Chest",                    BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,              {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST]                   = ItemLocation::Chest      (0x08, 0x10, "Bottom of the Well Underwater Front Chest",             BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,       {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST]                    = ItemLocation::Chest      (0x08, 0x09, "Bottom of the Well Underwater Left Chest",              BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,        {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_MAP_CHEST]                                = ItemLocation::Chest      (0x08, 0x07, "Bottom of the Well Map Chest",                          BOTTOM_OF_THE_WELL_MAP_CHEST,                    {Category::cBottomOfTheWell, Category::cVanillaMap,});
    locationTable[BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST]                         = ItemLocation::Chest      (0x08, 0x0A, "Bottom of the Well Fire Keese Chest",                   BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,             {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST]                          = ItemLocation::Chest      (0x08, 0x0C, "Bottom of the Well Like Like Chest",                    BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,              {Category::cBottomOfTheWell,});
    locationTable[BOTTOM_OF_THE_WELL_FREESTANDING_KEY]                         = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well Freestanding Key",                   BOTTOM_OF_THE_WELL_FREESTANDING_KEY,             {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
    //Bottom of the Well MQBottomOfTheWell]
    locationTable[BOTTOM_OF_THE_WELL_MQ_MAP_CHEST]                             = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well MQ Map Chest",                       BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                        {Category::cBottomOfTheWell, Category::cVanillaMap,});
    locationTable[BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST]                   = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well MQ Lens of Truth Chest",             BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,              {Category::cBottomOfTheWell, Category::cSongDungeonReward});
    locationTable[BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST]                         = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well MQ Compass Chest",                   BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,                    {Category::cBottomOfTheWell, Category::cVanillaCompass,});
    locationTable[BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY]            = ItemLocation::Collectable(0x08, 0x02, "Bottom of the Well MQ Dead Hand Freestanding Key",      BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY,       {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
    locationTable[BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY]      = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well MQ East Inner Room Freestanding Key",BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});

    //Ice Cavern Vanilla
    locationTable[ICE_CAVERN_MAP_CHEST]                                        = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern Map Chest",                                  ICE_CAVERN_MAP_CHEST,            {Category::cIceCavern, Category::cVanillaMap,});
    locationTable[ICE_CAVERN_COMPASS_CHEST]                                    = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern Compass Chest",                              ICE_CAVERN_COMPASS_CHEST,        {Category::cIceCavern, Category::cVanillaCompass,});
    locationTable[ICE_CAVERN_IRON_BOOTS_CHEST]                                 = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern Iron Boots Chest",                           ICE_CAVERN_IRON_BOOTS_CHEST,     {Category::cIceCavern,});
    locationTable[ICE_CAVERN_FREESTANDING_POH]                                 = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern Freestanding PoH",                           ICE_CAVERN_FREESTANDING_POH,     {Category::cIceCavern,});
    //Ice Cavern MQIceCavern]
    locationTable[ICE_CAVERN_MQ_IRON_BOOTS_CHEST]                              = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern MQ Iron Boots Chest",                        ICE_CAVERN_MQ_IRON_BOOTS_CHEST,  {Category::cIceCavern,});
    locationTable[ICE_CAVERN_MQ_COMPASS_CHEST]                                 = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern MQ Compass Chest",                           ICE_CAVERN_MQ_COMPASS_CHEST,     {Category::cIceCavern, Category::cVanillaCompass,});
    locationTable[ICE_CAVERN_MQ_MAP_CHEST]                                     = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern MQ Map Chest",                               ICE_CAVERN_MQ_MAP_CHEST,         {Category::cIceCavern, Category::cVanillaMap,});
    locationTable[ICE_CAVERN_MQ_FREESTANDING_POH]                              = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern MQ Freestanding PoH",                        ICE_CAVERN_MQ_FREESTANDING_POH,  {Category::cIceCavern,});

    //Gerudo Training Ground Vanilla
    locationTable[GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST]                    = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds Lobby Left Chest",              GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST,              {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST]                   = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds Lobby Right Chest",             GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST,             {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_STALFOS_CHEST]                       = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds Stalfos Chest",                 GERUDO_TRAINING_GROUNDS_STALFOS_CHEST,                 {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST]                        = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds Beamos Chest",                  GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST,                  {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST]                = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST,          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST]               = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds Maze Path First Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST,         {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST]              = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds Maze Path Second Chest",        GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST,        {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST]               = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds Maze Path Third Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST,         {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST]               = ItemLocation::Chest      (0x0B, 0x0C, "Gerudo Training Grounds Maze Path Final Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST,         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST]            = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds Maze Right Central Chest",      GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST,      {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST]               = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds Maze Right Side Chest",         GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST,         {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST]       = ItemLocation::Chest      (0x0B, 0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST, {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST]             = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST,       {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST]            = ItemLocation::Chest      (0x0B, 0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST,      {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST]                    = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds Eye Statue Chest",              GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST,              {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST]                = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds Near Scarecrow Chest",          GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST,          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST]            = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds Before Heavy Block Chest",      GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST,      {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST]             = ItemLocation::Chest      (0x0B, 0x0F, "Gerudo Training Grounds Heavy Block First Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST,       {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST]            = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST,      {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST]             = ItemLocation::Chest      (0x0B, 0x14, "Gerudo Training Grounds Heavy Block Third Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST,       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST]            = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST,      {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY]                    = ItemLocation::Collectable(0x0B, 0x01, "Gerudo Training Grounds Freestanding Key",              GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY,              {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    //Gerudo Training Grounds MQ
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST]                = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds MQ Lobby Right Chest",          GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST,            {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST]                 = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds MQ Lobby Left Chest",           GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST,             {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST]         = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds MQ First Iron Knuckle Chest",   GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST,     {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST]         = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds MQ Before Heavy Block Chest",   GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST,     {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST]                 = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds MQ Eye Statue Chest",           GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST,             {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST]               = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds MQ Flame Circle Chest",         GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST,           {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST]        = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds MQ Second Iron Knuckle Chest",  GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST,    {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST]                   = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds MQ Dinolfos Chest",             GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST,               {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST]                 = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds MQ Ice Arrows Chest",           GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST,             {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST]         = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds MQ Maze Right Central Chest",   GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST,     {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST]            = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds MQ Maze Path First Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST,        {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST]            = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds MQ Maze Right Side Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST,        {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST]            = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds MQ Maze Path Third Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST,        {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST]           = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds MQ Maze Path Second Chest",     GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST,       {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST]             = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds MQ Hidden Ceiling Chest",       GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST,         {Category::cGerudoTrainingGrounds,});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST]    = ItemLocation::Chest      (0x0B, 0x0D, "Gerudo Training Grounds MQ Underwater Silver Rupee Chest",GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST,{Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST]                = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds MQ Heavy Block Chest",          GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST,            {Category::cGerudoTrainingGrounds,});

    //Ganons Castle Shared
    locationTable[GANONS_TOWER_BOSS_KEY_CHEST]                                 = ItemLocation::Chest      (0x0A, 0x0B, "Ganon's Tower Boss Key Chest",                          GANONS_TOWER_BOSS_KEY_CHEST,                    {Category::cGanonsCastle,});
    //Ganons Castle Vanilla
    locationTable[GANONS_CASTLE_FOREST_TRIAL_CHEST]                            = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle Forest Trial Chest",                     GANONS_CASTLE_FOREST_TRIAL_CHEST,                  {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST]                        = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle Water Trial Left Chest",                 GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,              {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST]                       = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle Water Trial Right Chest",                GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST,             {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST]                      = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle Shadow Trial Front Chest",               GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,            {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST]           = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest",    GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST, {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST]             = ItemLocation::Chest      (0x0D, 0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",      GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST,   {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST]                  = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle Spirit Trial Invisible Chest",           GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,        {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST]                  = ItemLocation::Chest      (0x0D, 0x0C, "Ganon's Castle Light Trial First Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,        {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST]                 = ItemLocation::Chest      (0x0D, 0x0B, "Ganon's Castle Light Trial Second Left Chest",          GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,       {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST]                  = ItemLocation::Chest      (0x0D, 0x0D, "Ganon's Castle Light Trial Third Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,        {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST]                 = ItemLocation::Chest      (0x0D, 0x0E, "Ganon's Castle Light Trial First Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,       {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST]                = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle Light Trial Second Right Chest",         GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,      {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST]                 = ItemLocation::Chest      (0x0D, 0x0F, "Ganon's Castle Light Trial Third Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,       {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST]           = ItemLocation::Chest      (0x0D, 0x10, "Ganon's Castle Light Trial Invisible Enemies Chest",    GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST, {Category::cGanonsCastle, Category::cVanillaSmallKey});
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST]                     = ItemLocation::Chest      (0x0D, 0x11, "Ganon's Castle Light Trial Lullaby Chest",              GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,           {Category::cGanonsCastle, Category::cVanillaSmallKey});
    locationTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT]                        = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle Deku Scrub Center-Left",                 GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,              {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT]                       = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle Deku Scrub Center-Right",                GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,             {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_DEKU_SCRUB_RIGHT]                              = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle Deku Scrub Right",                       GANONS_CASTLE_DEKU_SCRUB_RIGHT,                    {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_DEKU_SCRUB_LEFT]                               = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle Deku Scrub Left",                        GANONS_CASTLE_DEKU_SCRUB_LEFT,                     {Category::cGanonsCastle, Category::cDekuScrub,});
    //Ganons Castle MQ
    locationTable[GANONS_CASTLE_MQ_WATER_TRIAL_CHEST]                          = ItemLocation::Chest      (0x0D, 0x01, "Ganon's Castle MQ Water Trial Chest",                   GANONS_CASTLE_MQ_WATER_TRIAL_CHEST,                    {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST]              = ItemLocation::Chest      (0x0D, 0x02, "Ganon's Castle MQ Forest Trial Eye Switch Chest",       GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,        {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST]       = ItemLocation::Chest      (0x0D, 0x03, "Ganon's Castle MQ Forest Trial Frozen Eye Switch Chest",GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST]                  = ItemLocation::Chest      (0x0D, 0x04, "Ganon's Castle MQ Light Trial Lullaby Chest",           GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST,            {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST]             = ItemLocation::Chest      (0x0D, 0x00, "Ganon's Castle MQ Shadow Trial Bomb Flower Chest",      GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST,       {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST]              = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle MQ Shadow Trial Eye Switch Chest",       GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,        {Category::cGanonsCastle,  Category::cVanillaSmallKey});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST]        = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle MQ Spirit Trial Golden Gauntlets Chest", GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,  {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST]          = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle MQ Spirit Trial Sun Back Right Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,    {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST]           = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle MQ Spirit Trial Sun Back Left Chest",    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,     {Category::cGanonsCastle,  Category::cVanillaSmallKey});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST]          = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle MQ Spirit Trial Sun Front Left Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,    {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST]                   = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle MQ Spirit Trial First Chest",            GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,             {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST]               = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle MQ Spirit Trial Invisible Chest",        GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,         {Category::cGanonsCastle,});
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY]              = ItemLocation::Collectable(0x0D, 0x01, "Ganon's Castle MQ Forest Trial Freestanding Key",       GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,        {Category::cGanonsCastle, Category::cVanillaSmallKey});
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT]                           = ItemLocation::Base       (0x0D, 0x30, "Ganon's Castle MQ Deku Scrub Right",                    GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,                     {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT]                     = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle MQ Deku Scrub Center-Left",              GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,               {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER]                          = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle MQ Deku Scrub Center",                   GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,                    {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT]                    = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle MQ Deku Scrub Center-Right",             GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,              {Category::cGanonsCastle, Category::cDekuScrub,});
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT]                            = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle MQ Deku Scrub Left",                     GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,                      {Category::cGanonsCastle, Category::cDekuScrub,});

    /*-------------------------------
       --- GOLD SKULLTULA TOKENS ---
      -------------------------------*/

    //Dungeons
    locationTable[DEKU_TREE_GS_BASEMENT_BACK_ROOM]                   = ItemLocation::GSToken(0x00, 0x01, "Deku Tree GS Basement Back Room",                  DEKU_TREE_GS_BASEMENT_BACK_ROOM,                  {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_GS_BASEMENT_GATE]                        = ItemLocation::GSToken(0x00, 0x02, "Deku Tree GS Basement Gate",                       DEKU_TREE_GS_BASEMENT_GATE,                       {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_GS_BASEMENT_VINES]                       = ItemLocation::GSToken(0x00, 0x04, "Deku Tree GS Basement Vines",                      DEKU_TREE_GS_BASEMENT_VINES,                      {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_GS_COMPASS_ROOM]                         = ItemLocation::GSToken(0x00, 0x08, "Deku Tree GS Compass Room",                        DEKU_TREE_GS_COMPASS_ROOM,                        {Category::cDekuTree, Category::cSkulltula,});

    locationTable[DEKU_TREE_MQ_GS_LOBBY]                             = ItemLocation::GSToken(0x00, 0x02, "Deku Tree MQ GS Lobby",                            DEKU_TREE_MQ_GS_LOBBY,                            {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_MQ_GS_COMPASS_ROOM]                      = ItemLocation::GSToken(0x00, 0x08, "Deku Tree MQ GS Compass Room",                     DEKU_TREE_MQ_GS_COMPASS_ROOM,                     {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM]              = ItemLocation::GSToken(0x00, 0x04, "Deku Tree MQ GS Basement Graves Room",             DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM,             {Category::cDekuTree, Category::cSkulltula,});
    locationTable[DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM]                = ItemLocation::GSToken(0x00, 0x01, "Deku Tree MQ GS Basement Back Room",               DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,               {Category::cDekuTree, Category::cSkulltula,});

    locationTable[DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS]             = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern GS Vines Above Stairs",            DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,            {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_GS_SCARECROW]                      = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern GS Scarecrow",                     DODONGOS_CAVERN_GS_SCARECROW,                     {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS]            = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern GS Alcove Above Stairs",           DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS,           {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_GS_BACK_ROOM]                      = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern GS Back Room",                     DODONGOS_CAVERN_GS_BACK_ROOM,                     {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS]  = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS, {Category::cDodongosCavern, Category::cSkulltula,});

    locationTable[DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM]                  = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern MQ GS Scrub Room",                 DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,                 {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM]     = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern MQ GS Song of Time Block Room",    DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM,    {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM]               = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern MQ GS Lizalfos Room",              DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,              {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM]                 = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern MQ GS Larvae Room",                DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,                {Category::cDodongosCavern, Category::cSkulltula,});
    locationTable[DODONGOS_CAVERN_MQ_GS_BACK_AREA]                   = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern MQ GS Back Room",                  DODONGOS_CAVERN_MQ_GS_BACK_AREA,                  {Category::cDodongosCavern, Category::cSkulltula,});

    locationTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER]          = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER,         {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER]          = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER,         {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_GS_NEAR_BOSS]                     = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly GS Near Boss",                    JABU_JABUS_BELLY_GS_NEAR_BOSS,                    {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM]             = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly GS Water Switch Room",            JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,            {Category::cJabuJabusBelly, Category::cSkulltula,});

    locationTable[JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM]           = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly MQ GS Tail Parasan Room",         JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,          {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM]     = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly MQ GS Invisible Enemies Room",    JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,    {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM]       = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly MQ GS Boomerang Chest Room",      JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,      {Category::cJabuJabusBelly, Category::cSkulltula,});
    locationTable[JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS]                  = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly MQ GS Near Boss",                 JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,                 {Category::cJabuJabusBelly, Category::cSkulltula,});

    locationTable[FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD]          = ItemLocation::GSToken(0x03, 0x01, "Forest Temple GS Raised Island Courtyard",         FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,         {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_GS_FIRST_ROOM]                       = ItemLocation::GSToken(0x03, 0x02, "Forest Temple GS First Room",                      FOREST_TEMPLE_GS_FIRST_ROOM,                      {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD]           = ItemLocation::GSToken(0x03, 0x04, "Forest Temple GS Level Island Courtyard",          FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD,          {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_GS_LOBBY]                            = ItemLocation::GSToken(0x03, 0x08, "Forest Temple GS Lobby",                           FOREST_TEMPLE_GS_LOBBY,                           {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_GS_BASEMENT]                         = ItemLocation::GSToken(0x03, 0x10, "Forest Temple GS Basement",                        FOREST_TEMPLE_GS_BASEMENT,                        {Category::cForestTemple, Category::cSkulltula,});

    locationTable[FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY]                 = ItemLocation::GSToken(0x03, 0x02, "Forest Temple MQ GS First Hallway",                FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY,                {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM]               = ItemLocation::GSToken(0x03, 0x10, "Forest Temple MQ GS Block Push Room",              FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM,              {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD]       = ItemLocation::GSToken(0x03, 0x01, "Forest Temple MQ GS Raised Island Courtyard",      FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD,      {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD]        = ItemLocation::GSToken(0x03, 0x04, "Forest Temple MQ GS Level Island Courtyard",       FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD,       {Category::cForestTemple, Category::cSkulltula,});
    locationTable[FOREST_TEMPLE_MQ_GS_WELL]                          = ItemLocation::GSToken(0x03, 0x08, "Forest Temple MQ GS Well",                         FOREST_TEMPLE_MQ_GS_WELL,                         {Category::cForestTemple, Category::cSkulltula,});

    locationTable[FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM]                  = ItemLocation::GSToken(0x04, 0x01, "Fire Temple GS Song of Time Room",                 FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                 {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_GS_BOSS_KEY_LOOP]                      = ItemLocation::GSToken(0x04, 0x02, "Fire Temple GS Boss Key Loop",                     FIRE_TEMPLE_GS_BOSS_KEY_LOOP,                     {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_GS_BOULDER_MAZE]                       = ItemLocation::GSToken(0x04, 0x04, "Fire Temple GS Boulder Maze",                      FIRE_TEMPLE_GS_BOULDER_MAZE,                      {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_GS_SCARECROW_TOP]                      = ItemLocation::GSToken(0x04, 0x08, "Fire Temple GS Scarecrow Top",                     FIRE_TEMPLE_GS_SCARECROW_TOP,                     {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_GS_SCARECROW_CLIMB]                    = ItemLocation::GSToken(0x04, 0x10, "Fire Temple GS Scarecrow Climb",                   FIRE_TEMPLE_GS_SCARECROW_CLIMB,                   {Category::cFireTemple, Category::cSkulltula,});

    locationTable[FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE]            = ItemLocation::GSToken(0x04, 0x02, "Fire Temple MQ GS Above Fire Wall Maze",           FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,           {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER]           = ItemLocation::GSToken(0x04, 0x08, "Fire Temple MQ GS Fire Wall Maze Center",          FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,          {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR]         = ItemLocation::GSToken(0x04, 0x01, "Fire Temple MQ GS Big Lava Room Open Door",        FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,        {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM]        = ItemLocation::GSToken(0x04, 0x10, "Fire Temple MQ GS Fire Wall Maze Side Room",       FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM,       {Category::cFireTemple, Category::cSkulltula,});
    locationTable[FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE]                   = ItemLocation::GSToken(0x04, 0x04, "Fire Temple MQ GS Skull on Fire",                  FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,                  {Category::cFireTemple, Category::cSkulltula,});

    locationTable[WATER_TEMPLE_GS_BEHIND_GATE]                       = ItemLocation::GSToken(0x05, 0x01, "Water Temple GS Behind Gate",                      WATER_TEMPLE_GS_BEHIND_GATE,                      {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM]             = ItemLocation::GSToken(0x05, 0x02, "Water Temple GS Falling Platform Room",            WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM,            {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_GS_CENTRAL_PILLAR]                    = ItemLocation::GSToken(0x05, 0x04, "Water Temple GS Central Pillar",                   WATER_TEMPLE_GS_CENTRAL_PILLAR,                   {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST]               = ItemLocation::GSToken(0x05, 0x08, "Water Temple GS Near Boss Key Chest",              WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST,              {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_GS_RIVER]                             = ItemLocation::GSToken(0x05, 0x10, "Water Temple GS River",                            WATER_TEMPLE_GS_RIVER,                            {Category::cWaterTemple, Category::cSkulltula,});

    locationTable[WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH]      = ItemLocation::GSToken(0x05, 0x04, "Water Temple MQ GS Before Upper Water Switch",     WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH,     {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA]          = ItemLocation::GSToken(0x05, 0x08, "Water Temple MQ GS Freestanding Key Area",         WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,         {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY]               = ItemLocation::GSToken(0x05, 0x01, "Water Temple MQ GS Lizalfos Hallway",              WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,              {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_MQ_GS_RIVER]                          = ItemLocation::GSToken(0x05, 0x02, "Water Temple MQ GS River",                         WATER_TEMPLE_MQ_GS_RIVER,                         {Category::cWaterTemple, Category::cSkulltula,});
    locationTable[WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH]              = ItemLocation::GSToken(0x05, 0x10, "Water Temple MQ GS Triple Wall Torch",             WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,             {Category::cWaterTemple, Category::cSkulltula,});

    locationTable[SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM]        = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple GS Hall After Sun Block Room",       SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM,       {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_GS_BOULDER_ROOM]                     = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple GS Boulder Room",                    SPIRIT_TEMPLE_GS_BOULDER_ROOM,                    {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_GS_LOBBY]                            = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple GS Lobby",                           SPIRIT_TEMPLE_GS_LOBBY,                           {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM]                = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple GS Sun on Floor Room",               SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,               {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_GS_METAL_FENCE]                      = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple GS Metal Fence",                     SPIRIT_TEMPLE_GS_METAL_FENCE,                     {Category::cSpiritTemple, Category::cSkulltula});

    locationTable[SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM]                 = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple MQ GS Symphony Room",                SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,                {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM]                   = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple MQ GS Leever Room",                  SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,                  {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST]        = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple MQ GS Nine Thrones Room West",       SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,       {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH]       = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple MQ GS Nine Thrones Room North",      SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,      {Category::cSpiritTemple, Category::cSkulltula});
    locationTable[SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM]                = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple MQ GS Sun Block Room",               SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,               {Category::cSpiritTemple, Category::cSkulltula});

    locationTable[SHADOW_TEMPLE_GS_SINGLE_GIANT_POT]                 = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple GS Single Giant Pot",                SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,                {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM]              = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple GS Falling Spikes Room",             SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,             {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT]                 = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple GS Triple Giant Pot",                SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,                {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM]                   = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple GS Like Like Room",                  SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                  {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_GS_NEAR_SHIP]                        = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple GS Near Ship",                       SHADOW_TEMPLE_GS_NEAR_SHIP,                       {Category::cShadowTemple, Category::cSkulltula,});

    locationTable[SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM]           = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple MQ GS Falling Spikes Room",          SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,          {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM]                = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple MQ GS Wind Hint Room",               SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,               {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_MQ_GS_AFTER_WIND]                    = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple MQ GS After Wind",                   SHADOW_TEMPLE_MQ_GS_AFTER_WIND,                   {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_MQ_GS_AFTER_SHIP]                    = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple MQ GS After Ship",                   SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,                   {Category::cShadowTemple, Category::cSkulltula,});
    locationTable[SHADOW_TEMPLE_MQ_GS_NEAR_BOSS]                     = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple MQ GS Near Boss",                    SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,                    {Category::cShadowTemple, Category::cSkulltula,});

    locationTable[BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE]              = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well GS Like Like Cage",             BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,             {Category::cBottomOfTheWell, Category::cSkulltula,});
    locationTable[BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM]             = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well GS East Inner Room",            BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,            {Category::cBottomOfTheWell, Category::cSkulltula,});
    locationTable[BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM]             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well GS West Inner Room",            BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,            {Category::cBottomOfTheWell, Category::cSkulltula,});

    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT]                 = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well MQ GS Basement",                BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,                {Category::cBottomOfTheWell, Category::cSkulltula,});
    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM]              = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well MQ GS Coffin Room",             BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,             {Category::cBottomOfTheWell, Category::cSkulltula,});
    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM]          = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well MQ GS West Inner Room",         BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,         {Category::cBottomOfTheWell, Category::cSkulltula,});

    locationTable[ICE_CAVERN_GS_PUSH_BLOCK_ROOM]                     = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern GS Push Block Room",                    ICE_CAVERN_GS_PUSH_BLOCK_ROOM,                    {Category::cIceCavern, Category::cSkulltula,});
    locationTable[ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM]                = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern GS Spinning Scythe Room",               ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM,               {Category::cIceCavern, Category::cSkulltula,});
    locationTable[ICE_CAVERN_GS_HEART_PIECE_ROOM]                    = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern GS Heart Piece Room",                   ICE_CAVERN_GS_HEART_PIECE_ROOM,                   {Category::cIceCavern, Category::cSkulltula,});

    locationTable[ICE_CAVERN_MQ_GS_SCARECROW]                        = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern MQ GS Scarecrow",                       ICE_CAVERN_MQ_GS_SCARECROW,                       {Category::cIceCavern, Category::cSkulltula,});
    locationTable[ICE_CAVERN_MQ_GS_ICE_BLOCK]                        = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern MQ GS Ice Block",                       ICE_CAVERN_MQ_GS_ICE_BLOCK,                       {Category::cIceCavern, Category::cSkulltula,});
    locationTable[ICE_CAVERN_MQ_GS_RED_ICE]                          = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern MQ GS Red Ice",                         ICE_CAVERN_MQ_GS_RED_ICE,                         {Category::cIceCavern, Category::cSkulltula,});

    //Overworld
    locationTable[KF_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(0x0C, 0x01, "KF GS Bean Patch",                                 KF_GS_BEAN_PATCH,                                 {Category::cKokiriForest, Category::cSkulltula,});
    locationTable[KF_GS_KNOW_IT_ALL_HOUSE]                           = ItemLocation::GSToken(0x0C, 0x02, "KF GS Know It All House",                          KF_GS_KNOW_IT_ALL_HOUSE,                          {Category::cKokiriForest, Category::cSkulltula,});
    locationTable[KF_GS_HOUSE_OF_TWINS]                              = ItemLocation::GSToken(0x0C, 0x04, "KF GS House of Twins",                             KF_GS_HOUSE_OF_TWINS,                             {Category::cKokiriForest, Category::cSkulltula,});

    locationTable[LW_GS_BEAN_PATCH_NEAR_BRIDGE]                      = ItemLocation::GSToken(0x0D, 0x01, "LW GS Bean Patch Near Bridge",                     LW_GS_BEAN_PATCH_NEAR_BRIDGE,                     {Category::cLostWoods, Category::cSkulltula,});
    locationTable[LW_GS_BEAN_PATCH_NEAR_THEATER]                     = ItemLocation::GSToken(0x0D, 0x02, "LW GS Bean Patch Near Theater",                    LW_GS_BEAN_PATCH_NEAR_THEATER,                    {Category::cLostWoods, Category::cSkulltula,});
    locationTable[LW_GS_ABOVE_THEATER]                               = ItemLocation::GSToken(0x0D, 0x04, "LW GS Above Theater",                              LW_GS_ABOVE_THEATER,                              {Category::cLostWoods, Category::cSkulltula,});
    locationTable[SFM_GS]                                            = ItemLocation::GSToken(0x0D, 0x08, "SFM GS",                                           SFM_GS,                                           {Category::cSacredForestMeadow, Category::cSkulltula,});

    locationTable[HF_GS_COW_GROTTO]                                  = ItemLocation::GSToken(0x0A, 0x01, "HF GS Cow Grotto",                                 HF_GS_COW_GROTTO,                                 {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});
    locationTable[HF_GS_NEAR_KAK_GROTTO]                             = ItemLocation::GSToken(0x0A, 0x02, "HF GS Near Kak Grotto",                            HF_GS_NEAR_KAK_GROTTO,                            {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});

    locationTable[LH_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(0x12, 0x01, "LH GS Bean Patch",                                 LH_GS_BEAN_PATCH,                                 {Category::cLakeHylia, Category::cSkulltula,});
    locationTable[LH_GS_SMALL_ISLAND]                                = ItemLocation::GSToken(0x12, 0x02, "LH GS Small Island",                               LH_GS_SMALL_ISLAND,                               {Category::cLakeHylia, Category::cSkulltula,});
    locationTable[LH_GS_LAB_WALL]                                    = ItemLocation::GSToken(0x12, 0x04, "LH GS Lab Wall",                                   LH_GS_LAB_WALL,                                   {Category::cLakeHylia, Category::cSkulltula,});
    locationTable[LH_GS_LAB_CRATE]                                   = ItemLocation::GSToken(0x12, 0x08, "LH GS Lab Crate",                                  LH_GS_LAB_CRATE,                                  {Category::cLakeHylia, Category::cSkulltula,});
    locationTable[LH_GS_TREE]                                        = ItemLocation::GSToken(0x12, 0x10, "LH GS Tree",                                       LH_GS_TREE,                                       {Category::cLakeHylia, Category::cSkulltula,});

    locationTable[GV_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(0x13, 0x01, "GV GS Bean Patch",                                 GV_GS_BEAN_PATCH,                                 {Category::cGerudoValley, Category::cSkulltula,});
    locationTable[GV_GS_SMALL_BRIDGE]                                = ItemLocation::GSToken(0x13, 0x02, "GV GS Small Bridge",                               GV_GS_SMALL_BRIDGE,                               {Category::cGerudoValley, Category::cSkulltula,});
    locationTable[GV_GS_PILLAR]                                      = ItemLocation::GSToken(0x13, 0x04, "GV GS Pillar",                                     GV_GS_PILLAR,                                     {Category::cGerudoValley, Category::cSkulltula,});
    locationTable[GV_GS_BEHIND_TENT]                                 = ItemLocation::GSToken(0x13, 0x08, "GV GS Behind Tent",                                GV_GS_BEHIND_TENT,                                {Category::cGerudoValley, Category::cSkulltula,});

    locationTable[GF_GS_ARCHERY_RANGE]                               = ItemLocation::GSToken(0x14, 0x01, "GF GS Archery Range",                              GF_GS_ARCHERY_RANGE,                              {Category::cGerudoFortress, Category::cSkulltula,});
    locationTable[GF_GS_TOP_FLOOR]                                   = ItemLocation::GSToken(0x14, 0x02, "GF GS Top Floor",                                  GF_GS_TOP_FLOOR,                                  {Category::cGerudoFortress, Category::cSkulltula,});

    locationTable[WASTELAND_GS]                                      = ItemLocation::GSToken(0x15, 0x02, "Wasteland GS",                                     WASTELAND_GS,                                     {Category::cHauntedWasteland, Category::cSkulltula,});
    locationTable[COLOSSUS_GS_BEAN_PATCH]                            = ItemLocation::GSToken(0x15, 0x01, "Colossus GS Bean Patch",                           COLOSSUS_GS_BEAN_PATCH,                           {Category::cDesertColossus, Category::cSkulltula,});
    locationTable[COLOSSUS_GS_HILL]                                  = ItemLocation::GSToken(0x15, 0x04, "Colossus GS Hill",                                 COLOSSUS_GS_HILL,                                 {Category::cDesertColossus, Category::cSkulltula,});
    locationTable[COLOSSUS_GS_TREE]                                  = ItemLocation::GSToken(0x15, 0x08, "Colossus GS Tree",                                 COLOSSUS_GS_TREE,                                 {Category::cDesertColossus, Category::cSkulltula,});

    locationTable[OGC_GS]                                            = ItemLocation::GSToken(0x0E, 0x01, "OGC GS",                                           OGC_GS,                                           {Category::cOutsideGanonsCastle, Category::cSkulltula,});
    locationTable[HC_GS_STORMS_GROTTO]                               = ItemLocation::GSToken(0x0E, 0x02, "HC GS Storms Grotto",                              HC_GS_STORMS_GROTTO,                              {Category::cHyruleCastle, Category::cSkulltula, Category::cGrotto});
    locationTable[HC_GS_TREE]                                        = ItemLocation::GSToken(0x0E, 0x04, "HC GS Tree",                                       HC_GS_TREE,                                       {Category::cHyruleCastle, Category::cSkulltula,});
    locationTable[MARKET_GS_GUARD_HOUSE]                             = ItemLocation::GSToken(0x0E, 0x08, "Market GS Guard House",                            MARKET_GS_GUARD_HOUSE,                            {Category::cInnerMarket, Category::cSkulltula,});

    locationTable[KAK_GS_HOUSE_UNDER_CONSTRUCTION]                   = ItemLocation::GSToken(0x10, 0x08, "Kak GS House Under Construction",                  KAK_GS_HOUSE_UNDER_CONSTRUCTION,                  {Category::cKakarikoVillage, Category::cSkulltula,});
    locationTable[KAK_GS_SKULLTULA_HOUSE]                            = ItemLocation::GSToken(0x10, 0x10, "Kak GS Skulltula House",                           KAK_GS_SKULLTULA_HOUSE,                           {Category::cKakarikoVillage, Category::cSkulltula,});
    locationTable[KAK_GS_GUARDS_HOUSE]                               = ItemLocation::GSToken(0x10, 0x02, "Kak GS Guards House",                              KAK_GS_GUARDS_HOUSE,                              {Category::cKakarikoVillage, Category::cSkulltula,});
    locationTable[KAK_GS_TREE]                                       = ItemLocation::GSToken(0x10, 0x20, "Kak GS Tree",                                      KAK_GS_TREE,                                      {Category::cKakarikoVillage, Category::cSkulltula,});
    locationTable[KAK_GS_WATCHTOWER]                                 = ItemLocation::GSToken(0x10, 0x04, "Kak GS Watchtower",                                KAK_GS_WATCHTOWER,                                {Category::cKakarikoVillage, Category::cSkulltula,});
    locationTable[KAK_GS_ABOVE_IMPAS_HOUSE]                          = ItemLocation::GSToken(0x10, 0x40, "Kak GS Above Impas House",                         KAK_GS_ABOVE_IMPAS_HOUSE,                         {Category::cKakarikoVillage, Category::cSkulltula,});

    locationTable[GRAVEYARD_GS_WALL]                                 = ItemLocation::GSToken(0x10, 0x80, "Graveyard GS Wall",                                GRAVEYARD_GS_WALL,                                {Category::cGraveyard, Category::cSkulltula,});
    locationTable[GRAVEYARD_GS_BEAN_PATCH]                           = ItemLocation::GSToken(0x10, 0x01, "Graveyard GS Bean Patch",                          GRAVEYARD_GS_BEAN_PATCH,                          {Category::cGraveyard, Category::cSkulltula,});

    locationTable[DMC_GS_BEAN_PATCH]                                 = ItemLocation::GSToken(0x0F, 0x01, "DMC GS Bean Patch",                                DMC_GS_BEAN_PATCH,                                {Category::cDeathMountainCrater, Category::cSkulltula,});
    locationTable[DMC_GS_CRATE]                                      = ItemLocation::GSToken(0x0F, 0x80, "DMC GS Crate",                                     DMC_GS_CRATE,                                     {Category::cDeathMountainCrater, Category::cSkulltula,});

    locationTable[DMT_GS_BEAN_PATCH]                                 = ItemLocation::GSToken(0x0F, 0x02, "DMT GS Bean Patch",                                DMT_GS_BEAN_PATCH,                                {Category::cDeathMountainTrail, Category::cSkulltula,});
    locationTable[DMT_GS_NEAR_KAK]                                   = ItemLocation::GSToken(0x0F, 0x04, "DMT GS Near Kak",                                  DMT_GS_NEAR_KAK,                                  {Category::cDeathMountainTrail, Category::cSkulltula,});
    locationTable[DMT_GS_ABOVE_DODONGOS_CAVERN]                      = ItemLocation::GSToken(0x0F, 0x08, "DMT GS Above Dodongos Cavern",                     DMT_GS_ABOVE_DODONGOS_CAVERN,                     {Category::cDeathMountainTrail, Category::cSkulltula,});
    locationTable[DMT_GS_FALLING_ROCKS_PATH]                         = ItemLocation::GSToken(0x0F, 0x10, "DMT GS Falling Rocks Path",                        DMT_GS_FALLING_ROCKS_PATH,                        {Category::cDeathMountainTrail, Category::cSkulltula,});

    locationTable[GC_GS_CENTER_PLATFORM]                             = ItemLocation::GSToken(0x0F, 0x20, "GC GS Center Platform",                            GC_GS_CENTER_PLATFORM,                            {Category::cGoronCity, Category::cSkulltula,});
    locationTable[GC_GS_BOULDER_MAZE]                                = ItemLocation::GSToken(0x0F, 0x40, "GC GS Boulder Maze",                               GC_GS_BOULDER_MAZE,                               {Category::cGoronCity, Category::cSkulltula,});

    locationTable[ZR_GS_LADDER]                                      = ItemLocation::GSToken(0x11, 0x01, "ZR GS Ladder",                                     ZR_GS_LADDER,                                     {Category::cZorasRiver, Category::cSkulltula,});
    locationTable[ZR_GS_TREE]                                        = ItemLocation::GSToken(0x11, 0x02, "ZR GS Tree",                                       ZR_GS_TREE,                                       {Category::cZorasRiver, Category::cSkulltula,});
    locationTable[ZR_GS_ABOVE_BRIDGE]                                = ItemLocation::GSToken(0x11, 0x08, "ZR GS Above Bridge",                               ZR_GS_ABOVE_BRIDGE,                               {Category::cZorasRiver, Category::cSkulltula,});
    locationTable[ZR_GS_NEAR_RAISED_GROTTOS]                         = ItemLocation::GSToken(0x11, 0x10, "ZR GS Near Raised Grottos",                        ZR_GS_NEAR_RAISED_GROTTOS,                        {Category::cZorasRiver, Category::cSkulltula,});

    locationTable[ZD_GS_FROZEN_WATERFALL]                            = ItemLocation::GSToken(0x11, 0x40, "ZD GS Frozen Waterfall",                           ZD_GS_FROZEN_WATERFALL,                           {Category::cZorasDomain, Category::cSkulltula,});
    locationTable[ZF_GS_ABOVE_THE_LOG]                               = ItemLocation::GSToken(0x11, 0x04, "ZF GS Above The Log",                              ZF_GS_ABOVE_THE_LOG,                              {Category::cZorasFountain, Category::cSkulltula,});
    locationTable[ZF_GS_HIDDEN_CAVE]                                 = ItemLocation::GSToken(0x11, 0x20, "ZF GS Hidden Cave",                                ZF_GS_HIDDEN_CAVE,                                {Category::cZorasFountain, Category::cSkulltula,});
    locationTable[ZF_GS_TREE]                                        = ItemLocation::GSToken(0x11, 0x80, "ZF GS Tree",                                       ZF_GS_TREE,                                       {Category::cZorasFountain, Category::cSkulltula,});

    locationTable[LLR_GS_BACK_WALL]                                  = ItemLocation::GSToken(0x0B, 0x01, "LLR GS Back Wall",                                 LLR_GS_BACK_WALL,                                 {Category::cLonLonRanch, Category::cSkulltula,});
    locationTable[LLR_GS_RAIN_SHED]                                  = ItemLocation::GSToken(0x0B, 0x02, "LLR GS Rain Shed",                                 LLR_GS_RAIN_SHED,                                 {Category::cLonLonRanch, Category::cSkulltula,});
    locationTable[LLR_GS_HOUSE_WINDOW]                               = ItemLocation::GSToken(0x0B, 0x04, "LLR GS House Window",                              LLR_GS_HOUSE_WINDOW,                              {Category::cLonLonRanch, Category::cSkulltula,});
    locationTable[LLR_GS_TREE]                                       = ItemLocation::GSToken(0x0B, 0x08, "LLR GS Tree",                                      LLR_GS_TREE,                                      {Category::cLonLonRanch, Category::cSkulltula,});

    /*-------------------------------
              --- BOSSES ---
      -------------------------------*/

    locationTable[LINKS_POCKET]                                  = ItemLocation::Reward (0xFF, 0xFF,                    "Link's Pocket",               LINKS_POCKET,                     {},                                                                                                          SpoilerCollectionCheck::AlwaysCollected());
    locationTable[QUEEN_GOHMA]                                   = ItemLocation::Reward (0xFF, DUNGEON_DEKU_TREE,       "Queen Gohma",                 QUEEN_GOHMA,                      {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x19));
    locationTable[KING_DODONGO]                                  = ItemLocation::Reward (0xFF, DUNGEON_DODONGOS_CAVERN, "King Dodongo",                KING_DODONGO,                     {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x25));
    locationTable[BARINADE]                                      = ItemLocation::Reward (0xFF, DUNGEON_JABUJABUS_BELLY, "Barinade",                    BARINADE,                         {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x37));
    locationTable[PHANTOM_GANON]                                 = ItemLocation::Reward (0xFF, DUNGEON_FOREST_TEMPLE,   "Phantom Ganon",               PHANTOM_GANON,                    {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x48));
    locationTable[VOLVAGIA]                                      = ItemLocation::Reward (0xFF, DUNGEON_FIRE_TEMPLE,     "Volvagia",                    VOLVAGIA,                         {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x49));
    locationTable[MORPHA]                                        = ItemLocation::Reward (0xFF, DUNGEON_WATER_TEMPLE,    "Morpha",                      MORPHA,                           {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x4A));
    locationTable[TWINROVA]                                      = ItemLocation::Reward (0xFF, DUNGEON_SPIRIT_TEMPLE,   "Twinrova",                    TWINROVA,                         {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x47));
    locationTable[BONGO_BONGO]                                   = ItemLocation::Reward (0xFF, DUNGEON_SHADOW_TEMPLE,   "Bongo Bongo",                 BONGO_BONGO,                      {},                                                                                                          SpoilerCollectionCheck::EventChkInf(0x46));
    locationTable[GANON]                                         = ItemLocation::Reward (0xFF, 0xF0,                    "Ganon",                       NONE,                             {},                                                                                                          SpoilerCollectionCheck::None());

    /*-------------------------------
          ---HEART CONTAINERS ---
      -------------------------------*/

    locationTable[DEKU_TREE_QUEEN_GOHMA_HEART]                   = ItemLocation::Base   (0x11, 0x4F, "Deku Tree Queen Gohma Heart Container",          DEKU_TREE_QUEEN_GOHMA_HEART,        {Category::cDekuTree, Category::cBossHeart, Category::cSongDungeonReward},                                 SpoilerCollectionCheck::Collectable(0x11, 0x4F));
    locationTable[DODONGOS_CAVERN_KING_DODONGO_HEART]            = ItemLocation::Base   (0x12, 0x4F, "Dodongos Cavern King Dodongo Heart Container",   DODONGOS_CAVERN_KING_DODONGO_HEART, {Category::cDodongosCavern, Category::cBossHeart, Category::cSongDungeonReward},                           SpoilerCollectionCheck::Collectable(0x12, 0x4F));
    locationTable[JABU_JABUS_BELLY_BARINADE_HEART]               = ItemLocation::Base   (0x13, 0x4F, "Jabu Jabus Belly Barinade Heart Container",      JABU_JABUS_BELLY_BARINADE_HEART,    {Category::cJabuJabusBelly, Category::cBossHeart, Category::cSongDungeonReward},                           SpoilerCollectionCheck::Collectable(0x13, 0x4F));
    locationTable[FOREST_TEMPLE_PHANTOM_GANON_HEART]             = ItemLocation::Base   (0x14, 0x4F, "Forest Temple Phantom Ganon Heart Container",    FOREST_TEMPLE_PHANTOM_GANON_HEART,  {Category::cForestTemple, Category::cBossHeart, Category::cSongDungeonReward},                             SpoilerCollectionCheck::Collectable(0x14, 0x4F));
    locationTable[FIRE_TEMPLE_VOLVAGIA_HEART]                    = ItemLocation::Base   (0x15, 0x4F, "Fire Temple Volvagia Heart Container",           FIRE_TEMPLE_VOLVAGIA_HEART,         {Category::cFireTemple, Category::cBossHeart, Category::cSongDungeonReward},                               SpoilerCollectionCheck::Collectable(0x15, 0x4F));
    locationTable[WATER_TEMPLE_MORPHA_HEART]                     = ItemLocation::Base   (0x16, 0x4F, "Water Temple Morpha Heart Container",            WATER_TEMPLE_MORPHA_HEART,          {Category::cWaterTemple, Category::cBossHeart, Category::cSongDungeonReward},                              SpoilerCollectionCheck::Collectable(0x16, 0x4F));
    locationTable[SPIRIT_TEMPLE_TWINROVA_HEART]                  = ItemLocation::Base   (0x17, 0x4F, "Spirit Temple Twinrova Heart Container",         SPIRIT_TEMPLE_TWINROVA_HEART,       {Category::cSpiritTemple, Category::cBossHeart, Category::cSongDungeonReward},                             SpoilerCollectionCheck::Collectable(0x17, 0x4F));
    locationTable[SHADOW_TEMPLE_BONGO_BONGO_HEART]               = ItemLocation::Base   (0x18, 0x4F, "Shadow Temple Bongo Bongo Heart Container",      SHADOW_TEMPLE_BONGO_BONGO_HEART,    {Category::cShadowTemple, Category::cBossHeart, Category::cSongDungeonReward},                             SpoilerCollectionCheck::Collectable(0x18, 0x4F));

    /*-------------------------------
            --- CUTSCENES ---
      -------------------------------*/

    locationTable[TOT_LIGHT_ARROWS_CUTSCENE]                     = ItemLocation::Delayed(0xFF, 0x01, "ToT Light Arrow Cutscene",                       TOT_LIGHT_ARROWS_CUTSCENE,         {Category::cTempleOfTime, Category::cMarket},                                                               SpoilerCollectionCheck::EventChkInf(0xC4));
    locationTable[LW_GIFT_FROM_SARIA]                            = ItemLocation::Delayed(0xFF, 0x02, "LW Gift From Saria",                             LW_GIFT_FROM_SARIA,                {Category::cLostWoods, Category::cForest},                                                                  SpoilerCollectionCheck::EventChkInf(0xC1));
    locationTable[ZF_GREAT_FAIRY_REWARD]                         = ItemLocation::Delayed(0xFF, 0x10, "ZF Great Fairy Reward",                          ZF_GREAT_FAIRY_REWARD,             {Category::cZorasFountain, Category::cFairies},                                                             SpoilerCollectionCheck::ItemGetInf(16));
    locationTable[HC_GREAT_FAIRY_REWARD]                         = ItemLocation::Delayed(0xFF, 0x11, "HC Great Fairy Reward",                          HC_GREAT_FAIRY_REWARD,             {Category::cHyruleCastle, Category::cMarket, Category::cFairies},                                           SpoilerCollectionCheck::ItemGetInf(17));
    locationTable[COLOSSUS_GREAT_FAIRY_REWARD]                   = ItemLocation::Delayed(0xFF, 0x12, "Colossus Great Fairy Reward",                    COLOSSUS_GREAT_FAIRY_REWARD,       {Category::cDesertColossus, Category::cFairies},                                                            SpoilerCollectionCheck::ItemGetInf(18));
    locationTable[DMT_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(0xFF, 0x13, "DMT Great Fairy Reward",                         DMT_GREAT_FAIRY_REWARD,            {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cFairies},                              SpoilerCollectionCheck::Collectable(0x3B, 0x13));
    locationTable[DMC_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(0xFF, 0x14, "DMC Great Fairy Reward",                         DMC_GREAT_FAIRY_REWARD,            {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cFairies},                             SpoilerCollectionCheck::Collectable(0x3B, 0x14));
    locationTable[OGC_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(0xFF, 0x15, "OGC Great Fairy Reward",                         OGC_GREAT_FAIRY_REWARD,            {Category::cOutsideGanonsCastle, Category::cMarket, Category::cFairies},                                    SpoilerCollectionCheck::Collectable(0x3B, 0x15));

    locationTable[SHEIK_IN_FOREST]                               = ItemLocation::Delayed(0xFF, 0x20, "Sheik in Forest",                                SHEIK_IN_FOREST,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,},                                       SpoilerCollectionCheck::EventChkInf(0x50));
    locationTable[SHEIK_IN_CRATER]                               = ItemLocation::Delayed(0xFF, 0x21, "Sheik in Crater",                                SHEIK_IN_CRATER,                   {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cSong,},                               SpoilerCollectionCheck::EventChkInf(0x51));
    locationTable[SHEIK_IN_ICE_CAVERN]                           = ItemLocation::Delayed(0xFF, 0x22, "Sheik in Ice Cavern",                            SHEIK_IN_ICE_CAVERN,               {Category::cIceCavern, Category::cSong, Category::cSongDungeonReward},                                      SpoilerCollectionCheck::EventChkInf(0x52));
    locationTable[SHEIK_AT_COLOSSUS]                             = ItemLocation::Delayed(0xFF, 0x23, "Sheik at Colossus",                              SHEIK_AT_COLOSSUS,                 {Category::cDesertColossus, Category::cSong,},                                                              SpoilerCollectionCheck::EventChkInf(0xAC));
    locationTable[SHEIK_IN_KAKARIKO]                             = ItemLocation::Delayed(0xFF, 0x24, "Sheik in Kakariko",                              SHEIK_IN_KAKARIKO,                 {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,},                                        SpoilerCollectionCheck::EventChkInf(0x54));
    locationTable[SHEIK_AT_TEMPLE]                               = ItemLocation::Delayed(0xFF, 0x25, "Sheik at Temple",                                SHEIK_AT_TEMPLE,                   {Category::cTempleOfTime, Category::cMarket, Category::cSong,},                                             SpoilerCollectionCheck::EventChkInf(0x55));
    locationTable[SONG_FROM_IMPA]                                = ItemLocation::Delayed(0xFF, 0x26, "Song from Impa",                                 SONG_FROM_IMPA,                    {Category::cHyruleCastle, Category::cMarket, Category::cSong, Category::cSongDungeonReward},                SpoilerCollectionCheck::EventChkInf(0x59));
    locationTable[SONG_FROM_MALON]                               = ItemLocation::Delayed(0xFF, 0x27, "Song from Malon",                                SONG_FROM_MALON,                   {Category::cLonLonRanch, Category::cSong,},                                                                 SpoilerCollectionCheck::EventChkInf(0x16));
    locationTable[SONG_FROM_SARIA]                               = ItemLocation::Delayed(0xFF, 0x28, "Song from Saria",                                SONG_FROM_SARIA,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,},                                       SpoilerCollectionCheck::EventChkInf(0x06));
    locationTable[SONG_FROM_COMPOSERS_GRAVE]                     = ItemLocation::Delayed(0xFF, 0x29, "Song from Composers Grave",                      SONG_FROM_COMPOSERS_GRAVE,         {Category::cGraveyard, Category::cKakariko, Category::cSong,},                                              SpoilerCollectionCheck::EventChkInf(0x5A));
    locationTable[SONG_FROM_OCARINA_OF_TIME]                     = ItemLocation::Delayed(0xFF, 0x2A, "Song from Ocarina of Time",                      SONG_FROM_OCARINA_OF_TIME,         {Category::cHyruleField, Category::cSong, Category::cNeedSpiritualStones,},                                 SpoilerCollectionCheck::EventChkInf(0xA9));
    locationTable[SONG_FROM_WINDMILL]                            = ItemLocation::Delayed(0xFF, 0x2B, "Song from Windmill",                             SONG_FROM_WINDMILL,                {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,},                                        SpoilerCollectionCheck::EventChkInf(0x5B));

    /*-------------------------------
               --- COWS ---
      -------------------------------*/

    locationTable[KF_LINKS_HOUSE_COW]                            = ItemLocation::Base   (0x34, 0x15, "KF Links House Cow",                             KF_LINKS_HOUSE_COW,                {Category::cForest, Category::cCow, Category::cMinigame},                                                   SpoilerCollectionCheck::Cow(0x34, 0x15));
    locationTable[HF_COW_GROTTO_COW]                             = ItemLocation::Base   (0x3E, 0x16, "HF Cow Grotto Cow",                              HF_COW_GROTTO_COW,                 {Category::cHyruleField, Category::cCow, Category::cGrotto},                                                SpoilerCollectionCheck::Cow(0x3E, 0x16));
    locationTable[LLR_STABLES_LEFT_COW]                          = ItemLocation::Base   (0x36, 0x16, "LLR Stables Left Cow",                           LLR_STABLES_LEFT_COW,              {Category::cLonLonRanch, Category::cCow},                                                                   SpoilerCollectionCheck::Cow(0x36, 0x16));
    locationTable[LLR_STABLES_RIGHT_COW]                         = ItemLocation::Base   (0x36, 0x15, "LLR Stables Right Cow",                          LLR_STABLES_RIGHT_COW,             {Category::cLonLonRanch, Category::cCow},                                                                   SpoilerCollectionCheck::Cow(0x36, 0x15));
    locationTable[LLR_TOWER_LEFT_COW]                            = ItemLocation::Base   (0x4C, 0x15, "LLR Tower Left Cow",                             LLR_TOWER_LEFT_COW,                {Category::cLonLonRanch, Category::cCow},                                                                   SpoilerCollectionCheck::Cow(0x4C, 0x16));
    locationTable[LLR_TOWER_RIGHT_COW]                           = ItemLocation::Base   (0x4C, 0x16, "LLR Tower Right Cow",                            LLR_TOWER_RIGHT_COW,               {Category::cLonLonRanch, Category::cCow},                                                                   SpoilerCollectionCheck::Cow(0x4C, 0x15));
    locationTable[KAK_IMPAS_HOUSE_COW]                           = ItemLocation::Base   (0x37, 0x15, "Kak Impas House Cow",                            KAK_IMPAS_HOUSE_COW,               {Category::cKakarikoVillage, Category::cKakariko, Category::cCow},                                          SpoilerCollectionCheck::Cow(0x37, 0x15));
    locationTable[DMT_COW_GROTTO_COW]                            = ItemLocation::Base   (0x3E, 0x15, "DMT Cow Grotto Cow",                             DMT_COW_GROTTO_COW,                {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cCow, Category::cGrotto},               SpoilerCollectionCheck::Cow(0x3E, 0x15));
    locationTable[GV_COW]                                        = ItemLocation::Base   (0x5A, 0x15, "GV Cow",                                         GV_COW,                            {Category::cGerudoValley, Category::cGerudo, Category::cCow},                                               SpoilerCollectionCheck::Cow(0x5A, 0x15));
    locationTable[JABU_JABUS_BELLY_MQ_COW]                       = ItemLocation::Base   (0x02, 0x15, "Jabu Jabus Belly MQ Cow",                        JABU_JABUS_BELLY_MQ_COW,           {Category::cJabuJabusBelly, Category::cCow},                                                                SpoilerCollectionCheck::Cow(0x02, 0x15));

    /*-------------------------------
              --- SHOPS ---
      8     6               2     4

      7     5               1     3
      -------------------------------*/

    locationTable[KF_SHOP_ITEM_1]                                = ItemLocation::Base(0x2D, 0x30, "KF Shop Item 1",                                   KF_SHOP_ITEM_1,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_2]                                = ItemLocation::Base(0x2D, 0x31, "KF Shop Item 2",                                   KF_SHOP_ITEM_2,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_3]                                = ItemLocation::Base(0x2D, 0x32, "KF Shop Item 3",                                   KF_SHOP_ITEM_3,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_4]                                = ItemLocation::Base(0x2D, 0x33, "KF Shop Item 4",                                   KF_SHOP_ITEM_4,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_5]                                = ItemLocation::Base(0x2D, 0x34, "KF Shop Item 5",                                   KF_SHOP_ITEM_5,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_6]                                = ItemLocation::Base(0x2D, 0x35, "KF Shop Item 6",                                   KF_SHOP_ITEM_6,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_7]                                = ItemLocation::Base(0x2D, 0x36, "KF Shop Item 7",                                   KF_SHOP_ITEM_7,             {Category::cKokiriForest, Category::cForest, Category::cShop});
    locationTable[KF_SHOP_ITEM_8]                                = ItemLocation::Base(0x2D, 0x37, "KF Shop Item 8",                                   KF_SHOP_ITEM_8,             {Category::cKokiriForest, Category::cForest, Category::cShop});

    locationTable[KAK_POTION_SHOP_ITEM_1]                        = ItemLocation::Base(0x30, 0x30, "Kak Potion Shop Item 1",                           KAK_POTION_SHOP_ITEM_1,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_2]                        = ItemLocation::Base(0x30, 0x31, "Kak Potion Shop Item 2",                           KAK_POTION_SHOP_ITEM_2,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_3]                        = ItemLocation::Base(0x30, 0x32, "Kak Potion Shop Item 3",                           KAK_POTION_SHOP_ITEM_3,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_4]                        = ItemLocation::Base(0x30, 0x33, "Kak Potion Shop Item 4",                           KAK_POTION_SHOP_ITEM_4,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_5]                        = ItemLocation::Base(0x30, 0x34, "Kak Potion Shop Item 5",                           KAK_POTION_SHOP_ITEM_5,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_6]                        = ItemLocation::Base(0x30, 0x35, "Kak Potion Shop Item 6",                           KAK_POTION_SHOP_ITEM_6,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_7]                        = ItemLocation::Base(0x30, 0x36, "Kak Potion Shop Item 7",                           KAK_POTION_SHOP_ITEM_7,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_POTION_SHOP_ITEM_8]                        = ItemLocation::Base(0x30, 0x37, "Kak Potion Shop Item 8",                           KAK_POTION_SHOP_ITEM_8,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});

    locationTable[MARKET_BOMBCHU_SHOP_ITEM_1]                    = ItemLocation::Base(0x32, 0x30, "MK Bombchu Shop Item 1",                           MARKET_BOMBCHU_SHOP_ITEM_1, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_2]                    = ItemLocation::Base(0x32, 0x31, "MK Bombchu Shop Item 2",                           MARKET_BOMBCHU_SHOP_ITEM_2, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_3]                    = ItemLocation::Base(0x32, 0x32, "MK Bombchu Shop Item 3",                           MARKET_BOMBCHU_SHOP_ITEM_3, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_4]                    = ItemLocation::Base(0x32, 0x33, "MK Bombchu Shop Item 4",                           MARKET_BOMBCHU_SHOP_ITEM_4, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_5]                    = ItemLocation::Base(0x32, 0x34, "MK Bombchu Shop Item 5",                           MARKET_BOMBCHU_SHOP_ITEM_5, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_6]                    = ItemLocation::Base(0x32, 0x35, "MK Bombchu Shop Item 6",                           MARKET_BOMBCHU_SHOP_ITEM_6, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_7]                    = ItemLocation::Base(0x32, 0x36, "MK Bombchu Shop Item 7",                           MARKET_BOMBCHU_SHOP_ITEM_7, {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_8]                    = ItemLocation::Base(0x32, 0x37, "MK Bombchu Shop Item 8",                           MARKET_BOMBCHU_SHOP_ITEM_8, {Category::cInnerMarket, Category::cMarket, Category::cShop});

    locationTable[MARKET_POTION_SHOP_ITEM_1]                     = ItemLocation::Base(0x31, 0x30, "MK Potion Shop Item 1",                            MARKET_POTION_SHOP_ITEM_1,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_2]                     = ItemLocation::Base(0x31, 0x31, "MK Potion Shop Item 2",                            MARKET_POTION_SHOP_ITEM_2,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_3]                     = ItemLocation::Base(0x31, 0x32, "MK Potion Shop Item 3",                            MARKET_POTION_SHOP_ITEM_3,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_4]                     = ItemLocation::Base(0x31, 0x33, "MK Potion Shop Item 4",                            MARKET_POTION_SHOP_ITEM_4,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_5]                     = ItemLocation::Base(0x31, 0x34, "MK Potion Shop Item 5",                            MARKET_POTION_SHOP_ITEM_5,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_6]                     = ItemLocation::Base(0x31, 0x35, "MK Potion Shop Item 6",                            MARKET_POTION_SHOP_ITEM_6,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_7]                     = ItemLocation::Base(0x31, 0x36, "MK Potion Shop Item 7",                            MARKET_POTION_SHOP_ITEM_7,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_POTION_SHOP_ITEM_8]                     = ItemLocation::Base(0x31, 0x37, "MK Potion Shop Item 8",                            MARKET_POTION_SHOP_ITEM_8,  {Category::cInnerMarket, Category::cMarket, Category::cShop});

    locationTable[MARKET_BAZAAR_ITEM_1]                          = ItemLocation::Base(0x2C, 0x30, "MK Bazaar Item 1",                                 MARKET_BAZAAR_ITEM_1,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_2]                          = ItemLocation::Base(0x2C, 0x31, "MK Bazaar Item 2",                                 MARKET_BAZAAR_ITEM_2,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_3]                          = ItemLocation::Base(0x2C, 0x32, "MK Bazaar Item 3",                                 MARKET_BAZAAR_ITEM_3,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_4]                          = ItemLocation::Base(0x2C, 0x33, "MK Bazaar Item 4",                                 MARKET_BAZAAR_ITEM_4,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_5]                          = ItemLocation::Base(0x2C, 0x34, "MK Bazaar Item 5",                                 MARKET_BAZAAR_ITEM_5,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_6]                          = ItemLocation::Base(0x2C, 0x35, "MK Bazaar Item 6",                                 MARKET_BAZAAR_ITEM_6,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_7]                          = ItemLocation::Base(0x2C, 0x36, "MK Bazaar Item 7",                                 MARKET_BAZAAR_ITEM_7,       {Category::cInnerMarket, Category::cMarket, Category::cShop});
    locationTable[MARKET_BAZAAR_ITEM_8]                          = ItemLocation::Base(0x2C, 0x37, "MK Bazaar Item 8",                                 MARKET_BAZAAR_ITEM_8,       {Category::cInnerMarket, Category::cMarket, Category::cShop});

    locationTable[KAK_BAZAAR_ITEM_1]                             = ItemLocation::Base(0x2C, 0x38, "Kak Bazaar Item 1",                                KAK_BAZAAR_ITEM_1,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_2]                             = ItemLocation::Base(0x2C, 0x39, "Kak Bazaar Item 2",                                KAK_BAZAAR_ITEM_2,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_3]                             = ItemLocation::Base(0x2C, 0x3A, "Kak Bazaar Item 3",                                KAK_BAZAAR_ITEM_3,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_4]                             = ItemLocation::Base(0x2C, 0x3B, "Kak Bazaar Item 4",                                KAK_BAZAAR_ITEM_4,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_5]                             = ItemLocation::Base(0x2C, 0x3C, "Kak Bazaar Item 5",                                KAK_BAZAAR_ITEM_5,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_6]                             = ItemLocation::Base(0x2C, 0x3D, "Kak Bazaar Item 6",                                KAK_BAZAAR_ITEM_6,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_7]                             = ItemLocation::Base(0x2C, 0x3E, "Kak Bazaar Item 7",                                KAK_BAZAAR_ITEM_7,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
    locationTable[KAK_BAZAAR_ITEM_8]                             = ItemLocation::Base(0x2C, 0x3F, "Kak Bazaar Item 8",                                KAK_BAZAAR_ITEM_8,          {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});

    locationTable[ZD_SHOP_ITEM_1]                                = ItemLocation::Base(0x2F, 0x30, "ZD Shop Item 1",                                   ZD_SHOP_ITEM_1,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_2]                                = ItemLocation::Base(0x2F, 0x31, "ZD Shop Item 2",                                   ZD_SHOP_ITEM_2,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_3]                                = ItemLocation::Base(0x2F, 0x32, "ZD Shop Item 3",                                   ZD_SHOP_ITEM_3,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_4]                                = ItemLocation::Base(0x2F, 0x33, "ZD Shop Item 4",                                   ZD_SHOP_ITEM_4,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_5]                                = ItemLocation::Base(0x2F, 0x34, "ZD Shop Item 5",                                   ZD_SHOP_ITEM_5,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_6]                                = ItemLocation::Base(0x2F, 0x35, "ZD Shop Item 6",                                   ZD_SHOP_ITEM_6,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_7]                                = ItemLocation::Base(0x2F, 0x36, "ZD Shop Item 7",                                   ZD_SHOP_ITEM_7,             {Category::cZorasDomain, Category::cShop});
    locationTable[ZD_SHOP_ITEM_8]                                = ItemLocation::Base(0x2F, 0x37, "ZD Shop Item 8",                                   ZD_SHOP_ITEM_8,             {Category::cZorasDomain, Category::cShop});

    locationTable[GC_SHOP_ITEM_1]                                = ItemLocation::Base(0x2E, 0x30, "GC Shop Item 1",                                   GC_SHOP_ITEM_1,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_2]                                = ItemLocation::Base(0x2E, 0x31, "GC Shop Item 2",                                   GC_SHOP_ITEM_2,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_3]                                = ItemLocation::Base(0x2E, 0x32, "GC Shop Item 3",                                   GC_SHOP_ITEM_3,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_4]                                = ItemLocation::Base(0x2E, 0x33, "GC Shop Item 4",                                   GC_SHOP_ITEM_4,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_5]                                = ItemLocation::Base(0x2E, 0x34, "GC Shop Item 5",                                   GC_SHOP_ITEM_5,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_6]                                = ItemLocation::Base(0x2E, 0x35, "GC Shop Item 6",                                   GC_SHOP_ITEM_6,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_7]                                = ItemLocation::Base(0x2E, 0x36, "GC Shop Item 7",                                   GC_SHOP_ITEM_7,             {Category::cGoronCity, Category::cShop});
    locationTable[GC_SHOP_ITEM_8]                                = ItemLocation::Base(0x2E, 0x37, "GC Shop Item 8",                                   GC_SHOP_ITEM_8,             {Category::cGoronCity, Category::cShop});

    /*-------------------------------
          --- GOSSIP STONES ---
      -------------------------------*/
    // These are not actual locations, but are filler spots used for hint reachability. - OoT Randomizer
    //                                                                                        flag + 0x400 = message ID
    locationTable[DMC_GOSSIP_STONE]                              = ItemLocation::HintStone(0x00, 0x05, "DMC Gossip Stone",                            {});
    locationTable[DMT_GOSSIP_STONE]                              = ItemLocation::HintStone(0x00, 0x04, "DMT Gossip Stone",                            {});
    locationTable[COLOSSUS_GOSSIP_STONE]                         = ItemLocation::HintStone(0x00, 0x1A, "Colossus Gossip Stone",                       {});
    locationTable[DODONGOS_CAVERN_GOSSIP_STONE]                  = ItemLocation::HintStone(0x00, 0x14, "Dodongo's Cavern Gossip Stone",               {});
    locationTable[GV_GOSSIP_STONE]                               = ItemLocation::HintStone(0x00, 0x11, "GV Gossip Stone",                             {});
    locationTable[GC_MAZE_GOSSIP_STONE]                          = ItemLocation::HintStone(0x00, 0x15, "GC Maze Gossip Stone",                        {});
    locationTable[GC_MEDIGORON_GOSSIP_STONE]                     = ItemLocation::HintStone(0x00, 0x19, "GC Medigoron Gossip Stone",                   {});
    locationTable[GRAVEYARD_GOSSIP_STONE]                        = ItemLocation::HintStone(0x00, 0x0A, "GY Gossip Stone",                             {});
    locationTable[HC_MALON_GOSSIP_STONE]                         = ItemLocation::HintStone(0x00, 0x12, "HC Malon Gossip Stone",                       {});
    locationTable[HC_ROCK_WALL_GOSSIP_STONE]                     = ItemLocation::HintStone(0x00, 0x0B, "HC Rock Wall Gossip Stone",                   {});
    locationTable[HC_STORMS_GROTTO_GOSSIP_STONE]                 = ItemLocation::HintStone(0x00, 0x13, "HC Storms Grotto Gossip Stone",               {});
    locationTable[KF_DEKU_TREE_GOSSIP_STONE_LEFT]                = ItemLocation::HintStone(0x00, 0x1F, "KF Deku Tree Left Gossip Stone",              {});
    locationTable[KF_DEKU_TREE_GOSSIP_STONE_RIGHT]               = ItemLocation::HintStone(0x00, 0x20, "KF Deku Tree Right Gossip Stone",             {});
    locationTable[KF_GOSSIP_STONE]                               = ItemLocation::HintStone(0x00, 0x1E, "KF Gossip Stone",                             {});
    locationTable[LH_LAB_GOSSIP_STONE]                           = ItemLocation::HintStone(0x00, 0x03, "LH Lab Gossip Stone",                         {});
    locationTable[LH_GOSSIP_STONE_SOUTHEAST]                     = ItemLocation::HintStone(0x00, 0x0F, "LH Southeast Gossip Stone",                   {});
    locationTable[LH_GOSSIP_STONE_SOUTHWEST]                     = ItemLocation::HintStone(0x00, 0x08, "LH Southwest Gossip Stone",                   {});
    locationTable[LW_GOSSIP_STONE]                               = ItemLocation::HintStone(0x00, 0x1D, "LW Gossip Stone",                             {});
    locationTable[SFM_MAZE_GOSSIP_STONE_LOWER]                   = ItemLocation::HintStone(0x00, 0x16, "SFM Maze Lower Gossip Stone",                 {});
    locationTable[SFM_MAZE_GOSSIP_STONE_UPPER]                   = ItemLocation::HintStone(0x00, 0x17, "SFM Maze Upper Gossip Stone",                 {});
    locationTable[SFM_SARIA_GOSSIP_STONE]                        = ItemLocation::HintStone(0x00, 0x1C, "SFM Saria Gossip Stone",                      {});
    locationTable[TOT_GOSSIP_STONE_LEFT]                         = ItemLocation::HintStone(0x00, 0x06, "ToT Left Gossip Stone",                       {});
    locationTable[TOT_GOSSIP_STONE_RIGHT]                        = ItemLocation::HintStone(0x00, 0x07, "ToT Left Center Gossip Stone",                {});
    locationTable[TOT_GOSSIP_STONE_RIGHT_CENTER]                 = ItemLocation::HintStone(0x00, 0x10, "ToT Right Center Gossip Stone",               {});
    locationTable[TOT_GOSSIP_STONE_LEFT_CENTER]                  = ItemLocation::HintStone(0x00, 0x0E, "ToT Right Gossip Stone",                      {});
    locationTable[ZD_GOSSIP_STONE]                               = ItemLocation::HintStone(0x00, 0x09, "ZD Gossip Stone",                             {});
    locationTable[ZF_FAIRY_GOSSIP_STONE]                         = ItemLocation::HintStone(0x00, 0x01, "Fairy Gossip Stone",                          {});
    locationTable[ZF_JABU_GOSSIP_STONE]                          = ItemLocation::HintStone(0x00, 0x02, "Jabu Gossip Stone",                           {});
    locationTable[ZR_NEAR_GROTTOS_GOSSIP_STONE]                  = ItemLocation::HintStone(0x00, 0x0D, "ZR Near Grottos Gossip Stone",                {});
    locationTable[ZR_NEAR_DOMAIN_GOSSIP_STONE]                   = ItemLocation::HintStone(0x00, 0x0C, "ZR Near Domain Gossip Stone",                 {});
    locationTable[HF_COW_GROTTO_GOSSIP_STONE]                    = ItemLocation::HintStone(0x00, 0x1B, "HF Cow Grotto Gossip Stone",                  {});

    locationTable[HF_NEAR_MARKET_GROTTO_GOSSIP_STONE]            = ItemLocation::HintStone(0x00, 0x30, "HF Near Market Gossip Stone",                 {});
    locationTable[HF_SOUTHEAST_GROTTO_GOSSIP_STONE]              = ItemLocation::HintStone(0x00, 0x32, "HF Southeast Gossip Stone",                   {});
    locationTable[HF_OPEN_GROTTO_GOSSIP_STONE]                   = ItemLocation::HintStone(0x00, 0x33, "HF Open Grotto Gossip Stone",                 {});
    locationTable[KAK_OPEN_GROTTO_GOSSIP_STONE]                  = ItemLocation::HintStone(0x00, 0x38, "Kak Open Grotto Gossip Stone",                {});
    locationTable[ZR_OPEN_GROTTO_GOSSIP_STONE]                   = ItemLocation::HintStone(0x00, 0x39, "ZR Open Grotto Gossip Stone",                 {});
    locationTable[KF_STORMS_GROTTO_GOSSIP_STONE]                 = ItemLocation::HintStone(0x00, 0x3C, "KF Storms Gossip Stone",                      {});
    locationTable[LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE]         = ItemLocation::HintStone(0x00, 0x34, "LW Near Shortcuts Gossip Stone",              {});
    locationTable[DMT_STORMS_GROTTO_GOSSIP_STONE]                = ItemLocation::HintStone(0x00, 0x37, "DMT Storms Grotto Gossip Stone",              {});
    locationTable[DMC_UPPER_GROTTO_GOSSIP_STONE]                 = ItemLocation::HintStone(0x00, 0x3A, "DMC Upper Grotto Gossip Stone",               {});

    locationTable[GANONDORF_HINT]                                = ItemLocation::OtherHint(0x00, 0x00, "Ganondorf Hint",                              {});

}
std::vector<LocationKey> KF_ShopLocations = {
  KF_SHOP_ITEM_1,
  KF_SHOP_ITEM_2,
  KF_SHOP_ITEM_3,
  KF_SHOP_ITEM_4,
  KF_SHOP_ITEM_5,
  KF_SHOP_ITEM_6,
  KF_SHOP_ITEM_7,
  KF_SHOP_ITEM_8,
};
std::vector<LocationKey> Kak_PotionShopLocations = {
  KAK_POTION_SHOP_ITEM_1,
  KAK_POTION_SHOP_ITEM_2,
  KAK_POTION_SHOP_ITEM_3,
  KAK_POTION_SHOP_ITEM_4,
  KAK_POTION_SHOP_ITEM_5,
  KAK_POTION_SHOP_ITEM_6,
  KAK_POTION_SHOP_ITEM_7,
  KAK_POTION_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_BombchuShopLocations = {
  MARKET_BOMBCHU_SHOP_ITEM_1,
  MARKET_BOMBCHU_SHOP_ITEM_2,
  MARKET_BOMBCHU_SHOP_ITEM_3,
  MARKET_BOMBCHU_SHOP_ITEM_4,
  MARKET_BOMBCHU_SHOP_ITEM_5,
  MARKET_BOMBCHU_SHOP_ITEM_6,
  MARKET_BOMBCHU_SHOP_ITEM_7,
  MARKET_BOMBCHU_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_PotionShopLocations = {
  MARKET_POTION_SHOP_ITEM_1,
  MARKET_POTION_SHOP_ITEM_2,
  MARKET_POTION_SHOP_ITEM_3,
  MARKET_POTION_SHOP_ITEM_4,
  MARKET_POTION_SHOP_ITEM_5,
  MARKET_POTION_SHOP_ITEM_6,
  MARKET_POTION_SHOP_ITEM_7,
  MARKET_POTION_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_BazaarLocations = {
  MARKET_BAZAAR_ITEM_1,
  MARKET_BAZAAR_ITEM_2,
  MARKET_BAZAAR_ITEM_3,
  MARKET_BAZAAR_ITEM_4,
  MARKET_BAZAAR_ITEM_5,
  MARKET_BAZAAR_ITEM_6,
  MARKET_BAZAAR_ITEM_7,
  MARKET_BAZAAR_ITEM_8,
};
std::vector<LocationKey> Kak_BazaarLocations = {
  KAK_BAZAAR_ITEM_1,
  KAK_BAZAAR_ITEM_2,
  KAK_BAZAAR_ITEM_3,
  KAK_BAZAAR_ITEM_4,
  KAK_BAZAAR_ITEM_5,
  KAK_BAZAAR_ITEM_6,
  KAK_BAZAAR_ITEM_7,
  KAK_BAZAAR_ITEM_8,
};
std::vector<LocationKey> ZD_ShopLocations = {
  ZD_SHOP_ITEM_1,
  ZD_SHOP_ITEM_2,
  ZD_SHOP_ITEM_3,
  ZD_SHOP_ITEM_4,
  ZD_SHOP_ITEM_5,
  ZD_SHOP_ITEM_6,
  ZD_SHOP_ITEM_7,
  ZD_SHOP_ITEM_8,
};
std::vector<LocationKey> GC_ShopLocations = {
  GC_SHOP_ITEM_1,
  GC_SHOP_ITEM_2,
  GC_SHOP_ITEM_3,
  GC_SHOP_ITEM_4,
  GC_SHOP_ITEM_5,
  GC_SHOP_ITEM_6,
  GC_SHOP_ITEM_7,
  GC_SHOP_ITEM_8,
};
//List of shop location lists, used for shop shuffle
std::vector<std::vector<LocationKey>> ShopLocationLists = {
  KF_ShopLocations,
  Kak_PotionShopLocations,
  MK_BombchuShopLocations,
  MK_PotionShopLocations,
  MK_BazaarLocations,
  Kak_BazaarLocations,
  ZD_ShopLocations,
  GC_ShopLocations,
};

//List of gossip stone locations for hints
std::vector<LocationKey> gossipStoneLocations = {
  DMC_GOSSIP_STONE,
  DMT_GOSSIP_STONE,
  COLOSSUS_GOSSIP_STONE,
  DODONGOS_CAVERN_GOSSIP_STONE,
  GV_GOSSIP_STONE,
  GC_MAZE_GOSSIP_STONE,
  GC_MEDIGORON_GOSSIP_STONE,
  GRAVEYARD_GOSSIP_STONE,
  HC_MALON_GOSSIP_STONE,
  HC_ROCK_WALL_GOSSIP_STONE,
  HC_STORMS_GROTTO_GOSSIP_STONE,
  KF_DEKU_TREE_GOSSIP_STONE_LEFT,
  KF_DEKU_TREE_GOSSIP_STONE_RIGHT,
  KF_GOSSIP_STONE,
  LH_LAB_GOSSIP_STONE,
  LH_GOSSIP_STONE_SOUTHEAST,
  LH_GOSSIP_STONE_SOUTHWEST,
  LW_GOSSIP_STONE,
  SFM_MAZE_GOSSIP_STONE_LOWER,
  SFM_MAZE_GOSSIP_STONE_UPPER,
  SFM_SARIA_GOSSIP_STONE,
  TOT_GOSSIP_STONE_LEFT,
  TOT_GOSSIP_STONE_RIGHT,
  TOT_GOSSIP_STONE_RIGHT_CENTER,
  TOT_GOSSIP_STONE_LEFT_CENTER,
  ZD_GOSSIP_STONE,
  ZF_FAIRY_GOSSIP_STONE,
  ZF_JABU_GOSSIP_STONE,
  ZR_NEAR_GROTTOS_GOSSIP_STONE,
  ZR_NEAR_DOMAIN_GOSSIP_STONE,
  HF_COW_GROTTO_GOSSIP_STONE,
  HF_NEAR_MARKET_GROTTO_GOSSIP_STONE,
  HF_SOUTHEAST_GROTTO_GOSSIP_STONE,
  HF_OPEN_GROTTO_GOSSIP_STONE,
  KAK_OPEN_GROTTO_GOSSIP_STONE,
  ZR_OPEN_GROTTO_GOSSIP_STONE,
  KF_STORMS_GROTTO_GOSSIP_STONE,
  LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE,
  DMT_STORMS_GROTTO_GOSSIP_STONE,
  DMC_UPPER_GROTTO_GOSSIP_STONE,
};

std::vector<LocationKey> dungeonRewardLocations = {
  //Bosses
  QUEEN_GOHMA,
  KING_DODONGO,
  BARINADE,
  PHANTOM_GANON,
  VOLVAGIA,
  MORPHA,
  TWINROVA,
  BONGO_BONGO,
  LINKS_POCKET,
};
std::vector<LocationKey> overworldLocations = {
  //Kokiri Forest
  KF_KOKIRI_SWORD_CHEST,
  KF_MIDOS_TOP_LEFT_CHEST,
  KF_MIDOS_TOP_RIGHT_CHEST,
  KF_MIDOS_BOTTOM_LEFT_CHEST,
  KF_MIDOS_BOTTOM_RIGHT_CHEST,
  KF_STORMS_GROTTO_CHEST,
  KF_LINKS_HOUSE_COW,

  //Shop
  KF_SHOP_ITEM_1,
  KF_SHOP_ITEM_2,
  KF_SHOP_ITEM_3,
  KF_SHOP_ITEM_4,
  KF_SHOP_ITEM_5,
  KF_SHOP_ITEM_6,
  KF_SHOP_ITEM_7,
  KF_SHOP_ITEM_8,

  //Lost Woods
  LW_GIFT_FROM_SARIA,
  LW_SKULL_KID,
  LW_OCARINA_MEMORY_GAME,
  LW_TARGET_IN_WOODS,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,
  LW_DEKU_SCRUB_NEAR_BRIDGE,
  LW_NEAR_SHORTCUTS_GROTTO_CHEST,
  LW_DEKU_SCRUB_GROTTO_REAR,
  LW_DEKU_SCRUB_GROTTO_FRONT,
  DEKU_THEATER_SKULL_MASK,
  DEKU_THEATER_MASK_OF_TRUTH,

  //Sacred Forest Meadow
  SONG_FROM_SARIA,
  SHEIK_IN_FOREST,
  SFM_WOLFOS_GROTTO_CHEST,
  SFM_DEKU_SCRUB_GROTTO_REAR,
  SFM_DEKU_SCRUB_GROTTO_FRONT,

  //Hyrule Field
  HF_SOUTHEAST_GROTTO_CHEST,
  HF_OPEN_GROTTO_CHEST,
  HF_NEAR_MARKET_GROTTO_CHEST,
  HF_OCARINA_OF_TIME_ITEM,
  SONG_FROM_OCARINA_OF_TIME,
  HF_TEKTITE_GROTTO_FREESTANDING_POH,
  HF_DEKU_SCRUB_GROTTO,
  HF_COW_GROTTO_COW,

  //Lake Hylia
  LH_CHILD_FISHING,
  LH_ADULT_FISHING,
  LH_LAB_DIVE,
  LH_UNDERWATER_ITEM,
  LH_SUN,
  LH_FREESTANDING_POH,
  LH_DEKU_SCRUB_GROTTO_LEFT,
  LH_DEKU_SCRUB_GROTTO_RIGHT,
  LH_DEKU_SCRUB_GROTTO_CENTER,

  //Gerudo Valley
  GV_CHEST,
  GV_WATERFALL_FREESTANDING_POH,
  GV_CRATE_FREESTANDING_POH,
  GV_DEKU_SCRUB_GROTTO_REAR,
  GV_DEKU_SCRUB_GROTTO_FRONT,
  GV_COW,

  //Gerudo Fortress
  GF_CHEST,
  GF_HBA_1000_POINTS,
  GF_HBA_1500_POINTS,
  GF_NORTH_F1_CARPENTER,
  GF_NORTH_F2_CARPENTER,
  GF_SOUTH_F1_CARPENTER,
  GF_SOUTH_F2_CARPENTER,
  GF_GERUDO_TOKEN,

  //Haunted Wasteland
  WASTELAND_CHEST,

  //Desert Colossus
  SHEIK_AT_COLOSSUS,
  COLOSSUS_FREESTANDING_POH,
  COLOSSUS_GREAT_FAIRY_REWARD,
  COLOSSUS_DEKU_SCRUB_GROTTO_REAR,
  COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,

  //Market
  MARKET_TREASURE_CHEST_GAME_REWARD,
  MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,
  MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,
  MARKET_BOMBCHU_BOWLING_BOMBCHUS,
  MARKET_LOST_DOG,
  MARKET_SHOOTING_GALLERY_REWARD,
  MARKET_10_BIG_POES,

  //Market Shops
  MARKET_BOMBCHU_SHOP_ITEM_1,
  MARKET_BOMBCHU_SHOP_ITEM_2,
  MARKET_BOMBCHU_SHOP_ITEM_3,
  MARKET_BOMBCHU_SHOP_ITEM_4,
  MARKET_BOMBCHU_SHOP_ITEM_5,
  MARKET_BOMBCHU_SHOP_ITEM_6,
  MARKET_BOMBCHU_SHOP_ITEM_7,
  MARKET_BOMBCHU_SHOP_ITEM_8,
  MARKET_POTION_SHOP_ITEM_1,
  MARKET_POTION_SHOP_ITEM_2,
  MARKET_POTION_SHOP_ITEM_3,
  MARKET_POTION_SHOP_ITEM_4,
  MARKET_POTION_SHOP_ITEM_5,
  MARKET_POTION_SHOP_ITEM_6,
  MARKET_POTION_SHOP_ITEM_7,
  MARKET_POTION_SHOP_ITEM_8,
  MARKET_BAZAAR_ITEM_1,
  MARKET_BAZAAR_ITEM_2,
  MARKET_BAZAAR_ITEM_3,
  MARKET_BAZAAR_ITEM_4,
  MARKET_BAZAAR_ITEM_5,
  MARKET_BAZAAR_ITEM_6,
  MARKET_BAZAAR_ITEM_7,
  MARKET_BAZAAR_ITEM_8,

  //Hyrule Castle
  HC_MALON_EGG,
  HC_ZELDAS_LETTER,
  SONG_FROM_IMPA,
  HC_GREAT_FAIRY_REWARD,
  OGC_GREAT_FAIRY_REWARD,

  //Temple of Time
  SHEIK_AT_TEMPLE,
  TOT_LIGHT_ARROWS_CUTSCENE,

  //Kakariko
  SHEIK_IN_KAKARIKO,
  KAK_REDEAD_GROTTO_CHEST,
  KAK_OPEN_GROTTO_CHEST,
  KAK_10_GOLD_SKULLTULA_REWARD,
  KAK_20_GOLD_SKULLTULA_REWARD,
  KAK_30_GOLD_SKULLTULA_REWARD,
  KAK_40_GOLD_SKULLTULA_REWARD,
  KAK_50_GOLD_SKULLTULA_REWARD,
  KAK_MAN_ON_ROOF,
  KAK_SHOOTING_GALLERY_REWARD,
  KAK_ANJU_AS_CHILD,
  KAK_ANJU_AS_ADULT,
  KAK_IMPAS_HOUSE_FREESTANDING_POH,
  KAK_WINDMILL_FREESTANDING_POH,
  SONG_FROM_WINDMILL,
  KAK_IMPAS_HOUSE_COW,

  //Kakariko Shops
  KAK_POTION_SHOP_ITEM_1,
  KAK_POTION_SHOP_ITEM_2,
  KAK_POTION_SHOP_ITEM_3,
  KAK_POTION_SHOP_ITEM_4,
  KAK_POTION_SHOP_ITEM_5,
  KAK_POTION_SHOP_ITEM_6,
  KAK_POTION_SHOP_ITEM_7,
  KAK_POTION_SHOP_ITEM_8,
  KAK_BAZAAR_ITEM_1,
  KAK_BAZAAR_ITEM_2,
  KAK_BAZAAR_ITEM_3,
  KAK_BAZAAR_ITEM_4,
  KAK_BAZAAR_ITEM_5,
  KAK_BAZAAR_ITEM_6,
  KAK_BAZAAR_ITEM_7,
  KAK_BAZAAR_ITEM_8,

  //Graveyard
  GRAVEYARD_HOOKSHOT_CHEST,
  GRAVEYARD_SHIELD_GRAVE_CHEST,
  GRAVEYARD_HEART_PIECE_GRAVE_CHEST,
  GRAVEYARD_COMPOSERS_GRAVE_CHEST,
  SONG_FROM_COMPOSERS_GRAVE,
  GRAVEYARD_FREESTANDING_POH,
  GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,
  GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,

  //Death Mountain Trail
  DMT_CHEST,
  DMT_STORMS_GROTTO_CHEST,
  DMT_BIGGORON,
  DMT_GREAT_FAIRY_REWARD,
  DMT_FREESTANDING_POH,
  DMT_COW_GROTTO_COW,

  //Goron City
  GC_MAZE_LEFT_CHEST,
  GC_MAZE_CENTER_CHEST,
  GC_MAZE_RIGHT_CHEST,
  GC_ROLLING_GORON_AS_CHILD,
  GC_ROLLING_GORON_AS_ADULT,
  GC_DARUNIAS_JOY,
  GC_POT_FREESTANDING_POH,
  GC_DEKU_SCRUB_GROTTO_LEFT,
  GC_DEKU_SCRUB_GROTTO_RIGHT,
  GC_DEKU_SCRUB_GROTTO_CENTER,

  //Goron City Shop
  GC_SHOP_ITEM_1,
  GC_SHOP_ITEM_2,
  GC_SHOP_ITEM_3,
  GC_SHOP_ITEM_4,
  GC_SHOP_ITEM_5,
  GC_SHOP_ITEM_6,
  GC_SHOP_ITEM_7,
  GC_SHOP_ITEM_8,

  //Death Mountain
  DMC_UPPER_GROTTO_CHEST,
  DMC_WALL_FREESTANDING_POH,
  DMC_VOLCANO_FREESTANDING_POH,
  SHEIK_IN_CRATER,
  DMC_DEKU_SCRUB,
  DMC_GREAT_FAIRY_REWARD,
  DMC_DEKU_SCRUB_GROTTO_LEFT,
  DMC_DEKU_SCRUB_GROTTO_RIGHT,
  DMC_DEKU_SCRUB_GROTTO_CENTER,

  //Zoras River
  ZR_OPEN_GROTTO_CHEST,
  ZR_MAGIC_BEAN_SALESMAN,
  ZR_FROGS_OCARINA_GAME,
  ZR_FROGS_IN_THE_RAIN,
  ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,
  ZR_NEAR_DOMAIN_FREESTANDING_POH,
  ZR_DEKU_SCRUB_GROTTO_REAR,
  ZR_DEKU_SCRUB_GROTTO_FRONT,

  //Zoras Domain
  ZD_CHEST,
  ZD_DIVING_MINIGAME,
  ZD_KING_ZORA_THAWED,

  //Zora's Domain Shop
  ZD_SHOP_ITEM_1,
  ZD_SHOP_ITEM_2,
  ZD_SHOP_ITEM_3,
  ZD_SHOP_ITEM_4,
  ZD_SHOP_ITEM_5,
  ZD_SHOP_ITEM_6,
  ZD_SHOP_ITEM_7,
  ZD_SHOP_ITEM_8,

  //Zoras Fountain
  ZF_ICEBERG_FREESTANDING_POH,
  ZF_BOTTOM_FREESTANDING_POH,
  ZF_GREAT_FAIRY_REWARD,

  //Lon Lon Ranch
  SONG_FROM_MALON,
  LLR_TALONS_CHICKENS,
  LLR_FREESTANDING_POH,
  LLR_DEKU_SCRUB_GROTTO_LEFT,
  LLR_DEKU_SCRUB_GROTTO_RIGHT,
  LLR_DEKU_SCRUB_GROTTO_CENTER,
  LLR_STABLES_LEFT_COW,
  LLR_STABLES_RIGHT_COW,
  LLR_TOWER_LEFT_COW,
  LLR_TOWER_RIGHT_COW,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  //Overworld
  KF_GS_BEAN_PATCH,
  KF_GS_KNOW_IT_ALL_HOUSE,
  KF_GS_HOUSE_OF_TWINS,

  LW_GS_BEAN_PATCH_NEAR_BRIDGE,
  LW_GS_BEAN_PATCH_NEAR_THEATER,
  LW_GS_ABOVE_THEATER,
  SFM_GS,

  HF_GS_COW_GROTTO,
  HF_GS_NEAR_KAK_GROTTO,

  LH_GS_BEAN_PATCH,
  LH_GS_SMALL_ISLAND,
  LH_GS_LAB_WALL,
  LH_GS_LAB_CRATE,
  LH_GS_TREE,

  GV_GS_BEAN_PATCH,
  GV_GS_SMALL_BRIDGE,
  GV_GS_PILLAR,
  GV_GS_BEHIND_TENT,

  GF_GS_ARCHERY_RANGE,
  GF_GS_TOP_FLOOR,

  WASTELAND_GS,
  COLOSSUS_GS_BEAN_PATCH,
  COLOSSUS_GS_HILL,
  COLOSSUS_GS_TREE,

  OGC_GS,
  HC_GS_STORMS_GROTTO,
  HC_GS_TREE,
  MARKET_GS_GUARD_HOUSE,

  KAK_GS_HOUSE_UNDER_CONSTRUCTION,
  KAK_GS_SKULLTULA_HOUSE,
  KAK_GS_GUARDS_HOUSE,
  KAK_GS_TREE,
  KAK_GS_WATCHTOWER,
  KAK_GS_ABOVE_IMPAS_HOUSE,

  DMC_GS_BEAN_PATCH,
  DMC_GS_CRATE,

  DMT_GS_BEAN_PATCH,
  DMT_GS_NEAR_KAK,
  DMT_GS_ABOVE_DODONGOS_CAVERN,
  DMT_GS_FALLING_ROCKS_PATH,

  GC_GS_CENTER_PLATFORM,
  GC_GS_BOULDER_MAZE,
  GRAVEYARD_GS_WALL,
  GRAVEYARD_GS_BEAN_PATCH,

  ZR_GS_LADDER,
  ZR_GS_TREE,
  ZR_GS_ABOVE_BRIDGE,
  ZR_GS_NEAR_RAISED_GROTTOS,

  ZD_GS_FROZEN_WATERFALL,
  ZF_GS_ABOVE_THE_LOG,
  ZF_GS_HIDDEN_CAVE,
  ZF_GS_TREE,

  LLR_GS_BACK_WALL,
  LLR_GS_RAIN_SHED,
  LLR_GS_HOUSE_WINDOW,
  LLR_GS_TREE,
};

ItemLocation* Location(LocationKey locKey) {
    return &(locationTable[locKey]);
}

std::vector<LocationKey> allLocations = {};
std::vector<LocationKey> everyPossibleLocation = {};

//set of overrides to write to the patch
std::set<ItemOverride, ItemOverride_Compare> overrides = {};

std::vector<std::vector<LocationKey>> playthroughLocations;
std::vector<LocationKey> wothLocations;
bool playthroughBeatable = false;

u16 itemsPlaced = 0;

void AddLocation(LocationKey loc, std::vector<LocationKey>* destination = &allLocations) {
  destination->push_back(loc);
}

template <typename Container>
void AddLocations(const Container& locations, std::vector<LocationKey>* destination = &allLocations) {
  destination->insert(destination->end(), std::cbegin(locations), std::cend(locations));
}

//sort through Vanilla and MQ dungeon locations
void GenerateLocationPool() {

  allLocations.clear();
  AddLocation(LINKS_POCKET);
  AddLocations(overworldLocations);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetDungeonLocations());
  }
}

void PlaceItemInLocation(LocationKey locKey, ItemKey item, bool applyEffectImmediately /*= false*/) {
  auto loc = Location(locKey);
  PlacementLog_Msg("\n");
  PlacementLog_Msg(ItemTable(item).GetName().GetEnglish());
  PlacementLog_Msg(" placed at ");
  PlacementLog_Msg(loc->GetName());
  PlacementLog_Msg("\n\n");

  if (applyEffectImmediately || Settings::Logic.Is(LOGIC_NONE)) {
    ItemTable(item).ApplyEffect();
    loc->Use();
  }

  itemsPlaced++;
  double completion = (double) itemsPlaced / (double)(allLocations.size() + dungeonRewardLocations.size());
  printf("\x1b[8;10HPlacing Items.");
  if (completion > 0.25) printf(".");
  if (completion > 0.50) printf(".");

  //If we're placing a non-shop item in a shop location, we want to record it for custom messages
  if (ItemTable(item).GetItemType() != ITEMTYPE_SHOP && loc->IsCategory(Category::cShop)) {
    int index = TransformShopIndex(GetShopIndex(locKey));
    NonShopItems[index].Name = ItemTable(item).GetName();
    NonShopItems[index].Repurchaseable = ItemTable(item).GetItemType() == ITEMTYPE_REFILL;
  }

  loc->SetPlacedItem(item);
}

std::vector<LocationKey> GetLocations(const std::vector<LocationKey>& locationPool, Category category) {
  std::vector<LocationKey> locationsInCategory;
  for (LocationKey locKey : locationPool) {
    if (Location(locKey)->IsCategory(category)) {
      locationsInCategory.push_back(locKey);
    }
  }
  return locationsInCategory;
}

void LocationReset() {
  for (LocationKey il : allLocations) {
    Location(il)->RemoveFromPool();
  }

  for (LocationKey il : dungeonRewardLocations) {
    Location(il)->RemoveFromPool();
  }

  for (LocationKey il : gossipStoneLocations) {
    Location(il)->RemoveFromPool();
  }

  Location(GANONDORF_HINT)->RemoveFromPool();
}

void ItemReset() {
  for (LocationKey il : allLocations) {
    Location(il)->ResetVariables();
  }

  for (LocationKey il : dungeonRewardLocations) {
    Location(il)->ResetVariables();
  }

  itemsPlaced = 0;
}

void HintReset() {
  for (LocationKey il : gossipStoneLocations) {
    Location(il)->ResetVariables();
  }
}

//Fills everyPossibleLocation and creates an exclusion option for each location.
//everyPossibleLocation is used in the menu to lock/hide excluding locations
void AddExcludedOptions() {
  AddLocations(overworldLocations, &everyPossibleLocation);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetEveryLocation(), &everyPossibleLocation);
  }

  for (LocationKey il: everyPossibleLocation) {
    Location(il)->AddExcludeOption();
  }
}

void CreateOverrides() {
  PlacementLog_Msg("NOW CREATING OVERRIDES\n\n");
  for (LocationKey locKey : allLocations) {
    auto loc = Location(locKey);
    ItemOverride_Value val = ItemTable(loc->GetPlacedItemKey()).Value();
    //If this is an ice trap in a shop, change the name based on what the model will look like
    if (loc->GetPlacedItemKey() == ICE_TRAP && loc->IsCategory(Category::cShop)) {
      NonShopItems[TransformShopIndex(GetShopIndex(locKey))].Name = GetIceTrapName(val.looksLikeItemId);
    }
    overrides.insert({
      .key = loc->Key(),
      .value = val,
    });
    PlacementLog_Msg("\tScene: ");
    PlacementLog_Msg(std::to_string(loc->Key().scene));
    PlacementLog_Msg("\tType: ");
    PlacementLog_Msg(std::to_string(loc->Key().type));
    PlacementLog_Msg("\tFlag:  ");
    PlacementLog_Msg(std::to_string(loc->Key().flag));
    PlacementLog_Msg("\t");
    PlacementLog_Msg(loc->GetName());
    PlacementLog_Msg(": ");
    PlacementLog_Msg(loc->GetPlacedItemName().GetEnglish());
    PlacementLog_Msg("\n");
  }
  PlacementLog_Msg("Overrides Created: ");
  PlacementLog_Msg(std::to_string(overrides.size()));
}
