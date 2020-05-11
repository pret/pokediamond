//
// Created by red031000 on 2020-05-06.
//

#ifndef POKEDIAMOND_REGISTERS_H
#define POKEDIAMOND_REGISTERS_H

#include "types.h"

#define reg_GX_VCOUNT              (*(REGType16v *)0x4000006)

#define reg_MI_DMA0SAD             (*(REGType32v *)0x40000b0)
#define reg_MI_DMA0DAD             (*(REGType32v *)0x40000b4)
#define reg_MI_DMA0CNT             (*(REGType32v *)0x40000b8)
#define reg_MI_DMA1SAD             (*(REGType32v *)0x40000bc)
#define reg_MI_DMA1DAD             (*(REGType32v *)0x40000c0)
#define reg_MI_DMA1CNT             (*(REGType32v *)0x40000c4)
#define reg_MI_DMA2SAD             (*(REGType32v *)0x40000c8)
#define reg_MI_DMA2DAD             (*(REGType32v *)0x40000cc)
#define reg_MI_DMA2CNT             (*(REGType32v *)0x40000d0)
#define reg_MI_DMA3SAD             (*(REGType32v *)0x40000d4)
#define reg_MI_DMA3DAD             (*(REGType32v *)0x40000d8)
#define reg_MI_DMA3CNT             (*(REGType32v *)0x40000dc)
#define reg_MI_DMA0_CLR_DATA       (*(REGType32v *)0x40000e0)
#define reg_MI_DMA1_CLR_DATA       (*(REGType32v *)0x40000e4)
#define reg_MI_DMA2_CLR_DATA       (*(REGType32v *)0x40000e8)
#define reg_MI_DMA3_CLR_DATA       (*(REGType32v *)0x40000ec)

#define reg_PAD_KEYINPUT           (*(REGType16v *)0x4000130)

#define reg_MI_MCCNT0              (*(REGType16v *)0x40001a0)
#define reg_MI_MCD0                (*(REGType16v *)0x40001a2)
#define reg_MI_MCCNT1              (*(REGType32v *)0x40001a4)
#define reg_MI_MCCMD0              (*(REGType32v *)0x40001a8)
#define reg_MI_MCCMD1              (*(REGType32v *)0x40001ac)
#define reg_MI_EXMEMCNT            (*(REGType16v *)0x4000204)

#define reg_CP_DIVCNT              (*(REGType16v *)0x4000280)
#define reg_CP_DIV_NUMER           (*(REGType64v *)0x4000290)
#define reg_CP_DIV_DENOM           (*(REGType64v *)0x4000298)
#define reg_CP_DIV_RESULT          (*(REGType64v *)0x40002A0)
#define reg_CP_DIVREM_RESULT       (*(REGType64v *)0x40002A8)
#define reg_CP_SQRTCNT             (*(REGType16v *)0x40002B0)
#define reg_CP_SQRT_RESULT         (*(REGType32v *)0x40002B4)
#define reg_CP_SQRT_PARAM          (*(REGType64v *)0x40002B8)

#define reg_G3_MTX_MODE            (*(REGType32v *)0x4000440)
#define reg_G3_MTX_PUSH            (*(REGType32v *)0x4000444)
#define reg_G3_MTX_POP             (*(REGType32v *)0x4000448)
#define reg_G3_MTX_STORE           (*(REGType32v *)0x400044c)

#define reg_G3X_GXSTAT             (*(REGType32v *)0x4000600)

#define reg_MI_MCD1                (*(REGType32v *)0x4100010)

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

#define REG_PAD_KEYCNT_LOGIC_SHIFT                         15
#define REG_PAD_KEYCNT_LOGIC_SIZE                          1
#define REG_PAD_KEYCNT_LOGIC_MASK                          0x8000

#define REG_PAD_KEYCNT_INTR_SHIFT                          14
#define REG_PAD_KEYCNT_INTR_SIZE                           1
#define REG_PAD_KEYCNT_INTR_MASK                           0x4000

#define REG_PAD_KEYCNT_L_SHIFT                             9
#define REG_PAD_KEYCNT_L_SIZE                              1
#define REG_PAD_KEYCNT_L_MASK                              0x0200

#define REG_PAD_KEYCNT_R_SHIFT                             8
#define REG_PAD_KEYCNT_R_SIZE                              1
#define REG_PAD_KEYCNT_R_MASK                              0x0100

#define REG_PAD_KEYCNT_DOWN_SHIFT                          7
#define REG_PAD_KEYCNT_DOWN_SIZE                           1
#define REG_PAD_KEYCNT_DOWN_MASK                           0x0080

#define REG_PAD_KEYCNT_UP_SHIFT                            6
#define REG_PAD_KEYCNT_UP_SIZE                             1
#define REG_PAD_KEYCNT_UP_MASK                             0x0040

#define REG_PAD_KEYCNT_LEFT_SHIFT                          5
#define REG_PAD_KEYCNT_LEFT_SIZE                           1
#define REG_PAD_KEYCNT_LEFT_MASK                           0x0020

#define REG_PAD_KEYCNT_RIGHT_SHIFT                         4
#define REG_PAD_KEYCNT_RIGHT_SIZE                          1
#define REG_PAD_KEYCNT_RIGHT_MASK                          0x0010

#define REG_PAD_KEYCNT_START_SHIFT                         3
#define REG_PAD_KEYCNT_START_SIZE                          1
#define REG_PAD_KEYCNT_START_MASK                          0x0008

#define REG_PAD_KEYCNT_SEL_SHIFT                           2
#define REG_PAD_KEYCNT_SEL_SIZE                            1
#define REG_PAD_KEYCNT_SEL_MASK                            0x0004

#define REG_PAD_KEYCNT_B_SHIFT                             1
#define REG_PAD_KEYCNT_B_SIZE                              1
#define REG_PAD_KEYCNT_B_MASK                              0x0002

#define REG_PAD_KEYCNT_A_SHIFT                             0
#define REG_PAD_KEYCNT_A_SIZE                              1
#define REG_PAD_KEYCNT_A_MASK                              0x0001

#ifndef SDK_ASM
#define REG_PAD_KEYCNT_FIELD( logic, intr, l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(logic) << REG_PAD_KEYCNT_LOGIC_SHIFT) | \
    ((u32)(intr) << REG_PAD_KEYCNT_INTR_SHIFT) | \
    ((u32)(l) << REG_PAD_KEYCNT_L_SHIFT) | \
    ((u32)(r) << REG_PAD_KEYCNT_R_SHIFT) | \
    ((u32)(down) << REG_PAD_KEYCNT_DOWN_SHIFT) | \
    ((u32)(up) << REG_PAD_KEYCNT_UP_SHIFT) | \
    ((u32)(left) << REG_PAD_KEYCNT_LEFT_SHIFT) | \
    ((u32)(right) << REG_PAD_KEYCNT_RIGHT_SHIFT) | \
    ((u32)(start) << REG_PAD_KEYCNT_START_SHIFT) | \
    ((u32)(sel) << REG_PAD_KEYCNT_SEL_SHIFT) | \
    ((u32)(b) << REG_PAD_KEYCNT_B_SHIFT) | \
    ((u32)(a) << REG_PAD_KEYCNT_A_SHIFT))
#endif

#endif //POKEDIAMOND_REGISTERS_H
