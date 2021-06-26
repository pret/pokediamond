#include "SND_lockChannel.h"

#include "SND_work.h"
#include "SND_exChannel.h"
#include "SND.h"

// TODO make these vars static after merging this file with exChannel
u32 sUnlockedChannelMask;
u32 sLockedChannelMask;

void SND_StopUnlockedChannel(u32 channelMask) {
    struct SNDExChannel *chn;
    
    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if ((channelMask & 1) == 0)
            continue;
        
        chn = &SNDi_Work.channels[i];

        if (sUnlockedChannelMask & (1 << i))
            continue;

        if (chn->callback)
            chn->callback(chn, 0, chn->callbackUserData);

        SND_StopChannel(i, 0);
        chn->priority = 0;
        SND_FreeExChannel(chn);
        chn->flags.syncFlag = 0;
        chn->flags.active = 0;
    }
}

void SND_LockChannel(u32 channelMask, u32 locked) {
    struct SNDExChannel *chn;
    u32 j = channelMask;
    int i = 0;

    for (; i < SND_CHANNEL_COUNT && j != 0; i++, j >>= 1) {
        if ((j & 1) == 0)
            continue;

        chn = &SNDi_Work.channels[i];

        if (sUnlockedChannelMask & (1 << i))
            continue;

        if (chn->callback)
            chn->callback(chn, 0, chn->callbackUserData);

        SND_StopChannel(i, 0);
        chn->priority = 0;
        SND_FreeExChannel(chn);
        chn->flags.syncFlag = 0;
        chn->flags.active = 0;
    }

    if (locked & 1) {
        sLockedChannelMask |= channelMask;
    } else {
        sUnlockedChannelMask |= channelMask;
    }
}

void SND_UnlockChannel(u32 channelMask, u32 locked) {
    if (locked & 1) {
        sLockedChannelMask &= ~channelMask;
    } else {
        sUnlockedChannelMask &= ~channelMask;
    }
}

u32 SND_GetLockedChannel(u32 locked) {
    if (locked & 1) {
        return sLockedChannelMask;
    } else {
        return sUnlockedChannelMask;
    }
}
