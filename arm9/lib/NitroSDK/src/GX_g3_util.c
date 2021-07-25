#include "global.h"
#include "gx.h"


ARM_FUNC void G3i_PerspectiveW_(fx32 fovsin, fx32 fovcos, fx32 ratio, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx){
    fx32 fovcot, temp1, temp2;
    fx64c temp0;
    vu32 *reg_ptr;

    fovcot = FX_Div(fovcos, fovsin);
    if (scale != 0x1000) //!= 1.0
        fovcot = (fovcot * scale) / 0x1000;
    reg_CP_DIV_NUMER = (u64)((s64)fovcot << 0x20);
    reg_CP_DIV_DENOM = (u32)ratio;
    if (load)
    {
        reg_G3_MTX_MODE =  0x0;
        reg_ptr = (vu32 *)&reg_G3_MTX_LOAD_4x4;
    }
    if (mtx)
    {
        mtx->_[1] = 0x0;
        mtx->_[2] = 0x0;
        mtx->_[3] = 0x0;
        mtx->_[4] = 0x0;
        mtx->_[6] = 0x0;
        mtx->_[7] = 0x0;
        mtx->_[8] = 0x0;
        mtx->_[9] = 0x0;
        mtx->_[11] = -scale;
        mtx->_[12] = 0x0;
        mtx->_[13] = 0x0;
        mtx->_[15] = 0x0;
    }
    temp1 = FX_GetDivResult();
    reg_CP_DIV_NUMER = (s64)0x1000 << 0x20;
    reg_CP_DIV_DENOM = (u32)(near - far);
    if (load)
    {
        *reg_ptr = (vu32)temp1;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = (vu32)fovcot;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
    }
    if (mtx)
    {
        mtx->_[0] = temp1;
        mtx->_[5] = fovcot;
    }
    temp0 = FX_GetDivResultFx64c();
    if (scale != 0x1000)
        temp0 = (temp0 * scale) / 0x1000;
    temp1 = (fx32)(((far + near) * temp0 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    temp2 = (fx32)((((fx32)(((fx64)(near << 1) * far + (1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT)) * temp0 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    if (load)
    {
        *reg_ptr = (vu32)temp1;
        *reg_ptr = (vu32)(-scale);
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = (vu32)temp2;
        *reg_ptr = 0x0;
    }
    if (mtx)
    {
        mtx->_[10] = temp1;
        mtx->_[14] = temp2;
    }
}

ARM_FUNC void G3i_OrthoW_(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx){
    fx64c temp1, temp2, temp3;
    fx32 temp0, temp4, temp5;
    vu32 *reg_ptr;

    FX_InvAsync(right - left);
    if (load)
    {
        reg_G3_MTX_MODE = 0x0;
        reg_ptr = (vu32 *)&reg_G3_MTX_LOAD_4x4;
    }
    if (mtx)
    {
        mtx->_[1] = 0x0;
        mtx->_[2] = 0x0;
        mtx->_[3] = 0x0;
        mtx->_[4] = 0x0;
        mtx->_[6] = 0x0;
        mtx->_[7] = 0x0;
        mtx->_[8] = 0x0;
        mtx->_[9] = 0x0;
        mtx->_[11] = 0x0;
        mtx->_[15] = scale;
    }
    temp1 = FX_GetDivResultFx64c();
    reg_CP_DIV_NUMER = (s64)0x1000 << 0x20;
    reg_CP_DIV_DENOM = (u32)(top - bottom);
    if (scale != 0x1000)
        temp1 = (temp1 * scale) / 0x1000;
    temp0 = (fx32)((0x2000 * temp1 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    if (load)
    {
        *reg_ptr = (vu32)temp0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
    }
    if (mtx)
    {
        mtx->_[0] = temp0;
    }
    temp2 = FX_GetDivResultFx64c();
    reg_CP_DIV_NUMER = (s64)0x1000 << 0x20;
    reg_CP_DIV_DENOM = (u32)(near - far);
    if (scale != 0x1000)
        temp2 = (temp2 * scale) / 0x1000;
    temp0 = (fx32)((0x2000 * temp2 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    if (load)
    {
        *reg_ptr = (vu32)temp0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
        *reg_ptr = 0x0;
    }
    if (mtx)
    {
        mtx->_[5] = temp0;
    }
    temp3 = FX_GetDivResultFx64c();
    if (scale != 0x1000)
        temp3 = (temp3 * scale) / 0x1000;
    temp0 = (fx32)((0x2000 * temp3 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    if (load)
    {
        *reg_ptr = (vu32)temp0;
        *reg_ptr = 0x0;
    }
    if (mtx)
    {
        mtx->_[10] = temp0;
    }
    temp0 = (fx32)(((-(right + left)) * temp1 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    temp4 = (fx32)(((-(top + bottom)) * temp2 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    temp5 = (fx32)(((far + near) * temp3 + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT);
    if (load)
    {
        *reg_ptr = (vu32)temp0;
        *reg_ptr = (vu32)temp4;
        *reg_ptr = (vu32)temp5;
        *reg_ptr = (vu32)scale;
    }
    if (mtx)
    {
        mtx->_[12] = temp0;
        mtx->_[13] = temp4;
        mtx->_[14] = temp5;
    }
}

ARM_FUNC void G3i_LookAt_(const struct Vecx32 *a, const struct Vecx32 *b, const struct Vecx32 *c, BOOL load, struct Mtx43 *mtx){
    struct Vecx32 temp, temp1, temp2;
    fx32 c1, c2, c3;
    vu32 *reg_ptr;
    temp.x = a->x - c->x;
    temp.y = a->y - c->y;
    temp.z = a->z - c->z;
    VEC_Normalize(&temp, &temp);
    VEC_CrossProduct(b, &temp, &temp1);
    VEC_Normalize(&temp1, &temp1);
    VEC_CrossProduct(&temp, &temp1, &temp2);
    if (load)
    {
        reg_G3_MTX_MODE = 0x2;
        reg_ptr = (vu32 *)&reg_G3_MTX_LOAD_4x3;
        *reg_ptr = (vu32)temp1.x;
        *reg_ptr = (vu32)temp2.x;
        *reg_ptr = (vu32)temp.x;
        *reg_ptr = (vu32)temp1.y;
        *reg_ptr = (vu32)temp2.y;
        *reg_ptr = (vu32)temp.y;
        *reg_ptr = (vu32)temp1.z;
        *reg_ptr = (vu32)temp2.z;
        *reg_ptr = (vu32)temp.z;
    }
    c1 = -VEC_DotProduct(a, &temp1);
    c2 = -VEC_DotProduct(a, &temp2);
    c3 = -VEC_DotProduct(a, &temp);
    if (load)
    {
        *reg_ptr = (vu32)c1;
        *reg_ptr = (vu32)c2;
        *reg_ptr = (vu32)c3;
    }
    if (mtx)
    {
        mtx->_[0] = temp1.x;
        mtx->_[1] = temp2.x;
        mtx->_[2] = temp.x;
        mtx->_[3] = temp1.y;
        mtx->_[4] = temp2.y;
        mtx->_[5] = temp.y;
        mtx->_[6] = temp1.z;
        mtx->_[7] = temp2.z;
        mtx->_[8] = temp.z;
        mtx->_[9] = c1;
        mtx->_[10] = c2;
        mtx->_[11] = c3;
    }
}

ARM_FUNC void G3_RotX(fx32 sinphi, fx32 cosphi){
    vu32 *reg_ptr;
    reg_ptr = (vu32 *)&reg_G3_MTX_MULT_3x3;
    *reg_ptr = 0x1000;
    *reg_ptr = 0x0;
    *reg_ptr = 0x0;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)cosphi;
    *reg_ptr = (vu32)sinphi;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)(-sinphi);
    *reg_ptr = (vu32)cosphi;
}

ARM_FUNC void G3_RotY(fx32 sinphi, fx32 cosphi){
    vu32 *reg_ptr;
    reg_ptr = (vu32 *)&reg_G3_MTX_MULT_3x3;
    *reg_ptr = (vu32)cosphi;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)(-sinphi);
    *reg_ptr = 0x0;
    *reg_ptr = 0x1000;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)sinphi;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)cosphi;
}

ARM_FUNC void G3_RotZ(fx32 sinphi, fx32 cosphi){
    vu32 *reg_ptr;
    reg_ptr = (vu32 *)&reg_G3_MTX_MULT_3x3;
    *reg_ptr = (vu32)cosphi;
    *reg_ptr = (vu32)sinphi;
    *reg_ptr = 0x0;
    *reg_ptr = (vu32)(-sinphi);
    *reg_ptr = (vu32)cosphi;
    *reg_ptr = 0x0;
    *reg_ptr = 0x0;
    *reg_ptr = 0x0;
    *reg_ptr = 0x1000;
}
