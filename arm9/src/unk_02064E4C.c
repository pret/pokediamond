#include "global.h"
#include "map_header.h"
#include "unk_02064E4C.h"

#pragma thumb on

// TODO: types of a0 and a2 aren't known yet
extern void FUN_02002E14(void * a0, struct String * str, void * a2);

void FUN_02064E4C(struct MsgData * msgData, u16 map_sec, struct String * dest)
{
    ReadMsgDataIntoString(msgData, map_sec, dest);
    FUN_02002E14(0, dest, 0);
}

void FUN_02064E60(u32 map_no, u32 heap_id, struct String * dest)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 382, heap_id);
    u16 map_sec = FUN_02034824(map_no);

    FUN_02064E4C(msgData, map_sec, dest);

    DestroyMsgData(msgData);
}
