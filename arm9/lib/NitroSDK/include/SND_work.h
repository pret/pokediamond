#ifndef GUARD_SND_WORK_H
#define GUARD_SND_WORK_H

#include "nitro/types.h"

#include "SND_main.h"
#include "nitro/SND_work_shared.h"

u32 SND_GetPlayerStatus(void);
u16 SND_GetChannelStatus(void);
//u16 SND_GetCaptureStatus(void);
u32 SND_GetPlayerTickCounter(u32 playerId);
//s16 SND_GetPlayerLocalVariable(u32 playerId, u32 var);
//s16 SND_GetPlayerGlobalVariable(u32 var);
//BOOL SND_ReadChannelInfo(const SNDDriverInfo *driverInfo, s32 chnId, SNDChannelInfo *chnInfo);
//BOOL SND_ReadPlayerInfo(const SNDDriverInfo *driverInfo, s32 playerId, s32 trackId, SNDPlayerInfo *playerInfo);
//BOOL SND_ReadTrackInfo(const SNDDriverInfo *driverInfo s32 playerId, s32 trackId, SNDTrackInfo *trackInfo);
u32 SNDi_GetFinishedCommandTag(void);
void SNDi_InitSharedWork(struct SNDSharedWork *sw);

extern struct SNDSharedWork *SNDi_SharedWork;

#endif // GUARD_SND_WORK_H
