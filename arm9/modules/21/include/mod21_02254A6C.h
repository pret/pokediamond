#ifndef POKEDIAMOND_MOD21_02254A6C_H
#define POKEDIAMOND_MOD21_02254A6C_H

#include "nitro/types.h"

typedef struct UnkStruct02254A6C UnkStruct02254A6C;

struct UnkStruct02254A6C
{
    UnkStruct02254A6C *Unk00;
    u32 Unk04;
    u32 Unk08[1];
    u32 Unk0C;
    u8 padding0[0x20];
    u32 Unk30[1];
};

BOOL MOD21_02254A6C(UnkStruct02254A6C *param0, void *param1);
void MOD21_02254AD4(void *param0, void *param1);
void MOD21_02254B04(void *param0);
void MOD21_02254B10(u32 *param0, u32 param1);
BOOL MOD21_02254B34(void *param0, u32 param1);
BOOL MOD21_02254B40(void *param0);
BOOL MOD21_02254B4C(void *param0);
BOOL MOD21_02254B60(u32 param0, void *param1);
BOOL MOD21_02254BF4(u32 param0, void *param1);
BOOL MOD21_02254C14(u32 param0, void *param1);
BOOL MOD21_02254C40(u32 param0, void *param1);

#endif //POKEDIAMOND_MOD21_02254A6C_H
