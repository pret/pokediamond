#ifndef POKEDIAMOND_SOUND_CHATOT_H
#define POKEDIAMOND_SOUND_CHATOT_H

#include "global.h"
#include "sav_chatot.h"

BOOL sub_02005CFC(void);
BOOL Chatot_checkCry(struct SaveChatotSoundClip *param0);
u32 sub_02005D48(struct SaveChatotSoundClip *param0, u32 param1, s32 param2, s32 param3);
void sub_02005DFC(void);
u32 Chatot_startRecording(void);
void Chatot_stopRecording(void);
void Chatot_saveRecording(struct SaveChatotSoundClip *param0);
void sub_02005E80(u8 param0);
void sub_02005E90(struct SaveChatotSoundClip *param0, u32 param1, s32 param2, s32 param3);
u32 sub_02005EE0(struct SaveChatotSoundClip *param0);
BOOL sub_02005F14(s32 param0);

#endif // POKEDIAMOND_UNK_02005CFC_H
