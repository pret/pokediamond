#include "SND_work.h"

#include "SND_channel.h"
#include "SND_exChannel.h"
#include "SND_capture.h"

struct SNDWork SNDi_Work;
struct SNDSharedWork *SNDi_SharedWork;

void SND_SetPlayerLocalVariable(int player, int var, s16 value) {
    SNDi_SharedWork->players[player].localVars[var] = value;
}

void SND_SetPlayerGlobalVariable(int var, s16 value) {
    SNDi_SharedWork->globalVars[var] = value;
}

void SND_UpdateSharedWork(void) {
    u16 channelActiveMask = 0;
    u16 channelCaptureMask = 0;

    if (SNDi_SharedWork == NULL)
        return;
    
    for (s32 i = 0; i < SND_CHANNEL_COUNT; i++) {
        if (SND_IsChannelActive(i))
            channelActiveMask |= 1 << i;
    }

    if (SND_IsCaptureActive(0))
        channelCaptureMask |= 0x1;
    if (SND_IsCaptureActive(1))
        channelCaptureMask |= 0x2;

    SNDi_SharedWork->channelStatus = channelActiveMask;
    SNDi_SharedWork->captureStatus = channelCaptureMask;
}
