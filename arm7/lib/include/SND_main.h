#ifndef GUARD_SND_MAIN_H
#define GUARD_SND_MAIN_H

#include "nitro/types.h"

void SND_Init(u32 priority);
void SND_CreateThread(u32 priority);
void SND_InitIntervalTimer(void);
void SND_StartIntervalTimer(void);
void SND_StopIntervalTimer(void);
u32 SND_WaitForIntervalTimer(void);
void SND_SendWakeupMessage(void);
void SNDi_LockMutex(void);
void SNDi_UnlockMutex(void);

#endif //GUARD_SND_MAIN_H
