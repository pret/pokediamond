#ifndef GUARD_LIBSDAT_H
#define GUARD_LIBSDAT_H

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
void * NNS_SndHeapCreate(void *, u32);
void NNS_SndArcInit(NNSSndArc *, const char *, void *, u32);
void NNS_SndArcPlayerSetup(void *);
void NNS_SndMain(void);
int NNS_SndHeapSaveState(void *);
void NNS_SndHeapLoadState(void *, int);
BOOL NNS_SndArcLoadGroup(u32 *, void *);
BOOL NNS_SndArcLoadSeq(u32 *, void *);
BOOL NNS_SndArcLoadSeqEx(u32 *, u32 *, void *);
BOOL NNS_SndArcLoadWaveArc(u32 *, void *);
BOOL NNS_SndArcLoadBank(u32 *, void *);
void NNS_SndHandleInit(u32 *);
void NNS_SndPlayerStopSeqByPlayerNo(int, int);
void NNS_SndHandleReleaseSeq(void);

#endif //GUARD_LIBSDAT_H
