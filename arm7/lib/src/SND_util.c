#include "SND_util.h"

#include "syscall.h"

// TODO remove this extern once the static const definition of it is here
extern s8 sLfoSinTable[0x21];

u16 SND_CalcTimer(int timer, int pitch)
{
    int octave = 0;
    int pitch_normalized = -pitch;

    while (pitch_normalized < 0)
    {
        octave--;
        pitch_normalized += 768;
    }

    while (pitch_normalized >= 768)
    {
        octave++;
        pitch_normalized -= 768;
    }

    u64 result = SVC_GetPitchTable(pitch_normalized);

    result += 0x10000;
    result *= timer;

    int shift = octave - 16;

    if (shift <= 0)
    {
        shift = -shift;
        result >>= shift;
    }
    else if (shift < 32)
    {
        // what ???
        u64 tmp = result & ~0uLL << (32 - shift);
        if (tmp != 0)
            return 0xFFFF;
        result <<= shift;
    }
    else
    {
        return 0xFFFF;
    }

    if (result < 0x10)
        result = 0x10;
    else if (result > 0xFFFF)
        result = 0xFFFF;

    return (u16)result;
}

u16 SND_CalcChannelVolume(int value)
{
    if (value < SND_VOL_DB_MIN)
        value = SND_VOL_DB_MIN;
    else if (value > 0)
        value = 0;

    int result = SVC_GetVolumeTable(value + (-SND_VOL_DB_MIN));
    int div;

    if (value < -240)
        div = 3;
    else if (value < -120)
        div = 2;
    else if (value < -60)
        div = 1;
    else
        div = 0;

    return (u16)(result | (div << 8));
}

s8 SND_SinIdx(int x)
{
    // BUG: UB for out of range values

    if (x < 0x20)
    {
        return sLfoSinTable[x];
    }
    else if (x < 0x40)
    {
        return sLfoSinTable[0x40 - x];
    }
    else if (x < 0x60)
    {
        return (s8)(-sLfoSinTable[x - 0x40]);
    }
    else
    {
        return (s8)(-sLfoSinTable[0x20 - (x - 0x60)]);
    }
}

u16 SND_CalcRandom(void)
{
    static u32 state = 0x12345678;

    // values from "Numerical Recipes"
    state = state * 1664525u + 1013904223u;
    return (u16)(state >> 16u);
}
