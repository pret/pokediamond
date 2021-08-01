#ifndef GUARD_SND_EXCHANNEL_H
#define GUARD_SND_EXCHANNEL_H

#include "nitro/types.h"

#include "nitro/SND_exChannel_shared.h"
#include "nitro/SND_main_shared.h"

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
BOOL SND_IsChannelActive(int idx);
void SND_InvalidateWave(const void *start, const void *end);

// TODO internal functions, move these so exChannel
int ExChannelSweepUpdate(struct SNDExChannel *chn, BOOL step);
int ExChannelLfoUpdate(struct SNDExChannel *chn, BOOL step);
void ExChannelStart(struct SNDExChannel *chn, int length);
int ExChannelVolumeCmp(struct SNDExChannel *chn_a, struct SNDExChannel *chn_b);
void ExChannelSetup(struct SNDExChannel *, SNDExChannelCallback callback, void *callbackUserData, int priority);

void SND_StopUnlockedChannel(u32 channelMask, u32 weak);
void SND_LockChannel(u32 channelMask, u32 weak);
void SND_UnlockChannel(u32 channelMask, u32 weak);
u32 SND_GetLockedChannel(u32 weak);

void SND_InvalidateWave(const void *begin, const void *end);

void SND_InitLfoParam(struct SNDLfoParam *lfoParam);
void SND_StartLfo(struct SNDLfo *lfo);
void SND_UpdateLfo(struct SNDLfo *lfo);
int SND_GetLfoValue(struct SNDLfo *lfo);

#endif //GUARD_SND_EXCHANNEL_H
