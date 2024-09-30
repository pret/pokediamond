#ifndef POKEDIAMOND_UNK_02088AAC_H
#define POKEDIAMOND_UNK_02088AAC_H

#include "bag.h"
#include "main.h"
#include "unk_0208890C.h"

struct UnkStruct_02088AAC {
    HeapID heapId;
    u16 unk04;
    u16 unk06;
    u32 item;
    struct BagCursor *unk0C;
    struct PoffinCaseAppData *poffinCaseAppData;
    u32 unk14;
    void *ovly_param;
    struct OverlayManager *ovly_data;
    u32 unk20;
};

u32 sub_02088AAC(struct UnkStruct_02088AAC *r0, u32 *r1);
u32 sub_02088AFC(struct UnkStruct_02088AAC *r0);
u32 sub_02088B28(struct UnkStruct_02088AAC *r0);
u32 sub_02088B48(void);
u32 sub_02088B4C(struct UnkStruct_02088AAC *r0);
u32 sub_02088BA8(struct UnkStruct_02088AAC *r0);
u32 sub_02088C3C(struct UnkStruct_02088AAC *r0);
u32 sub_02088CDC(struct UnkStruct_02088AAC *r0);

#endif // POKEDIAMOND_UNK_02088AAC_H
