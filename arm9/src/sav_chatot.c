#include "global.h"
#include "MI_memory.h"
#include "heap.h"
#include "save_block_2.h"

struct SaveChatotSoundClip
{
    // TODO: Fill this in
    BOOL exists;
    s8 data[1000];
};

THUMB_FUNC u32 FUN_02029EC4(void)
{
    return sizeof(struct SaveChatotSoundClip);
}

THUMB_FUNC void FUN_02029ECC(struct SaveChatotSoundClip * chatot)
{
    MIi_CpuClear32(0, chatot, sizeof(struct SaveChatotSoundClip));
    chatot->exists = FALSE;
}

THUMB_FUNC struct SaveChatotSoundClip * FUN_02029EE4(u32 heap_id)
{
    struct SaveChatotSoundClip * ret = (struct SaveChatotSoundClip *)AllocFromHeap(heap_id, sizeof(struct SaveChatotSoundClip));
    FUN_02029ECC(ret);
    return ret;
}

THUMB_FUNC struct SaveChatotSoundClip * FUN_02029EF8(struct SaveBlock2 * sav2)
{
    return (struct SaveChatotSoundClip *) SavArray_get(sav2, 22);
}

THUMB_FUNC u32 FUN_02029F04(struct SaveChatotSoundClip * chatot)
{
    return chatot->exists;
}

THUMB_FUNC void FUN_02029F08(struct SaveChatotSoundClip * chatot)
{
    chatot->exists = FALSE;
}

THUMB_FUNC s8 * FUN_02029F10(struct SaveChatotSoundClip * chatot)
{
    return chatot->data;
}
