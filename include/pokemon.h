#ifndef POKEDIAMOND_POKEMON_H
#define POKEDIAMOND_POKEMON_H

#include "nitro/types.h"

// Enums

#include "constants/pokemon.h"
#include "constants/species.h"

#include "mail.h"
#include "player_data.h"
#include "sound_chatot.h"
#include "string16.h"

#define LEVEL_UP_LEARNSET_END 0xFFFF
#define LEVEL_UP_LEARNSET_MAX 22

#define LEVEL_UP_LEARNSET_MOVEID_MASK  0x01FF
#define LEVEL_UP_LEARNSET_MOVEID_SHIFT 0
#define LEVEL_UP_LEARNSET_LEVEL_MASK   0xFE00
#define LEVEL_UP_LEARNSET_LEVEL_SHIFT  9

#define LEVEL_UP_LEARNSET_MOVE(x) ((u16)(((x) & LEVEL_UP_LEARNSET_MOVEID_MASK) >> LEVEL_UP_LEARNSET_MOVEID_SHIFT))
#define LEVEL_UP_LEARNSET_LVL(x)  (((x) & LEVEL_UP_LEARNSET_LEVEL_MASK) >> LEVEL_UP_LEARNSET_LEVEL_SHIFT)

typedef struct SpeciesData {
    /* 0x00 */ u8 hp;
    /* 0x01 */ u8 atk;
    /* 0x02 */ u8 def;
    /* 0x03 */ u8 speed;
    /* 0x04 */ u8 spatk;
    /* 0x05 */ u8 spdef;
    /* 0x06 */ u8 types[2];
    /* 0x08 */ u8 catchRate;
    /* 0x09 */ u8 expYield;
    /* 0x0A */ u16 hp_yield : 2;
    u16 atk_yield : 2;
    u16 def_yield : 2;
    u16 speed_yield : 2;
    /* 0x0B */ u16 spatk_yield : 2;
    u16 spdef_yield : 2;
    u16 padding_B_4 : 4;
    /* 0x0C */ u16 item1;
    /* 0x0E */ u16 item2;
    /* 0x10 */ u8 genderRatio;
    /* 0x11 */ u8 eggCycles;
    /* 0x12 */ u8 friendship;
    /* 0x13 */ u8 growthRate;
    /* 0x14 */ u8 eggGroups[2];
    /* 0x16 */ u8 abilities[2];
    /* 0x18 */ u8 greatMarshRate;
    /* 0x19 */ u8 color : 7;
    u8 flip : 1;
    u8 padding_1A[2];
    /* 0x1C */ u32 tmhm_1;
    /* 0x20 */ u32 tmhm_2;
    /* 0x24 */ u32 tmhm_3;
    /* 0x28 */ u32 tmhm_4;
} SpeciesData;

// Structs

typedef struct {
    /* 0x00 */ u16 species;
    /* 0x02 */ u16 heldItem;
    /* 0x04 */ u32 otID; // low 16: visible; high 16: secret
    /* 0x08 */ u32 exp;
    /* 0x0C */ u8 friendship;
    /* 0x0D */ u8 ability;
    /* 0x0E */ u8 markings; // circle, triangle, square, heart, star, diamond
    /* 0x0F */ u8 originLanguage;
    /* 0x10 */ u8 hpEV;
    /* 0x11 */ u8 atkEV;
    /* 0x12 */ u8 defEV;
    /* 0x13 */ u8 speedEV;
    /* 0x14 */ u8 spAtkEV;
    /* 0x15 */ u8 spDefEV;
    /* 0x16 */ u8 cool;
    /* 0x17 */ u8 beauty;
    /* 0x18 */ u8 cute;
    /* 0x19 */ u8 smart;
    /* 0x1A */ u8 tough;
    /* 0x1B */ u8 sheen;
    // TODO: Finish SinnohRibbonSet1
    /* 0x1C */ u32 ribbonsDS1;
    //    u8 sinnohChampRibbon:1, abilityRibbon:1;
    //    u8 field_0x1d;
    //    u8 gorgeousRoyalRibbon:1, footprintRibbon:1;
    //    u8 field_0x1f;
} PokemonDataBlockA;

typedef struct PokemonDataBlockB {
    /* 0x00 */ u16 moves[4];
    /* 0x08 */ u8 moveCurrentPPs[4];
    /* 0x0C */ u8 movePPUps[4];

    /* 0x10 */ u32 hpIV : 5;
               u32 atkIV : 5;
               u32 defIV : 5;
               u32 speedIV : 5;
               u32 spAtkIV : 5;
               u32 spDefIV : 5;
               u32 isEgg : 1;
               u32 hasNickname : 1;

    /* 0x14 */ u32 ribbonsGBA; //!< A bitmask of ribbons introduced in Generation 3. Cool, Beauty, Cute, Smart, Tough, Champion, Winning, Victory, Artist, Effort, Marine, Land, Sky, Country, National, Earth and World Ribbons.
    /* 0x18 */ u8 fatefulEncounter : 1;
               u8 gender : 2;
               u8 form : 5;
    /* 0x19 */ u8 unused1; //!< First 6 bits track Shiny Leaves from HGSS.
    /* 0x1A */ u16 unused2;

    /* 0x1C */ u16 EggLocation_PtHGSS;
    /* 0x1E */ u16 MetLocation_PtHGSS;
} PokemonDataBlockB;

typedef struct {
    /* 0x00 */ u16 nickname[POKEMON_NAME_LENGTH + 1];
    /* 0x16 */ u8 unused;
    /* 0x17 */ u8 originGame;
    /* 0x18 */ u64 ribbonsDS2; //!< A bitmask of ribbons given to the Pokemon from Sinnoh's Super Contests.
} PokemonDataBlockC;

typedef struct {
    /* 0x00 */ u16 otName[PLAYER_NAME_LENGTH + 1];

    /* 0x10 */ u8 eggYear;
    /* 0x11 */ u8 eggMonth;
    /* 0x12 */ u8 eggDay;

    /* 0x13 */ u8 metYear;
    /* 0x14 */ u8 metMonth;
    /* 0x15 */ u8 metDay;

    /* 0x16 */ u16 EggLocation_DP;
    /* 0x18 */ u16 MetLocation_DP;

    /* 0x1A */ u8 pokerus;
    /* 0x1B */ u8 pokeball;
    /* 0x1C */ u8 metLevel : 7;
    u8 otGender : 1;
    /* 0x1D */ u8 metTerrain;
    /* 0x1E */ u16 unused; //!< Stores Apricorn Ball and Mood from HGSS. Unused otherwise.
} PokemonDataBlockD;

typedef union {
    PokemonDataBlockA blockA;
    PokemonDataBlockB blockB;
    PokemonDataBlockC blockC;
    PokemonDataBlockD blockD;
} PokemonDataBlock;

typedef struct BoxPokemon {
    /* 0x000 */ u32 personality;
    /* 0x004 */ u16 partyDecrypted : 1;
    u16 boxDecrypted : 1;
    u16 checksumFailed : 1;
    u16 unused : 13;
    /* 0x006 */ u16 checksum;
    /* 0x008 */ PokemonDataBlock dataBlocks[4];
} BoxPokemon;

struct PartyPokemon {
    /* 0x088 */ u32 status; // slp:3, psn:1, brn:1, frz:1, prz:1, tox:1, ...
    /* 0x08C */ u8 level;
    /* 0x08D */ u8 ballCapsuleID;
    /* 0x08E */ u16 hp;
    /* 0x090 */ u16 maxHP;
    /* 0x092 */ u16 attack;
    /* 0x094 */ u16 defense;
    /* 0x096 */ u16 speed;
    /* 0x098 */ u16 spAtk;
    /* 0x09A */ u16 spDef;
    /* 0x09C */ struct Mail mail;
    /* 0x0D4 */ u8 ballCapsule[8][3];
};

typedef struct Pokemon {
    /* 0x000 */ struct BoxPokemon box;
    /* 0x088 */ struct PartyPokemon party;
} Pokemon; // size: 0xEC

struct SomeDrawPokemonStruct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 filler_9[3];
    u32 unkC;
};

struct PokeanmSub {
    s8 unk0;
    u8 unk1;
};

struct Pokeanm {
    struct PokeanmSub unk0[4];
    u8 unk8[20];
};

struct UnkStruct_02069038 {
    u16 unk0;
    u16 unk2;
    u8 unk4;
    u8 padding;
    struct Pokeanm anim;
};

struct Evolution {
    u16 method;
    u16 param;
    u16 target;
};

#define PARTY_SIZE 6

typedef struct Party {
    int maxCount;
    int curCount;
    struct Pokemon mons[PARTY_SIZE];
} Party;

void Pokemon_Init(Pokemon *mon);
void BoxPokemon_Init(BoxPokemon *boxMon);
u32 SizeOfStructPokemon(void);
Pokemon *Pokemon_New(HeapID heapId);
BOOL Pokemon_UnlockEncryption(Pokemon *mon);
BOOL Pokemon_LockEncryption(Pokemon *mon, BOOL decrypt_result);
BOOL AcquireBoxMonLock(BoxPokemon *boxMon);
BOOL BoxPokemon_LockEncryption(BoxPokemon *boxMon, BOOL decrypt_result);
void Pokemon_InitWithParams(Pokemon *mon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId);
void BoxPokemon_InitWithParams(BoxPokemon *boxMon, int species, int level, int ivs, BOOL hasFixedPersonality, int personality, int otIDType, int otID);
void Pokemon_InitWithNature(Pokemon *mon, u16 species, u8 level, u8 fixedIv, u8 nature);
void Pokemon_InitWithGenderNatureLetter(Pokemon *mon, u16 species, u8 level, u8 ivs, u8 gender, u8 nature, u8 letter);
u32 Personality_CreateFromGenderAndNature(u16 species, u8 gender, u8 nature);
void CreateMonWithFixedIVs(Pokemon *mon, int species, int level, int ivs, int personality);
void Pokemon_CalcLevelAndStats(Pokemon *mon);
void Pokemon_CalcStats(Pokemon *mon);
#ifndef IN_POKEMON_C
u32 Pokemon_GetData();
u32 BoxPokemon_GetData();
#else
u32 Pokemon_GetData(Pokemon *mon, int param, void *ptr);
u32 BoxPokemon_GetData(BoxPokemon *boxMon, int param, void *ptr);
#endif
void Pokemon_SetData(Pokemon *mon, int param, void *ptr);
void BoxPokemon_SetData(BoxPokemon *boxMon, int param, void *ptr);
void AddMonData(Pokemon *mon, int param, int amount);
SpeciesData *SpeciesData_NewFromSpecies(int species, HeapID heapId);
int SpeciesData_GetValue(SpeciesData *speciesData, enum SpeciesDataParam attr);
void SpeciesData_Free(SpeciesData *speciesData);
int Species_GetFormValue(int species, int form, enum SpeciesDataParam stat_id);
int Species_GetValue(int species, enum SpeciesDataParam stat_id);
u8 Pokemon_CalcPercentToNextLevel(Pokemon *mon);
u32 Pokemon_CalcExpToNextLevel(Pokemon *mon);
u32 Pokemon_GetCurrentLevelBaseExp(Pokemon *mon);
u32 Species_GetExpAtLevel(int species, int level);
void ExpRate_LoadTable(int growthRate, u32 *table);
u32 ExpRate_GetExpAtLevel(int rate, int level);
int Pokemon_CalcLevel(Pokemon *mon);
int BoxPokemon_CalcLevel(BoxPokemon *boxMon);
int Species_CalcLevelByExp(u16 species, u32 experience);
int SpeciesData_CalcLevelByExp(SpeciesData *speciesData, u16 species, u32 experience);
u8 BoxPokemon_GetNature(BoxPokemon *boxMon);
u8 Pokemon_GetNature(Pokemon *mon);
u8 Personality_GetNature(u32 personality);
void Pokemon_UpdateFriendship(Pokemon *mon, u32 kind, u32 location);
u8 Pokemon_GetGender(Pokemon *mon);
u8 BoxPokemon_GetGender(BoxPokemon *boxMon);
u8 Species_GetGenderFromPersonality(u16 species, u32 personality);
u8 Pokemon_IsShiny(Pokemon *mon);
u32 Personality_GenerateShiny(u32 otID);
void sub_02068B70(struct SomeDrawPokemonStruct *spC, BoxPokemon *boxMon, u8 sp10);
void sub_02068C00(struct SomeDrawPokemonStruct *spC, int species, u8 gender, u8 sp10, u8 shiny, u8 form, u32 personality);
u8 sub_02068E14(Pokemon *mon, u32 a1);
u8 sub_02068E1C(BoxPokemon *boxMon, u32 a1);
u8 sub_02068E88(int species, u8 gender, u32 a2, u8 form, u32 pid);
u32 GetArceusTypeByHeldItemEffect(u16 plate);
int sub_0206AA30(int a0);
void sub_02068B68(struct SomeDrawPokemonStruct *spC, Pokemon *mon, u8 sp10);
void sub_02068FE0(struct SomeDrawPokemonStruct *a0, u16 a1, int a2);
void sub_02069010(void *dest, int a1);
void sub_02069038(u32 a0, u32 a1, u32 a2, s32 a3, u32 a4, u32 a5, u32 a6);
void sub_020690AC(struct SomeDrawPokemonStruct *a0, u32 a1);
u32 sub_020690C4(void);
u32 sub_020690C8(void);
u8 GetBoxMonUnownLetter(BoxPokemon *boxMon);
u8 GetMonUnownLetter(Pokemon *mon);
void LoadLevelUpLearnset_HandleAlternateForm(int species, int form, u16 *levelUpLearnset);
BoxPokemon *sub_020690E4(Pokemon *mon);

u16 GetMonEvolution(struct Party *party, Pokemon *mon, u32 context, u32 usedItem, u32 *method_ret);
u16 ReadFromPersonalPmsNarc(u16 species);
u16 GetEggSpecies(u16 species);
BOOL sub_020690E8(Pokemon *mon);
u32 sub_02069698(Pokemon *mon, u16 move);
void sub_02069708(Pokemon *mon, u16 move);
void sub_02069718(BoxPokemon *boxMon, u16 move);
void MonSetMoveInSlot(Pokemon *mon, u16 move, u8 slot);
u32 sub_02069818(Pokemon *mon, u32 *r5, u16 *sp0);
void sub_020698E0(Pokemon *mon, int slot1, int slot2);
void sub_020698E8(BoxPokemon *boxMon, int slot1, int slot2);
void sub_020699A4(Pokemon *mon, u32 slot);
void CopyBoxPokemonToPokemon(BoxPokemon *src, Pokemon *dest);
u8 Party_GetMaxLevel(struct Party *party);
u16 SpeciesToSinnohDexNo(u16 species);
u16 SinnohDexNoToSpecies(u16 sinnoh_dex);
void CopyPokemonToPokemon(Pokemon *src, Pokemon *dest);
void CopyPokemonToBoxPokemon(Pokemon *src, BoxPokemon *dest);
void CopyBoxPokemonToBoxPokemon(BoxPokemon *src, BoxPokemon *dest);
s8 MonGetFlavorPreference(Pokemon *mon, int flavor);
int Species_LoadLearnsetTable(u16 species, u32 form, u16 *dest);
void Party_GivePokerusAtRandom(struct Party *party);
void Party_UpdatePokerus(struct Party *party, int r5);
void Party_SpreadPokerus(struct Party *party);
BOOL Pokemon_HasPokerus(Pokemon *mon);
BOOL Pokemon_IsImmuneToPokerus(Pokemon *mon);
void Pokemon_UpdateArceusForm(Pokemon *mon);
void sub_02069FB0(struct SaveChatotSoundClip *r7, u32 r5, u16 r4, s32 r6, s32 sp18, u32 sp1C, HeapID heapId);
void sub_0206A014(Pokemon *mon, PlayerProfile *a1, u32 pokeball, u32 a3, u32 encounterType, HeapID heapId);
void sub_0206A094(Pokemon *mon, u32 a1, u32 a2);
BOOL sub_0206A13C(Pokemon *mon, u32 a1);
void sub_0206A1C4(Pokemon *mon);
void sub_0206A23C(Pokemon *r5, u32 personality);
int LowestFlagNo(u32 mask);
BOOL IsPokemonLegendaryOrMythical(u16 species);
u16 GetLegendaryMon(u32 idx);
BOOL sub_0206A998(Pokemon *mon);
BOOL sub_0206A9AC(BoxPokemon *boxMon, PlayerProfile *sb2, HeapID heapId);
void Pokemon_RemoveCapsule(Pokemon *mon);
void RestoreBoxMonPP(BoxPokemon *boxMon);

#endif // POKEDIAMOND_POKEMON_H
