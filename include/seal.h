#ifndef POKEDIAMOND_SEAL_H
#define POKEDIAMOND_SEAL_H

typedef u8 Coords8[3];
typedef Coords8 CapsuleArray[8];

struct SealCase
{
    CapsuleArray coords[12];
    u8 padding_120[0x50];
};

u32 FUN_02029C58(void);
void FUN_02029C60(struct SealCase * sealCase);
void FUN_02029C74(const CapsuleArray * a0, CapsuleArray * a1);
struct SealCase * FUN_02029C80(struct SaveBlock2 * sav2);
CapsuleArray * FUN_02029C8C(struct SealCase * sealCase, s32 idx);
void FUN_02029CA4(struct SealCase * sealCase, const CapsuleArray * src, s32 idx);
Coords8 * FUN_02029CC8(CapsuleArray * a0, s32 a1);
u8 FUN_02029CE0(Coords8 * a0);
u8 FUN_02029CE4(Coords8 * a0);
u8 FUN_02029CE8(Coords8 * a0);

#endif //POKEDIAMOND_SEAL_H
