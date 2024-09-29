#ifndef POKEDIAMOND_MOVE_DATA_H
#define POKEDIAMOND_MOVE_DATA_H

struct WazaTbl {
    u16 effect;
    u8 class;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 effectChance;
    u16 unk8;
    s8 priority;
    u8 unkB;
    u8 unkC;
    u8 contestType;
    u8 padding[2];
};

typedef enum MoveAttr {
    MOVEATTR_EFFECT = 0,
    MOVEATTR_CLASS,
    MOVEATTR_POWER,
    MOVEATTR_TYPE,
    MOVEATTR_ACCURACY,
    MOVEATTR_PP,
    MOVEATTR_EFFECT_CHANCE,
    MOVEATTR_UNK7,
    MOVEATTR_PRIORTY,
    MOVEATTR_UNK9,
    MOVEATTR_UNK10,
    MOVEATTR_CONTEST_TYPE,
} MoveAttr;

void LoadAllWazaTbl(struct WazaTbl *dest);
u8 WazaGetMaxPp(u16 move, u8 ppUp);
u32 GetWazaAttr(u16 move, MoveAttr attr);
u32 GetAttrFromWazaTbl(struct WazaTbl *wazaTbl, MoveAttr attr);

#endif // POKEDIAMOND_MOVE_DATA_H
