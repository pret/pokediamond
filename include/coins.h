#ifndef POKEDIAMOND_COINS_H
#define POKEDIAMOND_COINS_H

#include "nitro/types.h"

#define MAX_COINS 50000

void Coins_Init(u16 *coins);
void Coins_SetValue(u16 *coins, u32 value);
u16 Coins_GetValue(u16 *coins);
BOOL Coins_Add(u16 *coins, u16 amount);
BOOL Coins_CanAdd(u16 *coins, u16 amount);
BOOL Coins_Subtract(u16 *coins, u16 amount);

#endif // POKEDIAMOND_COINS_H
