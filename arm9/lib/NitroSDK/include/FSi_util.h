#ifndef NITRO_FSI_UTIL_H_
#define NITRO_FSI_UTIL_H_

#include "CARD_common.h"

#define ALIGN_BYTE(n, a) (((u32)(n) + ALIGN_MASK(a)) & ~ALIGN_MASK(a))

#define BIT_MASK(a) ((u32)((1 << (a)) - 1))

static inline BOOL FSi_IsSlash(u32 c)
{
    return (c == '/') || (c == '\\');
}

static inline void FSi_CutFromListCore(FSFileLink *trg)
{
    FSFile *const pr = trg->prev;
    FSFile *const nx = trg->next;
    if (pr)
        pr->link.next = nx;
    if (nx)
        nx->link.prev = pr;
}

static inline void FSi_CutFromList(FSFile *elem)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    trg->next = trg->prev = NULL;
}

static inline void FSi_AppendToList(FSFile *elem, FSFile *list)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    {
        while (list->link.next)
            list = list->link.next;
        list->link.next = elem;
        trg->prev = list;
        trg->next = NULL;
    }
}


#endif //NITRO_FSI_UTIL_H_
