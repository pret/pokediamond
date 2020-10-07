#ifndef POKEDIAMOND_SEAL_H
#define POKEDIAMOND_SEAL_H

typedef u8 Coords8[3];
typedef Coords8 CapsuleArray[8];

struct SealCase
{
    CapsuleArray coords[12];
    u8 sealCounts[80];
};

u32 Sav2_SealCase_sizeof(void);
void Sav2_SealCase_init(struct SealCase * sealCase);
void CapsuleArray_copy(const CapsuleArray * a0, CapsuleArray * a1);
struct SealCase * Sav2_SealCase_get(struct SaveBlock2 * sav2);
CapsuleArray * SealCase_GetCapsuleI(struct SealCase * sealCase, s32 idx);
void SealCase_SetCapsuleI(struct SealCase * sealCase, const CapsuleArray * src, s32 idx);
Coords8 * Capsule_GetSealI(CapsuleArray * a0, s32 a1);
s32 Seal_GetId(Coords8 * a0);
s32 Seal_GetXCoord(Coords8 * a0);
s32 Seal_GetYCoord(Coords8 * a0);

#endif //POKEDIAMOND_SEAL_H
