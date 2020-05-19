#ifndef GUARD_GX_LOAD2D_H
#define GUARD_GX_LOAD2D_H

void GX_LoadBGPltt(void *src, u32 offset, u32 size);
void GXS_LoadBGPltt(void *src, u32 offset, u32 size);
void GX_LoadOBJPltt(void *src, u32 offset, u32 size);
void GXS_LoadOBJPltt(void *src, u32 offset, u32 size);
void GX_LoadOAM(void *src, u32 offset, u32 size);
void GXS_LoadOAM(void *src, u32 offset, u32 size);
void GX_LoadOBJ(void *src, u32 offset, u32 size);
void GXS_LoadOBJ(void *src, u32 offset, u32 size);
void GX_LoadBG0Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG0Scr(void *src, u32 offset, u32 size);
void GX_LoadBG1Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG1Scr(void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG2Scr(void *src, u32 offset, u32 size);
void GX_LoadBG3Scr(void *src, u32 offset, u32 size);
void GXS_LoadBG3Scr(void *src, u32 offset, u32 size);
void GX_LoadBG0Char(void *src, u32 offset, u32 size);
void GXS_LoadBG0Char(void *src, u32 offset, u32 size);
void GX_LoadBG1Char(void *src, u32 offset, u32 size);
void GXS_LoadBG1Char(void *src, u32 offset, u32 size);
void GX_LoadBG2Char(void *src, u32 offset, u32 size);
void GXS_LoadBG2Char(void *src, u32 offset, u32 size);
void GX_LoadBG3Char(void *src, u32 offset, u32 size);
void GXS_LoadBG3Char(void *src, u32 offset, u32 size);
void GX_BeginLoadBGExtPltt();
void GX_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadBGExtPltt();
void GX_BeginLoadOBJExtPltt();
void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadOBJExtPltt();
void GXS_BeginLoadBGExtPltt();
void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadBGExtPltt();
void GXS_BeginLoadOBJExtPltt();
void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadOBJExtPltt();

#endif //GUARD_GX_LOAD2D_H
