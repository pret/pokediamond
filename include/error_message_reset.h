#ifndef POKEDIAMOND_ERROR_MESSAGE_RESET_H
#define POKEDIAMOND_ERROR_MESSAGE_RESET_H

#include "global.h"
#include "heap.h"
#include "SPI_pm.h"
#include "game_init.h"
#include "msgdata.h"
#include "text.h"



struct GraphicsBanks
{
    s32 bg;
    s32 bgextpltt;
    s32 subbg;
    s32 subbgextpltt;
    s32 obj;
    s32 objextpltt;
    s32 subobj;
    s32 subobjextpltt;
    s32 tex;
    s32 texpltt;
};


struct GraphicsModes {
    u32 mode1;
    u32 mode2;
    u32 mode3;
    u32 mode4;
};


void VBlankHandler();
void PrintErrorMessageAndReset();

#endif //POKEDIAMOND_ERROR_MESSAGE_RESET_H
