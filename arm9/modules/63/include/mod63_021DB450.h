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

u32 MOD63_021DB450(u32 param0, u32 param1);
u32 MOD63_021DB474(u32 param0, u32 param1);
u32 MOD63_021DB498(void);
void Title_SetupMonAnimationSprites(struct UnkStruct63_021DB49C * arg0);
void MOD63_021DB580(UnkStruct63_021DB580 *param0);

#endif //POKEDIAMOND_MOD63_021DB450_H
