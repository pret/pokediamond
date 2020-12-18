#include "global.h"
#include "sound.h"
#include "SPI_mic.h"
#include "SPI_pm.h"

#pragma thumb on

static struct SoundData sSoundDataBuffer;
static u32 UNK_02107070[2];

void FUN_02003C40(void);
BOOL FUN_02003D04(void);
void FUN_020040C8(void);
void FUN_02004064(struct SoundData *);
void FUN_02004088(struct SoundData *);
void FUN_020040A4(struct SoundData *);
void FUN_02003CE8(int);
void FUN_020040DC(void);

extern BOOL FUN_020048BC(int);
extern void FUN_02004D60(u32);
extern BOOL FUN_02004D94(void);
extern void FUN_0200521C(int);
extern void FUN_0200538C(int, int, int);
extern BOOL FUN_02005404(void);
extern void FUN_02005CFC(void);

void InitSoundData(void * a0, struct Options * a1)
{
    struct SoundData * sdat = GetSoundDataPointer();
    SDAT_Init();
    FUN_020040C8();
    FUN_02004064(sdat);
    sdat->unk_00090 = FUN_020C2A94(sdat->unk_00094, sizeof(sdat->unk_00094));
    SDAT_Open(&sdat->header, "data/sound/sound_data.sdat", sdat->unk_00090, 0);
    FUN_020C39CC(sdat->unk_00090);
    FUN_02004088(sdat);
    FUN_020040A4(sdat);
    UNK_02107070[1] = 0;
    sdat->unk_BCD4C = a0;
    FUN_02004D60(a1->soundMethod);
}

void DoSoundUpdateFrame(void)
{
    struct SoundData * sdat = GetSoundDataPointer();
    if (!FUN_02003D04())
    {
        if (sdat->unk_BCD00 > 0)
            sdat->unk_BCD00--;
        FUN_02003C40();
    }
    FUN_02005CFC();
    FUN_020C01A0();
}

void FUN_02003C40(void)
{
    struct SoundData * sdat = GetSoundDataPointer();
    switch (UNK_02107070[0])
    {
    case 1:
        FUN_02003CE8(2);
        break;
    case 3:
        if (!FUN_02005404())
            FUN_02003CE8(2);
        break;
    case 4:
        if (!FUN_02005404())
            FUN_02003CE8(2);
        break;
    case 5:
        if (!FUN_02005404() && !FUN_02004D94())
        {
            FUN_020040DC();
            FUN_0200521C(sdat->unk_BCD0E);
        }
        break;
    case 6:
        if (!FUN_02005404() && !FUN_02004D94())
        {
            FUN_020040DC();
            FUN_0200521C(sdat->unk_BCD0E);
            FUN_0200538C(0x7F, (int)sdat->unk_BCD08, 0);
        }
        break;
    }
}

void FUN_02003CE8(int a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    sdat->unk_BCCFC = 0;
    UNK_02107070[0] = (u32)a0;
}

BOOL FUN_02003D04(void)
{
    struct SoundData * sdat = GetSoundDataPointer();
    if (FUN_020048BC(2))
        return TRUE;
    return sdat->unk_BCD12 != 0;
}

struct SoundData * GetSoundDataPointer(void)
{
    return &sSoundDataBuffer;
}

void * FUN_02003D38(u32 a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    switch (a0)
    {
    case 5:
        return &sdat->unk_BCCFE;
    case 0:
        return &sdat->unk_BBCB8;
    case 1:
        return &sdat->unk_BBCBC;
    case 2:
        return &sdat->unk_BBCC0;
    case 3:
        return &sdat->unk_BBCE0;
    case 4:
        return &sdat->unk_BCCE0;
    case 6:
        return &sdat->unk_BCD00;
    case 7:
        return &sdat->unk_BCD04;
    case 8:
        return &sdat->unk_BCD08;
    case 9:
        return &sdat->unk_BCD0C;
    case 10:
        return &sdat->unk_BCD0E;
    case 11:
        return &sdat->unk_BCD10;
    case 12:
        return &sdat->unk_BCD11;
    case 13:
        return &sdat->unk_BCD12;
    case 14:
        return &sdat->unk_BCD14;
    case 15:
        return &sdat->unk_BCD15;
    case 16:
        return &sdat->unk_BCD16;
    case 17:
        return &sdat->unk_BCD17;
    case 18:
        return &sdat->unk_BCD18;
    case 19:
        return &sdat->unk_BCD19;
    case 20:
        return &sdat->unk_BCD1A;
    case 21:
        return &sdat->unk_BCD1B;
    case 22:
        return &sdat->unk_BCD1C[0];
    case 23:
        return &sdat->unk_BCD1C[1];
    case 24:
        return &sdat->unk_BCD1C[2];
    case 25:
        return &sdat->unk_BCD1C[3];
    case 26:
        return &sdat->unk_BCD1C[4];
    case 27:
        return &sdat->unk_BCD1C[5];
    case 28:
        return &sdat->unk_BCD1C[6];
    case 29:
        return &sdat->unk_BCD38;
    case 30:
        return &sdat->unk_BCD39;
    case 31:
        return &sdat->unk_BCD3A;
    case 32:
        return &sdat->unk_BCD3C;
    case 33:
        return &sdat->unk_BCD40;
    case 34:
        return &sdat->unk_BCD48;
    case 35:
        return &sdat->unk_BCD4C;
    case 36:
        return &sdat->unk_BCD50;
    case 37:
        return &sdat->unk_BCD54;
    case 38:
        return &sdat->unk_BCD58;
    case 39:
        return &sdat->unk_BCD5C;
    default:
        GF_ASSERT(0);
        return NULL;
    }
}

int FUN_02003F3C(int * a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    int r4 = FUN_020C290C(sdat->unk_00090);
    GF_ASSERT(r4 != -1);
    if (a0 != NULL)
        *a0 = r4;
    return r4;
}

void FUN_02003F64(int a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    FUN_020C2828(sdat->unk_00090, a0);
}

BOOL FUN_02003F78(u32 * a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return FUN_020C36A8(a0, sdat->unk_00090);
}

BOOL FUN_02003F90(u32 * a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return FUN_020C3674(a0, sdat->unk_00090);
}

BOOL FUN_02003FA8(u32 * a0, u32 * a1)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return FUN_020C35E0(a0, a1, sdat->unk_00090);
}

BOOL FUN_02003FC4(u32 * a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return FUN_020C360C(a0, sdat->unk_00090);
}

BOOL FUN_02003FDC(u32 * a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return FUN_020C3640(a0, sdat->unk_00090);
}

u32 * FUN_02003FF4(int a0)
{
    struct SoundData * sdat = GetSoundDataPointer();
    if (a0 >= 9)
    {
        GF_ASSERT(0);
        a0 = 0;
    }
    return &sdat->unk_BBC94[a0];
}

u32 FUN_02004018(u32 a0)
{
    switch (a0)
    {
    case 1:
        return 0;
    case 0:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    default:
        GF_ASSERT(0);
        return 3;
    }
}

void FUN_02004064(struct SoundData * sdat)
{
    int i;
    memset(sdat, 0, sizeof(*sdat));
    for (i = 0; i < 7; i++)
        sdat->unk_BCD1C[i] = i + 1;
}

void FUN_02004088(struct SoundData * sdat)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        FUN_020C0F80(&sdat->unk_BBC94[i]);
    }
}

void FUN_020040A4(struct SoundData * sdat)
{
    FUN_02003F3C(&sdat->unk_BCD1C[0]);
    FUN_02003F78(NULL);
    FUN_02003F3C(&sdat->unk_BCD1C[1]);
}

void FUN_020040C8(void)
{
    MIC_Init();
    PM_SetAmp(1);
    PM_SetAmpGain(2);
}

void FUN_020040DC(void)
{
    FUN_020C1040(7, 0);
    FUN_02003FF4(7);
    FUN_020C0F68();
}
