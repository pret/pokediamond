#ifndef POKEDIAMOND_MSG_DATA_H
#define POKEDIAMOND_MSG_DATA_H

#include "filesystem.h"
#include "message_format.h"
#include "string16.h"

typedef enum MsgDataLoadType {
    MSGDATA_LOAD_DIRECT,
    MSGDATA_LOAD_LAZY,
} MsgDataLoadType;

struct MsgDataAlloc
{
    u32 offset;
    u32 length;
};

struct MsgDataTable
{
    u16 count;
    u16 key;
    struct MsgDataAlloc alloc[1];
};

typedef struct MsgData
{
    u16 type;
    u16 heapId;
    u16 narc_id;
    u16 file_id;
    union {
        struct MsgDataTable * raw;
        NARC * narc;
    } data;
} MsgData;

void ReadMsgData_NewNarc_ExistingString(NarcId narc_id, u32 group, u32 num, HeapID heapId, struct String * dest);
struct MsgData * NewMsgDataFromNarc(MsgDataLoadType type, NarcId narcId, s32 msgId, HeapID heapId);
void DestroyMsgData(struct MsgData *);
struct String * ReadMsgData_NewNarc_NewString(NarcId narc_id, u32 group, u32 num, HeapID heapId);
void ReadMsgDataIntoString(struct MsgData * msgData, u32 msg_no, struct String * dest);
struct String * NewString_ReadMsgData(struct MsgData *, u32);
u16 MsgDataGetCount(struct MsgData * msgData);
void ReadMsgDataIntoU16Array(struct MsgData * msgData, u32 msg_no, u16 * dest);
void GetSpeciesNameIntoArray(u16 species, HeapID heapId, u16 * dest);
struct String * ReadMsgData_ExpandPlaceholders(MessageFormat *messageFormat, struct MsgData * msgData, u32 msgno, HeapID heapId);
struct String * GetMoveName(u32 move, HeapID heapId);
struct String * GetSpeciesName(u16 species, HeapID heapId);

#endif //POKEDIAMOND_MSG_DATA_H
