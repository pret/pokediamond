#ifndef GUARD_GXCOMMON_H
#define GUARD_GXCOMMON_H

typedef u16 GXRgb;
#define GXRGB_ASSERT(gxrgb)       SDK_ASSERT(((gxrgb) & 0x8000) == 0)
#define GX_RGB_R_SHIFT            (0)
#define GX_RGB_R_MASK             (0x001f)
#define GX_RGB_G_SHIFT            (5)
#define GX_RGB_G_MASK             (0x03e0)
#define GX_RGB_B_SHIFT            (10)
#define GX_RGB_B_MASK             (0x7c00)
#define GX_RGB(r, g, b)           ((GXRgb)(((r) << GX_RGB_R_SHIFT) | \
                                           ((g) << GX_RGB_G_SHIFT) | \
                                           ((b) << GX_RGB_B_SHIFT)))

#define GX_RGB_BLACK              (GX_RGB(0, 0, 0))
#define GX_RGB_WHITE              (GX_RGB(31, 31, 31))

typedef u16 GXRgba;
#define GX_RGBA_R_SHIFT           (0)
#define GX_RGBA_R_MASK            (0x001f)
#define GX_RGBA_G_SHIFT           (5)
#define GX_RGBA_G_MASK            (0x03e0)
#define GX_RGBA_B_SHIFT           (10)
#define GX_RGBA_B_MASK            (0x7c00)
#define GX_RGBA_A_SHIFT           (15)
#define GX_RGBA_A_MASK            (0x8000)
#define GX_RGBA(r, g, b, a)       ((GXRgba)(((r) << GX_RGBA_R_SHIFT) | \
                                            ((g) << GX_RGBA_G_SHIFT) | \
                                            ((b) << GX_RGBA_B_SHIFT) | \
                                            ((a) << GX_RGBA_A_SHIFT)))
#endif //GUARD_GXCOMMON_H
