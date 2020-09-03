#ifndef POKEDIAMOND_UNK_02021FF8_H
#define POKEDIAMOND_UNK_02021FF8_H

struct UnkStruct_020220C4_sub
{
    u8 field_0;
    u8 field_1;
    u16 field_2;
};

struct UnkStruct_020220C4
{
    u8 * field_0;
    u32 field_4;
    void (*field_8)(s32, s32, u32);
    u32 field_C;
    struct UnkStruct_020220C4_sub * field_10;
};

BOOL String_IsTrainerName(struct String * string);
void StringCat_HandleTrainerName(struct String * dest, struct String * src);
struct UnkStruct_020220C4 * FUN_020220C4(u8 * a0, u32 a1, void (*a2)(s32, s32, u32), u32 a3, u32 a4);
void FUN_02022120(struct UnkStruct_020220C4_sub * sub);
void FUN_0202212C(struct UnkStruct_020220C4 * unk);
void FUN_02022144(struct UnkStruct_020220C4 * unk);
s32 FUN_020221EC(struct UnkStruct_020220C4_sub * a0, u32 a1, u32 a2);
s32 FUN_02022208(struct UnkStruct_020220C4_sub * a0, u32 a1, u32 a2);
void FUN_0202223C(struct UnkStruct_020220C4_sub * a0, u8 a1);

#endif //POKEDIAMOND_UNK_02021FF8_H
