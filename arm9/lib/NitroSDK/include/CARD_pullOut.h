#ifndef POKEDIAMOND_CARD_PULLOUT_H
#define POKEDIAMOND_CARD_PULLOUT_H

#include "nitro/types.h"

typedef BOOL (*CARDPulledOutCallback) (void);

void CARD_InitPulledOutCallback(void);
BOOL CARD_IsPulledOut(void);
void CARD_TerminateForPulledOut(void);
void CARDi_CheckPulledOutCore(u32 id);

#endif //POKEDIAMOND_CARD_PULLOUT_H
