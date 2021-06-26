#ifndef GUARD_SND_EXCHANNEL_H
#define GUARD_SND_EXCHANNEL_H

#include "nitro/types.h"

#include "nitro/SND_main_shared.h"

void SND_ExChannelInit(void);
BOOL SND_IsChannelActive(s32 idx);
void SND_UpdateExChannel(void);
void SND_ExChannelMain(BOOL update);
void SND_FreeExChannel(struct SNDExChannel *chn);

#endif //GUARD_SND_EXCHANNEL_H
