#ifndef GUARD_NNS_SND_HEAP_H
#define GUARD_NNS_SND_HEAP_H

struct NNSSndHeap;
typedef struct NNSSndHeap* NNSSndHeapHandle;

NNSSndHeapHandle * NNS_SndHeapCreate(void * start, u32 size);
int NNS_SndHeapSaveState(NNSSndHeapHandle * heap);
void NNS_SndHeapLoadState(NNSSndHeapHandle * heap, int level);

#endif //GUARD_NNS_SND_HEAP_H
