#include "nitro.h"
#include "FS_file.h"
#include "FS_command.h"
#include "FS_archive.h"
#include "MI_byteAccess.h"
#include "MI_memory.h"
#include "FSi_util.h"

typedef struct
{
    FSArchive *arc;
    u32 pos;
}
FSiSyncReadParam;

ARM_FUNC FSResult FSi_ReadFileCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_WriteFileCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_SeekDirCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_ReadDirCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_FindPathCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_GetPathCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_OpenFileFastCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_OpenFileDirectCommand(FSFile * p_file);
ARM_FUNC FSResult FSi_CloseFileCommand(FSFile * p_file);

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
ARM_FUNC u32 FSi_StrNICmp(const char * str1, const char * str2, u32 len)
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

ARM_FUNC FSResult FSi_ReadTable(FSiSyncReadParam * p, void * dst, u32 len)
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

ARM_FUNC FSResult FSi_SeekDirDirect(FSFile * p_dir, u32 id)
{
    p_dir->stat |= FS_FILE_STATUS_SYNC;
    p_dir->arg.seekdir.pos.arc = p_dir->arc;
    p_dir->arg.seekdir.pos.pos = 0;
    p_dir->arg.seekdir.pos.index = 0;
    p_dir->arg.seekdir.pos.own_id = (u16)id;
    return FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
}

// The actual commands
ARM_FUNC FSResult FSi_ReadFileCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.readfile.len;
    void *const dst = p_file->arg.readfile.dst;
    p_file->prop.file.pos += len;
    return (*p_arc->read_func)(p_arc, dst, pos, len);
}

ARM_FUNC FSResult FSi_WriteFileCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.writefile.len;
    const void *const src = p_file->arg.writefile.src;
    p_file->prop.file.pos += len;
    return (*p_arc->write_func)(p_arc, src, pos, len);
}

ARM_FUNC FSResult FSi_SeekDirCommand(FSFile * p_dir)
{
    FSResult ret;
    FSArchive *const p_arc = p_dir->arc;
    const FSDirPos *const arg = &p_dir->arg.seekdir.pos;

    FSArchiveFNT fnt_entry;
    FSiSyncReadParam param;
    param.arc = p_arc;
    param.pos = p_arc->fnt + arg->own_id * sizeof(fnt_entry);
    ret = FSi_ReadTable(&param, &fnt_entry, sizeof(fnt_entry));
    if (ret == FS_RESULT_SUCCESS)
    {
        p_dir->prop.dir.pos = *arg;
        if ((arg->index == 0) && (arg->pos == 0))
        {
            p_dir->prop.dir.pos.index = fnt_entry.index;
            p_dir->prop.dir.pos.pos = p_arc->fnt + fnt_entry.start;
        }
        p_dir->prop.dir.parent = (u32) (fnt_entry.parent & BIT_MASK(12));
    }
    return ret;
}

ARM_FUNC FSResult FSi_ReadDirCommand(FSFile *p_dir)
{
    FSDirEntry *p_entry = p_dir->arg.readdir.p_entry;
    FSResult ret;

    FSiSyncReadParam param;
    param.arc = p_dir->arc;
    param.pos = p_dir->prop.dir.pos.pos;

    {
        u8 len;
        ret = FSi_ReadTable(&param, &len, sizeof(len));
        if (ret != FS_RESULT_SUCCESS)
            return ret;
        p_entry->name_len = (u32)(len & BIT_MASK(7));
        p_entry->is_directory = (u32)((len >> 7) & 1);
    }
    if (p_entry->name_len == 0)
        return FS_RESULT_FAILURE;

    if (!p_dir->arg.readdir.skip_string)
    {
        ret = FSi_ReadTable(&param, p_entry->name, p_entry->name_len);
        if (ret != FS_RESULT_SUCCESS)
            return ret;
        MI_WriteByte((u8 *)p_entry->name + p_entry->name_len, (u8)'\0');
    }
    else
    {
        param.pos += p_entry->name_len;
    }

    if (p_entry->is_directory)
    {
        u16 id;
        ret = FSi_ReadTable(&param, &id, sizeof(id));
        if (ret != FS_RESULT_SUCCESS)
            return ret;
        p_entry->dir_id.arc = p_dir->arc;
        p_entry->dir_id.own_id = (u16)(id & BIT_MASK(12));
        p_entry->dir_id.index = 0;
        p_entry->dir_id.pos = 0;
    }
    else
    {
        p_entry->file_id.arc = p_dir->arc;
        p_entry->file_id.file_id = p_dir->prop.dir.pos.index;
        ++p_dir->prop.dir.pos.index;
    }
    p_dir->prop.dir.pos.pos = param.pos;

    return ret;
}

ARM_FUNC FSResult FSi_FindPathCommand(FSFile *p_dir)
{
    const char *path = p_dir->arg.findpath.path;
    const BOOL is_dir = p_dir->arg.findpath.find_directory;
    p_dir->arg.seekdir.pos = p_dir->arg.findpath.pos;
    (void)FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
    for (; MI_ReadByte(path); path += (MI_ReadByte(path) ? 1 : 0))
    {
        u32 is_directory;
        int name_len = 0;
        while ((is_directory = MI_ReadByte(path + name_len)),
            (is_directory && !FSi_IsSlash(is_directory)))
            ++name_len;
        if (is_directory || is_dir)
            is_directory = 1;
        if (name_len == 0)
        {
            return FS_RESULT_FAILURE;
        }
        else if (MI_ReadByte(path) == '.')
        {
            if (name_len == 1)
            {
                path += 1;
                continue;
            }
            else if ((name_len == 2) & (MI_ReadByte(path + 1) == '.'))
            {
                if (p_dir->prop.dir.pos.own_id != 0)
                    FSi_SeekDirDirect(p_dir, p_dir->prop.dir.parent);
                path += 2;
                continue;
            }
        }
        if (name_len > FS_FILE_NAME_MAX)
        {
            return FS_RESULT_FAILURE;
        }
        else
        {
            FSDirEntry etr;
            p_dir->arg.readdir.p_entry = &etr;
            p_dir->arg.readdir.skip_string = FALSE;
            for (;;)
            {
                if (FSi_TranslateCommand(p_dir, FS_COMMAND_READDIR) != FS_RESULT_SUCCESS)
                    return FS_RESULT_FAILURE;
                if ((is_directory != etr.is_directory) ||
                    (name_len != etr.name_len) || FSi_StrNICmp(path, etr.name, (u32)name_len))
                    continue;
                if (is_directory)
                {
                    path += name_len;
                    p_dir->arg.seekdir.pos = etr.dir_id;
                    (void)FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
                    break;
                }
                else if (is_dir)
                {
                    return FS_RESULT_FAILURE;
                }
                else
                {
                    *p_dir->arg.findpath.result.file = etr.file_id;
                    return FS_RESULT_SUCCESS;
                }
            }
        }
    }
    if (!is_dir)
        return FS_RESULT_FAILURE;
    *p_dir->arg.findpath.result.dir = p_dir->prop.dir.pos;
    return FS_RESULT_SUCCESS;
}

ARM_FUNC FSResult FSi_GetPathCommand(FSFile *p_file)
{
    FSArchive *const p_arc = p_file->arc;

    FSGetPathInfo *p_info = &p_file->arg.getpath;

    FSDirEntry entry;
    FSFile tmp;
    u32 dir_id;
    u32 file_id;
    u32 id;
    u32 len;

    enum
    { INVALID_ID = 0x10000 };

    FS_InitFile(&tmp);
    tmp.arc = p_file->arc;

    if (FS_IsDir(p_file))
    {
        dir_id = p_file->prop.dir.pos.own_id;
        file_id = INVALID_ID;
    }
    else
    {
        file_id = p_file->prop.file.own_id;
        if (p_info->total_len != 0)
        {
            dir_id = p_info->dir_id;
        }
        else
        {
            u32 pos = 0;
            u32 num_dir = 0;
            dir_id = INVALID_ID;
            do
            {
                FSi_SeekDirDirect(&tmp, pos);
                if (!pos)
                    num_dir = tmp.prop.dir.parent;
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = TRUE;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS)
                {
                    if (!entry.is_directory && (entry.file_id.file_id == file_id))
                    {
                        dir_id = tmp.prop.dir.pos.own_id;
                        break;
                    }
                }
            }
            while ((dir_id == INVALID_ID) && (++pos < num_dir));
        }
    }
    if (dir_id == INVALID_ID)
    {
        p_info->total_len = 0;
        return FS_RESULT_FAILURE;
    }
    if (p_info->total_len == 0)
    {
        len = 0;
        if (p_arc->name.pack <= 0x000000FF)
            len += 1;
        else if (p_arc->name.pack <= 0x0000FF00)
            len += 2;
        else
            len += 3;
        len += 1 + 1;
        if (file_id != INVALID_ID)
            len += entry.name_len;
        id = dir_id;
        if (id != 0)
        {
            FSi_SeekDirDirect(&tmp, id);
            do
            {
                FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = TRUE;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS)
                {
                    if (entry.is_directory && (entry.dir_id.own_id == id))
                    {
                        len += entry.name_len + 1;
                        break;
                    }
                }
                id = tmp.prop.dir.pos.own_id;
            }
            while (id != 0);
        }
        p_info->total_len = (u16)(len + 1);
        p_info->dir_id = (u16)dir_id;
    }
    if (!p_info->buf)
        return FS_RESULT_SUCCESS;
    if (p_info->buf_len < p_info->total_len)
        return FS_RESULT_FAILURE;
    else
    {
        u8 *dst = p_info->buf;
        u32 total = p_info->total_len;
        u32 pos = 0;
        if (p_arc->name.pack <= 0x000000FF)
            len = 1;
        else if (p_arc->name.pack <= 0x0000FF00)
            len = 2;
        else
            len = 3;
        MI_CpuCopy8(p_arc->name.ptr, dst + pos, len);
        pos += len;
        MI_CpuCopy8(":/", dst + pos, 2);
        pos += 2;
        id = dir_id;
        FSi_SeekDirDirect(&tmp, id);
        if (file_id != INVALID_ID)
        {
            tmp.arg.readdir.p_entry = &entry;
            tmp.arg.readdir.skip_string = FALSE;
            while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS)
            {
                if (!entry.is_directory && (entry.file_id.file_id == file_id))
                    break;
            }
            len = entry.name_len + 1;
            MI_CpuCopy8(entry.name, dst + total - len, len);
            total -= len;
        }
        else
        {
            MI_WriteByte(dst + total - 1, '\0');
            total -= 1;
        }
        if (id != 0)
        {
            do
            {
                FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = FALSE;
                MI_WriteByte(dst + total - 1, '/');
                total -= 1;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS)
                {
                    if (entry.is_directory && (entry.dir_id.own_id == id))
                    {
                        len = entry.name_len;
                        MI_CpuCopy8(entry.name, dst + total - len, len);
                        total -= len;
                        break;
                    }
                }
                id = tmp.prop.dir.pos.own_id;
            }
            while (id != 0);
        }
    }

    return FS_RESULT_SUCCESS;
}

ARM_FUNC FSResult FSi_OpenFileFastCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const FSFileID *p_id = &p_file->arg.openfilefast.id;
    const u32 index = p_id->file_id;
    FSResult ret;

    {
        u32 pos = (u32)(index * sizeof(FSArchiveFAT));
        if (pos >= p_arc->fat_size)
            return FS_RESULT_FAILURE;
        else
        {
            FSArchiveFAT fat;
            FSiSyncReadParam param;
            param.arc = p_arc;
            param.pos = p_arc->fat + pos;
            ret = FSi_ReadTable(&param, &fat, sizeof(fat));
            if (ret != FS_RESULT_SUCCESS)
                return ret;
            p_file->arg.openfiledirect.top = fat.top;
            p_file->arg.openfiledirect.bottom = fat.bottom;
            p_file->arg.openfiledirect.index = index;
            return FSi_TranslateCommand(p_file, FS_COMMAND_OPENFILEDIRECT);
        }
    }
}

ARM_FUNC FSResult FSi_OpenFileDirectCommand(FSFile * p_file)
{
    p_file->prop.file.top = p_file->arg.openfiledirect.top;
    p_file->prop.file.pos = p_file->arg.openfiledirect.top;
    p_file->prop.file.bottom = p_file->arg.openfiledirect.bottom;
    p_file->prop.file.own_id = p_file->arg.openfiledirect.index;
    return FS_RESULT_SUCCESS;
}

ARM_FUNC FSResult FSi_CloseFileCommand(FSFile * p_file)
{
    return FS_RESULT_SUCCESS;
}
