#ifndef POKEDIAMOND_MAP_HEADER_H
#define POKEDIAMOND_MAP_HEADER_H

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

u8 FUN_02034724(u32 mapno);
u8 FUN_02034738(u32 mapno);
u16 FUN_0203474C(u32 mapno);
u16 MapHeader_GetMsgBank(u32 mapno);
u16 MapHeader_GetScrSeqReleaseNo(u32 mapno);
u16 FUN_0203479C(u32 mapno);
u16 FUN_020347B0(u32 mapno);
u16 FUN_020347C4(u32 mapno);
BOOL FUN_020347D8(u32 mapno);
u16 FUN_020347FC(u32 mapno);
u16 FUN_02034810(u32 mapno);
u16 FUN_02034824(u32 mapno);
u8 FUN_02034838(u32 mapno);
u8 FUN_0203484C(u32 mapno);
u8 FUN_02034860(u32 mapno);
u8 FUN_0203487C(u32 mapno);
u8 FUN_02034898(u32 mapno);
u8 FUN_020348B4(u32 mapno);
u8 FUN_020348D0(u32 mapno);
BOOL FUN_020348E4(u32 mapno);
BOOL FUN_02034908(u32 mapno);
BOOL FUN_0203491C(u32 mapno);
BOOL FUN_02034930(u32 mapno);
BOOL FUN_02034944(u32 mapno);
BOOL FUN_02034964(u32 mapno);
BOOL FUN_02034984(u32 mapno);
BOOL FUN_02034998(u32 mapno);
BOOL FUN_020349AC(u32 mapno);
BOOL FUN_020349B8(u32 mapno);
BOOL FUN_020349CC(u32 mapno);
BOOL FUN_020349D8(u32 mapno);
BOOL FUN_020349E4(u16 a0);
u16 FUN_02034A04(u16 a0);

#endif //POKEDIAMOND_MAP_HEADER_H
