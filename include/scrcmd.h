#ifndef POKEDIAMOND_SCRCMD_H
#define POKEDIAMOND_SCRCMD_H

#include "global.h"
#include "script.h"

extern u16 VarGet(struct FieldSystem *fieldSystem, u16);
extern u16* GetVarPointer(struct FieldSystem *fieldSystem, u16);
extern struct SaveBlock2* ScriptEnvironment_GetSavePtr(struct FieldSystem *fieldSystem);

static inline u16 ScriptGetVar(struct ScriptContext* ctx)
{
    return VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
}

static inline u16 *ScriptGetVarPointer(struct ScriptContext* ctx)
{
    return GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
}

struct UnkStruct_0203A288 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 padding[1];
};

typedef struct UnkStruct_0203B174
{
    BOOL Unk00;
    u32 Unk04;
    void *Unk08;
    struct FieldSystem *fieldSystem;
} UnkStruct_0203B174;

//scrcmd.c
BOOL ScrCmd_Nop(struct ScriptContext* ctx);
BOOL ScrCmd_Dummy(struct ScriptContext* ctx);
BOOL ScrCmd_End(struct ScriptContext* ctx);
BOOL ScrCmd_Wait(struct ScriptContext* ctx);
BOOL ScrCmd_DebugWatch(struct ScriptContext* ctx);
BOOL ScrCmd_LoadByte(struct ScriptContext* ctx);
BOOL ScrCmd_LoadWord(struct ScriptContext* ctx);
BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext* ctx);
BOOL ScrCmd_WriteByteToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_SetPtrByte(struct ScriptContext* ctx);
BOOL ScrCmd_CopyLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CopyByte(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext* ctx);
BOOL ScrCmd_CompareVarToValue(struct ScriptContext* ctx);
BOOL ScrCmd_CompareVarToVar(struct ScriptContext* ctx);
BOOL ScrCmd_RunScript(struct ScriptContext* ctx);
BOOL ScrCmd_RunScriptWait(struct ScriptContext* ctx);
BOOL ScrCmd_RestartCurrentScript(struct ScriptContext* ctx);
BOOL ScrCmd_GoTo(struct ScriptContext* ctx);
BOOL ScrCmd_ObjectGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_BgGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_DirectionGoTo(struct ScriptContext* ctx);
BOOL ScrCmd_Call(struct ScriptContext* ctx);
BOOL ScrCmd_Return(struct ScriptContext* ctx);
BOOL ScrCmd_GoToIf(struct ScriptContext* ctx);
BOOL ScrCmd_CallIf(struct ScriptContext* ctx);
BOOL ScrCmd_SetFlag(struct ScriptContext* ctx);
BOOL ScrCmd_ClearFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckFlagVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetFlagVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext* ctx);
BOOL ScrCmd_AddVar(struct ScriptContext* ctx);
BOOL ScrCmd_SubVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetVar(struct ScriptContext* ctx);
BOOL ScrCmd_CopyVar(struct ScriptContext* ctx);
BOOL ScrCmd_SetOrCopyVar(struct ScriptContext* ctx);
BOOL ScrCmd_Message(struct ScriptContext* ctx);
BOOL ScrCmd_MessageFrom(struct ScriptContext* ctx);
BOOL ScrCmd_MessageFrom2(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FC(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FD(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FE(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01FF(struct ScriptContext* ctx);
BOOL ScrCmd_MessageUnown(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02C0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk020C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002F(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonAB(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx);
BOOL ScrCmd_WaitButton(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonABPad(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0033(struct ScriptContext *ctx);
BOOL ScrCmd_CloseMessageBox(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0035(struct ScriptContext* ctx);
BOOL ScrCmd_ScrollBg(struct ScriptContext* ctx);
BOOL ScrCmd_CreateMessageBox(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0037(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0038(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0039(struct ScriptContext* ctx);
BOOL ScrCmd_Unk003A(struct ScriptContext* ctx);
BOOL ScrCmd_Unk003B(struct ScriptContext *ctx);
BOOL ScrCmd_Menu(struct ScriptContext *ctx);
BOOL ScrCmd_YesNoMenu(struct ScriptContext *ctx);
BOOL ScrCmd_ShowWaitingIcon(struct ScriptContext *ctx);
BOOL ScrCmd_HideWaitingIcon(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0040(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0041(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0042(struct ScriptContext *ctx);
BOOL ScrCmd_Unk029D(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0043(struct ScriptContext *ctx);
BOOL ScrCmd_Unk02B9(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0044(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0045(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0046(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0047(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0048(struct ScriptContext *ctx);
BOOL ScrCmd_Unk02CF(struct ScriptContext *ctx);
BOOL ScrCmd_Unk02D0(struct ScriptContext *ctx);
BOOL ScrCmd_Unk005E(struct ScriptContext *ctx);
BOOL ScrCmd_Unk02A1(struct ScriptContext *ctx);
BOOL ScrCmd_WaitForMovement(struct ScriptContext *ctx);
BOOL ScrCmd_LockAllEvents(struct ScriptContext *ctx);
BOOL ScrCmd_LockAllEvents2(struct ScriptContext *ctx);
BOOL ScrCmd_ReleaseAllEvents(struct ScriptContext *ctx);
BOOL ScrCmd_LockEvent(struct ScriptContext *ctx);
BOOL ScrCmd_ReleaseEvent(struct ScriptContext *ctx);
BOOL ScrCmd_AddOverworldEvent(struct ScriptContext *ctx);
BOOL ScrCmd_RemoveOverworldEvent(struct ScriptContext *ctx);
BOOL ScrCmd_LockCamera(struct ScriptContext *ctx);
BOOL ScrCmd_ReleaseCamera(struct ScriptContext *ctx);
BOOL ScrCmd_FacePlayer(struct ScriptContext *ctx);
BOOL ScrCmd_GetPlayerPosition(struct ScriptContext *ctx);
BOOL ScrCmd_GetOverworldEventPosition(struct ScriptContext *ctx);
BOOL ScrCmd_GetPlayerDirection(struct ScriptContext *ctx);
BOOL ScrCmd_Unk006B(struct ScriptContext *ctx);
BOOL ScrCmd_KeepOverworldEvent(struct ScriptContext *ctx);
BOOL ScrCmd_SetOverworldEventMovement(struct ScriptContext *ctx);
BOOL ScrCmd_GetOverworldEventMovement(struct ScriptContext *ctx);
BOOL ScrCmd_OverworldEventStopFollowing(struct ScriptContext *ctx);
BOOL ScrCmd_Unk02AB(struct ScriptContext *ctx);
BOOL ScrCmd_GetSealCountFromId(struct ScriptContext *ctx);
BOOL ScrCmd_GiveSeals(struct ScriptContext *ctx);
BOOL ScrCmd_GetPokemonForme(struct ScriptContext *ctx);
BOOL ScrCmd_ChoosePokemonMenu(struct ScriptContext *ctx);
BOOL ScrCmd_OpenTradeScreen(struct ScriptContext *ctx);
BOOL ScrCmd_UnionChoosePokemonMenu(struct ScriptContext *ctx);
BOOL ScrCmd_GetSelectedPartySlot(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0194(ScriptContext *ctx);
BOOL ScrCmd_Unk0195(ScriptContext *ctx);
BOOL ScrCmd_Unk0196(ScriptContext *ctx);
BOOL ScrCmd_Unk0197(ScriptContext *ctx);
BOOL ScrCmd_Unk009B(ScriptContext *ctx);
BOOL ScrCmd_DummySetWeather(ScriptContext *ctx);
BOOL ScrCmd_DummyInitWeather(ScriptContext *ctx);
BOOL ScrCmd_DummyUpdateWeather(ScriptContext *ctx);
BOOL ScrCmd_DummyGetMapPosition(ScriptContext *ctx);
BOOL ScrCmd_RestoreOverworld(ScriptContext *ctx);
BOOL ScrCmd_TerminateOverworldProcess(ScriptContext *ctx);
BOOL ScrCmd_Unk00A2(ScriptContext *ctx);
BOOL ScrCmd_Unk00A3(ScriptContext *ctx);
BOOL ScrCmd_GetDressupPortraitSlot(ScriptContext *ctx);
BOOL ScrCmd_Unk0207(ScriptContext *ctx);
BOOL ScrCmd_ShowPokemonPic(ScriptContext *ctx);
BOOL ScrCmd_ShowPartyPokemonPic(ScriptContext *ctx);
BOOL ScrCmd_Unk0209(ScriptContext *ctx);
BOOL ScrCmd_Unk028D(ScriptContext *ctx);
BOOL ScrCmd_Unk028E(ScriptContext *ctx);
BOOL ScrCmd_Unk020A(ScriptContext *ctx);
BOOL ScrCmd_Unk020B(ScriptContext *ctx);
BOOL ScrCmd_Unk00A5(ScriptContext *ctx);
BOOL ScrCmd_DressupPokemon(ScriptContext *ctx);
BOOL ScrCmd_ShowDressedPokemon(ScriptContext *ctx);
BOOL ScrCmd_ShowContestPokemon(ScriptContext *ctx);
BOOL ScrCmd_CheckPortraitSlot(ScriptContext *ctx);
BOOL ScrCmd_CheckContestPortraitSlot(ScriptContext *ctx);
BOOL ScrCmd_Unk0130(ScriptContext *ctx);
BOOL ScrCmd_ShowGeonetScreen(ScriptContext *ctx);
BOOL ScrCmd_ShowSealCapsuleEditor(ScriptContext *ctx);
BOOL ScrCmd_ShowTownMapScreen(ScriptContext *ctx);
BOOL ScrCmd_Unk01D7(ScriptContext *ctx);
BOOL ScrCmd_Unk01D8(ScriptContext *ctx);
BOOL ScrCmd_Unk01D9(ScriptContext *ctx);
BOOL ScrCmd_ShowPCBoxScreen(ScriptContext *ctx);
BOOL ScrCmd_Unk00AC(ScriptContext *ctx);
BOOL ScrCmd_Unk00AD(ScriptContext *ctx);
BOOL ScrCmd_Unk00AE(ScriptContext *ctx);
BOOL ScrCmd_Unk00AF(ScriptContext *ctx);
BOOL ScrCmd_ShowEndGameScreen(ScriptContext *ctx);
BOOL ScrCmd_InitHallOfFame(ScriptContext *ctx);
BOOL ScrCmd_Unk00B2(ScriptContext *ctx);
BOOL ScrCmd_Unk00B3(ScriptContext *ctx);
BOOL ScrCmd_StarterSelectionScreen(ScriptContext *ctx);
BOOL ScrCmd_EndStarterSelectionScreen(ScriptContext *ctx);
BOOL ScrCmd_ShowBagScreen(ScriptContext *ctx);
BOOL ScrCmd_GetBagScreenSelection(ScriptContext *ctx);
BOOL ScrCmd_NamePlayerScreen(ScriptContext *ctx);
BOOL ScrCmd_NamePokemonScreen(ScriptContext *ctx);
BOOL ScrCmd_WriteWhiteRockInscription(ScriptContext *ctx);
BOOL ScrCmd_Unk0243(ScriptContext *ctx);
BOOL ScrCmd_Unk0244(ScriptContext *ctx);
BOOL ScrCmd_Unk0245(ScriptContext *ctx);
BOOL ScrCmd_FadeScreen(ScriptContext *ctx);
BOOL ScrCmd_WaitFadeScreen(ScriptContext *ctx);
BOOL ScrCmd_Warp(ScriptContext *ctx);
BOOL ScrCmd_BattleRoomWarp(ScriptContext *ctx);
BOOL ScrCmd_ExitBattleRoom(ScriptContext *ctx);

// scrcmd_mart.c
BOOL ScrCmd_NormalMart(struct ScriptContext * ctx);
BOOL ScrCmd_SpecialMart(struct ScriptContext * ctx);
BOOL ScrCmd_GoodsMart(struct ScriptContext * ctx);
BOOL ScrCmd_SealsMart(struct ScriptContext * ctx);
BOOL ScrCmd_AccessoriesShop(struct ScriptContext * ctx);

//scrcmd_4.c
BOOL ScrCmd_GetPlayerName(struct ScriptContext* ctx);
BOOL ScrCmd_GetRivalName(struct ScriptContext* ctx);
BOOL ScrCmd_GetFriendName(struct ScriptContext* ctx);
BOOL ScrCmd_GetPokemonName(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemName(struct ScriptContext* ctx);
BOOL ScrCmd_GetPocketName(struct ScriptContext* ctx);
BOOL ScrCmd_GetTMHMMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_GetMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D5(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0280(struct ScriptContext* ctx);
BOOL ScrCmd_GetPokemonNickname(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0251(struct ScriptContext* ctx);
BOOL ScrCmd_GetPoketchAppName(struct ScriptContext* ctx);
BOOL ScrCmd_GetTrainerClassName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D9(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00DA(struct ScriptContext* ctx);
struct String* FUN_02040AE4(u32 msg_no, u32 heap_id);
BOOL ScrCmd_GetPlayerStarterName(struct ScriptContext* ctx);
BOOL ScrCmd_GetRivalStarterName(struct ScriptContext* ctx);
BOOL ScrCmd_GetCounterpartStarterName(struct ScriptContext* ctx);
BOOL ScrCmd_GetDecorationName(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundTrapName(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundItemName(struct ScriptContext* ctx);
BOOL ScrCmd_GetMapName(struct ScriptContext* ctx);
BOOL ScrCmd_GetBerryName(struct ScriptContext* ctx);
BOOL ScrCmd_GetNatureName(struct ScriptContext* ctx);
BOOL ScrCmd_GetFashionName(struct ScriptContext* ctx);
BOOL ScrCmd_GetWhiteRockInscription(struct ScriptContext* ctx);
BOOL ScrCmd_GetPokemonMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_GetRibbonName(struct ScriptContext* ctx);
BOOL ScrCmd_GetSealName(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemNameWithIndefArticle(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemNamePlural(struct ScriptContext* ctx);
BOOL ScrCmd_GetDecorationNameWithArticle(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundTrapNameWithArticle(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundItemNameWithArticle(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02C9(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02CA(struct ScriptContext* ctx);
BOOL ScrCmd_GetFashionNameWithArticle(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02CC(struct ScriptContext* ctx);
BOOL ScrCmd_GetSealNamePlural(struct ScriptContext* ctx);
BOOL ScrCmd_CapitalizeFirstChar(struct ScriptContext* ctx);

//scrcmd_sound.c
BOOL ScrCmd_Unk02AE(struct ScriptContext *ctx);
BOOL ScrCmd_PlayBgm(struct ScriptContext *ctx);
BOOL ScrCmd_StopBgm(struct ScriptContext *ctx);
BOOL ScrCmd_PlayDefaultBgm(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0053(struct ScriptContext *ctx);
BOOL ScrCmd_FadeOutBgm(struct ScriptContext *ctx);
BOOL FUN_02041464(struct ScriptContext *ctx);
BOOL ScrCmd_FadeInBgm(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0056(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0057(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0058(struct ScriptContext* ctx);
BOOL ScrCmd_PlayFanfare(struct ScriptContext* ctx);
BOOL ScrCmd_StopFanfare(struct ScriptContext* ctx);
BOOL ScrCmd_PlayFanfareWait(struct ScriptContext* ctx);
BOOL FUN_02041540(struct ScriptContext* ctx);
BOOL ScrCmd_PlayCry(struct ScriptContext* ctx);
BOOL ScrCmd_PlayCryWait(struct ScriptContext* ctx);
BOOL FUN_02041598(struct ScriptContext* ctx);
BOOL ScrCmd_PlaySoundWait(struct ScriptContext* ctx);
BOOL FUN_020415CC(struct ScriptContext* ctx);
BOOL ScrCmd_PlaySound(struct ScriptContext* ctx);
BOOL ScrCmd_CheckChatotCry(struct ScriptContext* ctx);
BOOL ScrCmd_StartChatotRecord(struct ScriptContext* ctx);
BOOL ScrCmd_StopChatotRecord(struct ScriptContext* ctx);
BOOL ScrCmd_SaveChatotCry(struct ScriptContext* ctx);
BOOL ScrCmd_Unk005D(struct ScriptContext* ctx);
BOOL ScrCmd_SetVolume(struct ScriptContext *ctx);

//scrcmd_union.c
BOOL ScrCmd_UnionGroup(struct ScriptContext* ctx);

//scrcmd_berry_trees.c
BOOL ScrCmd_GetBerryTreeGrowth(struct ScriptContext* ctx);
BOOL ScrCmd_GetBerryTreeType(struct ScriptContext* ctx);
BOOL ScrCmd_GetBerryTreeMulch(struct ScriptContext* ctx);
BOOL ScrCmd_GetBerryTreeWater(struct ScriptContext* ctx);
BOOL ScrCmd_GetBerryTreeAmount(struct ScriptContext* ctx);
BOOL ScrCmd_SetBerryTreeMulch(struct ScriptContext* ctx);
BOOL ScrCmd_SetBerryTreeType(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0184(struct ScriptContext* ctx);
BOOL ScrCmd_TakeBerryTreeBerries(struct ScriptContext* ctx);

//scrcmd_13.c
BOOL ScrCmd_Unk0253(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0254(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0255(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0256(struct ScriptContext* ctx);

//scrcmd_coins.c
BOOL ScrCmd_ShowCoinBox(struct ScriptContext* ctx);
BOOL ScrCmd_HideCoinBox(struct ScriptContext* ctx);
BOOL ScrCmd_UpdateCoinBox(struct ScriptContext* ctx);
BOOL ScrCmd_GetCoins(struct ScriptContext* ctx);
BOOL ScrCmd_GiveCoins(struct ScriptContext* ctx);
BOOL ScrCmd_TakeCoinsImmediate(struct ScriptContext* ctx);
BOOL ScrCmd_TakeCoinsAddress(struct ScriptContext* ctx);
BOOL ScrCmd_HasEnoughCoinsImmediate(struct ScriptContext* ctx);
BOOL ScrCmd_HasEnoughCoinsAddress(struct ScriptContext* ctx);
BOOL ScrCmd_CanGiveCoins(struct ScriptContext* ctx);

//scrcmd_money.c
BOOL ScrCmd_GiveMoney(struct ScriptContext* ctx);
BOOL ScrCmd_TakeMoneyImmediate(struct ScriptContext* ctx);
BOOL ScrCmd_TakeMoneyAddress(struct ScriptContext* ctx);
BOOL ScrCmd_HasEnoughMoneyImmediate(struct ScriptContext* ctx);
BOOL ScrCmd_HasEnoughMoneyAddress(struct ScriptContext* ctx);
BOOL ScrCmd_ShowMoneyBox(struct ScriptContext* ctx);
BOOL ScrCmd_HideMoneyBox(struct ScriptContext* ctx);
BOOL ScrCmd_UpdateMoneyBox(struct ScriptContext* ctx);

//scrcmd_daycare.c
BOOL ScrCmd_GetDaycarePokemonNames(struct ScriptContext* ctx);
BOOL ScrCmd_GetDaycareStatus(struct ScriptContext* ctx);
BOOL ScrCmd_DeleteDaycareEgg(struct ScriptContext* ctx);
BOOL ScrCmd_GiveDaycareEgg(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A4(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AA(struct ScriptContext* ctx);
BOOL ScrCmd_GetDaycareLevel(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01B0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BC(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BE(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A5(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A6(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A7(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AD(struct ScriptContext* ctx);

//scrcmd_amity_square.c
BOOL ScrCmd_ClearAmitySquareSteps(struct ScriptContext* ctx);
BOOL ScrCmd_CheckAmitySquareSteps(struct ScriptContext* ctx);
BOOL ScrCmd_GetAmitySquareAccessory(struct ScriptContext* ctx);

//scrcmd_party.c
BOOL ScrCmd_GiveMon(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonSpecies(struct ScriptContext* ctx);
BOOL ScrCmd_CheckPartyMonOTID(struct ScriptContext* ctx);
BOOL ScrCmd_GiveEgg(struct ScriptContext* ctx);
BOOL ScrCmd_SetPartyMonMove(struct ScriptContext* ctx);
BOOL ScrCmd_PartyMonHasMove(struct ScriptContext* ctx);
BOOL ScrCmd_FindPartyMonWithMove(struct ScriptContext* ctx);
BOOL ScrCmd_SurvivePsn(struct ScriptContext* ctx);
BOOL ScrCmd_CountPartyMonsAtOrBelowLevel(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonLevel(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonNature(struct ScriptContext* ctx);
BOOL ScrCmd_FindPartyMonWithNature(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonFriendship(struct ScriptContext* ctx);
BOOL ScrCmd_AddPartyMonFriendship(struct ScriptContext* ctx);
BOOL ScrCmd_SubtractPartyMonFriendship(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonContestCondition(struct ScriptContext* ctx);
BOOL ScrCmd_GetLeadingPartyMonSlot(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonTypes(struct ScriptContext* ctx);
BOOL ScrCmd_CountPartyMons(struct ScriptContext* ctx);
BOOL ScrCmd_CountPartyMons_OmitEggs(struct ScriptContext* ctx);
BOOL ScrCmd_CountAvailablePartyMons_IgnoreSlot(struct ScriptContext* ctx);
BOOL ScrCmd_CountAvailablePartyAndPCMons(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyEggCount(struct ScriptContext* ctx);
BOOL ScrCmd_CheckPartyForPokerus(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonGender(struct ScriptContext* ctx);
BOOL ScrCmd_CountPartyMonMoves(struct ScriptContext* ctx);
BOOL ScrCmd_ForgetPartyMonMove(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonMove(struct ScriptContext* ctx);
BOOL ScrCmd_GetPartyMonHeldItem(struct ScriptContext* ctx);
BOOL ScrCmd_ResetPartyMonHeldItem(struct ScriptContext* ctx);
BOOL ScrCmd_CheckPartyForSpecies(struct ScriptContext* ctx);
BOOL ScrCmd_CountPartyMonRibbons(struct ScriptContext* ctx);
BOOL ScrCmd_CountTotalPartyRibbons(struct ScriptContext* ctx);
BOOL ScrCmd_PartyMonHasRibbon(struct ScriptContext* ctx);
BOOL ScrCmd_GivePartyMonRibbon(struct ScriptContext* ctx);
BOOL ScrCmd_CheckPartyForBadEgg(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00A0(struct ScriptContext* ctx);

//scrcmd_fossils.c
BOOL ScrCmd_CountFossils(struct ScriptContext* ctx);
BOOL ScrCmd_GetFossilPokemon(struct ScriptContext* ctx);
BOOL ScrCmd_GetFossilMinimumAmount(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F2(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F3(struct ScriptContext* ctx);

//scrcmd_prizes.c
BOOL ScrCmd_GetPrizeItemIdAndCost(struct ScriptContext* ctx);

//scrcmd_flags.c
BOOL ScrCmd_HasSinnohDex(struct ScriptContext* ctx);
BOOL ScrCmd_GiveSinnohDex(struct ScriptContext* ctx);
BOOL ScrCmd_HasRunningShoes(struct ScriptContext* ctx);
BOOL ScrCmd_GiveRunningShoes(struct ScriptContext* ctx);
BOOL ScrCmd_HasBadge(struct ScriptContext* ctx);
BOOL ScrCmd_GiveBadge(struct ScriptContext* ctx);
BOOL ScrCmd_HasBag(struct ScriptContext* ctx);
BOOL ScrCmd_GetTotalEarnedBadges(struct ScriptContext* ctx);
BOOL ScrCmd_GiveBag(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0160(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0161(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0162(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0163(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0164(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0165(struct ScriptContext* ctx);
BOOL ScrCmd_CheckGameCompleted(struct ScriptContext* ctx);
BOOL ScrCmd_SetGameCompleted(struct ScriptContext* ctx);
BOOL ScrCmd_GetSetStrength(struct ScriptContext* ctx);
BOOL ScrCmd_GetSetFlash(struct ScriptContext* ctx);
BOOL ScrCmd_GetSetDefog(struct ScriptContext* ctx);

//scrcmd_items.c
BOOL ScrCmd_GiveItem(struct ScriptContext* ctx);
BOOL ScrCmd_TakeItem(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForItem(struct ScriptContext* ctx);
BOOL ScrCmd_HasItem(struct ScriptContext* ctx);
BOOL ScrCmd_ItemIdIsTMOrHM(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemPocketId(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0081(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0082(struct ScriptContext* ctx);

//scrcmd_underground.c
BOOL ScrCmd_GiveSecretBaseDecoration(struct ScriptContext* ctx);
BOOL ScrCmd_TakeSecretBaseDecoration(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForDecoration(struct ScriptContext* ctx);
BOOL ScrCmd_GetDecorationCount(struct ScriptContext* ctx);
BOOL ScrCmd_GiveUndergroundTrap(struct ScriptContext* ctx);
BOOL ScrCmd_TakeUndergroundTrap(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForTrap(struct ScriptContext* ctx);
BOOL ScrCmd_GetTrapCount(struct ScriptContext* ctx);
BOOL ScrCmd_GiveTreasure(struct ScriptContext* ctx);
BOOL ScrCmd_TakeTreasure(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForTreasure(struct ScriptContext* ctx);
BOOL ScrCmd_GetTreasureCount(struct ScriptContext* ctx);
BOOL ScrCmd_GiveUndergroundSphere(struct ScriptContext* ctx);
BOOL ScrCmd_TakeUndergroundSphere(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForSphere(struct ScriptContext* ctx);
BOOL ScrCmd_GetSphereCount(struct ScriptContext* ctx);

//scrcmd_move_relearner.c
BOOL ScrCmd_Unk01C6(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01C7(struct ScriptContext* ctx);
BOOL ScrCmd_Unk021E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk021F(struct ScriptContext* ctx);
void FUN_02045E74(struct ScriptContext* ctx, u8 a1, struct Pokemon* pokemon, u16 *eligibleMoves);
BOOL ScrCmd_Unk0220(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0221(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0224(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0222(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0223(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0225(struct ScriptContext* ctx);

//scrcmd_25.c
BOOL ScrCmd_Unk023F(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0240(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0241(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0242(struct ScriptContext* ctx);

#endif //POKEDIAMOND_SCRCMD_H
