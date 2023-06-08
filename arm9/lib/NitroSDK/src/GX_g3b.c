#include "nitro/types.h"
#include "gx.h"
#include "code32.h"

void G3BS_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx){
    *(u32 *)displaylist->curr_cmd = 0x16;
    MI_Copy64B(mtx, displaylist->curr_param);
}

void G3B_PushMtx(struct GXDLInfo *displaylist){
    *(u32 *)displaylist->curr_cmd = 0x11;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_PopMtx(struct GXDLInfo *displaylist, void *mtx){
    *(u32 *)displaylist->curr_cmd = 0x12;
    *displaylist->curr_param = (u32)mtx;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx){
    G3BS_LoadMtx44(displaylist, mtx);
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + sizeof(struct Mtx44);
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

//color format is RGB555, stored in the lower bits
void G3B_Color(struct GXDLInfo * displaylist, u32 vtx_col){
    *(u32 *)displaylist->curr_cmd = 0x20;
    *displaylist->curr_param = vtx_col;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

/*
Only feed normalized Vectors
only the fractional part and the sign, which is in the first nonfraction bit
since the vector is assumed to be normalized, are used
*/
void G3B_Normal(struct GXDLInfo * displaylist, fx16 x, fx16 y, fx16 z){
    *(u32 *)displaylist->curr_cmd = 0x21;
    *displaylist->curr_param = (u32)(((x >> 3) & 0x3FF) | (((y >> 3) & 0x3FF) << 0xA) | (((z >> 3) & 0x3FF) << 0x14));
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_Vtx(struct GXDLInfo * displaylist, fx32 x, fx32 y, fx32 z){
    *(u32 *)displaylist->curr_cmd = 0x23;
    displaylist->curr_param[0] = (u32)(u16)x | (u32)(u16)y << 0x10;
    displaylist->curr_param[1] = (u32)(u16)z;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x8;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

//TODO: name arguments
void G3B_PolygonAttr(struct GXDLInfo *displaylist, u32 r1, u32 r2, u32 r3, u32 r4, u32 r5, u32 r6){
    *(u32 *)displaylist->curr_cmd = 0x29;
    *displaylist->curr_param = r1 | r2 << 0x4 | r3 << 0x6 | r6 | r4 << 0x18 | r5 << 0x10;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_MaterialColorDiffAmb(struct GXDLInfo *displaylist, u32 diffuse_col, u32 ambient_col, u32 replace){
    *(u32 *)displaylist->curr_cmd = 0x30;
    u32 replace_vtx_color_with_diffuse;
    if (replace)
        replace_vtx_color_with_diffuse = TRUE;
    else
        replace_vtx_color_with_diffuse = FALSE;
    *displaylist->curr_param = diffuse_col | ambient_col << 0x10 | replace_vtx_color_with_diffuse << 0xF;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_MaterialColorSpecEmi(struct GXDLInfo *displaylist, u32 specular_col, u32 emission_col, u32 shiny_table){
    *(u32 *)displaylist->curr_cmd = 0x31;
    u32 enable_shininess_table;
    if (shiny_table)
        enable_shininess_table = TRUE;
    else
        enable_shininess_table = FALSE;
    *displaylist->curr_param = specular_col | emission_col << 0x10 | enable_shininess_table << 0xF;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

/*
Only feed normalized Vectors
only the fractional part and the sign, which is in the first nonfraction bit
since the vector is assumed to be normalized, are used
*/
void G3B_LightVector(struct GXDLInfo * displaylist, u32 light_num, fx16 x, fx16 y, fx16 z){
    *(u32 *)displaylist->curr_cmd = 0x32;
    *displaylist->curr_param = ((x >> 3) & 0x3FF) | (((y >> 3) & 0x3FF) << 0xA) | (((z >> 3) & 0x3FF) << 0x14) | light_num << 0x1E;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_LightColor(struct GXDLInfo * displaylist, u32 light_num, u32 col){
    *(u32 *)displaylist->curr_cmd = 0x33;
    *displaylist->curr_param = col | light_num << 0x1E;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_Begin(struct GXDLInfo * displaylist, u32 type){
    *(u32 *)displaylist->curr_cmd = 0x40;
    *displaylist->curr_param = type;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param + 0x4;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}

void G3B_End(struct GXDLInfo * displaylist){
    *(u32 *)displaylist->curr_cmd = 0x41;
    displaylist->curr_cmd = (u8 *)displaylist->curr_param;
    displaylist->curr_param = (u32 *)displaylist->curr_cmd + 1;
}
