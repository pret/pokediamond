#ifndef POKEDIAMOND_UNK_0202C0E0_H
#define POKEDIAMOND_UNK_0202C0E0_H

#include "save.h"

struct UnkSaveStruct0202C0E4 {
    u16 data[5][4];
};

u32 sub_0202C0E0();
void sub_0202C0E4(struct UnkSaveStruct0202C0E4 *unkStruct);
void sub_0202C108(struct SaveData *save, u32 a1, u32 a2);
u16 sub_0202C12C(struct SaveData *save, u32 a1, u32 a2);

#endif // POKEDIAMOND_UNK_0202C0E0_H
