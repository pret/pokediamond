#ifndef POKEDIAMOND_GXS_IOREG_H
#define POKEDIAMOND_GXS_IOREG_H

#define REG_GXS_DB_DISPCNT_O_SHIFT                         31
#define REG_GXS_DB_DISPCNT_O_SIZE                          1
#define REG_GXS_DB_DISPCNT_O_MASK                          0x80000000

#define REG_GXS_DB_DISPCNT_BG_SHIFT                        30
#define REG_GXS_DB_DISPCNT_BG_SIZE                         1
#define REG_GXS_DB_DISPCNT_BG_MASK                         0x40000000

#define REG_GXS_DB_DISPCNT_OH_SHIFT                        23
#define REG_GXS_DB_DISPCNT_OH_SIZE                         1
#define REG_GXS_DB_DISPCNT_OH_MASK                         0x00800000

#define REG_GXS_DB_DISPCNT_EXOBJ_SHIFT                     20
#define REG_GXS_DB_DISPCNT_EXOBJ_SIZE                      2
#define REG_GXS_DB_DISPCNT_EXOBJ_MASK                      0x00300000

#define REG_GXS_DB_DISPCNT_MODE_SHIFT                      16
#define REG_GXS_DB_DISPCNT_MODE_SIZE                       1
#define REG_GXS_DB_DISPCNT_MODE_MASK                       0x00010000

#define REG_GXS_DB_DISPCNT_OW_SHIFT                        15
#define REG_GXS_DB_DISPCNT_OW_SIZE                         1
#define REG_GXS_DB_DISPCNT_OW_MASK                         0x00008000

#define REG_GXS_DB_DISPCNT_W1_SHIFT                        14
#define REG_GXS_DB_DISPCNT_W1_SIZE                         1
#define REG_GXS_DB_DISPCNT_W1_MASK                         0x00004000

#define REG_GXS_DB_DISPCNT_W0_SHIFT                        13
#define REG_GXS_DB_DISPCNT_W0_SIZE                         1
#define REG_GXS_DB_DISPCNT_W0_MASK                         0x00002000

#define REG_GXS_DB_DISPCNT_DISPLAY_SHIFT                   8
#define REG_GXS_DB_DISPCNT_DISPLAY_SIZE                    5
#define REG_GXS_DB_DISPCNT_DISPLAY_MASK                    0x00001f00

#define REG_GXS_DB_DISPCNT_BLANK_SHIFT                     7
#define REG_GXS_DB_DISPCNT_BLANK_SIZE                      1
#define REG_GXS_DB_DISPCNT_BLANK_MASK                      0x00000080

#define REG_GXS_DB_DISPCNT_OBJMAP_SHIFT                    4
#define REG_GXS_DB_DISPCNT_OBJMAP_SIZE                     3
#define REG_GXS_DB_DISPCNT_OBJMAP_MASK                     0x00000070

#define REG_GXS_DB_DISPCNT_BGMODE_SHIFT                    0
#define REG_GXS_DB_DISPCNT_BGMODE_SIZE                     3
#define REG_GXS_DB_DISPCNT_BGMODE_MASK                     0x00000007

#define REG_GXS_DB_DISPCNT_OBJMAP_CH_SHIFT                 4
#define REG_GXS_DB_DISPCNT_OBJMAP_CH_SIZE                  1
#define REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK                  0x00000010

#define REG_GXS_DB_DISPCNT_OBJMAP_BM_SHIFT                 5
#define REG_GXS_DB_DISPCNT_OBJMAP_BM_SIZE                  2
#define REG_GXS_DB_DISPCNT_OBJMAP_BM_MASK                  0x00000060

#define REG_GXS_DB_DISPCNT_EXOBJ_CH_SHIFT                  20
#define REG_GXS_DB_DISPCNT_EXOBJ_CH_SIZE                   2
#define REG_GXS_DB_DISPCNT_EXOBJ_CH_MASK                   0x00300000

#endif //POKEDIAMOND_GXS_IOREG_H
