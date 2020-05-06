//
// Created by red031000 on 2020-05-06.
//

#ifndef POKEDIAMOND_PXI_FIFO_H
#define POKEDIAMOND_PXI_FIFO_H

#include "function_target.h"

ENUMS_ALWAYS_INT_ON
typedef enum {
    PXI_FIFO_TAG_EX = 0,               // Extension format
    PXI_FIFO_TAG_USER_0,               // for application programmer, use it in free
    PXI_FIFO_TAG_USER_1,               // for application programmer, use it in free
    PXI_FIFO_TAG_SYSTEM,               // SDK inner usage
    PXI_FIFO_TAG_NVRAM,                // NVRAM
    PXI_FIFO_TAG_RTC,                  // RTC
    PXI_FIFO_TAG_TOUCHPANEL,           // Touch Panel
    PXI_FIFO_TAG_SOUND,                // Sound
    PXI_FIFO_TAG_PM,                   // Power Management
    PXI_FIFO_TAG_MIC,                  // Microphone
    PXI_FIFO_TAG_WM,                   // Wireless Manager
    PXI_FIFO_TAG_FS,                   // File System
    PXI_FIFO_TAG_OS,                   // OS
    PXI_FIFO_TAG_CTRDG,                // Cartridge
    PXI_FIFO_TAG_CARD,                 // Card
    PXI_FIFO_TAG_WVR,                  // Control driving wireless library
    PXI_FIFO_TAG_CTRDG_Ex,             // Cartridge Ex
    PXI_MAX_FIFO_TAG = 32              // MAX FIFO TAG
} PXIFifoTag;
ENUMS_ALWAYS_INT_RESET

#endif //POKEDIAMOND_PXI_FIFO_H
