#ifndef NITRO_FS_FILE_H_
#define NITRO_FS_FILE_H_

#include "nitro.h"

#include "FS_archive.h"

#define	FS_FILE_STATUS_BUSY			0x00000001
#define	FS_FILE_STATUS_CANCEL		0x00000002
#define	FS_FILE_STATUS_SYNC			0x00000004
#define	FS_FILE_STATUS_ASYNC		0x00000008
#define	FS_FILE_STATUS_IS_FILE		0x00000010
#define	FS_FILE_STATUS_IS_DIR		0x00000020
#define FS_FILE_STATUS_OPERATING    0x00000040

typedef enum FSSeekFileMode
{
    FS_SEEK_SET = 0,
    FS_SEEK_CUR,
    FS_SEEK_END
} FSSeekFileMode;

struct FSFile;

#define FS_DMA_NOT_USE ((u32)~0)

typedef struct FSDirPos
{
    struct FSArchive *arc;
    u16 own_id;
    u16 index;
    u32 pos;
}
FSDirPos;

typedef struct FSFileID
{
    struct FSArchive *arc;
    u32 file_id;
}
FSFileID;

typedef struct
{
    union
    {
        FSFileID file_id;
        FSDirPos dir_id;
    };
    u32 is_directory;
    u32 name_len;
    char name[128];
}
FSDirEntry;


typedef struct
{
    FSDirPos pos;
}
FSSeekDirInfo;


typedef struct
{
    FSDirEntry *p_entry;
    BOOL skip_string;
}
FSReadDirInfo;


typedef struct
{
    FSDirPos pos;
    const char *path;
    BOOL find_directory;
    union
    {
        FSFileID *file;
        FSDirPos *dir;
    }
        result;
}
FSFindPathInfo;


typedef struct
{
    u8 *buf;
    u32 buf_len;
    u16 total_len;
    u16 dir_id;
}
FSGetPathInfo;


typedef struct
{
    FSFileID id;
}
FSOpenFileFastInfo;


typedef struct
{
    u32 top;
    u32 bottom;
    u32 index;
}
FSOpenFileDirectInfo;


typedef struct
{
    u32 reserved;
}
FSCloseFileInfo;


typedef struct
{
    void *dst;
    u32 len_org;
    u32 len;
}
FSReadFileInfo;


typedef struct
{
    const void *src;
    u32 len_org;
    u32 len;
}
FSWriteFileInfo;

typedef struct FSFile
{
    FSFileLink link;
    struct FSArchive *arc;
    u32 stat;
    FSCommandType command;
    FSResult error;
    OSThreadQueue queue[1];
    union {
        struct
        {
            u32 own_id;
            u32 top;
            u32 bottom;
            u32 pos;
        } file;
        struct
        {
            FSDirPos pos;
            u32 parent;
        } dir;
    } prop;

    union {
        FSReadFileInfo readfile;
        FSWriteFileInfo writefile;

        FSSeekDirInfo seekdir;
        FSReadDirInfo readdir;
        FSFindPathInfo findpath;
        FSGetPathInfo getpath;
        FSOpenFileFastInfo openfilefast;
        FSOpenFileDirectInfo openfiledirect;
        FSCloseFileInfo closefile;
    } arg;
}
FSFile;

u32 FS_SetDefaultDMA(u32 dma_no); // returns the previous selection
void FS_InitFile(FSFile * p_file);
BOOL FS_WaitAsync(FSFile * p_file);
BOOL FS_OpenFileDirect(FSFile * p_file, FSArchive * p_arc, u32 image_top, u32 image_bottom, u32 file_index);
int FS_ReadFile(FSFile * p_file, void * dst, s32 len);
int FS_ReadFileAsync(FSFile * p_file, void * dst, s32 len);
BOOL FS_OpenFileFast(FSFile * p_file, FSFileID file_id);
BOOL FS_CloseFile(FSFile * p_file);

static inline u32 const FS_GetFileImageTop(volatile const FSFile * p_file) {
    return p_file->prop.file.top;
}

static inline u32 const FS_GetLength(volatile const FSFile * p_file)
{
    return p_file->prop.file.bottom - p_file->prop.file.top;
}

static inline BOOL FS_IsCanceling(volatile const FSFile * p_file)
{
    return (p_file->stat & FS_FILE_STATUS_CANCEL) ? TRUE : FALSE;
}

static inline BOOL FS_IsFileSyncMode(volatile const FSFile * p_file)
{
    return (p_file->stat & FS_FILE_STATUS_SYNC) ? TRUE : FALSE;
}

static inline BOOL FS_IsBusy(volatile const FSFile * p_file)
{
    return p_file->stat & FS_FILE_STATUS_BUSY ? TRUE : FALSE;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile * p_file)
{
    return (p_file->error == FS_RESULT_SUCCESS) ? TRUE : FALSE;
}

#endif //NITRO_FS_FILE_H_
