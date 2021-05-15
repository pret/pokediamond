#ifndef POKEDIAMOND_SCRCMD_H
#define POKEDIAMOND_SCRCMD_H

#include "global.h"
#include "script.h"

extern u16 VarGet(struct UnkSavStruct80* arg, u16);
extern u16* GetVarPointer(struct UnkSavStruct80* arg, u16);
extern struct SaveBlock2* ScriptEnvironment_GetSav2Ptr(struct UnkSavStruct80* unk);

struct UnkStruct_0203A288 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 padding[1];
};

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
BOOL ScrCmd_Unk026D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk02C0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk020C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk002F(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonAB(struct ScriptContext* ctx);
BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx);
BOOL ScrCmd_WaitButton(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0032(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0033(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0034(struct ScriptContext* ctx);
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
BOOL ScrCmd_ShowSaveClock(struct ScriptContext *ctx);
BOOL ScrCmd_HideSaveClock(struct ScriptContext *ctx);
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

//scrcmd_4.c
BOOL ScrCmd_GetPlayerName(struct ScriptContext* ctx);
BOOL ScrCmd_GetRivalName(struct ScriptContext* ctx);
BOOL ScrCmd_GetFriendName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D0(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemName(struct ScriptContext* ctx);
BOOL ScrCmd_GetPocketName(struct ScriptContext* ctx);
BOOL ScrCmd_GetTMHMMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_GetMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D5(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0280(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D6(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0251(struct ScriptContext* ctx);
BOOL ScrCmd_GetPoketchAppName(struct ScriptContext* ctx);
BOOL ScrCmd_GetTrainerClassName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00D9(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00DA(struct ScriptContext* ctx);
struct String* FUN_02040AE4(u32 msg_no, u32 heap_id);
BOOL ScrCmd_Unk00DB(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00DC(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00DD(struct ScriptContext* ctx);
BOOL ScrCmd_GetDecorationName(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundTrapName(struct ScriptContext* ctx);
BOOL ScrCmd_GetUndergroundItemName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk00E2(struct ScriptContext* ctx);
BOOL ScrCmd_Unk017B(struct ScriptContext* ctx);
BOOL ScrCmd_GetNatureName(struct ScriptContext* ctx);
BOOL ScrCmd_GetFashionName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0272(struct ScriptContext* ctx);
BOOL ScrCmd_GetPokemonMoveName(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0232(struct ScriptContext* ctx);
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
BOOL ScrCmd_Unk0050(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0051(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0052(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0053(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0054(struct ScriptContext *ctx);
BOOL FUN_02041464(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0055(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0056(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0058(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0049(struct ScriptContext* ctx);
BOOL ScrCmd_Unk004A(struct ScriptContext* ctx);
BOOL ScrCmd_Unk004B(struct ScriptContext* ctx);
BOOL FUN_02041540(struct ScriptContext* ctx);
BOOL ScrCmd_Unk004C(struct ScriptContext* ctx);
BOOL ScrCmd_PlayCryWait(struct ScriptContext* ctx);
BOOL FUN_02041598(struct ScriptContext* ctx);
BOOL ScrCmd_Unk004F(struct ScriptContext* ctx);
BOOL FUN_020415CC(struct ScriptContext* ctx);
BOOL ScrCmd_PlayBgm(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0059(struct ScriptContext* ctx);
BOOL ScrCmd_Unk005A(struct ScriptContext* ctx);
BOOL ScrCmd_Unk005B(struct ScriptContext* ctx);
BOOL ScrCmd_Unk005C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk005D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0283(struct ScriptContext *ctx);

//scrcmd_8.c
BOOL ScrCmd_Unk021D(struct ScriptContext* ctx);

//scrcmd_11.c
BOOL ScrCmd_Unk017D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk017E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk017F(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0180(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0181(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0182(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0183(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0184(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0185(struct ScriptContext* ctx);

//scrcmd_13.c
BOOL ScrCmd_Unk0253(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0254(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0255(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0256(struct ScriptContext* ctx);

//scrcmd_coins.c
BOOL ScrCmd_Unk0075(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0076(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0077(struct ScriptContext* ctx);
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
BOOL ScrCmd_Unk0072(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0073(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0074(struct ScriptContext* ctx);

//scrcmd_daycare.c
BOOL ScrCmd_Unk016D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk016E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A8(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A9(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A4(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AA(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AE(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01B0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BC(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BE(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01BF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A5(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A6(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01A7(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01AD(struct ScriptContext* ctx);

//scrcmd_18.c
BOOL ScrCmd_GiveMon(struct ScriptContext* ctx);

//scrcmd_19.c
BOOL ScrCmd_Unk01F1(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F4(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F5(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F2(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01F3(struct ScriptContext* ctx);

//scrcmd_20.c
BOOL ScrCmd_Unk02A6(struct ScriptContext* ctx);

//scrcmd_flags.c
BOOL ScrCmd_HasSinnohDex(struct ScriptContext* ctx);
BOOL ScrCmd_GiveSinnohDex(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0159(struct ScriptContext* ctx);
BOOL ScrCmd_Unk015A(struct ScriptContext* ctx);
BOOL ScrCmd_HasBadge(struct ScriptContext* ctx);
BOOL ScrCmd_GiveBadge(struct ScriptContext* ctx);
BOOL ScrCmd_Unk015E(struct ScriptContext* ctx);
BOOL ScrCmd_GetTotalEarnedBadges(struct ScriptContext* ctx);
BOOL ScrCmd_Unk015F(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0160(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0161(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0162(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0163(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0164(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0165(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0166(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0167(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01CF(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01D0(struct ScriptContext* ctx);
BOOL ScrCmd_Unk01D1(struct ScriptContext* ctx);

//scrcmd_items.c
BOOL ScrCmd_GiveItem(struct ScriptContext* ctx);
BOOL ScrCmd_TakeItem(struct ScriptContext* ctx);
BOOL ScrCmd_HasSpaceForItem(struct ScriptContext* ctx);
BOOL ScrCmd_HasItem(struct ScriptContext* ctx);
BOOL ScrCmd_ItemIdIsTMOrHM(struct ScriptContext* ctx);
BOOL ScrCmd_GetItemPocketId(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0081(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0082(struct ScriptContext* ctx);

//scrcmd_23.c
BOOL ScrCmd_Unk0083(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0084(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0085(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0086(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0087(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0088(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0089(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008A(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008B(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008C(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008D(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008E(struct ScriptContext* ctx);
BOOL ScrCmd_Unk008F(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0090(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0091(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0092(struct ScriptContext* ctx);

//scrcmd_25.c
BOOL ScrCmd_Unk023F(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0240(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0241(struct ScriptContext* ctx);
BOOL ScrCmd_Unk0242(struct ScriptContext* ctx);

#endif //POKEDIAMOND_SCRCMD_H
