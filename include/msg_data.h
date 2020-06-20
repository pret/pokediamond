#ifndef POKEDIAMOND_MSG_DATA_H
#define POKEDIAMOND_MSG_DATA_H

#include "string16.h"

struct UnkStruct_200A394_4
{
    u32 unk0;
    u32 unk4;
};

struct UnkStruct_200A394
{
    u16 unk0;
    u16 unk2;
    struct UnkStruct_200A394_4 unk4[1];
};

struct MsgData
{
    u16 type;
    u16 heap_id;
    u16 narc_id;
    u16 file_id;
    union {
        struct UnkStruct_200A394 * raw;
        NARC * narc;
    } data;
};

struct MsgData * NewMsgDataFromNarc(u32 type, NarcId narcId, s32 msgId, u32 heapno);
void DestroyMsgData(struct MsgData *);
void FUN_0200A8E0(struct MsgData * msgData, u32 msg_no, struct String * dest);
struct String * FUN_0200A914(struct MsgData *, u32);
u16 FUN_0200A940(struct MsgData * msgData);
void DecryptCopyString(struct MsgData * msgData, u32 msg_no, u16 * dest);
void GetSpeciesName(u16 species, u32 heap_id, u16 * dest);
struct String * FUN_0200A9C4(u32 * a0, struct MsgData * msgData, u32 msgno, struct String * a3);
struct String * FUN_0200AA14(u32 msg_no, u32 heapno);
struct String * FUN_0200AA50(u16 species, u32 heap_id);

#endif //POKEDIAMOND_MSG_DATA_H
