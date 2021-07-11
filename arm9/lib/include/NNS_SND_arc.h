#ifndef GUARD_NNS_SND_ARC_H
#define GUARD_NNS_SND_ARC_H

#include "SND_main.h"

typedef struct NNSSndArcHeader
{
    struct SNDBinaryFileHeader fileHeader;
    u32 symbolDataOffset;
    u32 symbolDataSize;
    u32 infoOffset;
    u32 infoSize;
    u32 fatOffset;
    u32 fatSize;
    u32 fileImageOffset;
    u32 fileImageSize;
} NNSSndArcHeader;

typedef struct NNSSndArc
{
    NNSSndArcHeader header;
    BOOL file_open;
    FSFile file;
    FSFileID fileId;
    struct NNSSndArcFat* fat;
    struct NNSSndArcSymbol* symbol;
    struct NNSSndArcInfo* info;
} NNSSndArc;

void NNS_SndInit(void);
void NNS_SndArcInit(NNSSndArc *, const char *, void *, u32);
void NNS_SndArcPlayerSetup(void *);
void NNS_SndMain(void);
void NNS_SndHandleInit(u32 *);
void NNS_SndPlayerStopSeqByPlayerNo(int playerNo, int fadeFrame);
void NNS_SndHandleReleaseSeq(u32 *);

#endif //GUARD_NNS_SND_ARC_H
