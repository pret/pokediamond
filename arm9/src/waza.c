#include "global.h"
#include "move_data.h"
#include "filesystem.h"
#include "constants/moves.h"

#pragma thumb on

void LoadWazaEntry(u16 waza, struct WazaTbl * dest);

// Effectively reads the entirety of the waza_tbl.narc file image.
// Even though each "file" is only 16 bytes, they are arranged
// contiguously and in the correct order.
void LoadAllWazaTbl(struct WazaTbl * dest)
{
    ReadFromNarcMemberByIdPair(dest, NARC_POKETOOL_WAZA_WAZA_TBL, 0, 0, (NUM_MOVES + 1) * sizeof(struct WazaTbl));
}

u32 GetWazaAttr(u16 waza, u32 attr)
{
    struct WazaTbl wazaTbl;
    LoadWazaEntry(waza, &wazaTbl);
    return GetAttrFromWazaTbl(&wazaTbl, attr);
}

u8 WazaGetMaxPp(u16 waza, u8 ppUp)
{
    u8 pp;
    if (ppUp > 3)
        ppUp = 3;
    pp = GetWazaAttr(waza, 5);
    return pp + (pp * 20 * ppUp) / 100;
}

u32 GetAttrFromWazaTbl(struct WazaTbl * wazaTbl, u32 attr)
{
    switch (attr)
    {
    case 0:
        return wazaTbl->unk0;
    case 1:
        return wazaTbl->unk2;
    case 2:
        return wazaTbl->unk3;
    case 3:
        return wazaTbl->unk4;
    case 4:
        return wazaTbl->unk5;
    case 5:
        return wazaTbl->pp;
    case 6:
        return wazaTbl->unk7;
    case 7:
        return wazaTbl->unk8;
    case 8:
        return wazaTbl->unkA;
    case 9:
        return wazaTbl->unkB;
    case 10:
        return wazaTbl->unkC;
    case 11:
        return wazaTbl->unkD;
    }
}

void LoadWazaEntry(u16 waza, struct WazaTbl * wazaTbl)
{
    ReadWholeNarcMemberByIdPair(wazaTbl, NARC_POKETOOL_WAZA_WAZA_TBL, waza);
}
