#ifndef POKEDIAMOND_OVERLAY_24_H
#define POKEDIAMOND_OVERLAY_24_H

typedef enum {
    TOUCH_TYPE_ERASE = 0,
    TOUCH_TYPE_DRAW = 1,
} TouchType;

typedef enum {
    MEMO_PAD_PIXEL_TYPE_FILLED = 1,
    MEMO_PAD_PIXEL_TYPE_EMPTY = 4,
} MemoPadPixelType;

typedef struct MemoPadDrawState
{
    TouchType touchType;
    u32 lastModifiedX;
    u32 lastModifiedY;
    u8 pixelData[78][75];
    u16 padding;
    u32 unk16E8;
} MemoPadDrawState;

typedef struct MemoPadDisplayHandler
{
    MemoPadDrawState *drawState;
    BgConfig *config;
    u32 unk8;
    u8 unkC[0x44];
    u32 unk50;
    u8 unk54[0x14];
    u32 *unk68[2];
    Window *window;
} MemoPadDisplayHandler;

typedef struct MemoPadAppHandler
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 touchHeld;
    u32 unk4;
    MemoPadDrawState drawState;
    MemoPadDisplayHandler *displayHandler;
    u32 unk16F8;
    u32 unk16FC;
} MemoPadAppHandler;

BOOL ov24_02254854(MemoPadAppHandler **appHandlerOut, s32 arg1, s32 arg2, s32 arg3);
BOOL ov24_0225489C(MemoPadAppHandler *appHandler, u32 arg1, u32 arg2, u32 arg3);
void ov24_022548F4(MemoPadAppHandler *appHandler);
void ov24_02254918(void *arg0, MemoPadAppHandler *appHandler);
void ov24_02254960(s32 arg0, s32 arg1, s32 arg2, MemoPadAppHandler *appHandler);
void ov24_02254990(MemoPadAppHandler *appHandler);
void ov24_02254998(MemoPadAppHandler *appHandler, u8 arg1);
BOOL ov24_022549AC(MemoPadAppHandler *appHandler);
BOOL ov24_022549F8(MemoPadAppHandler *appHandler);
BOOL ov24_02254A70(MemoPadAppHandler *appHandler);
BOOL ov24_02254AD4(MemoPadAppHandler *appHandler);
void ov24_02254B20(MemoPadAppHandler *appHandler, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
BOOL ov24_02254C64(MemoPadAppHandler *appHandler);
BOOL ov24_02254CA0(MemoPadDisplayHandler **displayHandlerOut, MemoPadDrawState *drawState);
BOOL ov24_02254D00(MemoPadDisplayHandler *displayHandler);
void ov24_02254D48(MemoPadDisplayHandler *displayHandler);
void ov24_02254D8C(MemoPadDisplayHandler *displayHandler, u32 arg1);
BOOL ov24_02254DB0(MemoPadDisplayHandler *displayHandler, u8 arg1);
BOOL ov24_02254DBC(MemoPadDisplayHandler *displayHandler);
void ov24_02254DC8(void *arg0);
void ov24_02254DDC(void *arg0, void *arg1);
void ov24_02254EE0(u32 arg0, void *arg1);
void ov24_02254F28(s32 arg0, void *arg1);
void ov24_02254F40(u32 arg0, void *arg1);
void ov24_02255038(u32 arg0, void *arg1);
void ov24_02255050(u32 arg0, void *arg1);
void ov24_02255078(MemoPadDisplayHandler *displayHandler);
void ov24_022550D4(MemoPadDisplayHandler *displayHandler);

#endif //POKEDIAMOND_OVERLAY_24_H
