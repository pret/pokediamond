#include "FS_archive.h"
#include "FS_file.h"
#include "FS_command.h"
#include "MI_memory.h"
#include "MI_byteAccess.h"

FSArchive * arc_list = NULL;
FSDirPos current_dir_pos;

u32 FSi_GetPackedName(const char * name, int name_len)
{
    u32 ret = 0;
    if (name_len <= FS_ARCHIVE_NAME_LEN_MAX)
    {
        int i = 0;
        for (; i < name_len; i++)
        {
            u32 c = MI_ReadByte(name + i);
            if (!c)
                break;
            c = (u32)(c - 'A');
            if (c <= (u32)('Z' - 'A'))
                c = (u32)(c + 'a');
            else
                c = (u32)(c + 'A');
            ret |= (u32)(c << (i * 8));
        }
    }
    return ret;
}

FSResult FSi_ReadMemCallback(FSArchive * p_arc, u8 * dest, u32 offset, u32 size)
{
    MI_CpuCopy8((const void *)FS_GetArchiveOffset(p_arc, offset), dest, size);
    return FS_RESULT_SUCCESS;
}

FSResult FSi_WriteMemCallback(FSArchive * p_arc, const u8 * src, u32 offset, u32 size)
{
    MI_CpuCopy8(src, (void *)FS_GetArchiveOffset(p_arc, offset), size);
    return FS_RESULT_SUCCESS;
}

FSResult FSi_ReadMemoryCore(FSArchive * p_arc, u8 * dest, u32 offset, u32 size)
{
    MI_CpuCopy8((const void *)offset, dest, size);
    return FS_RESULT_SUCCESS;
}

FSFile * FSi_NextCommand(FSArchive * p_arc)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();
    if (FSi_IsArchiveCanceling(p_arc))
    {
        FSFile *p, *q;
        p_arc->flag &= ~FS_ARCHIVE_FLAG_CANCELING;
        for (p = p_arc->list.next; p; p = q)
        {
            q = p->link.next;
            if (FS_IsCanceling(p))
            {
                if (p_arc->list.next == p)
                    p_arc->list.next = q;
                FSi_ReleaseCommand(p, FS_RESULT_CANCELED);
                if (!q)
                    q = p_arc->list.next;
            }
        }
    }
    if (!FSi_IsArchiveSuspending(p_arc) && !FS_IsArchiveSuspended(p_arc))
    {
        FSFile * p_file = p_arc->list.next;
        if (p_file != NULL)
        {
            const BOOL is_start = !FSi_IsArchiveRunning(p_arc);
            if (is_start)
                p_arc->flag |= FS_ARCHIVE_FLAG_RUNNING;
            OS_RestoreInterrupts(bak_psr);
            if (is_start)
            {
                if ((p_arc->proc_flag & FS_ARCHIVE_PROC_ACTIVATE) != 0)
                    (*p_arc->proc) (p_file, FS_COMMAND_ACTIVATE);
            }
            bak_psr = OS_DisableInterrupts();
            p_file->stat |= FS_FILE_STATUS_OPERATING;
            if (FS_IsFileSyncMode(p_file))
            {
                OS_WakeupThread(p_file->queue);
                OS_RestoreInterrupts(bak_psr);
                return NULL;
            }
            OS_RestoreInterrupts(bak_psr);
            return p_file;
        }
    }
    if (FSi_IsArchiveRunning(p_arc))
    {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_RUNNING;
        if (p_arc->proc_flag & FS_ARCHIVE_PROC_IDLE)
        {
            FSFile tmp;
            FS_InitFile(&tmp);
            tmp.arc = p_arc;
            (*p_arc->proc)(&tmp, FS_COMMAND_IDLE);
        }
    }
    if (FSi_IsArchiveSuspending(p_arc))
    {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_SUSPENDING;
        p_arc->flag |= FS_ARCHIVE_FLAG_SUSPEND;
        OS_WakeupThread(&p_arc->stat_q);
    }
    OS_RestoreInterrupts(bak_psr);
    return NULL;
}

void FSi_ExecuteAsyncCommand(FSFile * p_file)
{
    FSArchive *const p_arc = p_file->arc;
    while (p_file)
    {
        OSIntrMode bak_psr = OS_DisableInterrupts();
        p_file->stat |= FS_FILE_STATUS_OPERATING;
        if (FS_IsFileSyncMode(p_file))
        {
            OS_WakeupThread(p_file->queue);
            OS_RestoreInterrupts(bak_psr);
            break;
        }
        p_file->stat |= FS_FILE_STATUS_ASYNC;
        OS_RestoreInterrupts(bak_psr);
        if (FSi_TranslateCommand(p_file, p_file->command) == FS_RESULT_PROC_ASYNC)
            break;
        p_file = FSi_NextCommand(p_arc);
    }
}

BOOL FSi_ExecuteSyncCommand(FSFile * p_file)
{
    FSFile * p_target;
    FSResult ret = FSi_TranslateCommand(p_file, p_file->command);
    FSi_ReleaseCommand(p_file, ret);
    p_target = FSi_NextCommand(p_file->arc);
    if (p_target)
        FSi_ExecuteAsyncCommand(p_target);
    return FS_IsSucceeded(p_file);
}
