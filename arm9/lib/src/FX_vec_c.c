#include "global.h"
#include "main.h"
#include "fx.h"

void VEC_Add(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst){
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}

void VEC_Subtract(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst){
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
    dst->z = a->z - b->z;
}

void VEC_Fx16Add(struct Vecx16 *a, struct Vecx16 *b, struct Vecx16 *dst){
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}

s32 VEC_DotProduct(struct Vecx32 *a, struct Vecx32 *b){
    return ((s64)a->x * b->x + (s64)a->y * b->y + (s64)a->z * b->z + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT;
}

s32 VEC_Fx16DotProduct(struct Vecx16 *a, struct Vecx16 *b){
    s32 temp1, temp2;
    temp1 = (a->x * b->x) + (a->y * b->y);
    temp2 = (a->z * b->z) + (1 << (FX64_INT_SHIFT - 1));
    return (s32)(((s64)temp1 + temp2) >> FX64_INT_SHIFT);
}

void VEC_CrossProduct(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst);
