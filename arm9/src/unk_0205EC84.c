#include "unk_0205EC84.h"

#include "global.h"

#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/sndseq.h"

#include "proto.h"

static void _flag_set(struct SaveVarsFlags *state, u16 flag_id) {
    Save_VarsFlags_SetFlagInArray(state, flag_id);
}

static void _flag_clear(struct SaveVarsFlags *state, u16 flag_id) {
    Save_VarsFlags_ClearFlagInArray(state, flag_id);
}

static BOOL _flag_check(struct SaveVarsFlags *state, u16 flag_id) {
    return Save_VarsFlags_CheckFlagInArray(state, flag_id);
}

static BOOL _flag_op(struct SaveVarsFlags *state, u32 op, u32 flag_id) {
    switch (op) {
    case 1:
        _flag_set(state, (u16)flag_id);
        break;
    case 0:
        _flag_clear(state, (u16)flag_id);
        break;
    case 2:
        return _flag_check(state, (u16)flag_id);
    default:
        GF_ASSERT(0);
    }
    return FALSE;
}

void sub_0205ECD4(struct SaveVarsFlags *state) {
    _flag_set(state, 0x960);
}

BOOL sub_0205ECE0(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x960);
}

BOOL sub_0205ECEC(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x98D);
}

void sub_0205ECFC(struct SaveVarsFlags *state) {
    _flag_set(state, 0x964);
}

BOOL sub_0205ED0C(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x964);
}

void sub_0205ED1C(struct SaveVarsFlags *state) {
    _flag_set(state, 0x961);
}

void sub_0205ED2C(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x961);
}

BOOL Save_VarsFlags_CheckHaveFollower(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x961);
}

void sub_0205ED4C(struct SaveVarsFlags *state) {
    _flag_set(state, 0x965);
}

void sub_0205ED5C(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x965);
}

BOOL sub_0205ED6C(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x965);
}

void sub_0205ED7C(struct SaveVarsFlags *state) {
    _flag_set(state, 0x96D);
}

void sub_0205ED8C(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x96D);
}

BOOL sub_0205ED9C(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x96D);
}

void sub_0205EDAC(struct SaveVarsFlags *state) {
    _flag_set(state, 0x96E);
}

void sub_0205EDBC(struct SaveVarsFlags *state) {
    _flag_set(state, 0x96F);
}

void sub_0205EDCC(struct SaveVarsFlags *state) {
    _flag_set(state, 0x970);
}

void sub_0205EDD8(struct SaveVarsFlags *state) {
    _flag_set(state, 0x971);
}

void sub_0205EDE8(struct SaveVarsFlags *state) {
    _flag_set(state, 0x972);
}

void sub_0205EDF8(struct SaveVarsFlags *state) {
    _flag_set(state, 0x973);
}

void sub_0205EE08(struct SaveVarsFlags *state, u32 a1) {
    switch (a1) {
    case 0:
        _flag_set(state, 0x968);
        break;
    case 1:
        _flag_set(state, 0x969);
        break;
    case 2:
        _flag_set(state, 0x96A);
        break;
    case 3:
        _flag_set(state, 0x96B);
        break;
    case 4:
        _flag_set(state, 0x96C);
        break;
    }
}

BOOL sub_0205EE60(struct SaveVarsFlags *state, u32 a1) {
    switch (a1) {
    case 0:
        return _flag_check(state, 0x968);
    case 1:
        return _flag_check(state, 0x969);
    case 2:
        return _flag_check(state, 0x96A);
    case 3:
        return _flag_check(state, 0x96B);
    case 4:
        return _flag_check(state, 0x96C);
    }
    // UB: No return value
}

BOOL sub_0205EEB8(struct SaveVarsFlags *state, u32 a1) {
    BOOL ret = FALSE;
    switch (a1) {
    case 0:
        break;
    case 1:
        ret = _flag_check(state, 0x97F);
        break;
    case 2:
        ret = _flag_check(state, 0x980);
        break;
    case 3:
        ret = _flag_check(state, 0x981);
        break;
    case 4:
        ret = _flag_check(state, 0x982);
        break;
    case 5:
        ret = _flag_check(state, 0x983);
        break;
    }
    return ret;
}

s32 sub_0205EF20(struct SaveVarsFlags *state, s32 a1) {
    s32 ret = 0;
    switch (a1) {
    case MAP_D28R0101:
        if (_flag_check(state, 0x984) == TRUE) {
            ret = SEQ_D_LAKE;
        }
        break;
    case MAP_D28R0103:
        if (_flag_check(state, 0x984) == TRUE) {
            ret = SEQ_D_RYAYHY;
        }
        break;
    case MAP_D27R0102:
        if (_flag_check(state, 0x98E) == TRUE) {
            ret = SEQ_D_LAKE;
        }
        break;
    case MAP_D29R0102:
        if (_flag_check(state, 0x98F) == TRUE) {
            ret = SEQ_D_LAKE;
        }
        break;
    case MAP_D10R0101:
        if (_flag_check(state, 0x995) == TRUE) {
            ret = SEQ_D_SAFARI;
        }
        break;
    case MAP_T02R0101:
        if (_flag_check(state, 0x993) == TRUE) {
            ret = SEQ_OPENING2;
        }
        break;
    case MAP_D26R0101:
    case MAP_D26R0102:
    case MAP_D26R0103:
    case MAP_D26R0104:
    case MAP_D26R0105:
    case MAP_D26R0106:
    case MAP_D26R0107:
    case MAP_D26R0108:
        if (_flag_check(state, 0x985) == TRUE) {
            if (!IsNighttime()) {
                ret = SEQ_CITY07_D;
            } else {
                ret = SEQ_CITY07_N;
            }
        } else if (a1 == MAP_D26R0101) {
            if (_flag_check(state, 0x986) == TRUE) {
                ret = SEQ_D_AGITO;
            }
        }
        break;
    case MAP_C04R0201:
    case MAP_C04R0202:
    case MAP_C04R0203:
    case MAP_C04R0204:
        if (_flag_check(state, 0x987) == TRUE) {
            if (!IsNighttime()) {
                ret = SEQ_CITY04_D;
            } else {
                ret = SEQ_CITY04_N;
            }
        }
        break;
    case MAP_D02R0101:
        if (_flag_check(state, 0x988) == TRUE) {
            if (!IsNighttime()) {
                ret = SEQ_ROAD_C_D;
            } else {
                ret = SEQ_ROAD_C_N;
            }
        }
        break;
    case MAP_D13R0101:
        if (_flag_check(state, 0x989) == TRUE) {
            if (!IsNighttime()) {
                ret = SEQ_TOWN03_D;
            } else {
                ret = SEQ_TOWN03_N;
            }
        }
        break;
    case MAP_R224:
        if (_flag_check(state, 0x98A) == TRUE) {
            if (!IsNighttime()) {
                ret = SEQ_TOWN03_D;
            } else {
                ret = SEQ_TOWN03_N;
            }
        }
        break;
    case MAP_C10R0111:
        if (_flag_check(state, 0x98B) == TRUE) {
            ret = SEQ_SILENCE_FIELD;
        }
        break;
    }
    return ret;
}

void sub_0205F154(struct SaveVarsFlags *state) {
    _flag_set(state, 0x966);
}

void sub_0205F164(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x966);
}

BOOL sub_0205F174(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x966);
}

BOOL sub_0205F184(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x978);
}

BOOL sub_0205F194(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x992);
}

BOOL sub_0205F1A4(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x97D);
}

BOOL sub_0205F1B4(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x97E);
}

void sub_0205F1C4(struct SaveVarsFlags *state) {
    _flag_set(state, 0x97C);
}

void sub_0205F1D4(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x97C);
}

BOOL sub_0205F1E4(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x97C);
}

void Save_VarsFlags_SetSafariSysFlag(struct SaveVarsFlags *state) {
    _flag_set(state, FLAG_SYS_SAFARI);
}

void Save_VarsFlags_ClearSafariSysFlag(struct SaveVarsFlags *state) {
    _flag_clear(state, FLAG_SYS_SAFARI);
}

BOOL Save_VarsFlags_CheckSafariSysFlag(struct SaveVarsFlags *state) // Save_VarsFlags_CheckSafariSysFlag?
{
    return _flag_check(state, FLAG_SYS_SAFARI);
}

void sub_0205F224(struct SaveVarsFlags *state) {
    _flag_set(state, 0x979);
}

void sub_0205F234(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x979);
}

BOOL sub_0205F244(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x979);
}

void sub_0205F254(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x994);
}

BOOL sub_0205F264(struct SaveVarsFlags *state, u32 op) {
    return _flag_op(state, op, 0x962);
}

void sub_0205F274(struct SaveVarsFlags *state) {
    _flag_set(state, 0x97A);
}

void sub_0205F284(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x97A);
}

BOOL sub_0205F294(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x97A);
}

void sub_0205F2A4(struct SaveVarsFlags *state) {
    _flag_set(state, 0x97B);
}

void sub_0205F2B4(struct SaveVarsFlags *state) {
    _flag_clear(state, 0x97B);
}

BOOL sub_0205F2C4(struct SaveVarsFlags *state) {
    return _flag_check(state, 0x97B);
}

BOOL sub_0205F2D4(struct SaveVarsFlags *state, u32 op) {
    return _flag_op(state, op, 0x963);
}

BOOL sub_0205F2E4(struct SaveVarsFlags *state, u32 op, u16 flag_id) {
    GF_ASSERT(flag_id < 69);
    return _flag_op(state, op, 0x9B0 + flag_id);
}

void sub_0205F304(struct SaveVarsFlags *state) {
    _flag_set(state, 0x98C);
}
