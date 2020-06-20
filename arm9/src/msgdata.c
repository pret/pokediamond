#include "global.h"
#include "filesystem.h"
#include "msg_data.h"
#include "heap.h"
#include "MI_memory.h"
#include "string16.h"
#include "proto.h"

#pragma thumb on

void * LoadSingleElementFromNarc(NarcId narc_id, s32 file_id, u32 heap_id);
void FreeMsgDataRawData(void * data);
void CopyEncryptedMessage16(u16 * dest, const u16 * src, struct UnkStruct_200A394_4 * param);
void DecryptMessageDirect(struct UnkStruct_200A394 * r3, u32 r5, u16 * r4);
void DecryptMessageViaNewNarcHandle(NarcId narc_id, u32 group, u32 num, u32 heap_id, u16 * dest);
void FUN_0200A4D4(struct UnkStruct_200A394 * r5, u32 r4, struct String * dest);
struct String * FUN_0200A584(struct UnkStruct_200A394 * r5, u32 r4, u32 heap_id);
void FUN_0200A648(NarcId narc_id, u32 group, u32 num, u32 heap_id, struct String * dest);
void FUN_0200A670(NARC * narc, u32 group, u32 num, u32 heap_id, struct String * dest);
struct String * FUN_0200A738(NarcId narc_id, u32 group, u32 num, u32 heap_id);
struct String * FUN_0200A76C(NARC * narc, u32 group, u32 num, u32 heap_id);
u16 FUN_0200A848(struct UnkStruct_200A394 * tbl);
u16 FUN_0200A84C(NarcId narc_id, s32 file_id);

void * LoadSingleElementFromNarc(NarcId narc_id, s32 file_id, u32 heap_id)
{
    return AllocAndReadWholeNarcMemberByIdPair(narc_id, file_id, heap_id);
}

void FreeMsgDataRawData(void * data)
{
    FreeToHeap(data);
}

inline static void Decrypt1(struct UnkStruct_200A394_4 * arg0, u32 arg1, u32 seed)
{
    seed = seed * 765 * (arg1 + 1) & 0xffff;
    seed |= seed << 16;
    arg0->unk0 ^= seed;
    arg0->unk4 ^= seed;
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

void DecryptMessageDirect(struct UnkStruct_200A394 * table, u32 num, u16 * dest)
{
    struct UnkStruct_200A394_4 sp0;

    if (num < table->unk0)
    {
        sp0 = table->unk4[num];
        Decrypt1(&sp0, num, table->unk2);

        CopyEncryptedMessage16(dest, (const u16 *)((u8 *)table + sp0.unk0), &sp0);
        Decrypt2(dest, sp0.unk4, num);
    }
    else
    {
        GF_ASSERT(0);
    }
}

void DecryptMessageViaNewNarcHandle(NarcId narc_id, u32 group, u32 num, u32 heap_id, u16 * dest)
{
    NARC * narc = NARC_ctor(narc_id, heap_id);
    u16 spC[2];
    struct UnkStruct_200A394_4 sp4;
    if (narc != NULL)
    {
        NARC_ReadFromMember(narc, group, 0, 4, spC);
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &sp4);
        Decrypt1(&sp4, num, spC[1]);
        NARC_ReadFromMember(narc, group, sp4.unk0, 2 * sp4.unk4, dest);
        Decrypt2(dest, sp4.unk4, num);
        NARC_dtor(narc);
    }
}

void CopyEncryptedMessage16(u16 * dest, const u16 * src, struct UnkStruct_200A394_4 * param)
{
    MI_CpuCopy16(src, dest, 2 * param->unk4);
}

void FUN_0200A4D4(struct UnkStruct_200A394 * table, u32 num, struct String * dest)
{
    struct UnkStruct_200A394_4 sp4;
    u16 * buf;
    if (num < table->unk0)
    {
        sp4 = table->unk4[num];
        Decrypt1(&sp4, num, table->unk2);
        buf = AllocFromHeapAtEnd(0, 2 * sp4.unk4);
        if (buf != NULL)
        {
            MI_CpuCopy16((char *)table + sp4.unk0, buf, 2 * sp4.unk4);
            Decrypt2(buf, sp4.unk4, num);
            FUN_02021E8C(dest, buf, sp4.unk4);
            FreeToHeap(buf);
        }
    }
    else
    {
        GF_ASSERT(0);
        FUN_02021A4C(dest);
    }
}

struct String * FUN_0200A584(struct UnkStruct_200A394 * table, u32 num, u32 heap_id)
{
    struct UnkStruct_200A394_4 sp4;
    u16 * buf;
    struct String * dest;
    if (num < table->unk0)
    {
        sp4 = table->unk4[num];
        Decrypt1(&sp4, num, table->unk2);
        buf = AllocFromHeapAtEnd(heap_id, 2 * sp4.unk4);
        if (buf != NULL)
        {
            MI_CpuCopy16((char *)table + sp4.unk0, buf, 2 * sp4.unk4);
            Decrypt2(buf, sp4.unk4, num);
            dest = FUN_020219F4(sp4.unk4, heap_id);
            if (dest != NULL)
                FUN_02021E8C(dest, buf, sp4.unk4);
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
        GF_ASSERT(0);
        return FUN_020219F4(4, heap_id);
    }
}

void FUN_0200A648(NarcId narc_id, u32 group, u32 num, u32 heap_id, struct String * dest)
{
    NARC * narc = NARC_ctor(narc_id, heap_id);
    if (narc != NULL)
    {
        FUN_0200A670(narc, group, num, heap_id, dest);
        NARC_dtor(narc);
    }
}

void FUN_0200A670(NARC * narc, u32 group, u32 num, u32 heap_id, struct String * dest)
{
    u16 * buf;
    u32 size;
    u16 sp10[2];
    struct UnkStruct_200A394_4 sp8;

    NARC_ReadFromMember(narc, group, 0, 4, sp10);
    if (num < sp10[0])
    {
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &sp8);
        Decrypt1(&sp8, num, sp10[1]);
        size = sp8.unk4 * 2;
        buf = AllocFromHeapAtEnd(heap_id, size);
        if (buf != NULL)
        {
            NARC_ReadFromMember(narc, group, sp8.unk0, size, buf);
            Decrypt2(buf, sp8.unk4, num);
            FUN_02021E8C(dest, buf, sp8.unk4);
            FreeToHeap(buf);
            return;
        }
    }
    else
    {
        GF_ASSERT(0);
        FUN_02021A4C(dest);
    }
}

struct String * FUN_0200A738(NarcId narc_id, u32 group, u32 num, u32 heap_id)
{
    NARC * narc = NARC_ctor(narc_id, heap_id);
    struct String * string;
    if (narc != NULL)
    {
        string = FUN_0200A76C(narc, group, num, heap_id);
        NARC_dtor(narc);
    }
    else
    {
        string = FUN_020219F4(4, heap_id);
    }
    return string;
}

struct String * FUN_0200A76C(NARC * narc, u32 group, u32 num, u32 heap_id)
{
    struct String * dest;
    u16 * buf;
    u32 size;
    u16 sp10[2];
    struct UnkStruct_200A394_4 sp8;

    NARC_ReadFromMember(narc, group, 0, 4, sp10);
    if (num < sp10[0])
    {
        NARC_ReadFromMember(narc, group, 8 * num + 4, 8, &sp8);
        Decrypt1(&sp8, num, sp10[1]);
        dest = FUN_020219F4(sp8.unk4, heap_id);
        if (dest != NULL)
        {
            size = sp8.unk4 * 2;
            buf = AllocFromHeapAtEnd(heap_id, size);
            if (buf != NULL)
            {
                NARC_ReadFromMember(narc, group, sp8.unk0, size, buf);
                Decrypt2(buf, sp8.unk4, num);
                FUN_02021E8C(dest, buf, sp8.unk4);
                FreeToHeap(buf);
            }
        }
        return dest;
    }
    else
    {
        GF_ASSERT(0);
        return FUN_020219F4(4, heap_id);
    }
}

u16 FUN_0200A848(struct UnkStruct_200A394 * tbl)
{
    return tbl->unk0;
}

u16 FUN_0200A84C(NarcId narc_id, s32 file_id)
{
    u16 n[2];
    ReadFromNarcMemberByIdPair(&n, narc_id, file_id, 0, 4);
    return n[0];
}

struct MsgData * NewMsgDataFromNarc(u32 type, NarcId narc_id, s32 file_id, u32 heap_id)
{
    struct MsgData * msgData = AllocFromHeapAtEnd(heap_id, sizeof(struct MsgData));
    if (msgData != NULL)
    {
        if (type == 0)
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
            msgData->data.narc = NARC_ctor(narc_id, heap_id);
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
        case 0:
            FreeMsgDataRawData(msgData->data.raw);
            break;
        case 1:
            NARC_dtor(msgData->data.narc);
            break;
        }
        FreeToHeap(msgData);
    }
}

void FUN_0200A8E0(struct MsgData * msgData, u32 msg_no, struct String * dest)
{
    switch (msgData->type)
    {
    case 0:
        FUN_0200A4D4(msgData->data.raw, msg_no, dest);
        break;
    case 1:
        FUN_0200A670(msgData->data.narc, msgData->file_id, msg_no, msgData->heap_id, dest);
        break;
    }
}

struct String * FUN_0200A914(struct MsgData * msgData, u32 msg_no)
{
    switch (msgData->type)
    {
    case 0:
        return FUN_0200A584(msgData->data.raw, msg_no, msgData->heap_id);
    case 1:
        return FUN_0200A76C(msgData->data.narc, msgData->file_id, msg_no, msgData->heap_id);
    default:
        return NULL;
    }
}

u16 FUN_0200A940(struct MsgData * msgData)
{
    switch (msgData->type)
    {
    case 0:
        return FUN_0200A848(msgData->data.raw);
    case 1:
        return FUN_0200A84C((NarcId)msgData->narc_id, msgData->file_id);
    default:
        return 0;
    }
}

void DecryptCopyString(struct MsgData * msgData, u32 msg_no, u16 * dest)
{
    switch (msgData->type)
    {
    case 0:
        DecryptMessageDirect(msgData->data.raw, msg_no, dest);
        break;
    case 1:
        DecryptMessageViaNewNarcHandle((NarcId)msgData->narc_id, msgData->file_id, msg_no, msgData->heap_id, dest);
        break;
    }
}

void GetSpeciesName(u16 species, u32 heap_id, u16 * dest)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 362, heap_id);
    DecryptCopyString(msgData, species, dest);
    DestroyMsgData(msgData);
}

struct String * FUN_0200A9C4(u32 * a0, struct MsgData * msgData, u32 msgno, struct String * a3)
{
    struct String * ret = NULL;
    struct String * r4 = FUN_020219F4(1024, 0);
    struct String * r5;
    if (r4 != NULL)
    {
        r5 = FUN_0200A914(msgData, msgno);
        if (r5 != NULL)
        {
            FUN_0200B7B8(a0, r4, r5);
            ret = FUN_02021ACC(r4, a3);
            FUN_02021A20(r5);
        }
        FUN_02021A20(r4);
    }
    return ret;
}

struct String * FUN_0200AA14(u32 msg_no, u32 heapno)
{
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 588, heapno);
    struct String * ret;
    if (msgData != NULL)
    {
        ret = FUN_020219F4(16, heapno);
        if (ret != NULL)
        {
            FUN_0200A8E0(msgData, msg_no, ret);
        }
        DestroyMsgData(msgData);
        return ret;
    }
    return NULL;
}

struct String * FUN_0200AA50(u16 species, u32 heap_id)
{
    struct String * ret;
    struct MsgData * msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 362, heap_id);
    if (msgData != NULL)
    {
        ret = FUN_0200A914(msgData, species);
        DestroyMsgData(msgData);
        return ret;
    }
    return NULL;
}
