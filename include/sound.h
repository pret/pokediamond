#ifndef POKEDIAMOND_SOUND_H
#define POKEDIAMOND_SOUND_H

#include "FS_file.h"
#include "NNS_SND_arc.h"
#include "NNS_SND_heap.h"
#include "NNS_SND_arc_loader.h"
#include "player_data.h"

struct SoundData
{
    NNSSndArc header;
    NNSSndHeapHandle * heap; // 0x00090
    u8 unk_00094[0xBBC00];
    u32 players[9];
    u32 unk_BBCB8;
    u32 unk_BBCBC;
    u8 unk_BBCC0[0x20];
    u8 unk_BBCE0[0x1000];
    u8 unk_BCCE0[0x1C];
    u16 unk_BCCFC;
    u16 unk_BCCFE;
    s32 unk_BCD00;
    u32 unk_BCD04;
    u32 unk_BCD08;
    u16 unk_BCD0C;
    u16 unk_BCD0E;
    u8 unk_BCD10;
    u8 unk_BCD11;
    u16 unk_BCD12;
    u8 unk_BCD14;
    u8 unk_BCD15;
    u8 unk_BCD16;
    u8 unk_BCD17;
    u8 unk_BCD18;
    u8 unk_BCD19;
    u8 unk_BCD1A;
    u8 unk_BCD1B;
    int unk_BCD1C[7];
    u8 unk_BCD38;
    u8 unk_BCD39;
    u8 unk_BCD3A;
    u8 unk_BCD3B;
    u32 unk_BCD3C;
    u64 unk_BCD40;
    u32 unk_BCD48;
    void * unk_BCD4C;
    u32 unk_BCD50;
    u32 unk_BCD54;
    u32 unk_BCD58;
    u32 unk_BCD5C;
};

struct SoundData * GetSoundDataPointer(void);
void InitSoundData(void * a0, struct Options * a1);
void * FUN_02003D38(u32 a0);
int GF_Snd_SaveState(int * level_p);
void GF_Snd_RestoreState(int level);
BOOL GF_Snd_LoadGroup(int groupNo);
BOOL GF_Snd_LoadSeq(int seqNo);
BOOL GF_Snd_LoadSeqEx(int seqNo, u32 loadFlag);
BOOL GF_Snd_LoadWaveArc(int waveArcNo);
BOOL GF_Snd_LoadBank(int bankNo);
u32 * FUN_02003FF4(int playerNo);
u32 FUN_02004018(u32 a0);
void DoSoundUpdateFrame(void);

#endif //POKEDIAMOND_SOUND_H
