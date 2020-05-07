#ifndef NITRO_FS_COMMAND_H_
#define NITRO_FS_COMMAND_H_

#include "FS_file.h"

extern FSResult (*const fsi_default_command[])(FSFile *);

void FSi_ReleaseCommand(FSFile * file, FSResult signal);
FSResult FSi_TranslateCommand(FSFile * file, FSCommandType command);

#endif //NITRO_FS_COMMAND_H_
