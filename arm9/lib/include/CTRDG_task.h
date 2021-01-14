#ifndef POKEDIAMOND_CTRDG_TASK_H
#define POKEDIAMOND_CTRDG_TASK_H

#include "nitro/types.h"

struct CTRDGTaskInfo_tag;

typedef u32 (*CTRDG_TASK_FUNC) (struct CTRDGTaskInfo_tag *);

typedef struct CTRDGTaskInfo_tag
{
    CTRDG_TASK_FUNC task;
    CTRDG_TASK_FUNC callback;
    u32 result;
    u8 *data;
    u8 *adr;
    u32 offset;
    u32 size;
    u8 *dst;
    u16 sec_num;
    u8 busy;
    u8 param[1];
} CTRDGTaskInfo;

#endif //POKEDIAMOND_CTRDG_TASK_H
