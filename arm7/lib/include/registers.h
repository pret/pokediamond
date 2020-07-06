#ifndef POKEDIAMOND_ARM7_REGISTERS_H
#define POKEDIAMOND_ARM7_REGISTERS_H

#include "nitro/registers_shared.h"

#define reg_EXTKEYIN (*(REGType16v *)0x4000136)

#define EXTKEYIN_X (1<<0)
#define EXTKEYIN_Y (1<<1)
#define EXTKEYIN_DEBUG (1<<3)
#define EXTKEYIN_PEN (1<<6)
#define EXTKEYIN_HINGE (1<<7)

#endif //POKEDIAMOND_ARM7_REGISTERS_H
