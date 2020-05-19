#ifndef GUARD_GX_BGCNT_H
#define GUARD_GX_BGCNT_H

void *G2_GetBG0ScrPtr();
void *G2S_GetBG0ScrPtr();
void *G2_GetBG1ScrPtr();
void *G2S_GetBG1ScrPtr();
void *G2_GetBG2ScrPtr();
void *G2S_GetBG2ScrPtr();
void *G2_GetBG3ScrPtr();
void *G2S_GetBG3ScrPtr();
void *G2_GetBG0CharPtr();
void *G2S_GetBG0CharPtr();
void *G2_GetBG1CharPtr();
void *G2S_GetBG1CharPtr();
void *G2_GetBG2CharPtr();
void *G2S_GetBG2CharPtr();
void *G2_GetBG3CharPtr();
void *G2S_GetBG3CharPtr();

typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     charBase:4;
        u16     mosaic:1;
        u16     colorMode:1;
        u16     screenBase:5;
        u16     bgExtPltt:1;
        u16     screenSize:2;
    };
}
GXBg01Control;

typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     charBase:4;
        u16     mosaic:1;
        u16     colorMode:1;
        u16     screenBase:5;
        u16     _reserve:1;
        u16     screenSize:2;
    };
}
GXBg23ControlText;

typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     charBase:4;
        u16     mosaic:1;
        u16     _reserve:1;
        u16     screenBase:5;
        u16     areaOver:1;
        u16     screenSize:2;
    };
}
GXBg23ControlAffine;

typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     _reserve1:1;
        u16     charBase:3;
        u16     mosaic:1;
        u16     _reserve2:1;
        u16     screenBase:5;
        u16     areaOver:1;
        u16     screenSize:2;
    };
}
GXBg23Control256x16Pltt;


typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     _reserve1:4;
        u16     mosaic:1;
        u16     _reserve2:1;
        u16     screenBase:5;
        u16     areaOver:1;
        u16     screenSize:2;
    };
}
GXBg23Control256Bmp, GXBg23ControlDCBmp;

typedef union
{
    u16     raw;
    struct
    {
        u16     priority:2;
        u16     _reserve1:4;
        u16     mosaic:1;
        u16     _reserve2:6;
        u16     areaOver:1;
        u16     screenSize:2;
    };
}
GXBg2ControlLargeBmp;



typedef enum
{
    GX_BG_SCRSIZE_TEXT_256x256 = 0,
    GX_BG_SCRSIZE_TEXT_512x256 = 1,
    GX_BG_SCRSIZE_TEXT_256x512 = 2,
    GX_BG_SCRSIZE_TEXT_512x512 = 3
}
GXBGScrSizeText;

typedef enum
{
    GX_BG_SCRSIZE_AFFINE_128x128 = 0,
    GX_BG_SCRSIZE_AFFINE_256x256 = 1,
    GX_BG_SCRSIZE_AFFINE_512x512 = 2,
    GX_BG_SCRSIZE_AFFINE_1024x1024 = 3
}
GXBGScrSizeAffine;

typedef enum
{
    GX_BG_SCRSIZE_256x16PLTT_128x128 = 0,
    GX_BG_SCRSIZE_256x16PLTT_256x256 = 1,
    GX_BG_SCRSIZE_256x16PLTT_512x512 = 2,
    GX_BG_SCRSIZE_256x16PLTT_1024x1024 = 3
}
GXBGScrSize256x16Pltt;

typedef enum
{
    GX_BG_SCRSIZE_256BMP_128x128 = 0,
    GX_BG_SCRSIZE_256BMP_256x256 = 1,
    GX_BG_SCRSIZE_256BMP_512x256 = 2,
    GX_BG_SCRSIZE_256BMP_512x512 = 3
}
GXBGScrSize256Bmp;

typedef enum
{
    GX_BG_SCRSIZE_DCBMP_128x128 = 0,
    GX_BG_SCRSIZE_DCBMP_256x256 = 1,
    GX_BG_SCRSIZE_DCBMP_512x256 = 2,
    GX_BG_SCRSIZE_DCBMP_512x512 = 3
}
GXBGScrSizeDcBmp;

typedef enum
{
    GX_BG_SCRSIZE_LARGEBMP_512x1024 = 0,
    GX_BG_SCRSIZE_LARGEBMP_1024x512 = 1
}
GXBGScrSizeLargeBmp;

typedef enum
{
    GX_BG_COLORMODE_16 = 0,
    GX_BG_COLORMODE_256 = 1
}
GXBGColorMode;

typedef enum
{
    GX_BG_AREAOVER_XLU = 0,
    GX_BG_AREAOVER_REPEAT = 1
}
GXBGAreaOver;

typedef enum
{
    GX_BG_CHARBASE_0x00000 = 0,
    GX_BG_CHARBASE_0x04000 = 1,
    GX_BG_CHARBASE_0x08000 = 2,
    GX_BG_CHARBASE_0x0c000 = 3,
    GX_BG_CHARBASE_0x10000 = 4,
    GX_BG_CHARBASE_0x14000 = 5,
    GX_BG_CHARBASE_0x18000 = 6,
    GX_BG_CHARBASE_0x1c000 = 7,
    GX_BG_CHARBASE_0x20000 = 8,
    GX_BG_CHARBASE_0x24000 = 9,
    GX_BG_CHARBASE_0x28000 = 10,
    GX_BG_CHARBASE_0x2c000 = 11,
    GX_BG_CHARBASE_0x30000 = 12,
    GX_BG_CHARBASE_0x34000 = 13,
    GX_BG_CHARBASE_0x38000 = 14,
    GX_BG_CHARBASE_0x3c000 = 15
}
GXBGCharBase;

typedef enum
{
    GX_BG_SCRBASE_0x0000 = 0,
    GX_BG_SCRBASE_0x0800 = 1,
    GX_BG_SCRBASE_0x1000 = 2,
    GX_BG_SCRBASE_0x1800 = 3,
    GX_BG_SCRBASE_0x2000 = 4,
    GX_BG_SCRBASE_0x2800 = 5,
    GX_BG_SCRBASE_0x3000 = 6,
    GX_BG_SCRBASE_0x3800 = 7,
    GX_BG_SCRBASE_0x4000 = 8,
    GX_BG_SCRBASE_0x4800 = 9,
    GX_BG_SCRBASE_0x5000 = 10,
    GX_BG_SCRBASE_0x5800 = 11,
    GX_BG_SCRBASE_0x6000 = 12,
    GX_BG_SCRBASE_0x6800 = 13,
    GX_BG_SCRBASE_0x7000 = 14,
    GX_BG_SCRBASE_0x7800 = 15,
    GX_BG_SCRBASE_0x8000 = 16,
    GX_BG_SCRBASE_0x8800 = 17,
    GX_BG_SCRBASE_0x9000 = 18,
    GX_BG_SCRBASE_0x9800 = 19,
    GX_BG_SCRBASE_0xa000 = 20,
    GX_BG_SCRBASE_0xa800 = 21,
    GX_BG_SCRBASE_0xb000 = 22,
    GX_BG_SCRBASE_0xb800 = 23,
    GX_BG_SCRBASE_0xc000 = 24,
    GX_BG_SCRBASE_0xc800 = 25,
    GX_BG_SCRBASE_0xd000 = 26,
    GX_BG_SCRBASE_0xd800 = 27,
    GX_BG_SCRBASE_0xe000 = 28,
    GX_BG_SCRBASE_0xe800 = 29,
    GX_BG_SCRBASE_0xf000 = 30,
    GX_BG_SCRBASE_0xf800 = 31
}
GXBGScrBase;

typedef enum
{
    GX_BG_BMPSCRBASE_0x00000 = 0,
    GX_BG_BMPSCRBASE_0x04000 = 1,
    GX_BG_BMPSCRBASE_0x08000 = 2,
    GX_BG_BMPSCRBASE_0x0c000 = 3,
    GX_BG_BMPSCRBASE_0x10000 = 4,
    GX_BG_BMPSCRBASE_0x14000 = 5,
    GX_BG_BMPSCRBASE_0x18000 = 6,
    GX_BG_BMPSCRBASE_0x1c000 = 7,
    GX_BG_BMPSCRBASE_0x20000 = 8,
    GX_BG_BMPSCRBASE_0x24000 = 9,
    GX_BG_BMPSCRBASE_0x28000 = 10,
    GX_BG_BMPSCRBASE_0x2c000 = 11,
    GX_BG_BMPSCRBASE_0x30000 = 12,
    GX_BG_BMPSCRBASE_0x34000 = 13,
    GX_BG_BMPSCRBASE_0x38000 = 14,
    GX_BG_BMPSCRBASE_0x3c000 = 15,
    GX_BG_BMPSCRBASE_0x40000 = 16,
    GX_BG_BMPSCRBASE_0x44000 = 17,
    GX_BG_BMPSCRBASE_0x48000 = 18,
    GX_BG_BMPSCRBASE_0x4c000 = 19,
    GX_BG_BMPSCRBASE_0x50000 = 20,
    GX_BG_BMPSCRBASE_0x54000 = 21,
    GX_BG_BMPSCRBASE_0x58000 = 22,
    GX_BG_BMPSCRBASE_0x5c000 = 23,
    GX_BG_BMPSCRBASE_0x60000 = 24,
    GX_BG_BMPSCRBASE_0x64000 = 25,
    GX_BG_BMPSCRBASE_0x68000 = 26,
    GX_BG_BMPSCRBASE_0x6c000 = 27,
    GX_BG_BMPSCRBASE_0x70000 = 28,
    GX_BG_BMPSCRBASE_0x74000 = 29,
    GX_BG_BMPSCRBASE_0x78000 = 30,
    GX_BG_BMPSCRBASE_0x7c000 = 31
}
GXBGBmpScrBase;

typedef enum
{
    GX_BG_EXTPLTT_01 = 0,
    GX_BG_EXTPLTT_23 = 1
}
GXBGExtPltt;

//GX_capture
typedef enum
{
    GX_CAPTURE_DEST_VRAM_A_0x00000 = 0,
    GX_CAPTURE_DEST_VRAM_B_0x00000 = 1,
    GX_CAPTURE_DEST_VRAM_C_0x00000 = 2,
    GX_CAPTURE_DEST_VRAM_D_0x00000 = 3,

    GX_CAPTURE_DEST_VRAM_A_0x08000 = 4,
    GX_CAPTURE_DEST_VRAM_B_0x08000 = 5,
    GX_CAPTURE_DEST_VRAM_C_0x08000 = 6,
    GX_CAPTURE_DEST_VRAM_D_0x08000 = 7,

    GX_CAPTURE_DEST_VRAM_A_0x10000 = 8,
    GX_CAPTURE_DEST_VRAM_B_0x10000 = 9,
    GX_CAPTURE_DEST_VRAM_C_0x10000 = 10,
    GX_CAPTURE_DEST_VRAM_D_0x10000 = 11,

    GX_CAPTURE_DEST_VRAM_A_0x18000 = 12,
    GX_CAPTURE_DEST_VRAM_B_0x18000 = 13,
    GX_CAPTURE_DEST_VRAM_C_0x18000 = 14,
    GX_CAPTURE_DEST_VRAM_D_0x18000 = 15
}
GXCaptureDest;

typedef enum
{
    GX_CAPTURE_SIZE_128x128 = 0,
    GX_CAPTURE_SIZE_256x64 = 1,
    GX_CAPTURE_SIZE_256x128 = 2,
    GX_CAPTURE_SIZE_256x192 = 3
}
GXCaptureSize;

typedef enum
{
    GX_CAPTURE_SRCA_2D3D = 0,
    GX_CAPTURE_SRCA_3D = 1
}
GXCaptureSrcA;

typedef enum
{
    GX_CAPTURE_SRCB_VRAM_0x00000 = 0,
    GX_CAPTURE_SRCB_MRAM = 1,
    GX_CAPTURE_SRCB_VRAM_0x08000 = 2,
    GX_CAPTURE_SRCB_VRAM_0x10000 = 4,
    GX_CAPTURE_SRCB_VRAM_0x18000 = 6
}
GXCaptureSrcB;

typedef enum
{
    GX_CAPTURE_MODE_A = 0,
    GX_CAPTURE_MODE_B = 1,
    GX_CAPTURE_MODE_AB = 2
}
GXCaptureMode;

#endif //GUARD_GX_BGCNT_H
