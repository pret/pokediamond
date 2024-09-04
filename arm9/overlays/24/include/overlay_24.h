#ifndef POKEDIAMOND_OVERLAY_24_H
#define POKEDIAMOND_OVERLAY_24_H

typedef struct UnkSubStructOverlay24_1 UnkSubStructOverlay24_1;
struct UnkSubStructOverlay24_1
{
    u32 unk0;
    u32 lastModifiedX;
    u32 lastModifiedY;
    u8 pixelData[78][75];
    u16 unk16E6;
    u32 unk16E8;
};

typedef struct UnkSubStructOverlay24 UnkSubStructOverlay24;
struct UnkSubStructOverlay24
{
    UnkSubStructOverlay24_1* unk0;
    BgConfig* config;
    u32 unk8;
    u8 unkC[0x44];
    u32 unk50;
    u8 unk54[0x14];
    u32* unk68[2];
    Window *window;
};

typedef struct UnkStructOverlay24 UnkStructOverlay24;
struct UnkStructOverlay24
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u32 unk4;
    UnkSubStructOverlay24_1 unk8;
    UnkSubStructOverlay24* unk16F4;
    u32 unk16F8;
    u32 unk16FC;
};

BOOL ov24_02254854(UnkStructOverlay24**, int, int, int);
BOOL ov24_0225489C(UnkStructOverlay24*, u32, u32, u32);
void ov24_022548F4(UnkStructOverlay24*);
void ov24_02254918(void*, UnkStructOverlay24*);
void ov24_02254960(int, int, int, UnkStructOverlay24*);
void ov24_02254990(UnkStructOverlay24*);
void ov24_02254998(UnkStructOverlay24*, u8);
BOOL ov24_022549AC(UnkStructOverlay24*);
BOOL ov24_022549F8(UnkStructOverlay24*);
BOOL ov24_02254A70(UnkStructOverlay24*);
BOOL ov24_02254AD4(UnkStructOverlay24*);
void ov24_02254B20(UnkStructOverlay24*, u32, u32, u32, u32);
BOOL ov24_02254C64(UnkStructOverlay24*);
BOOL ov24_02254CA0(UnkSubStructOverlay24**, UnkSubStructOverlay24_1*);
BOOL ov24_02254D00(UnkSubStructOverlay24*);
void ov24_02254D48(UnkSubStructOverlay24*);
void ov24_02254D8C(UnkSubStructOverlay24*, u32);
BOOL ov24_02254DB0(UnkSubStructOverlay24*, u8);
BOOL ov24_02254DBC(UnkSubStructOverlay24*);
void ov24_02254DC8(void*);
void ov24_02254DDC(void*, void*);
void ov24_02254EE0(u32, void*);
void ov24_02254F28(int, void*);
void ov24_02254F40(u32 arg0, void* arg1);
void ov24_02255038(u32 arg0, void* arg1);
void ov24_02255050(u32 arg0, void* arg1);
void ov24_02255078(UnkSubStructOverlay24* arg0);
void ov24_022550D4(UnkSubStructOverlay24* arg0);

#endif //POKEDIAMOND_OVERLAY_24_H
