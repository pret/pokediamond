#ifndef POKEDIAMOND_UNK_02008DEC_H
#define POKEDIAMOND_UNK_02008DEC_H

#include "global.h"
#include "NNS_g2d.h"
#include "filesystem.h"

struct UnkStruct_02008DEC_sub
{
    u32 unk00;
    u32 unk04;
    void *unk08;
};

struct UnkStruct_02008DEC_1
{

    u32 unk00;
    struct UnkStruct_02008DEC_sub *unk04;
    s32 unk08;
    u32 unk0C;
    s32 unk10;
};

struct UnkStruct_02008DEC_2
{
    void *unk00;
    s32 unk04;
    u32 unk08;
    u8 unk0C;
};

struct UnkStruct_02008DEC_3
{
    s32 unk00;
    u8 unk04[0x40];
    u32 unk44;
    u32 unk48;
};

struct UnkStruct_02008DEC_4
{
    NarcId unk00;
    s32 unk04;
    BOOL unk08;
    s32 unk0C;
    u32 unk10;
    u32 unk14;
};

struct UnkStruct_02008DEC_5
{
    struct UnkStruct_02008DEC_sub **unk00;
    s32 unk04;
    s32 unk08;
};

struct CharacterData_02008DEC
{
    NNSG2dCharacterData *chData;
    u32 unk04;
};

struct PaletteData_02008DEC
{
    NNSG2dPaletteData *plttData;
    u32 unk04;
    u32 unk08;
};

struct CellDataBank_02008DEC
{
    NNSG2dCellDataBank *cellBank;
};

struct AnimBank_02008DEC
{
    NNSG2dAnimBankData *bankData;
};

struct UnkStruct_02008DEC_1 *FUN_02008DEC(u32 param0, s32 param1, u32 param2);
void FUN_02008E2C(struct UnkStruct_02008DEC_1 *param0);
struct UnkStruct_02008DEC_sub *FUN_02008E6C(
    struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_2 *param1, s32 param2, u32 param3);
struct UnkStruct_02008DEC_sub *FUN_02008F34(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6);
struct UnkStruct_02008DEC_sub *FUN_02008F90(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    BOOL param7);
struct UnkStruct_02008DEC_sub *FUN_02008FEC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7);
struct UnkStruct_02008DEC_sub *FUN_0200904C(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    BOOL param8);
struct UnkStruct_02008DEC_sub *FUN_020090AC(struct UnkStruct_02008DEC_1 *param0,
    NarcId param1,
    s32 param2,
    BOOL param3,
    s32 param4,
    u32 param5,
    u32 param6);
void FUN_020090FC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5);
void FUN_02009168(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5);
struct UnkStruct_02008DEC_sub *FUN_020091E0(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6);
struct UnkStruct_02008DEC_sub *FUN_0200923C(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7);
struct UnkStruct_02008DEC_sub *FUN_02009298(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7);
struct UnkStruct_02008DEC_sub *FUN_020092F8(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8);
struct UnkStruct_02008DEC_sub *FUN_02009358(struct UnkStruct_02008DEC_1 *param0,
    NARC *param1,
    u32 param2,
    u32 param3,
    s32 param4,
    u32 param5,
    u32 param6);
s32 FUN_020093A8(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_2 *param1, struct UnkStruct_02008DEC_5 *param2, u32 param3);
void FUN_020093DC(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_2 *param1,
    s32 param2,
    s32 param3,
    struct UnkStruct_02008DEC_5 *param4,
    u32 param5);
struct UnkStruct_02008DEC_5 *FUN_02009424(s32 param0, u32 param1);
void FUN_02009448(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_0200945C(struct UnkStruct_02008DEC_1 *param0, s32 param1);
void FUN_02009474(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009490(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_sub *param1);
void FUN_020094C4(struct UnkStruct_02008DEC_1 *param0);
struct UnkStruct_02008DEC_sub *FUN_020094F0(struct UnkStruct_02008DEC_1 *param0, s32 param1);
s32 FUN_02009530(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_02009544(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_0200955C(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_02009574(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_0200958C(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_020095A4(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_020095BC(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_020095D4(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_020095E4(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_02009610(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009630(struct UnkStruct_02008DEC_sub *param0, u32 param1);
u32 FUN_0200965C(void);
struct UnkStruct_02008DEC_2 *FUN_02009660(struct UnkStruct_02008DEC_2 *param0, s32 param1);
void FUN_02009668(u32 *param0, struct UnkStruct_02008DEC_2 *param1, u32 param2);
void FUN_020096B4(struct UnkStruct_02008DEC_2 *param0);
s32 FUN_020096CC(struct UnkStruct_02008DEC_2 *param0);
s32 FUN_020096DC(struct UnkStruct_02008DEC_2 *param0, s32 param1);
s32 FUN_02009710(struct UnkStruct_02008DEC_2 *param0, s32 param1);
BOOL FUN_0200973C(struct UnkStruct_02008DEC_2 *param0, s32 param1);
u32 FUN_02009768(struct UnkStruct_02008DEC_2 *param0, s32 param1);
u32 FUN_0200979C(struct UnkStruct_02008DEC_2 *param0, s32 param1);
struct UnkStruct_02008DEC_sub *FUN_020097D0(struct UnkStruct_02008DEC_1 *param0);
void FUN_020097FC(struct UnkStruct_02008DEC_sub *param0, u32 param1, u32 param2, u32 param3, u32 param4);
struct CharacterData_02008DEC *FUN_0200986C(void *param0, u32 param1, u32 param2);
struct PaletteData_02008DEC *FUN_0200988C(void *param0, u32 param1, u32 param2, u32 param3);
struct CellDataBank_02008DEC *FUN_020098B0(void *param0, u32 param1);
struct AnimBank_02008DEC *FUN_020098CC(void *param0, u32 param1);
void *FUN_020098E8(void *param0, u32 param1);
void *FUN_02009904(void *param0, u32 param1);
void FUN_02009920(struct UnkStruct_02008DEC_sub *param0);
u32 *FUN_02009934(struct UnkStruct_02008DEC_sub *param0);
void FUN_0200994C(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    void *param2,
    s32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7);
void FUN_02009978(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    BOOL param10);
void FUN_020099B0(struct UnkStruct_02008DEC_1 *param0,
    struct UnkStruct_02008DEC_sub *param1,
    NARC *param2,
    u32 param3,
    u32 param4,
    s32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    u32 param10);
s32 FUN_020099E8(struct UnkStruct_02008DEC_4 *param0);
void *FUN_02009A04(NARC *param0, u32 param1, u32 param2, u32 param3, u32 param4);
u32 FUN_02009A50(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009A90(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_02009AC4(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_02009B04(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009B44(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_02009B78(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009BB8(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1);
void FUN_02009BE8(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009C0C(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009C30(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_02009C5C(struct UnkStruct_02008DEC_sub *param0);
u32 FUN_02009C80(struct UnkStruct_02008DEC_sub *param0, struct UnkStruct_02008DEC_sub *param1);
void FUN_02009CDC(u32 param0);
u32 FUN_02009CF0(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009D34(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_02009D68(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009DAC(struct UnkStruct_02008DEC_5 *param0);
void FUN_02009DE0(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009E04(struct UnkStruct_02008DEC_sub *param0);
void FUN_02009E28(struct UnkStruct_02008DEC_5 *param0);
u32 FUN_02009E54(struct UnkStruct_02008DEC_sub *param0, u32 param1);
s32 FUN_02009E88(struct UnkStruct_02008DEC_sub *param0, u32 param1);

#endif // POKEDIAMOND_UNK_02008DEC_H
