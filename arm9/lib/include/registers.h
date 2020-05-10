//
// Created by red031000 on 2020-05-06.
//

#ifndef POKEDIAMOND_REGISTERS_H
#define POKEDIAMOND_REGISTERS_H

#include "types.h"

#define HW_REG_BASE                0x04000000
#define REG_VCOUNT_OFFSET          0x006
#define REG_VCOUNT_ADDR            (HW_REG_BASE + REG_VCOUNT_OFFSET)
#define reg_GX_VCOUNT              (*(REGType16v *)REG_VCOUNT_ADDR)

#define REG_KEYINPUT_OFFSET        0x130
#define REG_KEYINPUT_ADDR          (HW_REG_BASE + REG_KEYINPUT_OFFSET)
#define reg_PAD_KEYINPUT           (*(REGType16v *)REG_KEYINPUT_ADDR)

#define REG_DIVCNT_OFFSET          0x280
#define REG_DIVCNT_ADDR            (HW_REG_BASE + REG_DIVCNT_OFFSET)
#define reg_CP_DIVCNT              (*(REGType16v *)REG_DIVCNT_ADDR)

#define REG_DIV_NUMER_OFFSET       0x290
#define REG_DIV_NUMER_ADDR         (HW_REG_BASE + REG_DIV_NUMER_OFFSET)
#define reg_CP_DIV_NUMER           (*(REGType64v *)REG_DIV_NUMER_ADDR)

#define REG_DIV_DENOM_OFFSET       0x298
#define REG_DIV_DENOM_ADDR         (HW_REG_BASE + REG_DIV_DENOM_OFFSET)
#define reg_CP_DIV_DENOM           (*(REGType64v *)REG_DIV_DENOM_ADDR)

#define REG_DIV_RESULT_OFFSET      0x2A0
#define REG_DIV_RESULT_ADDR        (HW_REG_BASE + REG_DIV_RESULT_OFFSET)
#define reg_CP_DIV_RESULT          (*(REGType64v *)REG_DIV_RESULT_ADDR)

#define REG_DIVREM_RESULT_OFFSET   0x2A8
#define REG_DIVREM_RESULT_ADDR     (HW_REG_BASE + REG_DIVREM_RESULT_OFFSET)
#define reg_CP_DIVREM_RESULT       (*(REGType64v *)REG_DIVREM_RESULT_ADDR)

#define REG_SQRTCNT_OFFSET         0x2B0
#define REG_SQRTCNT_ADDR           (HW_REG_BASE + REG_SQRTCNT_OFFSET)
#define reg_CP_SQRTCNT             (*(REGType16v *)REG_SQRTCNT_ADDR)

#define REG_SQRT_RESULT_OFFSET     0x2B4
#define REG_SQRT_RESULT_ADDR       (HW_REG_BASE + REG_SQRT_RESULT_OFFSET)
#define reg_CP_SQRT_RESULT         (*(REGType32v *)REG_SQRT_RESULT_ADDR)

#define REG_SQRT_PARAM_OFFSET      0x2B8
#define REG_SQRT_PARAM_ADDR        (HW_REG_BASE + REG_SQRT_PARAM_OFFSET)
#define reg_CP_SQRT_PARAM          (*(REGType64v *)REG_SQRT_PARAM_ADDR)

#define REG_GXSTAT_OFFSET          0x600
#define REG_GXSTAT_ADDR            (HW_REG_BASE + REG_GXSTAT_OFFSET)
#define reg_G3X_GXSTAT             (*(REGType32v *)REG_GXSTAT_ADDR)

#define REG_PAD_KEYINPUT_L_SHIFT                           9
#define REG_PAD_KEYINPUT_L_SIZE                            1
#define REG_PAD_KEYINPUT_L_MASK                            0x0200

#define REG_PAD_KEYINPUT_R_SHIFT                           8
#define REG_PAD_KEYINPUT_R_SIZE                            1
#define REG_PAD_KEYINPUT_R_MASK                            0x0100

#define REG_PAD_KEYINPUT_DOWN_SHIFT                        7
#define REG_PAD_KEYINPUT_DOWN_SIZE                         1
#define REG_PAD_KEYINPUT_DOWN_MASK                         0x0080

#define REG_PAD_KEYINPUT_UP_SHIFT                          6
#define REG_PAD_KEYINPUT_UP_SIZE                           1
#define REG_PAD_KEYINPUT_UP_MASK                           0x0040

#define REG_PAD_KEYINPUT_LEFT_SHIFT                        5
#define REG_PAD_KEYINPUT_LEFT_SIZE                         1
#define REG_PAD_KEYINPUT_LEFT_MASK                         0x0020

#define REG_PAD_KEYINPUT_RIGHT_SHIFT                       4
#define REG_PAD_KEYINPUT_RIGHT_SIZE                        1
#define REG_PAD_KEYINPUT_RIGHT_MASK                        0x0010

#define REG_PAD_KEYINPUT_START_SHIFT                       3
#define REG_PAD_KEYINPUT_START_SIZE                        1
#define REG_PAD_KEYINPUT_START_MASK                        0x0008

#define REG_PAD_KEYINPUT_SEL_SHIFT                         2
#define REG_PAD_KEYINPUT_SEL_SIZE                          1
#define REG_PAD_KEYINPUT_SEL_MASK                          0x0004

#define REG_PAD_KEYINPUT_B_SHIFT                           1
#define REG_PAD_KEYINPUT_B_SIZE                            1
#define REG_PAD_KEYINPUT_B_MASK                            0x0002

#define REG_PAD_KEYINPUT_A_SHIFT                           0
#define REG_PAD_KEYINPUT_A_SIZE                            1
#define REG_PAD_KEYINPUT_A_MASK                            0x0001

#ifndef SDK_ASM
#define REG_PAD_KEYINPUT_FIELD( l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(l) << REG_PAD_KEYINPUT_L_SHIFT) | \
    ((u32)(r) << REG_PAD_KEYINPUT_R_SHIFT) | \
    ((u32)(down) << REG_PAD_KEYINPUT_DOWN_SHIFT) | \
    ((u32)(up) << REG_PAD_KEYINPUT_UP_SHIFT) | \
    ((u32)(left) << REG_PAD_KEYINPUT_LEFT_SHIFT) | \
    ((u32)(right) << REG_PAD_KEYINPUT_RIGHT_SHIFT) | \
    ((u32)(start) << REG_PAD_KEYINPUT_START_SHIFT) | \
    ((u32)(sel) << REG_PAD_KEYINPUT_SEL_SHIFT) | \
    ((u32)(b) << REG_PAD_KEYINPUT_B_SHIFT) | \
    ((u32)(a) << REG_PAD_KEYINPUT_A_SHIFT))
#endif

#endif //POKEDIAMOND_REGISTERS_H
