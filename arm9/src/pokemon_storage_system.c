#include "pokemon_storage_system.h"

#include "global.h"

#include "msgdata/msg.naix"

#include "msgdata.h"
#include "pokemon.h"
#include "save.h"
#include "string16.h"

void PCStorage_Init(struct PCStorage *pc) {
    PCStorage_InitializeBoxes(pc);
    Save_SetDirtyBit();
}

u32 PCStorage_sizeof(void) {
    return sizeof(struct PCStorage);
}

void PCStorage_InitializeBoxes(struct PCStorage *pc) {
    int i, j;
    for (i = 0; i < NUM_BOXES; i++) {
        for (j = 0; j < MONS_PER_BOX; j++) {
            ZeroBoxMonData(&pc->boxes[i][j]);
        }
    }
    for (i = 0, j = 0; i < NUM_BOXES; i++) {
        pc->wallpapers[i] = (u8)j;
        j++;
        if (j >= NUM_DEFAULT_WALLPAPERS) {
            j = 0;
        }
    }
    pc->unlockedWallpapers = 0;
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0014_bin, HEAP_ID_DEFAULT);
    if (msgData != NULL) {
        for (i = 0; i < NUM_BOXES; i++) {
            ReadMsgDataIntoU16Array(msgData, (u32)(i + 6), pc->names[i]);
        }
        DestroyMsgData(msgData);
    }
    pc->curBox = 0;
}

BOOL PCStorage_PlaceMonInFirstEmptySlotInAnyBox(struct PCStorage *pc, struct BoxPokemon *boxmon) {
    int i = (int)pc->curBox;
    do {
        RestoreBoxMonPP(boxmon);
        if (PCStorage_PlaceMonInBoxFirstEmptySlot(pc, i, boxmon)) {
            Save_SetDirtyBit();
            return TRUE;
        }
        i++;
        if (i >= NUM_BOXES) {
            i = 0;
        }
    } while (i != pc->curBox);
    return FALSE;
}

BOOL PCStorage_PlaceMonInBoxFirstEmptySlot(struct PCStorage *pc, int boxno, struct BoxPokemon *boxmon) {
    RestoreBoxMonPP(boxmon);
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    for (int i = 0; i < MONS_PER_BOX; i++) {
        if (GetBoxMonData(&pc->boxes[boxno][i], MON_DATA_SPECIES, NULL) == SPECIES_NONE) {
            pc->boxes[boxno][i] = *boxmon;
            Save_SetDirtyBit();
            return TRUE;
        }
    }
    return FALSE;
}

BOOL PCStorage_PlaceMonInBoxByIndexPair(struct PCStorage *pc, int boxno, int slotno, struct BoxPokemon *boxmon) {
    RestoreBoxMonPP(boxmon);
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES && slotno < MONS_PER_BOX) {
        pc->boxes[boxno][slotno] = *boxmon;
        Save_SetDirtyBit();
        return TRUE;
    }
    GF_ASSERT(0);
    return FALSE;
}

void PCStorage_DeleteBoxMonByIndexPair(struct PCStorage *pc, int boxno, int slotno) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (slotno < MONS_PER_BOX && boxno < NUM_BOXES) {
        ZeroBoxMonData(&pc->boxes[boxno][slotno]);
        Save_SetDirtyBit();
        return;
    }
    GF_ASSERT(0);
}

int PCStorage_GetActiveBox(struct PCStorage *pc) {
    return (int)pc->curBox;
}

int PCStorage_FindFirstBoxWithEmptySlot(struct PCStorage *pc) {
    int i, j;
    i = (int)pc->curBox;
    do {
        for (j = 0; j < (int)MONS_PER_BOX; j++) {
            if (!GetBoxMonData(&pc->boxes[i][j], MON_DATA_SPECIES_EXISTS, NULL)) {
                return i;
            }
        }
        i++;
        if (i >= (int)NUM_BOXES) {
            i = 0;
        }
    } while (i != pc->curBox);
    return (int)NUM_BOXES;
}

BOOL PCStorage_FindFirstEmptySlot(struct PCStorage *pc, int *boxno, int *slotno) {
    if (*boxno == -1) {
        *boxno = (int)pc->curBox;
    }
    int i = *boxno, j = *slotno;
    do {
        while (j < (int)MONS_PER_BOX) {
            if (!GetBoxMonData(&pc->boxes[i][j], MON_DATA_SPECIES_EXISTS, NULL)) {
                *boxno = i;
                *slotno = j;
                return TRUE;
            }
            j++;
        }
        i++;
        if (i >= (int)NUM_BOXES) {
            i = 0;
        }
        if (i == *boxno) {
            break;
        }
        j = 0;
    } while (1);
    return (int)NUM_BOXES; // bug: should return FALSE if reached
}

int PCStorage_CountMonsAndEggsInAllBoxes(struct PCStorage *pc) {
    int i, j, count = 0;
    for (i = 0; i < (int)NUM_BOXES; i++) {
        for (j = 0; j < (int)MONS_PER_BOX; j++) {
            if (GetBoxMonData(&pc->boxes[i][j], MON_DATA_SPECIES_EXISTS, NULL)) {
                count++;
            }
        }
    }
    return count;
}

void PCStorage_SetActiveBox(struct PCStorage *pc, int boxno) {
    if (boxno < NUM_BOXES) {
        pc->curBox = (u32)boxno;
        Save_SetDirtyBit();
        return;
    }
    GF_ASSERT(0);
}

u8 PCStorage_GetBoxWallpaper(struct PCStorage *pc, int boxno) {
    if (boxno < NUM_BOXES) {
        return pc->wallpapers[boxno];
    }
    GF_ASSERT(0);
    return 0;
}

void PCStorage_SetBoxWallpaper(struct PCStorage *pc, int boxno, u8 wallpaper) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES && wallpaper < NUM_WALLPAPERS) {
        pc->wallpapers[boxno] = wallpaper;
        Save_SetDirtyBit();
        return;
    }
    GF_ASSERT(0);
}

void PCStorage_GetBoxName(struct PCStorage *pc, int boxno, struct String *ret) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES) {
        CopyU16ArrayToString(ret, pc->names[boxno]);
        return;
    }
    GF_ASSERT(0);
}

void PCStorage_SetBoxName(struct PCStorage *pc, int boxno, struct String *src) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES) {
        CopyStringToU16Array(src, pc->names[boxno], BOX_NAME_LENGTH);
        Save_SetDirtyBit();
    }
}

int PCStorage_CountMonsAndEggsInBox(struct PCStorage *pc, int boxno) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES) {
        int i, count = 0;
        for (i = 0; i < (int)MONS_PER_BOX; i++) {
            if (GetBoxMonData(&pc->boxes[boxno][i], MON_DATA_SPECIES_EXISTS, NULL)) {
                count++;
            }
        }
        return count;
    }
    GF_ASSERT(0);
    return 0;
}

int PCStorage_CountMonsInBox(struct PCStorage *pc, int boxno) {
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    if (boxno < NUM_BOXES) {
        int i, count = 0;
        for (i = 0; i < (int)MONS_PER_BOX; i++) {
            if (GetBoxMonData(&pc->boxes[boxno][i], MON_DATA_SPECIES_EXISTS, NULL) && !GetBoxMonData(&pc->boxes[boxno][i], MON_DATA_IS_EGG, NULL)) {
                count++;
            }
        }
        return count;
    }
    GF_ASSERT(0);
    return 0;
}

int PCStorage_CountMonsInAllBoxes(struct PCStorage *pc) {
    int count, i;
    for (i = 0, count = 0; i < NUM_BOXES; i++) {
        count += PCStorage_CountMonsInBox(pc, i);
    }
    return count;
}

void PCStorage_SetBoxMonDataByIndexPair(struct PCStorage *pc, int boxno, int slotno, u32 attr, void *value) {
    if (boxno >= NUM_BOXES) {
        GF_ASSERT(boxno == -1);
    }
    GF_ASSERT(slotno < MONS_PER_BOX);
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    SetBoxMonData(&pc->boxes[boxno][slotno], (int)attr, value);
    Save_SetDirtyBit();
}

struct BoxPokemon *PCStorage_GetMonByIndexPair(struct PCStorage *pc, int boxno, int slotno) {
    if (boxno >= NUM_BOXES) {
        GF_ASSERT(boxno == -1);
    }
    GF_ASSERT(slotno < MONS_PER_BOX);
    if (boxno == -1) {
        boxno = (int)pc->curBox;
    }
    return &pc->boxes[boxno][slotno];
}

void PCStorage_UnlockBonusWallpaper(struct PCStorage *pc, int wallpaper) {
    GF_ASSERT(wallpaper < NUM_BONUS_WALLPAPERS);
    pc->unlockedWallpapers |= (1u << wallpaper);
    Save_SetDirtyBit();
}

BOOL PCStorage_IsBonusWallpaperUnlocked(struct PCStorage *pc, int wallpaper) {
    GF_ASSERT(wallpaper < NUM_BONUS_WALLPAPERS);
    return (pc->unlockedWallpapers & (1u << wallpaper)) != 0;
}

int PCStorage_CountUnlockedBonusWallpapers(struct PCStorage *pc) {
    int i, count;
    for (i = 0, count = 0; i < NUM_BONUS_WALLPAPERS; i++) {
        if (PCStorage_IsBonusWallpaperUnlocked(pc, i)) {
            count++;
        }
    }
    return count;
}
