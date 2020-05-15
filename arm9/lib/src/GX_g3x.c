#include "global.h"
#include "main.h"
#include "gx.h"

extern u32 gUnk02106814;

ARM_FUNC asm void GXi_NopClearFifo128_(void *reg){
    mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	mov r12, #0x0
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	bx lr
}

ARM_FUNC void G3X_Init(){
    G3X_ClearFifo();
    SETREG32(HW_REG_END_VTXS, 0x0);
    while (READREG32(HW_REG_GXSTAT) & 0x8000000); //wait for geometry engine to not be busy
    SETREG16(HW_REG_DISP3DCNT, 0x0);
    SETREG32(HW_REG_GXSTAT, 0x0);
    SETREG32(HW_REG_BG0HOFS, 0x0);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x2000);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x1000);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & ~0x3002);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & ~0x3000 | 0x10);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & (u16)~0x3004);
    SETREG32(HW_REG_GXSTAT, READREG32(HW_REG_GXSTAT) | 0x8000);
    SETREG32(HW_REG_GXSTAT, READREG32(HW_REG_GXSTAT) & ~0xC0000000 | 0x80000000);
    G3X_InitMtxStack();
    SETREG32(HW_REG_CLEAR_COLOR, 0x0);
    SETREG16(HW_REG_CLEAR_DEPTH, 0x7FFF);
    SETREG16(HW_REG_CLRIMAGE_OFFSET, 0x0);
    SETREG32(HW_REG_FOG_COLOR, 0x0);
    SETREG16(HW_REG_FOG_OFFSET, 0x0);
    SETREG16(HW_REG_BG0CNT, READREG16(HW_REG_BG0CNT) & ~0x3);
    G3X_InitTable();
    SETREG32(HW_REG_POLYGON_ATTR, 0x1F0080);
    SETREG32(HW_REG_TEXIMAGE_PARAM, 0x0);
    SETREG32(HW_REG_PLTT_BASE, 0x0);
}

ARM_FUNC void G3X_ResetMtxStack(){
    while (READREG32(HW_REG_GXSTAT) & 0x8000000);
    SETREG32(HW_REG_GXSTAT, READREG32(HW_REG_GXSTAT) | 0x8000);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x2000);
    SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) | 0x1000);
    G3X_ResetMtxStack_2();
    SETREG32(HW_REG_POLYGON_ATTR, 0x1F0080);
    SETREG32(HW_REG_TEXIMAGE_PARAM, 0x0);
    SETREG32(HW_REG_PLTT_BASE, 0x0);
}

ARM_FUNC void G3X_ClearFifo(){
    GXi_NopClearFifo128_((void *)HW_REG_GXFIFO);
    while (READREG32(HW_REG_GXSTAT) & 0x8000000);
}

ARM_FUNC void G3X_InitMtxStack(){
    u32 PV_level, PJ_level;
    SETREG32(HW_REG_GXSTAT, READREG32(HW_REG_GXSTAT) | 0x8000);
    while (G3X_GetMtxStackLevelPV(&PV_level));
    while (G3X_GetMtxStackLevelPJ(&PJ_level));
    SETREG32(HW_REG_MTX_MODE, 0x3);
    SETREG32(HW_REG_MTX_IDENTITY, 0x0);
    SETREG32(HW_REG_MTX_MODE, 0x0);
    if (PJ_level)
    {
        SETREG32(HW_REG_MTX_POP, PJ_level);
    }
    SETREG32(HW_REG_MTX_IDENTITY, 0x0);
    SETREG32(HW_REG_MTX_MODE, 0x2);
    SETREG32(HW_REG_MTX_POP, PV_level);
    SETREG32(HW_REG_MTX_IDENTITY, 0x0);
}

ARM_FUNC void G3X_ResetMtxStack_2(){
    u32 PV_level, PJ_level;
    SETREG32(HW_REG_GXSTAT, READREG32(HW_REG_GXSTAT) | 0x8000);
    while (G3X_GetMtxStackLevelPV(&PV_level));
    while (G3X_GetMtxStackLevelPJ(&PJ_level));
    SETREG32(HW_REG_MTX_MODE, 0x3);
    SETREG32(HW_REG_MTX_IDENTITY, 0x0);
    SETREG32(HW_REG_MTX_MODE, 0x0);
    if (PJ_level)
    {
        SETREG32(HW_REG_MTX_POP, PJ_level);
    }

    SETREG32(HW_REG_MTX_MODE, 0x2);
    SETREG32(HW_REG_MTX_POP, PV_level);
    SETREG32(HW_REG_MTX_IDENTITY, 0x0);

}

ARM_FUNC void G3X_SetFog(u32 enable, u32 alphamode, u32 depth, s32 offset){
    if (enable)
    {
        SETREG16(HW_REG_FOG_OFFSET, offset);
        SETREG16(HW_REG_DISP3DCNT,  (READREG16(HW_REG_DISP3DCNT) &~0x3f40) | (((depth << 0x8)|  (alphamode << 0x6)|0x80 )));

    }
    else
    {
        SETREG16(HW_REG_DISP3DCNT, READREG16(HW_REG_DISP3DCNT) & (u16)~0x3080);
    }
}

ARM_FUNC u32 G3X_GetClipMtx(struct Mtx44 *dst){
    if (READREG32(HW_REG_GXSTAT) & 0x8000000)
    {
        return -1;
    }
    else
    {
        MI_Copy64B((void *)HW_REG_CLIPMTX_RESULT, dst);
        return 0;
    }
}

ARM_FUNC u32 G3X_GetVectorMtx(struct Mtx33 *dst){
    if (READREG32(HW_REG_GXSTAT) & 0x8000000)
    {
        return -1;
    }
    else
    {
        MI_Copy36B((void *)HW_REG_VECMTX_RESULT, dst);
        return 0;
    }
}

ARM_FUNC void G3X_SetEdgeColorTable(void *tbl_ptr){
    MIi_CpuCopy16(tbl_ptr, (void *)HW_REG_EDGE_COLOR, 0x10);
}

ARM_FUNC void G3X_SetFogTable(void *tbl_ptr){
    MI_Copy16B(tbl_ptr, (void *)HW_REG_FOG_TABLE);
}

ARM_FUNC void G3X_SetClearColor(u32 col, u32 alpha, u32 depth, u32 polygon_id, u32 enable_fog){
    u32 temp = col | (alpha << 0x10) | (polygon_id << 0x18);
    if (enable_fog)
        temp |= 0x8000;
    SETREG32(HW_REG_CLEAR_COLOR, temp);
    SETREG16(HW_REG_CLEAR_DEPTH, depth);
}

ARM_FUNC void G3X_InitTable(){
    if (gUnk02106814 != -1)
    {
        MI_DmaFill32Async(gUnk02106814, (void *)HW_REG_EDGE_COLOR, 0x0, 0x10, 0x0, 0x0);
        MI_DmaFill32(gUnk02106814, (void *)HW_REG_FOG_TABLE, 0x0, 0x60);
    }
    else
    {
        MIi_CpuClear32(0x0, (void *)HW_REG_EDGE_COLOR, 0x10);
        MIi_CpuClear32(0x0, (void *)HW_REG_FOG_TABLE, 0x60);
    }
    for (int i = 0; i < 0x20; i++)
    {
        SETREG32(HW_REG_SHININESS, 0x0);
    }
}

ARM_FUNC u32 G3X_GetMtxStackLevelPV(u32 *level){
    if (READREG32(HW_REG_GXSTAT) & 0x4000)
    {
        return -1;
    }
    else
    {
        *level = (READREG32(HW_REG_GXSTAT) & 0x1F00) >> 0x8;
        return 0;
    }
}

ARM_FUNC u32 G3X_GetMtxStackLevelPJ(u32 *level){
    if (READREG32(HW_REG_GXSTAT) & 0x4000)
    {
        return -1;
    }
    else
    {
        *level = (READREG32(HW_REG_GXSTAT) & 0x2000) >> 0xD;
        return 0;
    }
}

ARM_FUNC u32 G3X_GetBoxTestResult(u32 *result){
    if (READREG32(HW_REG_GXSTAT) & 0x1)
    {
        return -1;
    }
    else
    {
        *result = (READREG32(HW_REG_GXSTAT) & 0x2);
        return 0;
    }
}

ARM_FUNC void G3X_SetHOffset(u32 offset){
    SETREG32(HW_REG_BG0HOFS, offset);
}
