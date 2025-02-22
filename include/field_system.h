#ifndef POKEDIAMOND_FIELD_SYSTEM_H
#define POKEDIAMOND_FIELD_SYSTEM_H

#include "global.h"

#include "bg_window.h"
#include "camera.h"
#include "field_player_avatar.h"
#include "field_types_def.h"
#include "save.h"
#include "task.h"

typedef struct Location {
    u32 mapId;
    u32 warpId;
    u32 x;
    u32 y;
    u32 direction;
} Location;

typedef struct UnkFieldStruct04 {
    u8 padding[0xC];
    u32 unk0C;
    u8 unk10[0xC];
    u32 unk1C;
} UnkFieldStruct04;

typedef struct UnkStruct_020464D4 {
    u16 unk0[4];
    u8 padding[0x108];
} UnkStruct_020464D4;

typedef struct UnkStruct_02046444 {
    u8 padding[0x24];
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u8 padding2[0x66];
    UnkStruct_020464D4 unk90[1]; // todo find size
} UnkStruct_02046444;

struct FieldSystem {
    u32 *unk00;
    UnkFieldStruct04 *unk04;
    BgConfig *bgConfig;
    SaveData *saveData; // 0xC
    TaskManager *taskManager;
    u8 padding2[0x8];
    Location *location;
    Camera *camera;
    u32 unk24;
    u8 padding3[0xC];
    MapObjectManager *mapObjectManager;
    PlayerAvatar *playerAvatar;
    u8 padding4[0x24];
    u32 unk60;
    u8 padding5[0x8];
    u32 unk6C;
    u8 padding6[0x6];
    u16 unk76;
    u32 unk78;
    u32 unk7C;
    u8 padding7[0x10];
    u32 unk90;
    u8 padding8[0x4];
    u32 *unk98;
    u8 padding9[0xC];
    UnkStruct_02046444 *unkA8;
};

#endif // POKEDIAMOND_FIELD_SYSTEM_H
