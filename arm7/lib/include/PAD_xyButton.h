#ifndef POKEDIAMOND_PAD_XYBUTTON_H
#define POKEDIAMOND_PAD_XYBUTTON_H

#include "mmap.h"
#include "nitro/types.h"

#define BUTTON_XY_BUF (*(vu16 *) HW_BUTTON_XY_BUF)

BOOL PAD_InitXYButton(void);
void PADi_xyButtonAlarmHandler(void);

#endif
