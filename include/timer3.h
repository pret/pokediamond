#ifndef POKEDIAMOND_TIMER3_H
#define POKEDIAMOND_TIMER3_H


#include "global.h"

struct Timer3Data
{
    BOOL NeedReset;
    vu64 Timer3Counter;
};

THUMB_FUNC void Init_Timer3();
THUMB_FUNC void CountUpTimer3();
THUMB_FUNC u64 internal_GetTimer3Count();
THUMB_FUNC u64 GetTimer3Count();
THUMB_FUNC u64 Timer3CountToMilliSeconds(u64 count);
THUMB_FUNC u64 Timer3CountToSeconds(u64 count);


#endif //POKEDIAMOND_TIMER3_H
