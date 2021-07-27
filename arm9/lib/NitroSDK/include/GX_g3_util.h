#ifndef GUARD_GX_G3_UTIL_H
#define GUARD_GX_G3_UTIL_H

#include "nitro/FX_types.h"

void G3i_PerspectiveW_(fx32 fovsin, fx32 fovcos, fx32 ratio, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx);
void G3i_OrthoW_(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scale, u32 load, struct Mtx44 *mtx);
void G3i_LookAt_(const struct Vecx32 *a, const struct Vecx32 *b, const struct Vecx32 *c, BOOL load, struct Mtx43 *mtx);
void G3_RotX(fx32 sinphi, fx32 cosphi);
void G3_RotY(fx32 sinphi, fx32 cosphi);
void G3_RotZ(fx32 sinphi, fx32 cosphi);

#endif //GUARD_GX_G3_UTIL_H
