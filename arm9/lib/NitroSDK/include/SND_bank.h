#ifndef GUARD_SND_BANK_H
#define GUARD_SND_BANK_H

#include "nitro/types.h"
#include "SND_main.h"
#include "nitro/SND_bank_shared.h"

void SND_AssignWaveArc(struct SNDBankData *bankData, s32 index, struct SNDWaveArc *waveArc);
void SND_DestroyBank(struct SNDBankData *bankData);
void SND_DestroyWaveArc(struct SNDWaveArc *waveArc);
struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData *bankData);
BOOL SND_GetNextInstData(const struct SNDBankData *bankData, struct SNDInstData *instData, struct SNDInstPos *instPos);
u32 SND_GetWaveDataCount(const struct SNDWaveArc *waveArc);
void SND_SetWaveDataAddress(struct SNDWaveArc *waveArc, s32 index, const struct SNDWaveData *waveData);
const struct SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, s32 index);

#endif // GUARD_SND_BANK_H
