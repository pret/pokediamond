#include "SND_exChannel.h"

#include "SND_channel.h"
#include "SND_main.h"
#include "SND_work.h"
#include "SND_util.h"

#include "registers.h"

// TODO import these tables into here if they belong here
extern u8 sChannelAllocationOrder[SND_CHANNEL_COUNT];
extern u8 sAttackCoeffTable[19];

static u32 sLockedChannelMask;
static u32 sWeakLockedChannelMask;

void SND_ExChannelInit(void) {
    struct SNDExChannel *chn;
    s32 i;

    for (i = 0; i < SND_CHANNEL_COUNT; i++) {
        chn = &SNDi_Work.channels[i];
        
        chn->id = (u8)i;
        chn->flags.syncFlag = 0;
        chn->flags.active = FALSE;
    }

    sLockedChannelMask = 0;
    sWeakLockedChannelMask = 0;
}

void SND_UpdateExChannel(void) {
    struct SNDExChannel *chn;
    s32 i;

    for (i = 0; i < SND_CHANNEL_COUNT; i++) {
        chn = &SNDi_Work.channels[i];

        if (chn->flags.syncFlag == 0)
            continue;

        if (chn->flags.syncFlag & SND_CHN_SYNC_STOP)
            SND_StopChannel(i, 0);
        
        if (chn->flags.syncFlag & SND_CHN_SYNC_START) {
            switch (chn->type) {
            case SND_CHN_TYPE_PCM:
                SND_SetupChannelPcm(
                    i,
                    chn->waveDataPtr,
                    chn->waveParam.format,
                    chn->waveParam.loopEnabled ? 1 : 2,
                    (s32)chn->waveParam.loopStart,
                    (s32)chn->waveParam.loopLength,
                    chn->volume & 0xFF,
                    chn->volume >> 8,
                    chn->timer,
                    chn->pan
                );
                break;
            case SND_CHN_TYPE_PSG:
                SND_SetupChannelPsg(
                    i,
                    chn->dutyCycle,
                    chn->volume & 0xFF,
                    chn->volume >> 8,
                    chn->timer,
                    chn->pan
                );
                break;
            case SND_CHN_TYPE_NOISE:
                SND_SetupChannelNoise(
                    i,
                    chn->volume & 0xFF,
                    chn->volume >> 8,
                    chn->timer,
                    chn->pan
                );
                break;
            }
        } else {
            if (chn->flags.syncFlag & SND_CHN_SYNC_TIMER) {
                SND_SetChannelTimer(i, chn->timer);
            }
            if (chn->flags.syncFlag & SND_CHN_SYNC_VOLUME) {
                SND_SetChannelVolume(i, chn->volume & 0xFF, chn->volume >> 8);
            }
            if (chn->flags.syncFlag & SND_CHN_SYNC_PAN) {
                SND_SetChannelPan(i, chn->pan);
            }
        }
    }

    for (i = 0; i < SND_CHANNEL_COUNT; i++) {
        chn = &SNDi_Work.channels[i];

        if (!chn->flags.syncFlag)
            continue;
        
        if (chn->flags.syncFlag & SND_CHN_SYNC_START)
            reg_SOUNDxCNT_STAT(i) |= 0x80;
        chn->flags.syncFlag = 0;
    }
}

void SND_ExChannelMain(BOOL step) {
    struct SNDExChannel *chn;
    s32 i;
    s32 vol;
    s32 pitch;
    s32 pan;
    s32 lfo;
    u16 newTimer;

    for (i = 0; i < SND_CHANNEL_COUNT; i++) {
        vol = 0;
        pitch = 0;
        pan = 0;
        chn = &SNDi_Work.channels[i];

        if (!chn->flags.active)
            continue;
        
        if (chn->flags.start) {
            chn->flags.syncFlag |= SND_CHN_SYNC_START;
            chn->flags.start = FALSE;
        } else if (!SND_IsChannelActive(i)) {
            if (chn->callback)
                chn->callback(chn, 1, chn->callbackUserData);
            else
                chn->priority = 0;
            chn->volume = 0;
            chn->flags.active = FALSE;
            continue;
        }
        
        vol += SNDi_DecibelSquareTable[chn->velocity];
        pitch += (chn->midiKey - chn->rootMidiKey) * 0x40;

        vol += SND_UpdateExChannelEnvelope(chn, step);
        pitch += ExChannelSweepUpdate(chn, step);

        vol += chn->userDecay;
        vol += chn->userDecay2;
        pitch += chn->userPitch;

        lfo = ExChannelLfoUpdate(chn, step);

        switch (chn->lfo.param.target) {
        case SND_LFO_VOLUME:
            if (vol > -0x8000)
                vol += lfo;
            break;
        case SND_LFO_PAN:
            pan += lfo;
            break;
        case SND_LFO_PITCH:
            pitch += lfo;
            break;
        }

        pan += chn->initPan;
        if (chn->panRange != 127) {
            pan = (pan * chn->panRange + 0x40) >> 7;
        }
        pan += chn->userPan;

        if (chn->envStatus == SND_ENV_RELEASE && vol <= -723) {
            chn->flags.syncFlag = SND_CHN_SYNC_STOP;
            if (chn->callback)
                chn->callback(chn, 1, chn->callbackUserData);
            else
                chn->priority = 0;
            chn->volume = 0;
            chn->flags.active = 0;
        } else {
            vol = SND_CalcChannelVolume(vol);
            newTimer = SND_CalcTimer(chn->waveParam.timer, pitch);

            if (chn->type == SND_CHN_TYPE_PSG)
                newTimer &= 0xFFFC;
            
            pan += 0x40;
            if (pan < 0)
                pan = 0;
            else if (pan > 127)
                pan = 127;
            
            if (vol != chn->volume) {
                chn->volume = (u16)vol;
                chn->flags.syncFlag |= SND_CHN_SYNC_VOLUME;
            }
            if (newTimer != chn->timer) {
                chn->timer = (u16)newTimer;
                chn->flags.syncFlag |= SND_CHN_SYNC_TIMER;
            }
            if (pan != chn->pan) {
                chn->pan = (u8)pan;
                chn->flags.syncFlag |= SND_CHN_SYNC_PAN;
            }
        }
    }
}

BOOL SND_StartExChannelPcm(struct SNDExChannel *chn, const struct SNDWaveParam *wave, const void *data, s32 length) {
    chn->type = SND_CHN_TYPE_PCM;
    chn->waveParam = *wave;
    chn->waveDataPtr = data;
    ExChannelStart(chn, length);
    return TRUE;
}

BOOL SND_StartExChannelPsg(struct SNDExChannel *chn, s32 duty, s32 length) {
    if (chn->id < 8) {
        return FALSE;
    } else if (chn->id > 13) {
        return FALSE;
    } else {
        chn->type = SND_CHN_TYPE_PSG;
        chn->dutyCycle = duty;
        chn->waveParam.timer = 8006;
        ExChannelStart(chn, length);
        return TRUE;
    }
}

BOOL SND_StartExChannelNoise(struct SNDExChannel *chn, s32 length) {
    if (chn->id < 14) {
        return FALSE;
    } else if (chn->id > 15) {
        return FALSE;
    } else {
        chn->type = SND_CHN_TYPE_NOISE;
        chn->waveParam.timer = 8006;
        ExChannelStart(chn, length);
        return TRUE;
    }
}

s32 SND_UpdateExChannelEnvelope(struct SNDExChannel *chn, BOOL step) {
    s32 sustain;

    if (step) {
        switch (chn->envStatus) {
        case SND_ENV_ATTACK:
            chn->envAttenuation = -((-chn->envAttenuation * chn->envAttack) >> 8);
            if (chn->envAttenuation == 0)
                chn->envStatus = SND_ENV_DECAY;
            break;
        case SND_ENV_DECAY:
            sustain = SNDi_DecibelSquareTable[chn->envSustain] << 7;
            chn->envAttenuation -= chn->envDecay;
            if (chn->envAttenuation <= sustain) {
                chn->envAttenuation = sustain;
                chn->envStatus = SND_ENV_SUSTAIN;
            }
            break;
        case SND_ENV_SUSTAIN:
            break;
        case SND_ENV_RELEASE:
            chn->envAttenuation -= chn->envRelease;
            break;
        }
    }

    return chn->envAttenuation >> 7;
}

void SND_SetExChannelAttack(struct SNDExChannel *chn, s32 attack) {
    if (attack < 109)
        chn->envAttack = (u8)(255 - attack);
    else
        chn->envAttack = sAttackCoeffTable[127 - attack];
}

void SND_SetExChannelDecay(struct SNDExChannel *chn, s32 decay) {
    chn->envDecay = CalcDecayCoeff(decay);
}

void SND_SetExChannelSustain(struct SNDExChannel *chn, s32 sustain) {
    chn->envSustain = (u8)sustain;
}

void SND_SetExChannelRelease(struct SNDExChannel *chn, s32 release) {
    chn->envRelease = CalcDecayCoeff(release);
}

void SND_ReleaseExChannel(struct SNDExChannel *chn) {
    chn->envStatus = SND_ENV_RELEASE;
}

BOOL SND_IsExChannelActive(struct SNDExChannel *chn) {
    return chn->flags.active;
}

struct SNDExChannel *SND_AllocExChannel(u32 channelMask, int priority, u32 flags, SNDExChannelCallback callback, void *callbackUserData) {
    struct SNDExChannel *chnPrev;
    int i;
    struct SNDExChannel *chn;
    u8 channelCandidate;

    channelMask &= ~sLockedChannelMask;
    if (flags == 0)
        channelMask &= ~sWeakLockedChannelMask;

    chnPrev = NULL;

    for (i = 0; i < SND_CHANNEL_COUNT; i++) {
        channelCandidate = sChannelAllocationOrder[i];

        if (channelMask & (1 << channelCandidate)) {
            chn = &SNDi_Work.channels[channelCandidate];

            if (chnPrev == NULL) {
                chnPrev = chn;
                continue;
            }
            
            if (chn->priority > chnPrev->priority)
                continue;
            
            if (chn->priority != chnPrev->priority || ExChannelVolumeCmp(chnPrev, chn) < 0)
                chnPrev = chn;
        }
    }

    if (chnPrev == NULL)
        return NULL;
    
    if (priority < chnPrev->priority)
        return NULL;

    if (chnPrev->callback)
        chnPrev->callback(chnPrev, 0, chnPrev->callbackUserData);
    
    chnPrev->flags.syncFlag = 2;
    chnPrev->flags.active = 0;
    ExChannelSetup(chnPrev, callback, callbackUserData, priority);
    return chnPrev;
}

void SND_FreeExChannel(struct SNDExChannel *chn) {
    if (chn) {
        chn->callback = NULL;
        chn->callbackUserData = NULL;
    }
}

void SND_StopUnlockedChannel(u32 channelMask, u32 weak) {
    (void)weak;

    struct SNDExChannel *chn;
    
    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1) {
        if ((channelMask & 1) == 0)
            continue;
        
        chn = &SNDi_Work.channels[i];

        if (sLockedChannelMask & (1 << i))
            continue;

        if (chn->callback)
            chn->callback(chn, 0, chn->callbackUserData);

        SND_StopChannel(i, 0);
        chn->priority = 0;
        SND_FreeExChannel(chn);
        chn->flags.syncFlag = 0;
        chn->flags.active = 0;
    }
}

void SND_LockChannel(u32 channelMask, u32 weak) {
    struct SNDExChannel *chn;
    u32 j = channelMask;
    int i = 0;

    for (; i < SND_CHANNEL_COUNT && j != 0; i++, j >>= 1) {
        if ((j & 1) == 0)
            continue;

        chn = &SNDi_Work.channels[i];

        if (sLockedChannelMask & (1 << i))
            continue;

        if (chn->callback)
            chn->callback(chn, 0, chn->callbackUserData);

        SND_StopChannel(i, 0);
        chn->priority = 0;
        SND_FreeExChannel(chn);
        chn->flags.syncFlag = 0;
        chn->flags.active = 0;
    }

    if (weak & 1) {
        sWeakLockedChannelMask |= channelMask;
    } else {
        sLockedChannelMask |= channelMask;
    }
}

void SND_UnlockChannel(u32 channelMask, u32 weak) {
    if (weak & 1) {
        sWeakLockedChannelMask &= ~channelMask;
    } else {
        sLockedChannelMask &= ~channelMask;
    }
}

u32 SND_GetLockedChannel(u32 weak) {
    if (weak & 1) {
        return sWeakLockedChannelMask;
    } else {
        return sLockedChannelMask;
    }
}
