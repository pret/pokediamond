#include "SND.h"

#include "registers.h"
#include "syscall.h"

#include "OS_system.h"
#include "PM.h"
#include "SND_exChannel.h"
#include "SND_work.h"
#include "SND_channel.h"

static int sMasterPan = -1;

static u8 sOrgVolume[SND_CHANNEL_COUNT];
static u8 sOrgPan[SND_CHANNEL_COUNT];
static int sSurroundDecay;

static int CalcSurroundDecay(int vol, int pan);

void SND_SetupChannelPcm(int chnIdx, const void *data, int format, int loop, int loopStart, int loopLength, int volume, int volumeDiv, int timer, int pan) {
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;
    
    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5) {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) = (u32)((format << 29) | (loop << 27) | (pan << 16) | (volumeDiv << 8) | (volume));
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
    reg_SOUNDoffPNT(off) = (u16)loopStart;
    reg_SOUNDoffLEN(off) = (u32)loopLength;
    reg_SOUNDoffSAD(off) = (u32)data;
}

void SND_SetupChannelPsg(int chnIdx, int duty, int volume, int volumeDiv, int timer, int pan) {
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;
    
    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5) {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) = (u32)(0x60000000 | (duty << 24) | (pan << 16) | (volumeDiv << 8) | volume);
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
}

void SND_SetupChannelNoise(int chnIdx, int volume, int volumeDiv, int timer, int pan) {
    int off = chnIdx * 0x10;

    sOrgPan[chnIdx] = (u8)pan;
    if (sMasterPan >= 0)
        pan = sMasterPan;
    
    sOrgVolume[chnIdx] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5) {
        volume = CalcSurroundDecay(volume, pan);
    }

    reg_SOUNDoffCNT(off) = (u32)(0x60000000 | (pan << 16) | (volumeDiv << 8) | volume);
    reg_SOUNDoffTMR(off) = (u16)(0x10000 - timer);
}

void SND_StopChannel(int idx, int hold) {
    vu32 *reg = &reg_SOUNDxCNT(idx);

    u32 v = *reg;

    // disable channel
    v &= ~0x80000000;

    // set hold flag
    if (hold & 1)
        v |= 0x8000;

    *reg = v;
}

void SND_SetChannelVolume(int chnIdx, int vol, int volDiv) {
    sOrgVolume[chnIdx] = (u8)vol;

    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5) {
        int pan = reg_SOUNDxCNT_PAN(chnIdx);
        vol = CalcSurroundDecay(vol, pan);
    }

    reg_SOUNDxCNT_VOLS(chnIdx) = (u16)((volDiv << 8) | vol);
}

void SND_SetChannelTimer(int chnIdx, int timer) {
    reg_SOUNDxTMR(chnIdx) = (u16)(0x10000 - timer);
}

void SND_SetChannelPan(int chnIdx, int pan) {
    sOrgPan[chnIdx] = (u8)pan;

    if (sMasterPan >= 0) {
        pan = sMasterPan;
    }

    reg_SOUNDxCNT_PAN(chnIdx) = (u8)pan;

    if (sSurroundDecay > 0 && (1 << chnIdx) & 0xFFF5) {
        reg_SOUNDxCNT_VOL(chnIdx) = (u8)CalcSurroundDecay(sOrgVolume[chnIdx], pan);
    }
}

BOOL SND_IsChannelActive(int chnIdx) {
    return (reg_SOUNDxCNT_STAT(chnIdx) & 0x80) != 0;
}

void SND_SetMasterPan(int pan) {
    sMasterPan = pan;

    if (pan >= 0) {
        for (int i = 0; i < SND_CHANNEL_COUNT; i++) {
            reg_SOUNDxCNT_PAN(i) = (u8)pan;
        }
    } else {
        for (int i = 0; i < SND_CHANNEL_COUNT; i++) {
            reg_SOUNDxCNT_PAN(i) = sOrgPan[i];
        }
    }
}

u32 SND_GetChannelControl(int chnIdx) {
    return reg_SOUNDxCNT(chnIdx);
}

void SNDi_SetSurroundDecay(int decay) {
    sSurroundDecay = decay;

    for (int i = 0; i < SND_CHANNEL_COUNT; i++) {
        // do not process channel 1+3 (capture playback channels)
        if ((1 << i) & 0xFFF5) {
            int pan = reg_SOUNDxCNT_PAN(i);
            reg_SOUNDxCNT_VOL(i) = (u8)CalcSurroundDecay(sOrgVolume[i], pan);
        }
    }
}

static int CalcSurroundDecay(int vol, int pan) {
    if (pan < 24) {
        return vol * (sSurroundDecay * (pan + 40) + ((0x7FFF - sSurroundDecay) << 6)) >> 21;
    } else if (pan <= 104) {
        return vol;
    } else {
        return vol * (-sSurroundDecay * (pan - 40) + ((sSurroundDecay + 0x7FFF) << 6)) >> 21;
    }
}

void SND_Enable(void) {
    reg_SOUNDCNT_MIX |= 0x80;
}

void SND_Disable(void) {
    reg_SOUNDCNT_MIX &= ~0x80;
}

void SND_Shutdown(void) {
    SND_Disable();

    for (int i = 0; i < SND_CHANNEL_COUNT; i++) {
        SND_StopChannel(i, 1);
    }

    reg_SNDCAPxCNT(0) = 0;
    reg_SNDCAPxCNT(1) = 0;
}

void SND_BeginSleep(void) {
    SND_Disable();
    SVC_SoundBiasReset(0x80);
    OS_SpinWait(0x40000);
    PMi_ResetControl(1);
    reg_POWCNT2 &= ~1;
}

void SND_EndSleep(void) {
    reg_POWCNT2 |= 1;   // enable speakers
    PMi_SetControl(1);
    SVC_SoundBiasSet(0x100);
    OS_SpinWait(0x7AB80); // what does this wait for and how long does it wait?
    SND_Enable();
}

void SND_SetMasterVolume(int vol) {
    reg_SOUNDCNT_VOL = (u8)vol;
}

void SND_SetOutputSelector(int leftOutputFrom, int rightOutputFrom, int outputCh1ToMixer, int outputCh3ToMixer) {
    int masterEnable = (reg_SOUNDCNT_MIX & 0x80) ? 1 : 0;
    reg_SOUNDCNT_MIX = (u8)((masterEnable << 7) | (outputCh3ToMixer << 5) | (outputCh1ToMixer << 4) | (rightOutputFrom << 2) | (leftOutputFrom));
}
