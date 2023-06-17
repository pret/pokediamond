#include "global.h"
#include "MI_memory.h"
#include "heap.h"
#include "sav_chatot.h"

u32 Save_Chatot_sizeof(void)
{
    return sizeof(struct SaveChatotSoundClip);
}

void Save_Chatot_Init(struct SaveChatotSoundClip * chatot)
{
    MI_CpuClear32(chatot, sizeof(struct SaveChatotSoundClip));
    chatot->exists = FALSE;
}

struct SaveChatotSoundClip * Chatot_New(u32 heap_id)
{
    struct SaveChatotSoundClip * ret = (struct SaveChatotSoundClip *)AllocFromHeap(heap_id, sizeof(struct SaveChatotSoundClip));
    Save_Chatot_Init(ret);
    return ret;
}

struct SaveChatotSoundClip * Save_Chatot_Get(struct SaveData * save)
{
    return (struct SaveChatotSoundClip *) SaveArray_Get(save, 22);
}

BOOL Chatot_Exists(struct SaveChatotSoundClip * chatot)
{
    return chatot->exists;
}

void Chatot_Invalidate(struct SaveChatotSoundClip * chatot)
{
    chatot->exists = FALSE;
}

s8 * Chatot_GetData(struct SaveChatotSoundClip * chatot)
{
    return chatot->data;
}

static inline s8 transform(u8 value)
{
    return (s8)(value - 8);
}

void Chatot_Decode(s8 * dest, const s8 * data)
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

void Chatot_Encode(struct SaveChatotSoundClip * chatot, const s8 * data)
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

void Chatot_Copy(struct SaveChatotSoundClip * dest, const struct SaveChatotSoundClip * src)
{
    MI_CpuCopyFast(src, dest, sizeof(struct SaveChatotSoundClip));
}
