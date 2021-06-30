#ifndef GUARD_SND_EXCHANNEL_H
#define GUARD_SND_EXCHANNEL_H

#include "nitro/types.h"

#include "nitro/SND_exChannel_shared.h"
#include "nitro/SND_main_shared.h"

typedef void (*SNDExChannelCallback)(struct SNDExChannel *chn, s32 status, void *userData);

void SND_ExChannelInit(void);
void SND_UpdateExChannel(void);
void SND_ExChannelMain(BOOL step);
BOOL SND_StartExChannelPcm(struct SNDExChannel *chn, const struct SNDWaveParam *wave, const void *data, s32 length);
BOOL SND_StartExChannelPsg(struct SNDExChannel *chn, s32 duty, s32 length);
BOOL SND_StartExChannelNoise(struct SNDExChannel *chn, s32 length);
s32 SND_UpdateExChannelEnvelope(struct SNDExChannel *chn, BOOL step);
void SND_SetExChannelAttack(struct SNDExChannel *chn, s32 attack);
void SND_SetExChannelDecay(struct SNDExChannel *chn, s32 decay);
void SND_SetExChannelSustain(struct SNDExChannel *chn, s32 sustain);
void SND_SetExChannelRelease(struct SNDExChannel *chn, s32 release);
void SND_ReleaseExChannel(struct SNDExChannel *chn);
BOOL SND_IsExChannelActive(struct SNDExChannel *chn);
struct SNDExChannel *SND_AllocExChannel(u32 channelMask, int priority, u32 flags, SNDExChannelCallback callback, void *callbackUserData);
void SND_FreeExChannel(struct SNDExChannel *chn);
BOOL SND_IsChannelActive(s32 idx);

// TODO internal functions, move these so exChannel
s32 ExChannelSweepUpdate(struct SNDExChannel *chn, BOOL step);
s32 ExChannelLfoUpdate(struct SNDExChannel *chn, BOOL step);
void ExChannelStart(struct SNDExChannel *chn, s32);
s32 ExChannelVolumeCmp(struct SNDExChannel *chn_a, struct SNDExChannel *chn_b);
void ExChannelSetup(struct SNDExChannel *, SNDExChannelCallback callback, void *callbackUserData, s32 priority);

#endif //GUARD_SND_EXCHANNEL_H
