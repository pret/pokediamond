#ifndef GUARD_NNS_SND_ARC_LOADER_H
#define GUARD_NNS_SND_ARC_LOADER_H

#include "NNS_SND_heap.h"

BOOL NNS_SndArcLoadGroup(int groupNo, NNSSndHeapHandle * heap);
BOOL NNS_SndArcLoadSeq(int seqNo, NNSSndHeapHandle * heap);
BOOL NNS_SndArcLoadSeqEx(int seqNo, u32 loadFlag, NNSSndHeapHandle * heap);
BOOL NNS_SndArcLoadWaveArc(int waveArcNo, NNSSndHeapHandle * heap);
BOOL NNS_SndArcLoadBank(int bankNo, NNSSndHeapHandle * heap);

#endif //GUARD_NNS_SND_ARC_LOADER_H
