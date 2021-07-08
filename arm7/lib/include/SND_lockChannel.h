#ifndef GUARD_SND_LOCKCHANNEL_H
#define GUARD_SND_LOCKCHANNEL_H

#include "nitro/types.h"

void SND_StopUnlockedChannel(u32 channelMask, u32 weak);
void SND_LockChannel(u32 channelMask, u32 weak);
void SND_UnlockChannel(u32 channelMask, u32 weak);
u32 SND_GetLockedChannel(u32 weak);

// TODO remove these externs if lockChannel is merged with exChannel
extern u32 sLockedChannelMask;
extern u32 sWeakLockedChannelMask;

#endif //GUARD_SND_LOCKCHANNEL_H
