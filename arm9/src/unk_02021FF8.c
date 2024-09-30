#include "unk_02021FF8.h"

#include "global.h"

#include "heap.h"
#include "string16.h"

struct UnkStruct_020220C4 *sub_020220C4(u8 *a0, u32 a1, void (*a2)(s32, s32, u32), u32 a3, HeapID heapId) {
    struct UnkStruct_020220C4 *ret;
    s32 i;
    GF_ASSERT(a1 != 0);
    ret = AllocFromHeap(heapId, sizeof(struct UnkStruct_020220C4));
    if (ret != NULL) {
        ret->field_0  = a0;
        ret->field_4  = a1;
        ret->field_8  = a2;
        ret->field_C  = a3;
        ret->field_10 = AllocFromHeap(heapId, a1 * sizeof(struct UnkStruct_020220C4_sub));
        if (ret->field_10 != NULL) {
            for (i = 0; i < a1; i++) {
                sub_02022120(&ret->field_10[i]);
            }
        } else {
            FreeToHeap(ret);
            ret = NULL;
        }
    }
    return ret;
}

void sub_02022120(struct UnkStruct_020220C4_sub *sub) {
    sub->field_0 = 0;
    sub->field_1 = 0;
    sub->field_2 = 0;
}

void sub_0202212C(struct UnkStruct_020220C4 *unk) {
    GF_ASSERT(unk != NULL);
    FreeToHeap(unk->field_10);
    FreeToHeap(unk);
}

extern u16 sub_02020A98(void);
extern u16 sub_02020AA4(void);
extern u8 sub_02020A40(u8 *a0);
extern u8 sub_02020A6C(u8 *a0);

s32 (*const UNK_020EE6CC[])(struct UnkStruct_020220C4_sub *a0, u32 a1, u32 a2) = {
    sub_020221EC,
    sub_02022208
};

void sub_02022144(struct UnkStruct_020220C4 *unk) {
    u32 sp4;
    u32 sp0 = sub_02020A98();
    s32 i;
    s32 r1;
    if (sp0 != 0) {
        sp4 = sub_02020AA4();
        for (i = 0; i < unk->field_4; i++) {
            u8 res;
            if (unk->field_10[i].field_1 != 0) {
                res = sub_02020A40(&unk->field_0[4 * i]);
            } else {
                res = sub_02020A6C(&unk->field_0[4 * i]);
            }
            unk->field_10[i].field_1 = res;
        }
    } else {
        sp4 = 0;
        for (i = 0; i < unk->field_4; i++) {
            unk->field_10[i].field_1 = 0;
        }
    }
    for (i = 0; i < unk->field_4; i++) {
        r1 = UNK_020EE6CC[unk->field_10[i].field_0](&unk->field_10[i], sp0, sp4);
        if (r1 != -1) {
            unk->field_8(i, r1, unk->field_C);
        }
    }
}

s32 sub_020221EC(struct UnkStruct_020220C4_sub *a0, u32 a1, u32 a2) {
#pragma unused(a1)
    if (a0->field_1 && a2) {
        sub_0202223C(a0, 1);
        return 0;
    }
    return -1;
}

s32 sub_02022208(struct UnkStruct_020220C4_sub *a0, u32 a1, u32 a2) {
#pragma unused(a2)
    if (a0->field_1) {
        if (a0->field_2 < 0xFFFF) {
            a0->field_2++;
        }
        return 2;
    } else if (a1) {
        sub_0202223C(a0, 0);
        return 3;
    }
    sub_0202223C(a0, 0);
    return 1;
}

void sub_0202223C(struct UnkStruct_020220C4_sub *a0, u8 a1) {
    a0->field_0 = a1;
    a0->field_2 = 0;
}
