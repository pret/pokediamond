#include "global.h"
#include "unk_020051F4.h"
#include "NNS_SND_arc.h"
#include "constants/species.h"
#include "heap.h"
#include "sound.h"
#include "unk_020040F4.h"
#include "unk_0200CA44.h"
#include "sound_chatot.h"

extern u32 NNS_SndArcPlayerStartSeq(u32 *, u32);
extern u32 NNS_SndArcPlayerStartSeqEx(u32 *, s32, s32, s32, u32);
extern void NNS_SndPlayerStopSeqBySeqNo(u32, u32);
extern void NNS_SndPlayerStopSeqAll(u32);
extern void NNS_SndPlayerStopSeq(u32 *, u32);
extern void NNS_SndPlayerSetTrackPan(u32 *, u32, u32);
extern void *sub_0201B6C8(u32 *);

u32 sub_020051F4(u16 param0)
{
    int playerNo = sub_02004018(sub_020048D0(param0));

    u32 ret = NNS_SndArcPlayerStartSeq(GetSoundPlayer(playerNo), param0);

    sub_0200526C(param0, playerNo);

    return ret;
}

u32 sub_0200521C(u16 param0)
{
    u8 r4 = sub_020048D0(param0);
    int playerNo = sub_02004018(r4);

    u32 ret;
    if (r4 == 7)
    {
        ret = sub_02005288(param0, r4, playerNo);
    }
    else if (r4 == 1)
    {
        ret = sub_020052B8(param0, r4, playerNo);
    }
    else
    {
        GF_AssertFail();
        return 0;
    }

    sub_02004DBC(0);
    sub_0200526C(param0, playerNo);

    return ret;
}

void sub_0200526C(u16 param0, int playerNo)
{
    sub_02004110(param0);
    sub_02004858(param0, playerNo);

    sub_02003CE8(1);
}

u32 sub_02005288(u16 param0, u32 param1, int playerNo)
{
#pragma unused(param1)
    GF_Snd_RestoreState(sub_02004748(3));
    GF_Snd_LoadSeq(param0);
    GF_Snd_SaveState(sub_02003D38(26));
    return NNS_SndArcPlayerStartSeq(GetSoundPlayer(playerNo), param0);
}

u32 sub_020052B8(u16 param0, u32 param1, int playerNo)
{
#pragma unused(param1)
    sub_02003D38(18);
    u16 *r4 = sub_02003D38(31);

    sub_020045C4(param0, sub_02004900(GF_SndPlayerGetSeqNo(GetSoundPlayer(0))));

    return NNS_SndArcPlayerStartSeqEx(GetSoundPlayer(playerNo), -1, sub_02004900(*r4), -1, param0);
}

u32 sub_02005308(u32 param0, u16 param1)
{
    if (param0 != 4)
    {
        GF_AssertFail();
        return 0;
    }

    if (sub_020048D0(param1) != 7)
    {
        GF_AssertFail();
        return 0;
    }

    GF_Snd_LoadSeqEx(param1, 1);

    u32 r4 = NNS_SndArcPlayerStartSeq(GetSoundPlayer(7), param1);
    sub_02004110(param1);
    sub_02003CE8(1);

    return r4;
}

void sub_02005350(u16 param0, u32 param1)
{
    NNS_SndPlayerStopSeqBySeqNo(param0, param1);

    u8 r0 = sub_020048D0(param0);
    if (r0 != 0xff)
    {
        NNS_SndHandleReleaseSeq(GetSoundPlayer(sub_02004018(r0)));
    }

    sub_02005374();
}

void sub_02005374()
{
    sub_02004110(0);
    sub_02004130(0);
    sub_02003CE8(0);
}

void sub_0200538C(s32 param0, u16 param1, u32 param2)
{
    u8 r0 = sub_020048D0(sub_02004124());
    if (r0 == 0xff)
    {
        return;
    }

    int playerNo = sub_02004018(r0);
    if (param2 == 0)
    {
        GF_SndPlayerMoveVolume(playerNo, 0, 0);
    }

    GF_SndPlayerMoveVolume(playerNo, param0, param1);
    sub_02004D74(param1);
    sub_02003CE8(3);
}

void GF_SndStartFadeOutBGM(u16 param0, u16 param1)
{
    u8 r6 = sub_020048D0(sub_02004124());
    if (r6 == 0xff)
    {
        return;
    }

    if (!sub_02005404())
    {
        GF_SndPlayerMoveVolume(sub_02004018(r6), param0, param1);
        sub_02004D74(param1);
    }

    sub_02003CE8(4);
}

u16 sub_02005404()
{
    return *(u16 *)sub_02003D38(6);
}

u16 sub_02005410(u16 param0)
{
    return GF_SndPlayerCountPlayingSeqByPlayerNo(sub_020048D0(param0));
}

void sub_0200541C()
{
    u8 *r5 = sub_02003D38(15);
    u8 *r4 = sub_02003D38(16);
    NNS_SndPlayerStopSeqAll(0);

    if (*r5 == 1)
    {
        sub_02004AAC(14);
    }

    if (*r4 == 1)
    {
        sub_02004AAC(15);
    }

    sub_02003CE8(0);
}

void sub_02005454()
{
    u8 *r5 = sub_02003D38(15);
    u8 *r4 = sub_02003D38(16);

    NNS_SndPlayerStopSeq(GetSoundPlayer(7), 0);
    sub_02005374();

    for (s32 i = 0; i < 4; i++)
    {
        sub_020054F8(i + 3, 0);
    }

    sub_02005614(0);

    if (*r5 == 1)
    {
        sub_02004AAC(14);
    }

    if (*r4 == 1)
    {
        sub_02004AAC(15);
    }
}

u32 sub_020054A8(u16 param0, u32 param1)
{
    u32 r6 = PlaySE(param0);
    sub_02005530(param0, 0xFFFF, param1);

    return r6;
}

u32 PlaySE(u16 param0)
{
    int playerNo = sub_02004018(sub_020048D0(param0));

    u32 r6 = NNS_SndArcPlayerStartSeq(GetSoundPlayer(playerNo), param0);
    sub_02004858(param0, playerNo);

    return r6;
}

void sub_020054F0(u32 param0, u32 param1)
{
    NNS_SndPlayerStopSeqBySeqNo(param0, param1);
}

void sub_020054F8(s32 param0, u32 param1)
{
    NNS_SndPlayerStopSeq(GetSoundPlayer(param0), param1);
}

u16 sub_02005508(u16 param0)
{
    return GF_SndPlayerCountPlayingSeqByPlayerNo(sub_020048D0(param0));
}

BOOL sub_02005514()
{
    for (s32 i = 0; i < 4; i++)
    {
        if (GF_SndPlayerCountPlayingSeqByPlayerNo(i + 3) == 1)
        {
            return TRUE;
        }
    }

    return FALSE;
}

void sub_02005530(u16 param0, u32 param1, u32 param2)
{
    NNS_SndPlayerSetTrackPan(GetSoundPlayer(sub_02004018(sub_020048D0(param0))), param1, param2);
}

void sub_0200554C(u32 param0)
{
    int playerNo = sub_02004018(3);

    for (int i = 0; i < 4; i++)
    {
        NNS_SndPlayerSetTrackPan(GetSoundPlayer(playerNo + i), 0xFFFF, param0);
    }
}

u32 sub_02005578(u16 species)
{
    u8 *r4 = sub_02003D38(17);
    struct SaveChatotSoundClip **r0 = sub_02003D38(35);

    if (species != SPECIES_CHATOT)
    {
        if (species > SPECIES_MANAPHY_EGG || species == SPECIES_NONE)
        {
            species = SPECIES_BULBASAUR;
        }
    }

    if (species == SPECIES_CHATOT)
    {
        if (sub_02005D48(*r0, 0, 127, 0) == 1)
        {
            sub_02005E80(0);

            return 1;
        }
    }

    u32 res;
    if (*r4 == 0)
    {
        sub_02005614(0);
        res = NNS_SndArcPlayerStartSeqEx(GetSoundPlayer(1), -1, species, -1, 2);
        sub_02004858(species, 1);
    }
    else
    {
        res = NNS_SndArcPlayerStartSeqEx(GetSoundPlayer(8), -1, species, -1, 2);
        sub_02004858(species, 8);
    }

    sub_02005E80(0);

    return res;
}

void sub_02005614(u32 param0)
{
    u8 *r6 = sub_02003D38(15);
    u8 *r4 = sub_02003D38(16);
    sub_02003D38(14);

    NNS_SndPlayerStopSeq(GetSoundPlayer(1), param0);
    NNS_SndPlayerStopSeq(GetSoundPlayer(8), param0);

    if (*r6 == 1)
    {
        sub_02004C3C(14);
        sub_02004A04(14);
    }

    if (*r4 == 1)
    {
        sub_02004C3C(15);
        sub_02004A04(15);
    }

    sub_02005DFC();
}

BOOL sub_02005670()
{
    u8 *r5 = sub_02003D38(15);
    u8 *r4 = sub_02003D38(16);
    sub_02003D38(14);

    if (*r5 == 1)
    {
        return sub_02004ABC(14);
    }

    if (*r4 == 1)
    {
        return sub_02004ABC(15);
    }

    return GF_SndPlayerCountPlayingSeqByPlayerNo(0);
}

u32 sub_020056AC(u32 param0, u16 param1, s32 param2, s32 param3, HeapID heapId)
{
    s32 st1c, st18;
    u8 *st14 = sub_02003D38(15);
    u8 *st10 = sub_02003D38(16);
    u8 *r4 = sub_02003D38(17);
    u8 *stc = sub_02003D38(29);
    sub_02003D38(35);

    st1c = 64 + (param2 / 2);
    st18 = param3 - 30;

    if (st18 <= 0)
    {
        st18 = 1;
    }

    *r4 = 0;
    if (*st14 == 1)
    {
        sub_02004C3C(14);
        sub_02004A04(14);
    }

    if (*st10 == 1)
    {
        sub_02004C3C(15);
        sub_02004A04(15);
    }

    u16 species = param1;
    if (species != SPECIES_CHATOT)
    {
        if (species > SPECIES_MANAPHY_EGG || species == SPECIES_NONE)
        {
            species = SPECIES_BULBASAUR;
        }
    }

    if (param1 == SPECIES_CHATOT)
    {
        switch (param0)
        {
            case 0:
            case 1:
            case 2:
            case 5:
            case 11:
            case 12:
                sub_02005578(SPECIES_CHATOT);
                if (*stc == 0)
                {
                    GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
                    sub_02005AC8(species, 1, param3);
                }
                else
                {
                    sub_02004ACC(14, (u8)st1c);
                    sub_02004AF8(14, param3);
                }

                return 1;

            default:
                sub_02005E80(1);
        }
    }

    switch (param0)
    {
        case 0:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            break;
        case 1:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(20, heapId);
            break;
        case 2:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, 64);
            sub_02005BC8(species, 20);
            GF_SndPlayerSetTrackPan(8, 0xFFFF, param2);
            sub_02005AC8(species, 8, st18);
            break;
        case 3:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(30, heapId);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, 192);
            sub_02005BC8(species, 16);
            GF_SndPlayerSetTrackPan(8, 0xFFFF, param2);
            sub_02005AC8(species, 8, st18);
            break;
        case 4:
            sub_02004984(14);
            sub_02004B30(species, param3, st1c, 14, heapId);
            sub_02004ACC(14, (u8)st1c);
            sub_02005AE0(15, heapId);
            sub_02004AE4(14, 34304);
            sub_02005BF8(species, -64, st18, st1c, heapId);
            sub_02004AE4(15, 34304);
            break;
        case 5:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, -224);
            break;
        case 6:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, 44);
            sub_02005BC8(species, -64);
            GF_SndPlayerSetTrackPan(8, 0xFFFF, param2);
            sub_02005AC8(species, 8, st18);
            break;
        case 7:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(11, heapId);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, -128);
            break;
        case 8:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(60, heapId);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, 60);
            break;
        case 9:
            sub_02004984(14);
            sub_02004B30(species, param3, st1c, 14, heapId);
            sub_02004ACC(14, (u8)st1c);
            sub_02005AE0(13, heapId);
            sub_02004AE4(14, 26624);
            break;
        case 10:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(100, heapId);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, -44);
            break;
        case 11:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, -96);
            break;
        case 12:
            sub_02005578(species);
            GF_SndPlayerSetTrackPan(1, 0xFFFF, param2);
            sub_02005AC8(species, 1, param3);
            sub_02005AE0(20, heapId);
            GF_SndPlayerSetTrackPitch(1, 0xFFFF, -96);
            break;
        case 13:
            sub_02005578(species);
            sub_02005AC8(species, 1, 127);
            sub_02005BC8(species, 20);
            GF_SndPlayerSetTrackPan(8, 0xFFFF, param2);
            GF_SndPlayerMoveVolume(8, param3, 0);
            break;
        case 14:
            sub_02005578(species);
            break;
    }

    return 1;
}

void sub_02005AC8(u32 param0, int playerNo, s32 param2)
{
    GF_SndPlayerSetInitialVolume(playerNo, param2);
    sub_02004858(param0, playerNo);
}

void sub_02005AE0(u32 param0, HeapID heapId)
{
    u32 *r6 = sub_02003D38(34);
    sub_02005BA0();

    u32 *ptr = AllocFromHeap(heapId, 2 * sizeof(u32));
    if (ptr == NULL)
    {
        GF_AssertFail();
        return;
    }

    ((u8 *)ptr)[0] = 0;
    ((u8 *)ptr)[1] = 0;
    ((u8 *)ptr)[2] = 0;
    ((u8 *)ptr)[3] = 0;
    ((u8 *)ptr)[4] = 0;
    ((u8 *)ptr)[5] = 0;
    ((u8 *)ptr)[6] = 0;
    ((u8 *)ptr)[7] = 0;

    ptr[0] = param0;
    u32 r0 = (u32)sub_0200CA44((void (*)(u32, void *))sub_02005B2C, (void *)ptr, 0);
    ptr[1] = r0;
    *r6 = r0;
}

void sub_02005B2C(u32 param0, s32 *param1)
{
#pragma unused(param0)
    u8 *r6 = sub_02003D38(15);
    u8 *r4 = sub_02003D38(16);

    if (*param1 == 10)
    {
        GF_SndPlayerMoveVolume(1, 0, *param1);
        GF_SndPlayerMoveVolume(8, 0, *param1);
    }

    (*param1)--;

    if (!sub_02005670())
    {
        *param1 = 0;
    }

    if (*param1 <= 0)
    {
        sub_02005614(0);
        if (*r6 == 1)
        {
            sub_02004C3C(14);
            sub_02004A04(14);
        }
        if (*r4 == 1)
        {
            sub_02004C3C(15);
            sub_02004A04(15);
        }

        sub_02005BA0();
    }
}

void sub_02005BA0()
{
    u32 **r4 = sub_02003D38(34);
    if (*r4 != NULL)
    {
        void *r5 = sub_0201B6C8(*r4);
        sub_0200CAB4((s32)(*r4));
        FreeToHeap(r5);
    }

    *r4 = 0;
}

u32 sub_02005BC8(u16 param0, s32 param1)
{
    *(u8 *)sub_02003D38(17) = 1;

    sub_02005E80(1);
    u32 res = sub_02005578(param0);

    GF_SndPlayerSetTrackPitch(8, 0xFFFF, param1);

    return res;
}

void sub_02005BF8(u32 param0, s32 param1, s32 param2, s32 param3, HeapID heapId)
{
#pragma unused(param1)
    *(u8 *)sub_02003D38(17) = 1;

    sub_02004984(15);
    sub_02004B30(param0, param2, param3, 15, heapId);
}

u32 PlaySound(u16 param0)
{
    sub_020048F4(param0);
    sub_02005CEC(param0);

    u8 r0 = sub_020048D0(sub_02004124());
    if (r0 != 0xff)
    {
        sub_020047C8(r0, 1);
    }

    GF_Snd_SaveState((int *)sub_02003D38(28));
    GF_Snd_LoadSeqEx(param0, 3);
    u32 res = NNS_SndArcPlayerStartSeq(GetSoundPlayer(2), param0);
    sub_02004858(param0, 2);

    return res;
}

BOOL sub_02005C74()
{
    u16 *r4 = sub_02003D38(13);

    if (GF_SndPlayerCountPlayingSeqByPlayerNo(2) != 0)
    {
        return TRUE;
    }

    if (*r4 != 0)
    {
        (*r4)--;
        return TRUE;
    }

    return FALSE;
}

void sub_02005CA0(u32 param0)
{
    NNS_SndPlayerStopSeq(GetSoundPlayer(2), param0);
    GF_Snd_RestoreState(sub_02004748(6));
}

BOOL sub_02005CBC()
{
    sub_02003D38(13);

    if (sub_02005C74() == TRUE)
    {
        return TRUE;
    }

    sub_02005CA0(0);
    u8 r0 = sub_020048D0(sub_02004124());

    if (r0 != 0xff)
    {
        sub_020047C8(r0, 0);
    }

    return FALSE;
}

void sub_02005CEC(u16 param0)
{
#pragma unused(param0)
    *(u16 *)sub_02003D38(13) = 15;
}
