#include "SND_lfo.h"

#include "SND_util.h"
#include "SND_exChannel.h"

void SND_InitLfoParam(struct SNDLfoParam *lfoParam) {
    lfoParam->target = SND_LFO_PITCH;
    lfoParam->depth = 0;
    lfoParam->range = 1;
    lfoParam->speed = 16;
    lfoParam->delay = 0;
}

void SND_StartLfo(struct SNDLfo *lfo) {
    lfo->counter = 0;
    lfo->delayCounter = 0;
}

void SND_UpdateLfo(struct SNDLfo *lfo) {
    if (lfo->delayCounter < lfo->param.delay) {
        lfo->delayCounter++;
    } else {
        u32 tmp = lfo->counter;
        tmp += lfo->param.speed << 6;
        tmp >>= 8;
        while (tmp >= 0x80) {
            tmp -= 0x80;
        }
        lfo->counter += lfo->param.speed << 6;
        lfo->counter &= 0xFF;
        lfo->counter |= tmp << 8;
    }
}

s32 SND_GetLfoValue(struct SNDLfo *lfo) {
    if (lfo->param.depth == 0) {
        return 0;
    } else if (lfo->delayCounter < lfo->param.delay) {
        return 0;
    } else {
        return SND_SinIdx((s32)((u32)lfo->counter >> 8)) * lfo->param.depth * lfo->param.range;
    }
}
