#ifndef POKEDIAMOND_UNK_020851B8_H
#define POKEDIAMOND_UNK_020851B8_H

struct UnkStruct_020851B8 {
    u32 flags[2];
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
};

struct UnkStruct_020851B8 *sub_020851B8(u8 heapId);
void sub_020851DC(struct UnkStruct_020851B8 *param0, u16 param1, BOOL param2);
void sub_020851F8(struct UnkStruct_020851B8 *param0, u8 param1, u8 param2, u8 param3);
void sub_02085200(struct UnkStruct_020851B8 *param0, u16 param1);
u8 sub_02085224(struct UnkStruct_020851B8 *param0, u16 param1);
void sub_0208524C(struct UnkStruct_020851B8 *param0, u8 *param1, u8 *param2);

#endif // POKEDIAMOND_UNK_020851B8_H
