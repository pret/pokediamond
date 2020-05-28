#include "scrn_id.h"

#define FIELD                        0
#define T101                         1
#define T102                         2
#define T103                         3
#define T104                         4
#define T105                         5
#define T106                         6
#define T107                         7
#define C101                         8
#define C102                         9
#define C103                        10
#define C104                        11
#define C105                        12
#define C106                        13
#define C107                        14
#define C108                        15
#define C109                        16
#define R104                        17
#define R111                        18
#define R112                        19
#define R114                        20
#define R116                        21
#define R117                        22
#define R121                        23
#define CAVE                        24
#define SP                          25
#define PARK                        26
#define TEST                        27
#define R109                        28
#define R110                        29
#define R113                        30
#define R123                        31
#define R119                        32
#define R124                        33


#define FIELD_C101                   0
#define FIELD_C102                   1
#define FIELD_C103                   2
#define FIELD_C104                   3
#define FIELD_C105                   4
#define FIELD_C106                   5
#define FIELD_C107                   6
#define FIELD_C108                   7
#define FIELD_C109                   8
#define FIELD_T101                   9
#define FIELD_T102                  10
#define FIELD_T103                  11
#define FIELD_T104                  12
#define FIELD_T105                  13
#define FIELD_T106                  14
#define FIELD_T107                  15
#define FIELD_R101                  16
#define FIELD_R102                  17
#define FIELD_R103                  18
#define FIELD_R104                  19
#define FIELD_R105                  20
#define FIELD_R106                  21
#define FIELD_R107                  22
#define FIELD_R108                  23
#define FIELD_R109                  24
#define FIELD_R110                  25
#define FIELD_R111                  26
#define FIELD_R112                  27
#define FIELD_R113                  28
#define FIELD_R114                  29
#define FIELD_R115                  30
#define FIELD_R116                  31
#define FIELD_R117                  32
#define FIELD_R118                  33
#define FIELD_R119                  34
#define FIELD_R120                  35
#define FIELD_R121                  36
#define FIELD_R122                  37
#define FIELD_R123                  38
#define FIELD_R124                  39
#define FIELD_R125                  40
#define FIELD_R126                  41
#define FIELD_R127                  42
#define FIELD_R128                  43
#define FIELD_R129                  44
#define FIELD_R130                  45
#define FIELD_R131                  46
#define FIELD_R132                  47
#define FIELD_R133                  48
#define FIELD_R134                  49
#define FIELD_W124                  50
#define FIELD_W126                  51
#define FIELD_W127                  52
#define FIELD_W128                  53

#define DIVISION_FIELD_MAX          54




#define T101_R0101                   0
#define T101_R0102                   1
#define T101_R0201                   2
#define T101_R0202                   3
#define T101_R0301                   4

#define DIVISION_T101_MAX            5




#define T102_R0101                   0
#define T102_R0201                   1
#define T102_PC01                    2
#define T102_PC02                    3
#define T102_FS01                    4

#define DIVISION_T102_MAX            5




#define T103_R0101                   0
#define T103_PC01                    1
#define T103_PC02                    2
#define T103_R0201                   3
#define T103_R0301                   4
#define T103_R0401                   5

#define DIVISION_T103_MAX            6




#define T104_R0101                   0
#define T104_R0201                   1
#define T104_R0202                   2
#define T104_R0301                   3
#define T104_FS01                    4
#define T104_PC01                    5
#define T104_PC02                    6

#define DIVISION_T104_MAX            7




#define T105_FS01                    0
#define T105_R0101                   1
#define T105_R0102                   2
#define T105_PC01                    3
#define T105_PC02                    4
#define T105_R0201                   5
#define T105_R0301                   6

#define DIVISION_T105_MAX            7




#define T106_R0101                   0
#define T106_R0102                   1
#define T106_FS01                    2
#define T106_PC01                    3
#define T106_PC02                    4
#define T106_R0201                   5
#define T106_R0301                   6
#define T106_R0401                   7

#define DIVISION_T106_MAX            8




#define T107_PC01                    0
#define T107_PC02                    1
#define T107_R0101                   2
#define T107_R0201                   3
#define T107_R0301                   4
#define T107_R0401                   5
#define T107_R0501                   6

#define DIVISION_T107_MAX            7




#define C101_R0101                   0
#define C101_R0201                   1
#define C101_R0301                   2
#define C101_R0401                   3
#define C101_PC01                    4
#define C101_PC02                    5
#define C101_FS01                    6

#define DIVISION_C101_MAX            7




#define C102_R0101                   0
#define C102_R0102                   1
#define C102_R0201                   2
#define C102_R0202                   3
#define C102_R0301                   4
#define C102_R0401                   5
#define C102_R0501                   6
#define C102_R0502                   7
#define C102_R0601                   8
#define C102_R0701                   9
#define C102_PC01                   10
#define C102_PC02                   11
#define C102_FS01                   12

#define DIVISION_C102_MAX           13




#define C103_R0101                   0
#define C103_R0201                   1
#define C103_R0301                   2
#define C103_R0401                   3
#define C103_R0501                   4
#define C103_PC01                    5
#define C103_PC02                    6
#define C103_FS01                    7

#define DIVISION_C103_MAX            8




#define C104_R0101                   0
#define C104_R0102                   1
#define C104_R0103                   2
#define C104_R0201                   3
#define C104_R0301                   4
#define C104_PC01                    5
#define C104_PC02                    6
#define C104_FS01                    7
#define C104_R0401                   8
#define C104_R0402                   9
#define C104_R0501                  10
#define C104_R0601                  11
#define C104_R0701                  12
#define C104_R0801                  13
#define C104_R0802                  14
#define C104_R0803                  15
#define C104_R0901                  16

#define DIVISION_C104_MAX           17




#define C105_R0101                   0
#define C105_R0201                   1
#define C105_PC01                    2
#define C105_PC02                    3
#define C105_FS01                    4
#define C105_R0301                   5
#define C105_R0401                   6
#define C105_R0501                   7
#define C105_R0601                   8
#define C105_R0701                   9

#define DIVISION_C105_MAX           10




#define C106_R0101                   0
#define C106_R0102                   1
#define C106_R0201                   2
#define C106_R0202                   3
#define C106_R0301                   4
#define C106_R0302                   5
#define C106_PC01                    6
#define C106_PC02                    7
#define C106_FS01                    8
#define C106_R0401                   9
#define C106_R0501                  10
#define C106_R0502                  11
#define C106_R0601                  12
#define C106_R0701                  13
#define C106_R0801                  14
#define C106_R0901                  15
#define C106_R1001                  16
#define C106_R1101                  17
#define C106_R1102                  18
#define C106_R1103                  19
#define C106_R1104                  20
#define C106_R1105                  21
#define C106_R1106                  22
#define C106_R1201                  23

#define DIVISION_C106_MAX           24




#define C107_R0101                   0
#define C107_R0201                   1
#define C107_R0301                   2
#define C107_PC01                    3
#define C107_PC02                    4
#define C107_FS01                    5
#define C107_R0401                   6
#define C107_R0501                   7
#define C107_R0601                   8
#define C107_R0701                   9
#define C107_R0702                  10
#define C107_R0801                  11
#define C107_R0802                  12

#define DIVISION_C107_MAX           13




#define C108_R0101                   0
#define C108_R0102                   1
#define C108_PC01                    2
#define C108_PC02                    3
#define C108_FS01                    4
#define C108_R0201                   5
#define C108_R0301                   6
#define C108_R0401                   7
#define C108_R0501                   8
#define C108_R0601                   9
#define C108_R0701                  10
#define C108_R0801                  11
#define C108_R0901                  12

#define DIVISION_C108_MAX           13




#define C109_R0101                   0
#define C109_R0102                   1
#define C109_R0103                   2
#define C109_R0104                   3
#define C109_R0105                   4
#define C109_R0201                   5
#define C109_R0202                   6
#define C109_R0203                   7
#define C109_R0204                   8
#define C109_R0205                   9
#define C109_R0206                  10
#define C109_R0301                  11
#define C109_PC01                   12
#define C109_PC02                   13

#define DIVISION_C109_MAX           14




#define R104_R0101                   0
#define R104_R0201                   1

#define DIVISION_R104_MAX            2




#define R111_R0101                   0
#define R111_R0201                   1

#define DIVISION_R111_MAX            2




#define R112_R0101                   0
#define R112_R0102                   1

#define DIVISION_R112_MAX            2




#define R114_R0101                   0
#define R114_R0102                   1
#define R114_R0201                   2

#define DIVISION_R114_MAX            3




#define R116_R0101                   0

#define DIVISION_R116_MAX            1




#define R117_R0101                   0

#define DIVISION_R117_MAX            1




#define R121_R0101                   0

#define DIVISION_R121_MAX            1




#define CAVE_D0101                   0
#define CAVE_D0102                   1
#define CAVE_D0103                   2
#define CAVE_D0104                   3
#define CAVE_D0201                   4
#define CAVE_D0301                   5
#define CAVE_D0401                   6
#define CAVE_D0501                   7
#define CAVE_D0502                   8
#define CAVE_D0503                   9
#define CAVE_D0504                  10
#define CAVE_D0601                  11
#define CAVE_D0701                  12
#define CAVE_D0702                  13
#define CAVE_D0703                  14
#define CAVE_D0801                  15
#define CAVE_D0802                  16
#define CAVE_D0803                  17
#define CAVE_D0804                  18
#define CAVE_D0805                  19
#define CAVE_D0806                  20
#define CAVE_D0807                  21
#define CAVE_D0808                  22
#define CAVE_D0901                  23
#define CAVE_D0902                  24
#define CAVE_D0903                  25
#define CAVE_D1101                  26
#define CAVE_D1102                  27
#define CAVE_D1103                  28
#define CAVE_D1104                  29
#define CAVE_D1105                  30
#define CAVE_D1106                  31
#define CAVE_D1107                  32
#define CAVE_D1108                  33
#define CAVE_D1109                  34
#define CAVE_D1110                  35
#define CAVE_D1111                  36
#define CAVE_D1201                  37
#define CAVE_D1202                  38
#define CAVE_D1203                  39
#define CAVE_D1204                  40
#define CAVE_D1205                  41
#define CAVE_D1206                  42
#define CAVE_D1301                  43
#define CAVE_D1302                  44
#define CAVE_D1303                  45
#define CAVE_D1401                  46
#define CAVE_D1402                  47
#define CAVE_D1403                  48
#define CAVE_D1404                  49
#define CAVE_D1405                  50
#define CAVE_D1406                  51
#define CAVE_D1601                  52
#define CAVE_D1602                  53
#define CAVE_D1701                  54
#define CAVE_D1702                  55
#define CAVE_D1703                  56
#define CAVE_D1704                  57
#define CAVE_D1705                  58
#define CAVE_D1706                  59
#define CAVE_D1707                  60
#define CAVE_D1708                  61
#define CAVE_D1709                  62
#define CAVE_D1710                  63
#define CAVE_D1711                  64
#define CAVE_D1712                  65
#define CAVE_D1713                  66
#define CAVE_D1801                  67
#define CAVE_D1901                  68
#define CAVE_D2001                  69
#define CAVE_D2002                  70
#define CAVE_D2003                  71
#define CAVE_D2004                  72
#define CAVE_D2101                  73
#define CAVE_D2201                  74
#define CAVE_D2202                  75
#define CAVE_D2203                  76
#define CAVE_D2301                  77
#define CAVE_D2302                  78
#define CAVE_D2303                  79
#define CAVE_D2304                  80
#define CAVE_D2305                  81
#define CAVE_D2306                  82
#define CAVE_D1407                  83
#define CAVE_D2307                  84
#define CAVE_D2308                  85

#define DIVISION_CAVE_MAX           86




#define SP_BASE01                    0
#define SP_BASE02                    1
#define SP_BASE03                    2
#define SP_BASE04                    3
#define SP_BASE05                    4
#define SP_BASE06                    5
#define SP_BASE07                    6
#define SP_BASE08                    7
#define SP_BASE09                    8
#define SP_BASE10                    9
#define SP_BASE11                   10
#define SP_BASE12                   11
#define SP_BASE13                   12
#define SP_BASE14                   13
#define SP_BASE15                   14
#define SP_BASE16                   15
#define SP_BASE17                   16
#define SP_BASE18                   17
#define SP_BASE19                   18
#define SP_BASE20                   19
#define SP_BASE21                   20
#define SP_BASE22                   21
#define SP_BASE23                   22
#define SP_BASE24                   23
#define SP_PC03                     24
#define SP_PC04                     25
#define SP_PC05                     26
#define SP_PC06                     27
#define SP_CONTEST03_1              28
#define SP_CONTEST03_2              29
#define SP_CONTEST03_3              30
#define SP_CONTEST03_4              31
#define SP_CONTEST03_5              32
#define SP_CONTEST03_6              33
#define SP_CONTEST03_7              34
#define SP_CONTEST03_8              35
#define SP_CONTEST03_9              36
#define SP_CONTEST03_10             37
#define SP_CONTEST03_11             38
#define SP_CONTEST03_12             39
#define SP_TRUCK                    40
#define SP_SHIP01                   41
#define SP_SHIP02                   42
#define SP_SHIP03                   43

#define DIVISION_SP_MAX             44




#define PARK_SAFARI01                0
#define PARK_SAFARI02                1
#define PARK_SAFARI03                2
#define PARK_SAFARI04                3
#define PARK_TOWER01                 4
#define PARK_BATTLE01                5
#define PARK_BATTLE02                6
#define PARK_BATTLE03                7
#define PARK_BATTLE04                8
#define PARK_KOKORO01                9
#define PARK_KOKORO02               10
#define PARK_SAFARI05               11

#define DIVISION_PARK_MAX           12




#define TEST_NEWTOWN                 0
#define TEST_NEWTOWN2                1

#define DIVISION_TEST_MAX            2




#define R109_R0101                   0

#define DIVISION_R109_MAX            1




#define R110_R0101                   0
#define R110_R0102                   1
#define R110_R0103                   2
#define R110_R0104                   3
#define R110_R0105                   4
#define R110_R0106                   5
#define R110_R0107                   6
#define R110_R0108                   7
#define R110_R0109                   8
#define R110_R0110                   9
#define R110_R0111                  10
#define R110_R0201                  11
#define R110_R0301                  12

#define DIVISION_R110_MAX           13




#define R113_R0101                   0

#define DIVISION_R113_MAX            1




#define R123_R0201                   0

#define DIVISION_R123_MAX            1




#define R119_R0101                   0
#define R119_R0102                   1
#define R119_R0201                   2

#define DIVISION_R119_MAX            3




#define R124_R0101                   0

#define DIVISION_R124_MAX            1







#define TData_field_c101	MAPSCRNID_CITY101
#define TData_field_c102	MAPSCRNID_CITY102
#define TData_field_c103	MAPSCRNID_CITY103
#define TData_field_c104	MAPSCRNID_CITY104
#define TData_field_c105	MAPSCRNID_CITY105
#define TData_field_c106	MAPSCRNID_CITY106
#define TData_field_c107	MAPSCRNID_CITY107
#define TData_field_c108	MAPSCRNID_CITY108
#define TData_field_c109	MAPSCRNID_CITY109
#define TData_field_t101	MAPSCRNID_TOWN101
#define TData_field_t102	MAPSCRNID_TOWN102
#define TData_field_t103	MAPSCRNID_TOWN103
#define TData_field_t104	MAPSCRNID_TOWN104
#define TData_field_t105	MAPSCRNID_TOWN105
#define TData_field_t106	MAPSCRNID_TOWN106
#define TData_field_t107	MAPSCRNID_TOWN107
#define TData_field_r101	MAPSCRNID_ROAD101
#define TData_field_r102	MAPSCRNID_ROAD102
#define TData_field_r103	MAPSCRNID_ROAD103
#define TData_field_r104	MAPSCRNID_ROAD104
#define TData_field_r105	MAPSCRNID_ROAD105
#define TData_field_r106	MAPSCRNID_ROAD106
#define TData_field_r107	MAPSCRNID_ROAD107
#define TData_field_r108	MAPSCRNID_ROAD108
#define TData_field_r109	MAPSCRNID_ROAD109
#define TData_field_r110	MAPSCRNID_ROAD110
#define TData_field_r111	MAPSCRNID_ROAD111
#define TData_field_r112	MAPSCRNID_ROAD112
#define TData_field_r113	MAPSCRNID_ROAD113
#define TData_field_r114	MAPSCRNID_ROAD114
#define TData_field_r115	MAPSCRNID_ROAD115
#define TData_field_r116	MAPSCRNID_ROAD116
#define TData_field_r117	MAPSCRNID_ROAD117
#define TData_field_r118	MAPSCRNID_ROAD118
#define TData_field_r119	MAPSCRNID_ROAD119
#define TData_field_r120	MAPSCRNID_ROAD120
#define TData_field_r121	MAPSCRNID_ROAD121
#define TData_field_r122	MAPSCRNID_ROAD122
#define TData_field_r123	MAPSCRNID_ROAD123
#define TData_field_r124	MAPSCRNID_ROAD124
#define TData_field_r125	MAPSCRNID_ROAD125
#define TData_field_r126	MAPSCRNID_ROAD126
#define TData_field_r127	MAPSCRNID_ROAD127
#define TData_field_r128	MAPSCRNID_ROAD128
#define TData_field_r129	MAPSCRNID_ROAD129
#define TData_field_r130	MAPSCRNID_ROAD130
#define TData_field_r131	MAPSCRNID_ROAD131
#define TData_field_r132	MAPSCRNID_ROAD132
#define TData_field_r133	MAPSCRNID_ROAD133
#define TData_field_r134	MAPSCRNID_ROAD134
#define TData_field_w124	MAPSCRNID_WATER124
#define TData_field_w126	MAPSCRNID_WATER126
#define TData_field_w127	MAPSCRNID_WATER127
#define TData_field_w128	MAPSCRNID_WATER128
#define TData_t101_r0101	MAPSCRNID_TOWN101_ROOM01_1
#define TData_t101_r0102	MAPSCRNID_TOWN101_ROOM01_2
#define TData_t101_r0201	MAPSCRNID_TOWN101_ROOM02_1
#define TData_t101_r0202	MAPSCRNID_TOWN101_ROOM02_2
#define TData_t101_r0301	MAPSCRNID_TOWN101_ROOM03
#define TData_t102_r0101	MAPSCRNID_MINKA01_2
#define TData_t102_r0201	MAPSCRNID_MINKA01_1
#define TData_t102_pc01	MAPSCRNID_PC01
#define TData_t102_pc02	MAPSCRNID_PC02
#define TData_t102_fs01	MAPSCRNID_FS01
#define TData_t103_r0101	MAPSCRNID_MINKA02_1
#define TData_t103_pc01	MAPSCRNID_PC01
#define TData_t103_pc02	MAPSCRNID_PC02
#define TData_t103_r0201	MAPSCRNID_GYM02_1
#define TData_t103_r0301	MAPSCRNID_RYUUKOU
#define TData_t103_r0401	MAPSCRNID_MINKA02_2
#define TData_t104_r0101	MAPSCRNID_DRGST
#define TData_t104_r0201	MAPSCRNID_GYM04_1
#define TData_t104_r0202	MAPSCRNID_GYM04_2
#define TData_t104_r0301	MAPSCRNID_MINKA02_1
#define TData_t104_fs01	MAPSCRNID_FS01
#define TData_t104_pc01	MAPSCRNID_PC01_1
#define TData_t104_pc02	MAPSCRNID_PC02
#define TData_t105_fs01	MAPSCRNID_FS01
#define TData_t105_r0101	MAPSCRNID_CONTEST01_1
#define TData_t105_r0102	MAPSCRNID_CONTEST02_1
#define TData_t105_pc01	MAPSCRNID_PC01
#define TData_t105_pc02	MAPSCRNID_PC02
#define TData_t105_r0201	MAPSCRNID_MINKA01_2
#define TData_t105_r0301	MAPSCRNID_MINKA01_1
#define TData_t106_r0101	MAPSCRNID_CONTEST01_1
#define TData_t106_r0102	MAPSCRNID_CONTEST02_1
#define TData_t106_fs01	MAPSCRNID_FS01
#define TData_t106_pc01	MAPSCRNID_PC01
#define TData_t106_pc02	MAPSCRNID_PC02
#define TData_t106_r0201	MAPSCRNID_RYOUYOU01_1
#define TData_t106_r0301	MAPSCRNID_MINKA01_1
#define TData_t106_r0401	MAPSCRNID_MINKA01_2
#define TData_t107_pc01	MAPSCRNID_PC01
#define TData_t107_pc02	MAPSCRNID_PC02
#define TData_t107_r0101	MAPSCRNID_MINKA05_1
#define TData_t107_r0201	MAPSCRNID_MINKA05_2
#define TData_t107_r0301	MAPSCRNID_MINKA05_1
#define TData_t107_r0401	MAPSCRNID_MINKA05_2
#define TData_t107_r0501	MAPSCRNID_MINKA05_1
#define TData_c101_r0101	MAPSCRNID_MINKA01_1
#define TData_c101_r0201	MAPSCRNID_GYM05_1
#define TData_c101_r0301	MAPSCRNID_MINKA01_2
#define TData_c101_r0401	MAPSCRNID_MINKA01_3
#define TData_c101_pc01	MAPSCRNID_PC01
#define TData_c101_pc02	MAPSCRNID_PC02
#define TData_c101_fs01	MAPSCRNID_FS01
#define TData_c102_r0101	MAPSCRNID_SHIPYARD01_1
#define TData_c102_r0102	MAPSCRNID_SHIPYARD01_2
#define TData_c102_r0201	MAPSCRNID_CONTEST01_1
#define TData_c102_r0202	MAPSCRNID_CONTEST02_1
#define TData_c102_r0301	MAPSCRNID_MINKA01_3
#define TData_c102_r0401	MAPSCRNID_CLUB01_1
#define TData_c102_r0501	MAPSCRNID_MUSEUM01_1
#define TData_c102_r0502	MAPSCRNID_MUSEUM01_2
#define TData_c102_r0601	MAPSCRNID_FUNANORI01_1
#define TData_c102_r0701	MAPSCRNID_MINKA01_1
#define TData_c102_pc01	MAPSCRNID_PC01
#define TData_c102_pc02	MAPSCRNID_PC02
#define TData_c102_fs01	MAPSCRNID_FS01
#define TData_c103_r0101	MAPSCRNID_GYM03_1
#define TData_c103_r0201	MAPSCRNID_JITEN01_1
#define TData_c103_r0301	MAPSCRNID_MINKA01_1
#define TData_c103_r0401	MAPSCRNID_GAME
#define TData_c103_r0501	MAPSCRNID_MINKA01_2
#define TData_c103_pc01	MAPSCRNID_PC01
#define TData_c103_pc02	MAPSCRNID_PC02
#define TData_c103_fs01	MAPSCRNID_FS01
#define TData_c104_r0101	MAPSCRNID_DEBON01_1
#define TData_c104_r0102	MAPSCRNID_DEBON01_2
#define TData_c104_r0103	MAPSCRNID_DEBON01_3
#define TData_c104_r0201	MAPSCRNID_GYM01_1
#define TData_c104_r0301	MAPSCRNID_P_SCHOOL01
#define TData_c104_pc01	MAPSCRNID_PC01
#define TData_c104_pc02	MAPSCRNID_PC02
#define TData_c104_fs01	MAPSCRNID_FS01
#define TData_c104_r0401	MAPSCRNID_MINKA03_7
#define TData_c104_r0402	MAPSCRNID_MINKA03_8
#define TData_c104_r0501	MAPSCRNID_MINKA03_2
#define TData_c104_r0601	MAPSCRNID_MINKA03_3
#define TData_c104_r0701	MAPSCRNID_MINKA03_1
#define TData_c104_r0801	MAPSCRNID_MINKA03_4
#define TData_c104_r0802	MAPSCRNID_MINKA03_5
#define TData_c104_r0803	MAPSCRNID_MINKA03_6
#define TData_c104_r0901	MAPSCRNID_MINKA03_1
#define TData_c105_r0101	MAPSCRNID_MINKA04_1
#define TData_c105_r0201	MAPSCRNID_GYM06_1
#define TData_c105_pc01	MAPSCRNID_PC01
#define TData_c105_pc02	MAPSCRNID_PC02
#define TData_c105_fs01	MAPSCRNID_FS01
#define TData_c105_r0301	MAPSCRNID_MINKA04_2
#define TData_c105_r0401	MAPSCRNID_MINKA04_1
#define TData_c105_r0501	MAPSCRNID_MINKA04_2
#define TData_c105_r0601	MAPSCRNID_MINKA04_1
#define TData_c105_r0701	MAPSCRNID_GOODS01_1
#define TData_c106_r0101	MAPSCRNID_MINSYUKU01_1
#define TData_c106_r0102	MAPSCRNID_MINSYUKU01_2
#define TData_c106_r0201	MAPSCRNID_ART01_1
#define TData_c106_r0202	MAPSCRNID_ART01_2
#define TData_c106_r0301	MAPSCRNID_CONTEST01_3
#define TData_c106_r0302	MAPSCRNID_CONTEST02_4
#define TData_c106_pc01	MAPSCRNID_PC01
#define TData_c106_pc02	MAPSCRNID_PC02
#define TData_c106_fs01	MAPSCRNID_FS01
#define TData_c106_r0401	MAPSCRNID_FAN01_1
#define TData_c106_r0501	MAPSCRNID_FUNANORI01_1
#define TData_c106_r0502	MAPSCRNID_FUNANORI02_2
#define TData_c106_r0601	MAPSCRNID_MINKA01_1
#define TData_c106_r0701	MAPSCRNID_MINKA01_2
#define TData_c106_r0801	MAPSCRNID_MINKA02_3
#define TData_c106_r0901	MAPSCRNID_MINKA01_1
#define TData_c106_r1001	MAPSCRNID_MINKA01_2
#define TData_c106_r1101	MAPSCRNID_DEP01_1
#define TData_c106_r1102	MAPSCRNID_DEP01_2
#define TData_c106_r1103	MAPSCRNID_DEP01_3
#define TData_c106_r1104	MAPSCRNID_DEP01_4
#define TData_c106_r1105	MAPSCRNID_DEP01_5
#define TData_c106_r1106	MAPSCRNID_DEP01_6
#define TData_c106_r1201	MAPSCRNID_DEP01_7
#define TData_c107_r0101	MAPSCRNID_GYM07_1
#define TData_c107_r0201	MAPSCRNID_MINKA01_1
#define TData_c107_r0301	MAPSCRNID_MINKA01_2
#define TData_c107_pc01	MAPSCRNID_PC01
#define TData_c107_pc02	MAPSCRNID_PC02
#define TData_c107_fs01	MAPSCRNID_FS01
#define TData_c107_r0401	MAPSCRNID_MINKA01_1
#define TData_c107_r0501	MAPSCRNID_DAIGO01_1
#define TData_c107_r0601	MAPSCRNID_MINKA01_3
#define TData_c107_r0701	MAPSCRNID_UCHU01_1
#define TData_c107_r0702	MAPSCRNID_UCHU01_2
#define TData_c107_r0801	MAPSCRNID_MINKA06_1
#define TData_c107_r0802	MAPSCRNID_MINKA06_2
#define TData_c108_r0101	MAPSCRNID_GYM08_1
#define TData_c108_r0102	MAPSCRNID_GYM08_2
#define TData_c108_pc01	MAPSCRNID_PC01
#define TData_c108_pc02	MAPSCRNID_PC02
#define TData_c108_fs01	MAPSCRNID_FS01
#define TData_c108_r0201	MAPSCRNID_MINKA07_1
#define TData_c108_r0301	MAPSCRNID_MINKA07_2
#define TData_c108_r0401	MAPSCRNID_MINKA07_3
#define TData_c108_r0501	MAPSCRNID_MINKA07_1
#define TData_c108_r0601	MAPSCRNID_MINKA07_2
#define TData_c108_r0701	MAPSCRNID_MINKA07_3
#define TData_c108_r0801	MAPSCRNID_MINKA07_1
#define TData_c108_r0901	MAPSCRNID_OHKISA01_1
#define TData_c109_r0101	MAPSCRNID_SHITEN01_1
#define TData_c109_r0102	MAPSCRNID_SHITEN01_2
#define TData_c109_r0103	MAPSCRNID_SHITEN01_3
#define TData_c109_r0104	MAPSCRNID_SHITEN01_4
#define TData_c109_r0105	MAPSCRNID_SHITEN01_5
#define TData_c109_r0201	MAPSCRNID_SHITEN02_1
#define TData_c109_r0202	MAPSCRNID_SHITEN02_1
#define TData_c109_r0203	MAPSCRNID_SHITEN02_1
#define TData_c109_r0204	MAPSCRNID_SHITEN02_3
#define TData_c109_r0205	MAPSCRNID_SHITEN02_1
#define TData_c109_r0206	MAPSCRNID_SHITEN02_2
#define TData_c109_r0301	MAPSCRNID_DENDOU01_1
#define TData_c109_pc01	MAPSCRNID_PC01
#define TData_c109_pc02	MAPSCRNID_PC02
#define TData_r104_r0101	MAPSCRNID_HAGI01_1
#define TData_r104_r0201	MAPSCRNID_FLWSP
#define TData_r111_r0101	MAPSCRNID_MINKA01_1
#define TData_r111_r0201	MAPSCRNID_MINKA02_1
#define TData_r112_r0101	MAPSCRNID_ROPEWAY01_1
#define TData_r112_r0102	MAPSCRNID_ROPEWAY01_1
#define TData_r114_r0101	MAPSCRNID_KASEKI01_1
#define TData_r114_r0102	MAPSCRNID_KASEKI01_2
#define TData_r114_r0201	MAPSCRNID_MAYUMI01_1
#define TData_r116_r0101	MAPSCRNID_IAIDOU
#define TData_r117_r0101	MAPSCRNID_SODATEYA01_1
#define TData_r121_r0101	MAPSCRNID_SAFARI
#define TData_cave_d0101	MAPSCRNID_R115DUN01_1
#define TData_cave_d0102	MAPSCRNID_R115DUN01_2
#define TData_cave_d0103	MAPSCRNID_R115DUN01_3
#define TData_cave_d0104	MAPSCRNID_R115DUN01_4
#define TData_cave_d0201	MAPSCRNID_R116DUN01_1
#define TData_cave_d0301	MAPSCRNID_W126DUN01_1
#define TData_cave_d0401	MAPSCRNID_R111DUN01_1
#define TData_cave_d0501	MAPSCRNID_R106DUN01_1
#define TData_cave_d0502	MAPSCRNID_R106DUN01_2
#define TData_cave_d0503	MAPSCRNID_R106DUN01_3
#define TData_cave_d0504	MAPSCRNID_R106DUN01_4
#define TData_cave_d0601	MAPSCRNID_R104DUN01_1
#define TData_cave_d0701	MAPSCRNID_R112DUN01_1
#define TData_cave_d0702	MAPSCRNID_R112DUN02_1
#define TData_cave_d0703	MAPSCRNID_R112DUN03_1
#define TData_cave_d0801	MAPSCRNID_R122DUN01_1
#define TData_cave_d0802	MAPSCRNID_R122DUN01_2
#define TData_cave_d0803	MAPSCRNID_R122DUN01_3
#define TData_cave_d0804	MAPSCRNID_R122DUN01_4
#define TData_cave_d0805	MAPSCRNID_R122DUN01_5
#define TData_cave_d0806	MAPSCRNID_R122DUN01_6
#define TData_cave_d0807	MAPSCRNID_R122DUN02_1
#define TData_cave_d0808	MAPSCRNID_R122DUN02_2
#define TData_cave_d0901	MAPSCRNID_C106DUN01_1
#define TData_cave_d0902	MAPSCRNID_C106DUN01_B1
#define TData_cave_d0903	MAPSCRNID_C106DUN01_B2
#define TData_cave_d1101	MAPSCRNID_W128DUN01_1
#define TData_cave_d1102	MAPSCRNID_W128DUN01_2
#define TData_cave_d1103	MAPSCRNID_W128DUN01_3
#define TData_cave_d1104	MAPSCRNID_W128DUN01_4
#define TData_cave_d1105	MAPSCRNID_W128DUN01_5
#define TData_cave_d1106	MAPSCRNID_W128DUN01_6
#define TData_cave_d1107	MAPSCRNID_W128DUN01_7
#define TData_cave_d1108	MAPSCRNID_W128DUN01_8
#define TData_cave_d1109	MAPSCRNID_W128DUN01_9
#define TData_cave_d1110	MAPSCRNID_W128DUN01_10
#define TData_cave_d1111	MAPSCRNID_W128DUN01_11
#define TData_cave_d1201	MAPSCRNID_C108DUN01_1
#define TData_cave_d1202	MAPSCRNID_C108DUN01_2
#define TData_cave_d1203	MAPSCRNID_C108DUN01_3
#define TData_cave_d1204	MAPSCRNID_C108DUN01_4
#define TData_cave_d1205	MAPSCRNID_C108DUN01_5
#define TData_cave_d1206	MAPSCRNID_C108DUN01_6
#define TData_cave_d1301	MAPSCRNID_C109DUN01_1
#define TData_cave_d1302	MAPSCRNID_C109DUN01_2
#define TData_cave_d1303	MAPSCRNID_C109DUN01_3
#define TData_cave_d1401	MAPSCRNID_R125DUN01_1
#define TData_cave_d1402	MAPSCRNID_R125DUN01_2
#define TData_cave_d1403	MAPSCRNID_R125DUN01_3
#define TData_cave_d1404	MAPSCRNID_R125DUN01_4
#define TData_cave_d1405	MAPSCRNID_R125DUN02_1
#define TData_cave_d1406	MAPSCRNID_R125DUN02_2
#define TData_cave_d1601	MAPSCRNID_R110DUN01_1
#define TData_cave_d1602	MAPSCRNID_R110DUN01_2
#define TData_cave_d1701	MAPSCRNID_R108DUN01_1
#define TData_cave_d1702	MAPSCRNID_R108DUN01_2
#define TData_cave_d1703	MAPSCRNID_R108DUN01_3
#define TData_cave_d1704	MAPSCRNID_R108DUN01_4
#define TData_cave_d1705	MAPSCRNID_R108DUN01_5
#define TData_cave_d1706	MAPSCRNID_R108DUN01_6
#define TData_cave_d1707	MAPSCRNID_R108DUN01_7
#define TData_cave_d1708	MAPSCRNID_R108DUN01_8
#define TData_cave_d1709	MAPSCRNID_R108DUN01_9
#define TData_cave_d1710	MAPSCRNID_R108DUN01_10
#define TData_cave_d1711	MAPSCRNID_R108DUN01_11
#define TData_cave_d1712	MAPSCRNID_R108DUN01_12
#define TData_cave_d1713	MAPSCRNID_R108DUN01_13
#define TData_cave_d1801	MAPSCRNID_R105DUN01_1
#define TData_cave_d1901	MAPSCRNID_R120DUN01_1
#define TData_cave_d2001	MAPSCRNID_W134DUN01_1
#define TData_cave_d2002	MAPSCRNID_W134DUN01_2
#define TData_cave_d2003	MAPSCRNID_W134DUN01_3
#define TData_cave_d2004	MAPSCRNID_W134DUN01_4
#define TData_cave_d2101	MAPSCRNID_R120DUN02_1
#define TData_cave_d2201	MAPSCRNID_C106DUN02_1
#define TData_cave_d2202	MAPSCRNID_C106DUN02_2
#define TData_cave_d2203	MAPSCRNID_C106DUN02_B1
#define TData_cave_d2301	MAPSCRNID_R131DUN01_2
#define TData_cave_d2302	MAPSCRNID_R131DUN01_3
#define TData_cave_d2303	MAPSCRNID_R131DUN01_4
#define TData_cave_d2304	MAPSCRNID_R131DUN01_5
#define TData_cave_d2305	MAPSCRNID_R131DUN01_6
#define TData_cave_d2306	MAPSCRNID_R131DUN01_7
#define TData_cave_d1407	MAPSCRNID_R125DUN01_5
#define TData_cave_d2307	MAPSCRNID_R131DUN01_8
#define TData_cave_d2308	MAPSCRNID_R131DUN01_9
#define TData_sp_base01	MAPSCRNID_H_TSUCHI_01
#define TData_sp_base02	MAPSCRNID_H_ISHI_01
#define TData_sp_base03	MAPSCRNID_H_SIME_01
#define TData_sp_base04	MAPSCRNID_H_SUNA_01
#define TData_sp_base05	MAPSCRNID_H_KINOUE_01
#define TData_sp_base06	MAPSCRNID_H_KUSA_01
#define TData_sp_base07	MAPSCRNID_H_TSUCHI_02
#define TData_sp_base08	MAPSCRNID_H_ISHI_02
#define TData_sp_base09	MAPSCRNID_H_SIME_02
#define TData_sp_base10	MAPSCRNID_H_SUNA_02
#define TData_sp_base11	MAPSCRNID_H_KINOUE_02
#define TData_sp_base12	MAPSCRNID_H_KUSA_02
#define TData_sp_base13	MAPSCRNID_H_TSUCHI_03
#define TData_sp_base14	MAPSCRNID_H_ISHI_03
#define TData_sp_base15	MAPSCRNID_H_SIME_03
#define TData_sp_base16	MAPSCRNID_H_SUNA_03
#define TData_sp_base17	MAPSCRNID_H_KINOUE_03
#define TData_sp_base18	MAPSCRNID_H_KUSA_03
#define TData_sp_base19	MAPSCRNID_H_TSUCHI_04
#define TData_sp_base20	MAPSCRNID_H_ISHI_04
#define TData_sp_base21	MAPSCRNID_H_SIME_04
#define TData_sp_base22	MAPSCRNID_H_SUNA_04
#define TData_sp_base23	MAPSCRNID_H_KINOUE_04
#define TData_sp_base24	MAPSCRNID_H_KUSA_04
#define TData_sp_pc03	MAPSCRNID_PC03
#define TData_sp_pc04	MAPSCRNID_PC04
#define TData_sp_pc05	MAPSCRNID_PC05
#define TData_sp_pc06	MAPSCRNID_PC06
#define TData_sp_contest03_1	MAPSCRNID_CONTEST03_1
#define TData_sp_contest03_2	MAPSCRNID_CONTEST03_2
#define TData_sp_contest03_3	MAPSCRNID_CONTEST03_3
#define TData_sp_contest03_4	MAPSCRNID_CONTEST03_4
#define TData_sp_contest03_5	MAPSCRNID_CONTEST03_5
#define TData_sp_contest03_6	MAPSCRNID_CONTEST03_6
#define TData_sp_contest03_7	MAPSCRNID_CONTEST03_7
#define TData_sp_contest03_8	MAPSCRNID_CONTEST03_8
#define TData_sp_contest03_9	MAPSCRNID_CONTEST03_9
#define TData_sp_contest03_10	MAPSCRNID_CONTEST03_10
#define TData_sp_contest03_11	MAPSCRNID_CONTEST03_11
#define TData_sp_contest03_12	MAPSCRNID_CONTEST03_12
#define TData_sp_truck	MAPSCRNID_TRUCK
#define TData_sp_ship01	MAPSCRNID_SHIP01_1
#define TData_sp_ship02	MAPSCRNID_SHIP01_2
#define TData_sp_ship03	MAPSCRNID_SHIP01_3
#define TData_park_safari01	MAPSCRNID_SAFARI01_1
#define TData_park_safari02	MAPSCRNID_SAFARI01_2
#define TData_park_safari03	MAPSCRNID_SAFARI01_3
#define TData_park_safari04	MAPSCRNID_SAFARI01_4
#define TData_park_tower01	MAPSCRNID_TOWER01_1
#define TData_park_battle01	MAPSCRNID_BATTLE01_1
#define TData_park_battle02	MAPSCRNID_BATTLE01_2
#define TData_park_battle03	MAPSCRNID_BATTLE01_3
#define TData_park_battle04	MAPSCRNID_BATTLE01_4
#define TData_park_kokoro01	MAPSCRNID_KOKORO01_1
#define TData_park_kokoro02	MAPSCRNID_KOKORO01_2
#define TData_park_safari05	MAPSCRNID_SAFARI_ROOM
#define TData_test_newtown	MAPSCRNID_ROAD104_1
#define TData_test_newtown2	MAPSCRNID_FLWSP
#define TData_r109_r0101	MAPSCRNID_UMINOIE
#define TData_r110_r0101	MAPSCRNID_KARAKURI01_1
#define TData_r110_r0102	MAPSCRNID_KARAKURI01_2
#define TData_r110_r0103	MAPSCRNID_KARAKURI01_3
#define TData_r110_r0104	MAPSCRNID_KARAKURI01_4
#define TData_r110_r0105	MAPSCRNID_KARAKURI01_5
#define TData_r110_r0106	MAPSCRNID_KARAKURI01_6
#define TData_r110_r0107	MAPSCRNID_KARAKURI01_7
#define TData_r110_r0108	MAPSCRNID_KARAKURI01_8
#define TData_r110_r0109	MAPSCRNID_KARAKURI01_9
#define TData_r110_r0110	MAPSCRNID_KARAKURI01_10
#define TData_r110_r0111	MAPSCRNID_KARAKURI01_11
#define TData_r110_r0201	MAPSCRNID_GATE01_1
#define TData_r110_r0301	MAPSCRNID_GATE01_1
#define TData_r113_r0101	MAPSCRNID_MINKA02_2
#define TData_r123_r0201	MAPSCRNID_MINKA01_1
#define TData_r119_r0101	MAPSCRNID_TENKI01_1
#define TData_r119_r0102	MAPSCRNID_TENKI01_2
#define TData_r119_r0201	MAPSCRNID_MINKA01_2
#define TData_r124_r0101	MAPSCRNID_TREASURE01_1

static
const unsigned short DivData_field[DIVISION_FIELD_MAX] =
{
        TData_field_c101,
        TData_field_c102,
        TData_field_c103,
        TData_field_c104,
        TData_field_c105,
        TData_field_c106,
        TData_field_c107,
        TData_field_c108,
        TData_field_c109,
        TData_field_t101,
        TData_field_t102,
        TData_field_t103,
        TData_field_t104,
        TData_field_t105,
        TData_field_t106,
        TData_field_t107,
        TData_field_r101,
        TData_field_r102,
        TData_field_r103,
        TData_field_r104,
        TData_field_r105,
        TData_field_r106,
        TData_field_r107,
        TData_field_r108,
        TData_field_r109,
        TData_field_r110,
        TData_field_r111,
        TData_field_r112,
        TData_field_r113,
        TData_field_r114,
        TData_field_r115,
        TData_field_r116,
        TData_field_r117,
        TData_field_r118,
        TData_field_r119,
        TData_field_r120,
        TData_field_r121,
        TData_field_r122,
        TData_field_r123,
        TData_field_r124,
        TData_field_r125,
        TData_field_r126,
        TData_field_r127,
        TData_field_r128,
        TData_field_r129,
        TData_field_r130,
        TData_field_r131,
        TData_field_r132,
        TData_field_r133,
        TData_field_r134,
        TData_field_w124,
        TData_field_w126,
        TData_field_w127,
        TData_field_w128,
};


static
const unsigned short DivData_t101[DIVISION_T101_MAX] =
{
        TData_t101_r0101,
        TData_t101_r0102,
        TData_t101_r0201,
        TData_t101_r0202,
        TData_t101_r0301,
};


static
const unsigned short DivData_t102[DIVISION_T102_MAX] =
{
        TData_t102_r0101,
        TData_t102_r0201,
        TData_t102_pc01,
        TData_t102_pc02,
        TData_t102_fs01,
};


static
const unsigned short DivData_t103[DIVISION_T103_MAX] =
{
        TData_t103_r0101,
        TData_t103_pc01,
        TData_t103_pc02,
        TData_t103_r0201,
        TData_t103_r0301,
        TData_t103_r0401,
};


static
const unsigned short DivData_t104[DIVISION_T104_MAX] =
{
        TData_t104_r0101,
        TData_t104_r0201,
        TData_t104_r0202,
        TData_t104_r0301,
        TData_t104_fs01,
        TData_t104_pc01,
        TData_t104_pc02,
};


static
const unsigned short DivData_t105[DIVISION_T105_MAX] =
{
        TData_t105_fs01,
        TData_t105_r0101,
        TData_t105_r0102,
        TData_t105_pc01,
        TData_t105_pc02,
        TData_t105_r0201,
        TData_t105_r0301,
};


static
const unsigned short DivData_t106[DIVISION_T106_MAX] =
{
        TData_t106_r0101,
        TData_t106_r0102,
        TData_t106_fs01,
        TData_t106_pc01,
        TData_t106_pc02,
        TData_t106_r0201,
        TData_t106_r0301,
        TData_t106_r0401,
};


static
const unsigned short DivData_t107[DIVISION_T107_MAX] =
{
        TData_t107_pc01,
        TData_t107_pc02,
        TData_t107_r0101,
        TData_t107_r0201,
        TData_t107_r0301,
        TData_t107_r0401,
        TData_t107_r0501,
};


static
const unsigned short DivData_c101[DIVISION_C101_MAX] =
{
        TData_c101_r0101,
        TData_c101_r0201,
        TData_c101_r0301,
        TData_c101_r0401,
        TData_c101_pc01,
        TData_c101_pc02,
        TData_c101_fs01,
};


static
const unsigned short DivData_c102[DIVISION_C102_MAX] =
{
        TData_c102_r0101,
        TData_c102_r0102,
        TData_c102_r0201,
        TData_c102_r0202,
        TData_c102_r0301,
        TData_c102_r0401,
        TData_c102_r0501,
        TData_c102_r0502,
        TData_c102_r0601,
        TData_c102_r0701,
        TData_c102_pc01,
        TData_c102_pc02,
        TData_c102_fs01,
};


static
const unsigned short DivData_c103[DIVISION_C103_MAX] =
{
        TData_c103_r0101,
        TData_c103_r0201,
        TData_c103_r0301,
        TData_c103_r0401,
        TData_c103_r0501,
        TData_c103_pc01,
        TData_c103_pc02,
        TData_c103_fs01,
};


static
const unsigned short DivData_c104[DIVISION_C104_MAX] =
{
        TData_c104_r0101,
        TData_c104_r0102,
        TData_c104_r0103,
        TData_c104_r0201,
        TData_c104_r0301,
        TData_c104_pc01,
        TData_c104_pc02,
        TData_c104_fs01,
        TData_c104_r0401,
        TData_c104_r0402,
        TData_c104_r0501,
        TData_c104_r0601,
        TData_c104_r0701,
        TData_c104_r0801,
        TData_c104_r0802,
        TData_c104_r0803,
        TData_c104_r0901,
};


static
const unsigned short DivData_c105[DIVISION_C105_MAX] =
{
        TData_c105_r0101,
        TData_c105_r0201,
        TData_c105_pc01,
        TData_c105_pc02,
        TData_c105_fs01,
        TData_c105_r0301,
        TData_c105_r0401,
        TData_c105_r0501,
        TData_c105_r0601,
        TData_c105_r0701,
};


static
const unsigned short DivData_c106[DIVISION_C106_MAX] =
{
        TData_c106_r0101,
        TData_c106_r0102,
        TData_c106_r0201,
        TData_c106_r0202,
        TData_c106_r0301,
        TData_c106_r0302,
        TData_c106_pc01,
        TData_c106_pc02,
        TData_c106_fs01,
        TData_c106_r0401,
        TData_c106_r0501,
        TData_c106_r0502,
        TData_c106_r0601,
        TData_c106_r0701,
        TData_c106_r0801,
        TData_c106_r0901,
        TData_c106_r1001,
        TData_c106_r1101,
        TData_c106_r1102,
        TData_c106_r1103,
        TData_c106_r1104,
        TData_c106_r1105,
        TData_c106_r1106,
        TData_c106_r1201,
};


static
const unsigned short DivData_c107[DIVISION_C107_MAX] =
{
        TData_c107_r0101,
        TData_c107_r0201,
        TData_c107_r0301,
        TData_c107_pc01,
        TData_c107_pc02,
        TData_c107_fs01,
        TData_c107_r0401,
        TData_c107_r0501,
        TData_c107_r0601,
        TData_c107_r0701,
        TData_c107_r0702,
        TData_c107_r0801,
        TData_c107_r0802,
};


static
const unsigned short DivData_c108[DIVISION_C108_MAX] =
{
        TData_c108_r0101,
        TData_c108_r0102,
        TData_c108_pc01,
        TData_c108_pc02,
        TData_c108_fs01,
        TData_c108_r0201,
        TData_c108_r0301,
        TData_c108_r0401,
        TData_c108_r0501,
        TData_c108_r0601,
        TData_c108_r0701,
        TData_c108_r0801,
        TData_c108_r0901,
};


static
const unsigned short DivData_c109[DIVISION_C109_MAX] =
{
        TData_c109_r0101,
        TData_c109_r0102,
        TData_c109_r0103,
        TData_c109_r0104,
        TData_c109_r0105,
        TData_c109_r0201,
        TData_c109_r0202,
        TData_c109_r0203,
        TData_c109_r0204,
        TData_c109_r0205,
        TData_c109_r0206,
        TData_c109_r0301,
        TData_c109_pc01,
        TData_c109_pc02,
};


static
const unsigned short DivData_r104[DIVISION_R104_MAX] =
{
        TData_r104_r0101,
        TData_r104_r0201,
};


static
const unsigned short DivData_r111[DIVISION_R111_MAX] =
{
        TData_r111_r0101,
        TData_r111_r0201,
};


static
const unsigned short DivData_r112[DIVISION_R112_MAX] =
{
        TData_r112_r0101,
        TData_r112_r0102,
};


static
const unsigned short DivData_r114[DIVISION_R114_MAX] =
{
        TData_r114_r0101,
        TData_r114_r0102,
        TData_r114_r0201,
};


static
const unsigned short DivData_r116[DIVISION_R116_MAX] =
{
        TData_r116_r0101,
};


static
const unsigned short DivData_r117[DIVISION_R117_MAX] =
{
        TData_r117_r0101,
};


static
const unsigned short DivData_r121[DIVISION_R121_MAX] =
{
        TData_r121_r0101,
};


static
const unsigned short DivData_cave[DIVISION_CAVE_MAX] =
{
        TData_cave_d0101,
        TData_cave_d0102,
        TData_cave_d0103,
        TData_cave_d0104,
        TData_cave_d0201,
        TData_cave_d0301,
        TData_cave_d0401,
        TData_cave_d0501,
        TData_cave_d0502,
        TData_cave_d0503,
        TData_cave_d0504,
        TData_cave_d0601,
        TData_cave_d0701,
        TData_cave_d0702,
        TData_cave_d0703,
        TData_cave_d0801,
        TData_cave_d0802,
        TData_cave_d0803,
        TData_cave_d0804,
        TData_cave_d0805,
        TData_cave_d0806,
        TData_cave_d0807,
        TData_cave_d0808,
        TData_cave_d0901,
        TData_cave_d0902,
        TData_cave_d0903,
        TData_cave_d1101,
        TData_cave_d1102,
        TData_cave_d1103,
        TData_cave_d1104,
        TData_cave_d1105,
        TData_cave_d1106,
        TData_cave_d1107,
        TData_cave_d1108,
        TData_cave_d1109,
        TData_cave_d1110,
        TData_cave_d1111,
        TData_cave_d1201,
        TData_cave_d1202,
        TData_cave_d1203,
        TData_cave_d1204,
        TData_cave_d1205,
        TData_cave_d1206,
        TData_cave_d1301,
        TData_cave_d1302,
        TData_cave_d1303,
        TData_cave_d1401,
        TData_cave_d1402,
        TData_cave_d1403,
        TData_cave_d1404,
        TData_cave_d1405,
        TData_cave_d1406,
        TData_cave_d1601,
        TData_cave_d1602,
        TData_cave_d1701,
        TData_cave_d1702,
        TData_cave_d1703,
        TData_cave_d1704,
        TData_cave_d1705,
        TData_cave_d1706,
        TData_cave_d1707,
        TData_cave_d1708,
        TData_cave_d1709,
        TData_cave_d1710,
        TData_cave_d1711,
        TData_cave_d1712,
        TData_cave_d1713,
        TData_cave_d1801,
        TData_cave_d1901,
        TData_cave_d2001,
        TData_cave_d2002,
        TData_cave_d2003,
        TData_cave_d2004,
        TData_cave_d2101,
        TData_cave_d2201,
        TData_cave_d2202,
        TData_cave_d2203,
        TData_cave_d2301,
        TData_cave_d2302,
        TData_cave_d2303,
        TData_cave_d2304,
        TData_cave_d2305,
        TData_cave_d2306,
        TData_cave_d1407,
        TData_cave_d2307,
        TData_cave_d2308,
};


static
const unsigned short DivData_sp[DIVISION_SP_MAX] =
{
        TData_sp_base01,
        TData_sp_base02,
        TData_sp_base03,
        TData_sp_base04,
        TData_sp_base05,
        TData_sp_base06,
        TData_sp_base07,
        TData_sp_base08,
        TData_sp_base09,
        TData_sp_base10,
        TData_sp_base11,
        TData_sp_base12,
        TData_sp_base13,
        TData_sp_base14,
        TData_sp_base15,
        TData_sp_base16,
        TData_sp_base17,
        TData_sp_base18,
        TData_sp_base19,
        TData_sp_base20,
        TData_sp_base21,
        TData_sp_base22,
        TData_sp_base23,
        TData_sp_base24,
        TData_sp_pc03,
        TData_sp_pc04,
        TData_sp_pc05,
        TData_sp_pc06,
        TData_sp_contest03_1,
        TData_sp_contest03_2,
        TData_sp_contest03_3,
        TData_sp_contest03_4,
        TData_sp_contest03_5,
        TData_sp_contest03_6,
        TData_sp_contest03_7,
        TData_sp_contest03_8,
        TData_sp_contest03_9,
        TData_sp_contest03_10,
        TData_sp_contest03_11,
        TData_sp_contest03_12,
        TData_sp_truck,
        TData_sp_ship01,
        TData_sp_ship02,
        TData_sp_ship03,
};


static
const unsigned short DivData_park[DIVISION_PARK_MAX] =
{
        TData_park_safari01,
        TData_park_safari02,
        TData_park_safari03,
        TData_park_safari04,
        TData_park_tower01,
        TData_park_battle01,
        TData_park_battle02,
        TData_park_battle03,
        TData_park_battle04,
        TData_park_kokoro01,
        TData_park_kokoro02,
        TData_park_safari05,
};


static
const unsigned short DivData_test[DIVISION_TEST_MAX] =
{
        TData_test_newtown,
        TData_test_newtown2,
};


static
const unsigned short DivData_r109[DIVISION_R109_MAX] =
{
        TData_r109_r0101,
};


static
const unsigned short DivData_r110[DIVISION_R110_MAX] =
{
        TData_r110_r0101,
        TData_r110_r0102,
        TData_r110_r0103,
        TData_r110_r0104,
        TData_r110_r0105,
        TData_r110_r0106,
        TData_r110_r0107,
        TData_r110_r0108,
        TData_r110_r0109,
        TData_r110_r0110,
        TData_r110_r0111,
        TData_r110_r0201,
        TData_r110_r0301,
};


static
const unsigned short DivData_r113[DIVISION_R113_MAX] =
{
        TData_r113_r0101,
};


static
const unsigned short DivData_r123[DIVISION_R123_MAX] =
{
        TData_r123_r0201,
};


static
const unsigned short DivData_r119[DIVISION_R119_MAX] =
{
        TData_r119_r0101,
        TData_r119_r0102,
        TData_r119_r0201,
};


static
const unsigned short DivData_r124[DIVISION_R124_MAX] =
{
        TData_r124_r0101,
};


const unsigned short * const rsmap_DivisionList[DIVISION_ID_MAX] =
{
        DivData_field,
        DivData_t101,
        DivData_t102,
        DivData_t103,
        DivData_t104,
        DivData_t105,
        DivData_t106,
        DivData_t107,
        DivData_c101,
        DivData_c102,
        DivData_c103,
        DivData_c104,
        DivData_c105,
        DivData_c106,
        DivData_c107,
        DivData_c108,
        DivData_c109,
        DivData_r104,
        DivData_r111,
        DivData_r112,
        DivData_r114,
        DivData_r116,
        DivData_r117,
        DivData_r121,
        DivData_cave,
        DivData_sp,
        DivData_park,
        DivData_test,
        DivData_r109,
        DivData_r110,
        DivData_r113,
        DivData_r123,
        DivData_r119,
        DivData_r124,
};


