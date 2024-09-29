#include "unk_02064E4C.h"

#include "global.h"

#include "msgdata/msg.naix"

#include "font.h"
#include "map_header.h"
#include "msgdata.h"

void sub_02064E4C(struct MsgData *msgData, u16 map_sec, struct String *dest) {
    ReadMsgDataIntoString(msgData, map_sec, dest);
    sub_02002E14(0, dest, 0);
}

void sub_02064E60(u32 map_no, HeapID heapId, struct String *dest) {
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0382_bin, heapId);
    u16 map_sec             = MapHeader_GetMapSec(map_no);

    sub_02064E4C(msgData, map_sec, dest);

    DestroyMsgData(msgData);
}
