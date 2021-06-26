#ifndef GUARD_SND_EXCHANNEL_H
#define GUARD_SND_EXCHANNEL_H

#include "nitro/types.h"

void SND_ExChannelInit(void);
BOOL SND_IsChannelActive(s32 idx);
void SND_UpdateExChannel(void);
void SND_ExChannelMain(BOOL update);

#endif //GUARD_SND_EXCHANNEL_H
