#include "SND_bank.h"
#include "OS_mutex.h"

void OS_LockMutex(struct OSMutex *);
void OS_UnlockMutex(struct OSMutex *);
void DC_StoreRange(const void *, u32);

/*
 * WaveArc linking seems to work like the following:
 *
 * Each SNDBankData can have up to 4 WaveArcs assigned.
 * To avoid loading the same WaveArc by multiple banks,
 * a linked list using WaveArcLinks is chained through all banks
 * which use a WaveArc.
 *
 * That WaveArc has a head pointer, which points to the first
 * WaveArcLink in that chain of banks.
 */

/*
 * Set bank's wavearc link at index to specified wavearc
 */
ARM_FUNC void SND_AssignWaveArc(struct SNDBankData *bankData, s32 index, struct SNDWaveArc *waveArc) {
    SNDi_LockMutex();
    struct SNDWaveArc *selectedWaveArc = bankData->waveArcLinks[index].waveArc;
    if (selectedWaveArc != NULL) {
        if (waveArc == selectedWaveArc) {
            SNDi_UnlockMutex();
            return;
        }

        if (&bankData->waveArcLinks[index] == selectedWaveArc->waveArcLLHead) {
            selectedWaveArc->waveArcLLHead = bankData->waveArcLinks[index].waveArcLLnext;
            DC_StoreRange(bankData->waveArcLinks[index].waveArc, sizeof(struct SNDWaveArc));
        } else {
            struct SNDWaveArcLink *cur;
            for (cur = selectedWaveArc->waveArcLLHead; cur != NULL; cur = cur->waveArcLLnext) {
                if (&bankData->waveArcLinks[index] == cur->waveArcLLnext)
                    break;
            }
            cur->waveArcLLnext = bankData->waveArcLinks[index].waveArcLLnext;
            DC_StoreRange(cur, sizeof(*cur));
        }
    }
    struct SNDWaveArcLink *oldHead = waveArc->waveArcLLHead;
    waveArc->waveArcLLHead = &bankData->waveArcLinks[index];
    bankData->waveArcLinks[index].waveArcLLnext = oldHead;
    bankData->waveArcLinks[index].waveArc = waveArc;
    // BUG: Shouldn't the mutex unlock be after writing to cache?
    SNDi_UnlockMutex();
    DC_StoreRange(bankData, sizeof(*bankData));
    DC_StoreRange(waveArc, sizeof(*waveArc));
}

ARM_FUNC void SND_DestroyBank(struct SNDBankData *bankData) {
    SNDi_LockMutex();

    for (s32 i = 0; i < SND_BANK_MAX_WAVEARC; i++) {
        struct SNDWaveArcLink *curWaveArcLink = &bankData->waveArcLinks[i];
        struct SNDWaveArc *curWaveArc = bankData->waveArcLinks[i].waveArc;

        if (curWaveArc == NULL)
            continue;

        if (curWaveArcLink == curWaveArc->waveArcLLHead) {
            curWaveArc->waveArcLLHead = bankData->waveArcLinks[i].waveArcLLnext;
            DC_StoreRange(curWaveArc, sizeof(*curWaveArc));
        } else {
            struct SNDWaveArcLink *cur;
            for (cur = curWaveArc->waveArcLLHead; cur != NULL; cur = cur->waveArcLLnext) {
                if (&bankData->waveArcLinks[i] == cur->waveArcLLnext)
                    break;
            }
            cur->waveArcLLnext = bankData->waveArcLinks[i].waveArcLLnext;
            DC_StoreRange(cur, sizeof(*cur));
        }
    }

    SNDi_UnlockMutex();
}

ARM_FUNC void SND_DestroyWaveArc(struct SNDWaveArc *waveArc) {
    SNDi_LockMutex();
    struct SNDWaveArcLink *cur = waveArc->waveArcLLHead;

    while (cur != NULL) {
        struct SNDWaveArcLink *newCur = cur->waveArcLLnext;
        cur->waveArc = NULL;
        cur->waveArcLLnext = NULL;
        DC_StoreRange(cur, sizeof(*cur));
        cur = newCur;
    }

    SNDi_UnlockMutex();
}

ARM_FUNC struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData *bankData) {
#pragma unused (bankData)
    struct SNDInstPos retval;
    retval.program = 0;
    retval.index = 0;
    return retval;
}

ARM_FUNC static inline struct SNDDrumSet *test(const struct SNDBankData *bank, u32 off) {
    return (struct SNDDrumSet *)((u8 *)bank + (off >> 8));
}

ARM_FUNC BOOL SND_GetNextInstData(const struct SNDBankData *bankData, struct SNDInstData *instData, struct SNDInstPos *instPos) {
    while (instPos->program < bankData->instCount) {
        struct SNDDrumSet *drums;
        struct SNDKeySplit *keySplit;

        u32 instOffset = bankData->instOffsets[instPos->program];
        instData->type = SND_INST_OFFSET_TYPE(instOffset);

        switch (instData->type) {
        case SND_INST_PCM:
        case SND_INST_PSG:
        case SND_INST_NOISE:
        case SND_INST_DIRECTPCM:
        case SND_INST_DUMMY:
            instData->param = *SND_INST_OFFSET_NORMAL(bankData, instOffset);
            instPos->program++;
            return TRUE;
        case SND_INST_DRUM_TABLE:
            drums = SND_INST_OFFSET_DRUMS(bankData, instOffset);
            // silly programming 101: put a loop in a place that never loops
            for (; instPos->index < drums->maxKey - drums->minKey + 1;) {
                *instData = drums->instruments[instPos->index];
                instPos->index++;
                return TRUE;
            }
            break;
        case SND_INST_KEY_SPLIT:
            keySplit = SND_INST_OFFSET_KEYSPL(bankData, instOffset);
            for (; instPos->index < SND_INST_MAX_KEYSPLIT;) {
                if (keySplit->key[instPos->index] == 0)
                    break;
                *instData = keySplit->instruments[instPos->index];
                instPos->index++;
                return TRUE;
            }
            break;
        }

        instPos->program++;
        instPos->index = 0;
    }
    return FALSE;
}

ARM_FUNC u32 SND_GetWaveDataCount(const struct SNDWaveArc *waveArc) {
    return waveArc->waveCount;
}

ARM_FUNC void SND_SetWaveDataAddress(struct SNDWaveArc *waveArc, s32 index, const struct SNDWaveData *waveData) {
    SNDi_LockMutex();
    waveArc->waveOffsets[index] = (u32)waveData;
    DC_StoreRange(&waveArc->waveOffsets[index], sizeof(u32));
    SNDi_UnlockMutex();
}

ARM_FUNC const struct SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, s32 index) {
    SNDi_LockMutex();
    u32 retval = waveArc->waveOffsets[index];
    if (retval != 0) {
        // < 0x2000000 aka, not a pointer to main RAM
        if (retval < 0x2000000)
            retval = (u32)&((u8 *)waveArc)[retval];
    } else {
        retval = 0;
    }
    SNDi_UnlockMutex();
    return (struct SNDWaveData *)retval;
}
