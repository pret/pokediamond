#ifndef POKEDIAMOND_SCRIPT_BUFFERS_H
#define POKEDIAMOND_SCRIPT_BUFFERS_H

#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "trainer_data.h"

struct UnkStruct_0200AA80_sub_sub
{
    u8 data[4];
};

struct UnkStruct_0200AA80_sub
{
    struct UnkStruct_0200AA80_sub_sub attrs;
    struct String * msg;
};

struct ScrStrBufs
{
    u32 count;
    u32 heap_id;
    struct UnkStruct_0200AA80_sub * array;
    struct String * tmpbuf;
};

struct Trainer
{
    u8 unk0;
    u8 unk1;
};

struct UnkStruct_0200B870_sub
{
    u8 filler_00[16];
    u32 unk_10;
    u8 * unk_14;
};

struct UnkStruct_0200B870
{
    void * unk_0;
    struct UnkStruct_0200B870_sub * unk_4;
    u16 data[16];
    u32 unk_28;
};

struct ScrStrBufs * ScrStrBufs_new(u32 heap_id);
struct ScrStrBufs * ScrStrBufs_new_custom(u32 nstr, u32 strlen, u32 heap_id);
void ScrStrBufs_delete(struct ScrStrBufs * ptr);
void ScrStrBufs_InitSub(struct UnkStruct_0200AA80_sub * sub);
void SetStringAsPlaceholder(struct ScrStrBufs * mgr, u32 idx, struct String * str, struct UnkStruct_0200AA80_sub_sub * a3);
void BufferString(struct ScrStrBufs * mgr, u32 idx, struct String * str, u32 a3, u32 a4, u32 a5);
void BufferPlayersName(struct ScrStrBufs * mgr, u32 idx, struct PlayerData * data);
void BufferRivalsName(struct ScrStrBufs * mgr, u32 idx, struct SaveBlock2 * sav2);
void BufferFriendsName(struct ScrStrBufs * mgr, u32 idx, struct SaveBlock2 * sav2);
void BufferBoxMonSpeciesName(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon);
void BufferBoxMonSpeciesNameWithArticle(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon);
void BufferSpeciesNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 species);
void BufferBoxMonNickname(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon);
void BufferBoxMonOTName(struct ScrStrBufs * mgr, u32 idx, struct BoxPokemon * mon);
void BufferIntegerAsString(struct ScrStrBufs * mgr, u32 idx, int num, u32 ndigits, int strConvMode, BOOL whichCharset);
void BufferMoveName(struct ScrStrBufs * mgr, u32 idx, u32 move);
void BufferRibbonNameOrDesc(struct ScrStrBufs * mgr, u32 idx, u32 ribbon);
void BufferAbilityName(struct ScrStrBufs * mgr, u32 idx, u32 ability);
void BufferNatureName(struct ScrStrBufs * mgr, u32 idx, u32 nature);
void BufferItemName(struct ScrStrBufs * mgr, u32 idx, u32 item);
void BufferItemNameWithIndefArticle(struct ScrStrBufs * mgr, u32 idx, u32 item);
void BufferItemNamePlural(struct ScrStrBufs * mgr, u32 idx, u32 item);
void BufferPocketName(struct ScrStrBufs * mgr, u32 idx, u32 pocket);
void BufferTypeName(struct ScrStrBufs * mgr, u32 idx, u32 type);
void BufferStatName(struct ScrStrBufs * mgr, u32 idx, u32 stat);
void BufferStatusName(struct ScrStrBufs * mgr, u32 idx, u32 status);
void BufferFlavorDislikeText(struct ScrStrBufs * mgr, u32 idx, u32 flavor);
void BufferLandmarkName(struct ScrStrBufs * mgr, u32 idx, u32 landmark);
void BufferPoketchAppName(struct ScrStrBufs * mgr, u32 idx, u32 app);
void BufferTrainerClassName(struct ScrStrBufs * mgr, u32 idx, u32 trclass);
void BufferTrainerClassNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 trclass);
void BufferTrainerClassName2(struct ScrStrBufs * mgr, u32 idx, struct Trainer * tr);
void BufferTrainerName(struct ScrStrBufs * mgr, u32 idx, u32 msgno);
void BufferTrainerNameFromDataStruct(struct ScrStrBufs * mgr, u32 idx, struct TrainerDataLoaded * trdata);
void BufferUndergroundItemName(struct ScrStrBufs * mgr, u32 idx, u32 item);
void BufferUndergroundItemNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 item);
void BufferUndergroundTrapName(struct ScrStrBufs * mgr, u32 idx, u32 trap);
void BufferUndergroundTrapNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 trap);
void BufferContestJudgeName(struct ScrStrBufs * mgr, u32 idx, u32 judge);
void BufferContestMessage(struct ScrStrBufs * mgr, u32 idx, u32 msg);
void BufferContestMessage2(struct ScrStrBufs * mgr, u32 idx, u32 msg);
void BufferInterviewQuestion(struct ScrStrBufs * mgr, u32 idx, u32 question);
void BufferInterviewAnswer(struct ScrStrBufs * mgr, u32 idx, u32 answer);
void BufferDecorationName(struct ScrStrBufs * mgr, u32 idx, u32 decor);
void BufferDecorationNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 decor);
void BufferGenderSymbol(struct ScrStrBufs * mgr, u32 idx, u32 gender);
void BufferBoxName(struct ScrStrBufs * mgr, u32 idx, struct PCStorage * pc, int boxno);
void BufferGymName(struct ScrStrBufs * mgr, u32 idx, u32 gym);
void BufferTimeOfDayName(struct ScrStrBufs * mgr, u32 idx, u32 time);
void BufferCountryName(struct ScrStrBufs * mgr, u32 idx, u32 country);
void BufferCityName(struct ScrStrBufs * mgr, u32 idx, u32 a2, u32 a3);
void FUN_0200B518(struct ScrStrBufs * mgr, u32 idx, u32 a2);
void BufferSealName(struct ScrStrBufs * mgr, u32 idx, u32 seal);
void BufferSealNamePlural(struct ScrStrBufs * mgr, u32 idx, u32 seal);
void BufferLocationName(struct ScrStrBufs * mgr, u32 idx, u16 a2);
void BufferPoffinName(struct ScrStrBufs * mgr, u32 idx, u32 poffin);
void BufferFashionName(struct ScrStrBufs * mgr, u32 idx, u32 fashion);
void BufferFashionNameWithArticle(struct ScrStrBufs * mgr, u32 idx, u32 fashion);
void BufferContestBackgroundName(struct ScrStrBufs * mgr, u32 idx, u32 bg);
void BufferEasyChatWord(struct ScrStrBufs * mgr, struct SaveBlock2 * sav2, u32 r5, u32 idx, u32 sp28);
void BufferMonthNameAbbr(struct ScrStrBufs * mgr, u32 idx, u32 month);
void ScrStrBufs_UpperFirstChar(struct ScrStrBufs * mgr, u32 idx);
void StringExpandPlaceholders(struct ScrStrBufs * mgr, struct String * dest, struct String * src);
void ScrStrBufs_ResetBuffers(struct ScrStrBufs * mgr);
struct UnkStruct_0200B870 * MessagePrinter_new(u32 r5, u32 r6, u32 sp4, u32 r4);
void MessagePrinter_delete(struct UnkStruct_0200B870 * a0);
void FUN_0200B9A8(struct UnkStruct_0200B870 * a0, int a1, int a2, int a3, int a4);
void FUN_0200B9EC(struct UnkStruct_0200B870 * string, u32 value, u32 n, enum PrintingMode mode, int sp30, int r5, int r7);

#endif //POKEDIAMOND_SCRIPT_BUFFERS_H
