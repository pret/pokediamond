#include "global.h"
#include "bg_window.h"
#include "unk_0200CA44.h"
#include "gf_gfx_loader.h"
#include "overlay_24.h"

const WindowTemplate ov24_0225510C = {
    .bgId = GF_BG_LYR_SUB_3,
    .left = 2,
    .top = 2,
    .width = 20,
    .height = 19,
    .palette = 0,
    .baseTile = 12,
};
const BgTemplate ov24_02255130 = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = 1,
    .colorMode = 0,
    .screenBase = GX_BG_SCRBASE_0x7800,
    .charBase = GX_BG_CHARBASE_0x00000,
    .bgExtPltt = 0,
    .priority = 3,
    .areaOver = 0,
    .dummy = 0,
    .mosaic = 0,
};
const BgTemplate ov24_02255114 = {
    .x = 0,
    .y = 0,
    .bufferSize = 0,
    .baseTile = 0,
    .size = 1,
    .colorMode = 0,
    .screenBase = GX_BG_SCRBASE_0x7000,
    .charBase = GX_BG_CHARBASE_0x00000,
    .bgExtPltt = 0,
    .priority = 2,
    .areaOver = 0,
    .dummy = 0,
    .mosaic = 0,
};
// TODO: types
const u32 ov24_0225514C[2][4] = {
    {
        0xC0000, 0x38000, 0x2000000, 0x0
    },
    {
        0xC0000, 0x88000, 0x2000003, 0x0
    }
};
const u32 ov24_0225516C[] = {
	0x00, (u32)ov24_02254DDC, 0x00,
	0x01, (u32)ov24_02254EE0, 0x00,
	0x02, (u32)ov24_02254F28, 0x00,
	0x03, (u32)ov24_02254F40, 0x00,
	0x04, (u32)ov24_02255038, 0x00,
	0x05, (u32)ov24_02255050, 0x00,
	0x00, 0x00000000, 0x00,
};