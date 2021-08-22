#ifndef POKEDIAMOND_UNK_020040F4_H
#define POKEDIAMOND_UNK_020040F4_H

#include "global.h"
#include "SPI_mic.h"

struct WaveArcInfo
{
    u32 unk00 : 24;
};

struct UnkStruct_020040F4_1
{
    void *unk00;
    u32 unk04;
    void *unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    s32 unk1c;
    u32 unk20;
    s32 unk24;
};

struct UnkStruct_020040F4_2
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u8 unk0c[9];
};

void FUN_020040F4(u8 param0);
u8 FUN_02004104(void);
void FUN_02004110(u16 param0);
u16 FUN_02004124(void);
void FUN_02004130(u16 param0);
u16 FUN_02004140(void);
void FUN_0200414C(u16 param0);
void FUN_0200415C(u8 param0);
BOOL FUN_02004180(s32 param0);
BOOL FUN_0200433C(u8 param0, int param1, u32 param2);
void FUN_020044A8(s32 param0);
void FUN_020044D4(int seqNo, u32 param1);
void FUN_02004568(int seqNo, u16 param1);
void FUN_020045C4(int seqNo, u32 param1);
void FUN_02004648(int param0, u32 param1);
void FUN_02004680(int param0, u32 param1);
void FUN_020046A0(int param0, u32 param1);
void FUN_020046C4(int param0, u32 param1);
void FUN_020046E8(s32 param0);
void FUN_02004704(s32 param0, int param1, u32 param2);
void FUN_02004724(int param0);
void FUN_02004738(void);
int FUN_02004748(s32 param0);
void FUN_020047C8(u8 param0, u8 param1);
void FUN_02004810(void);
void GF_SndPlayerMoveVolume(int playerNo, s32 param1, s32 param2);
void GF_SndPlayerSetInitialVolume(int playerNo, s32 param1);
void FUN_02004858(u32 param0, int playerNo);
void FUN_0200488C(u16 param0, u16 param1);
void GF_SndArcPlayerStartSeqEx(int playerNo, u32 param1, u32 param2);
u16 GF_SndPlayerCountPlayingSeqByPlayerNo(int playerNo);
u8 FUN_020048D0(u16 param0);
u32 GF_SndPlayerGetSeqNo(u32 *param0);
u32 FUN_020048F4(u16 param0);
u16 FUN_02004900(u32 param0);
u32 GF_MIC_StartAutoSampling(struct MIC_SamplingData *param0);
u32 GF_MIC_StopAutoSampling(void);
u32 GF_MIC_DoSamplingAsync(u32 param0, u32 param1, u32 param2, u32 param3);
void *FUN_02004930(u32 param0);
BOOL FUN_02004984(u32 param0);
void FUN_02004A04(u32 param0);
u32 FUN_02004A6C(struct UnkStruct_020040F4_1 *param0, u32 param1);
void FUN_02004AAC(u32 param0);
BOOL FUN_02004ABC(u32 param0);
void FUN_02004ACC(u32 param0, u32 param1);
void FUN_02004AE4(u32 param0, u32 param1);
void FUN_02004AF8(u32 param0, s32 param1);
u32 FUN_02004B30(u32 param0, s32 param1, s32 param2, u32 param3, u32 param4);
void FUN_02004C1C(u8 *param0, u32 param1);
void FUN_02004C3C(u32 param0);
BOOL GF_SndCaptureIsActive(void);
u32 GF_SndCaptureStartReverb(u32 param0);
void GF_SndCaptureStopReverb(u32 param0);
void GF_SndCaptureSetReverbVolume(u32 param0, u32 param1);
void FUN_02004CB4(void);
void GF_SndCaptureStopEffect(void);
void FUN_02004D04(s32 param0);
void GF_SndPlayerSetTrackPitch(int playerNo, u32 param1, s32 param2);
void FUN_02004D34(u16 param0, u32 param1, s32 param2);
void GF_SndPlayerSetTrackPan(int playerNo, u32 param1, s32 param2);
void GF_SndSetMonoFlag(u32 param0);
void FUN_02004D74(s32 param0);
void FUN_02004D84(u32 param0);
u16 FUN_02004D94(void);
u8 *FUN_02004DB4(void);
void FUN_02004DBC(u8 param0);
u32 FUN_02004DCC(u32 param0, u16 param1, u32 param2, u32 param3, u8 param4, u32 param5);
u32 FUN_02004E08(
    u32 param0, u16 param1, u32 param2, u32 param3, u32 param35, u8 param4, u32 param5);
void FUN_02004E44(u32 param0, u16 param1, u32 param2, u32 param3, u8 param4, u32 param5);
u32 FUN_02004E80(u32 param0);
u32 FUN_02004E8C(u32 *param0);
u32 FUN_02004E98(s32 param0);
u32 FUN_02004ED0(s32 param0);
u32 FUN_02004F28(u32 param0, struct UnkStruct_020040F4_2 *param1, s32 param2);
u32 GF_SndPlayerGetTick(int playerNo);
void FUN_02004F70(struct UnkStruct_020040F4_2 *param0, u8 *param1, int param2, s32 param3);
void FUN_02005068(s16 *param0, s16 *param1, u32 param2, u32 param3, void *param4);
void FUN_02005160(u32 param0);
void FUN_0200516C(u32 param0);
void FUN_020051AC(void);
void GF_SndPlayerSetPlayerVolume(u32 param0, u8 param1);

#endif // POKEDIAMOND_UNK_020040F4_H
