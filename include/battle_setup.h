#ifndef POKEDIAMOND_BATTLE_SETUP_H
#define POKEDIAMOND_BATTLE_SETUP_H

#include "global.h"
#include "party.h"

typedef struct BattleSetupUnkSub138 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} BattleSetupUnkSub138;

typedef struct BattleSetup {
    u32 flags;
    Party *party[4];
    u32 winFlag;
    u8 padding[0x11C];
    u32 unk134;
    BattleSetupUnkSub138 unk138;
    u8 padding2[0xC];
    u32 unk150;
    u32 unk154;
    u8 padding3[0x34];
    u32 unk18C;
} BattleSetup;

#endif //POKEDIAMOND_BATTLE_SETUP_H