#include "nitro.h"
#include "NNS_FND_heapcommon.h"
#include "NNS_FND_list.h"

BOOL sRootListInitialized;
NNSFndList sRootList;

static inline void NNSi_FndHeapHeadSetOptionFlag(NNSiFndHeapHead *pHead, u8 option_flag)
{
    pHead->attribute &= ~0xFF;
    pHead->attribute |= option_flag;
}

void *NNS_FndGetNextListObject(NNSFndList *, void *);

NNSiFndHeapHead* FindContainHeap(NNSFndList * pList, const void * memBlock)
{
    NNSiFndHeapHead * pHead = NULL;

    while ((pHead = NNS_FndGetNextListObject(pList, pHead)) != NULL)
    {
        if (pHead->heapStart <= memBlock && memBlock < pHead->heapEnd)
        {
            NNSiFndHeapHead * ret = FindContainHeap(&pHead->childList, memBlock);
            if (ret == NULL)
                ret = pHead;
            return ret;
        }
    }
    return NULL;
}

NNSFndList* FindListContainHeap(const void * memBlock)
{
    NNSFndList* ret = &sRootList;
    NNSiFndHeapHead* pHead = FindContainHeap(&sRootList, memBlock);
    if (pHead != NULL)
        ret = &pHead->childList;
    return ret;
}

void NNSi_FndInitHeapHead(NNSiFndHeapHead *pHead, u32 signature, void* heapStart, void* heapEnd, u16 optionFlag)
{
    pHead->signature = signature;
    pHead->heapStart = heapStart;
    pHead->heapEnd = heapEnd;
    pHead->attribute = 0;
    NNSi_FndHeapHeadSetOptionFlag(pHead, optionFlag);
    NNS_FndInitList(&pHead->childList, 4);
    if (!sRootListInitialized)
    {
        NNS_FndInitList(&sRootList, 4);
        sRootListInitialized = TRUE;
    }
    NNS_FndAppendListObject(FindListContainHeap(pHead), pHead);
}

void NNSi_FndFinalizeHeap(NNSiFndHeapHead *pHead)
{
    NNS_FndRemoveListObject(FindListContainHeap(pHead), pHead);
}
