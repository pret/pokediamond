#include "global.h"
#include "main.h"
#include "fx.h"

void VEC_Add(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst){
    dst->x = x->x + y->x;
    dst->y = x->y + y->y;
    dst->z = x->z + y->z;
}

void VEC_Subtract(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst){
    dst->x = x->x - y->x;
    dst->y = x->y - y->y;
    dst->z = x->z - y->z;
}

void VEC_Fx16Add(struct Vecx16 *x, struct Vecx16 *y, struct Vecx16 *dst){
    dst->x = x->x + y->x;
    dst->y = x->y + y->y;
    dst->z = x->z + y->z;
}

s32 VEC_DotProduct(struct Vecx32 *x, struct Vecx32 *y){
    return ((s64)x->x * y->x + (s64)x->y * y->y + (s64)x->z * y->z + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT;
}

s32 VEC_Fx16DotProduct(struct Vecx16 *x, struct Vecx16 *y){
    s32 temp1, temp2;
    temp1 = (x->x * y->x) + (x->y * y->y);
    temp2 = (x->z * y->z) + (1 << (FX64_INT_SHIFT - 1));
    return (s32)(((s64)temp1 + temp2) >> FX64_INT_SHIFT);
}

void VEC_CrossProduct(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *);
