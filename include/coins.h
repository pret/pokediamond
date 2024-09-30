#ifndef POKEDIAMOND_COINS_H
#define POKEDIAMOND_COINS_H

#include "nitro/types.h"

#define MAX_COINS 50000

void InitCoins(u16 *coins);
void SetCoins(u16 *coins, u16 value);
u16 CheckCoins(u16 *coins);
BOOL GiveCoins(u16 *coins, u16 amount);
BOOL CanGiveCoins(u16 *coins, u16 amount);
BOOL TakeCoins(u16 *coins, u16 amount);

#endif // POKEDIAMOND_COINS_H
