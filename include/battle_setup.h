#ifndef POKEDIAMOND_BATTLE_SETUP_H
#define POKEDIAMOND_BATTLE_SETUP_H

#include "global.h"
#include "party.h"

#define BATTLE_SETUP_FLAG_NONE              (0)
#define BATTLE_SETUP_FLAG_UNK_0             (1 << 0)
#define BATTLE_SETUP_FLAG_UNK_1             (1 << 1)
#define BATTLE_SETUP_FLAG_UNK_2             (1 << 2)
#define BATTLE_SETUP_FLAG_UNK_3             (1 << 3)
#define BATTLE_SETUP_FLAG_UNK_4             (1 << 4)
#define BATTLE_SETUP_FLAG_UNK_5             (1 << 5)
#define BATTLE_SETUP_FLAG_UNK_6             (1 << 6)
#define BATTLE_SETUP_FLAG_UNK_8             (1 << 8)
#define BATTLE_SETUP_FLAG_UNK_9             (1 << 9)
#define BATTLE_SETUP_FLAG_UNK_10            (1 << 10)
#define BATTLE_SETUP_FLAG_HEAL_AFTER_DEFEAT (1 << 11)
#define BATTLE_SETUP_FLAG_UNK_31            (1 << 31)

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