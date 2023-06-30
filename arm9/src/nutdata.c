//TODO: RENAME THIS ENTIRE FILE - WE SHOULD NOT BE USING NUT

#include "global.h"
#include "filesystem.h"
#include "nutdata.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "constants/items.h"

NARC * OpenNutsDataNarc(HeapID heapId)
{
    return NARC_New(NARC_ITEMTOOL_ITEMDATA_NUTS_DATA, heapId);
}

struct NutData * ReadNutDataFromNarc(NARC * narc, u32 berry_idx, HeapID heapId)
{
    return NARC_AllocAndReadWholeMember(narc, berry_idx, heapId);
}

void CloseNutsDataNarc(NARC * narc)
{
    NARC_Delete(narc);
}

struct NutData * LoadNutDataSingle(s32 berry_idx, HeapID heapId)
{
    return AllocAndReadWholeNarcMemberByIdPair(NARC_ITEMTOOL_ITEMDATA_NUTS_DATA, berry_idx, heapId);
}

struct NutData * LoadNutDataSingleByItemId(s32 item_id, HeapID heapId)
{
    return LoadNutDataSingle(item_id - FIRST_BERRY_IDX, heapId);
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

struct String * GetNutName(u32 berry_idx, HeapID heapId)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0373_bin, heapId);
    struct String * ret = NewString_ReadMsgData(msgData, berry_idx);
    DestroyMsgData(msgData);
    return ret;
}

struct String * GetNutDesc(u32 berry_idx, HeapID heapId)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0372_bin, heapId);
    struct String * ret = NewString_ReadMsgData(msgData, berry_idx);
    DestroyMsgData(msgData);
    return ret;
}
