#ifndef POKEDIAMOND_MOD63_021DB450_H
#define POKEDIAMOND_MOD63_021DB450_H

#include "global.h"

typedef struct UnkStruct63_021DB49C //animation struct?
{
    u32 field_00;
    u32 field_04[3]; //animation array?
    u32 field_10;
    void * field_14;
    void * field_18;
} UnkStruct63_021DB49C;

typedef struct UnkStruct63_021DB49C_2
{
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
} UnkStruct63_021DB49C_2;

typedef struct UnkStruct63_021DBEF0
{
    u32 field_00;
    u32 field_04;
} UnkStruct63_021DBEF0;

typedef struct UnkStruct63_021DB580 //possibly part of the above structs?
{
    u32 field_00;
    u8 filler[0x10];
    void *field_20;
    u32 field_24;
} UnkStruct63_021DB580;

typedef struct UnkStruct63_021DB598 //part of the above?
{
    u32 field_00;
} UnkStruct63_021DB598;

typedef struct UnkStruct63_021DB5A8 //possibly the same as above
{
    u32 field_00;
} UnkStruct63_021DB5A8;

typedef struct UnkStruct63_021DB5CC
{
    u8 filler_00[4];
    u32 field_04[5];
    u32 field_18;
    u8 field_1C;
    u8 field_1D;
} UnkStruct63_021DB5CC;

typedef struct UnkStruct63_021DBED8
{
    BOOL (*unk_00)(struct UnkStruct63_021DB5CC *, u32);
    BOOL (*unk_04)(struct UnkStruct63_021DB5CC *, u32);
} UnkStruct63_021DBED8;

u32 MOD63_021DB450(u32 param0, u32 param1);
u32 MOD63_021DB474(u32 param0, u32 param1);
u32 MOD63_021DB498(void);
void Title_SetupMonAnimationSprites(struct UnkStruct63_021DB49C * arg0);
void MOD63_021DB580(UnkStruct63_021DB580 *param0);
void MOD63_021DB598(UnkStruct63_021DB598 *param0);
void MOD63_021DB5A8(UnkStruct63_021DB5A8 *param0);
BOOL MOD63_021DB5CC(UnkStruct63_021DB5CC *param0, u32 param1, s32 param2);
BOOL MOD63_021DB720(UnkStruct63_021DB5CC *param0, u32 param1);
BOOL MOD63_021DB784(UnkStruct63_021DB5CC *param0, u32 param1);
BOOL MOD63_021DB7D0(UnkStruct63_021DB5CC *param0, u32 param1);
BOOL MOD63_021DB838(UnkStruct63_021DB5CC *param0, u32 param1);

#endif //POKEDIAMOND_MOD63_021DB450_H
