#ifndef POKEDIAMOND_UNK_02029FB0_H
#define POKEDIAMOND_UNK_02029FB0_H

struct Pokedex;

struct GameStats
{
    u32 unk_00[0x2C];
    u16 unk_B0[0x4D];
};

u32 Sav2_GameStats_sizeof(void);
void Sav2_GameStats_init(struct GameStats * ptr);
struct GameStats * Sav2_GameStats_get(struct SaveBlock2 * sav2);
u32 GameStats_GetValue(struct GameStats * ptr, s32 a1);
u32 GameStats_SetValue(struct GameStats * ptr, s32 a1, u32 a2);
u32 GameStats_GetMaxValue(s32 a0);
u16 GameStats_GetStdInc(s32 a0);
u32 GameStats_SetCapped(struct GameStats * ptr, s32 a1, u32 a2);
u32 GameStats_UpdateBounded(struct GameStats * ptr, s32 a1, u32 a2);
u32 GameStats_Inc(struct GameStats * ptr, s32 a1);
u32 GameStats_Add(struct GameStats * ptr, s32 a1, u32 a2);
u32 GameStats_GetCapped(struct GameStats * ptr, s32 a1);
u32 GameStats_AddSpecial(struct GameStats * ptr, s32 a1);
u32 GameStats_GetStat0(struct GameStats * ptr);
void GameStats_IncSpeciesCaught(struct GameStats * ptr, struct Pokedex * pokedex, u16 species);

#endif //POKEDIAMOND_UNK_02029FB0_H
