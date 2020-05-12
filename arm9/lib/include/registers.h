//
// Created by red031000 on 2020-05-06.
//

#ifndef POKEDIAMOND_REGISTERS_H
#define POKEDIAMOND_REGISTERS_H

#include "types.h"

#define reg_GX_VCOUNT              (*(REGType16v *)0x4000006)

#define reg_G3X_DISP3DCNT          (*(REGType16v *)0x4000060)

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

#define reg_G3X_RDLINES_COUNT      (*(const REGType16v *)0x4000320)
#define reg_G3X_EDGE_COLOR_0       (*(REGType32v *)0x4000330)
#define reg_G3X_EDGE_COLOR_0_L     (*(REGType16v *)0x4000330)
#define reg_G3X_EDGE_COLOR_0_H     (*(REGType16v *)0x4000332)
#define reg_G3X_EDGE_COLOR_1       (*(REGType32v *)0x4000334)
#define reg_G3X_EDGE_COLOR_1_L     (*(REGType16v *)0x4000334)
#define reg_G3X_EDGE_COLOR_1_H     (*(REGType16v *)0x4000336)
#define reg_G3X_EDGE_COLOR_2       (*(REGType32v *)0x4000338)
#define reg_G3X_EDGE_COLOR_2_L     (*(REGType16v *)0x4000338)
#define reg_G3X_EDGE_COLOR_2_H     (*(REGType16v *)0x400033a)
#define reg_G3X_EDGE_COLOR_3       (*(REGType32v *)0x400033c)
#define reg_G3X_EDGE_COLOR_3_L     (*(REGType16v *)0x400033c)
#define reg_G3X_EDGE_COLOR_3_H     (*(REGType16v *)0x400033e)
#define reg_G3X_ALPHA_TEST_REF     (*(REGType16v *)0x4000340)
#define reg_G3X_CLEAR_COLOR        (*(REGType32v *)0x4000350)
#define reg_G3X_CLEAR_DEPTH        (*(REGType16v *)0x4000354)
#define reg_G3X_CLRIMAGE_OFFSET    (*(REGType16v *)0x4000356)
#define reg_G3X_FOG_COLOR          (*(REGType32v *)0x4000358)
#define reg_G3X_FOG_OFFSET         (*(REGType16v *)0x400035c)
#define reg_G3X_FOG_TABLE_0        (*(REGType32v *)0x4000360)
#define reg_G3X_FOG_TABLE_0_L      (*(REGType16v *)0x4000360)
#define reg_G3X_FOG_TABLE_0_H      (*(REGType16v *)0x4000362)
#define reg_G3X_FOG_TABLE_1        (*(REGType32v *)0x4000364)
#define reg_G3X_FOG_TABLE_1_L      (*(REGType16v *)0x4000364)
#define reg_G3X_FOG_TABLE_1_H      (*(REGType16v *)0x4000366)
#define reg_G3X_FOG_TABLE_2        (*(REGType32v *)0x4000368)
#define reg_G3X_FOG_TABLE_2_L      (*(REGType16v *)0x4000368)
#define reg_G3X_FOG_TABLE_2_H      (*(REGType16v *)0x400036a)
#define reg_G3X_FOG_TABLE_3        (*(REGType32v *)0x400036c)
#define reg_G3X_FOG_TABLE_3_L      (*(REGType16v *)0x400036c)
#define reg_G3X_FOG_TABLE_3_H      (*(REGType16v *)0x400036e)
#define reg_G3X_FOG_TABLE_4        (*(REGType32v *)0x4000370)
#define reg_G3X_FOG_TABLE_4_L      (*(REGType16v *)0x4000370)
#define reg_G3X_FOG_TABLE_4_H      (*(REGType16v *)0x4000372)
#define reg_G3X_FOG_TABLE_5        (*(REGType32v *)0x4000374)
#define reg_G3X_FOG_TABLE_5_L      (*(REGType16v *)0x4000374)
#define reg_G3X_FOG_TABLE_5_H      (*(REGType16v *)0x4000376)
#define reg_G3X_FOG_TABLE_6        (*(REGType32v *)0x4000378)
#define reg_G3X_FOG_TABLE_6_L      (*(REGType16v *)0x4000378)
#define reg_G3X_FOG_TABLE_6_H      (*(REGType16v *)0x400037a)
#define reg_G3X_FOG_TABLE_7        (*(REGType32v *)0x400037c)
#define reg_G3X_FOG_TABLE_7_L      (*(REGType16v *)0x400037c)
#define reg_G3X_FOG_TABLE_7_H      (*(REGType16v *)0x400037e)
#define reg_G3X_TOON_TABLE_0       (*(REGType32v *)0x4000380)
#define reg_G3X_TOON_TABLE_0_L     (*(REGType16v *)0x4000380)
#define reg_G3X_TOON_TABLE_0_H     (*(REGType16v *)0x4000382)
#define reg_G3X_TOON_TABLE_1       (*(REGType32v *)0x4000384)
#define reg_G3X_TOON_TABLE_1_L     (*(REGType16v *)0x4000384)
#define reg_G3X_TOON_TABLE_1_H     (*(REGType16v *)0x4000386)
#define reg_G3X_TOON_TABLE_2       (*(REGType32v *)0x4000388)
#define reg_G3X_TOON_TABLE_2_L     (*(REGType16v *)0x4000388)
#define reg_G3X_TOON_TABLE_2_H     (*(REGType16v *)0x400038a)
#define reg_G3X_TOON_TABLE_3       (*(REGType32v *)0x400038c)
#define reg_G3X_TOON_TABLE_3_L     (*(REGType16v *)0x400038c)
#define reg_G3X_TOON_TABLE_3_H     (*(REGType16v *)0x400038e)
#define reg_G3X_TOON_TABLE_4       (*(REGType32v *)0x4000390)
#define reg_G3X_TOON_TABLE_4_L     (*(REGType16v *)0x4000390)
#define reg_G3X_TOON_TABLE_4_H     (*(REGType16v *)0x4000392)
#define reg_G3X_TOON_TABLE_5       (*(REGType32v *)0x4000394)
#define reg_G3X_TOON_TABLE_5_L     (*(REGType16v *)0x4000394)
#define reg_G3X_TOON_TABLE_5_H     (*(REGType16v *)0x4000396)
#define reg_G3X_TOON_TABLE_7       (*(REGType32v *)0x400039c)
#define reg_G3X_TOON_TABLE_7_L     (*(REGType16v *)0x400039c)
#define reg_G3X_TOON_TABLE_7_H     (*(REGType16v *)0x400039e)
#define reg_G3X_TOON_TABLE_8       (*(REGType32v *)0x40003a0)
#define reg_G3X_TOON_TABLE_8_L     (*(REGType16v *)0x40003a0)
#define reg_G3X_TOON_TABLE_8_H     (*(REGType16v *)0x40003a2)
#define reg_G3X_TOON_TABLE_9       (*(REGType32v *)0x40003a4)
#define reg_G3X_TOON_TABLE_9_L     (*(REGType16v *)0x40003a4)
#define reg_G3X_TOON_TABLE_9_H     (*(REGType16v *)0x40003a6)
#define reg_G3X_TOON_TABLE_10      (*(REGType32v *)0x40003a8)
#define reg_G3X_TOON_TABLE_10_L    (*(REGType16v *)0x40003a8)
#define reg_G3X_TOON_TABLE_10_H    (*(REGType16v *)0x40003aa)
#define reg_G3X_TOON_TABLE_11      (*(REGType32v *)0x40003ac)
#define reg_G3X_TOON_TABLE_11_L    (*(REGType16v *)0x40003ac)
#define reg_G3X_TOON_TABLE_11_H    (*(REGType16v *)0x40003ae)
#define reg_G3X_TOON_TABLE_12      (*(REGType32v *)0x40003b0)
#define reg_G3X_TOON_TABLE_12_L    (*(REGType16v *)0x40003b0)
#define reg_G3X_TOON_TABLE_12_H    (*(REGType16v *)0x40003b2)
#define reg_G3X_TOON_TABLE_13      (*(REGType32v *)0x40003b4)
#define reg_G3X_TOON_TABLE_13_L    (*(REGType16v *)0x40003b4)
#define reg_G3X_TOON_TABLE_13_H    (*(REGType16v *)0x40003b6)
#define reg_G3X_TOON_TABLE_14      (*(REGType32v *)0x40003b8)
#define reg_G3X_TOON_TABLE_14_L    (*(REGType16v *)0x40003b8)
#define reg_G3X_TOON_TABLE_14_H    (*(REGType16v *)0x40003ba)
#define reg_G3X_TOON_TABLE_15      (*(REGType32v *)0x40003bc)
#define reg_G3X_TOON_TABLE_15_L    (*(REGType16v *)0x40003bc)
#define reg_G3X_TOON_TABLE_15_H    (*(REGType16v *)0x40003be)
#define reg_G3X_GXFIFO             (*(REGType32v *)0x4000400)

#define reg_G3_MTX_MODE            (*(REGType32v *)0x4000440)
#define reg_G3_MTX_PUSH            (*(REGType32v *)0x4000444)
#define reg_G3_MTX_POP             (*(REGType32v *)0x4000448)
#define reg_G3_MTX_STORE           (*(REGType32v *)0x400044c)
#define reg_G3_MTX_RESTORE         (*(REGType32v *)0x4000450)
#define reg_G3_MTX_IDENTITY        (*(REGType32v *)0x4000454)
#define reg_G3_MTX_LOAD_4x4        (*(REGType32v *)0x4000458)
#define reg_G3_MTX_LOAD_4x3        (*(REGType32v *)0x400045c)
#define reg_G3_MTX_MULT_4x4        (*(REGType32v *)0x4000460)
#define reg_G3_MTX_MULT_4x3        (*(REGType32v *)0x4000464)
#define reg_G3_MTX_MULT_3x3        (*(REGType32v *)0x4000468)
#define reg_G3_MTX_SCALE           (*(REGType32v *)0x400046c)
#define reg_G3_MTX_TRANS           (*(REGType32v *)0x4000470)
#define reg_G3_COLOR               (*(REGType32v *)0x4000480)
#define reg_G3_NORMAL              (*(REGType32v *)0x4000484)
#define reg_G3_TEXCOORD            (*(REGType32v *)0x4000488)
#define reg_G3_VTX_16              (*(REGType32v *)0x400048c)
#define reg_G3_VTX_10              (*(REGType32v *)0x4000490)
#define reg_G3_VTX_XY              (*(REGType32v *)0x4000494)
#define reg_G3_VTX_XZ              (*(REGType32v *)0x4000498)
#define reg_G3_VTX_YZ              (*(REGType32v *)0x400049c)
#define reg_G3_VTX_DIFF            (*(REGType32v *)0x40004a0)
#define reg_G3_POLYGON_ATTR        (*(REGType32v *)0x40004a4)
#define reg_G3_TEXIMAGE_PARAM      (*(REGType32v *)0x40004a8)
#define reg_G3_TEXPLTT_BASE        (*(REGType32v *)0x40004ac)
#define reg_G3_DIF_AMB             (*(REGType32v *)0x40004c0)
#define reg_G3_SPE_EMI             (*(REGType32v *)0x40004c4)
#define reg_G3_LIGHT_VECTOR        (*(REGType32v *)0x40004c8)
#define reg_G3_LIGHT_COLOR         (*(REGType32v *)0x40004cc)
#define reg_G3_SHININESS           (*(REGType32v *)0x40004d0)
#define reg_G3_BEGIN_VTXS          (*(REGType32v *)0x4000500)
#define reg_G3_END_VTXS            (*(REGType32v *)0x4000504)
#define reg_G3_SWAP_BUFFERS        (*(REGType32v *)0x4000540)
#define reg_G3_VIEWPORT            (*(REGType32v *)0x4000580)
#define reg_G3_BOX_TEST            (*(REGType32v *)0x40005c0)
#define reg_G3_POS_TEST            (*(REGType32v *)0x40005c4)
#define reg_G3_VEC_TEST            (*(REGType32v *)0x40005c8)

#define reg_G3X_GXSTAT             (*(REGType32v *)0x4000600)
#define reg_G3X_LISTRAM_COUNT      (*(REGType16v *)0x4000604)
#define reg_G3X_VTXRAM_COUNT       (*(REGType16v *)0x4000606)
#define reg_G3X_DISP_1DOT_DEPTH    (*(REGType16v *)0x4000610)
#define reg_G3X_POS_RESULT_X       (*(const REGType32v *)0x4000620)
#define reg_G3X_POS_RESULT_Y       (*(const REGType32v *)0x4000624)
#define reg_G3X_POS_RESULT_Z       (*(const REGType32v *)0x4000628)
#define reg_G3X_POS_RESULT_W       (*(const REGType32v *)0x400062c)
#define reg_G3X_VEC_RESULT_X       (*(const REGType16v *)0x4000630)
#define reg_G3X_VEC_RESULT_Y       (*(const REGType16v *)0x4000632)
#define reg_G3X_VEC_RESULT_Z       (*(const REGType16v *)0x4000634)
#define reg_G3X_CLIPMTX_RESULT_0   (*(const REGType32v *)0x4000640)
#define reg_G3X_CLIPMTX_RESULT_1   (*(const REGType32v *)0x4000644)
#define reg_G3X_CLIPMTX_RESULT_2   (*(const REGType32v *)0x4000648)
#define reg_G3X_CLIPMTX_RESULT_3   (*(const REGType32v *)0x400064c)
#define reg_G3X_CLIPMTX_RESULT_4   (*(const REGType32v *)0x4000650)
#define reg_G3X_CLIPMTX_RESULT_5   (*(const REGType32v *)0x4000654)
#define reg_G3X_CLIPMTX_RESULT_6   (*(const REGType32v *)0x4000658)
#define reg_G3X_CLIPMTX_RESULT_7   (*(const REGType32v *)0x400065c)
#define reg_G3X_CLIPMTX_RESULT_8   (*(const REGType32v *)0x4000660)
#define reg_G3X_CLIPMTX_RESULT_9   (*(const REGType32v *)0x4000664)
#define reg_G3X_CLIPMTX_RESULT_10  (*(const REGType32v *)0x4000668)
#define reg_G3X_CLIPMTX_RESULT_11  (*(const REGType32v *)0x400066c)
#define reg_G3X_CLIPMTX_RESULT_12  (*(const REGType32v *)0x4000670)
#define reg_G3X_CLIPMTX_RESULT_13  (*(const REGType32v *)0x4000674)
#define reg_G3X_CLIPMTX_RESULT_14  (*(const REGType32v *)0x4000678)
#define reg_G3X_CLIPMTX_RESULT_15  (*(const REGType32v *)0x400067c)
#define reg_G3X_VECMTX_RESULT_0    (*(const REGType32v *)0x4000680)
#define reg_G3X_VECMTX_RESULT_1    (*(const REGType32v *)0x4000684)
#define reg_G3X_VECMTX_RESULT_2    (*(const REGType32v *)0x4000688)
#define reg_G3X_VECMTX_RESULT_3    (*(const REGType32v *)0x400068c)
#define reg_G3X_VECMTX_RESULT_4    (*(const REGType32v *)0x4000690)
#define reg_G3X_VECMTX_RESULT_5    (*(const REGType32v *)0x4000694)
#define reg_G3X_VECMTX_RESULT_6    (*(const REGType32v *)0x4000698)
#define reg_G3X_VECMTX_RESULT_7    (*(const REGType32v *)0x400069c)
#define reg_G3X_VECMTX_RESULT_8    (*(const REGType32v *)0x40006a0)

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
