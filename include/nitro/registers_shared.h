/*
 * NOTE:
 * This file is shared between ARM9 and ARM7
 * DO NOT PUT PROC SPECIFIC CODE IN HERE
 * Thank You!
 */

#ifndef POKEDIAMOND_REGISTERS_SHARED_H
#define POKEDIAMOND_REGISTERS_SHARED_H

#include "nitro/types.h"

#define reg_OS_IME                 (*(REGType16v *)0x4000208)
#define reg_OS_IE                  (*(REGType32v *)0x4000210)
#define reg_OS_IF                  (*(REGType32v *)0x4000214)

#endif //POKEDIAMOND_REGISTERS_SHARED_H
