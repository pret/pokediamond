#ifndef GUARD_LIBSDAT_H
#define GUARD_LIBSDAT_H

struct SDATHeader
{
    // Generic header
    char magic[4];
    u16 bom;
    u16 version;
    u32 filesize;
    u16 header_size;
    u16 section_count;
    // SDAT chunks
    u32 symb_offset, symb_size;
    u32 info_offset, info_size;
    u32 fat_offset, fat_size;
    u32 file_offset, file_size;
};

struct SDATFileMgr
{
    struct SDATHeader header;
    BOOL is_init;
    FSFile file; // 00034
    FSFileID fileID; // 7C
    void * fat_p;
    void * symb_p;
    void * info_p;
};

void NNS_SndInit(void);
void * NNS_SndHeapCreate(void *, u32);
void NNS_SndArcInit(struct SDATFileMgr *, char *, void *, u32);
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
