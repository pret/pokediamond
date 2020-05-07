#ifndef NITRO_FS_COMMAND_H_
#define NITRO_FS_COMMAND_H_

#include "FS_file.h"

void FSi_ReleaseCommand(FSFile * file, FSResult signal);
FSResult FSi_TranslateCommand(FSFile * file, FSCommandType command);

#endif //NITRO_FS_COMMAND_H_
