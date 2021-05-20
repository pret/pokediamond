#ifndef POKEDIAMOND_ERROR_MESSAGE_RESET_H
#define POKEDIAMOND_ERROR_MESSAGE_RESET_H

#include "global.h"
#include "heap.h"
#include "SPI_pm.h"
#include "game_init.h"
#include "msgdata.h"
#include "text.h"


THUMB_FUNC void VBlankHandler();
THUMB_FUNC void PrintErrorMessageAndReset();

#endif //POKEDIAMOND_ERROR_MESSAGE_RESET_H
