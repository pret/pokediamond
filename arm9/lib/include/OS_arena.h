#ifndef POKEDIAMOND_ARM9_OS_ARENA_H
#define POKEDIAMOND_ARM9_OS_ARENA_H

#include "nitro/types.h"
#include "nitro/OS_arena_shared.h"

void OS_InitArena(void);
void OS_InitArenaEx(void);
void* OS_GetArenaHi(OSArenaId id);
void* OS_GetArenaLo(OSArenaId id);
void* OS_GetInitArenaHi(OSArenaId id);
void* OS_GetInitArenaLo(OSArenaId id);
void OS_SetArenaHi(OSArenaId id, void *newHi);
void OS_SetArenaLo(OSArenaId id, void *newLo);
void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align);
void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align);

#endif //POKEDIAMOND_ARM9_OS_ARENA_H
