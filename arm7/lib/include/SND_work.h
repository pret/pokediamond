#ifndef GUARD_SND_WORK_H
#define GUARD_SND_WORK_H

#include "nitro/SND_work_shared.h"

extern struct SNDWork SNDi_Work;
extern struct SNDSharedWork *SNDi_SharedWork;

void SND_SetPlayerLocalVariable(u32 player, u32 var, s16 value);
void SND_SetPlayerGlobalVariable(u32 var, s16 value);
void SND_UpdateSharedWork(void);

#endif //GUARD_SND_WORK_H
