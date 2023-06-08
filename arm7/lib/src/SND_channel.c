#include "SND_channel.h"

#include "SND_work.h"
#include "registers.h"
#include "code32.h"

static int sMasterPan = -1;

static u8 sOrgVolume[SND_CHANNEL_COUNT];
static u8 sOrgPan[SND_CHANNEL_COUNT];
static int sSurroundDecay;

static int CalcSurroundDecay(int vol, int pan);

void SND_SetupChannelPcm(int chnIdx,
    const void *data,
    int format,
    int loop,
    int loopStart,
    int loopLength,
    int volume,
    int volumeDiv,
    int timer,
    int pan)
{
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;

    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5)
    {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) =
        (u32)((format << 29) | (loop << 27) | (pan << 16) | (volumeDiv << 8) | (volume));
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
    reg_SOUNDoffPNT(off) = (u16)loopStart;
    reg_SOUNDoffLEN(off) = (u32)loopLength;
    reg_SOUNDoffSAD(off) = (u32)data;
}

void SND_SetupChannelPsg(int chnIdx, int duty, int volume, int volumeDiv, int timer, int pan)
{
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;

    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5)
    {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) =
        (u32)(0x60000000 | (duty << 24) | (pan << 16) | (volumeDiv << 8) | volume);
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
}

void SND_SetupChannelNoise(int chnIdx, int volume, int volumeDiv, int timer, int pan)
{
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;

    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5)
    {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) = (u32)(0x60000000 | (pan << 16) | (volumeDiv << 8) | volume);
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
}

void SND_StopChannel(int idx, int hold)
{
    vu32 *reg = &reg_SOUNDxCNT(idx);

    u32 v = *reg;

    // disable channel
    v &= ~0x80000000;

    // set hold flag
    if (hold & 1)
        v |= 0x8000;

    *reg = v;
}

void SND_SetChannelVolume(int chnIdx, int vol, int volDiv)
{
    sOrgVolume[chnIdx] = (u8)vol;

    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5)
    {
        int pan = reg_SOUNDxCNT_PAN(chnIdx);
        vol = CalcSurroundDecay(vol, pan);
    }

    reg_SOUNDxCNT_VOLS(chnIdx) = (u16)((volDiv << 8) | vol);
}

void SND_SetChannelTimer(int chnIdx, int timer)
{
    reg_SOUNDxTMR(chnIdx) = (u16)(0x10000 - timer);
}

void SND_SetChannelPan(int chnIdx, int pan)
{
    sOrgPan[chnIdx] = (u8)pan;

    if (sMasterPan >= 0)
    {
        pan = sMasterPan;
    }

    reg_SOUNDxCNT_PAN(chnIdx) = (u8)pan;

    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5)
    {
        reg_SOUNDxCNT_VOL(chnIdx) = (u8)CalcSurroundDecay(sOrgVolume[chnIdx], pan);
    }
}

BOOL SND_IsChannelActive(int chnIdx)
{
    return (reg_SOUNDxCNT_STAT(chnIdx) & 0x80) != 0;
}

void SND_SetMasterPan(int pan)
{
    sMasterPan = pan;

    if (pan >= 0)
    {
        for (int i = 0; i < SND_CHANNEL_COUNT; i++)
        {
            reg_SOUNDxCNT_PAN(i) = (u8)pan;
        }
    }
    else
    {
        for (int i = 0; i < SND_CHANNEL_COUNT; i++)
        {
            reg_SOUNDxCNT_PAN(i) = sOrgPan[i];
        }
    }
}

u32 SND_GetChannelControl(int chnIdx)
{
    return reg_SOUNDxCNT(chnIdx);
}

void SNDi_SetSurroundDecay(int decay)
{
    sSurroundDecay = decay;

    for (int i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        // do not process channel 1+3 (capture playback channels)
        if ((1 << i) & 0xFFF5)
        {
            int pan = reg_SOUNDxCNT_PAN(i);
            reg_SOUNDxCNT_VOL(i) = (u8)CalcSurroundDecay(sOrgVolume[i], pan);
        }
    }
}

static int CalcSurroundDecay(int vol, int pan)
{
    if (pan < 24)
    {
        return vol * (sSurroundDecay * (pan + 40) + ((0x7FFF - sSurroundDecay) << 6)) >> 21;
    }
    else if (pan <= 104)
    {
        return vol;
    }
    else
    {
        return vol * (-sSurroundDecay * (pan - 40) + ((sSurroundDecay + 0x7FFF) << 6)) >> 21;
    }
}
