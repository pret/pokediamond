#ifndef POKEDIAMOND_GLOBAL_FIELDMAP_H
#define POKEDIAMOND_GLOBAL_FIELDMAP_H

struct MapHeader
{
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 mapsec;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17_0:4;
    u8 unk17_4:1;
    u8 unk17_5:1;
    u8 unk17_6:1;
    u8 unk17_7:1;
};

#endif //POKEDIAMOND_GLOBAL_FIELDMAP_H
