#include "global.h"
#include "sound.h"
#include "SPI_mic.h"
#include "SPI_pm.h"
#include "unk_020040F4.h"

#pragma thumb on

static struct SoundData sSoundDataBuffer;
static u32 UNK_02107070;
static u32 UNK_02107074;

void FUN_02003C40(void);
BOOL FUN_02003D04(void);
void GF_InitMic(void);
void GF_SoundDataInit(struct SoundData *);
void FUN_02004088(struct SoundData *);
void FUN_020040A4(struct SoundData *);
void FUN_020040DC(void);

extern void FUN_0200521C(int);
extern void FUN_0200538C(int, int, int);
extern BOOL FUN_02005404(void);
extern void FUN_02005CFC(void);

void InitSoundData(struct SaveChatotSoundClip * chatot, struct Options * options)
{
    struct SoundData * sdat = GetSoundDataPointer();
    NNS_SndInit();
    GF_InitMic();
    GF_SoundDataInit(sdat);
    sdat->heap = NNS_SndHeapCreate(sdat->heapBuffer, sizeof(sdat->heapBuffer));
    NNS_SndArcInit(&sdat->header, "data/sound/sound_data.sdat", sdat->heap, 0);
    NNS_SndArcPlayerSetup(sdat->heap);
    FUN_02004088(sdat);
    FUN_020040A4(sdat);
    UNK_02107074 = 0;
    sdat->chatot = chatot;
    GF_SndSetMonoFlag(options->soundMethod);
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
    NNS_SndMain();
}

void FUN_02003C40(void)
{
    struct SoundData * sdat = GetSoundDataPointer();
    switch (UNK_02107070)
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
    UNK_02107070 = (u32)a0;
}

BOOL FUN_02003D04(void)
{
    struct SoundData * sdat = GetSoundDataPointer();
    if (GF_SndPlayerCountPlayingSeqByPlayerNo(2))
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
        return &sdat->chatot;
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

int GF_Snd_SaveState(int * level_p)
{
    struct SoundData * sdat = GetSoundDataPointer();
    int level = NNS_SndHeapSaveState(sdat->heap);
    GF_ASSERT(level != -1);
    if (level_p != NULL)
        *level_p = level;
    return level;
}

void GF_Snd_RestoreState(int level)
{
    struct SoundData * sdat = GetSoundDataPointer();
    NNS_SndHeapLoadState(sdat->heap, level);
}

BOOL GF_Snd_LoadGroup(int groupNo)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return NNS_SndArcLoadGroup(groupNo, sdat->heap);
}

BOOL GF_Snd_LoadSeq(int seqNo)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return NNS_SndArcLoadSeq(seqNo, sdat->heap);
}

BOOL GF_Snd_LoadSeqEx(int seqNo, u32 loadFlag)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return NNS_SndArcLoadSeqEx(seqNo, loadFlag, sdat->heap);
}

BOOL GF_Snd_LoadWaveArc(int waveArcNo)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return NNS_SndArcLoadWaveArc(waveArcNo, sdat->heap);
}

BOOL GF_Snd_LoadBank(int bankNo)
{
    struct SoundData * sdat = GetSoundDataPointer();
    return NNS_SndArcLoadBank(bankNo, sdat->heap);
}

u32 * GetSoundPlayer(int playerNo)
{
    struct SoundData * sdat = GetSoundDataPointer();
    if (playerNo >= (s32)NELEMS(sdat->players))
    {
        GF_ASSERT(0);
        playerNo = 0;
    }
    return &sdat->players[playerNo];
}

int FUN_02004018(u32 a0)
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

void GF_SoundDataInit(struct SoundData * sdat)
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
        NNS_SndHandleInit(&sdat->players[i]);
    }
}

void FUN_020040A4(struct SoundData * sdat)
{
    GF_Snd_SaveState(&sdat->unk_BCD1C[0]);
    GF_Snd_LoadGroup(0);
    GF_Snd_SaveState(&sdat->unk_BCD1C[1]);
}

void GF_InitMic(void)
{
    MIC_Init();
    PM_SetAmp(1);
    PM_SetAmpGain(2);
}

void FUN_020040DC(void)
{
    NNS_SndPlayerStopSeqByPlayerNo(7, 0);
    NNS_SndHandleReleaseSeq(GetSoundPlayer(7));
}
