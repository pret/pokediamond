#ifndef POKEDIAMOND_MOD63_021DB450_H
#define POKEDIAMOND_MOD63_021DB450_H

#include "global.h"

typedef struct UnkStruct63_021DB450 //intro base struct type
{
    struct UnkStruct63_021DB450 * field_00; //oddly requires this to be set to progress past copyright/pokemon screen.
    u32 field_04[3]; //mon animations?
    u32 field_10;
    void * field_14;
    void * field_18;
    u8 field_1C;
    u8 field_1D;
    u8 padding_1E[2];
    u32 ** field_20;
    u32 field_24;
    u32 field_28;
    u32 field_2C;
    u32 field_30;
    u8 filler_34[0x30];
} UnkStruct63_021DB450;

typedef struct UnkStruct63_021DB49C
{
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
} UnkStruct63_021DB49C;

typedef struct UnkStruct63_021DBEF0
{
    u32 field_00;
    u32 field_04;
} UnkStruct63_021DBEF0;

typedef struct UnkStruct63_021DBED8
{
    BOOL (*unk_00)(struct UnkStruct63_021DB450 *, u32);
    BOOL (*unk_04)(struct UnkStruct63_021DB450 *, u32);
} UnkStruct63_021DBED8;

u32 MOD63_021DB450(u32 param0, u32 param1);
u32 MOD63_021DB474(u32 param0, u32 param1);
u32 MOD63_021DB498(void);
void Title_SetupMonAnimationSprites(struct UnkStruct63_021DB450 * arg0);
void MOD63_021DB580(UnkStruct63_021DB450 *param0);
void MOD63_021DB598(UnkStruct63_021DB450 *param0);
void MOD63_021DB5A8(UnkStruct63_021DB450 *param0);
BOOL MOD63_021DB5CC(UnkStruct63_021DB450 *param0, u32 param1, s32 param2);
BOOL MOD63_021DB720(UnkStruct63_021DB450 *param0, u32 param1);
BOOL MOD63_021DB784(UnkStruct63_021DB450 *param0, u32 param1);
BOOL MOD63_021DB7D0(UnkStruct63_021DB450 *param0, u32 param1);
BOOL MOD63_021DB838(UnkStruct63_021DB450 *param0, u32 param1);
BOOL MOD63_021DB884(UnkStruct63_021DB450 *param0, u32 param1);
BOOL MOD63_021DB8E8(UnkStruct63_021DB450 *param0, u32 param1);
void MOD63_021DB934(void);
void MOD63_021DB940(struct UnkStruct63_021DB450 * a0);

#endif //POKEDIAMOND_MOD63_021DB450_H
