#include "global.h"
#include "main.h"
#include "gx.h"


void MI_Copy64B(void *src, void *dst);

void G3BS_LoadMtx44(struct DL *displaylist, struct Mtx44 *mtx){
    *(u32 *)displaylist->var00 = 0x16;
    MI_Copy64B(mtx, displaylist->var04);
}

void G3B_PushMtx(struct DL *displaylist){
    *(u32 *)displaylist->var00 = 0x11;
    displaylist->var00 = (u8 *)displaylist->var04;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_PopMtx(struct DL *displaylist, void *mtx){
    *(u32 *)displaylist->var00 = 0x12;
    *displaylist->var04 = (u32)mtx;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_LoadMtx44(struct DL *displaylist, struct Mtx44 *mtx){
    G3BS_LoadMtx44(displaylist, mtx);
    displaylist->var00 = (u8 *)displaylist->var04 + sizeof(struct Mtx44);
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

//color format is RGB555, stored in the lower bits
void G3B_Color(struct DL * displaylist, u32 vtx_col){
    *(u32 *)displaylist->var00 = 0x20;
    *displaylist->var04 = vtx_col;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

/*
Only feed normalized Vectors
only the fractional part and the sign, which is in the first nonfraction bit
since the vector is assumed to be normalized, are used
*/
void G3B_Normal(struct DL * displaylist, fx16 x, fx16 y, fx16 z){
    *(u32 *)displaylist->var00 = 0x21;
    *displaylist->var04 = ((x >> 3) & 0x3FF) | (((y >> 3) & 0x3FF) << 0xA) | (((z >> 3) & 0x3FF) << 0x14) ;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_Vtx(struct DL * displaylist, fx32 x, fx32 y, fx32 z){
    *(u32 *)displaylist->var00 = 0x23;
    displaylist->var04[0] = (u32)(u16)x | (u32)(u16)y << 0x10;
    displaylist->var04[1] = (u32)(u16)z;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x8;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

//TODO: name arguments
void G3B_PolygonAttr(struct DL *displaylist, u32 r1, u32 r2, u32 r3, u32 r4, u32 r5, u32 r6){
    *(u32 *)displaylist->var00 = 0x29;
    *displaylist->var04 = r1 | r2 << 0x4 | r3 << 0x6 | r6 | r4 << 0x18 | r5 << 0x10;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_MaterialColorDiffAmb(struct DL *displaylist, u32 diffuse_col, u32 ambient_col, u32 replace){
    *(u32 *)displaylist->var00 = 0x30;
    u32 replace_vtx_color_with_diffuse;
    if (replace)
        replace_vtx_color_with_diffuse = TRUE;
    else
        replace_vtx_color_with_diffuse = FALSE;
    *displaylist->var04 = diffuse_col | ambient_col << 0x10 | replace_vtx_color_with_diffuse << 0xF;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_MaterialColorSpecEmi(struct DL *displaylist, u32 specular_col, u32 emission_col, u32 shiny_table){
    *(u32 *)displaylist->var00 = 0x31;
    u32 enable_shininess_table;
    if (shiny_table)
        enable_shininess_table = TRUE;
    else
        enable_shininess_table = FALSE;
    *displaylist->var04 = specular_col | emission_col << 0x10 | enable_shininess_table << 0xF;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

/*
Only feed normalized Vectors
only the fractional part and the sign, which is in the first nonfraction bit
since the vector is assumed to be normalized, are used
*/
void G3B_LightVector(struct DL * displaylist, u32 light_num, fx16 x, fx16 y, fx16 z){
    *(u32 *)displaylist->var00 = 0x32;
    *displaylist->var04 = ((x >> 3) & 0x3FF) | (((y >> 3) & 0x3FF) << 0xA) | (((z >> 3) & 0x3FF) << 0x14) | light_num << 0x1E;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_LightColor(struct DL * displaylist, u32 light_num, u32 col){
    *(u32 *)displaylist->var00 = 0x33;
    *displaylist->var04 = col | light_num << 0x1E;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_Begin(struct DL * displaylist, u32 type){
    *(u32 *)displaylist->var00 = 0x40;
    *displaylist->var04 = type;
    displaylist->var00 = (u8 *)displaylist->var04 + 0x4;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}

void G3B_End(struct DL * displaylist){
    *(u32 *)displaylist->var00 = 0x41;
    displaylist->var00 = (u8 *)displaylist->var04;
    displaylist->var04 = (u32 *)displaylist->var00 + 1;
}
