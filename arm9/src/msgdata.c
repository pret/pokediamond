#include "global.h"
#include "filesystem.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "heap.h"
#include "MI_memory.h"
#include "string16.h"

static void * LoadSingleElementFromNarc(NarcId narc_id, s32 file_id, u32 heap_id);
static void FreeMsgDataRawData(void * data);
static void ReadMsgData_ExistingTable_ExistingArray(struct MsgDataTable * table, u32 num, u16 * dest);
static void ReadMsgData_NewNarc_ExistingArray(NarcId narc_id, u32 group, u32 num, u32 heap_id, u16 * dest);
static void CopyEncryptedMessage16(u16 * dest, const u16 * src, struct MsgDataAlloc * param);
static void ReadMsgData_ExistingTable_ExistingString(struct MsgDataTable * table, u32 num, struct String * dest);
static struct String * ReadMsgData_ExistingTable_NewString(struct MsgDataTable * table, u32 num, u32 heap_id);
static void ReadMsgData_ExistingNarc_ExistingString(NARC * narc, u32 group, u32 num, u32 heap_id, struct String * dest);
static struct String * ReadMsgData_ExistingNarc_NewString(NARC * narc, u32 group, u32 num, u32 heap_id);
static u16 GetMsgCount_ExistingTable(struct MsgDataTable * tbl);
static u16 GetMsgCount_TableFromNarc(NarcId narc_id, s32 file_id);

static void * LoadSingleElementFromNarc(NarcId narc_id, s32 file_id, u32 heap_id)
{
    return AllocAndReadWholeNarcMemberByIdPair(narc_id, file_id, heap_id);
}

static void FreeMsgDataRawData(void * data)
{
    FreeToHeap(data);
}

inline static void Decrypt1(struct MsgDataAlloc * arg0, u32 arg1, u32 seed)
{
    seed = seed * 765 * (arg1 + 1) & 0xffff;
    seed |= seed << 16;
    arg0->offset ^= seed;
    arg0->length ^= seed;
}

inline static void Decrypt2(u16 * arg0, u32 count, u32 arg2)
{
    u16 seed = (u16)((arg2 + 1) * 596947);

    while (count-- > 0)
    {
        *arg0 ^= seed;
        arg0++;
        seed += 18749;
    }
}

static void ReadMsgData_ExistingTable_ExistingArray(struct MsgDataTable * table, u32 num, u16 * dest)
{
    struct MsgDataAlloc sp0;

    if (num < table->count)
    {
        sp0 = table->alloc[num];
        Decrypt1(&sp0, num, table->key);

        CopyEncryptedMessage16(dest, (const u16 *)((u8 *)table + sp0.offset), &sp0);
        Decrypt2(dest, sp0.length, num);
    }
    else
    {
        GF_ASSERT(FALSE);
    }
}

static void ReadMsgData_NewNarc_ExistingArray(NarcId narc_id, u32 group, u32 num, u32 heap_id, u16 * dest)
{
    NARC * narc = NARC_New(narc_id, heap_id);
    u16 header[2];
    struct MsgDataAlloc alloc;
    if (narc != NULL)
    {
        NARC_ReadFromMember(narc, group, 0, 4, header);
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &alloc);
        Decrypt1(&alloc, num, header[1]);
        NARC_ReadFromMember(narc, group, alloc.offset, 2 * alloc.length, dest);
        Decrypt2(dest, alloc.length, num);
        NARC_Delete(narc);
    }
}

static void CopyEncryptedMessage16(u16 * dest, const u16 * src, struct MsgDataAlloc * param)
{
    MI_CpuCopy16(src, dest, 2 * param->length);
}

static void ReadMsgData_ExistingTable_ExistingString(struct MsgDataTable * table, u32 num, struct String * dest)
{
    struct MsgDataAlloc alloc;
    u16 * buf;
    if (num < table->count)
    {
        alloc = table->alloc[num];
        Decrypt1(&alloc, num, table->key);
        buf = AllocFromHeapAtEnd(0, 2 * alloc.length);
        if (buf != NULL)
        {
            MI_CpuCopy16((char *)table + alloc.offset, buf, 2 * alloc.length);
            Decrypt2(buf, alloc.length, num);
            CopyU16ArrayToStringN(dest, buf, alloc.length);
            FreeToHeap(buf);
        }
    }
    else
    {
        GF_ASSERT(FALSE);
        StringSetEmpty(dest);
    }
}

static struct String * ReadMsgData_ExistingTable_NewString(struct MsgDataTable * table, u32 num, u32 heap_id)
{
    struct MsgDataAlloc alloc;
    u16 * buf;
    struct String * dest;
    if (num < table->count)
    {
        alloc = table->alloc[num];
        Decrypt1(&alloc, num, table->key);
        buf = AllocFromHeapAtEnd(heap_id, 2 * alloc.length);
        if (buf != NULL)
        {
            MI_CpuCopy16((char *)table + alloc.offset, buf, 2 * alloc.length);
            Decrypt2(buf, alloc.length, num);
            dest = String_New(alloc.length, heap_id);
            if (dest != NULL)
                CopyU16ArrayToStringN(dest, buf, alloc.length);
            FreeToHeap(buf);
            return dest;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        GF_ASSERT(FALSE);
        return String_New(4, heap_id);
    }
}

void ReadMsgData_NewNarc_ExistingString(NarcId narc_id, u32 group, u32 num, u32 heap_id, struct String * dest)
{
    NARC * narc = NARC_New(narc_id, heap_id);
    if (narc != NULL)
    {
        ReadMsgData_ExistingNarc_ExistingString(narc, group, num, heap_id, dest);
        NARC_Delete(narc);
    }
}

static void ReadMsgData_ExistingNarc_ExistingString(NARC * narc, u32 group, u32 num, u32 heap_id, struct String * dest)
{
    u16 * buf;
    u32 size;
    u16 sp10[2];
    struct MsgDataAlloc alloc;

    NARC_ReadFromMember(narc, group, 0, 4, sp10);
    if (num < sp10[0])
    {
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &alloc);
        Decrypt1(&alloc, num, sp10[1]);
        size = alloc.length * 2;
        buf = AllocFromHeapAtEnd(heap_id, size);
        if (buf != NULL)
        {
            NARC_ReadFromMember(narc, group, alloc.offset, size, buf);
            Decrypt2(buf, alloc.length, num);
            CopyU16ArrayToStringN(dest, buf, alloc.length);
            FreeToHeap(buf);
            return;
        }
    }
    else
    {
        GF_ASSERT(FALSE);
        StringSetEmpty(dest);
    }
}

struct String * ReadMsgData_NewNarc_NewString(NarcId narc_id, u32 group, u32 num, u32 heap_id)
{
    NARC * narc = NARC_New(narc_id, heap_id);
    struct String * string;
    if (narc != NULL)
    {
        string = ReadMsgData_ExistingNarc_NewString(narc, group, num, heap_id);
        NARC_Delete(narc);
    }
    else
    {
        string = String_New(4, heap_id);
    }
    return string;
}

static struct String * ReadMsgData_ExistingNarc_NewString(NARC * narc, u32 group, u32 num, u32 heap_id)
{
    struct String * dest;
    u16 * buf;
    u32 size;
    u16 sp10[2];
    struct MsgDataAlloc alloc;

    NARC_ReadFromMember(narc, group, 0, 4, sp10);
    if (num < sp10[0])
    {
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &alloc);
        Decrypt1(&alloc, num, sp10[1]);
        dest = String_New(alloc.length, heap_id);
        if (dest != NULL)
        {
            size = alloc.length * 2;
            buf = AllocFromHeapAtEnd(heap_id, size);
            if (buf != NULL)
            {
                NARC_ReadFromMember(narc, group, alloc.offset, size, buf);
                Decrypt2(buf, alloc.length, num);
                CopyU16ArrayToStringN(dest, buf, alloc.length);
                FreeToHeap(buf);
            }
        }
        return dest;
    }
    else
    {
        GF_ASSERT(FALSE);
        return String_New(4, heap_id);
    }
}

static u16 GetMsgCount_ExistingTable(struct MsgDataTable * tbl)
{
    return tbl->count;
}

static u16 GetMsgCount_TableFromNarc(NarcId narc_id, s32 file_id)
{
    u16 n[2];
    ReadFromNarcMemberByIdPair(&n, narc_id, file_id, 0, 4);
    return n[0];
}

struct MsgData * NewMsgDataFromNarc(MsgDataLoadType type, NarcId narc_id, s32 file_id, u32 heap_id)
{
    struct MsgData * msgData = AllocFromHeapAtEnd(heap_id, sizeof(struct MsgData));
    if (msgData != NULL)
    {
        if (type == MSGDATA_LOAD_DIRECT)
        {
            msgData->data.raw = LoadSingleElementFromNarc(narc_id, file_id, heap_id);
            if (msgData->data.raw == NULL)
            {
                FreeToHeap(msgData);
                return NULL;
            }
        }
        else
        {
            msgData->data.narc = NARC_New(narc_id, heap_id);
        }
        msgData->type = (u16)type;
        msgData->narc_id = (u16)narc_id;
        msgData->file_id = (u16)file_id;
        msgData->heap_id = (u16)heap_id;
    }
    return msgData;
}

void DestroyMsgData(struct MsgData * msgData)
{
    if (msgData != NULL)
    {
        switch (msgData->type)
        {
        case MSGDATA_LOAD_DIRECT:
            FreeMsgDataRawData(msgData->data.raw);
            break;
        case MSGDATA_LOAD_LAZY:
            NARC_Delete(msgData->data.narc);
            break;
        }
        FreeToHeap(msgData);
    }
}

void ReadMsgDataIntoString(struct MsgData * msgData, u32 msg_no, struct String * dest)
{
    switch (msgData->type)
    {
    case MSGDATA_LOAD_DIRECT:
        ReadMsgData_ExistingTable_ExistingString(msgData->data.raw, msg_no, dest);
        break;
    case MSGDATA_LOAD_LAZY:
        ReadMsgData_ExistingNarc_ExistingString(msgData->data.narc, msgData->file_id, msg_no, msgData->heap_id, dest);
        break;
    }
}

struct String * NewString_ReadMsgData(struct MsgData * msgData, u32 msg_no)
{
    switch (msgData->type)
    {
    case MSGDATA_LOAD_DIRECT:
        return ReadMsgData_ExistingTable_NewString(msgData->data.raw, msg_no, msgData->heap_id);
    case MSGDATA_LOAD_LAZY:
        return ReadMsgData_ExistingNarc_NewString(msgData->data.narc, msgData->file_id, msg_no, msgData->heap_id);
    default:
        return NULL;
    }
}

u16 MsgDataGetCount(struct MsgData * msgData)
{
    switch (msgData->type)
    {
    case MSGDATA_LOAD_DIRECT:
        return GetMsgCount_ExistingTable(msgData->data.raw);
    case MSGDATA_LOAD_LAZY:
        return GetMsgCount_TableFromNarc((NarcId)msgData->narc_id, msgData->file_id);
    default:
        return 0;
    }
}

void ReadMsgDataIntoU16Array(struct MsgData * msgData, u32 msg_no, u16 * dest)
{
    switch (msgData->type)
    {
    case MSGDATA_LOAD_DIRECT:
        ReadMsgData_ExistingTable_ExistingArray(msgData->data.raw, msg_no, dest);
        break;
    case MSGDATA_LOAD_LAZY:
        ReadMsgData_NewNarc_ExistingArray((NarcId)msgData->narc_id, msgData->file_id, msg_no, msgData->heap_id, dest);
        break;
    }
}

void GetSpeciesNameIntoArray(u16 species, u32 heap_id, u16 * dest)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 362, heap_id);
    ReadMsgDataIntoU16Array(msgData, species, dest);
    DestroyMsgData(msgData);
}

struct String * ReadMsgData_ExpandPlaceholders(MessageFormat *messageFormat, struct MsgData * msgData, u32 msgno, u32 heapId)
{
    struct String * ret = NULL;
    struct String * r4 = String_New(1024, 0);
    struct String * r5;
    if (r4 != NULL)
    {
        r5 = NewString_ReadMsgData(msgData, msgno);
        if (r5 != NULL)
        {
            StringExpandPlaceholders(messageFormat, r4, r5);
            ret = StringDup(r4, heapId);
            String_Delete(r5);
        }
        String_Delete(r4);
    }
    return ret;
}

struct String * GetMoveName(u32 move, u32 heapno)
{
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0588_bin, heapno);
    struct String * ret;
    if (msgData != NULL)
    {
        ret = String_New(16, heapno);
        if (ret != NULL)
        {
            ReadMsgDataIntoString(msgData, move, ret);
        }
        DestroyMsgData(msgData);
        return ret;
    }
    return NULL;
}

struct String * GetSpeciesName(u16 species, u32 heap_id)
{
    struct String * ret;
    struct MsgData * msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0362_bin, heap_id);
    if (msgData != NULL)
    {
        ret = NewString_ReadMsgData(msgData, species);
        DestroyMsgData(msgData);
        return ret;
    }
    return NULL;
}
