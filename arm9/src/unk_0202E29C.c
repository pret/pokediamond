#include "unk_0202E29C.h"

#include "global.h"

#include "MI_memory.h"
#include "OS_cache.h"
#include "WM_api.h"
#include "game_init.h"
#include "heap.h"
#include "mail_message.h"
#include "player_data.h"
#include "unk_0202D858.h"
#include "unk_0202F150.h"
#include "unk_02031734.h"

struct UnkStruct_0202E29C_const {
    u8 unk0[6];
};

const struct UnkStruct_0202E29C_const UNK_020EEC40 = {
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
};

u16 UNK_021C59E8;
struct UnkStruct_0202E29C *UNK_021C59F0;
u32 UNK_021C59EC;

extern u32 sub_0202CEEC();
extern u32 sub_02023AC4();
extern u32 sub_02090DB8(u32 param0, void (*param1)(u32, u32), u32 param2);
extern void sub_02090CC8(void (*param0)(), u32 param1);
extern void sub_0202CE64(void *param0);
extern void sub_0202CB70(u32 param0);
extern void sub_0202D2F4();
extern void sub_0202D0A0(void (*param0)(u32, u8 *, u32), u32 param1);
extern u32 sub_0202CBD4();
extern u32 sub_0202CBFC();
extern u32 sub_0202C570(void (*param0)(struct UnkStruct_0202E29C_sub *, u32), u8 *param1, u32 param2);
extern u32 sub_0202D21C();
extern void sub_0202C770();
extern u32 sub_0202D1E4();
extern void sub_0202D100();
extern u32 sub_0202D1C8();
extern u32 sub_0202D200();
extern void sub_0202C4D8(u32 param0, u8 *param1, u32 param2);
extern void sub_0202D034(u32 param0, struct UnkStruct_0202E29C_sub *param1);
extern u32 sub_0202D358();
extern void sub_0202CB7C(void *param0, u32 param1);
extern void sub_0202D240(void *param0, u32 size, u32 param2, u32 param3);
extern void sub_0202DF54();
extern u16 sub_0202D19C();
extern u32 sub_0202CBE8();
extern u32 sub_0202D178();
extern u16 sub_0202CDA4();
extern void sub_0202CF84(u32 param0, u16 param1, u16 param2, u32 param3, u32 param4, u32 param5);
extern u32 sub_0202CB8C();
extern u16 WM_GetDispersionBeaconPeriod();
extern BOOL sub_0202D2D0();

void sub_0202E29C(PlayerProfile *player_data) {
    if (UNK_021C59F0 == NULL) {
        UNK_021C59F0 = AllocFromHeap(HEAP_ID_15, sizeof(struct UnkStruct_0202E29C));
        MI_CpuFill8(UNK_021C59F0, 0, sizeof(struct UnkStruct_0202E29C));

        UNK_021C59F0->unkCA4 = AllocFromHeap(HEAP_ID_15, sub_0202CEEC());
        MI_CpuFill8(UNK_021C59F0->unkCA4, 0, sub_0202CEEC());

        UNK_021C59F0->unkCBC = AllocFromHeap(HEAP_ID_15, sub_02023AC4());
        MI_CpuFill8(UNK_021C59F0->unkCBC, 0, sub_02023AC4());

        UNK_021C59F0->unkCC0 = 0x333;
        UNK_021C59F0->unkCB8 = player_data;

        MailMsg_Init(&UNK_021C59F0->unkCA8);
        sub_0202E500();
    }
}

BOOL sub_0202E344() {
    if (UNK_021C59F0 != NULL) {
        return TRUE;
    }

    return FALSE;
}

BOOL sub_0202E358(u8 *param0, u8 *param1, s32 param2) {
    int i = 0;
    while (i < param2) {
        if (*param0 != *param1) {
            return FALSE;
        }

        i++;
        param0++;
        param1++;
    }

    return TRUE;
}

void sub_0202E380(struct UnkStruct_0202E29C_sub *param0, u32 param1) {
#pragma unused(param1)
    s32 r5 = sub_02033534();
    u8 r6 = sub_0203354C();
    struct UnkStruct_0202E29C_sub4 *r4 = &param0->unk50;

    if (r5 != 0xe) {
        if (sub_0202D8B0(r4->unk04) == 0 || sub_0202D8B0(r5) == 0) {
            if (r4->unk30[0x24] != 0) {
                if (r4->unk04 == 0xa) {
                    return;
                }
            }

            if (r4->unk04 != r5) {
                return;
            }
        }
    }

    if (r5 != 0xe) {
        if (r4->unk05 != r6) {
            return;
        }
    }

    for (int i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] == 0) {
            continue;
        }

        if (!sub_0202E358(UNK_021C59F0->unk054[i].unk04, param0->unk04, 6)) {
            continue;
        }

        UNK_021C59F0->unkC84[i] = 0x96;

        MI_CpuCopy8(param0, &UNK_021C59F0->unk054[i], sizeof(struct UnkStruct_0202E29C_sub));
        return;
    }

    int i;
    for (i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] == 0) {
            break;
        }
    }

    if (i < 0x10) {
        UNK_021C59F0->unkC84[i] = 0x96;
        MI_CpuCopy8(param0, &UNK_021C59F0->unk054[i], sizeof(struct UnkStruct_0202E29C_sub));
        UNK_021C59F0->unkCB4 = 1;
    }
}

void sub_0202E470(u32 param0, u32 param1) {
#pragma unused(param0)
    if (param1 != 0) {
        OS_Terminate();
    }

    UNK_021C59EC = 2;
}

void sub_0202E488() {
    UNK_021C59EC = 0;
    sub_02016454(4);
}

void sub_0202E49C() {
    sub_02016444(4);
    UNK_021C59EC = 1;
    if (sub_02090DB8(8, sub_0202E470, 0) != 1) {
        OS_Terminate();
    }
}

BOOL sub_0202E4C8() {
    if (UNK_021C59EC == 2) {
        return TRUE;
    }

    return FALSE;
}

BOOL sub_0202E4DC() {
    if (UNK_021C59EC != 0) {
        return TRUE;
    }

    return FALSE;
}

void sub_0202E4F0() {
    sub_02090CC8(sub_0202E488, 0);
}

void sub_0202E500() {
    UNK_021C59F0->unkCB0 = 0;
    sub_0202CE64(UNK_021C59F0->unkCA4 + (32 - (u32)(UNK_021C59F0->unkCA4) % 32));

    sub_0202CB70(UNK_021C59F0->unkCC0);
}

void sub_0202E538() {
    for (int i = 0; i < 0x10; i++) {
        UNK_021C59F0->unkC84[i] = 0;
    }

    MI_CpuFill8(UNK_021C59F0->unk054, 0, 0xC00);
}

void sub_0202E56C(u32 param0) {
    UNK_021C59F0->unkDAD_3 = (u8)param0;
}

void sub_0202E594() {
    UNK_021C59F0->unkCB4 = 0;

    UNK_021C59F0->unkDAD_0 = 0;

    UNK_021C59F0->unkDAD_2 = 0;

    UNK_021C59F0->unkDAA = 0;

    UNK_021C59F0->unkDAD_4 = 0;

    UNK_021C59F0->unkDAC = 0;

    UNK_021C59F0->unkDAB = 0;
}

BOOL sub_0202E5F8(u32 param0, u32 param1, u32 param2) {
#pragma unused(param0)
    sub_0202E594();
    sub_0202E56C(param1);
    sub_0202D2F4();

    if (UNK_021C59F0->unkDAB == 0) {
        sub_0202D0A0(sub_020303BC, 0xe);
        UNK_021C59F0->unkDAB = 1;
    }

    UNK_021C59F0->unkDAD_5 = (u8)param2;
    if (sub_0202CBD4() == 1 && sub_0202CBFC() != 0) {
        return TRUE;
    }

    return FALSE;
}

u32 sub_0202E66C(u32 param0, u32 param1) {
#pragma unused(param0)
    sub_0202E594();
    if (param1 != 0) {
        sub_0202E538();
    }

    if (UNK_021C59F0->unkDAB == 0) {
        sub_0202D0A0(sub_02030238, 0xe);
        UNK_021C59F0->unkDAB = 1;
    }

    if (sub_0202CBD4() == 1) {
        struct UnkStruct_0202E29C_const st0 = UNK_020EEC40;

        if (sub_0202C570(sub_0202E380, st0.unk0, 0) != 0) {
            return 1;
        }
    }

    return 0;
}

u32 sub_0202E6F0() {
    if (UNK_021C59F0 == NULL) {
        return 1;
    }

    switch (UNK_021C59F0->unkDAC) {
    case 0:
        if (sub_0202D21C() != 0) {
            sub_0202C770();
            UNK_021C59F0->unkDAC = 1;
        } else if (sub_0202D1E4() == 0) {
            sub_0202D100();
            UNK_021C59F0->unkDAC = 2;
        }
        break;

    case 1:
        if (sub_0202D1E4() == 0) {
            sub_0202D100();
            UNK_021C59F0->unkDAC = 2;
        }
        break;
    case 2:
        if (sub_0202D1C8() != 0) {
            return 1;
        }

        if (sub_0202D200() != 0) {
            UNK_021C59F0->unkDAC = 1;
        }
        break;
    }

    return 0;
}

BOOL sub_0202E784() {
    if (UNK_021C59F0 != NULL && UNK_021C59F0->unkDAA == 0) {
        UNK_021C59F0->unkDAA = 1;
        sub_0202D100();
        return TRUE;
    }

    return FALSE;
}

void sub_0202E7B0(u32 param0) {
    if (UNK_021C59F0 != NULL) {
        if (param0 != 0) {
            UNK_021C59F0->unkDAA = 2;
            return;
        }

        UNK_021C59F0->unkDAA = 0;
        sub_0202E500();
    }
}

void sub_0202E7D8() {
    FreeToHeap(UNK_021C59F0->unkCBC);
    FreeToHeap(UNK_021C59F0->unkCA4);
    FreeToHeap(UNK_021C59F0);

    UNK_021C59F0 = NULL;
}

u32 sub_0202E810() {
    if (sub_02030F40() == 0) {
        return 0;
    }

    u32 count = 0;
    for (int i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] != 0) {
            count++;
        }
    }

    return count;
}

s32 sub_0202E844(u32 param0) {
    int i;
    u32 count = 0;
    for (i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] == 0) {
            continue;
        }

        if (count == param0) {
            return i;
        }

        count++;
    }

    GF_ASSERT(0);
    return 0;
}

u8 sub_0202E878() {
    return UNK_021C59F0->unkCB4;
}

void sub_0202E88C() {
    UNK_021C59F0->unkCB4 = 0;
}

s32 sub_0202E8A0(s32 param0) {
    if (UNK_021C59F0->unkC84[param0] != 0) {
        if (UNK_021C59F0->unk054[param0].unk50.unk06 == 0) {
            return 1;
        } else {
            return UNK_021C59F0->unk054[param0].unk50.unk06;
        }
    }

    return 0;
}

s32 sub_0202E8D0(s32 param0) {
    for (int i = 0xf; i >= 0; i--) {
        s32 ret = sub_0202E8A0(i);
        if (ret > param0 && 8 > ret) {
            return i;
        }
    }

    return -1;
}

s32 sub_0202E8F4() {
    if (sub_0202E810() == 0) {
        return -1;
    }

    for (int i = 0xf; i >= 0; i--) {
        if (UNK_021C59F0->unkC84[i] != 0 && sub_0202EFE4(UNK_021C59F0->unk054[i].unk04)) {
            s32 ret2 = sub_0202E8A0(i);
            if (ret2 > 1 && ret2 < 8) {
                return i;
            }
        }
    }

    return -1;
}

s32 sub_0202E950() {
    if (sub_0202E810() == 0) {
        return -1;
    }

    for (int i = 0xf; i >= 0; i--) {
        if (UNK_021C59F0->unkC84[i] != 0 && sub_0202EFE4(UNK_021C59F0->unk054[i].unk04)) {

            return i;
        }
    }

    s32 ret = sub_0202E8D0(1);
    if (ret == -1) {
        return sub_0202E8D0(0);
    }

    return ret;
}

void sub_0202E9AC(u32 param0, PlayerProfile *player_data) {
    int i;
    u32 count = 0;
    for (i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] == 0) {
            continue;
        }

        if (param0 == count) {

            PlayerProfile_Copy(sub_0202EF84(i), player_data);
            return;
        }

        count++;
    }
}

u32 sub_0202E9E8(u32 param0) {
    if (sub_0202CBD4() == 2) {
        sub_0202C770();
        return 0;
    }

    if (sub_0202CBD4() == 1) {
        s32 ret = sub_02033534();
        UNK_021C59F0->unkDA8 = (u8)UNK_021C59F0->unk054[param0].unk36;
        if (sub_0202D8B0(ret) != 0) {
            sub_0202C4D8(1, UNK_021C59F0->unk054[param0].unk04, 0);
        } else {
            sub_0202D034(1, &UNK_021C59F0->unk054[param0]);
        }

        return 1;
    }

    return 0;
}

void sub_0202EA54() {
    for (int i = 0; i < 0x10; i++) {
        if (UNK_021C59F0->unkC84[i] == 0) {
            continue;
        }
        if (UNK_021C59F0->unkC84[i] == 0) {
            continue;
        }

        UNK_021C59F0->unkC84[i]--;

        if (UNK_021C59F0->unkC84[i] == 0) {
            UNK_021C59F0->unkCB4 = 1;
        }
    }
}

void sub_0202EA9C() {
    s32 res = sub_02033534();
    PlayerProfile *player_data = sub_0202EF70();

    if (res != 0xf) {
        struct UnkStruct_0202E29C_sub2 *res = &UNK_021C59F0->unkCC4;
        GF_ASSERT((s32)sub_02023AC4() <= 0x20);
        GF_ASSERT(PlayerProfile_sizeof() == 0x20);

        MI_CpuCopy8(player_data, &res->unk08.unk08, PlayerProfile_sizeof());

        MI_CpuCopy8(UNK_021C59F0->unkCBC, res->unk08.unk28, sub_02023AC4());

        res->unk00 = PlayerProfile_GetTrainerID(player_data);
        res->unk04 = (u8)sub_02033534();
        res->unk05 = sub_0203354C();

        MI_CpuCopy8(&UNK_021C59F0->unkCA8, &res->unk08.unk00, sizeof(struct MailMessage));
        res->unk08.unk4C = (u8)sub_0202D358();
    } else {
        struct UnkStruct_0202E29C_sub2 *res = &UNK_021C59F0->unkCC4;
        res->unk00 = PlayerProfile_GetTrainerID(player_data);
        res->unk04 = (u8)sub_02033534();
        res->unk05 = sub_0203354C();

        MI_CpuCopy8(&UNK_021C59F0->unk000, &res->unk08, sizeof(struct UnkStruct_0202E29C_sub3));
    }

    DC_FlushRange(&UNK_021C59F0->unkCC4, sizeof(struct UnkStruct_0202E29C_sub2));
    sub_0202CB7C(&UNK_021C59F0->unkCC4, sizeof(struct UnkStruct_0202E29C_sub2));
}

void sub_0202EB7C() {
    struct UnkStruct_0202E29C_sub2 *r4 = &UNK_021C59F0->unkCC4;
    if (r4->unk06 != sub_0202EDB8()) {
        r4->unk06 = (u8)sub_0202EDB8();
        DC_FlushRange(&UNK_021C59F0->unkCC4, sizeof(struct UnkStruct_0202E29C_sub2));
        sub_0202CB7C(&UNK_021C59F0->unkCC4, sizeof(struct UnkStruct_0202E29C_sub2));

        sub_0202D240(&UNK_021C59F0->unkCC4,
            sizeof(struct UnkStruct_0202E29C_sub2),
            UNK_021C59F0->unkCC0,
            UNK_021C59E8);
    }
}

void sub_0202EBD0(u16 param0) {
    u32 r5 = sub_0202CBD4();
    sub_0202DF54();
    sub_0202EB7C();

    if (sub_0202D19C() == 0 && sub_0202EE24() == 0 && UNK_021C59F0->unkDAD_2) {
        UNK_021C59F0->unkDAD_0 = 1;
    }

    if (UNK_021C59F0->unkDA6 == 0xFFFF) {
        UNK_021C59F0->unkDA6 = param0;
    }

    if (UNK_021C59F0->unkDAD_1 && UNK_021C59F0->unkDA6 > param0) {
        UNK_021C59F0->unkDAD_0 = 1;
    }

    if (sub_0202CBE8() == 25) {
        sub_020335D0(0);
    }

    switch (r5) {
    case 0:
        if (UNK_021C59F0->unkDAA == 1) {
            sub_0202E7D8();
            return;
        } else if (UNK_021C59F0->unkDAA == 2) {
            UNK_021C59F0->unkDAA = 3;
        }
        break;

    case 1:
        if (UNK_021C59F0->unkDAA == 1 && sub_0202D178() != 0) {
            return;
        }

        if (UNK_021C59F0->unkDAA == 2 && sub_0202D178() != 0) {
            return;
        }

        break;

    case 8:
    case 9:

        if (UNK_021C59F0 != NULL) {
            UNK_021C59F0->unkDAD_0 = 1;
            return;
        }
        break;

    case 7:
        u16 r0 = sub_0202CDA4();
        if (UNK_021C59F0->unkDA9 == 0) {
            UNK_021C59F0->unkDA4 = r0;
            UNK_021C59F0->unkDA9 = 5;
        } else {
            UNK_021C59F0->unkDA9--;
        }

        u16 r5 = UNK_021C59F0->unkDA4;
        if (UNK_021C59F0->unkDAD_3) {
            UNK_021C59E8++;
        }

        sub_0202EA9C();

        sub_0202CF84(0,
            UNK_021C59E8,
            r5,
            sub_0202D858((u16)sub_02033534()),
            sub_0202EEE8((u16)sub_02033534()),
            UNK_021C59F0->unkDAD_5);

        UNK_021C59F0->unkDA8 = (u8)r5;

        break;
    }
}

void sub_0202ED70(u16 param0) {
    if (UNK_021C59F0 != NULL) {
        sub_0202EBD0(param0);
    }
}

u32 sub_0202ED84(u16 param0) {
    if (UNK_021C59F0 == NULL) {
        return 0;
    }

    if (sub_0202CBD4() != 4) {
        return 0;
    }

    if ((sub_0202CB8C() & (1 << param0)) == 0) {
        return 0;
    }

    return 1;
}

u32 sub_0202EDB8() {
    u32 count = 0;
    for (int i = 0; i < 8; i++) {
        if (sub_0202ED84((u16)i) != 0) {
            count++;
        }
    }

    return count;
}

BOOL sub_0202EDD8() {
    if (UNK_021C59F0 != NULL) {
        if (UNK_021C59F0->unkDAA == 3) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL sub_0202EDF8() {
    if (UNK_021C59F0 != NULL) {
        return TRUE;
    }

    return FALSE;
}

u32 sub_0202EE0C() {
    if (UNK_021C59F0 != NULL) {
        return sub_0202D1C8();
    }

    return 1;
}

u32 sub_0202EE24() {
    if (UNK_021C59F0 != NULL) {
        return sub_0202CB8C() & 0xFFFE;
    }

    return 0;
}

BOOL sub_0202EE44() {
    if (sub_0202EE60() && sub_0202CBE8() == 0x14) {
        return TRUE;
    }

    return FALSE;
}

BOOL sub_0202EE60() {
    if (UNK_021C59F0 != NULL && UNK_021C59F0->unkDAD_0) {
        return TRUE;
    }

    return FALSE;
}

void sub_0202EE84(u32 param0) {
    if (UNK_021C59F0 != NULL) {
        UNK_021C59F0->unkDAD_2 = (u8)param0;
    }
}

void sub_0202EEB0(u32 param0) {
    if (UNK_021C59F0 != NULL) {
        UNK_021C59F0->unkDAD_1 = (u8)param0;

        UNK_021C59F0->unkDA6 = 0xFFFF;
    }
}

u16 sub_0202EEE8(u16 param0) {
    u16 r4 = WM_GetDispersionBeaconPeriod();
    GF_ASSERT(param0 < 0x1a);

    if (param0 == 0xa) {
        return (u16)(r4 >> 2);
    }

    if (param0 == 9 || param0 == 0xd) {
        return (u16)(r4 >> 2);
    }

    return r4;
}

struct UnkStruct_0202E29C_sub *sub_0202EF18(u32 param0) {
    if (UNK_021C59F0 != NULL) {
        if (UNK_021C59F0->unkC84[param0] != 0) {
            return &UNK_021C59F0->unk054[param0];
        }
    }

    return NULL;
}

struct UnkStruct_0202E29C_sub4 *sub_0202EF44(s32 param0) {
    if (UNK_021C59F0 != NULL) {
        if (UNK_021C59F0->unkC84[param0] != 0) {
            return &UNK_021C59F0->unk054[param0].unk50;
        }
    }

    return NULL;
}

PlayerProfile *sub_0202EF70() {
    return UNK_021C59F0->unkCB8;
}

PlayerProfile *sub_0202EF84(int param0) {
    if (UNK_021C59F0->unkC84[param0] == 0) {
        return NULL;
    }

    struct UnkStruct_0202E29C_sub4 *r0 = &UNK_021C59F0->unk054[param0].unk50;

    return &r0->unk10;
}

void sub_0202EFAC(u8 *param0, s32 param1) {
    if (UNK_021C59F0 != NULL) {
        GF_ASSERT(param1 < 8);

        MI_CpuCopy8(param0, UNK_021C59F0->unkC54[param1], 6);
    }
}

BOOL sub_0202EFE4(u8 *param0) {
    for (int i = 0; i < 8; i++) {
        if (WM_IsBssidEqual(UNK_021C59F0->unkC54[i], param0)) {
            return TRUE;
        }
    }

    return FALSE;
}

u32 sub_0202F03C() {
    if (UNK_021C59F0 != NULL) {
        return UNK_021C59F0->unkDAD_4;
    }

    return 0;
}

void sub_0202F05C() {
    if (UNK_021C59F0 != NULL) {
        UNK_021C59F0->unkDAD_4 = 1;
    }
}

void sub_0202F078(struct MailMessage *mail_message) {
    MI_CpuCopy8(mail_message, &UNK_021C59F0->unkCA8, sizeof(struct MailMessage));
}

void sub_0202F094(void *param0) {
    MI_CpuCopy8(param0, UNK_021C59F0->unkCBC, sub_02023AC4());
}

void sub_0202F0B8() {
    sub_0202EA9C();
    sub_0202D240(&UNK_021C59F0->unkCC4,
        sizeof(struct UnkStruct_0202E29C_sub2),
        UNK_021C59F0->unkCC0,
        UNK_021C59E8);
}

u32 sub_0202F0DC(u8 param0) {
    int i;
    u32 r5 = 0;
    for (i = 0; i < 0x10; i++) {
        struct UnkStruct_0202E29C_sub4 *res = sub_0202EF44(i);
        if (res != 0 && res->unk04 == param0) {
            r5 += res->unk06;
        }
    }

    return r5;
}

BOOL sub_0202F104() {
    return sub_0202D2D0();
}

void sub_0202F10C(struct UnkStruct_0202E29C_sub3 *param0) {
    MI_CpuCopy8(param0, &UNK_021C59F0->unk000, sizeof(struct UnkStruct_0202E29C_sub3));
    sub_0202F0B8();
}

u8 *sub_0202F124(u32 param0) {
    if (UNK_021C59F0 != NULL && UNK_021C59F0->unkC84[param0] != 0) {
        struct UnkStruct_0202E29C_sub4 *r0 = &UNK_021C59F0->unk054[param0].unk50;
        return r0->unk08;
    }

    return NULL;
}
