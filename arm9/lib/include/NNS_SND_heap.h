#ifndef GUARD_NNS_SND_HEAP_H
#define GUARD_NNS_SND_HEAP_H

struct NNSSndHeap;
typedef struct NNSSndHeap* NNSSndHeapHandle;

NNSSndHeapHandle * NNS_SndHeapCreate(void *, u32);
int NNS_SndHeapSaveState(NNSSndHeapHandle *);
void NNS_SndHeapLoadState(NNSSndHeapHandle *, int);

#endif //GUARD_NNS_SND_HEAP_H
