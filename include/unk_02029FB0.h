#ifndef POKEDIAMOND_UNK_02029FB0_H
#define POKEDIAMOND_UNK_02029FB0_H

struct Pokedex;

struct UnkStruct_02029FB0
{
    u32 unk_00[0x2C];
    u16 unk_B0[0x4D];
};

u32 FUN_02029FB0(void);
void FUN_02029FB8(struct UnkStruct_02029FB0 * ptr);
struct UnkStruct_02029FB0 * FUN_02029FC8(struct SaveBlock2 * sav2);
u32 FUN_02029FD4(struct UnkStruct_02029FB0 * ptr, s32 a1);
u32 FUN_02029FF8(struct UnkStruct_02029FB0 * ptr, s32 a1, u32 a2);
u32 FUN_0202A028(s32 a0);
u16 FUN_0202A070(s32 a0);
u32 FUN_0202A07C(struct UnkStruct_02029FB0 * ptr, s32 a1, u32 a2);
u32 FUN_0202A0A8(struct UnkStruct_02029FB0 * ptr, s32 a1, u32 a2);
u32 FUN_0202A0E8(struct UnkStruct_02029FB0 * ptr, s32 a1);
u32 FUN_0202A11C(struct UnkStruct_02029FB0 * ptr, s32 a1, u32 a2);
u32 FUN_0202A150(struct UnkStruct_02029FB0 * ptr, s32 a1);
u32 FUN_0202A170(struct UnkStruct_02029FB0 * ptr, s32 a1);
u32 FUN_0202A1B8(struct UnkStruct_02029FB0 * ptr);
void FUN_0202A1C4(struct UnkStruct_02029FB0 * ptr, struct Pokedex * pokedex, u16 species);

#endif //POKEDIAMOND_UNK_02029FB0_H
