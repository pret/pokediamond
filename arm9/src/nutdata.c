//TODO: RENAME THIS ENTIRE FILE - WE SHOULD NOT BE USING NUT

#include "global.h"
#include "filesystem.h"
#include "nutdata.h"
#include "msgdata.h"
#include "constants/items.h"

#pragma thumb on

NARC * OpenNutsDataNarc(u32 heap_id)
{
    return NARC_New(NARC_ITEMTOOL_ITEMDATA_NUTS_DATA, heap_id);
}

struct NutData * ReadNutDataFromNarc(NARC * narc, u32 berry_idx, u32 heap_id)
{
    return NARC_AllocAndReadWholeMember(narc, berry_idx, heap_id);
}

void CloseNutsDataNarc(NARC * narc)
{
    NARC_Delete(narc);
}

struct NutData * LoadNutDataSingle(s32 berry_idx, u32 heap_id)
{
    return AllocAndReadWholeNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_NUTS_DATA, berry_idx, heap_id);
}

struct NutData * LoadNutDataSingleByItemId(s32 item_id, u32 heap_id)
{
    return LoadNutDataSingle(item_id - FIRST_BERRY_IDX, heap_id);
}

u32 GetNutAttr(struct NutData * nut, u32 attr)
{
    switch (attr)
    {
    case 0:
        return nut->size;
    case 1:
        return nut->firmness;
    case 2:
        return nut->yieldCategory;
    case 3:
        return nut->stageDuration;
    case 4:
        return nut->unk5;
    case 5:
        return nut->spicy;
    case 6:
        return nut->dry;
    case 7:
        return nut->sweet;
    case 8:
        return nut->bitter;
    case 9:
        return nut->sour;
    case 10:
        return nut->smoothness;
    default:
        return 0;
    }
}

struct String * GetNutName(u32 berry_idx, u32 heap_id)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 373, heap_id);
    struct String * ret = NewString_ReadMsgData(msgData, berry_idx);
    DestroyMsgData(msgData);
    return ret;
}

struct String * GetNutDesc(u32 berry_idx, u32 heap_id)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 372, heap_id);
    struct String * ret = NewString_ReadMsgData(msgData, berry_idx);
    DestroyMsgData(msgData);
    return ret;
}
