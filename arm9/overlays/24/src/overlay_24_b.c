#include "global.h"
#include "bg_window.h"
#include "unk_0200CA44.h"
#include "gf_gfx_loader.h"
#include "overlay_24.h"

const WindowTemplate ov24_0225510C = {
    0x07, 0x02, 0x02, 0x14, 0x13, 0x00, 0x0C
};
const BgTemplate ov24_02255130 = {
    0, 0, 0x800, 0, 1, 0, 0xf, 0, 0, 3, 0, 0, 0
};
const BgTemplate ov24_02255114 = {
    0x0,
    0x0,
    0x0,
    0x0,
    1,
    0,
    0xe,
    0,
    0,
    2,
    0,
    0,
    0
};
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