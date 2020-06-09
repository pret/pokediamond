#ifndef POKEDIAMOND_ARM7_OS_ARENA_H
#define POKEDIAMOND_ARM7_OS_ARENA_H

#include "nitro/OS_arena_shared.h"

void OS_InitArena(void);
void* OS_GetArenaHi(OSArenaId id);
void* OS_GetArenaLo(OSArenaId id);
void* OS_GetInitArenaHi(OSArenaId id);
void* OS_GetInitArenaLo(OSArenaId id);
void OS_SetArenaHi(OSArenaId id, void* newHi);
void OS_SetArenaLo(OSArenaId id, void* newLo);

#endif //POKEDIAMOND_ARM7_OS_ARENA_H
