#include "global.h"
#include "MI_memory.h"
#include "heap.h"
#include "sav_chatot.h"

THUMB_FUNC u32 Sav2_Chatot_sizeof(void)
{
    return sizeof(struct SaveChatotSoundClip);
}

THUMB_FUNC void Sav2_Chatot_init(struct SaveChatotSoundClip * chatot)
{
    MI_CpuClear32(chatot, sizeof(struct SaveChatotSoundClip));
    chatot->exists = FALSE;
}

THUMB_FUNC struct SaveChatotSoundClip * Chatot_new(u32 heap_id)
{
    struct SaveChatotSoundClip * ret = (struct SaveChatotSoundClip *)AllocFromHeap(heap_id, sizeof(struct SaveChatotSoundClip));
    Sav2_Chatot_init(ret);
    return ret;
}

THUMB_FUNC struct SaveChatotSoundClip * Sav2_Chatot_get(struct SaveBlock2 * sav2)
{
    return (struct SaveChatotSoundClip *) SavArray_get(sav2, 22);
}

THUMB_FUNC BOOL Chatot_exists(struct SaveChatotSoundClip * chatot)
{
    return chatot->exists;
}

THUMB_FUNC void Chatot_invalidate(struct SaveChatotSoundClip * chatot)
{
    chatot->exists = FALSE;
}

THUMB_FUNC s8 * Chatot_GetData(struct SaveChatotSoundClip * chatot)
{
    return chatot->data;
}

static inline s8 transform(u8 value)
{
    return (s8)(value - 8);
}

THUMB_FUNC void Chatot_Decode(s8 * dest, const s8 * data)
{
    s32 i;
    s32 dest_i;
    u8 val;
    s8 val2;

    for (dest_i = 0, i = 0; i < 1000; i++, dest_i += 2)
    {
        val = (u8)(data[i] & 0xF);
        val2 = transform(val);
        dest[dest_i + 0] = (s8)(val2 << 4);
        val = (u8)(data[i] >> 4);
        val2 = transform(val);
        dest[dest_i + 1] = (s8)(val2 << 4);
    }
}

static inline u8 untransform(s8 val)
{
    val /= 16;
    return (u8)(val + 8);
}

THUMB_FUNC void Chatot_Encode(struct SaveChatotSoundClip * chatot, const s8 * data)
{
    s32 src_i;
    s32 i = 0;
    u8 val2;
    s8 val;
    chatot->exists = TRUE;

    for (src_i = 0; src_i < 2000; src_i += 2)
    {
        val = data[src_i + 0];
        val2 = untransform(val);
        chatot->data[i] = (s8)val2;

        val = data[src_i + 1];
        val2 = untransform(val);
        chatot->data[i] |= val2 << 4;

        i++;
    }
}

THUMB_FUNC void Chatot_copy(struct SaveChatotSoundClip * dest, const struct SaveChatotSoundClip * src)
{
    MI_CpuCopyFast(src, dest, sizeof(struct SaveChatotSoundClip));
}
