#ifndef POKEDIAMOND_MOVE_DATA_H
#define POKEDIAMOND_MOVE_DATA_H

struct WazaTbl
{
    u16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 pp;
    u8 unk7;
    u16 unk8;
    s8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 padding[2];
};

void LoadAllWazaTbl(struct WazaTbl * dest);
u8 WazaGetMaxPp(u16 move, u8 ppUp);
u32 GetWazaAttr(u16 move, u32 attr);
u32 GetAttrFromWazaTbl(struct WazaTbl * wazaTbl, u32 attr);

#endif //POKEDIAMOND_MOVE_DATA_H
