#ifndef POKEDIAMOND_START_MENU_H
#define POKEDIAMOND_START_MENU_H

#include "task.h"

typedef enum StartMenuState {
    START_MENU_STATE_INIT,
    START_MENU_STATE_INIT_FORCE_CURSOR,
    START_MENU_STATE_2,
    START_MENU_STATE_HANDLE_INPUT,
    START_MENU_STATE_WAIT_FADE,
    START_MENU_STATE_WAIT_APP,
    START_MENU_STATE_SAVE,
    START_MENU_STATE_7,
    START_MENU_STATE_EVOLUTION,
    START_MENU_STATE_WAIT_EVOLUTION,
    START_MENU_STATE_10,
    START_MENU_STATE_11,
    START_MENU_STATE_12,
    START_MENU_STATE_13,
    START_MENU_STATE_14,
    START_MENU_STATE_RETURN,
    START_MENU_STATE_CLOSE,
    START_MENU_STATE_RETURN_WAIT_FADE,
    START_MENU_STATE_18,
    START_MENU_STATE_19,
    START_MENU_STATE_20,
} StartMenuState;

// TODO: fill out
typedef struct StartMenuTaskData {
    u8 filler0[0x2A];
    u16 state;
    u8 filler1[0x19C];
    TaskFunc exitTaskFunc;
    u8 filler2[0x2C];
    void *exitTaskEnvironment;
    void *exitTaskEnvironment2;
    u8 filler3[0x4];
} StartMenuTaskData;

#endif // POKEDIAMOND_START_MENU_H
