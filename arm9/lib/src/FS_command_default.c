#include "nitro.h"
#include "FS_file.h"
#include "FS_command.h"
#include "FS_archive.h"
#include "MI_byteAccess.h"

typedef struct
{
    FSArchive *arc;
    u32 pos;
}
FSiSyncReadParam;

FSResult FSi_ReadFileCommand(FSFile * p_file);
FSResult FSi_WriteFileCommand(FSFile * p_file);
FSResult FSi_SeekDirCommand(FSFile * p_file);
FSResult FSi_ReadDirCommand(FSFile * p_file);
FSResult FSi_FindPathCommand(FSFile * p_file);
FSResult FSi_GetPathCommand(FSFile * p_file);
FSResult FSi_OpenFileFastCommand(FSFile * p_file);
FSResult FSi_OpenFileDirectCommand(FSFile * p_file);
FSResult FSi_CloseFileCommand(FSFile * p_file);

FSResult (*const fsi_default_command[])(FSFile *) = {
    [FS_COMMAND_READFILE]       = FSi_ReadFileCommand,
    [FS_COMMAND_WRITEFILE]      = FSi_WriteFileCommand,
    [FS_COMMAND_SEEKDIR]        = FSi_SeekDirCommand,
    [FS_COMMAND_READDIR]        = FSi_ReadDirCommand,
    [FS_COMMAND_FINDPATH]       = FSi_FindPathCommand,
    [FS_COMMAND_GETPATH]        = FSi_GetPathCommand,
    [FS_COMMAND_OPENFILEFAST]   = FSi_OpenFileFastCommand,
    [FS_COMMAND_OPENFILEDIRECT] = FSi_OpenFileDirectCommand,
    [FS_COMMAND_CLOSEFILE]      = FSi_CloseFileCommand,
};

// Case-insensitive string comparison
u32 FSi_StrNICmp(const char * str1, const char * str2, u32 len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        u32 c = MI_ReadByte(str1 + i) - 'A';
        u32 d = MI_ReadByte(str2 + i) - 'A';
        if (c <= 'Z' - 'A')
            c += 'a' - 'A';
        if (d <= 'Z' - 'A')
            d += 'a' - 'A';
        if (c != d)
            return c - d;
    }
    return 0;
}

FSResult FSi_ReadTable(FSiSyncReadParam * p, void * dst, u32 len)
{
    FSResult ret;
    FSArchive * const p_arc = p->arc;
    p_arc->flag |= FS_ARCHIVE_FLAG_IS_SYNC;
    switch (ret = (*p_arc->table_func)(p_arc, dst, p->pos, len))
    {
    case FS_RESULT_SUCCESS:
    case FS_RESULT_FAILURE:
        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_SYNC;
        break;
    case FS_RESULT_PROC_ASYNC:
    {
        OSIntrMode bak_psr = OS_DisableInterrupts();
        while (FSi_IsArchiveSync(p_arc))
            OS_SleepThread(&p_arc->sync_q);
        OS_RestoreInterrupts(bak_psr);
        ret = p_arc->list.next->error;
    }
        break;
    }
    p->pos += len;
    return ret;
}

FSResult FSi_SeekDirDirect(FSFile * p_dir, u32 id)
{
    p_dir->stat |= FS_FILE_STATUS_SYNC;
    p_dir->arg.seekdir.pos.arc = p_dir->arc;
    p_dir->arg.seekdir.pos.pos = 0;
    p_dir->arg.seekdir.pos.index = 0;
    p_dir->arg.seekdir.pos.own_id = (u16)id;
    return FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
}

// The actual commands
FSResult FSi_ReadFileCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.readfile.len;
    void *const dst = p_file->arg.readfile.dst;
    p_file->prop.file.pos += len;
    return (*p_arc->read_func)(p_arc, dst, pos, len);
}

FSResult FSi_WriteFileCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.writefile.len;
    const void *const src = p_file->arg.writefile.src;
    p_file->prop.file.pos += len;
    return (*p_arc->write_func)(p_arc, src, pos, len);
}
