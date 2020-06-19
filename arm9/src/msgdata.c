#include "global.h"
#include "filesystem.h"
#include "msg_data.h"
#include "heap.h"

#pragma thumb on

void * LoadSingleElementFromNarc(NarcId narc_id, s32 file_id, u32 heap_id);
void FreeMsgDataRawData(void * data);
void CopyEncryptedMessage16(u16 * dest, const u16 * src, struct UnkStruct_200A394_4 * param);
void DecryptMessageDirect(struct UnkStruct_200A394 * r3, u32 r5, u16 * r4);

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
    u16 seed = (arg2 + 1) * 596947;

    while (count-- > 0)
    {
        *arg0 ^= seed;
        seed += 18749;
        arg0++;
    }
}

void DecryptMessageDirect(struct UnkStruct_200A394 * r3, u32 r5, u16 * r4)
{
    struct UnkStruct_200A394_4 sp0;

    if (r5 < r3->unk0)
    {
        sp0 = r3->unk4[r5];
        Decrypt1(&sp0, r5, r3->unk2);

        CopyEncryptedMessage16(r4, (const u16 *)((u8 *)r3 + sp0.unk0), &sp0);
        Decrypt2(r4, sp0.unk4, r5);
    }
    else
    {
        GF_ASSERT(0);
    }
}
