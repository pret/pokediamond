#ifndef POKEDIAMOND_SAV_CHATOT_H
#define POKEDIAMOND_SAV_CHATOT_H

#include "save_block_2.h"

struct SaveChatotSoundClip
{
    // TODO: Fill this in
    BOOL exists;
    s8 data[1000];
};

u32 Sav2_Chatot_sizeof(void);
void Sav2_Chatot_init(struct SaveChatotSoundClip * chatot);
struct SaveChatotSoundClip * Chatot_new(u32 heap_id);
struct SaveChatotSoundClip * Sav2_Chatot_get(struct SaveBlock2 * sav2);
BOOL Chatot_exists(struct SaveChatotSoundClip * chatot);
void Chatot_invalidate(struct SaveChatotSoundClip * chatot);
s8 * Chatot_GetData(struct SaveChatotSoundClip * chatot);
void Chatot_Decode(s8 * dest, const s8 * data);
void Chatot_Encode(struct SaveChatotSoundClip * chatot, const s8 * data);
void Chatot_copy(struct SaveChatotSoundClip * dest, const struct SaveChatotSoundClip * src);

#endif //POKEDIAMOND_SAV_CHATOT_H
