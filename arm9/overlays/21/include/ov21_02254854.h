#ifndef POKEDIAMOND_ov21_02254854_H
#define POKEDIAMOND_ov21_02254854_H

#include "nitro/types.h"
#include "ov21_02254A6C.h"
#include "unk_0200CA44.h"

typedef struct Time
{
    u32 hour;
    u32 minute;
} Time;

typedef struct UnkStruct02254854
{
    u8 bytearray[8];
    u8 padding0[8];
    BOOL Unk10;
    Time time;
    u8 padding1[4];
    u32 Unk20;
    void *Unk24;
    u32 Unk28;
} UnkStruct02254854;

BOOL ov21_02254854(UnkStruct02254854 **param0, u32 param1, u32 param2, u32 param3);
BOOL ov21_0225489C(UnkStruct02254854 *param0, u32 param1, u32 param2, u32 param3);
void ov21_02254918(UnkStruct02254854 *param0);
void ov21_02254930(SysTask *task, UnkStruct02254854 *param1);
void ov21_0225496C(UnkStruct02254854 *param0);
void ov21_02254974(u32 param0, u32 param1, u32 param2, UnkStruct02254854 * param3);
void ov21_02254990(UnkStruct02254854 * param0, u8 param1);
BOOL ov21_022549A4(UnkStruct02254854 * param0);
BOOL ov21_022549E4(UnkStruct02254854 * param0);
BOOL ov21_02254A38(UnkStruct02254854 * param0);

#endif //POKEDIAMOND_ov21_02254854_H
