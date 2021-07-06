#ifndef POKEDIAMOND_ARM7_REGISTERS_H
#define POKEDIAMOND_ARM7_REGISTERS_H

#include "nitro/registers_shared.h"

#define reg_EXTKEYIN (*(REGType16v *)0x4000136)

#define reg_SOUNDxCNT_STAT(x) (*((REGType8v *)0x4000403 + ((int)(x) * 0x10)))
#define reg_SOUNDxCNT(x) (*((REGType32v *)0x4000400 + ((int)x) * 0x10))
#define reg_SOUNDxSAD(x) (*((REGType32v *)0x4000404 + ((int)x) * 0x10))
#define reg_SOUNDxTMR(x) (*((REGType16v *)0x4000408 + ((int)x) * 0x10))
#define reg_SOUNDxPNT(x) (*((REGType16v *)0x400040A + ((int)x) * 0x10))
#define reg_SOUNDxLEN(x) (*((REGType32v *)0x400040C + ((int)x) * 0x10))

#define reg_SNDCAPxCNT(x) (*((REGType8v *)0x4000508 + ((int)(x))))

#define EXTKEYIN_X (1<<0)
#define EXTKEYIN_Y (1<<1)
#define EXTKEYIN_DEBUG (1<<3)
#define EXTKEYIN_PEN (1<<6)
#define EXTKEYIN_HINGE (1<<7)

#endif //POKEDIAMOND_ARM7_REGISTERS_H
