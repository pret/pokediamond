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

u32 GetWazaAttr(u16 waza, MoveAttr attr)
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
    pp = (u8)GetWazaAttr(waza, MOVEATTR_PP);
    return (u8)(pp + (pp * 20 * ppUp) / 100);
}

u32 GetAttrFromWazaTbl(struct WazaTbl * wazaTbl, MoveAttr attr)
{
    switch (attr)
    {
    case MOVEATTR_EFFECT:
        return wazaTbl->effect;
    case MOVEATTR_CLASS:
        return wazaTbl->class;
    case MOVEATTR_POWER:
        return wazaTbl->power;
    case MOVEATTR_TYPE:
        return wazaTbl->type;
    case MOVEATTR_ACCURACY:
        return wazaTbl->accuracy;
    case MOVEATTR_PP:
        return wazaTbl->pp;
    case MOVEATTR_EFFECT_CHANCE:
        return wazaTbl->effectChance;
    case MOVEATTR_UNK7:
        return wazaTbl->unk8;
    case MOVEATTR_PRIORTY:
        return wazaTbl->priority;
    case MOVEATTR_UNK9:
        return wazaTbl->unkB;
    case MOVEATTR_UNK10:
        return wazaTbl->unkC;
    case MOVEATTR_CONTEST_TYPE:
        return wazaTbl->contestType;
    default:
        return (u32)wazaTbl;
    }
}

void LoadWazaEntry(u16 waza, struct WazaTbl * wazaTbl)
{
    ReadWholeNarcMemberByIdPair(wazaTbl, NARC_POKETOOL_WAZA_WAZA_TBL, waza);
}
