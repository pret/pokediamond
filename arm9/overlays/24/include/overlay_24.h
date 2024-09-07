#ifndef POKEDIAMOND_OVERLAY_24_H
#define POKEDIAMOND_OVERLAY_24_H

typedef enum {
    STYLUS_TYPE_ERASE = 0,
    STYLUS_TYPE_DRAW = 1,
} StylusType;

typedef enum {
    MEMO_PAD_PIXEL_TYPE_FILLED = 1,
    MEMO_PAD_PIXEL_TYPE_EMPTY = 4,
} MemoPadPixelType;

typedef struct MemoPadDrawState MemoPadDrawState;
struct MemoPadDrawState
{
    StylusType stylusType;
    u32 lastModifiedX;
    u32 lastModifiedY;
    u8 pixelData[78][75];
    u16 unk16E6;
    u32 unk16E8;
};

typedef struct MemoPadDisplayHandler MemoPadDisplayHandler;
struct MemoPadDisplayHandler
{
    MemoPadDrawState* drawState;
    BgConfig* config;
    u32 unk8;
    u8 unkC[0x44];
    u32 unk50;
    u8 unk54[0x14];
    u32* unk68[2];
    Window *window;
};

typedef struct MemoPadAppHandler MemoPadAppHandler;
struct MemoPadAppHandler
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u32 unk4;
    MemoPadDrawState drawState;
    MemoPadDisplayHandler* unk16F4;
    u32 unk16F8;
    u32 unk16FC;
};

BOOL ov24_02254854(MemoPadAppHandler**, int, int, int);
BOOL ov24_0225489C(MemoPadAppHandler*, u32, u32, u32);
void ov24_022548F4(MemoPadAppHandler*);
void ov24_02254918(void*, MemoPadAppHandler*);
void ov24_02254960(int, int, int, MemoPadAppHandler*);
void ov24_02254990(MemoPadAppHandler*);
void ov24_02254998(MemoPadAppHandler*, u8);
BOOL ov24_022549AC(MemoPadAppHandler*);
BOOL ov24_022549F8(MemoPadAppHandler*);
BOOL ov24_02254A70(MemoPadAppHandler*);
BOOL ov24_02254AD4(MemoPadAppHandler*);
void ov24_02254B20(MemoPadAppHandler*, u32, u32, u32, u32);
BOOL ov24_02254C64(MemoPadAppHandler*);
BOOL ov24_02254CA0(MemoPadDisplayHandler**, MemoPadDrawState*);
BOOL ov24_02254D00(MemoPadDisplayHandler*);
void ov24_02254D48(MemoPadDisplayHandler*);
void ov24_02254D8C(MemoPadDisplayHandler*, u32);
BOOL ov24_02254DB0(MemoPadDisplayHandler*, u8);
BOOL ov24_02254DBC(MemoPadDisplayHandler*);
void ov24_02254DC8(void*);
void ov24_02254DDC(void*, void*);
void ov24_02254EE0(u32, void*);
void ov24_02254F28(int, void*);
void ov24_02254F40(u32 arg0, void* arg1);
void ov24_02255038(u32 arg0, void* arg1);
void ov24_02255050(u32 arg0, void* arg1);
void ov24_02255078(MemoPadDisplayHandler* arg0);
void ov24_022550D4(MemoPadDisplayHandler* arg0);

#endif //POKEDIAMOND_OVERLAY_24_H
