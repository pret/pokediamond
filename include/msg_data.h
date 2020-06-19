#ifndef POKEDIAMOND_MSG_DATA_H
#define POKEDIAMOND_MSG_DATA_H

struct MsgData
{
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        u16 * raw;
        NARC * narc;
    } data;
};

struct MsgData * NewMsgDataFromNarc(u32 type, u32 narcId, u32 msgId, u32 heapno);
u16 * FUN_0200A914(struct MsgData *, u32);
void DestroyMsgData(struct MsgData *);

#endif //POKEDIAMOND_MSG_DATA_H
