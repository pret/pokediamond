#ifndef POKEDIAMOND_MOD21_02254854_H
#define POKEDIAMOND_MOD21_02254854_H

#include "nitro/types.h"

typedef struct UnkStruct02254854
{
    u8 bytearray[8];
    u8 padding0[8];
    BOOL Unk10;
    u32 Unk14[2];
    u8 padding1[4];
    u32 Unk20;
    u32 Unk24;
    u32 Unk28;
} UnkStruct02254854;

BOOL MOD21_02254854(UnkStruct02254854 **param0, u32 param1, u32 param2, u32 param3);
BOOL MOD21_0225489C(UnkStruct02254854 *param0, u32 param1, u32 param2, u32 param3);
void MOD21_02254918(UnkStruct02254854 *param0);

#endif //POKEDIAMOND_MOD21_02254854_H
