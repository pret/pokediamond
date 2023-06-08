#include "SND_bank.h"

#include "SND_exChannel.h"
#include "SND_main.h"

#include "mmap.h"
#include "code32.h"

static const struct SNDWaveData *GetWaveData(
    const struct SNDBankData *bankData, s32 waveArc, s32 wave);

BOOL SND_ReadInstData(
    const struct SNDBankData *bankData, s32 program, s32 midiKey, struct SNDInstData *instData)
{
    s32 i;
    struct SNDDrumSet *drumSet;
    struct SNDKeySplit *keySplit;
    u32 off;
    u8 minKey, maxKey;

    if (program < 0)
        return FALSE;

    SNDi_LockMutex();

    if (program >= bankData->instCount)
    {
        SNDi_UnlockMutex();
        return FALSE;
    }

    off = bankData->instOffsets[program];
    instData->type = SND_INST_OFFSET_TYPE(off);

    switch (instData->type)
    {
        case SND_INST_PCM:
        case SND_INST_PSG:
        case SND_INST_NOISE:
        case SND_INST_DIRECTPCM:
        case SND_INST_DUMMY:
            instData->param = *SND_INST_OFFSET_NORMAL(bankData, off);
            break;
        case SND_INST_DRUM_TABLE:
            drumSet = SND_INST_OFFSET_DRUMS(bankData, off);

            // seperate variables needed for matching
            maxKey = drumSet->maxKey;
            minKey = drumSet->minKey;

            if (midiKey < minKey || midiKey > maxKey)
            {
                SNDi_UnlockMutex();
                return FALSE;
            }

            *instData = drumSet->instruments[midiKey - drumSet->minKey];
            break;
        case SND_INST_KEY_SPLIT:
            i = 0;
            keySplit = SND_INST_OFFSET_KEYSPL(bankData, off);

            while (midiKey > keySplit->key[i])
            {
                i++;
                if (i >= SND_INST_MAX_KEYSPLIT)
                {
                    SNDi_UnlockMutex();
                    return FALSE;
                }
            }
            *instData = keySplit->instruments[i];
            break;
        case SND_INST_ILLEGAL:
        default:
            SNDi_UnlockMutex();
            return FALSE;
    }

    SNDi_UnlockMutex();
    return TRUE;
}

const struct SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, s32 wave)
{
    SNDi_LockMutex();

    const struct SNDWaveData *retval = (const struct SNDWaveData *)waveArc->waveOffsets[wave];
    if (retval != NULL)
    {
        if ((u32)retval < HW_MAIN_MEM)
        {
            retval = (const struct SNDWaveData *)((u32)waveArc + (u32)retval);
        }
    }
    else
    {
        retval = NULL;
    }

    SNDi_UnlockMutex();

    return retval;
}

BOOL SND_NoteOn(struct SNDExChannel *chn,
    s32 midiKey,
    s32 velocity,
    s32 length,
    const struct SNDBankData *bankData,
    const struct SNDInstData *instData)
{
    const struct SNDWaveData *waveData;
    u8 release;
    BOOL success;

    release = instData->param.envRelease;

    if (release == 0xFF)
    {
        length = -1;
        release = 0;
    }

    switch (instData->type)
    {
        case SND_INST_PCM:
        case SND_INST_DIRECTPCM:
            if (instData->type == SND_INST_PCM)
            {
                waveData = GetWaveData(bankData, instData->param.wave[1], instData->param.wave[0]);
            }
            else
            {
                waveData = (const struct SNDWaveData *)((instData->param.wave[1] << 16) |
                                                        instData->param.wave[0]);
            }

            if (waveData == NULL)
            {
                success = FALSE;
            }
            else
            {
                success =
                    SND_StartExChannelPcm(chn, &waveData->param, waveData->sampleData, length);
            }
            break;
        case SND_INST_PSG:
            success = SND_StartExChannelPsg(chn, instData->param.wave[0], length);
            break;
        case SND_INST_NOISE:
            success = SND_StartExChannelNoise(chn, length);
            break;
        default:
            success = FALSE;
            break;
    }

    if (success == FALSE)
    {
        return FALSE;
    }
    else
    {
        chn->midiKey = (u8)midiKey;
        chn->rootMidiKey = instData->param.rootKey;
        chn->velocity = (u8)velocity;
        SND_SetExChannelAttack(chn, instData->param.envAttack);
        SND_SetExChannelDecay(chn, instData->param.envDecay);
        SND_SetExChannelSustain(chn, instData->param.envSustain);
        SND_SetExChannelRelease(chn, release);
        chn->initPan = (s8)(instData->param.pan - 0x40);
        return TRUE;
    }
}

static const struct SNDWaveData *GetWaveData(
    const struct SNDBankData *bankData, s32 waveArc, s32 wave)
{
    const struct SNDWaveArc *arcPtr = bankData->waveArcLinks[waveArc].waveArc;

    if (arcPtr == NULL)
    {
        return NULL;
    }
    else if (wave < arcPtr->waveCount)
    {
        return SND_GetWaveDataAddress(arcPtr, wave);
    }
    else
    {
        return NULL;
    }
}
