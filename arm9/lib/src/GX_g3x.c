#include "global.h"
#include "main.h"
#include "gx.h"

extern u32 UNK_02106814;

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
    reg_G3_END_VTXS = 0x0;
    while (reg_G3X_GXSTAT & 0x8000000); //wait for geometry engine to not be busy
    reg_G3X_DISP3DCNT = 0x0;
    reg_G3X_GXSTAT = 0x0;
    reg_G2_BG0OFS = 0x0;
    reg_G3X_DISP3DCNT |= 0x2000;
    reg_G3X_DISP3DCNT |= 0x1000;
    reg_G3X_DISP3DCNT &= ~0x3002;
    reg_G3X_DISP3DCNT = reg_G3X_DISP3DCNT & ~0x3000 | 0x10;
    reg_G3X_DISP3DCNT = reg_G3X_DISP3DCNT & (u16)~0x3004;
    reg_G3X_GXSTAT |= 0x8000;
    reg_G3X_GXSTAT = reg_G3X_GXSTAT & ~0xC0000000 | 0x80000000;
    G3X_InitMtxStack();
    reg_G3X_CLEAR_COLOR = 0x0;
    reg_G3X_CLEAR_DEPTH = 0x7FFF;
    reg_G3X_CLRIMAGE_OFFSET = 0x0;
    reg_G3X_FOG_COLOR = 0x0;
    reg_G3X_FOG_OFFSET = 0x0;
    reg_G2_BG0CNT &= ~0x3;
    G3X_InitTable();
    reg_G3_POLYGON_ATTR = 0x1F0080;
    reg_G3_TEXIMAGE_PARAM = 0x0;
    reg_G3_TEXPLTT_BASE = 0x0;
}

ARM_FUNC void G3X_ResetMtxStack(){
    while (reg_G3X_GXSTAT & 0x8000000);
    reg_G3X_GXSTAT |= 0x8000;
    reg_G3X_DISP3DCNT |= 0x2000;
    reg_G3X_DISP3DCNT |= 0x1000;
    G3X_ResetMtxStack_2();
    reg_G3_POLYGON_ATTR = 0x1F0080;
    reg_G3_TEXIMAGE_PARAM = 0x0;
    reg_G3_TEXPLTT_BASE = 0x0;
}

ARM_FUNC void G3X_ClearFifo(){
    GXi_NopClearFifo128_((void *)&reg_G3X_GXFIFO);
    while (reg_G3X_GXSTAT & 0x8000000);
}

ARM_FUNC void G3X_InitMtxStack(){
    u32 PV_level, PJ_level;
    reg_G3X_GXSTAT |= 0x8000;
    while (G3X_GetMtxStackLevelPV(&PV_level));
    while (G3X_GetMtxStackLevelPJ(&PJ_level));
    reg_G3_MTX_MODE = 0x3;
    reg_G3_MTX_IDENTITY = 0x0;
    reg_G3_MTX_MODE = 0x0;
    if (PJ_level)
    {
        reg_G3_MTX_POP = PJ_level;
    }
    reg_G3_MTX_IDENTITY = 0x0;
    reg_G3_MTX_MODE = 0x2;
    reg_G3_MTX_POP = PV_level;
    reg_G3_MTX_IDENTITY = 0x0;
}

ARM_FUNC void G3X_ResetMtxStack_2(){
    u32 PV_level, PJ_level;
    reg_G3X_GXSTAT |= 0x8000;
    while (G3X_GetMtxStackLevelPV(&PV_level));
    while (G3X_GetMtxStackLevelPJ(&PJ_level));
    reg_G3_MTX_MODE = 0x3;
    reg_G3_MTX_IDENTITY = 0x0;
    reg_G3_MTX_MODE = 0x0;
    if (PJ_level)
    {
        reg_G3_MTX_POP = PJ_level;
    }

    reg_G3_MTX_MODE = 0x2;
    reg_G3_MTX_POP = PV_level;
    reg_G3_MTX_IDENTITY = 0x0;

}

ARM_FUNC void G3X_SetFog(u32 enable, u32 alphamode, u32 depth, s32 offset){
    if (enable)
    {
        reg_G3X_FOG_OFFSET = offset;
        reg_G3X_DISP3DCNT = (reg_G3X_DISP3DCNT &~0x3f40) | (((depth << 0x8)|  (alphamode << 0x6)|0x80 ));

    }
    else
    {
        reg_G3X_DISP3DCNT = reg_G3X_DISP3DCNT & (u16)~0x3080;
    }
}

ARM_FUNC u32 G3X_GetClipMtx(struct Mtx44 *dst){
    if (reg_G3X_GXSTAT & 0x8000000)
    {
        return -1;
    }
    else
    {
        MI_Copy64B((void *)&reg_G3X_CLIPMTX_RESULT_0, dst);
        return 0;
    }
}

ARM_FUNC u32 G3X_GetVectorMtx(struct Mtx33 *dst){
    if (reg_G3X_GXSTAT & 0x8000000)
    {
        return -1;
    }
    else
    {
        MI_Copy36B((void *)&reg_G3X_VECMTX_RESULT_0, dst);
        return 0;
    }
}

ARM_FUNC void G3X_SetEdgeColorTable(void *tbl_ptr){
    MIi_CpuCopy16(tbl_ptr, (void *)&reg_G3X_EDGE_COLOR_0, 0x10);
}

ARM_FUNC void G3X_SetFogTable(void *tbl_ptr){
    MI_Copy16B(tbl_ptr, (void *)&reg_G3X_FOG_TABLE_0);
}

ARM_FUNC void G3X_SetClearColor(u32 col, u32 alpha, u32 depth, u32 polygon_id, u32 enable_fog){
    u32 temp = col | (alpha << 0x10) | (polygon_id << 0x18);
    if (enable_fog)
        temp |= 0x8000;
    reg_G3X_CLEAR_COLOR = temp;
    reg_G3X_CLEAR_DEPTH = depth;
}

ARM_FUNC void G3X_InitTable(){
    if (UNK_02106814 != -1)
    {
        MI_DmaFill32Async(UNK_02106814, (void *)&reg_G3X_EDGE_COLOR_0, 0x0, 0x10, 0x0, 0x0);
        MI_DmaFill32(UNK_02106814, (void *)&reg_G3X_FOG_TABLE_0, 0x0, 0x60);
    }
    else
    {
        MIi_CpuClear32(0x0, (void *)&reg_G3X_EDGE_COLOR_0, 0x10);
        MIi_CpuClear32(0x0, (void *)&reg_G3X_FOG_TABLE_0, 0x60);
    }
    for (int i = 0; i < 0x20; i++)
    {
        reg_G3_SHININESS = 0x0;
    }
}

ARM_FUNC u32 G3X_GetMtxStackLevelPV(u32 *level){
    if (reg_G3X_GXSTAT & 0x4000)
    {
        return -1;
    }
    else
    {
        *level = (reg_G3X_GXSTAT & 0x1F00) >> 0x8;
        return 0;
    }
}

ARM_FUNC u32 G3X_GetMtxStackLevelPJ(u32 *level){
    if (reg_G3X_GXSTAT & 0x4000)
    {
        return -1;
    }
    else
    {
        *level = (reg_G3X_GXSTAT & 0x2000) >> 0xD;
        return 0;
    }
}

ARM_FUNC u32 G3X_GetBoxTestResult(u32 *result){
    if (reg_G3X_GXSTAT & 0x1)
    {
        return -1;
    }
    else
    {
        *result = (reg_G3X_GXSTAT & 0x2);
        return 0;
    }
}

ARM_FUNC void G3X_SetHOffset(u32 offset){
    reg_G2_BG0OFS = offset;
}
