#include "SND_channel.h"

#include "SND_lfo.h"

// TODO remove this extern once we actually know where this table is
extern u8 sSampleDataShiftTable[4];

u16 CalcDecayCoeff(int vol) {
    if (vol == 127)
        return 0xFFFF;
    else if (vol == 126)
        return 0x3C00;
    else if (vol < 50)
        return (u16)(vol * 2 + 1);
    else
        return (u16)(0x1E00 / (126 - vol));
}

void ExChannelSetup(struct SNDExChannel *chn, SNDExChannelCallback callback, void *callbackUserData, int priority) {
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

void ExChannelStart(struct SNDExChannel *chn, int length) {
    chn->envAttenuation = -92544;
    chn->envStatus = 0;
    chn->length = length;
    SND_StartLfo(&chn->lfo);
    chn->flags.start = TRUE;
    chn->flags.active = TRUE;
}

int ExChannelVolumeCmp(struct SNDExChannel *chn_a, struct SNDExChannel *chn_b) {
    int vol_a = chn_a->volume & 0xFF;
    int vol_b = chn_b->volume & 0xFF;

    vol_a <<= 4;
    vol_b <<= 4;

    vol_a >>= sSampleDataShiftTable[chn_a->volume >> 8];
    vol_b >>= sSampleDataShiftTable[chn_b->volume >> 8];

    if (vol_a != vol_b) {
        if (vol_a < vol_b)
            return 1;
        else
            return -1;
    }
    return 0;
}

int ExChannelSweepUpdate(struct SNDExChannel *chn, BOOL step) {
    s64 result;

    if (chn->sweepPitch == 0) {
        result = 0;
    } else if (chn->sweepCounter >= chn->sweepLength) {
        result = 0;
    } else {
        result = (s64)chn->sweepPitch * (chn->sweepLength - chn->sweepCounter) / chn->sweepLength;

        if (step && chn->flags.autoSweep)
            chn->sweepCounter++;
    }

    return (int)result;
}

int ExChannelLfoUpdate(struct SNDExChannel *chn, BOOL step) {
    s64 result = SND_GetLfoValue(&chn->lfo);

    if (result != 0) {
        switch (chn->lfo.param.target) {
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

    if (step) {
        SND_UpdateLfo(&chn->lfo);
    }

    return (int)result;
}
