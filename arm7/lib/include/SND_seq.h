#ifndef GUARD_SND_SEQ_H
#define GUARD_SND_SEQ_H

#include "nitro/types.h"

#include "nitro/SND_bank_shared.h"

void SND_SeqInit(void);
void SND_SeqMain(BOOL update);

void SND_StartSeq(int player, const void *seq, u32 offset, struct SNDBankData *bank);
void SND_StopSeq(int player);
void SND_PrepareSeq(int player, const void *seq, u32 offset, struct SNDBankData *bank);
void SND_StartPreparedSeq(int player);
void SND_PauseSeq(int player, BOOL pause);
void SND_SkipSeq(int player, u32 tick);
void SNDi_SetPlayerParam(int player, u32 offset, u32 data, int size);
void SNDi_SetTrackParam(int player, u32 trackMask, u32 offset, u32 data, int size);
void SND_SetTrackMute(int player, u32 trackMask, BOOL mute);
void SND_SetTrackAllocatableChannel(int player, u32 trackMask, u32 channelMask);
void SND_InvalidateSeq(const void *start, const void *end);
void SND_InvalidateBank(const void *start, const void *end);

#endif // GUARD_SND_SEQ_H
