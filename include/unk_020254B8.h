#ifndef POKEDIAMOND_UNK_020254B8_H
#define POKEDIAMOND_UNK_020254B8_H

struct UnkStruct_020254B8
{
    u16 field_00[8];
    u32 field_10;
    u8 filler_14[4];
    u32 field_18[16];
    u8 filler_58[16];
    u8 field_68[32];
};

u32 FUN_020254B8(void);
struct UnkStruct_020254B8 * FUN_020254C0(struct SaveBlock2 * sav2);
void FUN_020254CC(struct UnkStruct_020254B8 * arr);
u16 * FUN_020254F0(struct UnkStruct_020254B8 * arr, s32 i);
u8 FUN_020254F8(struct UnkStruct_020254B8 * unk, s32 i);
BOOL FUN_02025500(struct UnkStruct_020254B8 * a, struct UnkStruct_020254B8 * b);
void FUN_02025520(struct UnkStruct_020254B8 * sp0, struct UnkStruct_020254B8 * sp4, s32 n, u32 heap_id);
s32 FUN_02025614(struct UnkStruct_020254B8 * a0, u32 a1);

#endif //POKEDIAMOND_UNK_020254B8_H
