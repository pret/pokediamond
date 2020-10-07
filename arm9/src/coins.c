#include "global.h"
#include "coins.h"

#pragma thumb on

void InitCoins(u16 * coins)
{
    *coins = 0;
}

void SetCoins(u16 * coins, u16 value)
{
    GF_ASSERT(value <= MAX_COINS);
    *coins = value;
}

u16 CheckCoins(u16 * coins)
{
    return *coins;
}

BOOL GiveCoins(u16 * coins, u16 amount)
{
    if (*coins >= MAX_COINS)
        return FALSE;
    *coins += amount;
    if (*coins > MAX_COINS)
        *coins = MAX_COINS;
    return TRUE;
}

BOOL CanGiveCoins(u16 * coins, u16 amount)
{

    return (u32)(amount + *coins) <= MAX_COINS;
}

BOOL TakeCoins(u16 * coins, u16 amount)
{
    if (*coins < amount)
        return FALSE;
    *coins -= amount;
    return TRUE;
}
