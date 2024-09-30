#ifndef POKEDIAMOND_UNK_02008DEC_H
#define POKEDIAMOND_UNK_02008DEC_H

#include "global.h"

#include "NNS_g2d.h"
#include "filesystem.h"

struct UnkStruct_02008DEC_sub {
    u32 unk00;
    u32 unk04;
    void *unk08;
};

struct UnkStruct_02008DEC_1 {

    u32 unk00;
    struct UnkStruct_02008DEC_sub *unk04;
    s32 unk08;
    u32 unk0C;
    s32 unk10;
};

struct UnkStruct_02008DEC_2 {
    union {
        struct UnkStruct_02008DEC_3 *unk00_3;
        struct UnkStruct_02008DEC_4 *unk00_4;
    };
    s32 unk04;
    u32 unk08;
    u8 unk0C;
};

struct UnkStruct_02008DEC_3 {
    s32 unk00;
    u8 unk04[0x40];
    u32 unk44;
    u32 unk48;
};

struct UnkStruct_02008DEC_4 {
    NarcId unk00;
    s32 unk04;
    BOOL unk08;
    s32 unk0C;
    u32 unk10;
    u32 unk14;
};

struct UnkStruct_02008DEC_5 {
    struct UnkStruct_02008DEC_sub **unk00;
    s32 unk04;
    s32 unk08;
};

struct CharacterData_02008DEC {
    NNSG2dCharacterData *chData;
    u32 unk04;
};

struct PaletteData_02008DEC {
    NNSG2dPaletteData *plttData;
    u32 unk04;
    u32 unk08;
};

struct CellDataBank_02008DEC {
    NNSG2dCellDataBank *cellBank;
};

struct AnimBank_02008DEC {
    NNSG2dAnimBankData *bankData;
};

struct UnkStruct_02008DEC_1 *sub_02008DEC(u32 param0, s32 param1, HeapID heapId);
void sub_02008E2C(struct UnkStruct_02008DEC_1 *param0);
struct UnkStruct_02008DEC_sub *sub_02008E6C(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_2 *param1,
    s32 param2,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_02008F34(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_02008F90(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId,
    BOOL param7);
struct UnkStruct_02008DEC_sub *sub_02008FEC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_0200904C(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId,
    BOOL param8);
struct UnkStruct_02008DEC_sub *sub_020090AC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    HeapID heapId);
void sub_020090FC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    HeapID heapId);
void sub_02009168(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_020091E0(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_0200923C(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId,
    u32 param7);
struct UnkStruct_02008DEC_sub *sub_02009298(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId);
struct UnkStruct_02008DEC_sub *sub_020092F8(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId,
    u32 param8);
struct UnkStruct_02008DEC_sub *sub_02009358(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    HeapID heapId);
s32 sub_020093A8(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_2 *param1,
    struct UnkStruct_02008DEC_5 *param2,
    HeapID heapId);
void sub_020093DC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_2 *param1,
    s32 param2,
    s32 param3,
    struct UnkStruct_02008DEC_5 *param4,
    HeapID heapId);
struct UnkStruct_02008DEC_5 *sub_02009424(s32 param0, HeapID heapId);
void sub_02009448(struct UnkStruct_02008DEC_5 *param0);
u32 sub_0200945C(struct UnkStruct_02008DEC_1 *param0, s32 param1);
void sub_02009474(struct UnkStruct_02008DEC_sub *param0);
void sub_02009490(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_sub *param1);
void sub_020094C4(struct UnkStruct_02008DEC_1 *param0);
struct UnkStruct_02008DEC_sub *sub_020094F0(struct UnkStruct_02008DEC_1 *param0, s32 param1);
s32 sub_02009530(struct UnkStruct_02008DEC_sub *param0);
u32 sub_02009544(struct UnkStruct_02008DEC_sub *param0);
u32 sub_0200955C(struct UnkStruct_02008DEC_sub *param0);
u32 sub_02009574(struct UnkStruct_02008DEC_sub *param0);
u32 sub_0200958C(struct UnkStruct_02008DEC_sub *param0);
u32 sub_020095A4(struct UnkStruct_02008DEC_sub *param0);
u32 sub_020095BC(struct UnkStruct_02008DEC_sub *param0);
u32 sub_020095D4(struct UnkStruct_02008DEC_sub *param0);
u32 sub_020095E4(struct UnkStruct_02008DEC_sub *param0);
u32 sub_02009610(struct UnkStruct_02008DEC_sub *param0);
void sub_02009630(struct UnkStruct_02008DEC_sub *param0, u32 param1);
u32 sub_0200965C(void);
struct UnkStruct_02008DEC_2 *sub_02009660(struct UnkStruct_02008DEC_2 *param0, s32 param1);
void sub_02009668(u32 *param0, struct UnkStruct_02008DEC_2 *param1, HeapID heapId);
void sub_020096B4(struct UnkStruct_02008DEC_2 *param0);
s32 sub_020096CC(struct UnkStruct_02008DEC_2 *param0);
s32 sub_020096DC(struct UnkStruct_02008DEC_2 *param0, s32 param1);
s32 sub_02009710(struct UnkStruct_02008DEC_2 *param0, s32 param1);
BOOL sub_0200973C(struct UnkStruct_02008DEC_2 *param0, s32 param1);
u32 sub_02009768(struct UnkStruct_02008DEC_2 *param0, s32 param1);
u32 sub_0200979C(struct UnkStruct_02008DEC_2 *param0, s32 param1);
struct UnkStruct_02008DEC_sub *sub_020097D0(struct UnkStruct_02008DEC_1 *param0);
void sub_020097FC(
    struct UnkStruct_02008DEC_sub *param0, u32 param1, u32 param2, u32 param3, HeapID heapId);
struct CharacterData_02008DEC *sub_0200986C(void *param0, u32 param1, HeapID heapId);
struct PaletteData_02008DEC *sub_0200988C(void *param0, u32 param1, u32 param2, HeapID heapId);
struct CellDataBank_02008DEC *sub_020098B0(void *param0, HeapID heapId);
struct AnimBank_02008DEC *sub_020098CC(void *param0, HeapID heapId);
void *sub_020098E8(void *param0, HeapID heapId);
void *sub_02009904(void *param0, HeapID heapId);
void sub_02009920(struct UnkStruct_02008DEC_sub *param0);
u32 *sub_02009934(struct UnkStruct_02008DEC_sub *param0);
void sub_0200994C(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    void *param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    HeapID heapId);
void sub_02009978(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    HeapID heapId,
    BOOL param10);
void sub_020099B0(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NARC *param2,
    u32 param3,
    u32 param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    HeapID heapId,
    u32 param10);
s32 sub_020099E8(struct UnkStruct_02008DEC_4 *param0);
void *sub_02009A04(NARC *param0, u32 param1, u32 param2, HeapID heapId, u32 param4);
u32 sub_02009A50(struct UnkStruct_02008DEC_sub *param0);
void sub_02009A90(struct UnkStruct_02008DEC_5 *param0);
u32 sub_02009AC4(struct UnkStruct_02008DEC_sub *param0);
u32 sub_02009B04(struct UnkStruct_02008DEC_sub *param0);
void sub_02009B44(struct UnkStruct_02008DEC_5 *param0);
u32 sub_02009B78(struct UnkStruct_02008DEC_sub *param0);
void sub_02009BB8(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1);
void sub_02009BE8(struct UnkStruct_02008DEC_sub *param0);
void sub_02009C0C(struct UnkStruct_02008DEC_sub *param0);
void sub_02009C30(struct UnkStruct_02008DEC_5 *param0);
u32 sub_02009C5C(struct UnkStruct_02008DEC_sub *param0);
u32 sub_02009C80(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1);
void sub_02009CDC(u32 param0);
u32 sub_02009CF0(struct UnkStruct_02008DEC_sub *param0);
void sub_02009D34(struct UnkStruct_02008DEC_5 *param0);
u32 sub_02009D68(struct UnkStruct_02008DEC_sub *param0);
void sub_02009DAC(struct UnkStruct_02008DEC_5 *param0);
void sub_02009DE0(struct UnkStruct_02008DEC_sub *param0);
void sub_02009E04(struct UnkStruct_02008DEC_sub *param0);
void sub_02009E28(struct UnkStruct_02008DEC_5 *param0);
u32 sub_02009E54(struct UnkStruct_02008DEC_sub *param0, u32 param1);
s32 sub_02009E88(struct UnkStruct_02008DEC_sub *param0, u32 param1);

#endif // POKEDIAMOND_UNK_02008DEC_H
