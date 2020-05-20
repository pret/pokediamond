#include "global.h"
#include "main.h"
#include "GX.h"

extern u32 GXi_DmaId;

extern s32 sSubOBJExtPltt;
extern s32 sBGExtPltt;
extern u32 sBGExtPlttLCDCBlk;
extern u32 sBGExtPlttLCDCOffset;
extern s32 sOBJExtPltt;
extern u32 sOBJExtPlttLCDCBlk;
extern s32 sSubBGExtPltt;


static inline void *_GX_OBJ_PTR(){
    return (void *)0x6400000;
}
static inline void *_GXS_OBJ_PTR(){
    return (void *)0x6600000;
}

ARM_FUNC void GX_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000000 + offset), size);
}

ARM_FUNC void GXS_LoadBGPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000400 + offset), size);
}

ARM_FUNC void GX_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000200 + offset), size);
}

ARM_FUNC void GXS_LoadOBJPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(0x5000600 + offset), size);
}

ARM_FUNC void GX_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(0x7000000 + offset), size);
}

ARM_FUNC void GXS_LoadOAM(void *src, u32 offset, u32 size){
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(0x7000400 + offset), size);
}

ARM_FUNC void GX_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GX_OBJ_PTR();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadOBJ(void *src, u32 offset, u32 size){
    u32 base = (u32)_GXS_OBJ_PTR();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG0Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG1Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG2Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG3Scr(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG0CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG0Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG0CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG1CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG1Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG1CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG2CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG2Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG2CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2_GetBG3CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GXS_LoadBG3Char(void *src, u32 offset, u32 size){
    u32 base = (u32)G2S_GetBG3CharPtr();
    GXi_DmaCopy32(GXi_DmaId, src, (void *)(base + offset), size);
}

ARM_FUNC void GX_BeginLoadBGExtPltt(){
    sBGExtPltt = GX_ResetBankForBGExtPltt();
    switch (sBGExtPltt)
    {
    case 0: //needed to match
        break;
    case 0x10:
        sBGExtPlttLCDCBlk = 0x06880000;
        sBGExtPlttLCDCOffset = 0x0;
        break;
    case 0x40:
        sBGExtPlttLCDCBlk = 0x06894000;
        sBGExtPlttLCDCOffset = 0x4000;
        break;
    case 0x20:
    case 0x60:
        sBGExtPlttLCDCBlk = 0x06890000;
        sBGExtPlttLCDCOffset = 0x0;
        break;
    }
}

ARM_FUNC void GX_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sBGExtPlttLCDCBlk + offset - sBGExtPlttLCDCOffset), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadBGExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForBGExtPltt(sBGExtPltt);
    sBGExtPltt = 0x0;
    sBGExtPlttLCDCBlk = 0x0;
    sBGExtPlttLCDCOffset = 0x0;
}

ARM_FUNC void GX_BeginLoadOBJExtPltt(){
    sOBJExtPltt = GX_ResetBankForOBJExtPltt();
    switch (sOBJExtPltt)
    {
    case 0: //needed to match
        break;
    case 0x40:
        sOBJExtPlttLCDCBlk = 0x06894000;
        break;
    case 0x20:
        sOBJExtPlttLCDCBlk = 0x06890000;
        break;
    }
}

ARM_FUNC void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sOBJExtPlttLCDCBlk + offset), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadOBJExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForOBJExtPltt(sOBJExtPltt);
    sOBJExtPltt = 0x0;
    sOBJExtPlttLCDCBlk = 0x0;
}

ARM_FUNC void GXS_BeginLoadBGExtPltt(){
    sSubBGExtPltt = FUN_020C6034();
}

ARM_FUNC void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(0x06898000 + offset), size, NULL, NULL);
}

ARM_FUNC void GXS_EndLoadBGExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForSubBGExtPltt(sSubBGExtPltt);
    sSubBGExtPltt = 0x0;
}

ARM_FUNC void GXS_BeginLoadOBJExtPltt(){
    sSubOBJExtPltt = GX_ResetBankForSubOBJ();
}

ARM_FUNC void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(0x068A0000 + offset), size, NULL, NULL);
}

ARM_FUNC void GXS_EndLoadOBJExtPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForSubOBJExtPltt(sSubOBJExtPltt);
    sSubOBJExtPltt = 0x0;
}
