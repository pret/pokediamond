#ifndef GUARD_SND_BANK_H
#define GUARD_SND_BANK_H

#include "global.h"

#include "SND_main.h"
#include "nitro/SND_bank_shared.h"

#define SND_INST_ILLEGAL    0
#define SND_INST_PCM        1
#define SND_INST_PSG        2
#define SND_INST_NOISE      3
#define SND_INST_DIRECTPCM  4
#define SND_INST_DUMMY      5
#define SND_INST_DRUM_TABLE 16
#define SND_INST_KEY_SPLIT  17

#define SND_BANK_MAX_WAVEARC 4

#define SND_INST_OFFSET_TYPE(off) ((u8)off)
#define SND_INST_OFFSET_NORMAL(bank, off) ((struct SNDInstParam *)((u8 *)bank + (u32)(off >> 8)))
#define SND_INST_OFFSET_DRUMS(bank, off) ((struct SNDDrumSet *)((u8 *)bank + (u32)(off >> 8)))
#define SND_INST_OFFSET_KEYSPL(bank, off) ((struct SNDKeySplit *)((u8 *)bank + (u32)(off >> 8)))

struct SNDWaveArc;

struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;             // 0x0
    struct SNDWaveArcLink *waveArcLLnext;   // 0x4
};  // size = 0x8

struct SNDBankData {
    struct SNDBinaryFileHeader fileHeader;                      // 0x00
    struct SNDBinaryBlockHeader blockHeader;                    // 0x10
    struct SNDWaveArcLink waveArcLinks[SND_BANK_MAX_WAVEARC];   // 0x18
    u32 instCount;                                              // 0x38
    u32 instOffsets[];                                          // 0x3C
};  // size = 0x40

struct SNDWaveArc {
    struct SNDBinaryFileHeader fileHeader;      // 0x00
    struct SNDBinaryBlockHeader blockHeader;    // 0x10
    struct SNDWaveArcLink *waveArcLLHead;       // 0x18
    u8 unk_1C[28];                              // 0x1C
    u32 waveCount;                              // 0x38
    u32 waveOffsets[];                          // 0x3C
};  // size = 0x3C

struct SNDInstPos {
    u32 program;    // 0x0
    u32 index;      // 0x4
};  // size = 0x8

struct SNDWaveData {
    struct SNDWaveParam param;  // 0x0
    u8 sampleData[];            // 0xC
};  // size = 0xC

void SND_AssignWaveArc(struct SNDBankData *bankData, s32 index, struct SNDWaveArc *waveArc);
void SND_DestroyBank(struct SNDBankData *bankData);
void SND_DestroyWaveArc(struct SNDWaveArc *waveArc);
struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData *bankData);
BOOL SND_GetNextInstData(const struct SNDBankData *bankData, struct SNDInstData *instData, struct SNDInstPos *instPos);
u32 SND_GetWaveDataCount(const struct SNDWaveArc *waveArc);
void SND_SetWaveDataAddress(struct SNDWaveArc *waveArc, s32 index, const struct SNDWaveData *waveData);
const struct SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, s32 index);

#endif // GUARD_SND_BANK_H
