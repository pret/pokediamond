#include "unk_02031734.h"

const struct UnkStruct_02031734_const2 UNK_020EEC48 = { { (u32)FUN_02032B84, 0 } };

const struct UnkStruct_02031734_const1 UNK_020EEC50 = {
    { (u32)FUN_0203213C, (u32)FUN_02032138, 0 }
};

const struct UnkStruct_02031734_const1 UNK_020EEC5C = {
    { (u32)FUN_02032234, (u32)FUN_0203234C, 0 }
};

char UNK_02105D5C[] = "FREAK";

char UNK_02105D6C[] = " GAME";

char UNK_02105D64[] = " FULL";

struct UnkStruct_02031734 *UNK_021C5A00;

extern void FUN_0202E49C();
extern void FUN_0202D8D0(u32 param0, u32 param1, u32 param2);
extern void FUN_02033E74();
extern void FUN_0202D918();
extern void FUN_02033ED0();
extern void FUN_0202E4F0();
extern void FUN_0202D298();
extern void FUN_0202D344(u32 param0);
extern void FUN_0202D1B0(u8 param0);
extern void FUN_0202D36C(u32 param0);
extern u32 MOD04_021DDB08();
extern void FUN_02033EEC(u32 param0);
extern u32 FUN_0202EDF8();
extern u32 WM_GetLinkLevel();
extern u32 FUN_0202E4C8();
extern void FUN_0202E29C(struct PlayerData *player_data);
extern void FUN_0202DB14(struct SaveBlock2 *sav2, u32 param1);
extern s64 _ll_mul(s64, s64);
extern u32 FUN_0202EE0C();
extern void FUN_0202EA54();
extern s32 FUN_0202E8F4();
extern s32 FUN_0202E950();
extern u32 FUN_0202E8A0(u8 param0);
extern u32 FUN_0202E6F0();
extern void FUN_0202EE84(u8 param0);
extern void FUN_0202E7B0(u32 param0);
extern u32 FUN_0202F104();
extern void FUN_0202DBE0();
extern void FUN_0202DDE8();
extern void FUN_0202D308(void (*param0)(u32, u32));
extern void MOD04_021D83C0();
extern s32 MOD04_021D7F8C();
extern s32 MOD04_021D7800(u32 param0);
extern u32 MOD04_021D8494(s32 param0);
extern void MOD04_021D77C4(void (*param0)(u32, u8 *, u16), void (*param1)(u32, void *, u32));
extern u32 MOD04_021D82BC(u8 param0);
extern void MOD04_021D836C();
extern u32 MOD04_021DD718(u32 *param0, u32 *param1);
extern void MOD04_021DD6F0();
extern s32 MOD04_021D76AC();
extern MOD05_021D74E0(struct SaveBlock2 *sav2, u32 param1);
extern void MOD04_021D83A8(void (*param0)(s32));
extern void FUN_0202EEB0(u8 param0);
extern void FUN_02033F70(int, int, int);
extern void FUN_0200541C();
extern u32 FUN_0202EDD8();
extern u32 FUN_0202E344();

THUMB_FUNC void FUN_02031734(struct SaveBlock2 *sav2, u8 param1)
{
    if (UNK_021C5A00 == NULL)
    {
        FUN_0202E49C();
        struct UnkStruct_02031734 *ptr = AllocFromHeap(0xf, sizeof(struct UnkStruct_02031734));
        UNK_021C5A00 = ptr;
        MI_CpuFill8(ptr, 0, sizeof(struct UnkStruct_02031734));

        UNK_021C5A00->unk3A = 0x32;
        UNK_021C5A00->unk43 = 1;
        UNK_021C5A00->unk28 = sav2;

        UNK_021C5A00->unk2C = Sav2_PlayerData_GetProfileAddr(sav2);

        UNK_021C5A00->unk3C = 2;
        UNK_021C5A00->unk3D = 0;
        UNK_021C5A00->unk48 = 0;
        UNK_021C5A00->unk3F = param1;

        FUN_020312BC(UNK_021C5A00->unk0C);
        FUN_0202D8D0(0, 0, 0);

        if (param1 != 9 && param1 != 0x11 && param1 != 0xf)
        {
            FUN_02033E74();
        }
    }
}

THUMB_FUNC void FUN_020317C0()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_0202D918();
        if (UNK_021C5A00->unk00 != NULL)
        {
            FreeToHeap(UNK_021C5A00->unk00);
        }

        if (UNK_021C5A00->unk3F >= 0x13)
        {
            FUN_020168D0(0x31);
        }

        FUN_02033ED0();
        FUN_0202E4F0();

        FreeToHeap(UNK_021C5A00);
        FUN_020168D0(0xf);

        UNK_021C5A00 = NULL;
    }
}

THUMB_FUNC BOOL FUN_02031810()
{
    if (UNK_021C5A00 != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void FUN_02031824(struct SaveBlock2 *sav2)
{
    if (UNK_021C5A00 == NULL)
    {
        FUN_02016828(3, 0xf, 0xe000);
        FUN_02031734(sav2, 0xa);

        UNK_021C5A00->unk40 = 0;
        FUN_02031D20(FUN_02031D30, 0x32);
    }
}

THUMB_FUNC void FUN_02031860()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_02031468();
        FUN_02031D20(FUN_020323CC, 0);
    }
}

THUMB_FUNC void FUN_02031880()
{
    FUN_0202FC60();
    UNK_021C5A00->unk38 = FUN_02031190();

    FUN_02031D20(FUN_020321B8, 0);
}

THUMB_FUNC void FUN_020318A4(u8 param0)
{
    UNK_021C5A00->unk4F = param0;
}

THUMB_FUNC void FUN_020318B4()
{
    FUN_02031D20(FUN_02032028, 0);
}

THUMB_FUNC BOOL FUN_020318C4()
{
    struct UnkStruct_02031734_const1 st0 = UNK_020EEC50;

    u32 r1 = (u32)UNK_021C5A00->unk24;

    if (UNK_021C5A00 == NULL)
    {
        return FALSE;
    }

    for (u32 i = 0; st0.unk00[i] != 0; i++)
    {

        if (r1 == st0.unk00[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

THUMB_FUNC void FUN_02031914()
{
    FUN_02031D20(FUN_02032178, 0);
}

THUMB_FUNC void FUN_02031924()
{
    UNK_021C5A00->unk4C = 1;
}

THUMB_FUNC void FUN_02031934()
{
    FUN_0202E49C();
    FUN_02031D20(FUN_02032194, 0);
}

THUMB_FUNC void FUN_02031948(struct SaveBlock2 *sav2, u8 param1, u8 param2, u32 param3)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7080);
        FUN_02031734(sav2, param1);
        UNK_021C5A00->unk40 = param2;
        UNK_021C5A00->unk30 = param3;
        FUN_02031D20(FUN_020321D0, 0);
    }
}

THUMB_FUNC void FUN_02031990(struct SaveBlock2 *sav2, u8 param1, u8 param2, u32 param3)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7080);
        FUN_02031734(sav2, param1);
        UNK_021C5A00->unk40 = param2;
        UNK_021C5A00->unk30 = param3;
        FUN_02031D20(FUN_0203224C, 0);
    }
}

THUMB_FUNC void FUN_020319D8(u8 param0)
{
    UNK_021C5A00->unk3E = param0;
    FUN_02031D20(FUN_02032298, 0);
}

THUMB_FUNC void FUN_020319F4()
{
    FUN_0202FCA8();
    FUN_02031D20(FUN_02032364, 0);
}

THUMB_FUNC void FUN_02031A08()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_02031D20(FUN_02032440, 5);
    }
}

THUMB_FUNC void FUN_02031A24()
{
    FUN_0202D298();
}

THUMB_FUNC BOOL FUN_02031A2C()
{
    struct UnkStruct_02031734_const1 st0 = UNK_020EEC5C;

    u32 r1 = (u32)UNK_021C5A00->unk24;

    if (UNK_021C5A00 == NULL)
    {
        return FALSE;
    }

    for (u32 i = 0; st0.unk00[i] != 0; i++)
    {

        if (r1 == st0.unk00[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

THUMB_FUNC void FUN_02031A7C(struct SaveBlock2 *sav2)
{
    if (UNK_021C5A00 == NULL)
    {
        if (FUN_02016828(3, 0xf, 0x7080) == 0)
        {
            FUN_020335E0();
        }

        FUN_02031734(sav2, 9);
        UNK_021C5A00->unk3F = 9;
        UNK_021C5A00->unk40 = 0;
        FUN_02031D20(FUN_02032478, 0);
    }
}

THUMB_FUNC void FUN_02031AC8(u8 param0)
{
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk38 = 3;
    FUN_0202D344(1);
    FUN_02033E74();
    FUN_02031D20(FUN_02032628, 0);
}

THUMB_FUNC s32 FUN_02031AF4()
{
    if (UNK_021C5A00 == NULL)
    {
        return -1;
    }
    if (UNK_021C5A00->unk24 == FUN_0203279C)
    {
        return 1;
    }

    if (UNK_021C5A00->unk24 == FUN_020327B4)
    {
        return -1;
    }

    return 0;
}

THUMB_FUNC BOOL FUN_02031B2C()
{
    if (UNK_021C5A00 == NULL)
    {
        return FALSE;
    }
    if (UNK_021C5A00->unk24 == FUN_020327FC)
    {
        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC void FUN_02031B50()
{
    FUN_0202D344(0);
    if (UNK_021C5A00->unk44 != 1 || UNK_021C5A00->unk45 != 1 || UNK_021C5A00->unk3F == 9)
    {
        FUN_020334E8(0, 0);
    }

    FUN_02033ED0();
    UNK_021C5A00->unk3F = 9;
    UNK_021C5A00->unk48 = 0;
    FUN_0202D1B0(UNK_021C5A00->unk3C);

    if (FUN_02031190() == 0)
    {
        FUN_0202D36C(1);
        FUN_02031D20(FUN_020323DC, 0xf);
        return;
    }

    FUN_02031D20(FUN_02032424, 5);
}

THUMB_FUNC u32 FUN_02031BD0()
{
    if (UNK_021C5A00 == NULL)
    {
        return 1;
    }

    if (UNK_021C5A00->unk24 != FUN_020324F8)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC void FUN_02031BF4()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_02031D20(FUN_02032440, 5);
    }
}

THUMB_FUNC void FUN_02031C10()
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk48 = 1;
        FUN_0202D344(1);
    }
}

THUMB_FUNC void FUN_02031C2C()
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk48 = 1;
        FUN_0202D344(1);
        FUN_02031D20(FUN_02032850, 0);
    }
}

THUMB_FUNC void FUN_02031C54()
{
    UNK_021C5A00->unk3F = 0x12;
}

THUMB_FUNC void FUN_02031C64()
{
    UNK_021C5A00->unk3F = 0x9;
}

THUMB_FUNC void FUN_02031C74(struct SaveBlock2 *sav2, u8 param1)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7080);
        FUN_02031734(sav2, param1);
        FUN_02031D20(FUN_02032E00, 0);
    }
}

THUMB_FUNC void FUN_02031CA8(struct SaveBlock2 *sav2, u8 param1)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7080);
        FUN_02031734(sav2, param1);
        FUN_02031D20(FUN_02032E48, 0);
    }
}

THUMB_FUNC void FUN_02031CDC()
{
    if (UNK_021C5A00 != NULL && UNK_021C5A00->unk24 != 0)
    {
        ((void (*)(void))(UNK_021C5A00->unk24))();
    }
    if (FUN_02033590() != 0)
    {
        FUN_02033EEC(3 - MOD04_021DDB08());
        return;
    }

    if (FUN_0202EDF8() != 0)
    {
        FUN_02033EEC(3 - WM_GetLinkLevel());
    }
}

THUMB_FUNC void FUN_02031D20(void (*param0)(), u32 param1)
{
    UNK_021C5A00->unk24 = param0;
    UNK_021C5A00->unk3A = (u16)param1;
}

THUMB_FUNC void FUN_02031D30()
{
    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (FUN_0202E4C8() == 0)
    {
        return;
    }

    FUN_0202E29C(UNK_021C5A00->unk2C);
    FUN_0202DB14(UNK_021C5A00->unk28, 0);
    FUN_02031268(1);
    FUN_02030FA8();

    if (UNK_021C5A00->unk4A != 0)
    {
        if (FUN_0202F918(1, UNK_021C5A00->unk43, 0x1F4, 1) == 0)
        {
            return;
        }

        u32 r1 = compute(UNK_021C5A00->unk0C, 0x14);

        UNK_021C5A00->unk43 = 0;
        FUN_02031D20(FUN_020320C4, r1 + 0x14);
        return;
    }

    if (FUN_0202F950(1, 1, 0x1F4) != 0)
    {
        if (UNK_021C5A00->unk4C != 0)
        {
            FUN_02031D20(FUN_020323B8, 0);
        }
        else
        {
            FUN_02031D20(FUN_02031EE0, 0x40);
        }
    }
}

THUMB_FUNC void FUN_02031E08()
{
    if (FUN_0202EE0C() != 0)
    {
        FUN_02031268(1);
        FUN_02030FA8();

        if (UNK_021C5A00->unk4A != 0)
        {
            FUN_02031D20(FUN_02032058, 0);
            return;
        }

        if (FUN_0202F950(0, 1, 0x1F4) != 0)
        {

            u32 r1 = compute(UNK_021C5A00->unk0C, 0x40);

            if (UNK_021C5A00->unk38 != 0)
            {
                r1 = (u32)(UNK_021C5A00->unk38 << 6);
                UNK_021C5A00->unk38 = 0;
            }
            FUN_02031D20(FUN_02031EE0, r1);
        }
    }
}

THUMB_FUNC void FUN_02031E8C()
{
    if (FUN_0202EE0C() != 0)
    {
        if (FUN_0202F950(0, 0, 0x1F4) != 0)
        {

            u32 r1 = compute(UNK_021C5A00->unk0C, 0x20);

            FUN_02031D20(FUN_02031EE0, r1 + 0x10);
        }
    }
}

THUMB_FUNC void FUN_02031EE0()
{
    FUN_0202EA54();
    if (UNK_021C5A00->unk4F == 0 && UNK_021C5A00->unk4B == 0)
    {
        s32 r0 = FUN_0202E8F4();
        if (r0 != -1)
        {
            UNK_021C5A00->unk3E = (u8)r0;
            FUN_02031D20(FUN_02031F60, 0x20);
            return;
        }

        if (UNK_021C5A00->unk3A != 0)
        {
            UNK_021C5A00->unk3A--;
            return;
        }

        r0 = FUN_0202E950();
        if (r0 != -1)
        {
            UNK_021C5A00->unk3E = (u8)r0;
            FUN_02031D20(FUN_02031F60, 0x20);
            return;
        }

        FUN_02031D20(FUN_02032028, 0);
    }
}

THUMB_FUNC void FUN_02031F60()
{
    FUN_0202EA54();
    if (FUN_0202E8A0(UNK_021C5A00->unk3E) != 0 && FUN_0202FB18(UNK_021C5A00->unk3E) != 0)
    {
        FUN_02031D20(FUN_02031FC8, 0x64);
        return;
    }

    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_02032028, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_02031D20(FUN_02032028, 0);
}

THUMB_FUNC void FUN_02031FC8()
{
    if (FUN_02030E7C(FUN_02031190()) != 0)
    {
        FUN_0202FC60();
        FUN_02031268(0);
        FUN_02030FA8();
        FUN_02031D20(FUN_0203213C, 0);
        return;
    }

    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_02032028, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_02031D20(FUN_02032028, 0);
}

THUMB_FUNC void FUN_02032028()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02032058, 0);
    }
}

THUMB_FUNC void FUN_02032040()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02031E8C, 0);
    }
}

THUMB_FUNC void FUN_02032058()
{
    if (FUN_0202EE0C() != 0)
    {
        FUN_02031268(1);
        if (FUN_0202F918(0, UNK_021C5A00->unk43, 0x1F4, 1) != 0)
        {
            u32 r1 = compute(UNK_021C5A00->unk0C, 0x14);

            UNK_021C5A00->unk43 = 0;
            FUN_02031D20(FUN_020320C4, r1 + 0x14);
        }
    }
}

THUMB_FUNC void FUN_020320C4()
{
    if (FUN_020311E8() != 0)
    {
        UNK_021C5A00->unk43 = 1;
        FUN_02031D20(FUN_02032118, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (UNK_021C5A00->unk4A == 0 && FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02032040, 2);
    }
}

THUMB_FUNC void FUN_02032118()
{
    FUN_02031268(0);
    FUN_0202EE84(1);
    FUN_02030FA8();
    FUN_02031D20(FUN_02032138, 0);
}

THUMB_FUNC void FUN_02032138()
{
}
THUMB_FUNC void FUN_0203213C()
{
}

THUMB_FUNC void FUN_02032140()
{
    if (UNK_021C5A00->unk3F < 0x13)
    {
        if (FUN_0202EE0C() == 0)
        {
            return;
        }

        FUN_02031268(1);
        FUN_02030FA8();
        FUN_0202E7B0(1);
    }

    FUN_02031D20(FUN_020323B8, 0);
}

THUMB_FUNC void FUN_02032178()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_0202FC60();
        FUN_02031D20(FUN_02032140, 0);
    }
}

THUMB_FUNC void FUN_02032194()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E7B0(0);
        FUN_0202FC60();
        FUN_02031D20(FUN_02031E08, 0);
    }
}

THUMB_FUNC void FUN_020321B8()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02031E08, 0);
    }
}

THUMB_FUNC void FUN_020321D0()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, UNK_021C5A00->unk30);
        if (FUN_0202F918(1, 1, 0x200, 1) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032218, 0);
        }
    }
}

THUMB_FUNC void FUN_02032218()
{
    if (FUN_02030E7C(FUN_02031190()) != 0)
    {
        FUN_02031D20(FUN_02032234, 0);
    }
}

THUMB_FUNC void FUN_02032234()
{
    if (FUN_02030F40() == 0)
    {
        FUN_02031D20(FUN_020323BC, 0);
    }
}

THUMB_FUNC void FUN_0203224C()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, UNK_021C5A00->unk30);
        if (FUN_0202F950(1, 1, 0x200) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032290, 0);
        }
    }
}

THUMB_FUNC void FUN_02032290()
{
    FUN_0202EA54();
}

THUMB_FUNC void FUN_02032298()
{
    FUN_0202EA54();
    if (FUN_0202FB18(UNK_021C5A00->unk3E) != 0)
    {
        FUN_02031D20(FUN_020322C0, 0xa);
    }
}

THUMB_FUNC void FUN_020322C0()
{
    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_020322F8, 0);
    }

    if (FUN_02030E7C(FUN_02031190()) != 0 && FUN_02031190() != 0)
    {
        FUN_02031D20(FUN_0203234C, 0);
    }
}

THUMB_FUNC void FUN_020322F8()
{
    FUN_0202E6F0();
    FUN_02031D20(FUN_0203230C, 2);
}

THUMB_FUNC void FUN_0203230C()
{
    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (FUN_0202EE0C() != 0 && FUN_0202F950(0, 1, 0x200) != 0)
    {
        FUN_0202FA10();
        FUN_02031D20(FUN_02032298, 0xa);
    }
}

THUMB_FUNC void FUN_0203234C()
{
    if (FUN_02030F40() == 0)
    {
        FUN_02031D20(FUN_020323BC, 0);
    }
}

THUMB_FUNC void FUN_02032364()
{
    FUN_0202E6F0();
    FUN_02031D20(FUN_02032378, 2);
}

THUMB_FUNC void FUN_02032378()
{
    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (FUN_0202EE0C() != 0 && FUN_0202F950(0, 1, 0x200) != 0)
    {
        FUN_0202FA10();
        FUN_02031D20(FUN_02032290, 0xa);
    }
}

THUMB_FUNC void FUN_020323B8()
{
}

THUMB_FUNC void FUN_020323BC()
{
    if (FUN_02030F40() == 0)
    {
        FUN_020317C0();
    }
}

THUMB_FUNC void FUN_020323CC()
{
    FUN_02031D20(FUN_02032440, 5);
}

THUMB_FUNC void FUN_020323DC()
{
    if (FUN_02030F20() <= 1)
    {
        FUN_0202D36C(0);
        FUN_0202FC80();
        FUN_02031D20(FUN_020324F8, 0);
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_0202D36C(0);
    FUN_0202FC80();
    FUN_02031D20(FUN_020324F8, 0);
}

THUMB_FUNC void FUN_02032424()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_0202FC60();
        FUN_02031D20(FUN_020324F8, 0);
    }
}

THUMB_FUNC void FUN_02032440()
{
    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
    }

    if (FUN_0202E6F0() != 0 && UNK_021C5A00->unk3A == 0)
    {
        FUN_0202FA5C();
        FUN_02031D20(FUN_020323BC, 0);
    }
}

THUMB_FUNC void FUN_02032478()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202D1B0(UNK_021C5A00->unk3C);
        FUN_0202DB14(UNK_021C5A00->unk28, 0);
        if (FUN_0202F950(1, 1, 0x200) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_020324C8, 0x40);
        }
    }
}

THUMB_FUNC void FUN_020324C8()
{
    FUN_0202EA54();
    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02032510, 0);
    }
}

THUMB_FUNC void FUN_020324F8()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02032510, 0);
    }
}

THUMB_FUNC void FUN_02032510()
{
    if (FUN_0202EE0C() != 0 && FUN_0202F918(0, UNK_021C5A00->unk43, 0x200, 1) != 0)
    {
        // the compiler optimizes away the result of this function because it's not used, so any
        // second parameter value matches
        compute(UNK_021C5A00->unk0C, 0);

        FUN_0202FA10();
        UNK_021C5A00->unk43 = 0;

        FUN_02031D20(FUN_02032578, 0x2710);
    }
}

THUMB_FUNC void FUN_02032578()
{
    if (FUN_0202F104() == 0)
    {
        if (FUN_020311E8() != 0)
        {
            UNK_021C5A00->unk43 = 1;
            FUN_02033E74();
            FUN_02031D20(FUN_020327FC, 0);
            return;
        }

        if (UNK_021C5A00->unk3A != 0)
        {
            UNK_021C5A00->unk3A--;
            return;
        }
    }

    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_020325D0, 0);
    }
}

THUMB_FUNC void FUN_020325D0()
{
    if (FUN_0202EE0C() != 0 && FUN_0202F950(0, 0, 0x200) != 0)
    {
        FUN_0202FA10();

        u32 r1 = compute(UNK_021C5A00->unk0C, 0x20);

        FUN_02031D20(FUN_020324C8, r1);
    }
}

THUMB_FUNC void FUN_02032628()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_02032640, 0);
    }
}

THUMB_FUNC void FUN_02032640()
{
    if (FUN_0202EE0C() != 0 && FUN_0202F950(0, 0, 0x200))
    {
        FUN_0202FA10();
        FUN_02031D20(FUN_0203266C, 0x64);
    }
}

THUMB_FUNC void FUN_0203266C()
{
    if (FUN_0202E8A0(UNK_021C5A00->unk3E) != 0 && FUN_0202FB18(UNK_021C5A00->unk3E) != 0)
    {
        FUN_02031D20(FUN_020326D0, 0x64);
        return;
    }

    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_020327B8, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_02031D20(FUN_020327B8, 0);
}

THUMB_FUNC void FUN_020326D0()
{
    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_020327B8, 0);
        return;
    }

    if (FUN_02030E7C(FUN_02031190()) != 0)
    {
        UNK_021C5A00->unk3D = 0;
        FUN_020311D0(6, UNK_02105D5C);
        FUN_02031D20(FUN_02032738, 0x78);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_02031D20(FUN_020327B8, 0);
}

THUMB_FUNC void FUN_02032738()
{
    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_020327B8, 0);
        return;
    }

    if (UNK_021C5A00->unk3D == 2)
    {
        FUN_02031D20(FUN_020327B4, 0);
        return;
    }
    else if (UNK_021C5A00->unk3D == 1)
    {
        FUN_0202DBE0();
        FUN_02031D20(FUN_0203279C, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    FUN_02031D20(FUN_020327B8, 0);
}

THUMB_FUNC void FUN_0203279C()
{
    if (FUN_020311F0() != 0)
    {
        FUN_02031D20(FUN_020327B8, 0);
    }
}

THUMB_FUNC void FUN_020327B4()
{
}

THUMB_FUNC void FUN_020327B8()
{
    UNK_021C5A00->unk3D = 0;
    if (FUN_0202E6F0() != 0)
    {
        if (UNK_021C5A00->unk38 != 0)
        {
            UNK_021C5A00->unk38--;
            FUN_02031D20(FUN_02032640, 0);
            return;
        }

        FUN_02031D20(FUN_020327B4, 0);
    }
}

THUMB_FUNC void FUN_020327FC()
{
    if (FUN_020311E8() == 0)
    {
        if (FUN_02033510() == 0 && FUN_0202E6F0() != 0)
        {
            FUN_02031D20(FUN_020325D0, 0);
        }
    }
    else if (FUN_02031190() == 0)
    {
        FUN_0202DDE8();
    }

    if (FUN_020311F0() != 0 && FUN_02033510() == 0)
    {
        FUN_02031D20(FUN_020327B8, 0);
    }
}

THUMB_FUNC void FUN_02032850()
{
    if (FUN_0202EE0C() != 0)
    {
        if (FUN_0202F918(0, UNK_021C5A00->unk43, 0x200, 0) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_020323B8, 0);
        }
    }
}

THUMB_FUNC void FUN_02032888()
{
    u8 st0[4];
    UNK_021C5A00->unk3F = 0xd;
    if (FUN_02031190() == 0)
    {
        st0[1] = 0;
        FUN_020311D0(0xa, &st0[1]);
        return;
    }

    st0[0] = 0;
    FUN_020311D0(0xa, st0);
}

THUMB_FUNC void FUN_020328C0(u8 param0)
{
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk38 = 3;
    FUN_02031D20(FUN_02032924, 0);
}

THUMB_FUNC void FUN_020328E4()
{
    UNK_021C5A00->unk3F = 7;
}

THUMB_FUNC void FUN_020328F4(u8 param0)
{
    UNK_021C5A00->unk3E = param0;
    UNK_021C5A00->unk3F = 7;
    UNK_021C5A00->unk38 = 3;
    FUN_02033E74();
    FUN_02031D20(FUN_02032628, 0);
}

THUMB_FUNC void FUN_02032924()
{
    if (FUN_0202E6F0() != 0)
    {
        FUN_02031D20(FUN_0203293C, 0);
    }
}

THUMB_FUNC void FUN_0203293C()
{
    if (FUN_0202EE0C() != 0)
    {
        UNK_021C5A00->unk3F = 0xd;
        if (FUN_0202F950(0, 0, 0x200) != 0)
        {
            FUN_0202FA1C();
            FUN_02031D20(FUN_02032978, 0x64);
        }
    }
}

THUMB_FUNC void FUN_02032978()
{
    if (FUN_0202E8A0(UNK_021C5A00->unk3E) != 0 && FUN_0202FB18(UNK_021C5A00->unk3E) != 0)
    {
        FUN_02031D20(FUN_020329F4, 0x64);
        return;
    }

    if (FUN_020311F0() != 0 || UNK_021C5A00->unk3A == 0)
    {
        UNK_021C5A00->unk38--;
        if (UNK_021C5A00->unk38 == 0)
        {
            FUN_02031D20(FUN_020327B4, 0);
            return;
        }

        FUN_02031D20(FUN_02032924, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }
}

THUMB_FUNC void FUN_020329F4()
{
    if (UNK_021C5A00->unk3A > 0x5a)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    if (FUN_020311F0() != 0)
    {
        UNK_021C5A00->unk38--;
        if (UNK_021C5A00->unk38 == 0)
        {
            FUN_02031D20(FUN_020327B4, 0);
            return;
        }

        FUN_02031D20(FUN_02032924, 0);
        return;
    }

    if (FUN_02030E7C(FUN_02031190()) != 0)
    {
        FUN_02031D20(FUN_0203279C, 0);
        return;
    }

    if (UNK_021C5A00->unk3A != 0)
    {
        UNK_021C5A00->unk3A--;
        return;
    }

    UNK_021C5A00->unk38--;
    if (UNK_021C5A00->unk38 == 0)
    {
        FUN_02031D20(FUN_020327B4, 0);
        return;
    }

    FUN_02031D20(FUN_02032924, 0);
}

THUMB_FUNC void FUN_02032A8C(u8 param0, u32 param1, u8 *param2)
{
#pragma unused(param1)
    if (FUN_02031190() == 0)
    {

        u32 i;
        BOOL r3 = TRUE;
        for (i = 0; i < 6; i++)
        {
            if (UNK_02105D5C[i] != param2[i])
            {
                r3 = FALSE;
                break;
            }
        }

        if (r3 && UNK_021C5A00->unk48 == 0)
        {
            UNK_02105D6C[0] = param0;
            FUN_02030C4C(7, UNK_02105D6C);
            return;
        }

        UNK_02105D64[0] = param0;
        FUN_02030C4C(7, UNK_02105D64);
    }
}

THUMB_FUNC void FUN_02032AEC(u32 param0, u32 param1, u8 *param2)
{
#pragma unused(param0)
#pragma unused(param1)
    u32 i;
    BOOL r4 = TRUE;
    for (i = 1; i < 6; i++)
    {
        if (param2[i] != UNK_02105D6C[i])
        {
            r4 = FALSE;
            break;
        }
    }

    if (r4)
    {
        u8 first = param2[0];
        if (first != FUN_02031190())
        {
            return;
        }

        UNK_021C5A00->unk3D = 1;
        return;
    }

    r4 = TRUE;
    for (i = 1; i < 6; i++)
    {
        if (param2[i] != UNK_02105D64[i])
        {
            r4 = FALSE;
            break;
        }
    }

    if (r4)
    {
        u8 first = param2[0];
        if (first != (u8)FUN_02031190())
        {
            return;
        }

        UNK_021C5A00->unk3D = 2;
    }
}

THUMB_FUNC u32 FUN_02032B68()
{
    return 6;
}

THUMB_FUNC void FUN_02032B6C(u8 param0)
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk3C = param0;
        FUN_0202D1B0(param0);
    }
}

THUMB_FUNC void FUN_02032B84()
{
    FUN_0202EA54();
}

THUMB_FUNC void FUN_02032B8C()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, 0);
        if (FUN_0202F950(1, 1, 0x20) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032B84, 0);
        }
    }
}

THUMB_FUNC void FUN_02032BD0(struct SaveBlock2 *sav2)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7000);
        FUN_02031734(sav2, 0xe);
        UNK_021C5A00->unk40 = 0;
        FUN_02031D20(FUN_02032B8C, 0);
    }
}

THUMB_FUNC void FUN_02032C0C()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_02031D20(FUN_02032440, 5);
    }
}

THUMB_FUNC u32 FUN_02032C28()
{
    struct UnkStruct_02031734_const2 st0 = UNK_020EEC48;

    u32 fun = (u32)UNK_021C5A00->unk24;
    if (UNK_021C5A00 == NULL)
    {
        return 0;
    }

    u32 i = 0;
    while (st0.unk00[i] != 0)
    {
        if (st0.unk00[i] == fun)
        {
            return 1;
        }

        i++;
    }

    return 0;
}

THUMB_FUNC void FUN_02032C6C(u32 param0, u32 param1)
{
    switch (param0)
    {
    case 0x333:
        if (param1 != 0xf)
        {
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

THUMB_FUNC void FUN_02032CF4()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, 0);
        FUN_0202D308(FUN_02032C6C);
        if (FUN_0202F950(1, 1, 0x20) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032B84, 0);
        }
    }
}

THUMB_FUNC void FUN_02032D44(struct SaveBlock2 *sav2)
{
    if (FUN_02030F40() == 0)
    {
        FUN_02016828(3, 0xf, 0x7000);
        FUN_02031734(sav2, 0x11);
        UNK_021C5A00->unk40 = 0;
        FUN_02031D20(FUN_02032CF4, 0);
    }
}

THUMB_FUNC void FUN_02032D80()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_02031D20(FUN_02032440, 5);
    }
}

THUMB_FUNC u8 FUN_02032D9C()
{
    return UNK_021C5A00->unk49;
}

THUMB_FUNC BOOL FUN_02032DAC()
{
    FUN_02031468();

    if (UNK_021C5A00 == NULL)
    {
        return TRUE;
    }

    if ((u8)(UNK_021C5A00->unk3F + 0xe8) <= 1)
    {
        MOD04_021D83C0();
        return TRUE;
    };

    if (FUN_02033590() != 0)
    {
        FUN_02031D20(FUN_0203318C, 0);
    }
    else
    {
        FUN_02031D20(FUN_02032178, 0);
    }

    return FALSE;
}

THUMB_FUNC void FUN_02032E00()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, 0);
        if (FUN_0202F918(1, 1, 0x200, 1) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032218, 0);
        }
    }
}

THUMB_FUNC void FUN_02032E48()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_0202E29C(UNK_021C5A00->unk2C);
        FUN_0202DB14(UNK_021C5A00->unk28, 0);
        if (FUN_0202F950(1, 1, 0x200) != 0)
        {
            FUN_0202FA10();
            FUN_02031D20(FUN_02032290, 0);
        }
    }
}

THUMB_FUNC void FUN_02032E8C()
{
}

THUMB_FUNC void FUN_02032E90()
{
    if (MOD04_021D7F8C() < 0)
    {
        FUN_02031D20(FUN_02032E8C, 0);
    }
}

THUMB_FUNC void FUN_02032EA8()
{
}

THUMB_FUNC void FUN_02032EAC()
{
}

THUMB_FUNC void FUN_02032EB0()
{
    FUN_020313A0(1);

    s32 res = MOD04_021D7F8C();
    if (res >= 0xa)
    {
        FUN_02031D20(FUN_02032EAC, 0);
        return;
    }

    if (res < 0)
    {
        FUN_02031D20(FUN_02032E8C, 0);
        return;
    }

    if (res == 1)
    {
        FUN_02031D20(FUN_02032E90, 0);
        return;
    }

    if (res == 2)
    {
        if (UNK_021C5A00->unk44 != 0)
        {
            FUN_02031D20(FUN_02032E8C, 0);
            return;
        }
        FUN_02031D20(FUN_02032EA8, 0);
        return;
    }
}

THUMB_FUNC void FUN_02032F20(u32 param0)
{
    if (param0 + 2 > 1)
    {
        param0 = -param0;
    }

    UNK_021C5A00->unk34 = param0;
}

THUMB_FUNC void FUN_02032F34()
{
    s32 res = MOD04_021D7800(0);
    if (res >= 0xa)
    {
        FUN_02031D20(FUN_02032EAC, 0);
        return;
    }

    if (res < 0)
    {
        FUN_02032F20((u32)res);
        FUN_02031D20(FUN_02032E8C, 0);
        return;
    }

    if (res == 1)
    {
        FUN_02031D20(FUN_02032EB0, 0);
        return;
    }

    if (res == 2)
    {
        FUN_02031D20(FUN_02032EA8, 0);
        return;
    }

    if (res == 3)
    {
        FUN_02031D20(FUN_02032EAC, 0);
        return;
    }
}

THUMB_FUNC void FUN_02032F98()
{
    s32 res = MOD04_021D7800(1);
    if (res < 0)
    {
        FUN_02032F20((u32)res);
        FUN_02031D20(FUN_02032E8C, 0);
        return;
    }

    if (MOD04_021D8494(UNK_021C5A00->unk42) != 0)
    {
        FUN_0202FC60();
        FUN_02031D20(FUN_02032F34, 0);
    }
}

THUMB_FUNC u32 FUN_02032FDC(u8 param0)
{
    MOD04_021D77C4(FUN_020303BC, FUN_02030238);
    UNK_021C5A00->unk42 = param0;
    FUN_02031D20(FUN_02032F98, 0);

    return 1;
}

THUMB_FUNC u32 FUN_0203300C()
{
    if (UNK_021C5A00->unk24 == FUN_02032F34)
    {
        return 0;
    }

    if (UNK_021C5A00->unk24 == FUN_02032EB0)
    {
        return 1;
    }

    if (UNK_021C5A00->unk24 == FUN_02032E90)
    {
        return 3;
    }

    if (UNK_021C5A00->unk24 == FUN_02032EA8)
    {
        return 4;
    }

    if (UNK_021C5A00->unk24 == FUN_02032EAC)
    {
        return 5;
    }

    return 2;
}

THUMB_FUNC void FUN_02033060()
{
    MOD04_021D77C4(FUN_020303BC, FUN_02030238);
    if (MOD04_021D8494(-1) != 0)
    {
        UNK_021C5A00->unk4D = 0;
        FUN_0202FC60();
        FUN_02031D20(FUN_02032F34, 0);
    }
}

THUMB_FUNC void FUN_020330A0()
{
    FUN_020313A0(0);
    if (MOD04_021D82BC(UNK_021C5A00->unk41) != 0)
    {
        MOD04_021D836C();
        FUN_02031D20(FUN_02033060, 0);
        return;
    }

    if (MOD04_021D7F8C() < 0)
    {
        FUN_02031D20(FUN_02032E8C, 0);
    }
}

THUMB_FUNC void FUN_020330E4()
{
    if (FUN_02031190() == 0)
    {
        UNK_021C5A00->unk41 = 0;
        FUN_02031D20(FUN_020330A0, 0);
    }
    else
    {
        UNK_021C5A00->unk41 = 1;
        FUN_02031D20(FUN_020330A0, 0);
    }

    UNK_021C5A00->unk4D = 1;
}

THUMB_FUNC u8 FUN_02033128()
{
    return UNK_021C5A00->unk4D;
}

THUMB_FUNC u32 FUN_02033138()
{
    if (UNK_021C5A00->unk24 == FUN_02033060)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC u32 FUN_02033154()
{
    if (UNK_021C5A00->unk24 == FUN_02032F34)
    {
        return 1;
    }

    if (UNK_021C5A00->unk24 == FUN_02033060)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC u32 FUN_02033180()
{
    return UNK_021C5A00->unk34;
}

THUMB_FUNC void FUN_0203318C()
{
    FUN_020313A0(0);
    if (MOD04_021D82BC(0) != 0)
    {
        MOD04_021D836C();
        FUN_02031D20(FUN_02032440, 0);
    }

    if (MOD04_021D7F8C() < 0)
    {
        FUN_02031D20(FUN_02032E8C, 0);
    }
}

THUMB_FUNC void FUN_020331C4()
{
    if (UNK_021C5A00 != NULL)
    {
        FUN_020166B8(1);
        FUN_02031D20(FUN_02032440, 5);
    }
}

THUMB_FUNC void FUN_020331E8()
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk41 = 0;
        FUN_02031D20(FUN_020330A0, 0);
    }
}

THUMB_FUNC void FUN_02033208()
{
    if (UNK_021C5A00 != NULL)
    {
        if (FUN_02031190() == 0)
        {
            UNK_021C5A00->unk41 = 0;
        }
        else
        {
            UNK_021C5A00->unk41 = 1;
        }

        FUN_02031D20(FUN_020330A0, 0);
    }
}

THUMB_FUNC void FUN_0203323C()
{
    u8 res = (u8)FUN_02031190();
    FUN_020311D0(0x15, &res);
}

THUMB_FUNC u32 FUN_02033250()
{
    if (UNK_021C5A00 != NULL)
    {
        if (UNK_021C5A00->unk24 == FUN_02032E8C)
        {
            return 1;
        }

        if (UNK_021C5A00->unk24 == FUN_02032E90 && UNK_021C5A00->unk44 != 0)
        {
            return 1;
        }
    }

    return 0;
}

THUMB_FUNC void FUN_02033288(struct SaveBlock2 *sav2)
{
    if (UNK_021C5A00 == NULL)
    {
        FUN_02016828(3, 0xf, 0x100);
        UNK_021C5A00 =
            (struct UnkStruct_02031734 *)AllocFromHeap(0xf, sizeof(struct UnkStruct_02031734));
        MI_CpuFill8(UNK_021C5A00, 0, sizeof(struct UnkStruct_02031734));

        UNK_021C5A00->unk3F = 0x18;
        UNK_021C5A00->unk46 = 1;
        UNK_021C5A00->unk28 = sav2;
        FUN_020334E8(0, 1);
        FUN_020166A8(1);
    }
}

THUMB_FUNC void FUN_020332DC()
{
    if (UNK_021C5A00 != 0)
    {
        FUN_020166B8(1);
        FUN_020334E8(0, 0);
        FreeToHeap(UNK_021C5A00);
        UNK_021C5A00 = NULL;
        FUN_020168D0(0xf);
    }
}

THUMB_FUNC void FUN_02033310(struct SaveBlock2 *sav2)
{
    if (UNK_021C5A00 == NULL)
    {
        FUN_02016828(3, 0xf, 0x100);
        UNK_021C5A00 =
            (struct UnkStruct_02031734 *)AllocFromHeap(0xf, sizeof(struct UnkStruct_02031734));
        MI_CpuFill8(UNK_021C5A00, 0, sizeof(struct UnkStruct_02031734));
        UNK_021C5A00->unk3F = 0x19;
        UNK_021C5A00->unk46 = 1;
        UNK_021C5A00->unk28 = sav2;
        FUN_020334E8(0, 1);
        FUN_020166A8(1);
    }
}

THUMB_FUNC void FUN_02033364()
{
    if (UNK_021C5A00 != 0)
    {
        FUN_020166B8(1);
        FUN_020334E8(0, 0);
        FreeToHeap(UNK_021C5A00);
        UNK_021C5A00 = NULL;
        FUN_020168D0(0xf);
    }
}

THUMB_FUNC u32 FUN_02033398()
{
    u32 st4;
    u32 st0;
    if (UNK_021C5A00 == NULL)
    {
        return 0;
    }

    if (UNK_021C5A00->unk3F == 0x18)
    {
        if (MOD04_021DD718(&st4, &st0) != 0)
        {
            MOD04_021DD6F0();
            return 1;
        }
    }
    else if (UNK_021C5A00->unk3F == 0x19)
    {
        if (MOD04_021DD718(&st4, &st0) != 0 && st0 == 7)
        {
            return 1;
        }
    }

    return 0;
}

THUMB_FUNC void FUN_020333F0()
{
    s32 res = MOD04_021D76AC();
    if (res < 0)
    {
        FUN_02032F20((u32)res);
        FUN_02031D20(FUN_02032E8C, 0);
        return;
    }
    else if (res > 0)
    {
        FUN_02031D20(FUN_02033060, 0);
    }
}

THUMB_FUNC void FUN_0203341C()
{
    if (FUN_0202E4C8() != 0)
    {
        FUN_02016828(3, 0x31, 0x31000);
        if (FUN_0202F918(1, 1, 0x200, 1) != 0)
        {
            MOD05_021D74E0(UNK_021C5A00->unk28, 0x31);
            MOD04_021D83A8(FUN_020335D0);
            FUN_0202FA10();
            FUN_02031D20(FUN_020333F0, 0);
        }
    }
}

THUMB_FUNC void *FUN_0203346C(struct SaveBlock2 *sav2, u32 param1)
{
    Sav2_PlayerData_GetProfileAddr(sav2);
    if (FUN_02030F40() != 0)
    {
        return 0;
    }

    FUN_020166A8(1);
    FUN_02016828(3, 0xf, 0x7080);
    FUN_02031734(sav2, 0x17);
    UNK_021C5A00->unk00 = AllocFromHeap(0xf, param1);
    MI_CpuFill8(UNK_021C5A00->unk00, 0, param1);

    UNK_021C5A00->unk40 = 0;
    UNK_021C5A00->unk28 = sav2;
    FUN_02031D20(FUN_0203341C, 0);

    return UNK_021C5A00->unk00;
}

THUMB_FUNC void *FUN_020334DC()
{
    return UNK_021C5A00->unk00;
}

THUMB_FUNC void FUN_020334E8(u8 param0, u8 param1)
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk44 = param0;
        UNK_021C5A00->unk45 = param1;
    }

    FUN_0202EE84(param0);
    FUN_0202EEB0(param0);
}

THUMB_FUNC u8 FUN_02033510()
{
    if (UNK_021C5A00 != NULL)
    {
        if (UNK_021C5A00->unk4E != 0)
        {
            return 1;
        }

        return UNK_021C5A00->unk45;
    }

    return 0;
}

THUMB_FUNC s32 FUN_02033534()
{
    if (UNK_021C5A00 != NULL)
    {
        return UNK_021C5A00->unk3F;
    }

    return 1;
}

THUMB_FUNC u8 FUN_0203354C()
{
    if (UNK_021C5A00 != NULL)
    {
        return UNK_021C5A00->unk40;
    }

    return 0;
}

THUMB_FUNC void FUN_02033564(void *src)
{
    MI_CpuCopy8(src, UNK_021C5A00->unk04, 0x6);
}

THUMB_FUNC void FUN_02033578(void *dst)
{
    MI_CpuCopy8(UNK_021C5A00->unk04, dst, 0x6);
}

THUMB_FUNC u32 FUN_02033590()
{
    if (FUN_02033534() >= 0x13)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC void FUN_020335A4(u8 param0)
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk47 = param0;
    }
}

THUMB_FUNC u8 FUN_020335B8()
{
    if (UNK_021C5A00 != NULL)
    {
        return UNK_021C5A00->unk47;
    }

    return 0;
}

THUMB_FUNC void FUN_020335D0(s32 param0)
{
    FUN_02033F70(0, 1, param0);
    while (TRUE)
    {
    }
}

THUMB_FUNC void FUN_020335E0()
{
    FUN_02033F70(0, 4, 0);
    while (TRUE)
    {
    }
}

THUMB_FUNC void FUN_020335F0()
{
}

THUMB_FUNC void FUN_020335F4()
{
    if (FUN_02033510() != 0)
    {
        if (FUN_020311F0() == 0 && FUN_02033250() == 0 && FUN_02033398() == 0)
        {
            if (UNK_021C5A00->unk4E == 0)
            {
                return;
            }
        }

        if (FUN_020335B8() != 0)
        {
            return;
        }

        FUN_0200541C();
        FUN_0202287C(UNK_021C5A00->unk28);
        gMain.unk64 = 1;
        if (UNK_021C5A00->unk4E == 3)
        {
            FUN_020335A4(3);
            return;
        }

        if (UNK_021C5A00->unk3F == 0x19 || UNK_021C5A00->unk3F == 0xf)
        {
            FUN_020335A4(2);
        }
        else
        {
            FUN_020335A4(1);
        }
    }
}

THUMB_FUNC BOOL FUN_02033678()
{
    if (FUN_0202EDD8() != 0 || !FUN_02031810())
    {
        return TRUE;
    }

    if (FUN_0202E344() == 0)
    {
        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC u32 FUN_020336A0(u8 param0)
{
    if (UNK_021C5A00 != NULL)
    {
        UNK_021C5A00->unk4E = param0;
        FUN_02031468();
        return 1;
    }

    return 0;
}
