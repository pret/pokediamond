#ifndef GUARD_GX_LOAD3D_H
#define GUARD_GX_LOAD3D_H

void GX_BeginLoadTex();
void GX_LoadTex(void *src, u32 offset, u32 size);
void GX_EndLoadTex();
void GX_BeginLoadTexPltt();
void GX_LoadTexPltt(void *src, u32 offset, u32 size);
void GX_EndLoadTexPltt();
void GX_BeginLoadClearImage();
void GX_LoadClearImageColor(void *src, u32 size);
void GX_LoadClearImageDepth(void *src, u32 size);
void GX_EndLoadClearImage();

#endif //GUARD_GX_LOAD3D_H
