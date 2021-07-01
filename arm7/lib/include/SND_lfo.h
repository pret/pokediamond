#ifndef GUARD_SND_LFO_H
#define GUARD_SND_LFO_H

#include "nitro/types.h"

#include "nitro/SND_main_shared.h"

void SND_InitLfoParam(struct SNDLfoParam *lfoParam);
void SND_StartLfo(struct SNDLfo *lfo);
void SND_UpdateLfo(struct SNDLfo *lfo);
s32 SND_LfoGetValue(struct SNDLfo *lfo);

#endif //GUARD_SND_LFO_H
