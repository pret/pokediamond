#ifndef GUARD_SND_COMMAND_H
#define GUARD_SND_COMMAND_H

#include "nitro/SND_command_shared.h"

#include "nitro/types.h"

void SND_CommandInit(void);
const struct SNDCommand *SND_RecvCommandReply(u32 flags);
struct SNDCommand *SND_AllocCommand(u32 flags);
void SND_PushCommand(struct SNDCommand *cmd);
BOOL SND_FlushCommand(u32 flags);
void SND_WaitForCommandProc(u32 tag);
void SND_WaitForFreeCommand(s32 count);
u32 SND_GetCurrentCommandTag(void);
BOOL SND_IsFinishedCommandTag(u32 tag);
s32 SND_CountFreeCommand(void);
s32 SND_CountReservedCommand(void);
s32 SND_CountWaitingCommand(void);

#endif // GUARD_SND_COMMAND_H
