#ifndef GUARD_SND_LOCKCHANNEL_H
#define GUARD_SND_LOCKCHANNEL_H

#include "nitro/types.h"

void SND_StopUnlockedChannel(u32 channelMask);
void SND_LockChannel(u32 channelMask, u32 locked);
void SND_UnlockChannel(u32 channelMask, u32 locked);
u32 SND_GetLockedChannel(u32 locked);

#endif //GUARD_SND_LOCKCHANNEL_H
