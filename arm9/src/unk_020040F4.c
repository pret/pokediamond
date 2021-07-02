#include "global.h"
#include "unk_020040F4.h"
#include "OS_cache.h"
#include "sound.h"
#include "unk_0202F150.h"

u32 UNK_021C3DD8[2];

u8 UNK_021C3DE0[0x7d0];

const u8 UNK_020ECB8C[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };

extern void FUN_02005454();
extern void FUN_0200541C();
extern void FUN_0200521C(int);
extern void FUN_0200538C(u32, u16, u32);
extern void NNS_SndPlayerPause(u32 *, u8);
extern void NNS_SndPlayerMoveVolume(u32 *, u32, u32);
extern void NNS_SndPlayerSetInitialVolume(u32 *, s32);
extern void *NNS_SndArcGetSeqParam(u32);
extern void NNS_SndArcPlayerStartSeqEx(u32 *, u32, s32, s32, u32);
extern BOOL NNS_SndPlayerCountPlayingSeqByPlayerNo(int);
extern u32 NNS_SndPlayerGetSeqNo(u32 *);
extern u32 NNS_SndArcGetBankInfo(u32);
extern u32 MIC_StartAutoSampling(u32);
extern u32 MIC_StopAutoSampling();
extern u32 MIC_DoSamplingAsync(u32 param0, u32 param1, u32 param2, u32 param3);
extern u32 NNS_SndWaveOutAllocChannel(u32);
extern void NNS_SndWaveOutFreeChannel(u32);
extern u32 NNS_SndWaveOutStart(u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);
extern void NNS_SndWaveOutStop(u32);
extern void NNS_SndWaveOutIsPlaying(u32);
extern void NNS_SndWaveOutSetPan(u32, u32);
extern void NNS_SndWaveOutSetSpeed(u32, u32);
extern void NNS_SndWaveOutSetVolume(u32, u32);
extern struct WaveArcInfo *NNS_SndArcGetWaveArcInfo(u32);
extern u32 NNS_SndArcGetFileSize(u32);
extern s32 NNS_SndArcReadFile(u32, u32, u32, u32);
extern BOOL NNS_SndCaptureIsActive();
extern u32 NNS_SndCaptureStartReverb(u32, u32, u32, u32, u32);
extern void NNS_SndCaptureStopReverb(u32);
extern void NNS_SndCaptureSetReverbVolume();
extern u32 NNS_SndCaptureStartEffect(u32, u32, u32, u32, u32, void (*)(), u32);
extern void NNS_SndCaptureStopEffect();
extern void NNS_SndPlayerSetTrackPitch(u32, u32, u32);
extern void NNS_SndPlayerSetTrackPan(u32, u32, u32);
extern void NNS_SndSetMonoFlag(u32 param0);
extern void FUN_02003CE8(u32);
extern void FUN_020053CC(u32, u32);
extern u32 NNS_SndArcGetFileAddress(u32);
extern u32 SND_GetWaveDataAddress(u32, u32);
extern u32 NNS_SndPlayerGetTick(u32);
extern void NNS_SndPlayerSetAllocatableChannel(u32, u32);
extern BOOL FUN_02005404(void);
extern void NNS_SndPlayerSetPlayerVolume(u32, u8);

THUMB_FUNC void FUN_020040F4(u8 param0)
{
    u8 *ptr = FUN_02003D38(5);
    *ptr = param0;
}

THUMB_FUNC u8 FUN_02004104()
{
    u8 *ptr = FUN_02003D38(5);

    return *ptr;
}

THUMB_FUNC void FUN_02004110(u16 param0)
{
    u16 *ptr = FUN_02003D38(9);
    *ptr = param0;

    FUN_02004130(0);
}

THUMB_FUNC u16 FUN_02004124()
{
    u16 *ptr = FUN_02003D38(9);

    return *ptr;
}

THUMB_FUNC void FUN_02004130(u16 param0)
{
    u16 *ptr = FUN_02003D38(10);
    *ptr = param0;
}

THUMB_FUNC u16 FUN_02004140()
{
    u16 *ptr = FUN_02003D38(10);

    return *ptr;
}

THUMB_FUNC void FUN_0200414C(u16 param0)
{
    u16 *ptr = FUN_02003D38(31);
    *ptr = param0;
}

THUMB_FUNC void FUN_0200415C(u8 param0)
{
    u8 *ptr = FUN_02003D38(20);
    u8 *ptr2 = FUN_02003D38(21);

    if (param0 < 51)
    {
        *ptr = param0;
        *ptr2 = 0;
    }
    else
    {
        *ptr2 = param0;
    }
}

THUMB_FUNC BOOL FUN_02004180(s32 param0)
{
    BOOL res;
    switch (param0)
    {
        case 1:
        case 9:
        case 10:
        case 14:
            res = GF_Snd_LoadGroup(1);
            break;
        case 2:
        case 13:
            res = GF_Snd_LoadGroup(2);
            break;
        case 3:
            res = GF_Snd_LoadGroup(13);
            break;
        case 4:
            res = GF_Snd_LoadGroup(1);
            break;
        case 5:
            res = GF_Snd_LoadGroup(2);
            break;
        case 11:
            res = GF_Snd_LoadGroup(1);
            break;
        case 6:
            res = GF_Snd_LoadGroup(11);
            break;
        case 8:
            res = GF_Snd_LoadGroup(1);
            break;
        case 12:
            res = GF_Snd_LoadGroup(14);
            break;
        case 51:
            res = GF_Snd_LoadGroup(3);
            break;
        case 66:
            res = GF_Snd_LoadGroup(6);
            break;
        case 52:
            res = GF_Snd_LoadGroup(5);
            break;
        case 7:
        case 53:
            res = GF_Snd_LoadGroup(9);
            break;
        case 54:
            res = GF_Snd_LoadGroup(10);
            break;
        case 55:
        case 67:
            res = GF_Snd_LoadBank(0x5e5);
            res = GF_Snd_LoadWaveArc(0x5e5);
            break;
        case 56:
            res = GF_Snd_LoadGroup(12);
            break;
        case 57:
            res = GF_Snd_LoadGroup(7);
            break;
        case 58:
            res = GF_Snd_LoadGroup(8);
            break;
        case 59:
            res = GF_Snd_LoadGroup(15);
            break;
        case 60:
            res = GF_Snd_LoadGroup(3);
            break;
        case 61:
            res = GF_Snd_LoadGroup(5);
            break;
        case 62:
            res = GF_Snd_LoadGroup(15);
            break;
        case 63:
            res = GF_Snd_LoadGroup(4);
            break;
        case 64:
            res = GF_Snd_LoadBank(0x5ed);
            res = GF_Snd_LoadWaveArc(0x5ed);
            break;
        case 65:
            res = GF_Snd_LoadBank(0x5ec);
            res = GF_Snd_LoadWaveArc(0x5ec);
            break;
    }

    return res;
}

THUMB_FUNC u32 FUN_0200433C(u8 param0, u32 param1, u32 param2)
{
    u8 *st0 = FUN_02003D38(20);
    u8 *st4 = FUN_02003D38(21);
    u16 *r7 = FUN_02003D38(13);

    if (param0 < 51)
    {
        if (*st0 == param0)
        {
            return 0;
        }
    }
    else
    {
        if (*st4 == param0)
        {
            return 0;
        }
    }

    FUN_0200415C(param0);

    switch (param0)
    {
        case 4:
            FUN_0200516C(0);
            FUN_020044D4(param1, param2);
            *r7 = 0;
            break;
        case 5:
            FUN_02004648(param1, param2);
            break;
        case 11:
            FUN_02004680(param1, param2);
            break;
        case 6:
            FUN_020046A0(param1, param2);
            break;
        case 7:
            FUN_020046C4(param1, param2);
            break;
        case 57:
        case 53:
        case 51:
        case 52:
        case 54:
        case 55:
        case 56:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
            FUN_020046E8(param0);
            break;
        case 1:
            FUN_0200516C(1);
            FUN_02004704(param0, param1, param2);
            break;
        case 14:
            FUN_0200516C(2);
            FUN_02004704(param0, param1, param2);
            break;
        case 2:
            FUN_0200516C(0);
            FUN_02004704(param0, param1, param2);
            break;
        case 3:
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
            FUN_02004704(param0, param1, param2);
            break;
    }

    return 1;
}

THUMB_FUNC void FUN_020044A8(s32 param0)
{
    int *ptr = FUN_02003D38(23);
    GF_Snd_RestoreState(*ptr);

    int *ptr2 = FUN_02003D38(24);
    GF_Snd_SaveState(ptr2);

    FUN_02004180(param0);

    int *ptr3 = FUN_02003D38(25);
    GF_Snd_SaveState(ptr3);
}

THUMB_FUNC void FUN_020044D4(int param0, u32 param1)
{
    u8 *ptr = FUN_02003D38(11);

    FUN_02003D38(23);
    FUN_02003D38(31);
    u32 r4 = FUN_020048EC(FUN_02003FF4(0));

    if (*ptr == 0 && r4 == param0 && FUN_02004140() != 1152)
    {
        return;
    }

    FUN_02004DBC(1);
    FUN_02005454();

    if (r4 != param0)
    {
        FUN_020047C8(1, 0);
        FUN_0200541C();
    }

    if (*ptr == 1)
    {
        GF_Snd_RestoreState(FUN_02004748(2));
        FUN_02004180(4);
        GF_Snd_SaveState((int *)FUN_02003D38(25));

        if (r4 != param0)
        {
            FUN_020047C8(1, 0);
        }
        FUN_02004568(param0, (u16)r4);
        return;
    }

    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_02004568(int seqNo, u16 param1)
{
    u16 *ptr = FUN_02003D38(31);

    u32 r0 = FUN_02004900(*ptr);
    if (r0 != 1001 && r0 != 1003)
    {
        GF_Snd_LoadSeqEx(seqNo, 4);
        GF_ASSERT(FALSE);
    }
    else
    {
        GF_Snd_LoadSeqEx(*ptr, 6);
    }

    GF_Snd_SaveState((int *)FUN_02003D38(26));
    FUN_020047C8(1, 0);
    FUN_0200538C(0x7f, 0x28, 0);
    FUN_02004DBC(0);
}

THUMB_FUNC void FUN_020045C4(u32 param0, u32 param1)
{
    u8 *ptr = FUN_02003D38(18);
    u16 *ptr2 = FUN_02003D38(31);

    if (*ptr != 1 && param1 != 0)
    {
        return;
    }

    GF_Snd_RestoreState(FUN_02004748(1));
    GF_Snd_LoadSeqEx(*ptr2, 2);
    GF_Snd_SaveState((int *)FUN_02003D38(24));

    FUN_02004180(4);
    GF_Snd_SaveState((int *)FUN_02003D38(25));

    u32 r0 = FUN_02004900(*ptr2);
    if (r0 != 1001 && r0 != 1003)
    {
        GF_Snd_LoadSeqEx(param0, 4);
        GF_ASSERT(FALSE);
    }
    else
    {
        GF_Snd_LoadSeqEx(*ptr2, 4);
    }

    GF_Snd_SaveState((int *)FUN_02003D38(26));
}

THUMB_FUNC void FUN_02004648(u32 param0, u32 param1)
{
    FUN_02003D38(23);
    FUN_020051AC();

    GF_Snd_RestoreState(FUN_02004748(2));
    FUN_02004180(5);
    GF_Snd_SaveState((int *)FUN_02003D38(25));
    FUN_02004DBC(1);
    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_02004680(u32 param0, u32 param1)
{
    FUN_02003D38(23);
    FUN_0200541C();
    FUN_02004810();
    FUN_020044A8(4);
    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_020046A0(u32 param0, u32 param1)
{
    FUN_02003D38(23);
    FUN_0200541C();
    FUN_020044A8(6);
    FUN_02004DBC(1);
    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_020046C4(u32 param0, u32 param1)
{
    FUN_02003D38(23);
    FUN_0200541C();
    FUN_020044A8(7);
    FUN_02004DBC(1);
    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_020046E8(u32 param0)
{
    FUN_02004738();
    FUN_02004180(param0);
    GF_Snd_SaveState((int *)FUN_02003D38(27));
}

THUMB_FUNC void FUN_02004704(u32 param0, u32 param1, u32 param2)
{
    FUN_02003D38(23);
    FUN_0200541C();
    FUN_020044A8(param0);
    FUN_0200521C(param1);
}

THUMB_FUNC void FUN_02004724(u32 param0)
{
    GetSoundDataPointer();
    FUN_020051AC();
    FUN_0200521C(param0);
}

THUMB_FUNC void FUN_02004738()
{
    GF_Snd_RestoreState(FUN_02004748(4));
}

THUMB_FUNC int FUN_02004748(s32 param0)
{
    GetSoundDataPointer();

    if (param0 >= 7)
    {
        GF_AssertFail();
        return *(u32 *)FUN_02003D38(26);
    }

    u32 *r5;
    switch (param0)
    {
        case 0:
            r5 = FUN_02003D38(22);
            break;
        case 1:
            r5 = FUN_02003D38(23);
            break;
        case 2:
            r5 = FUN_02003D38(24);
            break;
        case 3:
            r5 = FUN_02003D38(25);
            break;
        case 4:
            r5 = FUN_02003D38(26);
            break;
        case 5:
            r5 = FUN_02003D38(27);
            break;
        case 6:
            r5 = FUN_02003D38(28);
            break;
    }

    return *r5;
}

THUMB_FUNC void FUN_020047C8(u8 param0, u8 param1)
{
    u8 *ptr;
    u32 r4;
    if (param0 == 1)
    {
        ptr = FUN_02003D38(11);
        r4 = 0;
    }
    else
    {
        if (param0 != 7)
        {
            return;
        }

        ptr = FUN_02003D38(12);
        r4 = 7;
    }

    if (param1 == 0)
    {
        FUN_02004110(FUN_020048EC(FUN_02003FF4(r4)));
    }

    NNS_SndPlayerPause(FUN_02003FF4(r4), param1);
    *ptr = param1;
}

THUMB_FUNC void FUN_02004810()
{
    u8 *ptr = FUN_02003D38(11);
    u8 *ptr2 = FUN_02003D38(12);
    *ptr = 0;
    *ptr2 = 0;
}

THUMB_FUNC void FUN_02004828(u32 param0, u32 param1, u32 param2)
{
    NNS_SndPlayerMoveVolume(FUN_02003FF4(param0), param1, param2);
}

THUMB_FUNC void FUN_0200483C(u32 param0, s32 param1)
{
    if (param1 < 0)
    {
        param1 = 0;
    }

    if (param1 > 127)
    {
        param1 = 127;
    }

    NNS_SndPlayerSetInitialVolume(FUN_02003FF4(param0), param1);
}

THUMB_FUNC void FUN_02004858(u32 param0, u32 param1)
{
    u8 *ret = NNS_SndArcGetSeqParam(param0);
    u8 r4;
    if (param1 == 1 || param1 == 8)
    {
        r4 = 127;
    }
    else
    {
        if (ret == NULL)
        {
            return;
        }

        r4 = ret[2];
    }

    if (FUN_020313EC() == 1)
    {
        FUN_0200483C(param1, r4 / 5);
    }
}

THUMB_FUNC void FUN_0200488C(u16 param0, u16 param1)
{
    FUN_0200483C(FUN_02004018(FUN_020048D0(param0)), param1);
}

THUMB_FUNC void FUN_020048A0(int param0, u32 param1, u32 param2)
{
    NNS_SndArcPlayerStartSeqEx(FUN_02003FF4(param0), param1, -1, -1, param2);
}

THUMB_FUNC BOOL FUN_020048BC(int param0)
{
    GF_ASSERT(param0 >= 0);

    return NNS_SndPlayerCountPlayingSeqByPlayerNo(param0);
}

THUMB_FUNC u8 FUN_020048D0(u16 param0)
{
    if (param0 == 0)
    {
        return 0xff;
    }

    u8 *ptr = NNS_SndArcGetSeqParam(param0);
    if (ptr == NULL)
    {
        return 0xff;
    }

    return ptr[5];
}

THUMB_FUNC u32 FUN_020048EC(u32 *param0)
{
    return NNS_SndPlayerGetSeqNo(param0);
}

THUMB_FUNC u32 FUN_020048F4(u16 param0)
{
    NNS_SndArcGetBankInfo(FUN_02004900(param0));
}

THUMB_FUNC u16 FUN_02004900(u16 param0)
{
    u16 *ptr = NNS_SndArcGetSeqParam(param0);
    if (ptr == NULL)
    {
        return 0;
    }

    return *ptr;
}

THUMB_FUNC u32 FUN_02004914(u32 param0)
{
    return MIC_StartAutoSampling(param0);
}

THUMB_FUNC u32 FUN_0200491C(u32 param0)
{
    GetSoundDataPointer();
    return MIC_StopAutoSampling();
}

THUMB_FUNC u32 FUN_02004928(u32 param0, u32 param1, u32 param2, u32 param3)
{
    return MIC_DoSamplingAsync(param0, param1, param2, param3);
}

THUMB_FUNC void *FUN_02004930(u32 param0)
{
    GetSoundDataPointer();
    u8 *ptr = FUN_02003D38(15);
    u8 *ptr2 = FUN_02003D38(16);
    GF_ASSERT(param0 == 14 || param0 == 15);
    GF_ASSERT(param0 != 14 || *ptr != 0);
    GF_ASSERT(param0 != 15 || *ptr2 != 0);

    if (param0 == 14)
    {
        return FUN_02003D38(0);
    }

    return FUN_02003D38(1);
}

THUMB_FUNC u32 FUN_02004984(u32 param0)
{
    GetSoundDataPointer();
    u8 *ptr = FUN_02003D38(15);
    u8 *ptr2 = FUN_02003D38(16);
    GF_ASSERT(param0 == 14 || param0 == 15);

    if (param0 == 14)
    {
        if (*ptr == 0)
        {
            u32 *r4 = FUN_02003D38(0);
            *r4 = NNS_SndWaveOutAllocChannel(param0);
            if (*r4 == 0)
            {
                return 0;
            }
            *ptr = 1;
        }
        else
        {
            GF_AssertFail();
        }
    }
    else
    {
        if (*ptr2 == 0)
        {
            u32 *r6 = FUN_02003D38(1);
            *r6 = NNS_SndWaveOutAllocChannel(param0);
            if (*r6 == 0)
            {
                return 0;
            }

            *ptr2 = 1;
        }
        else
        {
            GF_AssertFail();
        }
    }

    return 1;
}

THUMB_FUNC void FUN_02004A04(u32 param0)
{
    GetSoundDataPointer();
    u8 *ptr = FUN_02003D38(15);
    u8 *ptr2 = FUN_02003D38(16);
    if (param0 != 14 && param0 != 15)
    {
        GF_AssertFail();
        return;
    }

    if (param0 == 14)
    {
        if (*ptr == 1)
        {
            NNS_SndWaveOutFreeChannel(*(u32 *)FUN_02004930(param0));
            *ptr = 0;
            return;
        }
        else
        {
            GF_AssertFail();
            return;
        }
    }

    if (*ptr2 == 1)
    {
        NNS_SndWaveOutFreeChannel(*(u32 *)FUN_02004930(param0));
        *ptr2 = 0;
        return;
    }
    else
    {
        GF_AssertFail();
    }
}

THUMB_FUNC u32 FUN_02004A6C(u32 *param0, u32 param1)
{
    u32 res = NNS_SndWaveOutStart(*(u32 *)param0[0],
        param0[1],
        param0[2],
        param0[3],
        param0[4],
        param0[5],
        param0[6],
        param0[7],
        param0[8],
        param0[9]);
    if (res == 0)
    {
        FUN_02004A04(param1);
    }

    return res;
}

THUMB_FUNC void FUN_02004AAC(u32 param0)
{
    NNS_SndWaveOutStop(*(u32 *)FUN_02004930(param0));
}

THUMB_FUNC void FUN_02004ABC(u32 param0)
{
    NNS_SndWaveOutIsPlaying(*(u32 *)FUN_02004930(param0));
}

THUMB_FUNC void FUN_02004ACC(u32 param0, u32 param1)
{
    if (param1 > 127)
    {
        param1 = 127;
    }

    NNS_SndWaveOutSetPan(*(u32 *)FUN_02004930(param0), param1);
}

THUMB_FUNC void FUN_02004AE4(u32 param0, u32 param1)
{
    NNS_SndWaveOutSetSpeed(*(u32 *)FUN_02004930(param0), param1);
}

THUMB_FUNC void FUN_02004AF8(u32 param0, s32 param1)
{
    if (FUN_020313EC() == 1)
    {
        NNS_SndWaveOutSetVolume(*(u32 *)FUN_02004930(param0), param1 / 5);
        return;
    }

    NNS_SndWaveOutSetVolume(*(u32 *)FUN_02004930(param0), param1);
}

struct WaveArcInfo
{
    u32 unk00 : 24;
};

THUMB_FUNC u32 FUN_02004B30(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    GetSoundDataPointer();

    u32 *r4 = FUN_02003D38(33);
    GF_ASSERT(param3 == 14 || param3 == 15);

    struct WaveArcInfo *r7 = NNS_SndArcGetWaveArcInfo(param0);
    if (r7 == 0)
    {
        GF_AssertFail();
        return 0;
    }

    u32 r6 = NNS_SndArcGetFileSize(r7->unk00);
    if (r6 == 0)
    {
        GF_AssertFail();
        return 0;
    }

    if (param3 == 14)
    {
        void *ptr = AllocFromHeap(param4, r6);
        *r4 = ptr;
        if (ptr == NULL)
        {
            GF_AssertFail();
            return 0;
        }

        memset(ptr, 0, r6);
        if (NNS_SndArcReadFile(r7->unk00, *r4, r6, 0) == -1)
        {
            GF_AssertFail();
            return 0;
        }

        FUN_02004C1C(*r4, r6);
    }

    void *res = FUN_02004930(param3);

    u32 st8[10];

    st8[1] = 0;
    st8[0] = res;
    st8[2] = *r4;
    st8[3] = 0;
    st8[6] = 0x3443;
    st8[4] = 0;
    st8[7] = param1;
    st8[8] = 0x6000;
    st8[9] = param2;
    st8[5] = r6;

    u32 ret = FUN_02004A6C(st8, param3);
    FUN_02004AF8(param3, param1);
    u8 *r0 = FUN_02003D38(14);
    *r0 = 1;

    return ret;
}

THUMB_FUNC void FUN_02004C1C(u8 *param0, u32 param1)
{
    for (u32 r5 = 0; r5 < param1 / 2; r5++)
    {
        u8 r4 = param0[r5];
        param0[r5] = param0[param1 - 1 - r5];
        param0[param1 - 1 - r5] = r4;
    }
}

THUMB_FUNC void FUN_02004C3C(u32 param0)
{
    GetSoundDataPointer();
    u8 *ptr = FUN_02003D38(14);
    u32 *ptr2 = FUN_02003D38(33);

    GF_ASSERT(param0 == 14 || param0 == 15);

    FUN_02004AAC(param0);

    if (*ptr == 1)
    {
        *ptr = 0;
        FreeToHeap(*ptr2);
    }
}

THUMB_FUNC BOOL FUN_02004C78()
{
    return NNS_SndCaptureIsActive();
}

THUMB_FUNC u32 FUN_02004C80(u32 param0)
{
    GetSoundDataPointer();

    return NNS_SndCaptureStartReverb(FUN_02003D38(3), 0x1000, 0, 0x3E80, param0);
}

THUMB_FUNC void FUN_02004CA4(u32 param0)
{
    NNS_SndCaptureStopReverb(param0);
}

THUMB_FUNC void FUN_02004CAC()
{
    NNS_SndCaptureSetReverbVolume();
}

THUMB_FUNC void FUN_02004CB4()
{
    GetSoundDataPointer();

    MI_CpuFill8(FUN_02003D38(4), 0, 0x1c);

    void *r4 = FUN_02003D38(3);
    void *st8 = FUN_02003D38(4);

    NNS_SndCaptureStartEffect(r4, 0x1000, 0, 0x55F0, 2, FUN_02005068, st8);
}

THUMB_FUNC void FUN_02004CFC()
{
    NNS_SndCaptureStopEffect();
}

THUMB_FUNC void FUN_02004D04(s32 param0)
{
    u8 *ptr = FUN_02003D38(19);

    if (param0 > 8)
    {
        param0 = 8;
    }
    else if (param0 < 0)
    {
        param0 = 0;
    }

    *ptr = param0;
}

THUMB_FUNC void FUN_02004D20(u32 param0, u32 param1, u32 param2)
{
    NNS_SndPlayerSetTrackPitch(FUN_02003FF4(param0), param1, param2);
}

THUMB_FUNC void FUN_02004D34(u16 param0, u32 param1, u32 param2)
{
    FUN_02004D20(FUN_02004018(FUN_020048D0(param0)), param1, param2);
}

THUMB_FUNC void FUN_02004D4C(u32 param0, u32 param1, u32 param2)
{
    NNS_SndPlayerSetTrackPan(FUN_02003FF4(param0), param1, param2);
}

THUMB_FUNC void FUN_02004D60(u32 param0)
{
    NNS_SndSetMonoFlag(param0);
    UNK_021C3DD8[0] = param0;
}

THUMB_FUNC void FUN_02004D74(u32 param0)
{
    *(u32 *)FUN_02003D38(6) = param0;
}

THUMB_FUNC void FUN_02004D84(u32 param0)
{
    *(u32 *)FUN_02003D38(7) = param0;
}

THUMB_FUNC u16 FUN_02004D94()
{
    u16 *ptr = FUN_02003D38(7);

    if (*ptr == 0)
    {
        *ptr = 0;
        return 0;
    }

    return --(*ptr);
}

THUMB_FUNC u8 *FUN_02004DB4()
{
    return UNK_021C3DE0;
}

THUMB_FUNC void FUN_02004DBC(u8 param0)
{
    *(u8 *)FUN_02003D38(18) = param0;
}

THUMB_FUNC u32 FUN_02004DCC(u32 param0, u16 param1, u32 param2, u32 param3, u8 param4, u32 param5)
{
    u8 *ptr = FUN_02003D38(21);

    FUN_02004E44(param0, param1, param2, param3, param4, param5);

    *ptr = 0;
    FUN_02003CE8(5);
    return 1;
}

THUMB_FUNC u32 FUN_02004E08(
    u32 param0, u16 param1, u32 param2, u32 param3, u32 param35, u8 param4, u32 param5)
{
    u32 *ptr = FUN_02003D38(8);

    FUN_02004E44(param0, param1, param2, param3, param4, param5);

    *ptr = param35;
    FUN_02003CE8(6);
    return 1;
}

THUMB_FUNC void FUN_02004E44(u32 param0, u16 param1, u32 param2, u32 param3, u8 param4, u32 param5)
{
    u32 *ptr = FUN_02003D38(2);

    FUN_020053CC(0, param2);
    FUN_02004110(0);
    FUN_02004130(param1);
    FUN_02004D84(param3);
    *ptr = FUN_020048F4(param1);

    FUN_02004DBC(param4);
}

THUMB_FUNC u32 FUN_02004E80(u32 param0)
{
    if (param0 == 0)
    {
        return 0;
    }

    return param0 + 12;
}

THUMB_FUNC u32 FUN_02004E8C(u32 *param0)
{
    if (param0 == NULL)
    {
        return 0;
    }

    return param0[2];
}

THUMB_FUNC u32 FUN_02004E98(s32 param0)
{
    GF_Snd_RestoreState(FUN_02004748(5));

    u16 r4 = (u16)param0;

    if (r4 != 0x1B9 && (param0 > 0x1ef || param0 == 0))
    {
        r4 = 1;
    }

    GF_Snd_LoadWaveArc(r4);
    return FUN_02004ED0(r4);
}

THUMB_FUNC u32 FUN_02004ED0(s32 param0)
{
    u32 *ptr = FUN_02003D38(32);

    u16 r4 = (u16)param0;

    if (r4 != 0x1B9 && (param0 > 0x1ef || param0 == 0))
    {
        r4 = 1;
    }

    struct WaveArcInfo *info = NNS_SndArcGetWaveArcInfo(r4);
    if (info == NULL)
    {
        GF_AssertFail();
        return 0;
    }

    u32 address = NNS_SndArcGetFileAddress(info->unk00);
    if (address == 0)
    {
        GF_AssertFail();
        return 0;
    }

    *ptr = SND_GetWaveDataAddress(address, 0);
    return *ptr;
}

THUMB_FUNC u32 FUN_02004F28(u32 param0, u32 *param1, s32 param2)
{
    u32 r4 = FUN_02004F64(1);
    u32 r5 = param1[2];

    s32 r1 = (param2 / (3 * 0x100)) << 1;
    if (r1 < 0)
    {
        r1 = 32 / r1;
        r1 = -r1;
    }
    else if (r1 == 0)
    {
        r1 = 32;
    }
    else
    {
        r1 = 32 * r1;
    }

    u32 r0 = r4 * r1;
    if (r0 >= r5)
    {
        r0 = 0;
    }

    return r0;
}

THUMB_FUNC u32 FUN_02004F64(int param0)
{
    return NNS_SndPlayerGetTick(FUN_02003FF4(param0));
}

THUMB_FUNC void FUN_02004F70(u8 *param0, u8 *param1, int param2, u32 param3)
{
    int r0, r1;
    int i, j;
    u32 r12 = FUN_02004F28(1, param0, param3);
    r1 = r12 - 100;
    if (r1 < 0)
    {
        r1 = 0;
    }

    int r3 = 0;
    int r7 = 0;
    s8 r5;
    if ((param0 + 12)[r1] < 0x80)
    {
        r5 = 1;
    }
    else
    {
        r5 = -1;
    }
    r5 = (s8)(s32)r5;

    for (i = r1; i < r12; i += 2)
    {
        r0 = 0;
        if (r5 > 0)
        {
            if ((param0 + 12)[i] > 0x80)
            {
                r0 = 1;
            }
            else
            {
                r3++;
            }
        }
        else
        {
            if ((param0 + 12)[i] < 0x80)
            {
                r0 = 1;
            }
            else
            {
                r3++;
            }
        }

        if (r0 == 1)
        {
            for (j = 0; j < 9; j++)
            {
                if (r3 < UNK_020ECB8C[j])
                {
                    r7 = j;
                    break;
                }
            }

            if (r7 >= param2)
            {
                r7 = param2 - 1;
            }

            if (r3 != 0)
            {
                param1[param2 - 1 - r7]++;
            }

            r3 = 0;
            r0 = 0;
            if ((param0 + 12)[i] < 0x80)
            {
                r5 = 1;
            }
            else
            {
                r5 = -1;
            }
            r5 = (s8)(s32)r5;
        }
    }

    for (i = 0; i < param2; i++)
    {
        if (param1[i] >= 10)
        {
            param1[i] = 9;
        }
    }

    for (i = 0; i < param2 - 1; i++)
    {
        if (param1[i] == 0 && param1[i + 1] != 0)
        {
            param1[i] = param1[i + 1] / 2;
            return;
        }
    }
}

THUMB_FUNC void FUN_02005068(s16 *param0, s16 *param1, u32 param2, u32 param3, void *param4)
{
    s16 st10[8][2];
    s16(*st0)[2] = param4;
    u8 *r7 = FUN_02003D38(19);

    int r0;
    int i, j;

    if (param3 != 1)
    {
        param2 /= 2;
    }

    if (*r7 == 0)
    {
        return;
    }

    for (i = 0; i < *r7; i++)
    {
        st10[i][0] = param0[param2 - (*r7) + i];
        st10[i][1] = param1[param2 - (*r7) + i];
    }

    for (i = param2 - 1; i >= *r7 - 1; i--)
    {
        r0 = 0;
        for (j = 0; j < *r7; j++)
        {
            r0 += param0[i - j];
        }

        param0[i] = r0 / (*r7);

        r0 = 0;
        for (j = 0; j < *r7; j++)
        {
            r0 += param1[i - j];
        }

        param1[i] = r0 / (*r7);
    }

    for (i = 0; i < *r7; i++)
    {
        st0[i][0] = st10[i][0];
        st0[i][1] = st10[i][1];
    }

    DC_FlushRange(param0, param2);
    DC_FlushRange(param1, param2);
}

THUMB_FUNC void FUN_02005160(u32 param0)
{
    NNS_SndPlayerSetAllocatableChannel(7, param0);
}

THUMB_FUNC void FUN_0200516C(u32 param0)
{
    if (param0 == 0)
    {
        FUN_02005160(0x7ff);
        FUN_02004CA4(0);
    }
    else if (param0 == 1)
    {
        FUN_02005160(0x7fff);
        FUN_02004C80(30);
    }
    else
    {
        FUN_02005160(0x7fff);
        FUN_02004C80(15);
    }

    FUN_02004C78();
}

THUMB_FUNC void FUN_020051AC()
{
    if (FUN_02005404() == FALSE && FUN_020048EC(FUN_02003FF4(0)) != -1 && FUN_02004124() != 0x47e)
    {

        FUN_02005454();
        FUN_020047C8(1, 1);
        return;
    }

    FUN_0200541C();
}

THUMB_FUNC void FUN_020051EC(u32 param0, u8 param1)
{
    NNS_SndPlayerSetPlayerVolume(param0, param1);
}
