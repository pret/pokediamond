#include "global.h"

void * (* gUnk021C8C70)(u32);

ARM_FUNC void* FUN_020910A4(u32 size)
{
  if (gUnk021C8C70 != NULL)
    return gUnk021C8C70(size);
  return OS_AllocFromHeap(OS_ARENA_MAIN, -1, size);
}
