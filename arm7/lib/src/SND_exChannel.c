#include "SND_exChannel.h"

#include "SND_channel.h"
#include "SND_main.h"
#include "SND_util.h"
#include "SND_work.h"

#include "registers.h"

// TODO import these tables into here if we have a working .rodata section
extern const u8 sChannelAllocationOrder[SND_CHANNEL_COUNT];
extern const u8 sAttackCoeffTable[19];
extern const u8 sSampleDataShiftTable[4];

static u32 sLockedChannelMask;
static u32 sWeakLockedChannelMask;

static u16 CalcDecayCoeff(int vol);

static int ExChannelSweepUpdate(struct SNDExChannel *chn, BOOL step);
static int ExChannelLfoUpdate(struct SNDExChannel *chn, BOOL step);
static void ExChannelStart(struct SNDExChannel *chn, int length);
static int ExChannelVolumeCmp(struct SNDExChannel *chn_a, struct SNDExChannel *chn_b);
static void ExChannelSetup(
    struct SNDExChannel *, SNDExChannelCallback callback, void *callbackUserData, int priority);

void SND_ExChannelInit(void)
{
    struct SNDExChannel *chn;
    s32 i;

    for (i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        chn = &SNDi_Work.channels[i];

        chn->id = (u8)i;
        chn->flags.syncFlag = 0;
        chn->flags.active = FALSE;
    }

    sLockedChannelMask = 0;
    sWeakLockedChannelMask = 0;
}

void SND_UpdateExChannel(void)
{
    struct SNDExChannel *chn;
    s32 i;

    for (i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        chn = &SNDi_Work.channels[i];

        if (chn->flags.syncFlag == 0)
            continue;

        if (chn->flags.syncFlag & SND_CHN_SYNC_STOP)
            SND_StopChannel(i, 0);

        if (chn->flags.syncFlag & SND_CHN_SYNC_START)
        {
            switch (chn->type)
            {
                case SND_CHN_TYPE_PCM:
                    SND_SetupChannelPcm(i,
                        chn->waveDataPtr,
                        chn->waveParam.format,
                        chn->waveParam.loopEnabled ? 1 : 2,
                        (s32)chn->waveParam.loopStart,
                        (s32)chn->waveParam.loopLength,
                        chn->volume & 0xFF,
                        chn->volume >> 8,
                        chn->timer,
                        chn->pan);
                    break;
                case SND_CHN_TYPE_PSG:
                    SND_SetupChannelPsg(i,
                        chn->dutyCycle,
                        chn->volume & 0xFF,
                        chn->volume >> 8,
                        chn->timer,
                        chn->pan);
                    break;
                case SND_CHN_TYPE_NOISE:
                    SND_SetupChannelNoise(
                        i, chn->volume & 0xFF, chn->volume >> 8, chn->timer, chn->pan);
                    break;
            }
        }
        else
        {
            if (chn->flags.syncFlag & SND_CHN_SYNC_TIMER)
            {
                SND_SetChannelTimer(i, chn->timer);
            }
            if (chn->flags.syncFlag & SND_CHN_SYNC_VOLUME)
            {
                SND_SetChannelVolume(i, chn->volume & 0xFF, chn->volume >> 8);
            }
            if (chn->flags.syncFlag & SND_CHN_SYNC_PAN)
            {
                SND_SetChannelPan(i, chn->pan);
            }
        }
    }

    for (i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        chn = &SNDi_Work.channels[i];

        if (!chn->flags.syncFlag)
            continue;

        if (chn->flags.syncFlag & SND_CHN_SYNC_START)
            reg_SOUNDxCNT_STAT(i) |= 0x80;
        chn->flags.syncFlag = 0;
    }
}

void SND_ExChannelMain(BOOL step)
{
    struct SNDExChannel *chn;
    s32 i;
    s32 vol;
    s32 pitch;
    s32 pan;
    s32 lfo;
    u16 newTimer;

    for (i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        vol = 0;
        pitch = 0;
        pan = 0;
        chn = &SNDi_Work.channels[i];

        if (!chn->flags.active)
            continue;

        if (chn->flags.start)
        {
            chn->flags.syncFlag |= SND_CHN_SYNC_START;
            chn->flags.start = FALSE;
        }
        else if (!SND_IsChannelActive(i))
        {
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

        switch (chn->lfo.param.target)
        {
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
        if (chn->panRange != 127)
        {
            pan = (pan * chn->panRange + 0x40) >> 7;
        }
        pan += chn->userPan;

        if (chn->envStatus == SND_ENV_RELEASE && vol <= -723)
        {
            chn->flags.syncFlag = SND_CHN_SYNC_STOP;
            if (chn->callback)
                chn->callback(chn, 1, chn->callbackUserData);
            else
                chn->priority = 0;
            chn->volume = 0;
            chn->flags.active = 0;
        }
        else
        {
            vol = SND_CalcChannelVolume(vol);
            newTimer = SND_CalcTimer(chn->waveParam.timer, pitch);

            if (chn->type == SND_CHN_TYPE_PSG)
                newTimer &= 0xFFFC;

            pan += 0x40;
            if (pan < 0)
                pan = 0;
            else if (pan > 127)
                pan = 127;

            if (vol != chn->volume)
            {
                chn->volume = (u16)vol;
                chn->flags.syncFlag |= SND_CHN_SYNC_VOLUME;
            }
            if (newTimer != chn->timer)
            {
                chn->timer = (u16)newTimer;
                chn->flags.syncFlag |= SND_CHN_SYNC_TIMER;
            }
            if (pan != chn->pan)
            {
                chn->pan = (u8)pan;
                chn->flags.syncFlag |= SND_CHN_SYNC_PAN;
            }
        }
    }
}

BOOL SND_StartExChannelPcm(
    struct SNDExChannel *chn, const struct SNDWaveParam *wave, const void *data, s32 length)
{
    chn->type = SND_CHN_TYPE_PCM;
    chn->waveParam = *wave;
    chn->waveDataPtr = data;
    ExChannelStart(chn, length);
    return TRUE;
}

BOOL SND_StartExChannelPsg(struct SNDExChannel *chn, s32 duty, s32 length)
{
    if (chn->id < 8)
    {
        return FALSE;
    }
    else if (chn->id > 13)
    {
        return FALSE;
    }
    else
    {
        chn->type = SND_CHN_TYPE_PSG;
        chn->dutyCycle = duty;
        chn->waveParam.timer = 8006;
        ExChannelStart(chn, length);
        return TRUE;
    }
}

BOOL SND_StartExChannelNoise(struct SNDExChannel *chn, s32 length)
{
    if (chn->id < 14)
    {
        return FALSE;
    }
    else if (chn->id > 15)
    {
        return FALSE;
    }
    else
    {
        chn->type = SND_CHN_TYPE_NOISE;
        chn->waveParam.timer = 8006;
        ExChannelStart(chn, length);
        return TRUE;
    }
}

s32 SND_UpdateExChannelEnvelope(struct SNDExChannel *chn, BOOL step)
{
    s32 sustain;

    if (step)
    {
        switch (chn->envStatus)
        {
            case SND_ENV_ATTACK:
                chn->envAttenuation = -((-chn->envAttenuation * chn->envAttack) >> 8);
                if (chn->envAttenuation == 0)
                    chn->envStatus = SND_ENV_DECAY;
                break;
            case SND_ENV_DECAY:
                sustain = SNDi_DecibelSquareTable[chn->envSustain] << 7;
                chn->envAttenuation -= chn->envDecay;
                if (chn->envAttenuation <= sustain)
                {
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

void SND_SetExChannelAttack(struct SNDExChannel *chn, s32 attack)
{
    if (attack < 109)
        chn->envAttack = (u8)(255 - attack);
    else
        chn->envAttack = sAttackCoeffTable[127 - attack];
}

void SND_SetExChannelDecay(struct SNDExChannel *chn, s32 decay)
{
    chn->envDecay = CalcDecayCoeff(decay);
}

void SND_SetExChannelSustain(struct SNDExChannel *chn, s32 sustain)
{
    chn->envSustain = (u8)sustain;
}

void SND_SetExChannelRelease(struct SNDExChannel *chn, s32 release)
{
    chn->envRelease = CalcDecayCoeff(release);
}

void SND_ReleaseExChannel(struct SNDExChannel *chn)
{
    chn->envStatus = SND_ENV_RELEASE;
}

BOOL SND_IsExChannelActive(struct SNDExChannel *chn)
{
    return chn->flags.active;
}

struct SNDExChannel *SND_AllocExChannel(
    u32 channelMask, int priority, u32 flags, SNDExChannelCallback callback, void *callbackUserData)
{
    struct SNDExChannel *chnPrev;
    int i;
    struct SNDExChannel *chn;
    u8 channelCandidate;

    channelMask &= ~sLockedChannelMask;
    if (flags == 0)
        channelMask &= ~sWeakLockedChannelMask;

    chnPrev = NULL;

    for (i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        channelCandidate = sChannelAllocationOrder[i];

        if (channelMask & (1 << channelCandidate))
        {
            chn = &SNDi_Work.channels[channelCandidate];

            if (chnPrev == NULL)
            {
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

void SND_FreeExChannel(struct SNDExChannel *chn)
{
    if (chn)
    {
        chn->callback = NULL;
        chn->callbackUserData = NULL;
    }
}

void SND_StopUnlockedChannel(u32 channelMask, u32 weak)
{
    (void)weak;

    struct SNDExChannel *chn;

    for (int i = 0; i < SND_CHANNEL_COUNT && channelMask != 0; i++, channelMask >>= 1)
    {
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

void SND_LockChannel(u32 channelMask, u32 weak)
{
    struct SNDExChannel *chn;
    u32 j = channelMask;
    int i = 0;

    for (; i < SND_CHANNEL_COUNT && j != 0; i++, j >>= 1)
    {
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

    if (weak & 1)
    {
        sWeakLockedChannelMask |= channelMask;
    }
    else
    {
        sLockedChannelMask |= channelMask;
    }
}

void SND_UnlockChannel(u32 channelMask, u32 weak)
{
    if (weak & 1)
    {
        sWeakLockedChannelMask &= ~channelMask;
    }
    else
    {
        sLockedChannelMask &= ~channelMask;
    }
}

u32 SND_GetLockedChannel(u32 weak)
{
    if (weak & 1)
    {
        return sWeakLockedChannelMask;
    }
    else
    {
        return sLockedChannelMask;
    }
}

void SND_InvalidateWave(const void *start, const void *end)
{
    for (u8 i = 0; i < SND_CHANNEL_COUNT; i++)
    {
        struct SNDExChannel *chn = &SNDi_Work.channels[i];

        if (chn->flags.active && chn->type == 0 && start <= chn->waveDataPtr &&
            chn->waveDataPtr <= end)
        {
            chn->flags.start = FALSE;
            SND_StopChannel(i, 0);
        }
    }
}

void SND_InitLfoParam(struct SNDLfoParam *lfoParam)
{
    lfoParam->target = SND_LFO_PITCH;
    lfoParam->depth = 0;
    lfoParam->range = 1;
    lfoParam->speed = 16;
    lfoParam->delay = 0;
}

void SND_StartLfo(struct SNDLfo *lfo)
{
    lfo->counter = 0;
    lfo->delayCounter = 0;
}

void SND_UpdateLfo(struct SNDLfo *lfo)
{
    if (lfo->delayCounter < lfo->param.delay)
    {
        lfo->delayCounter++;
    }
    else
    {
        u32 tmp = lfo->counter;
        tmp += lfo->param.speed << 6;
        tmp >>= 8;
        while (tmp >= 0x80)
        {
            tmp -= 0x80;
        }
        lfo->counter += lfo->param.speed << 6;
        lfo->counter &= 0xFF;
        lfo->counter |= tmp << 8;
    }
}

int SND_GetLfoValue(struct SNDLfo *lfo)
{
    if (lfo->param.depth == 0)
    {
        return 0;
    }
    else if (lfo->delayCounter < lfo->param.delay)
    {
        return 0;
    }
    else
    {
        return SND_SinIdx((s32)((u32)lfo->counter >> 8)) * lfo->param.depth * lfo->param.range;
    }
}

static u16 CalcDecayCoeff(int vol)
{
    if (vol == 127)
        return 0xFFFF;
    else if (vol == 126)
        return 0x3C00;
    else if (vol < 50)
        return (u16)(vol * 2 + 1);
    else
        return (u16)(0x1E00 / (126 - vol));
}

static void ExChannelSetup(
    struct SNDExChannel *chn, SNDExChannelCallback callback, void *callbackUserData, int priority)
{
    chn->channelLLNext = NULL;
    chn->callback = callback;
    chn->callbackUserData = callbackUserData;
    chn->length = 0;
    chn->priority = (u8)priority;
    chn->volume = 127;
    chn->flags.start = FALSE;
    chn->flags.autoSweep = TRUE;
    chn->midiKey = 60;
    chn->rootMidiKey = 60;
    chn->velocity = 127;
    chn->initPan = 0;
    chn->userDecay = 0;
    chn->userDecay2 = 0;
    chn->userPitch = 0;
    chn->userPan = 0;
    chn->panRange = 127;
    chn->sweepPitch = 0;
    chn->sweepLength = 0;
    chn->sweepCounter = 0;

    SND_SetExChannelAttack(chn, 127);
    SND_SetExChannelDecay(chn, 127);
    SND_SetExChannelSustain(chn, 127);
    SND_SetExChannelRelease(chn, 127);
    SND_InitLfoParam(&chn->lfo.param);
}

static void ExChannelStart(struct SNDExChannel *chn, int length)
{
    chn->envAttenuation = -92544;
    chn->envStatus = 0;
    chn->length = length;
    SND_StartLfo(&chn->lfo);
    chn->flags.start = TRUE;
    chn->flags.active = TRUE;
}

static int ExChannelVolumeCmp(struct SNDExChannel *chn_a, struct SNDExChannel *chn_b)
{
    int vol_a = chn_a->volume & 0xFF;
    int vol_b = chn_b->volume & 0xFF;

    vol_a <<= 4;
    vol_b <<= 4;

    vol_a >>= sSampleDataShiftTable[chn_a->volume >> 8];
    vol_b >>= sSampleDataShiftTable[chn_b->volume >> 8];

    if (vol_a != vol_b)
    {
        if (vol_a < vol_b)
            return 1;
        else
            return -1;
    }
    return 0;
}

static int ExChannelSweepUpdate(struct SNDExChannel *chn, BOOL step)
{
    s64 result;

    if (chn->sweepPitch == 0)
    {
        result = 0;
    }
    else if (chn->sweepCounter >= chn->sweepLength)
    {
        result = 0;
    }
    else
    {
        result = (s64)chn->sweepPitch * (chn->sweepLength - chn->sweepCounter) / chn->sweepLength;

        if (step && chn->flags.autoSweep)
            chn->sweepCounter++;
    }

    return (int)result;
}

static int ExChannelLfoUpdate(struct SNDExChannel *chn, BOOL step)
{
    s64 result = SND_GetLfoValue(&chn->lfo);

    if (result != 0)
    {
        switch (chn->lfo.param.target)
        {
            case SND_LFO_VOLUME:
                result *= 60;
                break;
            case SND_LFO_PITCH:
                result <<= 6;
                break;
            case SND_LFO_PAN:
                result <<= 6;
                break;
        }
        result >>= 14;
    }

    if (step)
    {
        SND_UpdateLfo(&chn->lfo);
    }

    return (int)result;
}
