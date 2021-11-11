#ifndef POKEDIAMOND_PLAY_TIMER_H
#define POKEDIAMOND_PLAY_TIMER_H

#include "global.h"
#include "igt.h"
#include "timer3.h"

void PlayTimerInit(void);
void PlayTimerStart(struct IGT *igt);
void PlayTimerUpdate(void);

#endif //POKEDIAMOND_PLAY_TIMER_H
