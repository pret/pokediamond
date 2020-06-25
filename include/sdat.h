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
    u32 unk_00030;
    FSFile file; // 00034
    FSFileID fileID; // 7C
    u32 unk_00084;
    u32 unk_00088;
    void * unk_0008C;
};

void FUN_020C01D0(void);
void * FUN_020C2A94(void *, u32);
void FUN_020C26F8(struct SDATHeader *, char *, void *, u32);
void FUN_020C39CC(void *);
void FUN_020C01A0(void);
int FUN_020C290C(void *);
void FUN_020C2828(void *, int);
BOOL FUN_020C36A8(u32 *, void *);
BOOL FUN_020C3674(u32 *, void *);
BOOL FUN_020C35E0(u32 *, u32 *, void *);
BOOL FUN_020C360C(u32 *, void *);
BOOL FUN_020C3640(u32 *, void *);
void FUN_020C0F80(u32 *);
void FUN_020C1040(int, int);
void FUN_020C0F68(void);

#endif //GUARD_LIBSDAT_H
