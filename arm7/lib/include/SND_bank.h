#ifndef GUARD_SND_BANK_H
#define GUARD_SND_BANK_H

#include "nitro/SND_bank_shared.h"
#include "nitro/types.h"

BOOL SND_ReadInstData(const struct SNDBankData *bankData, s32 program, s32 midiKey, struct SNDInstData *instData);
const struct SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, s32 wave);
BOOL SND_NoteOn(struct SNDExChannel *chn, s32 midiKey, s32 velocity, s32 length, const struct SNDBankData *bankData, const struct SNDInstData *instData);

#endif //GUARD_SND_BANK_H
