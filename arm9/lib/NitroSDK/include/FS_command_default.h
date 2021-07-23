#ifndef POKEDIAMOND_FS_COMMAND_DEFAULT_H
#define POKEDIAMOND_FS_COMMAND_DEFAULT_H

#include "nitro/types.h"
#include "FS_archive.h"

typedef struct
{
    FSArchive *arc;
    u32 pos;
} FSiSyncReadParam;


u32 FSi_StrNICmp(const char * str1, const char * str2, u32 len);
FSResult FSi_ReadTable(FSiSyncReadParam * p, void * dst, u32 len);
FSResult FSi_SeekDirDirect(FSFile * p_dir, u32 id);
FSResult FSi_ReadFileCommand(FSFile * p_file);
FSResult FSi_WriteFileCommand(FSFile * p_file);
FSResult FSi_SeekDirCommand(FSFile * p_dir);
FSResult FSi_ReadDirCommand(FSFile *p_dir);
FSResult FSi_FindPathCommand(FSFile *p_dir);
FSResult FSi_GetPathCommand(FSFile *p_file);
FSResult FSi_OpenFileFastCommand(FSFile * p_file);
FSResult FSi_OpenFileDirectCommand(FSFile * p_file);
FSResult FSi_CloseFileCommand(FSFile * p_file);

#endif //POKEDIAMOND_FS_COMMAND_DEFAULT_H
