.arm
.text

.global hook_before_GlobalContext_Update
hook_before_GlobalContext_Update:
    push {r0-r12, lr}
    bl before_GlobalContext_Update
    pop {r0-r12, lr}
    cpy r7,r0
    bx lr

.global hook_after_GlobalContext_Update
hook_after_GlobalContext_Update:
    push {r0-r12, lr}
    bl after_GlobalContext_Update
    pop {r0-r12, lr}
    b 0x2E25F0

.global hook_Gfx_Update
hook_Gfx_Update:
    push {r0-r12, lr}
    bl Gfx_Update
    pop {r0-r12, lr}
    pop {r4-r8, pc}

.global hook_Draw_PreSwapBuffers
hook_Draw_PreSwapBuffers:
    push {r0-r12, lr}
    bl Draw_PreSwapBuffers
    pop {r0-r12, lr}
    bx lr

.global hook_Gfx_SleepQueryCallback
hook_Gfx_SleepQueryCallback:
    push {r0-r12, lr}
    bl Gfx_SleepQueryCallback
    pop {r0-r12, lr}
    add r0,r0,#0x9C
    b 0x3FD6C8

.global hook_Gfx_AwakeCallback
hook_Gfx_AwakeCallback:
    push {r0-r12, lr}
    bl Gfx_AwakeCallback
    pop {r0-r12, lr}
    add r0,r0,#0x9C
    b 0x3FD440

.global hook_IncomingGetItemID
hook_IncomingGetItemID:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r6
    cpy r2,r7
    bl ItemOverride_GetItem
    pop {r0-r12, lr}
    bx lr

.global hook_SaveFile_Init
hook_SaveFile_Init:
    push {r0-r12, lr}
    mov r0, r5
    bl SaveFile_Init
    pop {r0-r12, lr}
    strb r1,[r0,#0x35]
    bx lr

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global hook_OverrideTextID
hook_OverrideTextID:
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideTextID
    b 0x2BC1D0
noOverrideTextID:
    ldrb r1,[r6,#0x4]
    b 0x2BC1C8

.global hook_OverrideItemID
hook_OverrideItemID:
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideItemID
    push {r0-r12, lr}
    cpy r0,r2
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    b 0x2BC1DC
noOverrideItemID:
    ldrb r1,[r6,#0x0]
    b 0x2BC1D4

# Puts override graphic ID into r0, no other effects
# If no active override, puts -0x1
# Need to wrap around this for individual cases because of differing register usage
.global hook_OverrideGraphicID
.global rActiveItemGraphicId_addr
.rActiveItemGraphicId_addr:
    .word rActiveItemGraphicId
hook_OverrideGraphicID:
    ldr r0,.rActiveItemRow_addr
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicID

    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    b returnGraphicID
noOverrideGraphicID:
    mov r0,#-0x1
returnGraphicID:
    bx lr

.global hook_OverrideGraphicID_351B94
hook_OverrideGraphicID_351B94:
    push {r0,r1,lr}
    bl hook_OverrideGraphicID
    cpy r1,r0
    cmp r1,#-0x1
    pop {r0}
    bne returnGraphicID_351B94
    ldrsh r1,[r0,#-0x4]
returnGraphicID_351B94:
    cpy r0,r1
    pop {r1,lr}
    bx lr

.global hook_OverrideGraphicID_35495C
hook_OverrideGraphicID_35495C:
    push {lr}
    bl hook_OverrideGraphicID
    cmp r0,#-0x1
    bne returnGraphicID_35495C
    ldrsh r0,[r6,#0x2]
returnGraphicID_35495C:
    pop {lr}
    bx lr

.global hook_OverrideGraphicID_354BB8
hook_OverrideGraphicID_354BB8:
    push {lr}
    bl hook_OverrideGraphicID
    cmp r0,#-0x1
    bne returnGraphicID_354BB8
    ldrsh r0,[r6,#0x2]
returnGraphicID_354BB8:
    pop {lr}
    bx lr

.global hook_EditDrawGetItemBeforeModelSpawn
hook_EditDrawGetItemBeforeModelSpawn:
    push {r0-r12, lr}
    bl ItemOverride_EditDrawGetItemBeforeModelSpawn
    pop {r0-r12, lr}
    mov r7,#0x0
    bx lr

.global hook_EditDrawDetItemAfterModelSpawn
hook_EditDrawDetItemAfterModelSpawn:
    push {r0-r12, lr}
    bl ItemOverride_EditDrawGetItemAfterModelSpawn
    pop {r0-r12, lr}
    str r0,[r6,#0x78]
    bx lr

# TODO: Text ID in game gets messed up,
# Gives the "What's that?" text instead of
# the text about moving the statue
.global hook_AdultRollingGoronTwo
hook_AdultRollingGoronTwo:
    mov r0,#0x3000
    add r0,r0,#0x38
    b 0x1954B0

.global hook_DaruniaStrengthCheck
hook_DaruniaStrengthCheck:
    push {r0-r12, lr}
    bl EnDu_CheckRewardFlag
    cmp r0,#0x1
    pop {r0-r12, lr}
    b 0x1E48A0

.global hook_GetToken
hook_GetToken:
    push {r0-r12, lr}
    cpy r0,r4
    bl ItemOverride_GetSkulltulaToken
    pop {r0-r12, lr}
    bx lr

.global hook_ModelSpawnGetObjectStatus
hook_ModelSpawnGetObjectStatus:
    push {r1-r12, lr}
    cpy r0,r1
    bl ExtendedObject_GetStatus
    pop {r1-r12, lr}
    bx lr

.global hook_ChestGetIceTrapObjectStatus
hook_ChestGetIceTrapObjectStatus:
    push {r1-r12, lr}
    mov r0,#0x3
    bl ExtendedObject_GetStatus
    pop {r1-r12, lr}
    bx lr

.global hook_PoeCollectorCheckPoints
hook_PoeCollectorCheckPoints:
    push {r0-r12, lr}
    bl EnGb_CheckPoints
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_ItemEtceteraModelDraw
hook_ItemEtceteraModelDraw:
    push {r0-r12, lr}
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x1170B4
    cpy r4,r0
    bx lr

.global hook_KokiriCheckOpenForest
hook_KokiriCheckOpenForest:
    push {r0-r12, lr}
    bl EnKo_CheckOpenForest
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_EnExItemModelDraw
hook_EnExItemModelDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x249BC8
    add r1,r4,#0x148
    bx lr

.global hook_DemoEffectMedallionDraw
hook_DemoEffectMedallionDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x372148
    ldr r0,[r4,#0x2A8]
    b 0x372150

.global hook_DemoEffectStoneDraw
hook_DemoEffectStoneDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x1D20C0
    ldr r0,[r4,#0x2A8]
    b 0x1D20A0

.global hook_EnKoInitCheckForest
hook_EnKoInitCheckForest:
    push {r1-r12, lr}
    bl EnKo_CheckForestTempleBeat
    tst r0,#0x1
    pop {r1-r12, lr}
    bx lr

.global hook_FireArrowCheckChestFlag
hook_FireArrowCheckChestFlag:
    push {r0-r12, lr}
    bl ShotSun_CheckChestFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SerenadeCheckChestFlag
hook_SerenadeCheckChestFlag:
    push {r0-r12, lr}
    bl Cutscene_SerenadeCheckChestFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    cpy r0,r5
    bx lr

.global hook_ScarecrowCheckToBeActivated
hook_ScarecrowCheckToBeActivated:
    push {r0-r12, lr}
    bl Scarecrow_CheckToBeActivated
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_EponasSongCheckFlag
hook_EponasSongCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckEponasSongFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SariasSongCheckFlag
hook_SariasSongCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckSariasSongFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_PoeCollectorGetFirstTextbox
hook_PoeCollectorGetFirstTextbox:
    push {r1-r12, lr}
    bl EnGb_GetFirstTextbox
    pop {r1-r12, lr}
    bx lr

.global hook_ApplyDamageMultiplier
hook_ApplyDamageMultiplier:
    push {r0-r3, r5-r12, lr}
    bl Settings_ApplyDamageMultiplier
    cpy r4,r0
    pop {r0-r3, r5-r12, lr}
    bx lr

.global hook_SceneInitAfterCopyScenes
hook_SceneInitAfterCopyScenes:
    push {r0-r12, lr}
    bl 0x371738
    bl Scene_Init
    pop {r0-r12, lr}
    bx lr

.global hook_StoreChildBButtonEquip
hook_StoreChildBButtonEquip:
    push {r0-r12, lr}
    bl SaveFile_SaveChildBButton
    pop {r0-r12, lr}
    b 0x45F210

.global hook_LullabyCheckFlag
hook_LullabyCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckLullabyFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_FishingIgnoreTempBOne
hook_FishingIgnoreTempBOne:
    bne 0x2C3A14
    push {r0-r12, lr}
    bl isFishing
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x2C3998
    moveq r0,#89
    b 0x2C3A14

.global hook_FishingIgnoreTempBTwo
hook_FishingIgnoreTempBTwo:
    blt 0x34CFD0
    push {r0-r12, lr}
    bl isFishing
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x34CFF0
    ldrb r1,[r4,#0x80]
    b 0x34CFD0

.global hook_ConvertBombDropOne
hook_ConvertBombDropOne:
    push {r1-r12, lr}
    bl Item_ConvertBombDrop
    pop {r1-r12, lr}
    cpy r12,r0
    b 0x35E474

.global hook_ConvertBombDropTwo
hook_ConvertBombDropTwo:
    push {r1-r12, lr}
    cpy r0,r6
    bl Item_ConvertBombDrop
    pop {r1-r12, lr}
    cpy r6,r0
    b 0x3747B0

.global hook_BeanDaddyModifyBeansBought
hook_BeanDaddyModifyBeansBought:
    push {r1-r12, lr}
    bl EnMs_ModifyBeansBought
    pop {r1-r12, lr}
    cmp r0,#0xa
    bx lr

.global hook_BeanDaddyModifyPrice
hook_BeanDaddyModifyPrice:
    push {r0,r2-r12, lr}
    cpy r0,r1
    bl EnMs_ModifyPrice
    cpy r1,r0
    pop {r0,r2-r12, lr}
    cmp r0,r1
    bx lr

.global hook_CheckGerudoToken
hook_CheckGerudoToken:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    bx lr

.global hook_CowBottleCheck
hook_CowBottleCheck:
    push {r1-r12, lr}
    cpy r0,r4
    bl EnCow_BottleCheck
    pop {r1-r12, lr}
    bx lr

.global hook_CowItemOverride
hook_CowItemOverride:
    push {r0-r1, r3-r12, lr}
    bl EnCow_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x3EE37C

.global hook_AnjuCheckCuccoAmount
hook_AnjuCheckCuccoAmount:
    push {r1-r12, lr}
    bl EnNiwLady_CheckCuccoAmount
    pop {r1-r12, lr}
    cmp r0,#0x7
    cpylt r8,r0
    b 0x179424

.global hook_KingZoraCheckMovedFlag
hook_KingZoraCheckMovedFlag:
    push {r1-r12, lr}
    bl EnKz_CheckMovedFlag
    pop {r1-r12, lr}
    cmp r0,#0x0
    bx lr

.global hook_FrogReward
hook_FrogReward:
    push {r0-r12, lr}
    bl EnFr_rSetReward
    pop {r0-r12, lr}
    b 0x389930

.global hook_CanPlayBombchuBowling
hook_CanPlayBombchuBowling:
    push {r0-r12, lr}
    bl EnBomBowlMan_CheckExplosives
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SlidingDoorDestroyCustomModels
hook_SlidingDoorDestroyCustomModels:
    push {r0-r12, lr}
    cpy r0,r4
    bl Door_CheckToDeleteCustomModels
    pop {r0-r12, lr}
    mov r0,#0x0
    bx lr

.global hook_HandleDoorDestroyCustomModels
hook_HandleDoorDestroyCustomModels:
    push {r0-r12, lr}
    cpy r0,r4
    bl Door_CheckToDeleteCustomModels
    pop {r0-r12, lr}
    str r0,[r4,#0x3E4]
    bx lr

.global hook_TalonGetCastleTextbox
hook_TalonGetCastleTextbox:
    push {r0, r2-r12, lr}
    bl EnTa_GetCastleTextbox
    mov r1, r0
    pop {r0, r2-r12, lr}
    bx lr

.global hook_MidoCheckSpawn
hook_MidoCheckSpawn:
    push {r0-r12, lr}
    bl EnMd_ShouldSpawn
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_MidoForestDialog
hook_MidoForestDialog:
    push {r1-r12, lr}
    bl EnMd_GetTextKokiriForest
    pop {r1-r12, lr}
    bx lr

.global hook_CheckDekuTreeClear
hook_CheckDekuTreeClear:
    push {r0-r12, lr}
    bl Dungeon_CheckDekuTreeClear
    tst r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_CheckCurrentDungeonMode
hook_CheckCurrentDungeonMode:
    push {r0-r12, lr}
    bl Dungeon_GetCurrentDungeonMode
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_DungeonCheckJabuMQBox
hook_DungeonCheckJabuMQBox:
    push {r0-r12, lr}
    bl Dungeon_GetCurrentDungeonMode
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_JabuSwitchRutoCheck
hook_JabuSwitchRutoCheck:
    cmp r0,#0xA1
    bxeq lr
    cmp r0,#0x110
    bx lr

.global hook_JabuBoxCheckRuto
hook_JabuBoxCheckRuto:
    tst r0,#0x80
    push {r0-r12, lr}
    bleq ObjKibako_CheckRuto
    cmpeq r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_CanReadHints
hook_CanReadHints:
    push {r0-r12, lr}
    bl Hints_CanReadHints
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Cannot read hints, show this text
    # "What do you suppose this stone is?"
    movne r0,#0x100
    addne r0,r0,#0xB1
    bxne lr
    push {r0-r12, lr}
    bl Hints_GetHintsSetting
    cmp r0,#0x0
    pop {r0-r12, lr}
    # Vanilla hints, can read them (wearing mask)
    # "Responding to your mask..."
    moveq r0,#0x2000
    addeq r0,r0,#0x54
    bxeq lr
    # Randomizer hints enabled, can read them
    # Hint message, skipping other text
    ldrh r0,[r4,#0x1C]
    and r0,r0,#0xFF
    add r0,r0,#0x400
    # Register hint for Saria's Song
    push {r0-r12, lr}
    add r0,r0,#0x600
    bl Hints_AddSariasSongHint
    pop {r0-r12, lr}
    bx lr

.global hook_FastChests
hook_FastChests:
    push {r0-r12, lr}
    bl Chest_OverrideAnimation
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_DecoratedChest
hook_DecoratedChest:
    push {r0-r12, lr}
    bl Chest_OverrideDecoration
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_FastOwlCutscenes
hook_FastOwlCutscenes:
    push {r0-r12, lr}
    bl EnOwl_FastCutscene
    pop {r0-r12, lr}
    mov r1,#0xa
    bx lr

.global hook_SetChildCustomTunic
hook_SetChildCustomTunic:
    push {r0-r12, lr}
    bl Player_SetChildCustomTunicCMAB
    pop {r0-r12, lr}
    b 0x191E60

.global hook_ShortenRainbowBridgeCS
hook_ShortenRainbowBridgeCS:
    push {r0-r12, lr}
    bl ShortenRainbowBridgeCS
    pop {r0-r12, lr}
    cpy r4,r0
    bx lr

.global hook_Chest_OverrideIceSmoke
hook_Chest_OverrideIceSmoke:
    push {r0-r12, lr}
    mov r0,r4
    bl Chest_OverrideIceSmoke
    cmp r0,#0x0
    pop {r0-r12, lr}
    cpy r0,r6
    bne 0x1D5E64
    b 0x1D5E60

.global hook_EnableFW
hook_EnableFW:
    push {r0-r12, lr}
    bl EnableFW
    pop {r0-r12, lr}
    add sp,sp,#0x14
    bx lr

.global hook_FWUnset
hook_FWUnset:
    push {r0-r12, lr}
    bl MagicWind_Unset
    mov r0,#-0x1
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_FWGetSet
hook_FWGetSet:
    push {r0-r12, lr}
    bl MagicWind_CheckSet
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x351A64
    b 0x3519D0

.global hook_SetSavewarpEntrance
hook_SetSavewarpEntrance:
    push {r0-r12, lr}
    bl Entrance_SetSavewarpEntrance
    pop {r0-r12, lr}
    bx lr

.global hook_SetGameOverEntrance
hook_SetGameOverEntrance:
    push {r0-r12, lr}
    bl Entrance_SetGameOverEntrance
    pop {r0-r12, lr}
    bx lr

.global hook_SetGameOverRespawnFlag
hook_SetGameOverRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceGrottoReturn
    pop {r0-r12, lr}
    cmp r8,#0x3
    bx lr

.global hook_SetSunsSongRespawnFlag
hook_SetSunsSongRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceGrottoReturn
    pop {r0-r12, lr}
    cpy r0,r6
    bx lr

.global hook_SunsSongEndCloseTextbox
hook_SunsSongEndCloseTextbox:
    push {r0-r12, lr}
    bl Settings_SunsSongEndCloseTextbox
    pop {r0-r12, lr}
    b 0x45B518

.global hook_SetSpecialVoidOutRespawnFlag
hook_SetSpecialVoidOutRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceRegularVoidOut
    pop {r0-r12, lr}
    mov r1,#0x104
    bx lr

.global hook_NoHealFromHealthUpgrades
hook_NoHealFromHealthUpgrades:
    push {r1-r12, lr}
    bl NoHealFromHealthUpgrades
    pop {r1-r12, lr}
    bx lr

.global hook_NoHealFromBombchuBowlingPrize
hook_NoHealFromBombchuBowlingPrize:
    push {r1-r12, lr}
    bl NoHealFromBombchuBowlingPrize
    pop {r1-r12, lr}
    bx lr

.global hook_FairyPickupHealAmount
hook_FairyPickupHealAmount:
    push {r0-r12, lr}
    bl FairyPickupHealAmount
    pop {r0-r12, lr}
    bx lr

.global hook_FairyReviveHealAmount
hook_FairyReviveHealAmount:
    push {r1-r12, lr}
    bl FairyReviveHealAmount
    pop {r1-r12, lr}
    bx lr

.global hook_FairyUseHealAmount
hook_FairyUseHealAmount:
    push {r1-r12, lr}
    bl FairyUseHealAmount
    pop {r1-r12, lr}
    bx lr

.global hook_MedigoronCheckFlagOne
hook_MedigoronCheckFlagOne:
    push {r0-r12, lr}
    bl EnGm_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    blt 0x130254
    beq 0x13026C
    tst r12,r3
    b 0x130250

.global hook_MedigoronCheckFlagTwo
hook_MedigoronCheckFlagTwo:
    bne childLink
    push {r0-r12, lr}
    bl EnGm_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    blt 0x1302F8
    bne 0x1302C8
childLink:
    b 0x1302F0

.global hook_MedigoronSetRewardFlag
hook_MedigoronSetRewardFlag:
    mvn r0,#0xc7
    push {r0-r12, lr}
    bl EnGm_SetRewardFlag
    pop {r0-r12, lr}
    b 0x16C91C

.global hook_MedigoronItemOverrideOne
hook_MedigoronItemOverrideOne:
    push {r0-r1, r3-r12, lr}
    bl EnGm_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x14D960

.global hook_MedigoronItemOverrideTwo
hook_MedigoronItemOverrideTwo:
    push {r0-r1, r3-r12, lr}
    bl EnGm_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x16C9C0

.global hook_MedigoronGetCustomText
hook_MedigoronGetCustomText:
    push {r0-r12, lr}
    bl EnGm_UseCustomText
    cmp r0,#1
    pop {r0-r12, lr}
    moveq r2,#0x9100
    addeq r2,r2,#0x20
    movne r2,#0x3000
    addne r2,r2,#0x4F
    b 0x130260

.global hook_CarpetSalesmanCheckFlagOne
hook_CarpetSalesmanCheckFlagOne:
    push {r0-r12, lr}
    bl EnJs_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    cmpne r0,#0
    bx lr

.global hook_CarpetSalesmanCheckFlagTwo
hook_CarpetSalesmanCheckFlagTwo:
    push {r0-r12, lr}
    bl EnJs_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    addeq r1,r1,#1
    strh r1,[r0,r4]
    bx lr

.global hook_CarpetSalesmanSetFlag
hook_CarpetSalesmanSetFlag:
    push {r0-r12, lr}
    bl EnJs_SetRewardFlag
    pop {r0-r12, lr}
    mvn r0,#0xC7
    bx lr

.global hook_KakarikoGateCheck
hook_KakarikoGateCheck:
    push {r0-r12, lr}
    bl KakGate_CheckToFixBug
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_DoorOfTimeCheck
hook_DoorOfTimeCheck:
    cmp r0,#0x4
    bne 0x274B70
    push {r0-r12, lr}
    bl DoorOfTime_RequirementCheck
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_SongOfTimeJingle
hook_SongOfTimeJingle:
    mov r1,#0x0
    push {r0-r12, lr}
    bl DoorOfTime_RequirementCheck
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne r0,r0,#0x4
    bx lr

.global hook_GKSetDurability
hook_GKSetDurability:
    push {r0-r12, lr}
    bl GK_SetDurability
    strh r0,[r8,#0x4a]
    pop {r0-r12, lr}
    b 0x376BE0

.global hook_SkippableText
hook_SkippableText:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x2E0ED4
    ldr r0,[r5,#0x0]
    b 0x2E09C0

.global hook_InstantTextFirstLine
hook_InstantTextFirstLine:
    cmp r9,#0x0
    bgt NoInstantText
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    blt NoInstantText
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
NoInstantText:
    cmp r10,#0xFF
    bx lr

.global hook_InstantTextBoxBreak
hook_InstantTextBoxBreak:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    blt 0x2E0EE0
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
    b 0x2E0EE0

.global hook_InstantTextRemoveOff
hook_InstantTextRemoveOff:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    bge 0x2E0ED4
    ldr r0,[r5,#0x0]
    b 0x2E06CC

.global hook_TurboTextAdvance
hook_TurboTextAdvance:
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_ItemsMenuDraw
hook_ItemsMenuDraw:
    push {r0-r12, lr}
    bl ItemsMenu_Draw
    pop {r0-r12, lr}
    b 0x2F8160

.global hook_PlaySound
hook_PlaySound:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r3-r7, lr}
    b 0x35C52C

.global hook_SetBGMEntrance
hook_SetBGMEntrance:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x33104C

.global hook_SetBGMDayNight
hook_SetBGMDayNight:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x483C8C

.global hook_SetBGMEvent
hook_SetBGMEvent:
    push {r0, r2-r12, lr}
    cpy r0,r1
    bl SetBGM
    cpy r1,r0
    pop {r0, r2-r12, lr}
    push {r4-r11, lr}
    b 0x36EC44

.global hook_SetSFX
hook_SetSFX:
    push {r1-r12, lr}
    bl SetSFX
    pop {r1-r12, lr}
    push {r0-r11, lr}
    b 0x375480

.global hook_TurboTextClose
hook_TurboTextClose:
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_TurboTextSignalNPC
hook_TurboTextSignalNPC:
    movne r4,#0x1
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    movne r4,#0x1
    bx lr

.global hook_SkipSongReplays_TimeBlocksFix
hook_SkipSongReplays_TimeBlocksFix:
    bne 0x208008
    push  {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    moveq r1,#0x6E
    movne r1,#0x10
    cmp r0,r0
    b 0x208008

.global hook_SkipSongReplays_WarpBlocksFix
hook_SkipSongReplays_WarpBlocksFix:
    bne 0x20806C
    push  {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    moveq r1,#0x6E
    movne r1,#0x10
    cmp r0,r0
    b 0x20806C

.global hook_CarpenterBossSetTradedSawFlag
hook_CarpenterBossSetTradedSawFlag:
    push {r0-r12, lr}
    bl EnToryo_SetTradedSawFlag
    pop {r0-r12, lr}
    str r0,[r4,#0xB10]
    bx lr

.global hook_KingZoraSetTradedPrescriptionFlag
hook_KingZoraSetTradedPrescriptionFlag:
    push {r0-r12, lr}
    bl EnKz_SetTradedPrescriptionFlag
    pop {r0-r12, lr}
    mov r2,#0x24
    b 0x1C52A4

.global hook_SkipTimeTravelCutsceneOne
hook_SkipTimeTravelCutsceneOne:
    push {r0-r12, lr}
    bl TimeTravelAdvanceCutsceneTimer
    pop {r0-r12, lr}
    ldmia sp!,{r4,r5,r6,pc}

.global hook_SkipTimeTravelCutsceneTwo
hook_SkipTimeTravelCutsceneTwo:
    push {r0-r12, lr}
    bl SetTimeTraveled
    pop {r0-r12, lr}
    mov r1,#0x324
    bx lr

.global hook_SkipMasterSwordFanfare
hook_SkipMasterSwordFanfare:
    push {r0-r12, lr}
    bl ShouldSkipMasterSwordCutscene
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x3E5F7C
    mov r1,#0x0
    bx lr

.global hook_EnteredLocation
hook_EnteredLocation:
    cpy r4,r0
    push {r0-r12, lr}
    bl Entrance_EnteredLocation
    pop {r0-r12, lr}
    bx lr

.global hook_LostWoodsBridgeMusic
hook_LostWoodsBridgeMusic:
    push {r0-r12, lr}
    bl Entrance_IsLostWoodsBridge
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_LoadGame
hook_LoadGame:
    add r0, r4, r5
    push {r0-r12, lr}
    bl SaveFile_LoadExtSaveData
    pop {r0-r12, lr}
    b 0x447384

.global hook_SaveGame
hook_SaveGame:
    cmp r5, #0
    beq .notSaving
    push {r0-r12, lr}
    ldrb r0, [r5, #42]
    adds r0, #-0x30
    bl SaveFile_SaveExtSaveData
    pop {r0-r12, lr}
.notSaving:
    push {r4-r9, lr}
    b 0x2fbfac

.global hook_SaveMenuIgnoreOpen
hook_SaveMenuIgnoreOpen:
    push {r0-r12, lr}
    bl SaveMenu_IgnoreOpen
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x42F270
    bx lr

.global hook_OverrideFogDuringGameplayInit
hook_OverrideFogDuringGameplayInit:
    push {r0-r12, lr}
    bl Fog_OverrideState
    pop {r0-r12, lr}
    bx lr

.global hook_SkipTwinrovaQuarrelCutscene
hook_SkipTwinrovaQuarrelCutscene:
    mov r0,#0x500
    add r0,r0,#0x9
    bx lr

.global hook_FixItemsMenuSlotDuplication
hook_FixItemsMenuSlotDuplication:
    mov r4,#0xFF
    mov lr,#0xFF
    add r10,r10,#0x1
    b 0x456B94

.global hook_PlayEntranceCutscene
hook_PlayEntranceCutscene:
    bgt 0x44F0A4
    push {r0-r12, lr}
    ldrb r0,[r5,#0x3]
    bl EntranceCutscene_ShouldPlay
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x44F0A4
    b 0x44F06C

.global hook_SkipJabuOpeningCutscene
hook_SkipJabuOpeningCutscene:
    ldrh r0,[r0,#0x0]
    push {r0-r12, lr}
    bl Jabu_SkipOpeningCutscene
    pop {r0-r12, lr}
    bx lr

.global hook_MultiplyPlayerSpeed
hook_MultiplyPlayerSpeed:
    vldr.32 s0,[r6,#0x21C]
    push {r0-r12, lr}
    bl Player_GetSpeedMultiplier
    vmov s1,r0
    pop {r0-r12, lr}
    vmul.f32 s0,s1
    bx lr

.global hook_RunAnimationSpeed
hook_RunAnimationSpeed:
    vldr.32 s17,[r5,#0x21C]
    push {r0-r12, lr}
    bl Player_GetSpeedMultiplier
    vmov s1,r0
    pop {r0-r12, lr}
    vmul.f32 s17,s1
    bx lr

.global hook_SilenceNavi
hook_SilenceNavi:
    push {r0-r12, lr}
    bl IsNaviSilenced
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x26808C
    cmp r0,r2
    bx lr

.global hook_ChestMinigame_KeyChestVisibility
hook_ChestMinigame_KeyChestVisibility:
    push {r0-r12, lr}
    bl Settings_GetChestMinigameOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    orrne r10,r7,#0x0
    orreq r10,r7,#0x4000
    bx lr

.global hook_ChestMinigame_DontOpenChestsOnInit
hook_ChestMinigame_DontOpenChestsOnInit:
    cmp r0,#0x0
    bxeq lr
    push {r0-r12, lr}
    bl Settings_GetChestMinigameOption
    cmp r0,#0x1
    cmpgt r0,r0
    pop {r0-r12, lr}
    bx lr

.global hook_GameplayDestroy
hook_GameplayDestroy:
    cpy r4,r0
    push {r0-r12, lr}
    bl Entrance_CheckEpona
    pop {r0-r12, lr}
    bx lr

.global hook_SceneExitOverride
hook_SceneExitOverride:
    ldrsh r9, [r1,r0]
    push {r0-r8, r10-r12, lr}
    cpy r0, r9
    bl Entrance_OverrideNextIndex
    cpy r9, r0
    pop {r0-r8, r10-r12, lr}
    bx lr

.global hook_SceneExitDynamicOverride
hook_SceneExitDynamicOverride:
    push {r0-r12, lr}
    bl Entrance_OverrideDynamicExit
    pop {r0-r12, lr}
    bx lr

.global hook_OverrideGrottoActorEntrance
hook_OverrideGrottoActorEntrance:
    push {r0-r12, lr}
    cpy r0, r4
    bl Grotto_OverrideActorEntrance
    pop {r0-r12, lr}
    b 0x3F22C4

.global hook_ReturnFWSetupGrottoInfo
hook_ReturnFWSetupGrottoInfo:
    push {r0-r12, lr}
    bl Grotto_SetupReturnInfoOnFWReturn
    pop {r0-r12, lr}
    add sp,sp,#0x8
    bx lr

.global hook_ChildHoverBoots
hook_ChildHoverBoots:
    beq 0x2D5F04
    push {r0-r12, lr}
    bl Player_ShouldDrawHoverBootsEffect
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x2D5F04
    b 0x2D5DFC

.global hook_ArrowsOrSeeds
hook_ArrowsOrSeeds:
    push {r0-r12, lr}
    bl Player_ShouldUseSlingshot
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_HookshotDrawRedLaser
hook_HookshotDrawRedLaser:
    push {r0-r12, lr}
    bl Player_ShouldDrawHookshotParts
    cmp r0,#0x0
    pop {r0-r12, lr}
    bxeq lr
    b 0x4C55C0

.global hook_HookshotDrawChain
hook_HookshotDrawChain:
    push {r0-r12, lr}
    bl Player_ShouldDrawHookshotParts
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x2202BC
    ldr r0,[r4,#0x290]
    b 0x2202A4

.global hook_HookshotRotation
hook_HookshotRotation:
    push {r0-r12, lr}
    bl Hookshot_GetZRotation
    vmov.f32 s0,r0
    pop {r0-r12, lr}
    bx lr

.global hook_LinkReflection
hook_LinkReflection:
    push {r0-r12, lr}
    bl Player_ShouldDrawHookshotParts
    cmp r0,#0x1
    pop {r0-r12, lr}
    streq r1,[r0,#0x714]
    bx lr

.global hook_ChildCanOpenBowSubMenu
hook_ChildCanOpenBowSubMenu:
    push {r0-r12, lr}
    bl Settings_BowAsChild
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x2EB2DC
    cmp r12,#0x0
    b 0x2EB2DC

.global hook_BrownBoulderExplode
hook_BrownBoulderExplode:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r7
    bl ObjBombiwa_GetFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bne 0x26FA7C
    b 0x346D94

.global hook_RedBoulderExplode
hook_RedBoulderExplode:
    ldrb r0,[r5,#0x1B5]
    push {r0-r12, lr}
    cpy r0,r5
    bl ObjHamishi_HitCount
    cmp r0,#0x2
    pop {r0-r12, lr}
    bge 0x26FE9C
    b 0x26FE80

.global hook_Multiplayer_UpdatePrevActorFlags
hook_Multiplayer_UpdatePrevActorFlags:
    str r0,[r5,#0x1b8]
    push {r0-r12, lr}
    bl Multiplayer_Sync_UpdatePrevActorFlags
    pop {r0-r12, pc}

.global hook_Multiplayer_OnLoadFile
hook_Multiplayer_OnLoadFile:
    strh r6,[r0,#0x4C]
    push {r0-r12, lr}
    bl Multiplayer_OnFileLoad
    pop {r0-r12, lr}
    b 0x449F00

.global hook_SendDroppedBottleContents
hook_SendDroppedBottleContents:
    add r0,r0,#0x8C
    push {r0-r12, lr}
    cpy r0,r2
    vmov r1,s0
    vmov r2,s1
    vmov r3,s2
    bl SendDroppedBottleContents
    pop {r0-r12, lr}
    bx lr

.global hook_IgnoreMaskReaction
hook_IgnoreMaskReaction:
    ldrh r0,[r0,#0x0]
    push {r0-r12, lr}
    cpy r0,r4
    bl SaveFile_GetIgnoreMaskReactionOption
    cmp r0,#0x1
    pop {r0-r12, lr}
    moveq r0,#0x0
    b 0x36BBC8

.global hook_MasterQuestGoldSkulltulaCheck
hook_MasterQuestGoldSkulltulaCheck:
    push {r0-r5,r7-r12, lr}
    bl Settings_IsMasterQuestDungeon
    cpy r6,r0
    pop {r0-r5,r7-r12, lr}
    b 0x3415CC

.global hook_WaterSpoutMasterQuestCheck
hook_WaterSpoutMasterQuestCheck:
    push {r1-r12, lr}
    bl Settings_IsMasterQuestDungeon
    pop {r1-r12, lr}
    bx lr

.global hook_PierreSoftlockFixTwo
hook_PierreSoftlockFixTwo:
    cpy r6,r1
    push {r0-r12, lr}
    mov r2,#0x1
    mov r1,#0x0
    cpy r0,r6
    bl 0x36E980
    pop {r0-r12, lr}
    bx lr

.global hook_StoreTargetActorType
hook_StoreTargetActorType:
    push {r0-r12, lr}
    cpy r0,r6
    bl Fairy_StoreTargetActorType
    pop {r0-r12, lr}
    cmp r5,#0x0
    bx lr

.global hook_ForceTrailEffectUpdate
hook_ForceTrailEffectUpdate:
    push {r1-r12, lr}
    cpy r0,r4
    bl forceTrailEffectUpdate
    pop {r1-r12, lr}
    cmp r0,#0x10
    bx lr

.global hook_RainbowSwordTrail
hook_RainbowSwordTrail:
    push {r0-r12, lr}
    bl updateSwordTrailColors
    pop {r0-r12, lr}
    add r8,r7,#0x100
    bx lr

.global hook_BoomerangTrailEffect
hook_BoomerangTrailEffect:
    push {r0-r12, lr}
    bl updateBoomerangTrailEffect
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x1F4228
    strb r4,[r0,#0x282]
    bx lr

.global hook_RainbowChuTrail
hook_RainbowChuTrail:
    push {r0-r12, lr}
    bl updateChuTrailColors
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne pc,lr,#0x4
    strb r7,[r0,#0x282]
    bx lr

.global hook_TimerExpiration
hook_TimerExpiration:
    mov r0,#0x5
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    bxne lr
    add lr,lr,#0x30
    mov r0,#0x0
    strh r0,[r4,#0x62]
    bx lr

.global hook_WarpSongTimerDepletion
hook_WarpSongTimerDepletion:
    moveq r1,#0x1
    movne r1,#0xEF
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    bxne lr
    strh r1,[r0,#0x64]
    bx lr

.global hook_Timer2TickSound
hook_Timer2TickSound:
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    addeq lr,lr,#0x4
    cmp r0,#0x3C
    bx lr

.global hook_CurseTrapDizzyStick
hook_CurseTrapDizzyStick:
    push {r0-r12,lr}
    bl IceTrap_ReverseStick
    pop {r0-r12,lr}
    b 0x2FF258

.global hook_CurseTrapDizzyButtons
hook_CurseTrapDizzyButtons:
    push {r0,r3-r12,lr}
    # R1 and R2 contain button status fields
    # Apply the curse effect to both
    push {r2}
    cpy r0,r1
    bl IceTrap_RandomizeButtons
    pop {r2}
    push {r0}
    cpy r0,r2
    bl IceTrap_RandomizeButtons
    cpy r2,r0
    pop {r1}
    pop {r0,r3-r12,lr}
    stmia r0,{r1,r2,r3,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    b 0x41ABE0

.global hook_CrouchStabHitbox
hook_CrouchStabHitbox:
    push {r0-r12,lr}
    bl IceTrap_IsSlashHitboxDisabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    movne r10,#0xFF
    strb r10,[r6,#0x227]
    bx lr

.global hook_BossChallenge_Enter
hook_BossChallenge_Enter:
    push {r0-r12,lr}
    bl BossChallenge_Enter
    pop {r0-r12,lr}
    cpy r4,r0
    bx lr

.global hook_BossChallenge_ExitMenu
hook_BossChallenge_ExitMenu:
    push {r0-r12,lr}
    cpy r0,r8
    bl BossChallenge_ExitMenu
    pop {r0-r12,lr}
    cmp r8,#0x0
    bx lr

.global hook_RestoreISG
hook_RestoreISG:
    push {lr}
    push {r0-r12}
    bl Settings_IsIsgEnabled
    cmp r0,#0x0
    pop {r0-r12}
    bleq 0x34BBFC @Function that cancels ISG
    pop {lr}
    bx lr

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
