#ifndef GUARD_SND_INTERFACE_H
#define GUARD_SND_INTERFACE_H

#include "nitro/types.h"
#include "SND_bank.h"
#include "SND_work.h"
#include "SND_alarm.h"

void SND_StartSeq(s32 player, const void *seqBasePtr, u32 seqOffset, struct SNDBankData *bankData);
void SND_StopSeq(s32 player);
void SND_PrepareSeq(s32 player, const void *seqBasePtr, u32 seqOffset, struct SNDBankData *bankData);
void SND_StartPreparedSeq(s32 player);
void SND_PauseSeq(s32 player, BOOL flag);

void SND_SetPlayerTempoRatio(s32 player, s32 ratio);
void SND_SetPlayerVolume(s32 player, s32 volume);
void SND_SetPlayerChannelPriority(s32 player, s32 prio);
void SND_SetPlayerLocalVariable(s32 player, s32 varNo, s16 var);
void SND_SetPlayerGlobalVariable(s32 varNo, s16 var);

void SND_SetTrackVolume(s32 player, u32 trackBitMask, s32 volume);
void SND_SetTrackPitch(s32 player, u32 trackBitMask, s32 pitch);
void SND_SetTrackPan(s32 player, u32 trackBitMask, s32 pan);
void SND_SetTrackPanRange(s32 player, u32 trackBitMask, s32 panRange);
void SND_SetTrackModDepth(s32 player, u32 trackBitMask, s32 depth);
void SND_SetTrackModSpeed(s32 player, u32 trackBitMask, s32 speed);
void SND_SetTrackAllocatableChannel(s32 player, u32 trackBitMask, u32 chnBitMask);
void SND_SetTrackMute(s32 player, u32 trackBitMask, BOOL flag);

void SND_StartTimer(u32 chnBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void SND_StopTimer(u32 chnBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);

void SND_SetupCapture(s32 capture, s32 format, void *bufferPtr, u32 length, BOOL loopFlag, s32 in, s32 out);
void SND_SetupAlarm(s32 alarm, u32 tick, u32 period, SNDAlarmCallback cb, void *userData);

void SND_StopUnlockedChannel(u32 chnBitMask, u32 flags);
void SND_LockChannel(u32 chnBitMask, u32 flags);
void SND_UnlockChannel(u32 chnBitMask, u32 flags);

void SND_SetChannelTimer(u32 chnBitMask, s32 timer);
void SND_SetChannelVolume(u32 chnBitMask, s32 volume, s32 chnDataShift);
void SND_SetChannelPan(u32 chnBitMask, s32 pan);
void SND_SetupChannelPcm(s32 chn, s32 waveFormat, const void *dataAddr, s32 loopMode, s32 loopStart, s32 dataLen, s32 volume, s32 chnDataShift, s32 timer, s32 pan);
void SND_SetupChannelPsg(s32 chn, s32 sndDuty, s32 volume, s32 chnDataShift, s32 timer, s32 pan);
void SND_SetupChannelNoise(s32 chn, s32 volume, s32 chnDataShift, s32 timer, s32 pan);

void SND_InvalidateSeqData(const void *start, const void *end);
void SND_InvalidateBankData(const void *start, const void *end);
void SND_InvalidateWaveData(const void *start, const void *end);

void SND_SetMasterVolume(s32 volume);
void SND_SetOutputSelector(s32 left, s32 right, s32 channel1, s32 channel3);
void SND_SetMasterPan(s32 pan);
void SND_ResetMasterPan(void);

void SND_ReadDriverInfo(struct SNDDriverInfo *info);

void SNDi_SetPlayerParam(s32 player, u32 offset, u32 data, s32 size);
void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);
void SNDi_SetSurroundDecay(s32 decay);
void SNDi_SkipSeq(s32 player, u32 tick);

#endif // GUARD_SND_INTERFACE_H
