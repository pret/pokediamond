#include "unk_02031734.h"

#include "global.h"

#include "MI_memory.h"
#include "communication_error.h"
#include "game_init.h"
#include "heap.h"
#include "player_data.h"
#include "unk_0202E29C.h"
#include "unk_0202F150.h"

const struct UnkStruct_02031734_const2 UNK_020EEC48 = {
    { (u32)sub_02032B84, 0 }
};

const struct UnkStruct_02031734_const1 UNK_020EEC50 = {
    { (u32)sub_0203213C, (u32)sub_02032138, 0 }
};

const struct UnkStruct_02031734_const1 UNK_020EEC5C = {
    { (u32)sub_02032234, (u32)sub_0203234C, 0 }
};

char UNK_02105D64[] = " FULL";
char UNK_02105D5C[] = "FREAK";
char UNK_02105D6C[] = " GAME";

struct UnkStruct_02031734 *UNK_021C5A00;

extern void sub_0202D8D0(u32 param0, u32 param1, u32 param2);
extern void sub_02033E74();
extern void sub_0202D918();
extern void sub_02033ED0();
extern void sub_0202D298();
extern void sub_0202D344(u32 param0);
extern void sub_0202D1B0(u8 param0);
extern void sub_0202D36C(u32 param0);
extern u32 ov04_021DDB08();
extern void sub_02033EEC(u32 param0);
extern u32 WM_GetLinkLevel();
extern void sub_0202DB14(struct SaveData *save, u32 param1);
extern s64 _ll_mul(s64, s64);
extern void sub_0202DBE0();
extern void sub_0202DDE8();
extern void sub_0202D308(void (*param0)(u32, u32));
extern void ov04_021D83C0();
extern s32 ov04_021D7F8C();
extern s32 ov04_021D7800(u32 param0);
extern u32 ov04_021D8494(s32 param0);
extern void ov04_021D77C4(void (*param0)(u32, u8 *, u32), void (*param1)(u32, u8 *, u32));
extern u32 ov04_021D82BC(u8 param0);
extern void ov04_021D836C();
extern u32 ov04_021DD718(u32 *param0, u32 *param1);
extern void ov04_021DD6F0();
extern s32 ov04_021D76AC();
extern ov05_021D74E0(struct SaveData *save, u32 param1);
extern void ov04_021D83A8(void (*param0)(s32));
extern void sub_0200541C();

void sub_02031734(struct SaveData *save, u8 param1) {
    if (UNK_021C5A00 == NULL) {
        sub_0202E49C();
        struct UnkStruct_02031734 *ptr = AllocFromHeap(HEAP_ID_15, sizeof(struct UnkStruct_02031734));
        UNK_021C5A00                   = ptr;
        MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct_02031734));

        UNK_021C5A00->unk3A = 0x32;
        UNK_021C5A00->unk43 = 1;
        UNK_021C5A00->unk28 = save;

        UNK_021C5A00->unk2C = Save_PlayerData_GetProfileAddr(save);

        UNK_021C5A00->unk3C = 2;
        UNK_021C5A00->unk3D = 0;
        UNK_021C5A00->unk48 = 0;
        UNK_021C5A00->unk3F = param1;

        sub_020312BC(UNK_021C5A00->unk0C);
        sub_0202D8D0(0, 0, 0);

        if (param1 != 9 && param1 != 0x11 && param1 != 0xf) {
            sub_02033E74();
        }
    }
}

void sub_020317C0() {
    if (UNK_021C5A00 != NULL) {
        sub_0202D918();
        if (UNK_021C5A00->unk00 != NULL) {
            FreeToHeap(UNK_021C5A00->unk00);
        }

        if (UNK_021C5A00->unk3F >= 0x13) {
            DestroyHeap(HEAP_ID_49);
        }

        sub_02033ED0();
        sub_0202E4F0();

        FreeToHeap(UNK_021C5A00);
        DestroyHeap(HEAP_ID_15);

        UNK_021C5A00 = NULL;
    }
}

BOOL sub_02031810() {
    if (UNK_021C5A00 != NULL) {
        return TRUE;
    }
    return FALSE;
}

void sub_02031824(struct SaveData *save) {
    if (UNK_021C5A00 == NULL) {
        CreateHeapAtEnd(3, 0xf, 0xe000);
        sub_02031734(save, 0xa);

        UNK_021C5A00->unk40 = 0;
        sub_02031D20(sub_02031D30, 0x32);
    }
}

void sub_02031860() {
    if (UNK_021C5A00 != NULL) {
        sub_02031468();
        sub_02031D20(sub_020323CC, 0);
    }
}

void sub_02031880() {
    sub_0202FC60();
    UNK_021C5A00->unk38 = sub_02031190();

    sub_02031D20(sub_020321B8, 0);
}

void sub_020318A4(u8 param0) {
    UNK_021C5A00->unk4F = param0;
}

void sub_020318B4() {
    sub_02031D20(sub_02032028, 0);
}

BOOL sub_020318C4() {
    struct UnkStruct_02031734_const1 st0 = UNK_020EEC50;

    u32 r1 = (u32)UNK_021C5A00->unk24;

    if (UNK_021C5A00 == NULL) {
        return FALSE;
    }

    for (u32 i = 0; st0.unk00[i] != 0; i++) {

        if (r1 == st0.unk00[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

void sub_02031914() {
    sub_02031D20(sub_02032178, 0);
}

void sub_02031924() {
    UNK_021C5A00->unk4C = 1;
}

void sub_02031934() {
    sub_0202E49C();
    sub_02031D20(sub_02032194, 0);
}

void sub_02031948(struct SaveData *save, u8 param1, u8 param2, u32 param3) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7080);
        sub_02031734(save, param1);
        UNK_021C5A00->unk40 = param2;
        UNK_021C5A00->unk30 = param3;
        sub_02031D20(sub_020321D0, 0);
    }
}

void sub_02031990(struct SaveData *save, u8 param1, u8 param2, u32 param3) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7080);
        sub_02031734(save, param1);
        UNK_021C5A00->unk40 = param2;
        UNK_021C5A00->unk30 = param3;
        sub_02031D20(sub_0203224C, 0);
    }
}

void sub_020319D8(u8 param0) {
    UNK_021C5A00->unk3E = param0;
    sub_02031D20(sub_02032298, 0);
}

void sub_020319F4() {
    sub_0202FCA8();
    sub_02031D20(sub_02032364, 0);
}

void sub_02031A08() {
    if (UNK_021C5A00 != NULL) {
        sub_02031D20(sub_02032440, 5);
    }
}

void sub_02031A24() {
    sub_0202D298();
}

BOOL sub_02031A2C() {
    struct UnkStruct_02031734_const1 st0 = UNK_020EEC5C;

    u32 r1 = (u32)UNK_021C5A00->unk24;

    if (UNK_021C5A00 == NULL) {
        return FALSE;
    }

    for (u32 i = 0; st0.unk00[i] != 0; i++) {

        if (r1 == st0.unk00[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

void sub_02031A7C(struct SaveData *save) {
    if (UNK_021C5A00 == NULL) {
        if (CreateHeapAtEnd(3, 0xf, 0x7080) == 0) {
            sub_020335E0();
        }

        sub_02031734(save, 9);
        UNK_021C5A00->unk3F = 9;
        UNK_021C5A00->unk40 = 0;
        sub_02031D20(sub_02032478, 0);
    }
}

void sub_02031AC8(u8 param0) {
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk38 = 3;
    sub_0202D344(1);
    sub_02033E74();
    sub_02031D20(sub_02032628, 0);
}

s32 sub_02031AF4() {
    if (UNK_021C5A00 == NULL) {
        return -1;
    }
    if (UNK_021C5A00->unk24 == sub_0203279C) {
        return 1;
    }

    if (UNK_021C5A00->unk24 == sub_020327B4) {
        return -1;
    }

    return 0;
}

BOOL sub_02031B2C() {
    if (UNK_021C5A00 == NULL) {
        return FALSE;
    }
    if (UNK_021C5A00->unk24 == sub_020327FC) {
        return TRUE;
    }

    return FALSE;
}

void sub_02031B50() {
    sub_0202D344(0);
    if (UNK_021C5A00->unk44 != 1 || UNK_021C5A00->unk45 != 1 || UNK_021C5A00->unk3F == 9) {
        sub_020334E8(0, 0);
    }

    sub_02033ED0();
    UNK_021C5A00->unk3F = 9;
    UNK_021C5A00->unk48 = 0;
    sub_0202D1B0(UNK_021C5A00->unk3C);

    if (sub_02031190() == 0) {
        sub_0202D36C(1);
        sub_02031D20(sub_020323DC, 0xf);
        return;
    }

    sub_02031D20(sub_02032424, 5);
}

u32 sub_02031BD0() {
    if (UNK_021C5A00 == NULL) {
        return 1;
    }

    if (UNK_021C5A00->unk24 != sub_020324F8) {
        return 1;
    }

    return 0;
}

void sub_02031BF4() {
    if (UNK_021C5A00 != NULL) {
        sub_02031D20(sub_02032440, 5);
    }
}

void sub_02031C10() {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk48 = 1;
        sub_0202D344(1);
    }
}

void sub_02031C2C() {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk48 = 1;
        sub_0202D344(1);
        sub_02031D20(sub_02032850, 0);
    }
}

void sub_02031C54() {
    UNK_021C5A00->unk3F = 0x12;
}

void sub_02031C64() {
    UNK_021C5A00->unk3F = 0x9;
}

void sub_02031C74(struct SaveData *save, u8 param1) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7080);
        sub_02031734(save, param1);
        sub_02031D20(sub_02032E00, 0);
    }
}

void sub_02031CA8(struct SaveData *save, u8 param1) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7080);
        sub_02031734(save, param1);
        sub_02031D20(sub_02032E48, 0);
    }
}

void sub_02031CDC() {
    if (UNK_021C5A00 != NULL && UNK_021C5A00->unk24 != 0) {
        ((void (*)(void))(UNK_021C5A00->unk24))();
    }
    if (sub_02033590() != 0) {
        sub_02033EEC(3 - ov04_021DDB08());
        return;
    }

    if (sub_0202EDF8()) {
        sub_02033EEC(3 - WM_GetLinkLevel());
    }
}

void sub_02031D20(void (*param0)(), u32 param1) {
    UNK_021C5A00->unk24 = param0;
    UNK_021C5A00->unk3A = (u16)param1;
}

void sub_02031D30() {
    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (!sub_0202E4C8()) {
        return;
    }

    sub_0202E29C(UNK_021C5A00->unk2C);
    sub_0202DB14(UNK_021C5A00->unk28, 0);
    sub_02031268(1);
    sub_02030FA8();

    if (UNK_021C5A00->unk4A != 0) {
        if (sub_0202F918(1, UNK_021C5A00->unk43, 0x1F4, 1) == 0) {
            return;
        }

        u32 r1 = compute(UNK_021C5A00->unk0C, 0x14);

        UNK_021C5A00->unk43 = 0;
        sub_02031D20(sub_020320C4, r1 + 0x14);
        return;
    }

    if (sub_0202F950(1, 1, 0x1F4) != 0) {
        if (UNK_021C5A00->unk4C != 0) {
            sub_02031D20(sub_020323B8, 0);
        } else {
            sub_02031D20(sub_02031EE0, 0x40);
        }
    }
}

void sub_02031E08() {
    if (sub_0202EE0C() != 0) {
        sub_02031268(1);
        sub_02030FA8();

        if (UNK_021C5A00->unk4A != 0) {
            sub_02031D20(sub_02032058, 0);
            return;
        }

        if (sub_0202F950(0, 1, 0x1F4) != 0) {

            u32 r1 = compute(UNK_021C5A00->unk0C, 0x40);

            if (UNK_021C5A00->unk38 != 0) {
                r1                  = (u32)(UNK_021C5A00->unk38 << 6);
                UNK_021C5A00->unk38 = 0;
            }
            sub_02031D20(sub_02031EE0, r1);
        }
    }
}

void sub_02031E8C() {
    if (sub_0202EE0C() != 0) {
        if (sub_0202F950(0, 0, 0x1F4) != 0) {

            u32 r1 = compute(UNK_021C5A00->unk0C, 0x20);

            sub_02031D20(sub_02031EE0, r1 + 0x10);
        }
    }
}

void sub_02031EE0() {
    sub_0202EA54();
    if (UNK_021C5A00->unk4F == 0 && UNK_021C5A00->unk4B == 0) {
        s32 r0 = sub_0202E8F4();
        if (r0 != -1) {
            UNK_021C5A00->unk3E = (u8)r0;
            sub_02031D20(sub_02031F60, 0x20);
            return;
        }

        if (UNK_021C5A00->unk3A != 0) {
            UNK_021C5A00->unk3A--;
            return;
        }

        r0 = sub_0202E950();
        if (r0 != -1) {
            UNK_021C5A00->unk3E = (u8)r0;
            sub_02031D20(sub_02031F60, 0x20);
            return;
        }

        sub_02031D20(sub_02032028, 0);
    }
}

void sub_02031F60() {
    sub_0202EA54();
    if (sub_0202E8A0(UNK_021C5A00->unk3E) != 0 && sub_0202FB18(UNK_021C5A00->unk3E) != 0) {
        sub_02031D20(sub_02031FC8, 0x64);
        return;
    }

    if (sub_020311F0() != 0) {
        sub_02031D20(sub_02032028, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_02031D20(sub_02032028, 0);
}

void sub_02031FC8() {
    if (sub_02030E7C(sub_02031190()) != 0) {
        sub_0202FC60();
        sub_02031268(0);
        sub_02030FA8();
        sub_02031D20(sub_0203213C, 0);
        return;
    }

    if (sub_020311F0() != 0) {
        sub_02031D20(sub_02032028, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_02031D20(sub_02032028, 0);
}

void sub_02032028() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02032058, 0);
    }
}

void sub_02032040() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02031E8C, 0);
    }
}

void sub_02032058() {
    if (sub_0202EE0C() != 0) {
        sub_02031268(1);
        if (sub_0202F918(0, UNK_021C5A00->unk43, 0x1F4, 1) != 0) {
            u32 r1 = compute(UNK_021C5A00->unk0C, 0x14);

            UNK_021C5A00->unk43 = 0;
            sub_02031D20(sub_020320C4, r1 + 0x14);
        }
    }
}

void sub_020320C4() {
    if (sub_020311E8() != 0) {
        UNK_021C5A00->unk43 = 1;
        sub_02031D20(sub_02032118, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (UNK_021C5A00->unk4A == 0 && sub_0202E6F0() != 0) {
        sub_02031D20(sub_02032040, 2);
    }
}

void sub_02032118() {
    sub_02031268(0);
    sub_0202EE84(1);
    sub_02030FA8();
    sub_02031D20(sub_02032138, 0);
}

void sub_02032138() {
}
void sub_0203213C() {
}

void sub_02032140() {
    if (UNK_021C5A00->unk3F < 0x13) {
        if (sub_0202EE0C() == 0) {
            return;
        }

        sub_02031268(1);
        sub_02030FA8();
        sub_0202E7B0(1);
    }

    sub_02031D20(sub_020323B8, 0);
}

void sub_02032178() {
    if (sub_0202E6F0() != 0) {
        sub_0202FC60();
        sub_02031D20(sub_02032140, 0);
    }
}

void sub_02032194() {
    if (sub_0202E4C8()) {
        sub_0202E7B0(0);
        sub_0202FC60();
        sub_02031D20(sub_02031E08, 0);
    }
}

void sub_020321B8() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02031E08, 0);
    }
}

void sub_020321D0() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, UNK_021C5A00->unk30);
        if (sub_0202F918(1, 1, 0x200, 1) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032218, 0);
        }
    }
}

void sub_02032218() {
    if (sub_02030E7C(sub_02031190()) != 0) {
        sub_02031D20(sub_02032234, 0);
    }
}

void sub_02032234() {
    if (sub_02030F40() == 0) {
        sub_02031D20(sub_020323BC, 0);
    }
}

void sub_0203224C() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, UNK_021C5A00->unk30);
        if (sub_0202F950(1, 1, 0x200) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032290, 0);
        }
    }
}

void sub_02032290() {
    sub_0202EA54();
}

void sub_02032298() {
    sub_0202EA54();
    if (sub_0202FB18(UNK_021C5A00->unk3E) != 0) {
        sub_02031D20(sub_020322C0, 0xa);
    }
}

void sub_020322C0() {
    if (sub_020311F0() != 0) {
        sub_02031D20(sub_020322F8, 0);
    }

    if (sub_02030E7C(sub_02031190()) != 0 && sub_02031190() != 0) {
        sub_02031D20(sub_0203234C, 0);
    }
}

void sub_020322F8() {
    sub_0202E6F0();
    sub_02031D20(sub_0203230C, 2);
}

void sub_0203230C() {
    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (sub_0202EE0C() != 0 && sub_0202F950(0, 1, 0x200) != 0) {
        sub_0202FA10();
        sub_02031D20(sub_02032298, 0xa);
    }
}

void sub_0203234C() {
    if (sub_02030F40() == 0) {
        sub_02031D20(sub_020323BC, 0);
    }
}

void sub_02032364() {
    sub_0202E6F0();
    sub_02031D20(sub_02032378, 2);
}

void sub_02032378() {
    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (sub_0202EE0C() != 0 && sub_0202F950(0, 1, 0x200) != 0) {
        sub_0202FA10();
        sub_02031D20(sub_02032290, 0xa);
    }
}

void sub_020323B8() {
}

void sub_020323BC() {
    if (sub_02030F40() == 0) {
        sub_020317C0();
    }
}

void sub_020323CC() {
    sub_02031D20(sub_02032440, 5);
}

void sub_020323DC() {
    if (sub_02030F20() <= 1) {
        sub_0202D36C(0);
        sub_0202FC80();
        sub_02031D20(sub_020324F8, 0);
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_0202D36C(0);
    sub_0202FC80();
    sub_02031D20(sub_020324F8, 0);
}

void sub_02032424() {
    if (sub_0202E6F0() != 0) {
        sub_0202FC60();
        sub_02031D20(sub_020324F8, 0);
    }
}

void sub_02032440() {
    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
    }

    if (sub_0202E6F0() != 0 && UNK_021C5A00->unk3A == 0) {
        sub_0202FA5C();
        sub_02031D20(sub_020323BC, 0);
    }
}

void sub_02032478() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202D1B0(UNK_021C5A00->unk3C);
        sub_0202DB14(UNK_021C5A00->unk28, 0);
        if (sub_0202F950(1, 1, 0x200) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_020324C8, 0x40);
        }
    }
}

void sub_020324C8() {
    sub_0202EA54();
    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02032510, 0);
    }
}

void sub_020324F8() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02032510, 0);
    }
}

void sub_02032510() {
    if (sub_0202EE0C() != 0 && sub_0202F918(0, UNK_021C5A00->unk43, 0x200, 1) != 0) {
        // the compiler optimizes away the result of this function because it's not used, so any
        // second parameter value matches
        compute(UNK_021C5A00->unk0C, 0);

        sub_0202FA10();
        UNK_021C5A00->unk43 = 0;

        sub_02031D20(sub_02032578, 0x2710);
    }
}

void sub_02032578() {
    if (!sub_0202F104()) {
        if (sub_020311E8() != 0) {
            UNK_021C5A00->unk43 = 1;
            sub_02033E74();
            sub_02031D20(sub_020327FC, 0);
            return;
        }

        if (UNK_021C5A00->unk3A != 0) {
            UNK_021C5A00->unk3A--;
            return;
        }
    }

    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_020325D0, 0);
    }
}

void sub_020325D0() {
    if (sub_0202EE0C() != 0 && sub_0202F950(0, 0, 0x200) != 0) {
        sub_0202FA10();

        u32 r1 = compute(UNK_021C5A00->unk0C, 0x20);

        sub_02031D20(sub_020324C8, r1);
    }
}

void sub_02032628() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_02032640, 0);
    }
}

void sub_02032640() {
    if (sub_0202EE0C() != 0 && sub_0202F950(0, 0, 0x200)) {
        sub_0202FA10();
        sub_02031D20(sub_0203266C, 0x64);
    }
}

void sub_0203266C() {
    if (sub_0202E8A0(UNK_021C5A00->unk3E) != 0 && sub_0202FB18(UNK_021C5A00->unk3E) != 0) {
        sub_02031D20(sub_020326D0, 0x64);
        return;
    }

    if (sub_020311F0() != 0) {
        sub_02031D20(sub_020327B8, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_02031D20(sub_020327B8, 0);
}

void sub_020326D0() {
    if (sub_020311F0() != 0) {
        sub_02031D20(sub_020327B8, 0);
        return;
    }

    if (sub_02030E7C(sub_02031190()) != 0) {
        UNK_021C5A00->unk3D = 0;
        sub_020311D0(6, UNK_02105D5C);
        sub_02031D20(sub_02032738, 0x78);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_02031D20(sub_020327B8, 0);
}

void sub_02032738() {
    if (sub_020311F0() != 0) {
        sub_02031D20(sub_020327B8, 0);
        return;
    }

    if (UNK_021C5A00->unk3D == 2) {
        sub_02031D20(sub_020327B4, 0);
        return;
    } else if (UNK_021C5A00->unk3D == 1) {
        sub_0202DBE0();
        sub_02031D20(sub_0203279C, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    sub_02031D20(sub_020327B8, 0);
}

void sub_0203279C() {
    if (sub_020311F0() != 0) {
        sub_02031D20(sub_020327B8, 0);
    }
}

void sub_020327B4() {
}

void sub_020327B8() {
    UNK_021C5A00->unk3D = 0;
    if (sub_0202E6F0() != 0) {
        if (UNK_021C5A00->unk38 != 0) {
            UNK_021C5A00->unk38--;
            sub_02031D20(sub_02032640, 0);
            return;
        }

        sub_02031D20(sub_020327B4, 0);
    }
}

void sub_020327FC() {
    if (sub_020311E8() == 0) {
        if (sub_02033510() == 0 && sub_0202E6F0() != 0) {
            sub_02031D20(sub_020325D0, 0);
        }
    } else if (sub_02031190() == 0) {
        sub_0202DDE8();
    }

    if (sub_020311F0() != 0 && sub_02033510() == 0) {
        sub_02031D20(sub_020327B8, 0);
    }
}

void sub_02032850() {
    if (sub_0202EE0C() != 0) {
        if (sub_0202F918(0, UNK_021C5A00->unk43, 0x200, 0) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_020323B8, 0);
        }
    }
}

void sub_02032888() {
    u8 st0[4];
    UNK_021C5A00->unk3F = 0xd;
    if (sub_02031190() == 0) {
        st0[1] = 0;
        sub_020311D0(0xa, &st0[1]);
        return;
    }

    st0[0] = 0;
    sub_020311D0(0xa, st0);
}

void sub_020328C0(u8 param0) {
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk38 = 3;
    sub_02031D20(sub_02032924, 0);
}

void sub_020328E4() {
    UNK_021C5A00->unk3F = 7;
}

void sub_020328F4(u8 param0) {
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk3F = 7;
    UNK_021C5A00->unk38 = 3;
    sub_02033E74();
    sub_02031D20(sub_02032628, 0);
}

void sub_02032924() {
    if (sub_0202E6F0() != 0) {
        sub_02031D20(sub_0203293C, 0);
    }
}

void sub_0203293C() {
    if (sub_0202EE0C() != 0) {
        UNK_021C5A00->unk3F = 0xd;
        if (sub_0202F950(0, 0, 0x200) != 0) {
            sub_0202FA1C();
            sub_02031D20(sub_02032978, 0x64);
        }
    }
}

void sub_02032978() {
    if (sub_0202E8A0(UNK_021C5A00->unk3E) != 0 && sub_0202FB18(UNK_021C5A00->unk3E) != 0) {
        sub_02031D20(sub_020329F4, 0x64);
        return;
    }

    if (sub_020311F0() != 0 || UNK_021C5A00->unk3A == 0) {
        UNK_021C5A00->unk38--;
        if (UNK_021C5A00->unk38 == 0) {
            sub_02031D20(sub_020327B4, 0);
            return;
        }

        sub_02031D20(sub_02032924, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }
}

void sub_020329F4() {
    if (UNK_021C5A00->unk3A > 0x5a) {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (sub_020311F0() != 0) {
        UNK_021C5A00->unk38--;
        if (UNK_021C5A00->unk38 == 0) {
            sub_02031D20(sub_020327B4, 0);
            return;
        }

        sub_02031D20(sub_02032924, 0);
        return;
    }

    if (sub_02030E7C(sub_02031190()) != 0) {
        sub_02031D20(sub_0203279C, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0) {
        UNK_021C5A00->unk3A--;
        return;
    }

    UNK_021C5A00->unk38--;
    if (UNK_021C5A00->unk38 == 0) {
        sub_02031D20(sub_020327B4, 0);
        return;
    }

    sub_02031D20(sub_02032924, 0);
}

void sub_02032A8C(u8 param0, u32 param1, u8 *param2) {
#pragma unused(param1)
    if (sub_02031190() == 0) {

        u32 i;
        BOOL r3 = TRUE;
        for (i = 0; i < 6; i++) {
            if (UNK_02105D5C[i] != param2[i]) {
                r3 = FALSE;
                break;
            }
        }

        if (r3 && UNK_021C5A00->unk48 == 0) {
            UNK_02105D6C[0] = param0;
            sub_02030C4C(7, UNK_02105D6C);
            return;
        }

        UNK_02105D64[0] = param0;
        sub_02030C4C(7, UNK_02105D64);
    }
}

void sub_02032AEC(u32 param0, u32 param1, u8 *param2) {
#pragma unused(param0)
#pragma unused(param1)
    u32 i;
    BOOL r4 = TRUE;
    for (i = 1; i < 6; i++) {
        if (param2[i] != UNK_02105D6C[i]) {
            r4 = FALSE;
            break;
        }
    }

    if (r4) {
        u8 first = param2[0];
        if (first != sub_02031190()) {
            return;
        }

        UNK_021C5A00->unk3D = 1;
        return;
    }

    r4 = TRUE;
    for (i = 1; i < 6; i++) {
        if (param2[i] != UNK_02105D64[i]) {
            r4 = FALSE;
            break;
        }
    }

    if (r4) {
        u8 first = param2[0];
        if (first != (u8)sub_02031190()) {
            return;
        }

        UNK_021C5A00->unk3D = 2;
    }
}

u32 sub_02032B68() {
    return 6;
}

void sub_02032B6C(u8 param0) {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk3C = param0;
        sub_0202D1B0(param0);
    }
}

void sub_02032B84() {
    sub_0202EA54();
}

void sub_02032B8C() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, 0);
        if (sub_0202F950(1, 1, 0x20) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032B84, 0);
        }
    }
}

void sub_02032BD0(struct SaveData *save) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7000);
        sub_02031734(save, 0xe);
        UNK_021C5A00->unk40 = 0;
        sub_02031D20(sub_02032B8C, 0);
    }
}

void sub_02032C0C() {
    if (UNK_021C5A00 != NULL) {
        sub_02031D20(sub_02032440, 5);
    }
}

u32 sub_02032C28() {
    struct UnkStruct_02031734_const2 st0 = UNK_020EEC48;

    u32 fun = (u32)UNK_021C5A00->unk24;
    if (UNK_021C5A00 == NULL) {
        return 0;
    }

    u32 i = 0;
    while (st0.unk00[i] != 0) {
        if (st0.unk00[i] == fun) {
            return 1;
        }

        i++;
    }

    return 0;
}

void sub_02032C6C(u32 param0, u32 param1) {
    switch (param0) {
    case 0x333:
        if (param1 != 0xf) {
            return;
        }
        UNK_021C5A00->unk49 |= 1;
        break;
    case 0x400318:

        UNK_021C5A00->unk49 |= 1;
        break;

    case 0x400131:

        UNK_021C5A00->unk49 |= 2;
        break;

    case 0x400286:

        UNK_021C5A00->unk49 |= 4;
        break;
    }
}

void sub_02032CF4() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, 0);
        sub_0202D308(sub_02032C6C);
        if (sub_0202F950(1, 1, 0x20) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032B84, 0);
        }
    }
}

void sub_02032D44(struct SaveData *save) {
    if (sub_02030F40() == 0) {
        CreateHeapAtEnd(3, 0xf, 0x7000);
        sub_02031734(save, 0x11);
        UNK_021C5A00->unk40 = 0;
        sub_02031D20(sub_02032CF4, 0);
    }
}

void sub_02032D80() {
    if (UNK_021C5A00 != NULL) {
        sub_02031D20(sub_02032440, 5);
    }
}

u8 sub_02032D9C() {
    return UNK_021C5A00->unk49;
}

BOOL sub_02032DAC() {
    sub_02031468();

    if (UNK_021C5A00 == NULL) {
        return TRUE;
    }

    if ((u8)(UNK_021C5A00->unk3F + 0xe8) <= 1) {
        ov04_021D83C0();
        return TRUE;
    };

    if (sub_02033590() != 0) {
        sub_02031D20(sub_0203318C, 0);
    } else {
        sub_02031D20(sub_02032178, 0);
    }

    return FALSE;
}

void sub_02032E00() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, 0);
        if (sub_0202F918(1, 1, 0x200, 1) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032218, 0);
        }
    }
}

void sub_02032E48() {
    if (sub_0202E4C8()) {
        sub_0202E29C(UNK_021C5A00->unk2C);
        sub_0202DB14(UNK_021C5A00->unk28, 0);
        if (sub_0202F950(1, 1, 0x200) != 0) {
            sub_0202FA10();
            sub_02031D20(sub_02032290, 0);
        }
    }
}

void sub_02032E8C() {
}

void sub_02032E90() {
    if (ov04_021D7F8C() < 0) {
        sub_02031D20(sub_02032E8C, 0);
    }
}

void sub_02032EA8() {
}

void sub_02032EAC() {
}

void sub_02032EB0() {
    sub_020313A0(1);

    s32 res = ov04_021D7F8C();
    if (res >= 0xa) {
        sub_02031D20(sub_02032EAC, 0);
        return;
    }

    if (res < 0) {
        sub_02031D20(sub_02032E8C, 0);
        return;
    }

    if (res == 1) {
        sub_02031D20(sub_02032E90, 0);
        return;
    }

    if (res == 2) {
        if (UNK_021C5A00->unk44 != 0) {
            sub_02031D20(sub_02032E8C, 0);
            return;
        }
        sub_02031D20(sub_02032EA8, 0);
        return;
    }
}

void sub_02032F20(u32 param0) {
    if (param0 + 2 > 1) {
        param0 = -param0;
    }

    UNK_021C5A00->unk34 = param0;
}

void sub_02032F34() {
    s32 res = ov04_021D7800(0);
    if (res >= 0xa) {
        sub_02031D20(sub_02032EAC, 0);
        return;
    }

    if (res < 0) {
        sub_02032F20((u32)res);
        sub_02031D20(sub_02032E8C, 0);
        return;
    }

    if (res == 1) {
        sub_02031D20(sub_02032EB0, 0);
        return;
    }

    if (res == 2) {
        sub_02031D20(sub_02032EA8, 0);
        return;
    }

    if (res == 3) {
        sub_02031D20(sub_02032EAC, 0);
        return;
    }
}

void sub_02032F98() {
    s32 res = ov04_021D7800(1);
    if (res < 0) {
        sub_02032F20((u32)res);
        sub_02031D20(sub_02032E8C, 0);
        return;
    }

    if (ov04_021D8494(UNK_021C5A00->unk42) != 0) {
        sub_0202FC60();
        sub_02031D20(sub_02032F34, 0);
    }
}

u32 sub_02032FDC(u8 param0) {
    ov04_021D77C4(sub_020303BC, sub_02030238);
    UNK_021C5A00->unk42 = param0;
    sub_02031D20(sub_02032F98, 0);

    return 1;
}

u32 sub_0203300C() {
    if (UNK_021C5A00->unk24 == sub_02032F34) {
        return 0;
    }

    if (UNK_021C5A00->unk24 == sub_02032EB0) {
        return 1;
    }

    if (UNK_021C5A00->unk24 == sub_02032E90) {
        return 3;
    }

    if (UNK_021C5A00->unk24 == sub_02032EA8) {
        return 4;
    }

    if (UNK_021C5A00->unk24 == sub_02032EAC) {
        return 5;
    }

    return 2;
}

void sub_02033060() {
    ov04_021D77C4(sub_020303BC, sub_02030238);
    if (ov04_021D8494(-1) != 0) {
        UNK_021C5A00->unk4D = 0;
        sub_0202FC60();
        sub_02031D20(sub_02032F34, 0);
    }
}

void sub_020330A0() {
    sub_020313A0(0);
    if (ov04_021D82BC(UNK_021C5A00->unk41) != 0) {
        ov04_021D836C();
        sub_02031D20(sub_02033060, 0);
        return;
    }

    if (ov04_021D7F8C() < 0) {
        sub_02031D20(sub_02032E8C, 0);
    }
}

void sub_020330E4() {
    if (sub_02031190() == 0) {
        UNK_021C5A00->unk41 = 0;
        sub_02031D20(sub_020330A0, 0);
    } else {
        UNK_021C5A00->unk41 = 1;
        sub_02031D20(sub_020330A0, 0);
    }

    UNK_021C5A00->unk4D = 1;
}

u8 sub_02033128() {
    return UNK_021C5A00->unk4D;
}

u32 sub_02033138() {
    if (UNK_021C5A00->unk24 == sub_02033060) {
        return 1;
    }

    return 0;
}

u32 sub_02033154() {
    if (UNK_021C5A00->unk24 == sub_02032F34) {
        return 1;
    }

    if (UNK_021C5A00->unk24 == sub_02033060) {
        return 1;
    }

    return 0;
}

u32 sub_02033180() {
    return UNK_021C5A00->unk34;
}

void sub_0203318C() {
    sub_020313A0(0);
    if (ov04_021D82BC(0) != 0) {
        ov04_021D836C();
        sub_02031D20(sub_02032440, 0);
    }

    if (ov04_021D7F8C() < 0) {
        sub_02031D20(sub_02032E8C, 0);
    }
}

void sub_020331C4() {
    if (UNK_021C5A00 != NULL) {
        ClearSoftResetDisableMask(1);
        sub_02031D20(sub_02032440, 5);
    }
}

void sub_020331E8() {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk41 = 0;
        sub_02031D20(sub_020330A0, 0);
    }
}

void sub_02033208() {
    if (UNK_021C5A00 != NULL) {
        if (sub_02031190() == 0) {
            UNK_021C5A00->unk41 = 0;
        } else {
            UNK_021C5A00->unk41 = 1;
        }

        sub_02031D20(sub_020330A0, 0);
    }
}

void sub_0203323C() {
    u8 res = (u8)sub_02031190();
    sub_020311D0(0x15, &res);
}

u32 sub_02033250() {
    if (UNK_021C5A00 != NULL) {
        if (UNK_021C5A00->unk24 == sub_02032E8C) {
            return 1;
        }

        if (UNK_021C5A00->unk24 == sub_02032E90 && UNK_021C5A00->unk44 != 0) {
            return 1;
        }
    }

    return 0;
}

void sub_02033288(struct SaveData *save) {
    if (UNK_021C5A00 == NULL) {
        CreateHeapAtEnd(3, 0xf, 0x100);
        UNK_021C5A00 = (struct UnkStruct_02031734 *)AllocFromHeap(HEAP_ID_15, sizeof(struct UnkStruct_02031734));
        MI_CpuFill8(UNK_021C5A00, 0, sizeof(struct UnkStruct_02031734));

        UNK_021C5A00->unk3F = 0x18;
        UNK_021C5A00->unk46 = 1;
        UNK_021C5A00->unk28 = save;
        sub_020334E8(0, 1);
        SetSoftResetDisableMask(1);
    }
}

void sub_020332DC() {
    if (UNK_021C5A00 != 0) {
        ClearSoftResetDisableMask(1);
        sub_020334E8(0, 0);
        FreeToHeap(UNK_021C5A00);
        UNK_021C5A00 = NULL;
        DestroyHeap(HEAP_ID_15);
    }
}

void sub_02033310(struct SaveData *save) {
    if (UNK_021C5A00 == NULL) {
        CreateHeapAtEnd(3, HEAP_ID_15, 0x100);
        UNK_021C5A00 = (struct UnkStruct_02031734 *)AllocFromHeap(HEAP_ID_15, sizeof(struct UnkStruct_02031734));
        MI_CpuFill8(UNK_021C5A00, 0, sizeof(struct UnkStruct_02031734));
        UNK_021C5A00->unk3F = 0x19;
        UNK_021C5A00->unk46 = 1;
        UNK_021C5A00->unk28 = save;
        sub_020334E8(0, 1);
        SetSoftResetDisableMask(1);
    }
}

void sub_02033364() {
    if (UNK_021C5A00 != 0) {
        ClearSoftResetDisableMask(1);
        sub_020334E8(0, 0);
        FreeToHeap(UNK_021C5A00);
        UNK_021C5A00 = NULL;
        DestroyHeap(HEAP_ID_15);
    }
}

u32 sub_02033398() {
    u32 st4;
    u32 st0;
    if (UNK_021C5A00 == NULL) {
        return 0;
    }

    if (UNK_021C5A00->unk3F == 0x18) {
        if (ov04_021DD718(&st4, &st0) != 0) {
            ov04_021DD6F0();
            return 1;
        }
    } else if (UNK_021C5A00->unk3F == 0x19) {
        if (ov04_021DD718(&st4, &st0) != 0 && st0 == 7) {
            return 1;
        }
    }

    return 0;
}

void sub_020333F0() {
    s32 res = ov04_021D76AC();
    if (res < 0) {
        sub_02032F20((u32)res);
        sub_02031D20(sub_02032E8C, 0);
        return;
    } else if (res > 0) {
        sub_02031D20(sub_02033060, 0);
    }
}

void sub_0203341C() {
    if (sub_0202E4C8()) {
        CreateHeapAtEnd(3, 0x31, 0x31000);
        if (sub_0202F918(1, 1, 0x200, 1) != 0) {
            ov05_021D74E0(UNK_021C5A00->unk28, 0x31);
            ov04_021D83A8(sub_020335D0);
            sub_0202FA10();
            sub_02031D20(sub_020333F0, 0);
        }
    }
}

void *sub_0203346C(struct SaveData *save, u32 param1) {
    Save_PlayerData_GetProfileAddr(save);
    if (sub_02030F40() != 0) {
        return 0;
    }

    SetSoftResetDisableMask(1);
    CreateHeapAtEnd(3, 0xf, 0x7080);
    sub_02031734(save, 0x17);
    UNK_021C5A00->unk00 = AllocFromHeap(HEAP_ID_15, param1);
    MI_CpuFill8(UNK_021C5A00->unk00, 0, param1);

    UNK_021C5A00->unk40 = 0;
    UNK_021C5A00->unk28 = save;
    sub_02031D20(sub_0203341C, 0);

    return UNK_021C5A00->unk00;
}

void *sub_020334DC() {
    return UNK_021C5A00->unk00;
}

void sub_020334E8(u8 param0, u8 param1) {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk44 = param0;
        UNK_021C5A00->unk45 = param1;
    }

    sub_0202EE84(param0);
    sub_0202EEB0(param0);
}

u8 sub_02033510() {
    if (UNK_021C5A00 != NULL) {
        if (UNK_021C5A00->unk4E != 0) {
            return 1;
        }

        return UNK_021C5A00->unk45;
    }

    return 0;
}

s32 sub_02033534() {
    if (UNK_021C5A00 != NULL) {
        return UNK_021C5A00->unk3F;
    }

    return 1;
}

u8 sub_0203354C() {
    if (UNK_021C5A00 != NULL) {
        return UNK_021C5A00->unk40;
    }

    return 0;
}

void sub_02033564(void *src) {
    MI_CpuCopy8(src, UNK_021C5A00->unk04, 0x6);
}

void sub_02033578(void *dst) {
    MI_CpuCopy8(UNK_021C5A00->unk04, dst, 0x6);
}

u32 sub_02033590() {
    if (sub_02033534() >= 0x13) {
        return 1;
    }

    return 0;
}

void sub_020335A4(u8 param0) {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk47 = param0;
    }
}

u8 sub_020335B8() {
    if (UNK_021C5A00 != NULL) {
        return UNK_021C5A00->unk47;
    }

    return 0;
}

void sub_020335D0(s32 param0) {
    ShowCommunicationError(HEAP_ID_DEFAULT, 1, param0);
    while (TRUE) {
    }
}

void sub_020335E0() {
    ShowCommunicationError(HEAP_ID_DEFAULT, 4, 0);
    while (TRUE) {
    }
}

void sub_020335F0() {
}

void sub_020335F4() {
    if (sub_02033510() != 0) {
        if (sub_020311F0() == 0 && sub_02033250() == 0 && sub_02033398() == 0) {
            if (UNK_021C5A00->unk4E == 0) {
                return;
            }
        }

        if (sub_020335B8() != 0) {
            return;
        }

        sub_0200541C();
        sub_0202287C(UNK_021C5A00->unk28);
        gSystem.touchpadReadAuto = 1;
        if (UNK_021C5A00->unk4E == 3) {
            sub_020335A4(3);
            return;
        }

        if (UNK_021C5A00->unk3F == 0x19 || UNK_021C5A00->unk3F == 0xf) {
            sub_020335A4(2);
        } else {
            sub_020335A4(1);
        }
    }
}

BOOL sub_02033678() {
    if (sub_0202EDD8() || !sub_02031810()) {
        return TRUE;
    }

    if (!sub_0202E344()) {
        return TRUE;
    }

    return FALSE;
}

u32 sub_020336A0(u8 param0) {
    if (UNK_021C5A00 != NULL) {
        UNK_021C5A00->unk4E = param0;
        sub_02031468();
        return 1;
    }

    return 0;
}
