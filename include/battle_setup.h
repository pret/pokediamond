#ifndef POKEDIAMOND_BATTLE_SETUP_H
#define POKEDIAMOND_BATTLE_SETUP_H

#include "global.h"
#include "party.h"
#include "trainer_data.h"

typedef struct BattleSetupUnkSub138 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} BattleSetupUnkSub138;

struct BattleSetup {
    u32 flags;
    Party *party[4];
    u32 winFlag;
    u32 trainerId[4];
    Trainer trainers[4];
    u8 padding[0x3C];
    u32 unk134;
    BattleSetupUnkSub138 unk138;
    u8 padding2[0xC];
    u32 unk150;
    u32 unk154;
    u8 padding3[0x8];
    u32 unk160;
    u8 padding4[0xC];
    u32 unk170;
    u8 padding5[0x18];
    u32 unk18C;
};

#endif //POKEDIAMOND_BATTLE_SETUP_H