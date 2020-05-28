//==============================================================================
/**
 * @file	contype_icon.h
 * @brief	コンテストタイプアイコンのヘッダ
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#ifndef __CONTYPE_ICON_H__
#define __CONTYPE_ICON_H__


//==============================================================================
//	外部関数宣言
//==============================================================================
extern u32 ConTypeIcon_CgrIDGet(int con_type);
extern u32 ConTypeIcon_PlttIDGet(void);
extern u32 ConTypeIcon_CellIDGet(void);
extern u32 ConTypeIcon_CellAnmIDGet(void);
extern u8 ConTypeIcon_PlttOffsetGet(int con_type);
extern u32 ConTypeIcon_ArcIDGet(void);
extern void ConTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	u32 cell_id, u32 anm_id);
extern void ConTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id);
extern void ConTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id);
extern void ConTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id);
extern void ConTypeIcon_ActorDelete(CATS_ACT_PTR cap);
extern void ConTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int con_type, u32 char_id);
extern void ConTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);
extern void ConTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id);
extern CATS_ACT_PTR ConTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int con_type, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data);


#endif	//__CONTYPE_ICON_H__

