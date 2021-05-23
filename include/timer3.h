#ifndef POKEDIAMOND_TIMER3_H
#define POKEDIAMOND_TIMER3_H


#include "global.h"

struct Timer3Data
{
    BOOL NeedReset;
    vu64 Timer3Counter;
};

void Init_Timer3();
void CountUpTimer3();
u64 internal_GetTimer3Count();
u64 GetTimer3Count();
u64 Timer3CountToMilliSeconds(u64 count);
u64 Timer3CountToSeconds(u64 count);


#endif //POKEDIAMOND_TIMER3_H
