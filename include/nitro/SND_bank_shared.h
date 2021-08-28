#ifndef GUARD_SND_BANK_SHARED_H
#define GUARD_SND_BANK_SHARED_H

#include "nitro/types.h"

#include "nitro/SND_exChannel_shared.h"
#include "nitro/SND_main_shared.h"

#define SND_INST_MAX_KEYSPLIT 8

#define SND_INST_ILLEGAL 0
#define SND_INST_PCM 1
#define SND_INST_PSG 2
#define SND_INST_NOISE 3
#define SND_INST_DIRECTPCM 4
#define SND_INST_DUMMY 5
#define SND_INST_DRUM_TABLE 16
#define SND_INST_KEY_SPLIT 17

#define SND_BANK_MAX_WAVEARC 4

#define SND_INST_OFFSET_TYPE(off) ((u8)off)
#define SND_INST_OFFSET_NORMAL(bank, off) ((struct SNDInstParam *)((u8 *)bank + (u32)(off >> 8)))
#define SND_INST_OFFSET_DRUMS(bank, off) ((struct SNDDrumSet *)((u8 *)bank + (u32)(off >> 8)))
#define SND_INST_OFFSET_KEYSPL(bank, off) ((struct SNDKeySplit *)((u8 *)bank + (u32)(off >> 8)))

struct SNDInstParam
{
    u16 wave[2]; // 0x0
    u8 rootKey; // 0x4
    u8 envAttack; // 0x5
    u8 envDecay; // 0x6
    u8 envSustain; // 0x7
    u8 envRelease; // 0x8
    u8 pan; // 0x9
}; // size = 0xA

struct SNDInstData
{
    u8 type; // 0x0
    u8 unk_1; // 0x1
    struct SNDInstParam param; // 0x2
}; // size = 0xC

struct SNDKeySplit
{
    u8 key[SND_INST_MAX_KEYSPLIT]; // 0x0
    struct SNDInstData instruments[]; // 0x8
}; // size = 0x8

struct SNDDrumSet
{
    u8 minKey;
    u8 maxKey;
    struct SNDInstData instruments[];
}; // size = 0x2

struct SNDWaveArc;

struct SNDWaveArcLink
{
    struct SNDWaveArc *waveArc; // 0x0
    struct SNDWaveArcLink *waveArcLLnext; // 0x4
}; // size = 0x8

struct SNDBankData
{
    struct SNDBinaryFileHeader fileHeader; // 0x00
    struct SNDBinaryBlockHeader blockHeader; // 0x10
    struct SNDWaveArcLink waveArcLinks[SND_BANK_MAX_WAVEARC]; // 0x18
    u32 instCount; // 0x38
    u32 instOffsets[]; // 0x3C
}; // size = 0x40

struct SNDWaveArc
{
    struct SNDBinaryFileHeader fileHeader; // 0x00
    struct SNDBinaryBlockHeader blockHeader; // 0x10
    struct SNDWaveArcLink *waveArcLLHead; // 0x18
    u8 unk_1C[28]; // 0x1C
    u32 waveCount; // 0x38
    u32 waveOffsets[]; // 0x3C
}; // size = 0x3C

struct SNDInstPos
{
    u32 program; // 0x0
    u32 index; // 0x4
}; // size = 0x8

struct SNDWaveData
{
    struct SNDWaveParam param; // 0x0
    u8 sampleData[]; // 0xC
}; // size = 0xC

#endif // GUARD_SND_BANK_SHARED_H
